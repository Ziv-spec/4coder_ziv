
//~ Jump Definition Commands

function void
zk_lister_fill_index(Application_Links *app, Lister *lister){
  code_index_lock();
  for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
       buffer != 0;
       buffer = get_buffer_next(app, buffer, Access_Always)){
    Code_Index_File *file = code_index_get_file(buffer);
    if (file != 0){
      for (i32 i = 0; i < file->root.note_array.count; i += 1){
        Code_Index_Note *note = file->root.note_array.ptrs[i];
        Tiny_Jump *jump = push_array(lister->arena, Tiny_Jump, 1);
        jump->buffer = buffer;
        jump->pos = note->pos.first;

        String_Const_u8 sort = string_u8_empty;

        switch (note->note_kind) {
          case CodeIndexNote_Type:   { sort = string_u8_litexpr("type");   } break;
          case CodeIndexNote_Macro:  { sort = string_u8_litexpr("macro");  } break;
          case CodeIndexNote_Enum:   { sort = string_u8_litexpr("enum");   } break;
          case CodeIndexNote_Global: { sort = string_u8_litexpr("global"); } break;
          case CodeIndexNote_Function: {
            if (note->parent != 0) {
              Code_Index_Nest* scope = note->parent->next;
              sort = (scope != 0 && scope->kind == CodeIndexNest_Scope) ?
                string_u8_litexpr("function") : string_u8_litexpr("function [decl]");
            }
          } break;
        }
        lister_add_item(lister, note->text, sort, jump, 0);
      }
    }
  }
  code_index_unlock();
}

CUSTOM_UI_COMMAND_SIG(zk_jump_to_definition_lister)
CUSTOM_DOC("List all definitions in the code index and jump to one chosen by the user.")
{
  Scratch_Block scratch(app);
  Lister_Block lister(app, scratch);
  lister_set_query(lister, string_u8_litexpr("Definition:"));
  lister_set_default_handlers(lister);

  zk_lister_fill_index(app, lister);

  Lister_Result l_result = run_lister(app, lister);
  Tiny_Jump result = {};
  if (!l_result.canceled && l_result.user_data != 0){
    block_copy_struct(&result, (Tiny_Jump*)l_result.user_data);
  }

  if (result.buffer != 0){
    View_ID view = get_this_ctx_view(app, Access_Always);
    point_stack_push_view_cursor(app, view);
    jump_to_location(app, view, result.buffer, result.pos);
  }
}


#if OS_WINDOWS
function String_Const_u8
zk_msvc_sdk_include_path(Arena *arena) {

  // NOTE(ziv): when writing microsoft_crazyness.h Jon was likely concerned
  // with .lib files his compiler had to link against. I don't care about
  // those, I just care about the include folder with all the .h files I can
  // match against. So this function is modfied to give me the Include folder
  wchar_t *windows_sdk_include_root = find_windows_kit_root();
  u64 size = wcslen(windows_sdk_include_root);

  u8 *out  = push_array(arena, u8, size);
  u64 out_size = 0;
  {
    u64 cap = size;

    Character_Consume_Result consume;
    for (int i = 0; i < size; i += consume.inc, cap -= consume.inc) {
      consume = utf16_consume((u16 *)&windows_sdk_include_root[i], cap);
      out_size += utf8_write((u8 *)&out[out_size], consume.codepoint);
    }
  }
  free(windows_sdk_include_root);

  return SCu8(out, out_size);
}

function void
zk_find_file_in_folder_recursive__inner(Arena *arena, String_Const_u8 base, String_Const_u8 file, String_Const_u8 *out, int depth) {
  Assert(arena && out);

  if (depth >= 32) return; // just to feel safe

  File_List list = system_get_file_list(arena, base);
  for (File_Info **ptr = list.infos, **end = list.infos + list.count;
       ptr < end;
       ptr += 1){
    File_Info *info = *ptr;
    String_Const_u8 name = info->file_name;
    if (HasFlag(info->attributes.flags, FileAttribute_IsDirectory)){

      String_Const_u8 inner = push_u8_stringf(arena, "%S/%S", base, name);
      zk_find_file_in_folder_recursive__inner(arena, inner, file, out, ++depth);
    }
    else if (string_match(name, file, StringMatch_CaseInsensitive)) {

      u8 *dst = out->str;
      block_copy(dst, base.str, base.size); dst += base.size;
      block_copy(dst, "\\", 1); dst += 1;
      block_copy(dst, file.str, file.size); dst+= file.size;
      out->size = dst - out->str;

      return;
    }
  }
}

