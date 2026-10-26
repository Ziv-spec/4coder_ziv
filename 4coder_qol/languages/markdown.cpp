
struct Lex_Markdown_State {
  u8 *str;
  i64 begin;
  i64 size;
};

enum Markdown_TokenSubKind {
  Markdown_TokenSubKind_None,
  Markdown_TokenSubKind_Heading,
  Markdown_TokenSubKind_Tag,
  Markdown_TokenSubKind_Italic,
  Markdown_TokenSubKind_Bold,
  Markdown_TokenSubKind_Code,
};

internal void
lex_full_input_markdown_init(Lex_Markdown_State *state_ptr, String_Const_u8 input){
  state_ptr->str = input.str;
  state_ptr->size = input.size;
  state_ptr->begin = 0;
}

// NOTE(edye): based on F4_MD_CharIsSymbol
internal b32
is_operator(u8 c)
{
  return (c == '~' || c == '!' || c == '@' || c == '#' || c == '$' ||
          c == '%' || c == '^' || c == '&' || c == '*' || c == '(' ||
          c == ')' || c == '-' || c == '=' || c == '+' || c == '[' ||
          c == ']' || c == '{' || c == '}' || c == ':' || c == ';' ||
          c == ',' || c == '<' || c == '.' || c == '>' || c == '/' ||
          c == '?' || c == '|' || c == '\\');
}

