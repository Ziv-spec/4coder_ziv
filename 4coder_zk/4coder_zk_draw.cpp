
function void
zk_draw_file_bar(Application_Links *app, View_ID view_id, Buffer_ID buffer, Face_ID face_id, Rect_f32 bar){
  Scratch_Block scratch(app);

  draw_rectangle_fcolor(app, bar, 0.f, fcolor_id(defcolor_bar));

  FColor base_color = fcolor_id(defcolor_base);
  FColor pop2_color = fcolor_id(defcolor_pop2);

  i64 cursor_position = view_get_cursor_pos(app, view_id);
  Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_position));

  Fancy_Line list = {};
  String_Const_u8 unique_name = push_buffer_unique_name(app, scratch, buffer);
  push_fancy_string(scratch, &list, base_color, unique_name);
  push_fancy_stringf(scratch, &list, base_color, " - Row: %3.lld Col: %3.lld -", cursor.line, cursor.col);

  Managed_Scope scope = buffer_get_managed_scope(app, buffer);
  Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting,
                                                   Line_Ending_Kind);
  switch (*eol_setting){
    case LineEndingKind_Binary:{ push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" bin"));  }break;
    case LineEndingKind_LF:    { push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" lf"));   }break;
    case LineEndingKind_CRLF:  { push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" crlf")); }break;
  }

  u8 space[3];
  {
    Dirty_State dirty = buffer_get_dirty_state(app, buffer);
    String_u8 str = Su8(space, 0, 3);
    if (dirty != 0) string_append(&str, string_u8_litexpr(" "));
    if (HasFlag(dirty, DirtyState_UnsavedChanges)) string_append(&str, string_u8_litexpr("*"));
    if (HasFlag(dirty, DirtyState_UnloadedChanges)) string_append(&str, string_u8_litexpr("!"));
    push_fancy_string(scratch, &list, pop2_color, str.string);
  }

  Vec2_f32 p = bar.p0 + V2f32(2.f, 2.f);
  draw_fancy_line(app, face_id, fcolor_zero(), &list, p);


  // right side
  f32 left_line_width = get_fancy_line_width(app, face_id, &list);
  f32 char_wid = get_face_metrics(app, face_id).normal_advance;

  f32 p_right = bar.x1 - char_wid*3.5f;
  p.x = clamp_bot(p_right, p.x+left_line_width+char_wid);
  i64 N = buffer_get_size(app, buffer);
  String_Const_u8 pos_text = (cursor_position== 0 ? string_u8_litexpr("Top") :
                              cursor_position== N ? string_u8_litexpr("Bot") :
                              push_stringf(scratch, "%d%%", i64(100.f*cursor_position/f64(N))));
  draw_string(app, face_id, pos_text, p, base_color);
}

function void
zk_draw_function_tooltip_inner(Application_Links *app, Arena *arena, Code_Index_Note *note, Code_Index_Nest* paren_define, Code_Index_Nest* paren_caller, i64 pos, i64 depth, Rect_f32 region){
  i64 param_hovered = 0;
  i64 pos_start = paren_caller->open.min;
  for (Code_Index_Nest *n = paren_caller->nest_list.first; n != 0; n = n->next){
    if (n->next == 0 || range_contains(Ii64(pos_start, n->close.min), pos)){ break; }
    pos_start = n->close.start;
    param_hovered++;
  }

  String8List prefix = {};
  String8List middle = {};
  String8List suffix = {};
  string_list_push(arena, &prefix, note->text);
  string_list_push(arena, &prefix, string_u8_litexpr("("));

  for (Code_Index_Nest *n = paren_define->nest_list.first; n != 0; n = n->next){
    String8List* list = (0<param_hovered ? &prefix : param_hovered==0 ? &middle : &suffix);
    param_hovered--;
    String_Const_u8 param = push_buffer_range(app, arena, note->file->buffer, range_union(n->open, n->close));
    string_list_push(arena, list, string_condense_whitespace(arena, param));
    if (n->next){ string_list_push(arena, list, string_u8_litexpr(" ")); }
  }
  string_list_push(arena, &suffix, string_u8_litexpr(")"));

  Face_Metrics metrics = get_face_metrics(app, qol_small_face);
  f32 char_wid = metrics.normal_advance;
  f32 line_hit = metrics.line_height;
  FColor cl_line = fcolor_id(depth == 1 ? defcolor_cursor : defcolor_ghost_character);
  f32 wid = 2.f;
  f32 pad = 2.f;

  String_Const_u8 pre = string_list_flatten(arena, prefix);
  String_Const_u8 mid = string_list_flatten(arena, middle);
  String_Const_u8 suf = string_list_flatten(arena, suffix);


  Vec2_f32 p0;
  Rect_f32 full, r_mid, r_line;
  if (def_get_config_b32(vars_save_string_lit("draw_function_tooltip_at_bottom"))) {
    p0 = V2f32(region.x0+wid, region.y1 - (depth*(1.f + metrics.line_height + pad + 2.f*wid)));
    full   = Rf32(p0, p0 + V2f32((pre.size+mid.size+suf.size)*char_wid, line_hit));
    r_mid  = Rf32(p0 + V2f32(pre.size*char_wid, 0.f), p0 + V2f32((pre.size+mid.size)*char_wid, wid + line_hit));
    r_line = Rf32(r_mid.x0, r_mid.y1-2.f, r_mid.x1 + 2.f - (suffix.node_count != 1)*char_wid, r_mid.y1);
  }
  else {
    p0 = V2f32(f32_floor32(qol_cur_cursor_pos.x), f32_floor32(qol_cur_cursor_pos.y) + 2.f + depth*(1.f + metrics.line_height + pad + 2.f*wid));
    full   = Rf32(p0 - V2f32(pre.size*char_wid, 0.f), p0 + V2f32((mid.size+suf.size)*char_wid, line_hit));
    r_mid  = Rf32(p0, p0 + V2f32(mid.size*char_wid, wid + line_hit));
    r_line = Rf32(r_mid.x0, r_mid.y1-4.f, r_mid.x1 + 2.f - (suffix.node_count != 1)*char_wid, r_mid.y1-3.f);
  }

  Vec2_f32 pre_p0 = full.p0;
  Vec2_f32 mid_p0 = r_mid.p0;
  Vec2_f32 suf_p0 = full.p1 - V2f32(suf.size*char_wid, line_hit);

  draw_rectangle_fcolor(app, rect_inner(full, -wid), 3.f, fcolor_id(defcolor_back));
  draw_string(app, qol_small_face, pre, pre_p0 + wid*V2f32(1,1), fcolor_id(defcolor_ghost_character));
  draw_string(app, qol_small_face, mid, mid_p0 + wid*V2f32(1,1), fcolor_id(defcolor_text_default));
  draw_string(app, qol_small_face, suf, suf_p0 + wid*V2f32(1,1), fcolor_id(defcolor_ghost_character));
  draw_rectangle_fcolor(app, r_line, 2.f, cl_line);
  draw_rectangle_outline_fcolor(app, rect_inner(full, -wid), 3.f, wid, cl_line);
}

