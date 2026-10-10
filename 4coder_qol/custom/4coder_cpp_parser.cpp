////////////////////////////////
// NOTE(allen): Parser Helpers

function void
generic_parse_inc(Generic_Parse_State *state){
  if (!token_it_inc_all(&state->it)){
    state->finished = true;
  }
}

function void
generic_parse_skip_soft_tokens(Generic_Parse_State *state){
  for (;;){
    Token *token = token_it_read(&state->it);
    if (token == 0 || state->finished){ break; }
    if (state->in_preprocessor && !HasFlag(token->flags, TokenBaseFlag_PreprocessorBody)){ break; }
    else if (token->kind == TokenBaseKind_Comment){ /* could look for @META here or somth. */ }
    else if (token->kind == TokenBaseKind_Whitespace){
#if 0 // NOTE: Wasn't actually being used anywhere
      Range_i64 range = Ii64(token);
      u8 *ptr = state->contents.str + range.max - 1;
      u8 *end = state->contents.str + range.min - 1;
      for (; ptr != end; --ptr){
        if (*ptr == '\n'){
          state->prev_line_start = ptr + 1;
          break;
        }
      }
#endif
    }
    else{
      break;
    }
    generic_parse_inc(state);
  }
}

function void
generic_parse_init(Application_Links *app, Arena *arena, String_Const_u8 contents, Token_Array *tokens, Generic_Parse_State *state){
  state->app = app;
  state->arena = arena;
  state->contents = contents;
  state->it = token_iterator(0, tokens);
  state->prev_line_start = contents.str;
}

////////////////////////////////
// NOTE(allen): Parser

#if 0
/*
// NOTE(allen): grammar syntax
(X) = X
X Y = X and then Y
X? = zero or one X
$X = check for X but don't consume
[X] = zero or more Xs
X | Y = either X or Y
* = anything that does not match previous options in a X | Y | ... chain
* - X = anything that does not match X or previous options in a Y | Z | ... chain
<X> = a token of type X
"X" = literally the string "X"
X{Y} = X with flag Y

// NOTE(allen): grammar of code index parse
file: [preprocessor | scope | parens | function | type | * - <end-of-file>] <end-of-file>
preprocessor: <preprocessor> [scope | parens | stmnt]{pp-body}
scope: <scope-open> [preprocessor | scope | parens | * - <scope-close>] <scope-close>
paren: <paren-open> [preprocessor | scope | parens | * - <paren-close>] <paren-close>
stmnt-close-pattern: <scope-open> | <scope-close> | <paren-open> | <paren-close> | <stmnt-close> | <preprocessor>
stmnt: [type | * - stmnt-close-pattern] stmnt-close-pattern
type: struct | union | enum | typedef
struct: "struct" <identifier> $(";" | "{")
union: "union" <identifier> $(";" | "{")
enum: "enum" <identifier> $(";" | "{")
typedef: "typedef" [* - (<identifier> (";" | "("))] <identifier> $(";" | "(")
function: <identifier> >"(" ["(" ")" | * - ("(" | ")")] ")" ("{" | ";")
*/
#endif

function Code_Index_Note*
index_new_note(Code_Index_File *index, Generic_Parse_State *state, Range_i64 range, Code_Index_Note_Kind kind, Code_Index_Nest *parent){
  Code_Index_Note *result = push_array(state->arena, Code_Index_Note, 1);
  sll_queue_push(index->root.note_list.first, index->root.note_list.last, result);
  index->root.note_list.count += 1;
  result->note_kind = kind;
  result->pos = range;
  result->text = push_string_copy(state->arena, string_substring(state->contents, range));
  result->file = index;
  result->parent = parent;
  return(result);
}

function void
cpp_parse_using(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);

  Token *token = token_it_read(&state->it);
  if (token != 0 && token->kind == TokenBaseKind_Identifier){
    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(state);
    Token *peek = token_it_read(&state->it);
    if (peek != 0 && peek->sub_kind == TokenCppKind_Eq){
      generic_parse_inc(state);
      index_new_note(index, state, Ii64(token), CodeIndexNote_Type, parent);
    }
  }
}

