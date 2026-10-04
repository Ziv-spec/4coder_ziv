
CUSTOM_COMMAND_SIG(zk_startup)
CUSTOM_DOC("ZK command for responding to a startup event")
{
  ProfileScope(app, "qol startup");
  User_Input input = get_current_input(app);
  if (match_core_code(&input, CoreCode_Startup)){
    String_Const_u8_Array file_names = input.event.core.file_names;
    load_themes_default_folder(app);

    {
      Face_Description description = get_face_description(app, 0);
      i32 override_font_size = description.parameters.pt_size;
      b32 override_hinting   = description.parameters.hinting;

      Scratch_Block scratch(app);
      load_config_and_apply(app, &global_config_arena, override_font_size, override_hinting);

      String_Const_u8 bindings_file_name = string_u8_litexpr("bindings.4coder");
      String_Const_u8 mapping = def_get_config_string(scratch, vars_save_string_lit("mapping"));

      if (string_match(mapping, string_u8_litexpr("mac-default"))){
        bindings_file_name = string_u8_litexpr("mac-bindings.4coder");
      }
      else if (OS_MAC && string_match(mapping, string_u8_litexpr("choose"))){
        bindings_file_name = string_u8_litexpr("mac-bindings.4coder");
      }

      String_ID global_map_id = vars_save_string_lit("keys_global");
      String_ID file_map_id = vars_save_string_lit("keys_file");
      String_ID code_map_id = vars_save_string_lit("keys_code");

      if (dynamic_binding_load_from_file(app, &framework_mapping, bindings_file_name)){
        zk_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
      }
      else{
        TAB_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
        zk_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
        zk_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
      }

      // open command line files
      String_Const_u8 hot_directory = push_hot_directory(app, scratch);
      for (i32 i = 0; i < file_names.count; i += 1){
        Temp_Memory_Block temp(scratch);
        String_Const_u8 input_name = file_names.vals[i];
        String_Const_u8 full_name = push_u8_stringf(scratch, "%S/%S", hot_directory, input_name);
        Buffer_ID new_buffer = create_buffer(app, full_name, BufferCreate_NeverNew|BufferCreate_MustAttachToFile);
        if (new_buffer == 0){
          create_buffer(app, input_name, 0);
        }
      }
    }

    //default_4coder_initialize(app, file_names);
    default_4coder_side_by_side_panels(app, file_names);

    if (def_get_config_b32(vars_save_string_lit("automatically_load_project"))){
      load_project(app);
    }

    qol_temp_buffer = create_buffer(app, string_u8_litexpr("*qol_temp*"),
                                    BufferCreate_Background | BufferCreate_AlwaysNew | BufferCreate_NeverAttachToFile);
    buffer_set_setting(app, qol_temp_buffer, BufferSetting_Unimportant, true);
    buffer_set_setting(app, qol_temp_buffer, BufferSetting_Unkillable, true);
    buffer_set_setting(app, qol_temp_buffer, BufferSetting_ReadOnly, false);

    qol_snippet_init(app);
    TAB_startup_inner(app);
    qol_bview_init(app);
  }

  {
    def_audio_init();
  }

  {
    def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
    clear_all_layouts(app);
  }

  Face_Description desc = get_global_face_description(app);
  desc.parameters.pt_size -= 4;
  qol_small_face = try_create_new_face(app, &desc);

  String_Const_u8 non_word_chars = string_u8_litexpr(" \t\n/\\()\"':,.;<>~!@#$%^&*|+=[]{}`?-_");
  character_predicate_non_word = character_predicate_from_chars(non_word_chars);
  character_predicate_word     = character_predicate_not(&character_predicate_non_word);

  Scratch_Block scratch(app);
  set_active_color(get_color_table_by_name(def_get_config_string(scratch, vars_save_string_lit("default_theme_name"))));
  qol_cur_colors = qol_color_table_init(app);
  qol_nxt_colors = qol_color_table_init(app);
  qol_color_table_copy(qol_cur_colors, active_color_table);
  qol_color_table_copy(qol_nxt_colors, active_color_table);
}