function void
zk_draw_function_tooltip(Application_Links *app, Buffer_ID buffer, Rect_f32 region, i64 pos){
  Token_Array tokens = get_token_array_from_buffer(app, buffer);
  if (tokens.tokens == 0){ return; }
  i64 count = 0;

  Scratch_Block scratch(app);

  struct ToolTip_Ctx {
    struct ToolTip_Ctx *next;
    Code_Index_Note *note;
    Code_Index_Nest* paren_define;
    Code_Index_Nest* paren_caller;
  };
  ToolTip_Ctx tooltip_render_ctx[8];

  code_index_lock();
  Code_Index_File *file = code_index_get_file(buffer);
  for (Code_Index_Nest* n=code_index_get_nest(file, pos); n != 0; n = n->parent){
    if (n->kind != CodeIndexNest_Paren){ continue; }
    Token_Iterator_Array it = token_iterator_pos(0, &tokens, n->open.min);
    token_it_dec_non_whitespace(&it);
    Token *token = token_it_read(&it);

    if (token->kind == TokenBaseKind_Identifier){
      String_Const_u8 lexeme = push_token_lexeme(app, scratch, buffer, token);
      Code_Index_Note *note = code_index_note_from_string(lexeme);
      if (note == NULL){ continue; }
      if (note->note_kind == CodeIndexNote_Function ||
            note->note_kind == CodeIndexNote_Macro)
      {
        Code_Index_Nest *paren_define = note->parent->nest_list.first;
        if (paren_define != NULL && paren_define->kind == CodeIndexNest_Paren){
          if (count > 8) break; // I show only the top 8 results

          ToolTip_Ctx *ctx = &tooltip_render_ctx[count++];
          ctx->note = note;
          ctx->paren_define = paren_define;
          ctx->paren_caller = n;
        }
      }
    }
  }

  if (def_get_config_b32(vars_save_string_lit("draw_function_tooltip_at_bottom"))) {
    for (i64 i = 0; i < count; i++) {
      ToolTip_Ctx *ctx = &tooltip_render_ctx[count-1-i];
      zk_draw_function_tooltip_inner(app, scratch, ctx->note, ctx->paren_define, ctx->paren_caller, pos, 1+i, region);
    }
  }
  else {
    for (i64 i = 0; i < count; i++) {
      ToolTip_Ctx *ctx = &tooltip_render_ctx[i];
      zk_draw_function_tooltip_inner(app, scratch, ctx->note, ctx->paren_define, ctx->paren_caller, pos, 1+i, region);
    }
  }

  code_index_unlock();
}