function void
cpp_parse_extern(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);
  Token *token = token_it_read(&state->it);
  if (token == 0 || token->kind != TokenBaseKind_LiteralString){ return; }

  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);
  token = token_it_read(&state->it);
  if (token == 0 || token->kind != TokenBaseKind_ScopeOpen){ return; }

  Code_Index_Nest *result = push_array_zero(state->arena, Code_Index_Nest, 1);
  result->kind = CodeIndexNest_Scope;
  result->open = Ii64(token);
  result->close = Ii64(max_i64);
  result->file = index;
  result->parent = parent;

  state->scope_counter += 1;
  generic_parse_inc(state);

  if (generic_parse_top(index, state, result)){
    result->is_closed = true;
    result->close = Ii64(token_it_read(&state->it));
    generic_parse_inc(state);
  }

  result->nest_array = code_index_nest_ptr_array_from_list(state->arena, &result->nest_list); state->scope_counter -= 1;
  code_index_push_nest(&index->root.nest_list, result);
}

function void
cpp_parse_type_structure(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);
  if (state->finished){
    return;
  }

  Token *token = token_it_read(&state->it);
  if (token != 0 && token->kind == TokenBaseKind_Identifier){
    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(state);
    Token *peek = token_it_read(&state->it);
    if (peek != 0 && (peek->kind == TokenBaseKind_StmntClose ||
                      peek->kind == TokenBaseKind_ScopeOpen)){
      index_new_note(index, state, Ii64(token), CodeIndexNote_Type, parent);
      token = peek;
    }
  }
  if (token != 0 && token->kind == TokenBaseKind_ScopeOpen){
    Code_Index_Nest *nest = generic_parse_scope(index, state, parent);
    code_index_push_nest(&index->root.nest_list, nest);
  }
}

function void
cpp_parse_scan_comma(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  for (;;){
    generic_parse_skip_soft_tokens(state);
    Token *token = token_it_read(&state->it);
    if (token == 0 || state->finished){ break; }

    if (token->sub_kind == TokenCppKind_Comma){
      generic_parse_inc(state);
      break;
    }

    if (token->kind == TokenBaseKind_ScopeClose){
      break;
    }

    if (token->kind == TokenBaseKind_ScopeOpen){
      Code_Index_Nest *nest = generic_parse_scope(index, state, parent);
      code_index_push_nest(&index->root.nest_list, nest);
      continue;
    }

    if (token->kind == TokenBaseKind_ParenOpen){
      Code_Index_Nest *nest = generic_parse_paren(index, state, parent);
      code_index_push_nest(&index->root.nest_list, nest);
      continue;
    }

    generic_parse_inc(state);
  }
}

function void
cpp_parse_enum_list(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent, Token* open){
  generic_parse_inc(state);
  Code_Index_Nest *nest = push_array_zero(state->arena, Code_Index_Nest, 1);
  nest->kind = CodeIndexNest_Scope;
  nest->is_closed = false;
  nest->open = Ii64(open);
  nest->close = Ii64(max_i64);
  nest->file = index;
  nest->parent = parent;
  state->scope_counter += 1;

  for (;;){
    generic_parse_skip_soft_tokens(state);
    Token *token = token_it_read(&state->it);
    if (token == 0 || state->finished){ break; }

    if (token->kind == TokenBaseKind_ScopeClose){
      nest->is_closed = true;
      nest->close = Ii64(token);
      generic_parse_inc(state);
      generic_parse_skip_soft_tokens(state);
      break;
    }
    if (token->kind == TokenBaseKind_Identifier){
      index_new_note(index, state, Ii64(token), CodeIndexNote_Enum, parent);
      generic_parse_inc(state);
      cpp_parse_scan_comma(index, state, parent);
      continue;
    }

    generic_parse_inc(state);
  }

  state->scope_counter -= 1;
  nest->nest_array = code_index_nest_ptr_array_from_list(state->arena, &nest->nest_list);
  code_index_push_nest(&index->root.nest_list, nest);
}

function void
cpp_parse_enum(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  // "enum struct Kind : unsigned long long { E1, E2, ... };"
  generic_parse_inc(state);  // "enum"
  generic_parse_skip_soft_tokens(state);
  if (state->finished){ return; }

  Token *token = token_it_read(&state->it);
  if (token == 0){ return; }

  if (token->sub_kind == TokenCppKind_Struct || token->sub_kind == TokenCppKind_Class){
    generic_parse_inc(state);  // "struct" | "class"
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
    if (token == 0){ return; }
  }

  if (token->kind == TokenBaseKind_Identifier){
    index_new_note(index, state, Ii64(token), CodeIndexNote_Type, parent);
    generic_parse_inc(state);  // <iden>
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
    if (token == 0){ return; }
  }

  if (token->sub_kind == TokenCppKind_Colon){
    do {
      generic_parse_inc(state);  // ":" <int_type>*
      generic_parse_skip_soft_tokens(state);
      token = token_it_read(&state->it);
      if (token == 0){ return; }
    }while(token->kind == TokenBaseKind_Primitive || token->kind == TokenBaseKind_Identifier);
  }

  if (token->kind == TokenBaseKind_ScopeOpen){
    cpp_parse_enum_list(index, state, parent, token);  // "{" ... "}"
  }
}