function String_Const_u8
zk_find_file_in_folder_recursive(Arena *arena, String_Const_u8 base, String_Const_u8 file) {

  u8 out[256]; u64 size = 0;
  String_Const_u8 found_path = { out, size };

  Temp_Memory temp = begin_temp(arena);
  zk_find_file_in_folder_recursive__inner(arena, base, file, &found_path, 0);
  end_temp(temp);

  if (found_path.size == 0) return String_Const_u8{0};
  // copy result to an actuall buffer

  u8 *result = push_array(arena, u8, found_path.size);
  block_copy(result, found_path.str, found_path.size);

  return String_Const_u8{ result, found_path.size };

}
#endif

function String_Const_u8
string_remove_last_folder_and_slash(String_Const_u8 path) {
  String_Const_u8 result = string_remove_last_folder(path);
  if (character_is_slash(string_get_character(result, result.size - 1))) {
    result = string_chop(result, 1);
  }
  return result;
}

internal void
zk_open_other_panel_to_location(Application_Links *app, Buffer_ID buffer, i64 pos)
{
  View_ID view = get_active_view(app, Access_Always);
  Rect_f32 region = view_get_buffer_region(app, view);
  f32 view_height = rect_height(region);
  view = get_next_view_looped_primary_panels(app, view, Access_Always);

  view_set_buffer(app, view, buffer, 0);
  i64 line_number = get_line_number_from_pos(app, buffer, pos);
  Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
  scroll.position.line_number = line_number;
  scroll.target.line_number = line_number;
  scroll.position.pixel_shift.y = scroll.target.pixel_shift.y = -view_height*0.5f;
  view_set_buffer_scroll(app, view, scroll, SetBufferScroll_SnapCursorIntoView);
  view_set_cursor(app, view, seek_pos(pos));
  view_set_mark(app, view, seek_pos(pos));
}

function Code_Index_Note *
zk_find_next_intuitive_note(Buffer_ID buffer, Code_Index_Note *first_note, String_Const_u8 iden_string, i64 pos) {
  if (!first_note) return NULL;

  b32 do_save_next_note = false;
  Code_Index_Note *best_note  = NULL;
  Code_Index_Note *last_best_note  = NULL;
  for (Code_Index_Note *note = first_note; note != 0; note = note->next_in_hash){
    if (!string_match(iden_string, note->text)){ continue; }

    if (do_save_next_note) {
      best_note = note;
      break;
    }

    Assert(note->file); // Is it fine to assume? idk..

    // Found a note I am currently at, now jump to next one
    if (buffer == note->file->buffer && note->pos.min <= pos && pos <= note->pos.max) {
      do_save_next_note = true;
      last_best_note = note;
    }
  }

  best_note = (best_note != NULL) ? best_note : last_best_note;

  if (best_note) {
    return best_note;
  }
  else {
    // Prioretize function implementation instead of decloration
    for (Code_Index_Note *note = first_note; note != 0; note = note->next_in_hash){
      if (!string_match(iden_string, note->text)){ continue; }

      if (note->note_kind == CodeIndexNote_Function && note->parent != 0){
        Code_Index_Nest* scope = note->parent->next;
        if (scope != 0 && scope->kind == CodeIndexNest_Scope){
          best_note = note;
          break;
        }
      }
    }
  }

  if (best_note) {
    return best_note; // found implementation
  }

  // give first decloration you can find
  for (Code_Index_Note *note = first_note; note != 0; note = note->next_in_hash){
    if (string_match(iden_string, note->text)){
      return note;
    }
  }

  return NULL; // Nothing was found
}