// COPYPASTA From fleury layer
function void
zk_highlight_cursor_mark_range(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id, Rect_f32 clip, f32 h)
{
  Rect_f32 view_rect = view_get_screen_rect(app, view_id);
  Rect_f32 old_clip = draw_set_clip(app, view_rect);

  i64 mark_pos = view_get_mark_pos(app, view_id); // view_get_cursor_pos(app, view);
  Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
  if(mark_pos < visible_range.start) {
    qol_cur_mark_pos.y = clip.y0;
  }
  else if (mark_pos > visible_range.end) {
    qol_cur_mark_pos.y = clip.y1;
  }

  Range_f32 bound = If32(qol_cur_cursor_pos.y, qol_cur_mark_pos.y);
  draw_rectangle(app, Rf32(view_rect.x0, bound.min, view_rect.x0 + 4, bound.max+h), 3.f,
                 fcolor_resolve(fcolor_change_alpha(fcolor_id(defcolor_comment), 0.5f)));
  draw_set_clip(app, old_clip);
}


function void
zk_draw_cursor_mark(Application_Links *app, View_ID view_id, b32 is_active_view,
                    Buffer_ID buffer, Text_Layout_ID text_layout_id,
                    f32 roundness, f32 outline_thickness){
  b32 has_highlight_range = draw_highlight_range(app, view_id, buffer, text_layout_id, roundness);

  i64 cursor_pos = view_get_cursor_pos(app, view_id);
  i64 mark_pos = view_get_mark_pos(app, view_id);

  Rect_f32 nxt_cursor_rect = text_layout_character_on_screen(app, text_layout_id, cursor_pos);
  Rect_f32 cur_cursor_rect = Rf32_xy_wh(qol_cur_cursor_pos, rect_dim(nxt_cursor_rect));
  if (is_active_view && nxt_cursor_rect.x1 > 0.f){
    qol_nxt_cursor_pos = nxt_cursor_rect.p0;
  }

  if (!has_highlight_range){
    Scratch_Block scratch(app);
    QOL_Cursor_Kind cursor_kind = qol_cursor_kind(def_get_config_string(scratch, vars_save_string_lit("cursor_style")));
    QOL_Cursor_Kind   mark_kind = qol_cursor_kind(def_get_config_string(scratch, vars_save_string_lit("mark_style")));

    ARGB_Color cl_cursor = fcolor_resolve(fcolor_id(defcolor_cursor, default_cursor_sub_id()));
    ARGB_Color cl_mark   = fcolor_resolve(fcolor_id(defcolor_mark));
    if (is_active_view && cursor_kind == QOL_Cursor_Rect && rect_overlap(nxt_cursor_rect, cur_cursor_rect)){
      // NOTE: Only paint once cursor is overlapping (from Jack Punter)
      paint_text_color_pos(app, text_layout_id, cursor_pos, fcolor_id(defcolor_at_cursor));
    }
    else if (!is_active_view){
      draw_rectangle_outline(app, nxt_cursor_rect, roundness, outline_thickness, cl_cursor);
    }

    b32 b = cursor_pos < mark_pos;
    b32 c = mark_pos <= cursor_pos;
    f32 w = rect_width(cur_cursor_rect) - 3.f;

    {
      Vec2_f32 d = V2f32(c ? w : 0, 0);
      Rect_f32 rect_shifted = Rf32(cur_cursor_rect.p0-d, cur_cursor_rect.p1-d);
      switch (cursor_kind){
        case QOL_Cursor_Rect:    draw_rectangle(app, cur_cursor_rect, roundness, cl_cursor); break;
        case QOL_Cursor_Thin:    draw_rectangle(app, rect_vsplit(cur_cursor_rect, 1.f, 0), 0.f, cl_cursor); break;
        case QOL_Cursor_Under:   draw_rectangle(app, rect_hsplit(cur_cursor_rect, 3.f, 1), roundness, cl_cursor); break;
        case QOL_Cursor_Corner: (draw_rectangle(app, rect_vsplit(cur_cursor_rect, 3.f, 0), roundness, cl_cursor),
                                 draw_rectangle(app, rect_hsplit(rect_shifted,    3.f, c), roundness, cl_cursor)); break;
      }
    }

    {
      Rect_f32 mark_rect = text_layout_character_on_screen(app, text_layout_id, mark_pos);
      if (is_active_view && mark_rect.x1 > 0) {
        qol_nxt_mark_pos = mark_rect.p0;
      }
      Vec2_f32 d = V2f32(b ? w : 0, 0);
      Rect_f32 rect_shifted = Rf32(mark_rect.p0-d, mark_rect.p1-d);
      switch (mark_kind){
        case QOL_Cursor_Rect:    draw_rectangle_outline(app, mark_rect, roundness, outline_thickness, cl_mark); break;
        case QOL_Cursor_Thin:    draw_rectangle(app, rect_vsplit(mark_rect, 1.f, 0), 0.f, cl_mark); break;
        case QOL_Cursor_Under:   draw_rectangle(app, rect_hsplit(mark_rect, 3.f, 1), roundness, cl_mark); break;
        case QOL_Cursor_Corner: (draw_rectangle(app, rect_vsplit(mark_rect,    outline_thickness,  0), roundness, cl_mark),
                                 draw_rectangle(app, rect_hsplit(rect_shifted, outline_thickness, !c), roundness, cl_mark));
      }
    }

  }

  MC_render_cursors(app, view_id, text_layout_id);
}