function void
cpp_parse_type_def(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);
  for (;;){
    b32 did_advance = false;
    Token *token = token_it_read(&state->it);
    if (token == 0 || state->finished){
      break;
    }

    if (token->kind == TokenBaseKind_Identifier){
      did_advance = true;
      generic_parse_inc(state);
      generic_parse_skip_soft_tokens(state);
      Token *peek = token_it_read(&state->it);
      if (peek != 0 && (peek->kind == TokenBaseKind_StmntClose ||
                        peek->kind == TokenBaseKind_ParenOpen)){
        index_new_note(index, state, Ii64(token), CodeIndexNote_Type, parent);
        break;
      }
    }
    // typedef type (*func_type_name)( <params> )
    else if (token->kind == TokenBaseKind_ParenOpen){
      Token *paren = token;
      generic_parse_inc(state);
      generic_parse_skip_soft_tokens(state);
      Token *peek = token_it_read(&state->it);
      if (peek != 0 && peek->sub_kind == TokenCppKind_Star){
        generic_parse_inc(state);
        generic_parse_skip_soft_tokens(state);
        peek = token_it_read(&state->it);
        if (peek != 0 && peek->kind == TokenBaseKind_Identifier){
          index_new_note(index, state, Ii64(peek), CodeIndexNote_Type, parent);

          state->it = token_iterator(state, paren);
          Code_Index_Nest *nest = generic_parse_paren(index, state, parent);
          code_index_push_nest(&index->root.nest_list, nest);
          break;
        }
      }
      state->it = token_iterator(state, paren);
    }
    else if (token->kind == TokenBaseKind_StmntClose ||
             token->kind == TokenBaseKind_ScopeOpen ||
             token->kind == TokenBaseKind_ScopeClose ||
             token->kind == TokenBaseKind_ScopeOpen ||
             token->kind == TokenBaseKind_ScopeClose){
      break;
    }
    else if (token->kind == TokenBaseKind_Keyword ||
             token->kind == TokenBaseKind_Struct){
      if (token->sub_kind == TokenCppKind_Struct ||
          token->sub_kind == TokenCppKind_Union){
        cpp_parse_type_structure(index, state, parent);
        did_advance = true;
      }
      else if(token->sub_kind == TokenCppKind_Enum){
        cpp_parse_enum(index, state, parent);
        did_advance = true;
      }
    }
    if (!did_advance){
      generic_parse_inc(state);
      generic_parse_skip_soft_tokens(state);
    }
  }
}

function b32
generic_scan_parens(Code_Index_File *index, Generic_Parse_State *state){
  i32 paren_nest_level = 1;
  for (;;){
    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(state);
    Token *peek = token_it_read(&state->it);
    if (peek == 0 || state->finished){ return false; }
    paren_nest_level += (peek->kind == TokenBaseKind_ParenOpen);
    paren_nest_level -= (peek->kind == TokenBaseKind_ParenClose);
    if (paren_nest_level == 0){ return true; }
  }
}

function b32
cpp_parse_function(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  Token *token = token_it_read(&state->it);
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);
  if (state->finished){ return false; }

  Token *begin = token_it_read(&state->it);
  if (begin == 0 || begin->sub_kind != TokenCppKind_ParenOp){ return false; }

  if (generic_scan_parens(index, state)){
    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(state);
    Token *end = token_it_read(&state->it);
    if (end != 0 && end->kind == TokenBaseKind_ScopeOpen || end->kind == TokenBaseKind_StmntClose) {
      state->it = token_iterator(state, begin);
      Code_Index_Nest *nest = generic_parse_paren(index, state, parent);
      code_index_push_nest(&index->root.nest_list, nest);
      index_new_note(index, state, Ii64(token), CodeIndexNote_Function, parent);

      state->it = token_iterator(state, end);
      return true;
    }
  }

  state->it = token_iterator(state, begin);
  return false;
}

