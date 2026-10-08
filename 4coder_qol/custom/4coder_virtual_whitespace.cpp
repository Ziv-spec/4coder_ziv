////////////////////////////////
// NOTE(allen): Virtual Whitespace Layout

function f32 layout_indent(Code_Index_Nest *n, i64 pos, f32 indent){
  return pos == n->open.min || (pos == n->close.max && n->close.min != n->close.max) || n->close.min <= pos && n->is_closed ? 0.f : indent;
}

// TODO: maybe somth. else idk...
global b32 g_anchor_pproc = true;
global i64 g_x_shift_id = 1;

function void
layout_init_vws_table(){
  g_x_shift_id += 1;
  VWS_Action VWS_ACT_PProc = g_anchor_pproc ? VWS_ACT_Reset : VWS_ACT_Nop;
  vws_table[VWS_Q_Start][CodeIndexNest_PProc] = {VWS_Q_Start, VWS_ACT_PProc};
  vws_table[VWS_Q_Start][CodeIndexNest_Scope] = {VWS_Q_Start, VWS_ACT_Inc};
  vws_table[VWS_Q_Start][CodeIndexNest_Paren] = {VWS_Q_Paren, VWS_ACT_Reflex};
  vws_table[VWS_Q_Start][CodeIndexNest_Stmnt] = {VWS_Q_Start, VWS_ACT_Inc};
  vws_table[VWS_Q_Paren][CodeIndexNest_PProc] = {VWS_Q_Start, VWS_ACT_PProc};
  vws_table[VWS_Q_Paren][CodeIndexNest_Scope] = {VWS_Q_Start, VWS_ACT_Inc};
  vws_table[VWS_Q_Paren][CodeIndexNest_Paren] = {VWS_Q_Paren, VWS_ACT_Reflex};
  vws_table[VWS_Q_Paren][CodeIndexNest_Stmnt] = {VWS_Q_Paren, VWS_ACT_Nop};
}

function f32
layout_index_x_shift(Application_Links *app, Layout_Reflex *reflex, Code_Index_File *file, i64 pos, f32 regular_indent, b32 *unresolved_dependence){
  VWS_State state = {};
  state.q = VWS_Q_Start;
  state.reflex_pos = -1;

  Code_Index_Nest_Ptr_Array *array = &file->nest_array;
  Code_Index_Nest *nest = NULL;
  for (;;){
    b32 found = false;
    for (i64 i=0; i<array->count; i += 1){
      Code_Index_Nest *n = array->ptrs[i];
      if (n->open.min <= pos && pos <= n->close.min){
        nest = n;
        array = &n->nest_array;
        VWS_Transition t = vws_table[state.q][n->kind];
        switch (t.act){
          case VWS_ACT_Nop: break;
          case VWS_ACT_Reset:                            { state.shift  = layout_indent(nest, pos, regular_indent); state.reflex_pos = -1; }break;
          case VWS_ACT_Reflex: if (pos != nest->open.min){ state.shift  = 0.f;                                      state.reflex_pos = nest->open.max-1; }break;
          case VWS_ACT_Inc:                              { state.shift += layout_indent(nest, pos, regular_indent); }break;
        }
        state.q = t.q;
        found = true;
      }
    }
    if (!found){ break; }
  }

  if (state.reflex_pos != -1){
    state.shift += layout_reflex_get_rect(app, reflex, state.reflex_pos, unresolved_dependence).x1;
  }

  return state.shift;
}

function f32
layout_index_x_shift(Application_Links *app, Layout_Reflex *reflex, Code_Index_File *file, i64 pos, f32 regular_indent){
  b32 ignore;
  return(layout_index_x_shift(app, reflex, file, pos, regular_indent, &ignore));
}

global Code_Index_Nest *g_nest_walk = NULL;

function Code_Index_Nest*
layout_index_x_shift_walk_(Code_Index_File *file, i64 pos){
  //return code_index_get_nest(file, pos);
  if (g_nest_walk == NULL || g_nest_walk->file != file){
    return g_nest_walk = code_index_get_nest(file, pos);
  }
  return g_nest_walk = code_index_nest_walk(g_nest_walk, pos);
}

function f32
layout_index_x_shift_walk(Application_Links *app, Layout_Reflex *reflex, Code_Index_File *file, i64 pos, f32 regular_indent, b32 *unresolved_dependence){
  //Code_Index_Nest *nest = layout_index_x_shift_walk_(file, pos);
  //if (nest == NULL){ return 0; }
  //return layout_index_x_shift(app, reflex, nest, pos, regular_indent, unresolved_dependence);
  return layout_index_x_shift(app, reflex, file, pos, regular_indent, unresolved_dependence);
}