function void
zk_tick(Application_Links *app, Frame_Info frame_info){
  qol_tick(app, frame_info);
  f32 dt = frame_info.animation_dt;

  if (g_use_code_peek_hover || g_use_minimap_hover) {
    g_hover_dt += dt;
    if (g_hover_dt < HOVER_TIME)
      animate_in_n_milliseconds(app, 0);
  }
  else {
    g_hover_dt = 0;
  }
}


function void
zk_render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, Rect_f32 rect){
  ProfileScope(app, "zk render buffer");

  View_ID active_view = get_active_view(app, Access_Always);
  b32 is_active_view = (active_view == view_id);
  Rect_f32 prev_clip = draw_set_clip(app, rect);

  Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);

  // NOTE(allen): Cursor shape
  Face_Metrics metrics = get_face_metrics(app, face_id);
  u64 cursor_roundness_100 = def_get_config_u64(app, vars_save_string_lit("cursor_roundness"));
  f32 cursor_roundness = metrics.normal_advance*cursor_roundness_100*0.01f;
  f32 mark_thickness = (f32)def_get_config_u64(app, vars_save_string_lit("mark_thickness"));

  i64 cursor_pos = view_correct_cursor(app, view_id);
  view_correct_mark(app, view_id);

  // NOTE(allen): Line highlight
  b32 highlight_line_at_cursor = def_get_config_b32(vars_save_string_lit("highlight_line_at_cursor"));
  if (highlight_line_at_cursor && is_active_view){
    i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
    draw_line_highlight(app, text_layout_id, line_number, fcolor_id(defcolor_highlight_cursor_line));
  }

  // NOTE(allen): Token colorizing
  Token_Array token_array = get_token_array_from_buffer(app, buffer);
  if (token_array.tokens != 0){
    qol_draw_token_colors(app, view_id, buffer, text_layout_id, &token_array);

    // NOTE(allen): Scan for TODOs and NOTEs
    b32 use_comment_keyword = def_get_config_b32(vars_save_string_lit("use_comment_keyword"));
    if (use_comment_keyword){
      Comment_Highlight_Pair pairs[] = {
        {string_u8_litexpr("NOTE"), finalize_color(defcolor_comment_pop, 0)},
        {string_u8_litexpr("TODO"), finalize_color(defcolor_comment_pop, 1)},
      };
      draw_comment_highlights(app, buffer, text_layout_id, &token_array, pairs, ArrayCount(pairs));
    }
    qol_draw_comments(app, buffer, text_layout_id, &token_array, rect);
  }
  else{
    paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
  }

  // NOTE(allen): Scope highlight
  b32 use_scope_highlight = def_get_config_b32(vars_save_string_lit("use_scope_highlight"));
  if (use_scope_highlight){
    Color_Array colors = finalize_color_array(defcolor_back_cycle);
    draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
  }

  if (qol_col_cursor.pos >= 0 && qol_col_buffer == buffer){
    Rect_f32 r = view_relative_box_of_pos(app, view_id, qol_col_cursor.line, qol_col_cursor.pos);
    f32 dx = view_get_buffer_scroll(app, view_id).position.pixel_shift.x;
    Rect_f32 col_rect = Rf32(rect_range_x(r) + rect.x0 - dx, rect_range_y(rect));
    draw_rectangle_fcolor(app, col_rect, 0.f, fcolor_id(defcolor_highlight_cursor_line));
  }

  qol_draw_scopes(app, view_id, buffer, text_layout_id, metrics.normal_advance);

  b32 use_error_highlight = def_get_config_b32(vars_save_string_lit("use_error_highlight"));
  b32 use_jump_highlight = def_get_config_b32(vars_save_string_lit("use_jump_highlight"));
  if (use_error_highlight || use_jump_highlight){
    // NOTE(allen): Error highlight
    String_Const_u8 name = string_u8_litexpr("*compilation*");
    Buffer_ID compilation_buffer = get_buffer_by_name(app, name, Access_Always);
    if (use_error_highlight){
      qol_draw_compile_errors(app, buffer, text_layout_id, compilation_buffer);
    }

    // NOTE(allen): Search highlight
    if (use_jump_highlight){
      Buffer_ID jump_buffer = get_locked_jump_buffer(app);
      if (jump_buffer != compilation_buffer){
        draw_jump_highlights(app, buffer, text_layout_id, jump_buffer, fcolor_id(defcolor_highlight_white));
      }
    }
  }

  // NOTE(allen): Color parens
  b32 use_paren_helper = def_get_config_b32(vars_save_string_lit("use_paren_helper"));
  if (use_paren_helper){
    Color_Array colors = finalize_color_array(defcolor_text_cycle);
    draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
  }

  // NOTE(allen): Whitespace highlight
  b64 show_whitespace = false;
  view_get_setting(app, view_id, ViewSetting_ShowWhitespace, &show_whitespace);
  if (show_whitespace){
    if (token_array.tokens == 0){
      draw_whitespace_highlight(app, buffer, text_layout_id, cursor_roundness);
    }
    else{
      draw_whitespace_highlight(app, text_layout_id, &token_array, cursor_roundness);
    }
  }

  b32 show_hex_colors = def_get_config_b32(vars_save_string_lit("show_hex_colors"));
  if (show_hex_colors){
    qol_draw_hex_color(app, view_id, buffer, text_layout_id);
  }

  // TODO(ziv): consider using whatever is useful from here
  // vim_draw_search_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
  SEARCH_draw_highlights_inner(app, view_id, text_layout_id);

  // NOTE(allen): Cursor
  switch (fcoder_mode){
    case FCoderMode_Original:
    {
      Rect_f32 r = draw_set_clip(app, prev_clip);

      Scratch_Block scratch(app);
      String_ID key = vars_save_string_lit("cursor_style");
      String_Const_u8 prev = def_get_config_string(scratch, key);
      qol_draw_cursor_mark(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);

      draw_set_clip(app, r);
    }break;
    case FCoderMode_NotepadLike:
    {
      draw_notepad_style_cursor_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
    }break;
  }

  // NOTE(allen): Fade ranges
  paint_fade_ranges(app, text_layout_id, buffer);

  // NOTE(allen): put the actual text on the actual screen
  draw_text_layout_default(app, text_layout_id);

  if (rect_contains_point(rect, qol_cur_cursor_pos) &&
        def_get_config_b32(vars_save_string_lit("use_function_tooltip"))){
    zk_draw_function_tooltip(app, buffer, rect, cursor_pos);
  }

  if (token_array.tokens){
    Scratch_Block scratch(app);
    ARGB_Color cl_nest = fcolor_resolve(fcolor_change_alpha(fcolor_id(defcolor_control), 0.8f));
    Text_Layout_ID minimap_id = MM_begin(app, scratch, view_id, face_id, buffer, token_array, rect, visible_range, cl_nest);
    qol_paint_token_colors(app, buffer, minimap_id);
    MM_end(app, minimap_id);
  }

  draw_set_clip(app, prev_clip);
}