// <type> global :: <op>* <iden>{Emit} <op>* (';' | '=' <stmnt> | ',' <global>)
// e.g. My_Type g_var, *g_another;
// e.g. int** g_array[COUNT_Y][COUNT_X] = {};
function b32
cpp_parse_global(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  b32 result = false;
  generic_parse_inc(state);
  loop:;
  generic_parse_skip_soft_tokens(state);
  Token *token = token_it_read(&state->it);
  Token_Iterator_Array reset_it = state->it;
  Token *parens[16];  // im ok disallowing over 16-dimensional global arrays...
  Token *iden = 0;
  i64 paren_count = 0;

  // <op>*
  for (;;){
    if (token == 0 || state->finished){ goto fail; }
    if (token->sub_kind == TokenCppKind_BrackOp){
      if (!generic_scan_parens(index, state)){ goto fail; }
      if (paren_count >= ArrayCount(parens)){ goto fail; }
      parens[paren_count++] = token;
    }
    else if (token->kind != TokenBaseKind_Operator || token->sub_kind == TokenCppKind_Eq){ break; }

    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
  }

  // <iden>{Emit}
  if (token->kind != TokenBaseKind_Identifier){ goto fail; }
  iden = token;
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(state);
  token = token_it_read(&state->it);

  // <op>*
  for (;;){
    if (token == 0 || state->finished){ goto fail; }
    if (token->sub_kind == TokenCppKind_BrackOp){
      if (!generic_scan_parens(index, state)){ goto fail; }
      if (paren_count >= ArrayCount(parens)){ goto fail; }
      parens[paren_count++] = token;
    }
    else if (token->kind != TokenBaseKind_Operator || token->sub_kind == TokenCppKind_Eq){ break; }

    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
  }

  // [,;=]
  if (token->sub_kind == TokenCppKind_Comma || token->sub_kind == TokenCppKind_Semicolon || token->sub_kind == TokenCppKind_Eq){
    for (i64 i=0; i<paren_count; i += 1){
      state->it = token_iterator(state, parens[i]);
      Code_Index_Nest *nest = generic_parse_paren(index, state, parent);
      code_index_push_nest(&index->root.nest_list, nest);
    }

    state->it = token_iterator(state, token);
    generic_parse_inc(state);
    index_new_note(index, state, Ii64(iden), CodeIndexNote_Global, parent);

    if (token->sub_kind == TokenCppKind_Eq){
      for (;;){
        generic_parse_skip_soft_tokens(state);
        token = token_it_read(&state->it);
        if (token == 0 || state->finished){ break; }

        if (token->sub_kind == TokenCppKind_Comma){ generic_parse_inc(state); goto loop; }
        if (token->kind == TokenBaseKind_StmntClose){ generic_parse_inc(state); break; }
        if (token->kind == TokenBaseKind_ScopeClose){ break; }
        if (token->kind == TokenBaseKind_ScopeOpen){
          Code_Index_Nest *nest = generic_parse_scope(index, state, parent);
          code_index_push_nest(&index->root.nest_list, nest);
          continue;
        }

        if (token->kind == TokenBaseKind_ParenOpen){
          Code_Index_Nest *nest = generic_parse_paren(index, state, parent);
          code_index_push_nest(&index->root.nest_list, nest);
          continue;
        }

        generic_parse_inc(state);
      }
    }
    if (token->sub_kind == TokenCppKind_Comma){
      goto loop;
    }
    return true;
  }

  fail:
  state->it = reset_it;
  return result;
}

function Code_Index_Nest*
generic_parse_statement(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  Token *token = token_it_read(&state->it);
  Code_Index_Nest *result = push_array_zero(state->arena, Code_Index_Nest, 1);
  result->kind = CodeIndexNest_Statement;
  result->open = Ii64(token->pos);
  result->close = Ii64(max_i64);
  result->file = index;
  result->parent = parent;

  state->in_statement = true;

  for (;;){
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
    if (token == 0 || state->finished){
      break;
    }

    if (state->in_preprocessor){
      if (!HasFlag(token->flags, TokenBaseFlag_PreprocessorBody) ||
          token->kind == TokenBaseKind_Preproc){
        result->is_closed = true;
        result->close = Ii64(token->pos);
        break;
      }
    }
    else{
      if (token->kind == TokenBaseKind_Preproc){
        result->is_closed = true;
        result->close = Ii64(token->pos);
        break;
      }
    }

    if (token->kind == TokenBaseKind_ScopeOpen ||
        token->kind == TokenBaseKind_ScopeClose ||
        token->kind == TokenBaseKind_ParenOpen){
      result->is_closed = true;
      result->close = Ii64(token->pos);
      break;
    }

    if (token->kind == TokenBaseKind_StmntClose){
      result->is_closed = true;
      result->close = Ii64(token);
      generic_parse_inc(state);
      break;
    }

    generic_parse_inc(state);
  }

  state->in_statement = false;

  return(result);
}