function f32
layout_index_x_shift_walk(Application_Links *app, Layout_Reflex *reflex, Code_Index_File *file, i64 pos, f32 regular_indent){
  b32 ignore;
  return layout_index_x_shift_walk(app, reflex, file, pos, regular_indent, &ignore);
}

function void
layout_index__emit_chunk(LefRig_TopBot_Layout_Vars *pos_vars, Face_ID face, Arena *arena, u8 *text_str, i64 range_first, u8 *ptr, u8 *end, Layout_Item_List *list){
  for (;ptr < end;){
    Character_Consume_Result consume = utf8_consume(ptr, (u64)(end - ptr));
    if (consume.codepoint != '\r'){
      i64 index = layout_index_from_ptr(ptr, text_str, range_first);
      if (consume.codepoint != max_u32){
        lr_tb_write(pos_vars, face, arena, list, index, consume.codepoint);
      }
      else{
        lr_tb_write_byte(pos_vars, face, arena, list, index, *ptr);
      }
    }
    ptr += consume.inc;
  }
}

function Token_Pair
layout_token_pair(Token_Array *tokens, i64 pos){
  Token_Pair result = {};
  Token_Iterator_Array it = token_iterator_pos(0, tokens, pos);
  Token *b = token_it_read(&it);
  if (b != 0){
    if (b->kind == TokenBaseKind_Whitespace){
      token_it_inc_non_whitespace(&it);
      b = token_it_read(&it);
    }
  }
  token_it_dec_non_whitespace(&it);
  Token *a = token_it_read(&it);
  if (a != 0){ result.a = *a; }
  if (b != 0){ result.b = *b; }
  return(result);
}

function i32
layout_token_score_wrap_token(Token_Pair *pair, Token_Cpp_Kind kind){
  i32 result = 0;
  if (pair->a.sub_kind != kind && pair->b.sub_kind == kind){
    result -= 1;
  }
  else if (pair->a.sub_kind == kind && pair->b.sub_kind != kind){
    result += 1;
  }
  return(result);
}