function void
zk_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id){
  ProfileScope(app, "zk render caller");
  View_ID active_view = get_active_view(app, Access_Always);
  b32 is_active_view = (active_view == view_id);

  Rect_f32 region = view_get_screen_rect(app, view_id);
  Rect_f32 prev_clip = draw_set_clip(app, region);
  draw_rectangle_fcolor(app, region, 0.f, fcolor_id(defcolor_back));

  Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
  Face_ID face_id = get_face_id(app, buffer);
  Face_Metrics face_metrics = get_face_metrics(app, face_id);
  f32 line_height = face_metrics.line_height;
  f32 normal_advance = face_metrics.normal_advance;
  f32 digit_advance = face_metrics.decimal_digit_advance;

  // NOTE(allen): query bars
  region = SEARCH_draw_bar_inner(app, frame_info, region, view_id, face_id);
  region = qol_draw_query_bars(app, region, view_id, face_id);

  // NOTE(allen): file bar
  b64 showing_file_bar = false;
  b64 has_bot_border = false;
  if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar){
    b32 on_top = def_get_config_b32(vars_save_string_lit("filebar_on_top"));
    Rect_f32_Pair pair = (on_top ?
                            layout_file_bar_on_top(region, line_height) :
                          layout_file_bar_on_bot(region, line_height));
    zk_draw_file_bar(app, view_id, buffer, face_id, pair.e[1-on_top]);
    region = pair.e[on_top];
  }

  if (!has_bot_border){
    Rect_f32_Pair pair = rect_split_top_bottom_neg(region, 2.f);
    draw_rectangle_fcolor(app, pair.max, 0.f, fcolor_id(defcolor_bar));
    region = pair.min;
  }

  {
    Rect_f32 r = global_get_screen_rectangle(app);
    ARGB_Color cl = fcolor_resolve(fcolor_id(defcolor_margin));
    if(region.x0 != r.x0){ draw_rectangle(app, Rf32(region.x0,   region.y0, region.x0+2, region.y1), 0.f, cl); region.x0 += 2; }
    if(region.x1 != r.x1){ draw_rectangle(app, Rf32(region.x1-2, region.y0, region.x1,   region.y1), 0.f, cl); region.x1 -= 2; }
  }

  f32 char_count = def_get_config_f32(app, vars_save_string_lit("scroll_margin_x"));
  f32 line_count = def_get_config_f32(app, vars_save_string_lit("scroll_margin_y"));
  Vec2_f32 margin = V2f32(char_count*normal_advance, line_count*line_height);
  view_set_camera_bounds(app, view_id, margin, V2f32(1,1));

  Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);

  Buffer_Point_Delta_Result delta = delta_apply(app, view_id, frame_info.animation_dt, scroll);
  if (!block_match_struct(&scroll.position, &delta.point)){
    if (is_active_view){
      qol_cur_cursor_pos -= view_point_difference(app, view_id, delta.point, scroll.position);
    }
    block_copy_struct(&scroll.position, &delta.point);
    view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
  }
  if (delta.still_animating){
    animate_in_n_milliseconds(app, 0);
  }

  // NOTE(allen): FPS hud
  if (show_fps_hud){
    Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
    draw_fps_hud(app, frame_info, face_id, pair.max);
    region = pair.min;
    animate_in_n_milliseconds(app, 1000);
  }

  // NOTE(allen): layout line numbers
  b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
  Rect_f32 line_number_rect = {};
  if (show_line_number_margins){
    Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
    line_number_rect = pair.min;
    region = pair.max;
  }
  region = rect_split_left_right(region, 4.f).max;

  // NOTE(allen): begin buffer render
  Buffer_Point buffer_point = scroll.position;
  Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);

  // NOTE(allen): draw line numbers
  if (show_line_number_margins){
    draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
  }

  // NOTE(allen): draw the buffer
  zk_render_buffer(app, view_id, face_id, buffer, text_layout_id, region);
  loco_render_buffer(app, view_id, face_id, buffer, text_layout_id, region, frame_info);

  text_layout_free(app, text_layout_id);
  draw_set_clip(app, prev_clip);
}