function void
zk_go_to_definition_at_cursor(Application_Links *app, b32 same_panel) {
  ProfileScope(app, "[ZK] Jump to definition at cursor");
  Scratch_Block scratch(app);

  View_ID view = get_active_view(app, Access_Visible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
  i64 pos = view_get_cursor_pos(app, view);

  if (!same_panel)
    view = get_next_view_looped_primary_panels(app, view, Access_Always);
  if (view == 0) return;

  Token *token = get_token_from_pos(app, buffer, pos);
  if (token == NULL || token->size <= 0 ||
        token->kind == TokenBaseKind_Whitespace) return;
  String_Const_u8 query = push_buffer_range(app, scratch, buffer, Ii64(token));

  if (token->kind != TokenBaseKind_LiteralString) {
    code_index_lock();
    Code_Index_Note_List* list = code_index__list_from_string(query);
    Code_Index_Note *note = zk_find_next_intuitive_note(buffer, list->first, query, pos);
    if (note) {
      point_stack_push_view_cursor(app, view);
      if (same_panel) jump_to_location(app, view,  note->file->buffer, note->pos.first);
      else zk_open_other_panel_to_location(app, note->file->buffer, note->pos.first);
    }
    code_index_unlock();
  }


  // Opening file buffer from string
  // TODO(ziv): Figure out a way to make this not langauge specific
  // like allowing to open odin packages if they are in the system

  b32 is_quotes     = '\"'== query.str[0] && query.str[query.size-1] == '\"';
  b32 is_alt_quotes = '<' == query.str[0] && query.str[query.size-1] == '>';
  if (!is_quotes && !is_alt_quotes) return;

  // if in project, just switch to the already opened buffer
  String_Const_u8 filename = SCu8(query.str+1, query.size-2);
  if (view_open_file(app, view, filename, true)) {
    view_set_active(app, view);
    return;
  }

  if (is_quotes && query.size > 2) {

    // not in project, assume base directory from file you request from
    String_Const_u8 base_path = string_remove_last_folder_and_slash(push_buffer_file_name(app, scratch, buffer));

    // Handle relative path
    i64 relative_count =0;
    u8 *str  = filename.str;
    for (u64 i = 0; i < filename.size; str+=3, i+=3) {
      if (str[0] == '.' && str[1] == '.' && str[2] == '/') {
        relative_count++;
      }
      else {
        break;
      }
    }
    for (i64 i = 0; i < relative_count; i++) {
      base_path = string_remove_last_folder_and_slash(base_path);
    }
    filename = string_skip(filename, relative_count*3);

    String_Const_u8 full_path = push_u8_stringf(scratch, "%S\\%S", base_path, filename);
    if (view_open_file(app, view, full_path, true)){
      view_set_active(app, view);
    }
    return;
  }

  #if OS_WINDOWS
  if (is_alt_quotes) {

    // This is currently specific to my c/c++ development
    // It searches the msvc sdk, finds all folders that contain
    // relevant .h files, and returns the main ones I should
    // care about like winrt, cppwinrt, um, shared, ucrt
    local_persist List_String_Const_u8 list = {0};

    if (list.node_count == 0) {
      Arena *arena = &global_permanent_arena;
      String_Const_u8 base = zk_msvc_sdk_include_path(scratch);
      string_list_push(arena, &list, push_u8_stringf(arena, "%S\\%S", base, SCu8("ucrt")));
      string_list_push(arena, &list, push_u8_stringf(arena, "%S\\%S", base, SCu8("shared")));
      string_list_push(arena, &list, push_u8_stringf(arena, "%S\\%S", base, SCu8("um")));
      string_list_push(arena, &list, push_u8_stringf(arena, "%S\\%S", base, SCu8("winrt")));
      string_list_push(arena, &list, push_u8_stringf(arena, "%S\\%S", base, SCu8("cppwinrt")));

      // NOTE(ziv): Things like <stdint.h> are inside of the compiler's include folder
      // and I do not plan on supporting those.
    }

    String_Const_u8 full_path = {0};
    for (Node_String_Const_u8 *node = list.first; node; node = node->next) {
      full_path = zk_find_file_in_folder_recursive(scratch, node->string, filename);
      if (file_exists_and_is_file(app, full_path))  break;
    }

    // try to open the path
    Buffer_ID buf = get_buffer_by_name(app, full_path, Access_ReadVisible);
    if (!buffer_exists(app, buf)){
      buf = create_buffer(app, full_path,
                          BufferCreate_Background | BufferCreate_NeverNew);

      buffer_set_setting(app, buf, BufferSetting_Unimportant, true);
      buffer_set_setting(app, buf, BufferSetting_ReadOnly, true);
      buffer_set_setting(app, buf, BufferSetting_Unkillable, false);
    }

    view_set_buffer(app, view, buf, 0);
    view_set_active(app, view);
    return;
  }
  #endif

}

CUSTOM_COMMAND_MC_GLOBAL_SIG(zk_go_to_definition_same_panel)
CUSTOM_DOC("[ZK] Jump to the definition of identifier at the cursor")
{
  zk_go_to_definition_at_cursor(app, 1);
}

CUSTOM_COMMAND_MC_GLOBAL_SIG(zk_go_to_definition_other_panel)
CUSTOM_DOC("[ZK] Jump to the definition of identifier at the cursor other panel")
{
  zk_go_to_definition_at_cursor(app, 0);
}

//~ Mouse behavior stuff


CUSTOM_COMMAND_MC_GLOBAL_SIG(zk_mouse_column_toggle)
CUSTOM_DOC("[ZK] Toggles the column for bumping and selects hovered char at mouse position")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  Mouse_State mouse = get_mouse_state(app);

  if (qol_col_cursor.pos < 0){
    i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
    qol_col_cursor = buffer_compute_cursor(app, buffer, seek_pos(pos));
    qol_col_buffer = buffer;

    if (mc_context.active){
      for_mc (node, mc_context.cursors){
        Buffer_Cursor cursor = buffer_compute_cursor(app, buffer, seek_pos(node->cursor_pos));
        if(qol_col_cursor.col < cursor.col){
          qol_col_cursor = cursor;
        }
      }
    }

    qol_target_char = buffer_get_char(app, buffer, qol_col_cursor.pos);
    qol_col_cursor = buffer_compute_cursor(app, buffer, seek_pos(pos));
  }
  else{
    qol_col_cursor.pos = -1;
  }
}