function Layout_Item_List
layout_index__inner(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width, Code_Index_File *file, Layout_Wrap_Kind kind){
  layout_init_vws_table();
  Scratch_Block scratch(app, arena);

  Token_Array tokens = get_token_array_from_buffer(app, buffer);
  Token_Array *tokens_ptr = &tokens;

  Layout_Item_List list = get_empty_item_list(range);
  String_Const_u8 text = push_buffer_range(app, scratch, buffer, range);

  Face_Advance_Map advance_map = get_face_advance_map(app, face);
  Face_Metrics metrics = get_face_metrics(app, face);
  f32 tab_width = (f32)def_get_config_u64(app, vars_save_string_lit("default_tab_width"));
  tab_width = clamp_bot(1, tab_width);
  LefRig_TopBot_Layout_Vars pos_vars = get_lr_tb_layout_vars(&advance_map, &metrics, tab_width, width);

  u64 vw_indent = def_get_config_u64(app, vars_save_string_lit("virtual_whitespace_regular_indent"));
  f32 regular_indent = metrics.space_advance*vw_indent;
  f32 wrap_align_x = width - metrics.normal_advance;

  Layout_Reflex reflex = get_layout_reflex(&list, buffer, width, face);

  if (text.size == 0){
    lr_tb_write_blank(&pos_vars, face, arena, &list, range.start);
  }
  else{
    b32 first_of_the_line = true;
    Newline_Layout_Vars newline_vars = get_newline_layout_vars();

    u8 *ptr = text.str;
    u8 *end_ptr = ptr + text.size;
    u8 *word_ptr = ptr;

    u8 *pending_wrap_ptr = ptr;
    f32 pending_wrap_x = 0.f;
    i32 pending_wrap_paren_nest_count = 0;
    i32 pending_wrap_token_score = 0;
    f32 pending_wrap_accumulated_w = 0.f;

    start:
    if (ptr == end_ptr){
      i64 index = layout_index_from_ptr(ptr, text.str, range.first);
      f32 shift = layout_index_x_shift_walk(app, &reflex, file, index, regular_indent);
      lr_tb_advance_x_without_item(&pos_vars, shift);
      goto finish;
    }

    if (!character_is_whitespace(*ptr)){
      i64 index = layout_index_from_ptr(ptr, text.str, range.first);
      f32 shift = layout_index_x_shift_walk(app, &reflex, file, index, regular_indent);
      lr_tb_advance_x_without_item(&pos_vars, shift);
      goto consuming_non_whitespace;
    }

    {
      for (;ptr < end_ptr; ptr += 1){
        if (!character_is_whitespace(*ptr)){
          pending_wrap_ptr = ptr;
          word_ptr = ptr;
          i64 index = layout_index_from_ptr(ptr, text.str, range.first);
          f32 shift = layout_index_x_shift_walk(app, &reflex, file, index, regular_indent);
          lr_tb_advance_x_without_item(&pos_vars, shift);
          goto consuming_non_whitespace;
        }
        if (*ptr == '\r'){
          i64 index = layout_index_from_ptr(ptr, text.str, range.first);
          newline_layout_consume_CR(&newline_vars, index);
        }
        else if (*ptr == '\n'){
          pending_wrap_ptr = ptr;
          i64 index = layout_index_from_ptr(ptr, text.str, range.first);
          f32 shift = layout_index_x_shift_walk(app, &reflex, file, index, regular_indent);
          lr_tb_advance_x_without_item(&pos_vars, shift);
          goto consuming_normal_whitespace;
        }
      }

      if (ptr == end_ptr){
        pending_wrap_ptr = ptr;
        i64 index = layout_index_from_ptr(ptr - 1, text.str, range.first);
        f32 shift = layout_index_x_shift_walk(app, &reflex, file, index, regular_indent);
        lr_tb_advance_x_without_item(&pos_vars, shift);
        goto finish;
      }
    }

    consuming_non_whitespace:
    {
      for (;ptr <= end_ptr; ptr += 1){
        if (ptr == end_ptr || character_is_whitespace(*ptr)){
          break;
        }
      }

      // NOTE(allen): measure this word
      newline_layout_consume_default(&newline_vars);
      String_Const_u8 word = SCu8(word_ptr, ptr);
      u8 *word_end = ptr;
      {
        f32 word_advance = 0.f;
        ptr = word.str;
        for (;ptr < word_end;){
          Character_Consume_Result consume = utf8_consume(ptr, (u64)(word_end - ptr));
          if (consume.codepoint != max_u32){
            word_advance += lr_tb_advance(&pos_vars, face, consume.codepoint);
          }
          else{
            word_advance += lr_tb_advance_byte(&pos_vars);
          }
          ptr += consume.inc;
        }
        pending_wrap_accumulated_w += word_advance;
      }

      if (!first_of_the_line && (kind == Layout_Wrapped) && lr_tb_crosses_width(&pos_vars, pending_wrap_accumulated_w)){
        i64 index = layout_index_from_ptr(pending_wrap_ptr, text.str, range.first);
        lr_tb_align_rightward(&pos_vars, wrap_align_x);
        lr_tb_write_ghost(&pos_vars, face, arena, &list, index, '\\');

        lr_tb_next_line(&pos_vars);
#if 0
        f32 shift = layout_index_x_shift_walk(app, &reflex, file, index, regular_indent);
        lr_tb_advance_x_without_item(&pos_vars, shift);
#endif

        ptr = pending_wrap_ptr;
        pending_wrap_accumulated_w = 0.f;
        first_of_the_line = true;
        goto start;
      }
    }

    consuming_normal_whitespace:
    for (; ptr < end_ptr; ptr += 1){
      if (!character_is_whitespace(*ptr)){
        u8 *new_wrap_ptr = ptr;

        i64 index = layout_index_from_ptr(new_wrap_ptr, text.str, range.first);
        Code_Index_Nest *new_wrap_nest = layout_index_x_shift_walk_(file, index);
        //Code_Index_Nest *new_wrap_nest = code_index_get_nest(file, index);
        b32 invalid_wrap_x = false;
        //f32 new_wrap_x = layout_index_x_shift(app, &reflex, new_wrap_nest, index, regular_indent, &invalid_wrap_x);
        f32 new_wrap_x = layout_index_x_shift(app, &reflex, file, index, regular_indent, &invalid_wrap_x);
        if (invalid_wrap_x){
          new_wrap_x = max_f32;
        }

        i32 new_wrap_paren_nest_count = 0;
        for (Code_Index_Nest *nest = new_wrap_nest;
             nest != 0;
             nest = nest->parent){
          if (nest->kind == CodeIndexNest_Paren){
            new_wrap_paren_nest_count += 1;
          }
        }

        Token_Pair new_wrap_token_pair = layout_token_pair(tokens_ptr, index);

        // TODO(allen): pull out the token scoring part and make it replacable for other
        // language's token based wrap scoring needs.
        i32 token_score = 0;
        if (new_wrap_token_pair.a.kind == TokenBaseKind_Keyword){
          if (new_wrap_token_pair.b.kind == TokenBaseKind_ParenOpen ||
              new_wrap_token_pair.b.kind == TokenBaseKind_Keyword){
            token_score -= 2;
          }
        }
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_Eq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_PlusEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_MinusEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_StarEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_DivEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_ModEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_LeftLeftEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_RightRightEq);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_Comma);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_AndAnd);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_OrOr);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_Ternary);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_Colon);
        token_score += layout_token_score_wrap_token(&new_wrap_token_pair, TokenCppKind_Semicolon);

        i32 new_wrap_token_score = token_score;

        b32 new_wrap_ptr_is_better = false;
        if (first_of_the_line){
          new_wrap_ptr_is_better = true;
        }
        else{
          if (new_wrap_token_score > pending_wrap_token_score){
            new_wrap_ptr_is_better = true;
          }
          else if (new_wrap_token_score == pending_wrap_token_score){
            f32 new_score = new_wrap_paren_nest_count*10.f + new_wrap_x;
            f32 old_score = pending_wrap_paren_nest_count*10.f + pending_wrap_x + metrics.normal_advance*4.f + pending_wrap_accumulated_w*0.5f;

            if (new_score < old_score){
              new_wrap_ptr_is_better = true;
            }
          }
        }

        if (new_wrap_ptr_is_better){
          layout_index__emit_chunk(&pos_vars, face, arena, text.str, range.first, pending_wrap_ptr, new_wrap_ptr, &list);
          first_of_the_line = false;

          pending_wrap_ptr = new_wrap_ptr;
          pending_wrap_paren_nest_count = new_wrap_paren_nest_count;
          pending_wrap_x = layout_index_x_shift(app, &reflex, file, index, regular_indent);
          pending_wrap_paren_nest_count = new_wrap_paren_nest_count;
          pending_wrap_token_score = new_wrap_token_score;
          pending_wrap_accumulated_w = 0.f;
        }

        word_ptr = ptr;
        goto consuming_non_whitespace;
      }

      i64 index = layout_index_from_ptr(ptr, text.str, range.first);
      switch (*ptr){
        default:
        {
          newline_layout_consume_default(&newline_vars);
          pending_wrap_accumulated_w += lr_tb_advance(&pos_vars, face, *ptr);
        }break;

        case '\r':
        {
          newline_layout_consume_CR(&newline_vars, index);
        }break;

        case '\n':
        {
          layout_index__emit_chunk(&pos_vars, face, arena, text.str, range.first, pending_wrap_ptr, ptr, &list);
          pending_wrap_ptr = ptr + 1;
          pending_wrap_accumulated_w = 0.f;

          u64 newline_index = newline_layout_consume_LF(&newline_vars, index);
          lr_tb_write_blank(&pos_vars, face, arena, &list, newline_index);
          lr_tb_next_line(&pos_vars);
          first_of_the_line = true;
          ptr += 1;
          goto start;
        }break;
      }
    }

    finish:
    if (newline_layout_consume_finish(&newline_vars)){
      layout_index__emit_chunk(&pos_vars, face, arena, text.str, range.first, pending_wrap_ptr, ptr, &list);
      i64 index = layout_index_from_ptr(ptr, text.str, range.first);
      lr_tb_write_blank(&pos_vars, face, arena, &list, index);
    }
  }

  layout_item_list_finish(&list, -pos_vars.line_to_text_shift);

  g_nest_walk = NULL;  // ensure this is never stale for nest caller
  return(list);
}