function void
zk_whole_screen_render_caller(Application_Links *app, Frame_Info frame_info){
  if (def_get_config_b32(vars_save_string_lit("use_code_peek")) &&
        g_use_code_peek_hover && g_hover_dt > HOVER_TIME){
    zk_draw_peek(app, frame_info);
  }

  if (qol_try_exit_view != 0){
    qol_try_exit_render(app, frame_info);
  }
}

function i32 zk_buffer_edit_range(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range){
  i64 pos = qol_col_cursor.pos;
  Range_i64 old_range = Ii64(old_cursor_range.min.pos, old_cursor_range.max.pos);
  if (pos >= 0 && qol_col_buffer == buffer_id){
    i64 insert_size = range_size(new_range);
    index_shift(&pos, old_range, insert_size);
    qol_col_cursor = buffer_compute_cursor(app, buffer_id, seek_pos(pos));
  }

  loco_on_buffer_edit(app, buffer_id, old_range, new_range);
  MC_buffer_edit_range_inner(app, buffer_id, new_range, old_cursor_range);
  return qol_lang_buffer_edit_range(app, buffer_id, new_range, old_cursor_range);
}


BUFFER_HOOK_SIG(zk_begin_buffer){
  ProfileScope(app, "begin buffer");

  Scratch_Block scratch(app);

  Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
  Lang_ID *lang_ptr = scope_attachment(app, scope, buffer_lang, Lang_ID);

  String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer_id);
  if (file_name.size > 0){
    String_Const_u8 treat_as_code_string = def_get_config_string(scratch, vars_save_string_lit("treat_as_code"));
    String_Const_u8_Array extensions = parse_extension_line_to_extension_list(scratch, treat_as_code_string);
    String_Const_u8 ext = string_file_extension(file_name);
    for (i32 i = 0; i < extensions.count; ++i){
      if (string_match(ext, extensions.strings[i])){

        if (string_match(ext, string_u8_litexpr("cpp")) ||
              string_match(ext, string_u8_litexpr("h")) ||
              string_match(ext, string_u8_litexpr("c")) ||
              string_match(ext, string_u8_litexpr("hpp")) ||
              string_match(ext, string_u8_litexpr("cc")) ||
              string_match(ext, string_u8_litexpr("4coder"))){
          *lang_ptr = Lang_Cpp;
        }
        else if (string_match(ext, string_u8_litexpr("lua"))){
          *lang_ptr = Lang_Lua;
        }

        break;
      }
    }
  }


  // TODO(ziv): Replace this with actualy something reasonable when you can. This is
  // very much a hack as of right now, and should not be allowed to stay in the form that
  // it is at currently.

  String_Const_u8 yeet_name = string_u8_litexpr("*yeet*");
  Buffer_ID yeet_buffer = get_buffer_by_name(app, yeet_name, Access_Always);
  if (buffer_id == yeet_buffer) {
    *lang_ptr = Lang_Cpp;
  }

  b32 is_code = (*lang_ptr != Lang_None);

  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");
  Command_Map_ID map_id = (is_code)?(code_map_id):(file_map_id);
  Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
  *map_id_ptr = map_id;

  Line_Ending_Kind setting = guess_line_ending_kind_from_buffer(app, buffer_id);
  Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting, Line_Ending_Kind);
  *eol_setting = setting;

  // NOTE(allen): Decide buffer settings
  b32 wrap_lines = true;
  if (is_code){
    wrap_lines = def_get_config_b32(vars_save_string_lit("enable_code_wrapping"));
  }

  String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer_id);
  if (buffer_name.size > 0 && buffer_name.str[0] == '*' && buffer_name.str[buffer_name.size - 1] == '*'){
    wrap_lines = def_get_config_b32(vars_save_string_lit("enable_output_wrapping"));
  }

  if (is_code){
    ProfileBlock(app, "begin buffer kick off lexer");
    Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);
    *lex_task_ptr = async_task_no_dep(&global_async_system, qol_lang_full_lex_async, make_data_struct(&buffer_id));
  }

  {
    b32 *wrap_lines_ptr = scope_attachment(app, scope, buffer_wrap_lines, b32);
    *wrap_lines_ptr = wrap_lines;
  }

  if (is_code){
    buffer_set_layout(app, buffer_id, layout_virt_indent_index_generic);
  }
  else{
    buffer_set_layout(app, buffer_id, layout_generic);
  }

  return 0;
}

BUFFER_HOOK_SIG(zk_end_buffer_close_jump_list){
  Marker_List *list = get_marker_list_for_buffer(buffer_id);
  if (list != 0){
    delete_marker_list(list);
  }
  loco_on_buffer_end(app, buffer_id);
  default_end_buffer(app, buffer_id);
  return(0);
}

// COPYPASTA from fleury layer
function DELTA_RULE_SIG(zk_delta_rule)
{
  Vec2_f32 *velocity = (Vec2_f32*)data;
  if(velocity->x == 0.f)
  {
    velocity->x = 1.f;
    velocity->y = 1.f;
  }
  Smooth_Step step_x = smooth_camera_step(pending.x, velocity->x, 80.f, 1.f/4.f);
  Smooth_Step step_y = smooth_camera_step(pending.y, velocity->y, 80.f, 1.f/4.f);
  *velocity = V2f32(step_x.v, step_y.v);
  return(V2f32(step_x.p, step_y.p));
}