function void
zk_render_kill_rect(Application_Links *app, Frame_Info frame_info, View_ID view){
  Render_Caller_Function *custom_render = (Render_Caller_Function*)get_custom_hook(app, HookID_RenderCaller);
  custom_render(app, frame_info, view);

  Rect_f32 view_rect = view_get_screen_rect(app, view);
  Rect_f32 region = view_get_buffer_region(app, view);

  Face_ID face_id = get_face_id(app, 0);
  Face_Metrics metrics = get_face_metrics(app, face_id);
  f32 line_height = metrics.line_height;

  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
  Buffer_Point buffer_point = scroll.position;
  Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);
  Range_i64 range = get_view_range(app, view);
  Rect_f32 r0 = text_layout_character_on_screen(app, text_layout_id, range.min);
  Rect_f32 r1 = text_layout_character_on_screen(app, text_layout_id, range.max);
  Rect_f32 rect = rect_union(r0, r1);
  FColor f_color = fcolor_id(defcolor_highlight);

  String_Const_u8 prompt = string_u8_litexpr("Kill Rectangle: Yes: (Y) No: (N)");
  Vec2_f32 p = rect.p0 - V2f32(0, line_height);
  f32 advance = get_string_advance(app, face_id, prompt);
  Rect_f32 prompt_rect = Rf32(p - V2f32(10.f, 10.f), p + V2f32(advance + 10.f, line_height));
  draw_rectangle(app, prompt_rect, 5.f, 0xDD000000);
  draw_string(app, face_id, prompt, p, 0xFFFFFFFF);
  draw_rectangle_fcolor(app, rect, 5.f, fcolor_change_alpha(f_color, 0.5f));
  text_layout_free(app, text_layout_id);
}

CUSTOM_COMMAND_SIG(zk_kill_rectangle)
CUSTOM_DOC("[QOL] Prompt deletion of text in the cursor/mark rectangle")
{
  View_ID view = get_active_view(app, Access_Always);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
  Range_i64 range = get_view_range(app, view);
  if (buffer == 0){
    return qol_block_apply(app, view, view_get_buffer(app, view, Access_Always), range, qol_range_fade);
  }

  View_Context ctx = view_current_context(app, view);
  ctx.render_caller = zk_render_kill_rect;
  ctx.hides_buffer = false;
  View_Context_Block ctx_block(app, view, &ctx);

  for (;;){
    User_Input in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
    if (in.abort){ break; }
    else if (in.event.kind == InputEventKind_CustomFunction){ return in.event.custom_func(app); }
    else if (match_core_code(&in, CoreCode_TryExit)){ return implicit_map_function(app, 0, 0, &in.event).command(app); }
    else if (match_key_code(&in, KeyCode_Y)){ return qol_block_delete(app, view, buffer, range); }
    else if (match_key_code(&in, KeyCode_N)){ return; }
  }
}