function Code_Index_Nest*
generic_parse_preproc(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  Token *token = token_it_read(&state->it);
  Code_Index_Nest *result = push_array_zero(state->arena, Code_Index_Nest, 1);
  result->kind = CodeIndexNest_Preprocessor;
  result->open = Ii64(token->pos);
  result->close = Ii64(max_i64);
  result->file = index;
  result->parent = parent;

  state->in_preprocessor = true;

  b32 potential_macro  = false;
  if (state->do_cpp_parse){
    if (token->sub_kind == TokenCppKind_PPDefine){
      potential_macro = true;
    }
  }

  generic_parse_inc(state);
  for (;;){
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
    if (token == 0 || state->finished){
      break;
    }

    if (!HasFlag(token->flags, TokenBaseFlag_PreprocessorBody) ||
        token->kind == TokenBaseKind_Preproc){
      result->is_closed = true;
      result->close = Ii64(token->pos);
      break;
    }

    if (state->do_cpp_parse && potential_macro){
      if (token->sub_kind == TokenCppKind_Identifier){
        index_new_note(index, state, Ii64(token), CodeIndexNote_Macro, result);
      }
      potential_macro = false;
    }

    if (token->kind == TokenBaseKind_ScopeOpen){
      Code_Index_Nest *nest = generic_parse_scope(index, state, result);
      code_index_push_nest(&result->nest_list, nest);
      continue;
    }

    if (token->kind == TokenBaseKind_ParenOpen){
      Code_Index_Nest *nest = generic_parse_paren(index, state, result);
      code_index_push_nest(&result->nest_list, nest);
      continue;
    }

    generic_parse_inc(state);
  }

  result->nest_array = code_index_nest_ptr_array_from_list(state->arena, &result->nest_list);

  state->in_preprocessor = false;

  return(result);
}

function Code_Index_Nest*
generic_parse_scope(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  Token *token = token_it_read(&state->it);
  Code_Index_Nest *result = push_array_zero(state->arena, Code_Index_Nest, 1);
  result->kind = CodeIndexNest_Scope;
  result->open = Ii64(token);
  result->close = Ii64(max_i64);
  result->file = index;
  result->parent = parent;

  state->scope_counter += 1;

  generic_parse_inc(state);
  for (;;){
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
    if (token == 0 || state->finished){
      break;
    }

    if (state->in_preprocessor){
      if (!HasFlag(token->flags, TokenBaseFlag_PreprocessorBody) ||
          token->kind == TokenBaseKind_Preproc){
        break;
      }
    }
    else{
      if (token->kind == TokenBaseKind_Preproc){
        Code_Index_Nest *nest = generic_parse_preproc(index, state, parent);
        code_index_push_nest(&index->root.nest_list, nest);
        continue;
      }
    }

    if (token->kind == TokenBaseKind_ScopeClose){
      result->is_closed = true;
      result->close = Ii64(token);
      generic_parse_inc(state);
      break;
    }

    if (token->kind == TokenBaseKind_ScopeOpen){
      Code_Index_Nest *nest = generic_parse_scope(index, state, result);
      code_index_push_nest(&result->nest_list, nest);
      continue;
    }

    if (token->kind == TokenBaseKind_ParenClose){
      generic_parse_inc(state);
      continue;
    }

    if (token->kind == TokenBaseKind_ParenOpen){
      Code_Index_Nest *nest = generic_parse_paren(index, state, result);
      code_index_push_nest(&result->nest_list, nest);

      // NOTE(allen): after a parenthetical group we consider ourselves immediately
      // transitioning into a statement
      nest = generic_parse_statement(index, state, result);
      code_index_push_nest(&result->nest_list, nest);

      continue;
    }

    {
      Code_Index_Nest *nest = generic_parse_statement(index, state, result);
      code_index_push_nest(&result->nest_list, nest);
    }
  }

  result->nest_array = code_index_nest_ptr_array_from_list(state->arena, &result->nest_list);

  state->scope_counter -= 1;

  return(result);
}