internal b32
lex_full_input_markdown_breaks(Arena *arena, Token_List *list, Lex_Markdown_State  *state_ptr, u64 max) {

  u64 emit_counter = 0;

  Lex_Markdown_State state;
  block_copy_struct(&state, state_ptr);

  i64 i = state.begin;
  for (; i < state.size;) {
    char c = state.str[i];

    // Whitespace
    if (character_is_whitespace(c)) {
      i64 inner = i+1;
      for (; inner < state.size; inner++) {
        if (!character_is_whitespace(state.str[inner])) {
          break;
        }
      }

      Token token = {};
      token.pos  = i;
      token.size = inner - i;
      token.kind = TokenBaseKind_Whitespace;
      token_list_push(arena, list, &token); // adding a token

      i = inner;
    }

    // Heading
    else if (c == '#') {

      b32 is_heading = true;
      u16 heading_level = 1; // heading1 or heading2 and so on...

      // the #### part
      i64 inner = i+1;
      for (; inner < state.size; inner++) {
        if (is_heading && state.str[inner] == '#') {
          heading_level++; // TODO(ziv): currently I don't handle cases where I have more than 64k # one after the other, I just overflow which is fine I think ?
        }
        else {
          break;
        }
      }

      // everything upto newline (including)
      for (; inner < state.size; inner++) {
        if (state.str[inner] == '\n') {
          break;
        }
      }

      Token token = {};
      token.pos  = i;
      token.size = inner - i;
      token.kind = TokenBaseKind_Identifier;
      token.sub_kind = Markdown_TokenSubKind_Heading;
      token.sub_flags = heading_level; // heading level
      token_list_push(arena, list, &token); // adding a token

      i = inner;
    }

    // Tags
    else if(c == '@')
    {
      i64 inner = i+1;
      for (; inner < state.size; inner++) {
        if (!character_is_alpha_numeric(state.str[inner])) {
          break;
        }
      }

      Token token = {};
      token.pos = i;
      token.size = inner-i;
      token.kind = TokenBaseKind_Identifier;
      token.sub_kind = Markdown_TokenSubKind_Tag;
      token_list_push(arena, list, &token);

      i = inner;
    }

    #if 0
    // italics
    else if (c == '_') {

      i64 inner = i+1;
      for (; inner < state.size; inner++) {

        if (!(('a' <= state.str[inner] && state.str[inner] <= 'z') ||
              ('A' <= state.str[inner] && state.str[inner] <= 'Z') ||
              ('0' <= state.str[inner] && state.str[inner] <= '9'))) {
          break;
        }
      }

      if () {

      }
    }
    #endif

    // number list e.g.   1. 2. 3. and so on...
    else if ('0' <= c && c <= '9') {

      i64 inner = i+1;
      for (; inner < state.size; inner++) {
        if (!(('0' <= state.str[inner]) && (state.str[inner] <= '9'))) {
          break;
        }
      }

      Token token = {};
      token.pos = i;
      if (state.str[inner] == '.') {
        token.kind = TokenBaseKind_LiteralInteger;
        inner += 1; // include '.' in the token
      }
      else {
        token.kind = TokenBaseKind_Identifier;
      }
      token.size = inner-i;
      token_list_push(arena, list, &token);

      i = inner;
    }

    // Identifier
    else if (character_is_alpha_numeric(c)) {
      i64 inner = i+1;
      for (; inner < state.size; inner++) {
        if (!character_is_alpha_numeric(state.str[inner])) {
          break;
        }
      }

      Token token = {};
      token.pos = i;
      token.size = inner-i;
      token.kind = TokenBaseKind_Identifier;
      token_list_push(arena, list, &token);

      i = inner;
    }

    #define EMIT_SIZE_1_TOKEN(pos, kind) \
    Token t = { pos, 1, kind, 0 };       \
    token_list_push(arena, list, &t);    \
    pos += 1;

    else if(c == '>')             { EMIT_SIZE_1_TOKEN(i, TokenBaseKind_Comment);  }
    else if(c == '{')             { EMIT_SIZE_1_TOKEN(i, TokenBaseKind_ScopeOpen);  }
    else if(c == '}')             { EMIT_SIZE_1_TOKEN(i, TokenBaseKind_ScopeClose); }
    else if(c == '(' || c == '[') { EMIT_SIZE_1_TOKEN(i, TokenBaseKind_ParenOpen);  }
    else if(c == ')' || c == ']') { EMIT_SIZE_1_TOKEN(i, TokenBaseKind_ParenClose); }
    else if(c == '\''|| c == '\"'){ EMIT_SIZE_1_TOKEN(i, TokenBaseKind_Operator); }
    else if(is_operator(c))       { EMIT_SIZE_1_TOKEN(i, TokenBaseKind_Operator);   }
    else if(c == ',' || c == ';' || (c == '-' && i+1 < state.size && state.str[i+1] == '>')) {
      EMIT_SIZE_1_TOKEN(i, TokenBaseKind_StmntClose);
    }
    else // Catch all
    {
      EMIT_SIZE_1_TOKEN(i, TokenBaseKind_LexError);
    }

    // limit the amount of tokens to lex at a time for partial lexing
    emit_counter += 1;
    if (emit_counter >= max) {
      break;
    }

  }

  state.begin = i;
  *state_ptr = state;

  if (i >= state.size) {
    EMIT_SIZE_1_TOKEN(i, TokenBaseKind_EOF);
    return true;
  }
  #undef EMIT_SIZE_1_TOKEN

  return false;
}

internal Token_List
lex_full_input_markdown(Arena *arena, String_Const_u8 input){
  Lex_Markdown_State state = {};
  lex_full_input_markdown_init(&state, input);
  Token_List list = {};
  lex_full_input_markdown_breaks(arena, &list, &state, max_u64);
  return(list);
}

internal Token_List
lex_full_input_async_markdown(Async_Context *actx, Arena *arena, String_Const_u8 input, i32 limit, b32 *canceled){
  Lex_Markdown_State state = {};
  Token_List list = {};
  lex_full_input_markdown_init(&state, input);
  for (;;){
    if (lex_full_input_markdown_breaks(arena, &list, &state, limit)){
      break;
    }
    if (async_check_canceled(actx)){
      *canceled = true;
      break;
    }
  }
  return(list);
}

function FColor qol_get_token_color_markdown(Token *token){
  switch(token->sub_kind){
    case Markdown_TokenSubKind_Tag:      return fcolor_id(defcolor_comment_pop, 2);
    case Markdown_TokenSubKind_Heading:  return fcolor_id(defcolor_function);
  }
  return fcolor_id(qol_get_token_color_base(token));
}