//~

CUSTOM_COMMAND_SIG(casey_delete_to_end_of_line)
CUSTOM_DOC("Deletes everything from the cursor to the end of the line.")
{
  View_ID view = get_active_view(app, Access_ReadWriteVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
  i64 pos = view_get_cursor_pos(app, view);
  i64 line = get_line_number_from_pos(app, buffer, pos);
  Range_i64 range = get_line_pos_range(app, buffer, line);
  if(pos == range.end)
  {
    range.end = pos + 1;
    range.start = pos;
  }
  else
  {
    range.start = pos + 1;
  }

  i32 size = (i32)buffer_get_size(app, buffer);
  range.end = clamp_top(range.end, size);
  if (range_size(range) == 0 ||
        buffer_get_char(app, buffer, range.end - 1) != '\n'){
    range.start -= 1;
    range.first = clamp_bot(0, range.first);
  }
  buffer_replace_range(app, buffer, range, string_u8_litexpr(""));
}


//~


CUSTOM_COMMAND_SIG(zk_find_divider_up_or_notepadlike_highlight)
CUSTOM_DOC("[ZK] Find //- divider above cursor")
{
  if (fcoder_mode == FCoderMode_NotepadLike) {
    move_up_to_blank_line_end(app);
  }
  else {
    qol_find_divider(app, Scan_Backward);
  }
}

CUSTOM_COMMAND_SIG(zk_find_divider_down_or_notepadlike_highlight)
CUSTOM_DOC("[ZK] Find //- divider below cursor in orignal mode, on notepad mode highlights")
{
  if (fcoder_mode == FCoderMode_NotepadLike) {
    move_down_to_blank_line_end(app);
  }
  else {
    qol_find_divider(app, Scan_Forward);
  }
}


CUSTOM_COMMAND_SIG(zk_mouse_wheel_scroll)
CUSTOM_DOC("Reads the scroll wheel value from the mouse state and scrolls accordingly.")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Mouse_State mouse = get_mouse_state(app);
  if (mouse.wheel != 0){
    Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
    scroll.target = view_move_buffer_point(app, view, scroll.target, V2f32(0.f, (f32)mouse.wheel));

    if (fcoder_mode == FCoderMode_NotepadLike) {
      // Support correct notepad like behavior
      view_set_buffer_scroll(app, view, scroll, SetBufferScroll_NoCursorChange);
      no_mark_snap_to_cursor(app, view);
    }
    else {
      view_set_buffer_scroll(app, view, scroll, SetBufferScroll_SnapCursorIntoView);
    }
  }
  if (mouse.l){
    i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
    view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
    no_mark_snap_to_cursor(app, view);
  }
}

CUSTOM_COMMAND_SIG(zk_word_select)
CUSTOM_DOC("Selects word under mouse")
{
  Scratch_Block scratch(app);
  View_ID view = get_active_view(app, Access_Always);
  Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
  Mouse_State m = get_mouse_state(app);
  i64 pos = view_pos_from_xy(app, view, V2f32(m.p));

  #if 0
  Token *token = get_token_from_pos(app, buffer, pos);
  if (token != 0 && token->size > 0 && token->kind != TokenBaseKind_Whitespace){
    Range_i64 range = Ii64(token);
    view_set_mark(app, view, seek_pos(range.min));
    view_set_cursor(app, view, seek_pos(range.max));
  }
  #else
  i64 first_pos = 0;
  String_Const_u8 word = zk_buffer_get_string_under_cursor(app, scratch, buffer, pos, &first_pos);

  if (word.str != NULL && word.size > 0) {
    Range_i64 range = { first_pos, first_pos + (i64)word.size};
    view_set_mark(app, view, seek_pos(range.min));
    view_set_cursor(app, view, seek_pos(range.max));
  }
  #endif


}