function Code_Index_Nest*
generic_parse_paren(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  Token *token = token_it_read(&state->it);
  Code_Index_Nest *result = push_array_zero(state->arena, Code_Index_Nest, 1);
  result->kind = CodeIndexNest_Paren;
  result->open = Ii64(token);
  result->close = Ii64(max_i64);
  result->file = index;
  result->parent = parent;
  state->paren_counter += 1;

  generic_parse_inc(state);
  for (;;){
    generic_parse_skip_soft_tokens(state);
    token = token_it_read(&state->it);
    if (token == 0 || state->finished){
      break;
    }

    if (state->in_preprocessor){
      if (!HasFlag(token->flags, TokenBaseFlag_PreprocessorBody) ||
          token->kind == TokenBaseKind_Preproc){
        break;
      }
    }
    else{
      if (token->kind == TokenBaseKind_Preproc){
        Code_Index_Nest *nest = generic_parse_preproc(index, state, parent);
        code_index_push_nest(&index->root.nest_list, nest);
        continue;
      }
    }

    if (token->kind == TokenBaseKind_ParenClose){
      result->is_closed = true;
      result->close = Ii64(token);
      generic_parse_inc(state);
      break;
    }

    if (token->kind == TokenBaseKind_ScopeClose){
      break;
    }

    if (token->kind == TokenBaseKind_ScopeOpen){
      Code_Index_Nest *nest = generic_parse_scope(index, state, result);
      code_index_push_nest(&result->nest_list, nest);
      continue;
    }

    if (token->kind == TokenBaseKind_ParenOpen){
      Code_Index_Nest *nest = generic_parse_paren(index, state, result);
      code_index_push_nest(&result->nest_list, nest);
      continue;
    }

    generic_parse_inc(state);
  }

  result->nest_array = code_index_nest_ptr_array_from_list(state->arena, &result->nest_list);

  state->paren_counter -= 1;

  return(result);
}

function b32
generic_parse_top(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  b32 result = false;
  for (;;){
    generic_parse_skip_soft_tokens(state);
    Token *token = token_it_read(&state->it);

    if (token == 0 || state->finished){
      result = true;
      break;
    }

    if (parent != 0 && token->kind == TokenBaseKind_ScopeClose){
      result = true;
      break;
    }
    else if (token->kind == TokenBaseKind_Preproc) { code_index_push_nest(&index->root.nest_list, generic_parse_preproc(index, state, parent)); }
    else if (token->kind == TokenBaseKind_ScopeOpen)    { code_index_push_nest(&index->root.nest_list, generic_parse_scope  (index, state, parent)); }
    else if (token->kind == TokenBaseKind_ParenOpen)    { code_index_push_nest(&index->root.nest_list, generic_parse_paren  (index, state, parent)); }
    else if (state->do_cpp_parse){
      /**/ if (token->sub_kind == TokenCppKind_Enum)   { cpp_parse_enum(index, state, parent); }
      else if (token->sub_kind == TokenCppKind_Struct) { cpp_parse_type_structure(index, state, parent); }
      else if (token->sub_kind == TokenCppKind_Union)  { cpp_parse_type_structure(index, state, parent); }
      else if (token->sub_kind == TokenCppKind_Typedef){ cpp_parse_type_def(index, state, parent); }
      else if (token->sub_kind == TokenCppKind_Using)  { cpp_parse_using(index, state, parent); }
      else if (token->sub_kind == TokenCppKind_Extern) { cpp_parse_extern(index, state, parent); }
      else if (token->sub_kind == TokenCppKind_Identifier && cpp_parse_function(index, state, parent)){ }
      else if (token->sub_kind == TokenCppKind_Identifier || token->kind == TokenBaseKind_Primitive){
        state->it = token_iterator(state, token);
        cpp_parse_global(index, state, parent);
      }
      else{
        generic_parse_inc(state);
      }
    }
    else{
      generic_parse_inc(state);
    }

    if (state->token_it_index_opl <= token_it_index(&state->it)){
      token = token_it_read(&state->it);
      if (token == 0){
        result = true;
      }
      break;
    }
  }

  if (result){
    index->root.nest_array = code_index_nest_ptr_array_from_list(state->arena, &index->root.nest_list);
    index->root.note_array = code_index_note_ptr_array_from_list(state->arena, &index->root.note_list);
  }

  return(result);
}

function b32
generic_parse_full_input_breaks(Code_Index_File *index, Generic_Parse_State *state, i32 limit){
  state->token_it_index_opl = token_it_index(&state->it) + limit;
  return(generic_parse_top(index, state, NULL));
}