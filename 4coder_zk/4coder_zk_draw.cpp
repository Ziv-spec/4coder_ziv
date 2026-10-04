
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

function void
zk_draw_peek(Application_Links *app, Frame_Info frame_info){
  Scratch_Block scratch(app);
  
  View_ID view = get_active_view(app, Access_Always);
  Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
  Mouse_State mouse = get_mouse_state(app);
  i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
  String_Const_u8 lexeme = push_token_or_word_under_pos(app, scratch, buffer, pos);
  
  Code_Index_Note *note = code_index_note_from_string(lexeme);
  switch (note ? note->note_kind : -1){
    case CodeIndexNote_Function:
    case CodeIndexNote_Type:
    case CodeIndexNote_Macro: break;
    default: return;
  }
  
  Rect_f32 region = panel_get_rect(app, TAB_root(app));
  Vec2_f32 center = rect_center(region);
  Vec2_f32 dim = rect_half_dim(region);
  Vec2_f32 bound = V2f32(lerp(rect_x(region), 0.4f),  // x bias since text is left-to-right
                         lerp(rect_y(region), 0.5f));
  f32 x0 = f32_floor32(mouse.p.x < bound.x ? center.x : region.x0);
  f32 line_h = get_view_line_height(app, view); 
  f32 rounded_mouse_y = line_h * floorf((mouse.p.y/line_h));
  f32 y0 = f32_floor32(Min(rounded_mouse_y, region.y1-dim.y));
  Rect_f32 rect = Rf32_xy_wh(V2f32(x0, y0), dim);
  // ^ or iterate panels selecting max via (panel-height, dist-to-cursor)
  
  Buffer_ID peek_buffer = 0;
  i64 peek_line = 0;
  
  {
    code_index_lock();
    for (Buffer_ID b = get_buffer_next(app, 0, Access_Always);
         b != 0;
         b = get_buffer_next(app, b, Access_Always)){
      Code_Index_File *file = code_index_get_file(b);
      if (file == 0){ continue; }
      
      for (i32 i = 0; i < file->note_array.count; i += 1){
        Code_Index_Note *n = file->note_array.ptrs[i];
        if (!string_match(n->text, lexeme)){ continue; }
        
        peek_buffer = b;
        peek_line = get_line_number_from_pos(app, b, n->pos.first);
        goto done;
      }
    }
    done:;
    code_index_unlock();
  }
  
  if (peek_buffer == 0){ return; }
  
  Buffer_Point point = {peek_line};
  Text_Layout_ID text_layout_id = text_layout_create(app, peek_buffer, rect_inner(rect, 10), point);
  
  draw_rectangle_fcolor(app, rect, 5, fcolor_change_alpha(fcolor_id(defcolor_back), 0.9f));
  draw_rectangle_outline_fcolor(app, rect, 5, 5, fcolor_id(defcolor_bar));
  draw_line_highlight(app, text_layout_id, peek_line, fcolor_id(defcolor_highlight_cursor_line));
  
  Rect_f32 prev_clip = draw_set_clip(app, text_layout_region(app, text_layout_id));
  qol_paint_token_colors(app, peek_buffer, text_layout_id);
  draw_text_layout_default(app, text_layout_id);
  text_layout_free(app, text_layout_id);
  draw_set_clip(app, prev_clip);
}