function Layout_Item_List
layout_virt_indent_index(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width, Layout_Wrap_Kind kind){
  Layout_Item_List result = {};

  b32 enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
  if (enable_virtual_whitespace){
    code_index_lock();
    Code_Index_File *file = code_index_get_file(buffer);
    if (file != 0){
      result = layout_index__inner(app, arena, buffer, range, face, width, file, kind);
    }
    code_index_unlock();
    if (file == 0){
      result = layout_virt_indent_literal(app, arena, buffer, range, face, width, kind);
    }
  }
  else{
    result = layout_basic(app, arena, buffer, range, face, width, kind);
  }

  return(result);
}

function Layout_Item_List
layout_virt_indent_index_unwrapped(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width){
  return(layout_virt_indent_index(app, arena, buffer, range, face, width, Layout_Unwrapped));
}

function Layout_Item_List
layout_virt_indent_index_wrapped(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width){
  return(layout_virt_indent_index(app, arena, buffer, range, face, width, Layout_Wrapped));
}

function Layout_Item_List
layout_virt_indent_index_generic(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width){
  Managed_Scope scope = buffer_get_managed_scope(app, buffer);
  b32 *wrap_lines_ptr = scope_attachment(app, scope, buffer_wrap_lines, b32);
  b32 wrap_lines = (wrap_lines_ptr != 0 && *wrap_lines_ptr);
  return(layout_virt_indent_index(app, arena, buffer, range, face, width, wrap_lines?Layout_Wrapped:Layout_Unwrapped));
}

CUSTOM_COMMAND_MC_GLOBAL_SIG(toggle_virtual_whitespace)
CUSTOM_DOC("Toggles virtual whitespace for all files.")
{
  String_ID key = vars_save_string_lit("enable_virtual_whitespace");
  b32 enable_virtual_whitespace = def_get_config_b32(key);
  def_set_config_b32(key, !enable_virtual_whitespace);
}