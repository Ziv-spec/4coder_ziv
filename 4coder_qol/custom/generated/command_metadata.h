#if !defined(META_PASS)
#define command_id(c) (fcoder_metacmd_ID_##c)
#define command_metadata(c) (&fcoder_metacmd_table[command_id(c)])
#define command_metadata_by_id(id) (&fcoder_metacmd_table[id])
#define command_one_past_last_id 355
#if defined(CUSTOM_COMMAND_SIG)
#define PROC_LINKS(x,y) x
#else
#define PROC_LINKS(x,y) y
#endif

#if defined(CUSTOM_COMMAND_SIG)
void MC_add_at_pos(struct Application_Links *app);
void MC_begin_multi(struct Application_Links *app);
void MC_begin_multi_block(struct Application_Links *app);
void MC_del_at_pos(struct Application_Links *app);
void MC_down_trail(struct Application_Links *app);
void MC_end_multi(struct Application_Links *app);
void MC_error_fade(struct Application_Links *app);
void MC_up_trail(struct Application_Links *app);
void TAB_close(struct Application_Links *app);
void TAB_new(struct Application_Links *app);
void TAB_next(struct Application_Links *app);
void TAB_prev(struct Application_Links *app);
void allow_mouse(struct Application_Links *app);
void auto_indent_line_at_cursor(struct Application_Links *app);
void auto_indent_range(struct Application_Links *app);
void auto_indent_whole_file(struct Application_Links *app);
void backspace_alpha_numeric_boundary(struct Application_Links *app);
void backspace_char(struct Application_Links *app);
void basic_change_active_panel(struct Application_Links *app);
void begin_clipboard_collection_mode(struct Application_Links *app);
void begin_tutorial(struct Application_Links *app);
void build_in_build_panel(struct Application_Links *app);
void build_search(struct Application_Links *app);
void casey_delete_to_end_of_line(struct Application_Links *app);
void center_view(struct Application_Links *app);
void change_active_panel(struct Application_Links *app);
void change_active_panel_backwards(struct Application_Links *app);
void change_to_build_panel(struct Application_Links *app);
void clean_all_lines(struct Application_Links *app);
void clean_trailing_whitespace(struct Application_Links *app);
void clear_all_themes(struct Application_Links *app);
void clear_clipboard(struct Application_Links *app);
void click_set_cursor(struct Application_Links *app);
void click_set_cursor_and_mark(struct Application_Links *app);
void click_set_cursor_if_lbutton(struct Application_Links *app);
void click_set_mark(struct Application_Links *app);
void clipboard_record_clip(struct Application_Links *app);
void close_all_buffers(struct Application_Links *app);
void close_all_code(struct Application_Links *app);
void close_build_panel(struct Application_Links *app);
void close_panel(struct Application_Links *app);
void command_documentation(struct Application_Links *app);
void command_lister(struct Application_Links *app);
void comment_line(struct Application_Links *app);
void comment_line_toggle(struct Application_Links *app);
void copy(struct Application_Links *app);
void cursor_mark_swap(struct Application_Links *app);
void custom_api_documentation(struct Application_Links *app);
void cut(struct Application_Links *app);
void decrease_face_size(struct Application_Links *app);
void default_file_externally_modified(struct Application_Links *app);
void default_startup(struct Application_Links *app);
void default_try_exit(struct Application_Links *app);
void default_view_input_handler(struct Application_Links *app);
void delete_alpha_numeric_boundary(struct Application_Links *app);
void delete_char(struct Application_Links *app);
void delete_current_scope(struct Application_Links *app);
void delete_file_query(struct Application_Links *app);
void delete_line(struct Application_Links *app);
void delete_range(struct Application_Links *app);
void display_key_codes(struct Application_Links *app);
void display_text_input(struct Application_Links *app);
void double_backspace(struct Application_Links *app);
void duplicate_line(struct Application_Links *app);
void execute_any_cli(struct Application_Links *app);
void execute_previous_cli(struct Application_Links *app);
void exit_4coder(struct Application_Links *app);
void go_to_user_directory(struct Application_Links *app);
void goto_beginning_of_file(struct Application_Links *app);
void goto_end_of_file(struct Application_Links *app);
void goto_first_jump(struct Application_Links *app);
void goto_first_jump_same_panel_sticky(struct Application_Links *app);
void goto_jump_at_cursor(struct Application_Links *app);
void goto_jump_at_cursor_same_panel(struct Application_Links *app);
void goto_line(struct Application_Links *app);
void goto_next_jump(struct Application_Links *app);
void goto_next_jump_no_skips(struct Application_Links *app);
void goto_prev_jump(struct Application_Links *app);
void goto_prev_jump_no_skips(struct Application_Links *app);
void hide_filebar(struct Application_Links *app);
void hide_scrollbar(struct Application_Links *app);
void hit_sfx(struct Application_Links *app);
void hsplit(struct Application_Links *app);
void if0_off(struct Application_Links *app);
void if_read_only_goto_position(struct Application_Links *app);
void if_read_only_goto_position_same_panel(struct Application_Links *app);
void increase_face_size(struct Application_Links *app);
void interactive_kill_buffer(struct Application_Links *app);
void interactive_new(struct Application_Links *app);
void interactive_open(struct Application_Links *app);
void interactive_open_or_new(struct Application_Links *app);
void interactive_switch_buffer(struct Application_Links *app);
void jump_to_definition(struct Application_Links *app);
void jump_to_definition_at_cursor(struct Application_Links *app);
void jump_to_last_point(struct Application_Links *app);
void keyboard_macro_finish_recording(struct Application_Links *app);
void keyboard_macro_replay(struct Application_Links *app);
void keyboard_macro_start_recording(struct Application_Links *app);
void kill_buffer(struct Application_Links *app);
void kill_tutorial(struct Application_Links *app);
void left_adjust_view(struct Application_Links *app);
void list_all_functions_all_buffers(struct Application_Links *app);
void list_all_functions_all_buffers_lister(struct Application_Links *app);
void list_all_functions_current_buffer(struct Application_Links *app);
void list_all_functions_current_buffer_lister(struct Application_Links *app);
void list_all_locations(struct Application_Links *app);
void list_all_locations_case_insensitive(struct Application_Links *app);
void list_all_locations_of_identifier(struct Application_Links *app);
void list_all_locations_of_identifier_case_insensitive(struct Application_Links *app);
void list_all_locations_of_selection(struct Application_Links *app);
void list_all_locations_of_selection_case_insensitive(struct Application_Links *app);
void list_all_locations_of_type_definition(struct Application_Links *app);
void list_all_locations_of_type_definition_of_identifier(struct Application_Links *app);
void list_all_substring_locations(struct Application_Links *app);
void list_all_substring_locations_case_insensitive(struct Application_Links *app);
void load_project(struct Application_Links *app);
void load_theme_current_buffer(struct Application_Links *app);
void load_themes_default_folder(struct Application_Links *app);
void load_themes_hot_directory(struct Application_Links *app);
void loco_jump_between_yeet(struct Application_Links *app);
void loco_load_yeet_snapshot_1(struct Application_Links *app);
void loco_load_yeet_snapshot_2(struct Application_Links *app);
void loco_load_yeet_snapshot_3(struct Application_Links *app);
void loco_save_yeet_snapshot_1(struct Application_Links *app);
void loco_save_yeet_snapshot_2(struct Application_Links *app);
void loco_save_yeet_snapshot_3(struct Application_Links *app);
void loco_yeet_clear(struct Application_Links *app);
void loco_yeet_remove_marker_pair(struct Application_Links *app);
void loco_yeet_reset_all(struct Application_Links *app);
void loco_yeet_selected_range_or_jump(struct Application_Links *app);
void loco_yeet_surrounding_function(struct Application_Links *app);
void loco_yeet_tag(struct Application_Links *app);
void make_directory_query(struct Application_Links *app);
void miblo_decrement_basic(struct Application_Links *app);
void miblo_decrement_time_stamp(struct Application_Links *app);
void miblo_decrement_time_stamp_minute(struct Application_Links *app);
void miblo_increment_basic(struct Application_Links *app);
void miblo_increment_time_stamp(struct Application_Links *app);
void miblo_increment_time_stamp_minute(struct Application_Links *app);
void mouse_wheel_change_face_size(struct Application_Links *app);
void mouse_wheel_scroll(struct Application_Links *app);
void move_down(struct Application_Links *app);
void move_down_10(struct Application_Links *app);
void move_down_textual(struct Application_Links *app);
void move_down_to_blank_line(struct Application_Links *app);
void move_down_to_blank_line_end(struct Application_Links *app);
void move_down_to_blank_line_skip_whitespace(struct Application_Links *app);
void move_left(struct Application_Links *app);
void move_left_alpha_numeric_boundary(struct Application_Links *app);
void move_left_alpha_numeric_or_camel_boundary(struct Application_Links *app);
void move_left_token_boundary(struct Application_Links *app);
void move_left_whitespace_boundary(struct Application_Links *app);
void move_left_whitespace_or_token_boundary(struct Application_Links *app);
void move_line_down(struct Application_Links *app);
void move_line_up(struct Application_Links *app);
void move_right(struct Application_Links *app);
void move_right_alpha_numeric_boundary(struct Application_Links *app);
void move_right_alpha_numeric_or_camel_boundary(struct Application_Links *app);
void move_right_token_boundary(struct Application_Links *app);
void move_right_whitespace_boundary(struct Application_Links *app);
void move_right_whitespace_or_token_boundary(struct Application_Links *app);
void move_up(struct Application_Links *app);
void move_up_10(struct Application_Links *app);
void move_up_to_blank_line(struct Application_Links *app);
void move_up_to_blank_line_end(struct Application_Links *app);
void move_up_to_blank_line_skip_whitespace(struct Application_Links *app);
void multi_paste(struct Application_Links *app);
void multi_paste_interactive(struct Application_Links *app);
void multi_paste_interactive_quick(struct Application_Links *app);
void music_start(struct Application_Links *app);
void music_stop(struct Application_Links *app);
void open_all_code(struct Application_Links *app);
void open_all_code_recursive(struct Application_Links *app);
void open_file_in_quotes(struct Application_Links *app);
void open_in_other(struct Application_Links *app);
void open_long_braces(struct Application_Links *app);
void open_long_braces_break(struct Application_Links *app);
void open_long_braces_semicolon(struct Application_Links *app);
void open_matching_file_cpp(struct Application_Links *app);
void open_panel_hsplit(struct Application_Links *app);
void open_panel_vsplit(struct Application_Links *app);
void page_down(struct Application_Links *app);
void page_up(struct Application_Links *app);
void paste(struct Application_Links *app);
void paste_and_indent(struct Application_Links *app);
void paste_next(struct Application_Links *app);
void paste_next_and_indent(struct Application_Links *app);
void place_in_scope(struct Application_Links *app);
void play_with_a_counter(struct Application_Links *app);
void profile_clear(struct Application_Links *app);
void profile_disable(struct Application_Links *app);
void profile_enable(struct Application_Links *app);
void profile_inspect(struct Application_Links *app);
void project_command_F1(struct Application_Links *app);
void project_command_F10(struct Application_Links *app);
void project_command_F11(struct Application_Links *app);
void project_command_F12(struct Application_Links *app);
void project_command_F13(struct Application_Links *app);
void project_command_F14(struct Application_Links *app);
void project_command_F15(struct Application_Links *app);
void project_command_F16(struct Application_Links *app);
void project_command_F2(struct Application_Links *app);
void project_command_F3(struct Application_Links *app);
void project_command_F4(struct Application_Links *app);
void project_command_F5(struct Application_Links *app);
void project_command_F6(struct Application_Links *app);
void project_command_F7(struct Application_Links *app);
void project_command_F8(struct Application_Links *app);
void project_command_F9(struct Application_Links *app);
void project_command_lister(struct Application_Links *app);
void project_fkey_command(struct Application_Links *app);
void project_go_to_root_directory(struct Application_Links *app);
void project_reprint(struct Application_Links *app);
void qol_bview_active_to_bottom(struct Application_Links *app);
void qol_bview_bottom_to_active(struct Application_Links *app);
void qol_bview_close(struct Application_Links *app);
void qol_bview_open(struct Application_Links *app);
void qol_bview_scroll_down(struct Application_Links *app);
void qol_bview_scroll_up(struct Application_Links *app);
void qol_bview_toggle(struct Application_Links *app);
void qol_char_backward(struct Application_Links *app);
void qol_char_forward(struct Application_Links *app);
void qol_clear_jumps(struct Application_Links *app);
void qol_column_toggle(struct Application_Links *app);
void qol_ctrl_backspace(struct Application_Links *app);
void qol_ctrl_backwards(struct Application_Links *app);
void qol_ctrl_delete(struct Application_Links *app);
void qol_ctrl_forwards(struct Application_Links *app);
void qol_explorer(struct Application_Links *app);
void qol_find_divider_down(struct Application_Links *app);
void qol_find_divider_up(struct Application_Links *app);
void qol_format_all_buffers(struct Application_Links *app);
void qol_home(struct Application_Links *app);
void qol_jump_down(struct Application_Links *app);
void qol_jump_to_definition(struct Application_Links *app);
void qol_jump_up(struct Application_Links *app);
void qol_kill_rectangle(struct Application_Links *app);
void qol_loc(struct Application_Links *app);
void qol_modal_return(struct Application_Links *app);
void qol_move_selection_down(struct Application_Links *app);
void qol_move_selection_up(struct Application_Links *app);
void qol_reformat_current(struct Application_Links *app);
void qol_reload_bindings(struct Application_Links *app);
void qol_reload_config(struct Application_Links *app);
void qol_reload_project(struct Application_Links *app);
void qol_reopen_all_buffers(struct Application_Links *app);
void qol_reverse_search(struct Application_Links *app);
void qol_scroll_hovered(struct Application_Links *app);
void qol_search(struct Application_Links *app);
void qol_search_identifier(struct Application_Links *app);
void qol_snippet_begin(struct Application_Links *app);
void qol_snippet_end(struct Application_Links *app);
void qol_startup(struct Application_Links *app);
void qol_try_exit(struct Application_Links *app);
void qol_view_input_handler(struct Application_Links *app);
void qol_write_space(struct Application_Links *app);
void qol_write_text_and_auto_indent(struct Application_Links *app);
void qol_write_text_input(struct Application_Links *app);
void query_replace(struct Application_Links *app);
void query_replace_identifier(struct Application_Links *app);
void query_replace_selection(struct Application_Links *app);
void quick_swap_buffer(struct Application_Links *app);
void redo(struct Application_Links *app);
void redo_all_buffers(struct Application_Links *app);
void rename_file_query(struct Application_Links *app);
void reopen(struct Application_Links *app);
void replace_in_all_buffers(struct Application_Links *app);
void replace_in_buffer(struct Application_Links *app);
void replace_in_range(struct Application_Links *app);
void reverse_search(struct Application_Links *app);
void reverse_search_identifier(struct Application_Links *app);
void save(struct Application_Links *app);
void save_all_dirty_buffers(struct Application_Links *app);
void save_to_query(struct Application_Links *app);
void search(struct Application_Links *app);
void search_identifier(struct Application_Links *app);
void seek_beginning_of_line(struct Application_Links *app);
void seek_beginning_of_textual_line(struct Application_Links *app);
void seek_end_of_line(struct Application_Links *app);
void seek_end_of_textual_line(struct Application_Links *app);
void select_all(struct Application_Links *app);
void select_next_scope_absolute(struct Application_Links *app);
void select_next_scope_after_current(struct Application_Links *app);
void select_prev_scope_absolute(struct Application_Links *app);
void select_prev_top_most_scope(struct Application_Links *app);
void select_surrounding_scope(struct Application_Links *app);
void select_surrounding_scope_maximal(struct Application_Links *app);
void set_eol_mode_from_contents(struct Application_Links *app);
void set_eol_mode_to_binary(struct Application_Links *app);
void set_eol_mode_to_crlf(struct Application_Links *app);
void set_eol_mode_to_lf(struct Application_Links *app);
void set_face_size(struct Application_Links *app);
void set_face_size_this_buffer(struct Application_Links *app);
void set_mark(struct Application_Links *app);
void set_mode_to_notepad_like(struct Application_Links *app);
void set_mode_to_original(struct Application_Links *app);
void setup_build_bat(struct Application_Links *app);
void setup_build_bat_and_sh(struct Application_Links *app);
void setup_build_sh(struct Application_Links *app);
void setup_new_project(struct Application_Links *app);
void show_filebar(struct Application_Links *app);
void show_scrollbar(struct Application_Links *app);
void show_the_log_graph(struct Application_Links *app);
void snipe_backward_whitespace_or_token_boundary(struct Application_Links *app);
void snipe_forward_whitespace_or_token_boundary(struct Application_Links *app);
void snippet_lister(struct Application_Links *app);
void string_repeat(struct Application_Links *app);
void suppress_mouse(struct Application_Links *app);
void swap_panels(struct Application_Links *app);
void theme_lister(struct Application_Links *app);
void to_lowercase(struct Application_Links *app);
void to_uppercase(struct Application_Links *app);
void toggle_code_peek(struct Application_Links *app);
void toggle_filebar(struct Application_Links *app);
void toggle_fps_meter(struct Application_Links *app);
void toggle_fullscreen(struct Application_Links *app);
void toggle_function_tooltip(struct Application_Links *app);
void toggle_highlight_enclosing_scopes(struct Application_Links *app);
void toggle_highlight_line_at_cursor(struct Application_Links *app);
void toggle_line_numbers(struct Application_Links *app);
void toggle_line_wrap(struct Application_Links *app);
void toggle_mouse(struct Application_Links *app);
void toggle_paren_matching_helper(struct Application_Links *app);
void toggle_pproc_anchor(struct Application_Links *app);
void toggle_show_whitespace(struct Application_Links *app);
void toggle_virtual_whitespace(struct Application_Links *app);
void tutorial_maximize(struct Application_Links *app);
void tutorial_minimize(struct Application_Links *app);
void uncomment_line(struct Application_Links *app);
void undo(struct Application_Links *app);
void undo_all_buffers(struct Application_Links *app);
void view_buffer_other_panel(struct Application_Links *app);
void view_jump_list_with_lister(struct Application_Links *app);
void vsplit(struct Application_Links *app);
void word_complete(struct Application_Links *app);
void word_complete_drop_down(struct Application_Links *app);
void word_complete_prev(struct Application_Links *app);
void write_block(struct Application_Links *app);
void write_hack(struct Application_Links *app);
void write_note(struct Application_Links *app);
void write_space(struct Application_Links *app);
void write_text_and_auto_indent(struct Application_Links *app);
void write_text_input(struct Application_Links *app);
void write_todo(struct Application_Links *app);
void write_underscore(struct Application_Links *app);
void write_zero_struct(struct Application_Links *app);
void zk_go_to_definition_other_panel(struct Application_Links *app);
void zk_go_to_definition_same_panel(struct Application_Links *app);
void zk_jump_to_definition_lister(struct Application_Links *app);
void zk_kill_rectangle(struct Application_Links *app);
void zk_list_all_locations(struct Application_Links *app);
void zk_mouse_column_toggle(struct Application_Links *app);
void zk_reverse_search(struct Application_Links *app);
void zk_search(struct Application_Links *app);
void zk_startup(struct Application_Links *app);
#endif

struct Command_Metadata{
PROC_LINKS(Custom_Command_Function, void) *proc;
u64 mc_kind;
b32 is_ui;
char *name;
i32 name_len;
char *description;
i32 description_len;
char *source_name;
i32 source_name_len;
i32 line_number;
};

static Command_Metadata fcoder_metacmd_table[355] = {
{ PROC_LINKS(MC_add_at_pos, 0), 0, false, "MC_add_at_pos", 13, "[MC] adds multi-cursor at current pos", 37, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 375 },
{ PROC_LINKS(MC_begin_multi, 0), 0, false, "MC_begin_multi", 14, "[MC] begins multi-cursors", 25, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 388 },
{ PROC_LINKS(MC_begin_multi_block, 0), 0, false, "MC_begin_multi_block", 20, "[MC] begins multi-cursor using cursor-mark block-rect", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 414 },
{ PROC_LINKS(MC_del_at_pos, 0), 0, false, "MC_del_at_pos", 13, "[MC] deletes multi-cursor at current pos", 40, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 381 },
{ PROC_LINKS(MC_down_trail, 0), 0, false, "MC_down_trail", 13, "[MC] moves down, leaving a multi-cursor behind it", 49, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 407 },
{ PROC_LINKS(MC_end_multi, 0), 2, false, "MC_end_multi", 12, "[MC] ends multi-cursors", 23, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 394 },
{ PROC_LINKS(MC_error_fade, 0), 1, false, "MC_error_fade", 13, "[MC] display error fades", 24, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 366 },
{ PROC_LINKS(MC_up_trail, 0), 0, false, "MC_up_trail", 11, "[MC] moves up, leaving a multi-cursor behind it", 47, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_multi_cursor.cpp", 60, 400 },
{ PROC_LINKS(TAB_close, 0), 0, false, "TAB_close", 9, "[TAB] closes current tab", 24, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_tabs.cpp", 52, 513 },
{ PROC_LINKS(TAB_new, 0), 0, false, "TAB_new", 7, "[TAB] create new tab with current buffer", 40, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_tabs.cpp", 52, 501 },
{ PROC_LINKS(TAB_next, 0), 0, false, "TAB_next", 8, "[TAB] switch to next tab in list", 32, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_tabs.cpp", 52, 487 },
{ PROC_LINKS(TAB_prev, 0), 0, false, "TAB_prev", 8, "[TAB] switch to prev tab in list", 32, "E:\\dev\\4coder_ziv\\4coder_qol\\plugins\\4coder_tabs.cpp", 52, 494 },
{ PROC_LINKS(allow_mouse, 0), 2, false, "allow_mouse", 11, "Shows the mouse and causes all mouse input to be processed normally.", 68, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 482 },
{ PROC_LINKS(auto_indent_line_at_cursor, 0), 0, false, "auto_indent_line_at_cursor", 26, "Auto-indents the line on which the cursor sits.", 47, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_auto_indent.cpp", 58, 420 },
{ PROC_LINKS(auto_indent_range, 0), 0, false, "auto_indent_range", 17, "Auto-indents the range between the cursor and the mark.", 55, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_auto_indent.cpp", 58, 430 },
{ PROC_LINKS(auto_indent_whole_file, 0), 0, false, "auto_indent_whole_file", 22, "Audo-indents the entire current buffer.", 39, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_auto_indent.cpp", 58, 411 },
{ PROC_LINKS(backspace_alpha_numeric_boundary, 0), 1, false, "backspace_alpha_numeric_boundary", 32, "Delete characters between the cursor position and the first alphanumeric boundary to the left.", 94, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 156 },
{ PROC_LINKS(backspace_char, 0), 1, false, "backspace_char", 14, "Deletes the character to the left of the cursor.", 48, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 96 },
{ PROC_LINKS(basic_change_active_panel, 0), 0, false, "basic_change_active_panel", 25, "Change the currently active panel, moving to the panel with the next highest view_id.  Will not skipe the build panel if it is open.", 132, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 675 },
{ PROC_LINKS(begin_clipboard_collection_mode, 0), 0, true, "begin_clipboard_collection_mode", 31, "Allows the user to copy multiple strings from other applications before switching to 4coder and pasting them all.", 113, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 71 },
{ PROC_LINKS(begin_tutorial, 0), 2, false, "begin_tutorial", 14, "Tutorial for built in 4coder bindings and features.", 51, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_tutorial.cpp", 55, 880 },
{ PROC_LINKS(build_in_build_panel, 0), 2, false, "build_in_build_panel", 20, "Looks for a build.bat, build.sh, or makefile in the current and parent directories.  Runs the first that it finds and prints the output to *compilation*.  Puts the *compilation* buffer in a panel at the footer of the current view.", 230, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_build_commands.cpp", 61, 160 },
{ PROC_LINKS(build_search, 0), 2, false, "build_search", 12, "Looks for a build.bat, build.sh, or makefile in the current and parent directories.  Runs the first that it finds and prints the output to *compilation*.", 153, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_build_commands.cpp", 61, 120 },
{ PROC_LINKS(casey_delete_to_end_of_line, 0), 0, false, "casey_delete_to_end_of_line", 27, "Deletes everything from the cursor to the end of the line.", 58, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_commands.cpp", 50, 438 },
{ PROC_LINKS(center_view, 0), 2, false, "center_view", 11, "Centers the view vertically on the line on which the cursor sits.", 65, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 199 },
{ PROC_LINKS(change_active_panel, 0), 0, false, "change_active_panel", 19, "Change the currently active panel, moving to the panel with the next highest view_id.", 85, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 344 },
{ PROC_LINKS(change_active_panel_backwards, 0), 0, false, "change_active_panel_backwards", 29, "Change the currently active panel, moving to the panel with the next lowest view_id.", 84, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 350 },
{ PROC_LINKS(change_to_build_panel, 0), 0, false, "change_to_build_panel", 21, "If the special build panel is open, makes the build panel the active panel.", 75, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_build_commands.cpp", 61, 181 },
{ PROC_LINKS(clean_all_lines, 0), 2, false, "clean_all_lines", 15, "Removes trailing whitespace from all lines and removes all blank lines in the current buffer.", 93, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 655 },
{ PROC_LINKS(clean_trailing_whitespace, 0), 2, false, "clean_trailing_whitespace", 25, "Removes trailing whitespace from all lines in the current buffer.", 65, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 664 },
{ PROC_LINKS(clear_all_themes, 0), 2, false, "clear_all_themes", 16, "Clear the theme list", 20, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 566 },
{ PROC_LINKS(clear_clipboard, 0), 3, false, "clear_clipboard", 15, "Clears the history of the clipboard", 35, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 221 },
{ PROC_LINKS(click_set_cursor, 0), 0, false, "click_set_cursor", 16, "Sets the cursor position to the mouse position.", 47, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 240 },
{ PROC_LINKS(click_set_cursor_and_mark, 0), 0, false, "click_set_cursor_and_mark", 25, "Sets the cursor position and mark to the mouse position.", 56, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 227 },
{ PROC_LINKS(click_set_cursor_if_lbutton, 0), 0, false, "click_set_cursor_if_lbutton", 27, "If the mouse left button is pressed, sets the cursor position to the mouse position.", 84, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 253 },
{ PROC_LINKS(click_set_mark, 0), 0, false, "click_set_mark", 14, "Sets the mark position to the mouse position.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 267 },
{ PROC_LINKS(clipboard_record_clip, 0), 0, false, "clipboard_record_clip", 21, "In response to a new clipboard contents events, saves the new clip onto the clipboard history", 93, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 7 },
{ PROC_LINKS(close_all_buffers, 0), 0, false, "close_all_buffers", 17, "[QOL] Closes all buffers", 24, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 105 },
{ PROC_LINKS(close_all_code, 0), 0, false, "close_all_code", 14, "Closes any buffer with a filename ending with an extension configured to be recognized as a code file type.", 107, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 806 },
{ PROC_LINKS(close_build_panel, 0), 2, false, "close_build_panel", 17, "If the special build panel is open, closes it.", 46, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_build_commands.cpp", 61, 175 },
{ PROC_LINKS(close_panel, 0), 0, false, "close_panel", 11, "Closes the currently active panel if it is not the only panel open.", 67, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 683 },
{ PROC_LINKS(command_documentation, 0), 0, true, "command_documentation", 21, "Prompts the user to select a command then loads a doc buffer for that item", 74, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_docs.cpp", 51, 187 },
{ PROC_LINKS(command_lister, 0), 0, true, "command_lister", 14, "Opens an interactive list of all registered commands.", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 756 },
{ PROC_LINKS(comment_line, 0), 1, false, "comment_line", 12, "Insert '//' at the beginning of the line after leading whitespace.", 66, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 125 },
{ PROC_LINKS(comment_line_toggle, 0), 1, false, "comment_line_toggle", 19, "Turns uncommented lines into commented lines and vice versa for comments starting with '//'.", 92, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 149 },
{ PROC_LINKS(copy, 0), 3, false, "copy", 4, "Copy the text in the range from the cursor to the mark onto the clipboard.", 74, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 110 },
{ PROC_LINKS(cursor_mark_swap, 0), 1, false, "cursor_mark_swap", 16, "Swaps the position of the cursor and the mark.", 46, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 124 },
{ PROC_LINKS(custom_api_documentation, 0), 0, true, "custom_api_documentation", 24, "Prompts the user to select a Custom API item then loads a doc buffer for that item", 82, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_docs.cpp", 51, 172 },
{ PROC_LINKS(cut, 0), 3, false, "cut", 3, "Cut the text in the range from the cursor to the mark onto the clipboard.", 73, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 119 },
{ PROC_LINKS(decrease_face_size, 0), 2, false, "decrease_face_size", 18, "Decrease the size of the face used by the current buffer.", 57, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 768 },
{ PROC_LINKS(default_file_externally_modified, 0), 0, false, "default_file_externally_modified", 32, "Notes the external modification of attached files by printing a message.", 72, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 2075 },
{ PROC_LINKS(default_startup, 0), 0, false, "default_startup", 15, "Default command for responding to a startup event", 49, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_hooks.cpp", 60, 7 },
{ PROC_LINKS(default_try_exit, 0), 0, false, "default_try_exit", 16, "Default command for responding to a try-exit event", 50, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_hooks.cpp", 60, 33 },
{ PROC_LINKS(default_view_input_handler, 0), 0, false, "default_view_input_handler", 26, "Input consumption loop for default view behavior", 48, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_hooks.cpp", 60, 77 },
{ PROC_LINKS(delete_alpha_numeric_boundary, 0), 1, false, "delete_alpha_numeric_boundary", 29, "Delete characters between the cursor position and the first alphanumeric boundary to the right.", 95, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 164 },
{ PROC_LINKS(delete_char, 0), 1, false, "delete_char", 11, "Deletes the character to the right of the cursor.", 49, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 79 },
{ PROC_LINKS(delete_current_scope, 0), 0, false, "delete_current_scope", 20, "Deletes the braces surrounding the currently selected scope.  Leaves the contents within the scope.", 99, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 112 },
{ PROC_LINKS(delete_file_query, 0), 0, false, "delete_file_query", 17, "Deletes the file of the current buffer if 4coder has the appropriate access rights. Will ask the user for confirmation first.", 125, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1391 },
{ PROC_LINKS(delete_line, 0), 1, false, "delete_line", 11, "Delete the line the on which the cursor sits.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1563 },
{ PROC_LINKS(delete_range, 0), 1, false, "delete_range", 12, "Deletes the text in the range between the cursor and the mark.", 62, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 134 },
{ PROC_LINKS(display_key_codes, 0), 2, false, "display_key_codes", 17, "Example of input handling loop", 30, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 90 },
{ PROC_LINKS(display_text_input, 0), 2, false, "display_text_input", 18, "Example of to_writable and leave_current_input_unhandled", 56, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 137 },
{ PROC_LINKS(double_backspace, 0), 1, false, "double_backspace", 16, "Example of history group helpers", 32, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 10 },
{ PROC_LINKS(duplicate_line, 0), 1, false, "duplicate_line", 14, "Create a copy of the line on which the cursor sits.", 51, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1549 },
{ PROC_LINKS(execute_any_cli, 0), 2, false, "execute_any_cli", 15, "Queries for an output buffer name and system command, runs the system command as a CLI and prints the output to the specified buffer.", 133, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_cli_command.cpp", 58, 22 },
{ PROC_LINKS(execute_previous_cli, 0), 2, false, "execute_previous_cli", 20, "If the command execute_any_cli has already been used, this will execute a CLI reusing the most recent buffer name and command.", 126, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_cli_command.cpp", 58, 7 },
{ PROC_LINKS(exit_4coder, 0), 2, false, "exit_4coder", 11, "Attempts to close 4coder.", 25, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 857 },
{ PROC_LINKS(go_to_user_directory, 0), 2, false, "go_to_user_directory", 20, "Go to the 4coder user directory", 31, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_config.cpp", 53, 1746 },
{ PROC_LINKS(goto_beginning_of_file, 0), 0, false, "goto_beginning_of_file", 22, "Sets the cursor to the beginning of the file.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_helper.cpp", 53, 2271 },
{ PROC_LINKS(goto_end_of_file, 0), 0, false, "goto_end_of_file", 16, "Sets the cursor to the end of the file.", 39, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_helper.cpp", 53, 2279 },
{ PROC_LINKS(goto_first_jump, 0), 0, false, "goto_first_jump", 15, "If a buffer containing jump locations has been locked in, goes to the first jump in the buffer.", 95, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 529 },
{ PROC_LINKS(goto_first_jump_same_panel_sticky, 0), 0, false, "goto_first_jump_same_panel_sticky", 33, "If a buffer containing jump locations has been locked in, goes to the first jump in the buffer and views the buffer in the panel where the jump list was.", 153, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 546 },
{ PROC_LINKS(goto_jump_at_cursor, 0), 0, false, "goto_jump_at_cursor", 19, "If the cursor is found to be on a jump location, parses the jump location and brings up the file and position in another view and changes the active panel to the view containing the jump.", 187, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 349 },
{ PROC_LINKS(goto_jump_at_cursor_same_panel, 0), 0, false, "goto_jump_at_cursor_same_panel", 30, "If the cursor is found to be on a jump location, parses the jump location and brings up the file and position in this view, losing the compilation output or jump list.", 167, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 376 },
{ PROC_LINKS(goto_line, 0), 0, false, "goto_line", 9, "Queries the user for a number, and jumps the cursor to the corresponding line.", 78, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 865 },
{ PROC_LINKS(goto_next_jump, 0), 0, false, "goto_next_jump", 14, "If a buffer containing jump locations has been locked in, goes to the next jump in the buffer, skipping sub jump locations.", 123, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 467 },
{ PROC_LINKS(goto_next_jump_no_skips, 0), 0, false, "goto_next_jump_no_skips", 23, "If a buffer containing jump locations has been locked in, goes to the next jump in the buffer, and does not skip sub jump locations.", 132, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 498 },
{ PROC_LINKS(goto_prev_jump, 0), 0, false, "goto_prev_jump", 14, "If a buffer containing jump locations has been locked in, goes to the previous jump in the buffer, skipping sub jump locations.", 127, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 485 },
{ PROC_LINKS(goto_prev_jump_no_skips, 0), 0, false, "goto_prev_jump_no_skips", 23, "If a buffer containing jump locations has been locked in, goes to the previous jump in the buffer, and does not skip sub jump locations.", 136, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 515 },
{ PROC_LINKS(hide_filebar, 0), 2, false, "hide_filebar", 12, "Sets the current view to hide it's filebar.", 43, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 715 },
{ PROC_LINKS(hide_scrollbar, 0), 2, false, "hide_scrollbar", 14, "Sets the current view to hide it's scrollbar.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 701 },
{ PROC_LINKS(hit_sfx, 0), 2, false, "hit_sfx", 7, "Play the hit sound effect", 25, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 240 },
{ PROC_LINKS(hsplit, 0), 0, false, "hsplit", 6, "Create a new panel by horizontally splitting the active panel.", 62, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 386 },
{ PROC_LINKS(if0_off, 0), 1, false, "if0_off", 7, "Surround the range between the cursor and mark with an '#if 0' and an '#endif'", 78, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 70 },
{ PROC_LINKS(if_read_only_goto_position, 0), 0, false, "if_read_only_goto_position", 26, "If the buffer in the active view is writable, inserts a character, otherwise performs goto_jump_at_cursor.", 106, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 568 },
{ PROC_LINKS(if_read_only_goto_position_same_panel, 0), 0, false, "if_read_only_goto_position_same_panel", 37, "If the buffer in the active view is writable, inserts a character, otherwise performs goto_jump_at_cursor_same_panel.", 117, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_sticky.cpp", 58, 585 },
{ PROC_LINKS(increase_face_size, 0), 2, false, "increase_face_size", 18, "Increase the size of the face used by the current buffer.", 57, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 757 },
{ PROC_LINKS(interactive_kill_buffer, 0), 0, true, "interactive_kill_buffer", 23, "Interactively kill an open buffer.", 34, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 519 },
{ PROC_LINKS(interactive_new, 0), 0, true, "interactive_new", 15, "Interactively creates a new file.", 33, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 658 },
{ PROC_LINKS(interactive_open, 0), 0, true, "interactive_open", 16, "Interactively opens a file.", 27, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 711 },
{ PROC_LINKS(interactive_open_or_new, 0), 0, true, "interactive_open_or_new", 23, "Interactively open a file out of the file system.", 49, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 610 },
{ PROC_LINKS(interactive_switch_buffer, 0), 0, true, "interactive_switch_buffer", 25, "Interactively switch to an open buffer.", 39, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 509 },
{ PROC_LINKS(jump_to_definition, 0), 0, true, "jump_to_definition", 18, "List all definitions in the code index and jump to one chosen by the user.", 74, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_code_index_listers.cpp", 65, 38 },
{ PROC_LINKS(jump_to_definition_at_cursor, 0), 0, true, "jump_to_definition_at_cursor", 28, "Jump to the first definition in the code index matching an identifier at the cursor", 83, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_code_index_listers.cpp", 65, 61 },
{ PROC_LINKS(jump_to_last_point, 0), 0, false, "jump_to_last_point", 18, "Read from the top of the point stack and jump there; if already there pop the top and go to the next option", 107, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1344 },
{ PROC_LINKS(keyboard_macro_finish_recording, 0), 2, false, "keyboard_macro_finish_recording", 31, "Stop macro recording, do nothing if macro recording is not already started", 74, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_keyboard_macro.cpp", 61, 54 },
{ PROC_LINKS(keyboard_macro_replay, 0), 1, false, "keyboard_macro_replay", 21, "Replay the most recently recorded keyboard macro", 48, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_keyboard_macro.cpp", 61, 77 },
{ PROC_LINKS(keyboard_macro_start_recording, 0), 2, false, "keyboard_macro_start_recording", 30, "Start macro recording, do nothing if macro recording is already started", 71, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_keyboard_macro.cpp", 61, 41 },
{ PROC_LINKS(kill_buffer, 0), 0, false, "kill_buffer", 11, "Kills the current buffer.", 25, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1734 },
{ PROC_LINKS(kill_tutorial, 0), 2, false, "kill_tutorial", 13, "If there is an active tutorial, kill it.", 40, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_tutorial.cpp", 55, 10 },
{ PROC_LINKS(left_adjust_view, 0), 2, false, "left_adjust_view", 16, "Sets the left size of the view near the x position of the cursor.", 65, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 214 },
{ PROC_LINKS(list_all_functions_all_buffers, 0), 2, false, "list_all_functions_all_buffers", 30, "Creates a jump list of lines from all buffers that appear to define or declare functions.", 89, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_function_list.cpp", 60, 297 },
{ PROC_LINKS(list_all_functions_all_buffers_lister, 0), 0, true, "list_all_functions_all_buffers_lister", 37, "Creates a lister of locations that look like function definitions and declarations all buffers.", 95, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_function_list.cpp", 60, 303 },
{ PROC_LINKS(list_all_functions_current_buffer, 0), 2, false, "list_all_functions_current_buffer", 33, "Creates a jump list of lines of the current buffer that appear to define or declare functions.", 94, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_function_list.cpp", 60, 269 },
{ PROC_LINKS(list_all_functions_current_buffer_lister, 0), 0, true, "list_all_functions_current_buffer_lister", 40, "Creates a lister of locations that look like function definitions and declarations in the buffer.", 97, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_function_list.cpp", 60, 279 },
{ PROC_LINKS(list_all_locations, 0), 0, false, "list_all_locations", 18, "Queries the user for a string and lists all exact case-sensitive matches found in all open buffers.", 99, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 173 },
{ PROC_LINKS(list_all_locations_case_insensitive, 0), 0, false, "list_all_locations_case_insensitive", 35, "Queries the user for a string and lists all exact case-insensitive matches found in all open buffers.", 101, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 185 },
{ PROC_LINKS(list_all_locations_of_identifier, 0), 0, false, "list_all_locations_of_identifier", 32, "Reads a token or word under the cursor and lists all exact case-sensitive mathces in all open buffers.", 102, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 197 },
{ PROC_LINKS(list_all_locations_of_identifier_case_insensitive, 0), 0, false, "list_all_locations_of_identifier_case_insensitive", 49, "Reads a token or word under the cursor and lists all exact case-insensitive mathces in all open buffers.", 104, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 203 },
{ PROC_LINKS(list_all_locations_of_selection, 0), 0, false, "list_all_locations_of_selection", 31, "Reads the string in the selected range and lists all exact case-sensitive mathces in all open buffers.", 102, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 209 },
{ PROC_LINKS(list_all_locations_of_selection_case_insensitive, 0), 0, false, "list_all_locations_of_selection_case_insensitive", 48, "Reads the string in the selected range and lists all exact case-insensitive mathces in all open buffers.", 104, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 215 },
{ PROC_LINKS(list_all_locations_of_type_definition, 0), 0, false, "list_all_locations_of_type_definition", 37, "Queries user for string, lists all locations of strings that appear to define a type whose name matches the input string.", 121, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 221 },
{ PROC_LINKS(list_all_locations_of_type_definition_of_identifier, 0), 0, false, "list_all_locations_of_type_definition_of_identifier", 51, "Reads a token or word under the cursor and lists all locations of strings that appear to define a type whose name matches it.", 125, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 229 },
{ PROC_LINKS(list_all_substring_locations, 0), 0, false, "list_all_substring_locations", 28, "Queries the user for a string and lists all case-sensitive substring matches found in all open buffers.", 103, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 179 },
{ PROC_LINKS(list_all_substring_locations_case_insensitive, 0), 0, false, "list_all_substring_locations_case_insensitive", 45, "Queries the user for a string and lists all case-insensitive substring matches found in all open buffers.", 105, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 191 },
{ PROC_LINKS(load_project, 0), 2, false, "load_project", 12, "Looks for a project.4coder file in the current directory and tries to load it.  Looks in parent directories until a project file is found or there are no more parents.", 167, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 892 },
{ PROC_LINKS(load_theme_current_buffer, 0), 2, false, "load_theme_current_buffer", 25, "Parse the current buffer as a theme file and add the theme to the theme list. If the buffer has a .4coder postfix in it's name, it is removed when the name is saved.", 165, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_config.cpp", 53, 1702 },
{ PROC_LINKS(load_themes_default_folder, 0), 2, false, "load_themes_default_folder", 26, "Loads all the theme files in the default theme folder.", 54, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 536 },
{ PROC_LINKS(load_themes_hot_directory, 0), 2, false, "load_themes_hot_directory", 25, "Loads all the theme files in the current hot directory.", 55, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 555 },
{ PROC_LINKS(loco_jump_between_yeet, 0), 0, false, "loco_jump_between_yeet", 22, "Jumps from the yeet sheet to the original buffer or vice versa.", 63, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 723 },
{ PROC_LINKS(loco_load_yeet_snapshot_1, 0), 0, false, "loco_load_yeet_snapshot_1", 25, "Load yeets snapshot from slot 1.", 32, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 887 },
{ PROC_LINKS(loco_load_yeet_snapshot_2, 0), 0, false, "loco_load_yeet_snapshot_2", 25, "Load yeets snapshot from slot 2.", 32, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 894 },
{ PROC_LINKS(loco_load_yeet_snapshot_3, 0), 0, false, "loco_load_yeet_snapshot_3", 25, "Load yeets snapshot from slot 3.", 32, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 901 },
{ PROC_LINKS(loco_save_yeet_snapshot_1, 0), 0, false, "loco_save_yeet_snapshot_1", 25, "Save yeets snapshot to slot 1.", 30, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 866 },
{ PROC_LINKS(loco_save_yeet_snapshot_2, 0), 0, false, "loco_save_yeet_snapshot_2", 25, "Save yeets snapshot to slot 2.", 30, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 873 },
{ PROC_LINKS(loco_save_yeet_snapshot_3, 0), 0, false, "loco_save_yeet_snapshot_3", 25, "Save yeets snapshot to slot 3.", 30, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 880 },
{ PROC_LINKS(loco_yeet_clear, 0), 0, false, "loco_yeet_clear", 15, "Clears all yeets.", 17, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 772 },
{ PROC_LINKS(loco_yeet_remove_marker_pair, 0), 0, false, "loco_yeet_remove_marker_pair", 28, "Removes the marker pair the cursor is currently inside.", 55, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 818 },
{ PROC_LINKS(loco_yeet_reset_all, 0), 0, false, "loco_yeet_reset_all", 19, "Clears all yeets in all snapshots, also clears all the markers.", 63, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 801 },
{ PROC_LINKS(loco_yeet_selected_range_or_jump, 0), 0, false, "loco_yeet_selected_range_or_jump", 32, "Yeets some code into a yeet buffer.", 35, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 730 },
{ PROC_LINKS(loco_yeet_surrounding_function, 0), 0, false, "loco_yeet_surrounding_function", 30, "Selects the surrounding function scope and yeets it.", 52, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 746 },
{ PROC_LINKS(loco_yeet_tag, 0), 0, false, "loco_yeet_tag", 13, "Find all locations of a comment tag (//@tag) in all buffers and yeet the scope they precede.", 92, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_loco_yeets.cpp", 49, 1040 },
{ PROC_LINKS(make_directory_query, 0), 0, false, "make_directory_query", 20, "Queries the user for a name and creates a new directory with the given name.", 76, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1503 },
{ PROC_LINKS(miblo_decrement_basic, 0), 1, false, "miblo_decrement_basic", 21, "Decrement an integer under the cursor by one.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_miblo_numbers.cpp", 60, 44 },
{ PROC_LINKS(miblo_decrement_time_stamp, 0), 1, false, "miblo_decrement_time_stamp", 26, "Decrement a time stamp under the cursor by one second. (format [m]m:ss or h:mm:ss", 81, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_miblo_numbers.cpp", 60, 237 },
{ PROC_LINKS(miblo_decrement_time_stamp_minute, 0), 1, false, "miblo_decrement_time_stamp_minute", 33, "Decrement a time stamp under the cursor by one minute. (format [m]m:ss or h:mm:ss", 81, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_miblo_numbers.cpp", 60, 249 },
{ PROC_LINKS(miblo_increment_basic, 0), 1, false, "miblo_increment_basic", 21, "Increment an integer under the cursor by one.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_miblo_numbers.cpp", 60, 29 },
{ PROC_LINKS(miblo_increment_time_stamp, 0), 1, false, "miblo_increment_time_stamp", 26, "Increment a time stamp under the cursor by one second. (format [m]m:ss or h:mm:ss", 81, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_miblo_numbers.cpp", 60, 231 },
{ PROC_LINKS(miblo_increment_time_stamp_minute, 0), 1, false, "miblo_increment_time_stamp_minute", 33, "Increment a time stamp under the cursor by one minute. (format [m]m:ss or h:mm:ss", 81, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_miblo_numbers.cpp", 60, 243 },
{ PROC_LINKS(mouse_wheel_change_face_size, 0), 2, false, "mouse_wheel_change_face_size", 28, "Reads the state of the mouse wheel and uses it to either increase or decrease the face size.", 92, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 810 },
{ PROC_LINKS(mouse_wheel_scroll, 0), 0, false, "mouse_wheel_scroll", 18, "Reads the scroll wheel value from the mouse state and scrolls accordingly.", 74, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 277 },
{ PROC_LINKS(move_down, 0), 1, false, "move_down", 9, "Moves the cursor down one line.", 31, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 351 },
{ PROC_LINKS(move_down_10, 0), 1, false, "move_down_10", 12, "Moves the cursor down ten lines.", 32, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 363 },
{ PROC_LINKS(move_down_textual, 0), 1, false, "move_down_textual", 17, "Moves down to the next line of actual text, regardless of line wrapping.", 72, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 369 },
{ PROC_LINKS(move_down_to_blank_line, 0), 0, false, "move_down_to_blank_line", 23, "Seeks the cursor down to the next blank line.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 422 },
{ PROC_LINKS(move_down_to_blank_line_end, 0), 0, false, "move_down_to_blank_line_end", 27, "Seeks the cursor down to the next blank line and places it at the end of the line.", 82, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 446 },
{ PROC_LINKS(move_down_to_blank_line_skip_whitespace, 0), 0, false, "move_down_to_blank_line_skip_whitespace", 39, "Seeks the cursor down to the next blank line and places it at the end of the line.", 82, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 434 },
{ PROC_LINKS(move_left, 0), 1, false, "move_left", 9, "Moves the cursor one character to the left.", 43, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 452 },
{ PROC_LINKS(move_left_alpha_numeric_boundary, 0), 1, false, "move_left_alpha_numeric_boundary", 32, "Seek left for boundary between alphanumeric characters and non-alphanumeric characters.", 87, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 529 },
{ PROC_LINKS(move_left_alpha_numeric_or_camel_boundary, 0), 1, false, "move_left_alpha_numeric_or_camel_boundary", 41, "Seek left for boundary between alphanumeric characters or camel case word and non-alphanumeric characters.", 106, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 543 },
{ PROC_LINKS(move_left_token_boundary, 0), 1, false, "move_left_token_boundary", 24, "Seek left for the next beginning of a token.", 44, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 501 },
{ PROC_LINKS(move_left_whitespace_boundary, 0), 1, false, "move_left_whitespace_boundary", 29, "Seek left for the next boundary between whitespace and non-whitespace.", 70, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 486 },
{ PROC_LINKS(move_left_whitespace_or_token_boundary, 0), 1, false, "move_left_whitespace_or_token_boundary", 38, "Seek left for the next end of a token or boundary between whitespace and non-whitespace.", 88, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 515 },
{ PROC_LINKS(move_line_down, 0), 0, false, "move_line_down", 14, "Swaps the line under the cursor with the line below it, and moves the cursor down with it.", 90, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1543 },
{ PROC_LINKS(move_line_up, 0), 0, false, "move_line_up", 12, "Swaps the line under the cursor with the line above it, and moves the cursor up with it.", 88, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1537 },
{ PROC_LINKS(move_right, 0), 1, false, "move_right", 10, "Moves the cursor one character to the right.", 44, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 460 },
{ PROC_LINKS(move_right_alpha_numeric_boundary, 0), 1, false, "move_right_alpha_numeric_boundary", 33, "Seek right for boundary between alphanumeric characters and non-alphanumeric characters.", 88, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 522 },
{ PROC_LINKS(move_right_alpha_numeric_or_camel_boundary, 0), 1, false, "move_right_alpha_numeric_or_camel_boundary", 42, "Seek right for boundary between alphanumeric characters or camel case word and non-alphanumeric characters.", 107, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 536 },
{ PROC_LINKS(move_right_token_boundary, 0), 1, false, "move_right_token_boundary", 25, "Seek right for the next end of a token.", 39, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 494 },
{ PROC_LINKS(move_right_whitespace_boundary, 0), 1, false, "move_right_whitespace_boundary", 30, "Seek right for the next boundary between whitespace and non-whitespace.", 71, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 478 },
{ PROC_LINKS(move_right_whitespace_or_token_boundary, 0), 1, false, "move_right_whitespace_or_token_boundary", 39, "Seek right for the next end of a token or boundary between whitespace and non-whitespace.", 89, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 508 },
{ PROC_LINKS(move_up, 0), 1, false, "move_up", 7, "Moves the cursor up one line.", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 345 },
{ PROC_LINKS(move_up_10, 0), 1, false, "move_up_10", 10, "Moves the cursor up ten lines.", 30, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 357 },
{ PROC_LINKS(move_up_to_blank_line, 0), 0, false, "move_up_to_blank_line", 21, "Seeks the cursor up to the next blank line.", 43, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 416 },
{ PROC_LINKS(move_up_to_blank_line_end, 0), 0, false, "move_up_to_blank_line_end", 25, "Seeks the cursor up to the next blank line and places it at the end of the line.", 80, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 440 },
{ PROC_LINKS(move_up_to_blank_line_skip_whitespace, 0), 0, false, "move_up_to_blank_line_skip_whitespace", 37, "Seeks the cursor up to the next blank line and places it at the end of the line.", 80, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 428 },
{ PROC_LINKS(multi_paste, 0), 0, false, "multi_paste", 11, "Paste multiple entries from the clipboard at once", 49, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 229 },
{ PROC_LINKS(multi_paste_interactive, 0), 0, false, "multi_paste_interactive", 23, "Paste multiple lines from the clipboard history, controlled with arrow keys", 75, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 371 },
{ PROC_LINKS(multi_paste_interactive_quick, 0), 0, false, "multi_paste_interactive_quick", 29, "Paste multiple lines from the clipboard history, controlled by inputing the number of lines to paste", 100, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 380 },
{ PROC_LINKS(music_start, 0), 2, false, "music_start", 11, "Starts the music.", 17, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 213 },
{ PROC_LINKS(music_stop, 0), 2, false, "music_stop", 10, "Stops the music.", 16, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 234 },
{ PROC_LINKS(open_all_code, 0), 0, false, "open_all_code", 13, "Open all code in the current directory. File types are determined by extensions. An extension is considered code based on the extensions specified in 4coder.config.", 164, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 815 },
{ PROC_LINKS(open_all_code_recursive, 0), 0, false, "open_all_code_recursive", 23, "Works as open_all_code but also runs in all subdirectories.", 59, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 824 },
{ PROC_LINKS(open_file_in_quotes, 0), 0, false, "open_file_in_quotes", 19, "Reads a filename from surrounding '\"' characters and attempts to open the corresponding file.", 94, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1584 },
{ PROC_LINKS(open_in_other, 0), 0, false, "open_in_other", 13, "Interactively opens a file in the other panel.", 46, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 2069 },
{ PROC_LINKS(open_long_braces, 0), 1, false, "open_long_braces", 16, "At the cursor, insert a '{' and '}' separated by a blank line.", 62, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 46 },
{ PROC_LINKS(open_long_braces_break, 0), 1, false, "open_long_braces_break", 22, "At the cursor, insert a '{' and '}break;' separated by a blank line.", 68, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 62 },
{ PROC_LINKS(open_long_braces_semicolon, 0), 1, false, "open_long_braces_semicolon", 26, "At the cursor, insert a '{' and '};' separated by a blank line.", 63, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 54 },
{ PROC_LINKS(open_matching_file_cpp, 0), 0, false, "open_matching_file_cpp", 22, "If the current file is a *.cpp or *.h, attempts to open the corresponding *.h or *.cpp file in the other view.", 110, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1667 },
{ PROC_LINKS(open_panel_hsplit, 0), 0, false, "open_panel_hsplit", 17, "Create a new panel by horizontally splitting the active panel.", 62, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 370 },
{ PROC_LINKS(open_panel_vsplit, 0), 0, false, "open_panel_vsplit", 17, "Create a new panel by vertically splitting the active panel.", 60, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 360 },
{ PROC_LINKS(page_down, 0), 0, false, "page_down", 9, "Scrolls the view down one view height and moves the cursor down one view height.", 80, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 387 },
{ PROC_LINKS(page_up, 0), 0, false, "page_up", 7, "Scrolls the view up one view height and moves the cursor up one view height.", 76, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 379 },
{ PROC_LINKS(paste, 0), 4, false, "paste", 5, "At the cursor, insert the text at the top of the clipboard.", 59, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 130 },
{ PROC_LINKS(paste_and_indent, 0), 4, false, "paste_and_indent", 16, "Paste from the top of clipboard and run auto-indent on the newly pasted text.", 77, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 207 },
{ PROC_LINKS(paste_next, 0), 4, false, "paste_next", 10, "If the previous command was paste or paste_next, replaces the paste range with the next text down on the clipboard, otherwise operates as the paste command.", 156, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 164 },
{ PROC_LINKS(paste_next_and_indent, 0), 4, false, "paste_next_and_indent", 21, "Paste the next item on the clipboard and run auto-indent on the newly pasted text.", 82, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_clipboard.cpp", 56, 214 },
{ PROC_LINKS(place_in_scope, 0), 1, false, "place_in_scope", 14, "Wraps the code contained in the range between cursor and mark with a new curly brace scope.", 91, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 106 },
{ PROC_LINKS(play_with_a_counter, 0), 2, false, "play_with_a_counter", 19, "Example of query bar", 20, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 29 },
{ PROC_LINKS(profile_clear, 0), 2, false, "profile_clear", 13, "Clear all profiling information from 4coder's self profiler.", 60, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_profile.cpp", 54, 226 },
{ PROC_LINKS(profile_disable, 0), 2, false, "profile_disable", 15, "Prevent 4coder's self profiler from gathering new profiling information.", 72, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_profile.cpp", 54, 219 },
{ PROC_LINKS(profile_enable, 0), 2, false, "profile_enable", 14, "Allow 4coder's self profiler to gather new profiling information.", 65, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_profile.cpp", 54, 212 },
{ PROC_LINKS(profile_inspect, 0), 0, true, "profile_inspect", 15, "Inspect all currently collected profiling information in 4coder's self profiler.", 80, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_profile_inspect.cpp", 62, 879 },
{ PROC_LINKS(project_command_F1, 0), 2, false, "project_command_F1", 18, "Run the command with index 1", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1071 },
{ PROC_LINKS(project_command_F10, 0), 2, false, "project_command_F10", 19, "Run the command with index 10", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1125 },
{ PROC_LINKS(project_command_F11, 0), 2, false, "project_command_F11", 19, "Run the command with index 11", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1131 },
{ PROC_LINKS(project_command_F12, 0), 2, false, "project_command_F12", 19, "Run the command with index 12", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1137 },
{ PROC_LINKS(project_command_F13, 0), 2, false, "project_command_F13", 19, "Run the command with index 13", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1143 },
{ PROC_LINKS(project_command_F14, 0), 2, false, "project_command_F14", 19, "Run the command with index 14", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1149 },
{ PROC_LINKS(project_command_F15, 0), 2, false, "project_command_F15", 19, "Run the command with index 15", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1155 },
{ PROC_LINKS(project_command_F16, 0), 2, false, "project_command_F16", 19, "Run the command with index 16", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1161 },
{ PROC_LINKS(project_command_F2, 0), 2, false, "project_command_F2", 18, "Run the command with index 2", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1077 },
{ PROC_LINKS(project_command_F3, 0), 2, false, "project_command_F3", 18, "Run the command with index 3", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1083 },
{ PROC_LINKS(project_command_F4, 0), 2, false, "project_command_F4", 18, "Run the command with index 4", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1089 },
{ PROC_LINKS(project_command_F5, 0), 2, false, "project_command_F5", 18, "Run the command with index 5", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1095 },
{ PROC_LINKS(project_command_F6, 0), 2, false, "project_command_F6", 18, "Run the command with index 6", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1101 },
{ PROC_LINKS(project_command_F7, 0), 2, false, "project_command_F7", 18, "Run the command with index 7", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1107 },
{ PROC_LINKS(project_command_F8, 0), 2, false, "project_command_F8", 18, "Run the command with index 8", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1113 },
{ PROC_LINKS(project_command_F9, 0), 2, false, "project_command_F9", 18, "Run the command with index 9", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1119 },
{ PROC_LINKS(project_command_lister, 0), 2, false, "project_command_lister", 22, "Open a lister of all commands in the currently loaded project.", 62, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1023 },
{ PROC_LINKS(project_fkey_command, 0), 2, false, "project_fkey_command", 20, "Run an 'fkey command' configured in a project.4coder file.  Determines the index of the 'fkey command' by which function key or numeric key was pressed to trigger the command.", 175, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 961 },
{ PROC_LINKS(project_go_to_root_directory, 0), 2, false, "project_go_to_root_directory", 28, "Changes 4coder's hot directory to the root directory of the currently loaded project. With no loaded project nothing hapepns.", 125, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 987 },
{ PROC_LINKS(project_reprint, 0), 0, false, "project_reprint", 15, "Prints the current project to the file it was loaded from; prints in the most recent project file version", 105, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1033 },
{ PROC_LINKS(qol_bview_active_to_bottom, 0), 2, false, "qol_bview_active_to_bottom", 26, "[QOL] Sets opens active buffer in bottom view", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 27 },
{ PROC_LINKS(qol_bview_bottom_to_active, 0), 0, false, "qol_bview_bottom_to_active", 26, "[QOL] Opens bottom view buffer in active view", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 35 },
{ PROC_LINKS(qol_bview_close, 0), 2, false, "qol_bview_close", 15, "[QOL] Closes bottom view", 24, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 2 },
{ PROC_LINKS(qol_bview_open, 0), 2, false, "qol_bview_open", 14, "[QOL] Opens bottom view", 23, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 8 },
{ PROC_LINKS(qol_bview_scroll_down, 0), 2, false, "qol_bview_scroll_down", 21, "[QOL] Scolls bottom view down", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 52 },
{ PROC_LINKS(qol_bview_scroll_up, 0), 2, false, "qol_bview_scroll_up", 19, "[QOL] Scrolls bottom view up", 28, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 43 },
{ PROC_LINKS(qol_bview_toggle, 0), 2, false, "qol_bview_toggle", 16, "[QOL] Toggles bottom view open/close", 36, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_bview.cpp", 49, 16 },
{ PROC_LINKS(qol_char_backward, 0), 1, false, "qol_char_backward", 17, "[QOL] Seeks back in current line to the selected char", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 320 },
{ PROC_LINKS(qol_char_forward, 0), 1, false, "qol_char_forward", 16, "[QOL] Seeks forward in current line to the selected char", 56, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 310 },
{ PROC_LINKS(qol_clear_jumps, 0), 2, false, "qol_clear_jumps", 15, "[QOL] Clears any jump highlights", 32, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 33 },
{ PROC_LINKS(qol_column_toggle, 0), 2, false, "qol_column_toggle", 17, "[QOL] Toggles the column for bumping and selects hovered char", 61, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 330 },
{ PROC_LINKS(qol_ctrl_backspace, 0), 1, false, "qol_ctrl_backspace", 18, "[QOL] Standard ctrl-backspace", 29, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 272 },
{ PROC_LINKS(qol_ctrl_backwards, 0), 1, false, "qol_ctrl_backwards", 18, "[QOL] Standard ctrl-left", 24, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 286 },
{ PROC_LINKS(qol_ctrl_delete, 0), 1, false, "qol_ctrl_delete", 15, "[QOL] Standard ctrl-delete", 26, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 265 },
{ PROC_LINKS(qol_ctrl_forwards, 0), 1, false, "qol_ctrl_forwards", 17, "[QOL] Standard ctrl-right", 25, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 279 },
{ PROC_LINKS(qol_explorer, 0), 2, false, "qol_explorer", 12, "[QOL] Opens file explorer in cwd", 32, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 207 },
{ PROC_LINKS(qol_find_divider_down, 0), 0, false, "qol_find_divider_down", 21, "[QOL] Find //- divider below cursor", 35, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 520 },
{ PROC_LINKS(qol_find_divider_up, 0), 0, false, "qol_find_divider_up", 19, "[QOL] Find //- divider above cursor", 35, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 514 },
{ PROC_LINKS(qol_format_all_buffers, 0), 0, false, "qol_format_all_buffers", 22, "[QOL] Auto-indent and remove blank lines for all loaded buffers", 63, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_reformat.cpp", 52, 105 },
{ PROC_LINKS(qol_home, 0), 1, false, "qol_home", 8, "[QOL] Seeks the cursor to the beginning of the visual line", 58, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 39 },
{ PROC_LINKS(qol_jump_down, 0), 0, false, "qol_jump_down", 13, "[QOL] Jump down the view's jump stack", 37, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_jumps.cpp", 49, 108 },
{ PROC_LINKS(qol_jump_to_definition, 0), 2, false, "qol_jump_to_definition", 22, "[QOL] Jump to the definition in the code index matching an identifier at the cursor", 83, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 49 },
{ PROC_LINKS(qol_jump_up, 0), 0, false, "qol_jump_up", 11, "[QOL] Jump back up the view's jump stack", 40, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_jumps.cpp", 49, 125 },
{ PROC_LINKS(qol_kill_rectangle, 0), 0, false, "qol_kill_rectangle", 18, "[QOL] Prompt deletion of text in the cursor/mark rectangle", 58, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 558 },
{ PROC_LINKS(qol_loc, 0), 2, false, "qol_loc", 7, "[QOL] Prints Lines of Code", 26, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 187 },
{ PROC_LINKS(qol_modal_return, 0), 1, false, "qol_modal_return", 16, "[QOL] Either goto_jump_at_cursor or writes newline and completes {} when appropriate", 84, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 403 },
{ PROC_LINKS(qol_move_selection_down, 0), 1, false, "qol_move_selection_down", 23, "[QOL] Move selected lines down 1 line", 37, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 475 },
{ PROC_LINKS(qol_move_selection_up, 0), 1, false, "qol_move_selection_up", 21, "[QOL] Move selected lines up 1 line", 35, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 469 },
{ PROC_LINKS(qol_reformat_current, 0), 0, false, "qol_reformat_current", 20, "[QOL] reformat buffer via code index", 36, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_reformat.cpp", 52, 98 },
{ PROC_LINKS(qol_reload_bindings, 0), 2, false, "qol_reload_bindings", 19, "[QOL] Reloads the bindings.4coder file", 38, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 143 },
{ PROC_LINKS(qol_reload_config, 0), 2, false, "qol_reload_config", 17, "[QOL] Reloads the config.4coder file", 36, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 114 },
{ PROC_LINKS(qol_reload_project, 0), 2, false, "qol_reload_project", 18, "[QOL] Reloads the project.4coder file", 37, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 129 },
{ PROC_LINKS(qol_reopen_all_buffers, 0), 0, false, "qol_reopen_all_buffers", 22, "[QOL] Reloads the project.4coder file", 37, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 160 },
{ PROC_LINKS(qol_reverse_search, 0), 0, false, "qol_reverse_search", 18, "[QOL] I-search up", 17, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_isearch.cpp", 51, 176 },
{ PROC_LINKS(qol_scroll_hovered, 0), 0, false, "qol_scroll_hovered", 18, "[QOL] Scrolls hovered view", 26, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 83 },
{ PROC_LINKS(qol_search, 0), 0, false, "qol_search", 10, "[QOL] I-search down", 19, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_isearch.cpp", 51, 170 },
{ PROC_LINKS(qol_search_identifier, 0), 0, false, "qol_search_identifier", 21, "[QOL] I-search identifier under cursor", 38, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_isearch.cpp", 51, 156 },
{ PROC_LINKS(qol_snippet_begin, 0), 0, false, "qol_snippet_begin", 17, "[QOL] Opens *qol_snippet* empty buffer", 38, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_snippets.cpp", 52, 13 },
{ PROC_LINKS(qol_snippet_end, 0), 0, false, "qol_snippet_end", 15, "[QOL] ", 6, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_snippets.cpp", 52, 23 },
{ PROC_LINKS(qol_startup, 0), 0, false, "qol_startup", 11, "QOL command for responding to a startup event", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_hooks.cpp", 49, 2 },
{ PROC_LINKS(qol_try_exit, 0), 2, false, "qol_try_exit", 12, "[QOL] response to a try-exit event", 34, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 595 },
{ PROC_LINKS(qol_view_input_handler, 0), 0, false, "qol_view_input_handler", 22, "QOL Input consumption loop for views", 36, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_hooks.cpp", 49, 256 },
{ PROC_LINKS(qol_write_space, 0), 1, false, "qol_write_space", 15, "[QOL] Writes as many spaces needed for bumping to column", 56, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 357 },
{ PROC_LINKS(qol_write_text_and_auto_indent, 0), 1, false, "qol_write_text_and_auto_indent", 30, "[QOL] Inserts whatever text was used to trigger this command.", 61, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 394 },
{ PROC_LINKS(qol_write_text_input, 0), 1, false, "qol_write_text_input", 20, "[QOL] Inserts whatever text was used to trigger this command.", 61, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 385 },
{ PROC_LINKS(query_replace, 0), 0, false, "query_replace", 13, "Queries the user for two strings, and incrementally replaces every occurence of the first string with the second string.", 120, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1290 },
{ PROC_LINKS(query_replace_identifier, 0), 0, false, "query_replace_identifier", 24, "Queries the user for a string, and incrementally replace every occurence of the word or token found at the cursor with the specified string.", 140, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1311 },
{ PROC_LINKS(query_replace_selection, 0), 0, false, "query_replace_selection", 23, "Queries the user for a string, and incrementally replace every occurence of the string found in the selected range with the specified string.", 141, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1327 },
{ PROC_LINKS(quick_swap_buffer, 0), 0, false, "quick_swap_buffer", 17, "Change to the most recently used buffer in this view - or to the top of the buffer stack if the most recent doesn't exist anymore", 129, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1714 },
{ PROC_LINKS(redo, 0), 0, false, "redo", 4, "Advances forwards through the undo history of the current buffer.", 65, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1896 },
{ PROC_LINKS(redo_all_buffers, 0), 0, false, "redo_all_buffers", 16, "Advances forward through the undo history in the buffer containing the most recent regular edit.", 96, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1993 },
{ PROC_LINKS(rename_file_query, 0), 0, false, "rename_file_query", 17, "Queries the user for a new name and renames the file of the current buffer, altering the buffer's name too.", 107, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1468 },
{ PROC_LINKS(reopen, 0), 0, false, "reopen", 6, "Reopen the current buffer from the hard drive.", 46, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1752 },
{ PROC_LINKS(replace_in_all_buffers, 0), 0, false, "replace_in_all_buffers", 22, "Queries the user for a needle and string. Replaces all occurences of needle with string in all editable buffers.", 112, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1200 },
{ PROC_LINKS(replace_in_buffer, 0), 0, false, "replace_in_buffer", 17, "Queries the user for a needle and string. Replaces all occurences of needle with string in the active buffer.", 109, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1191 },
{ PROC_LINKS(replace_in_range, 0), 0, false, "replace_in_range", 16, "Queries the user for a needle and string. Replaces all occurences of needle with string in the range between cursor and the mark in the active buffer.", 150, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1182 },
{ PROC_LINKS(reverse_search, 0), 0, false, "reverse_search", 14, "Begins an incremental search up through the current buffer for a user specified string.", 87, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1123 },
{ PROC_LINKS(reverse_search_identifier, 0), 0, false, "reverse_search_identifier", 25, "Begins an incremental search up through the current buffer for the word or token under the cursor.", 98, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1135 },
{ PROC_LINKS(save, 0), 2, false, "save", 4, "Saves the current buffer.", 25, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1742 },
{ PROC_LINKS(save_all_dirty_buffers, 0), 2, false, "save_all_dirty_buffers", 22, "Saves all buffers marked dirty (showing the '*' indicator).", 59, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 455 },
{ PROC_LINKS(save_to_query, 0), 0, false, "save_to_query", 13, "Queries the user for a file name and saves the contents of the current buffer, altering the buffer's name too.", 110, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1435 },
{ PROC_LINKS(search, 0), 0, false, "search", 6, "Begins an incremental search down through the current buffer for a user specified string.", 89, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1117 },
{ PROC_LINKS(search_identifier, 0), 0, false, "search_identifier", 17, "Begins an incremental search down through the current buffer for the word or token under the cursor.", 100, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1129 },
{ PROC_LINKS(seek_beginning_of_line, 0), 1, false, "seek_beginning_of_line", 22, "Seeks the cursor to the beginning of the visual line.", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_helper.cpp", 53, 2259 },
{ PROC_LINKS(seek_beginning_of_textual_line, 0), 1, false, "seek_beginning_of_textual_line", 30, "Seeks the cursor to the beginning of the line across all text.", 62, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_helper.cpp", 53, 2247 },
{ PROC_LINKS(seek_end_of_line, 0), 1, false, "seek_end_of_line", 16, "Seeks the cursor to the end of the visual line.", 47, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_helper.cpp", 53, 2265 },
{ PROC_LINKS(seek_end_of_textual_line, 0), 1, false, "seek_end_of_textual_line", 24, "Seeks the cursor to the end of the line across all text.", 56, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_helper.cpp", 53, 2253 },
{ PROC_LINKS(select_all, 0), 0, false, "select_all", 10, "Puts the cursor at the top of the file, and the mark at the bottom of the file.", 79, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 552 },
{ PROC_LINKS(select_next_scope_absolute, 0), 0, false, "select_next_scope_absolute", 26, "Finds the first scope started by '{' after the cursor and puts the cursor and mark on the '{' and '}'.", 102, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 57 },
{ PROC_LINKS(select_next_scope_after_current, 0), 0, false, "select_next_scope_after_current", 31, "If a scope is selected, find first scope that starts after the selected scope. Otherwise find the first scope that starts after the cursor.", 139, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 66 },
{ PROC_LINKS(select_prev_scope_absolute, 0), 0, false, "select_prev_scope_absolute", 26, "Finds the first scope started by '{' before the cursor and puts the cursor and mark on the '{' and '}'.", 103, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 82 },
{ PROC_LINKS(select_prev_top_most_scope, 0), 0, false, "select_prev_top_most_scope", 26, "Finds the first scope that starts before the cursor, then finds the top most scope that contains that scope.", 108, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 99 },
{ PROC_LINKS(select_surrounding_scope, 0), 0, false, "select_surrounding_scope", 24, "Finds the scope enclosed by '{' '}' surrounding the cursor and puts the cursor and mark on the '{' and '}'.", 107, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 27 },
{ PROC_LINKS(select_surrounding_scope_maximal, 0), 0, false, "select_surrounding_scope_maximal", 32, "Selects the top-most scope that surrounds the cursor.", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_scope_commands.cpp", 61, 39 },
{ PROC_LINKS(set_eol_mode_from_contents, 0), 2, false, "set_eol_mode_from_contents", 26, "Sets the buffer's line ending mode to match the contents of the buffer.", 71, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_eol.cpp", 50, 125 },
{ PROC_LINKS(set_eol_mode_to_binary, 0), 2, false, "set_eol_mode_to_binary", 22, "Puts the buffer in bin line ending mode.", 40, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_eol.cpp", 50, 112 },
{ PROC_LINKS(set_eol_mode_to_crlf, 0), 2, false, "set_eol_mode_to_crlf", 20, "Puts the buffer in crlf line ending mode.", 41, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_eol.cpp", 50, 86 },
{ PROC_LINKS(set_eol_mode_to_lf, 0), 2, false, "set_eol_mode_to_lf", 18, "Puts the buffer in lf line ending mode.", 39, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_eol.cpp", 50, 99 },
{ PROC_LINKS(set_face_size, 0), 2, false, "set_face_size", 13, "Set face size of the face used by the current buffer.", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 737 },
{ PROC_LINKS(set_face_size_this_buffer, 0), 2, false, "set_face_size_this_buffer", 25, "Set face size of the face used by the current buffer; if any other buffers are using the same face a new face is created so that only this buffer is effected", 157, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 779 },
{ PROC_LINKS(set_mark, 0), 1, false, "set_mark", 8, "Sets the mark to the current position of the cursor.", 52, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 115 },
{ PROC_LINKS(set_mode_to_notepad_like, 0), 2, false, "set_mode_to_notepad_like", 24, "Sets the edit mode to Notepad like.", 35, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 500 },
{ PROC_LINKS(set_mode_to_original, 0), 2, false, "set_mode_to_original", 20, "Sets the edit mode to 4coder original.", 38, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 494 },
{ PROC_LINKS(setup_build_bat, 0), 0, false, "setup_build_bat", 15, "Queries the user for several configuration options and initializes a new build batch script.", 92, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1005 },
{ PROC_LINKS(setup_build_bat_and_sh, 0), 0, false, "setup_build_bat_and_sh", 22, "Queries the user for several configuration options and initializes a new build batch script.", 92, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1017 },
{ PROC_LINKS(setup_build_sh, 0), 0, false, "setup_build_sh", 14, "Queries the user for several configuration options and initializes a new build shell script.", 92, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 1011 },
{ PROC_LINKS(setup_new_project, 0), 0, false, "setup_new_project", 17, "Queries the user for several configuration options and initializes a new 4coder project with build scripts for every OS.", 120, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_project_commands.cpp", 63, 998 },
{ PROC_LINKS(show_filebar, 0), 2, false, "show_filebar", 12, "Sets the current view to show it's filebar.", 43, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 708 },
{ PROC_LINKS(show_scrollbar, 0), 2, false, "show_scrollbar", 14, "Sets the current view to show it's scrollbar.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 694 },
{ PROC_LINKS(show_the_log_graph, 0), 0, true, "show_the_log_graph", 18, "Parses *log* and displays the 'log graph' UI", 44, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_log_parser.cpp", 57, 991 },
{ PROC_LINKS(snipe_backward_whitespace_or_token_boundary, 0), 1, false, "snipe_backward_whitespace_or_token_boundary", 43, "Delete a single, whole token on or to the left of the cursor and post it to the clipboard.", 90, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 181 },
{ PROC_LINKS(snipe_forward_whitespace_or_token_boundary, 0), 1, false, "snipe_forward_whitespace_or_token_boundary", 42, "Delete a single, whole token on or to the right of the cursor and post it to the clipboard.", 91, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 189 },
{ PROC_LINKS(snippet_lister, 0), 0, true, "snippet_lister", 14, "Opens a snippet lister for inserting whole pre-written snippets of text.", 72, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 286 },
{ PROC_LINKS(string_repeat, 0), 0, false, "string_repeat", 13, "Example of query_user_string and query_user_number", 50, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_examples.cpp", 55, 179 },
{ PROC_LINKS(suppress_mouse, 0), 2, false, "suppress_mouse", 14, "Hides the mouse and causes all mosue input (clicks, position, wheel) to be ignored.", 83, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 476 },
{ PROC_LINKS(swap_panels, 0), 2, false, "swap_panels", 11, "Swaps the active panel with it's sibling.", 41, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1692 },
{ PROC_LINKS(theme_lister, 0), 0, true, "theme_lister", 12, "Opens an interactive list of all registered themes.", 51, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_lists.cpp", 52, 780 },
{ PROC_LINKS(to_lowercase, 0), 1, false, "to_lowercase", 12, "Converts all ascii text in the range between the cursor and the mark to lowercase.", 82, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 577 },
{ PROC_LINKS(to_uppercase, 0), 1, false, "to_uppercase", 12, "Converts all ascii text in the range between the cursor and the mark to uppercase.", 82, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 565 },
{ PROC_LINKS(toggle_code_peek, 0), 2, false, "toggle_code_peek", 16, "[QOL] Toggles the visibility of the code peek", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 20 },
{ PROC_LINKS(toggle_filebar, 0), 2, false, "toggle_filebar", 14, "Toggles the visibility status of the current view's filebar.", 60, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 722 },
{ PROC_LINKS(toggle_fps_meter, 0), 2, false, "toggle_fps_meter", 16, "Toggles the visibility of the FPS performance meter", 51, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 731 },
{ PROC_LINKS(toggle_fullscreen, 0), 2, false, "toggle_fullscreen", 17, "Toggle fullscreen mode on or off.  The change(s) do not take effect until the next frame.", 89, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 530 },
{ PROC_LINKS(toggle_function_tooltip, 0), 2, false, "toggle_function_tooltip", 23, "[QOL] Toggles the visibility of the function tooltips", 53, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 14 },
{ PROC_LINKS(toggle_highlight_enclosing_scopes, 0), 2, false, "toggle_highlight_enclosing_scopes", 33, "In code files scopes surrounding the cursor are highlighted with distinguishing colors.", 87, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 514 },
{ PROC_LINKS(toggle_highlight_line_at_cursor, 0), 2, false, "toggle_highlight_line_at_cursor", 31, "Toggles the line highlight at the cursor.", 41, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 506 },
{ PROC_LINKS(toggle_line_numbers, 0), 2, false, "toggle_line_numbers", 19, "Toggles the left margin line numbers.", 37, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 836 },
{ PROC_LINKS(toggle_line_wrap, 0), 2, false, "toggle_line_wrap", 16, "Toggles the line wrap setting on this buffer.", 45, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 844 },
{ PROC_LINKS(toggle_mouse, 0), 2, false, "toggle_mouse", 12, "Toggles the mouse suppression mode, see suppress_mouse and allow_mouse.", 71, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 488 },
{ PROC_LINKS(toggle_paren_matching_helper, 0), 2, false, "toggle_paren_matching_helper", 28, "In code files matching parentheses pairs are colored with distinguishing colors.", 80, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 522 },
{ PROC_LINKS(toggle_pproc_anchor, 0), 2, false, "toggle_pproc_anchor", 19, "[QOL] Toggles whether pproc tokens are anchored left", 52, "E:\\dev\\4coder_ziv\\4coder_qol\\4coder_qol_commands.cpp", 52, 26 },
{ PROC_LINKS(toggle_show_whitespace, 0), 2, false, "toggle_show_whitespace", 22, "Toggles the current buffer's whitespace visibility status.", 58, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 827 },
{ PROC_LINKS(toggle_virtual_whitespace, 0), 2, false, "toggle_virtual_whitespace", 25, "Toggles virtual whitespace for all files.", 41, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_code_index.cpp", 57, 1452 },
{ PROC_LINKS(tutorial_maximize, 0), 2, false, "tutorial_maximize", 17, "Expand the tutorial window", 26, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_tutorial.cpp", 55, 21 },
{ PROC_LINKS(tutorial_minimize, 0), 2, false, "tutorial_minimize", 17, "Shrink the tutorial window", 26, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_tutorial.cpp", 55, 35 },
{ PROC_LINKS(uncomment_line, 0), 1, false, "uncomment_line", 14, "If present, delete '//' at the beginning of the line after leading whitespace.", 78, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 137 },
{ PROC_LINKS(undo, 0), 0, false, "undo", 4, "Advances backwards through the undo history of the current buffer.", 66, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1844 },
{ PROC_LINKS(undo_all_buffers, 0), 0, false, "undo_all_buffers", 16, "Advances backward through the undo history in the buffer containing the most recent regular edit.", 97, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1922 },
{ PROC_LINKS(view_buffer_other_panel, 0), 0, false, "view_buffer_other_panel", 23, "Set the other non-active panel to view the buffer that the active panel views, and switch to that panel.", 104, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 1680 },
{ PROC_LINKS(view_jump_list_with_lister, 0), 0, false, "view_jump_list_with_lister", 26, "When executed on a buffer with jumps, creates a persistent lister for all the jumps", 83, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_jump_lister.cpp", 58, 59 },
{ PROC_LINKS(vsplit, 0), 0, false, "vsplit", 6, "Create a new panel by vertically splitting the active panel.", 60, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_default_framework.cpp", 64, 380 },
{ PROC_LINKS(word_complete, 0), 0, false, "word_complete", 13, "Iteratively tries completing the word to the left of the cursor with other words in open buffers that have the same prefix string.", 130, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 452 },
{ PROC_LINKS(word_complete_drop_down, 0), 0, false, "word_complete_drop_down", 23, "Word complete with drop down menu.", 34, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 726 },
{ PROC_LINKS(word_complete_prev, 0), 0, false, "word_complete_prev", 18, "Reverse iterates word_complete list", 35, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_search.cpp", 53, 498 },
{ PROC_LINKS(write_block, 0), 1, false, "write_block", 11, "At the cursor, insert a block comment.", 38, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 94 },
{ PROC_LINKS(write_hack, 0), 1, false, "write_hack", 10, "At the cursor, insert a '// HACK' comment, includes user name if it was specified in config.4coder.", 99, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 82 },
{ PROC_LINKS(write_note, 0), 1, false, "write_note", 10, "At the cursor, insert a '// NOTE' comment, includes user name if it was specified in config.4coder.", 99, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 88 },
{ PROC_LINKS(write_space, 0), 1, false, "write_space", 11, "Inserts a space.", 16, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 67 },
{ PROC_LINKS(write_text_and_auto_indent, 0), 1, false, "write_text_and_auto_indent", 26, "Inserts text and auto-indents the line on which the cursor sits if any of the text contains 'layout punctuation' such as ;:{}()[]# and new lines.", 145, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_auto_indent.cpp", 58, 440 },
{ PROC_LINKS(write_text_input, 0), 0, false, "write_text_input", 16, "Inserts whatever text was used to trigger this command.", 55, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 59 },
{ PROC_LINKS(write_todo, 0), 1, false, "write_todo", 10, "At the cursor, insert a '// TODO' comment, includes user name if it was specified in config.4coder.", 99, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 76 },
{ PROC_LINKS(write_underscore, 0), 1, false, "write_underscore", 16, "Inserts an underscore.", 22, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_base_commands.cpp", 60, 73 },
{ PROC_LINKS(write_zero_struct, 0), 1, false, "write_zero_struct", 17, "At the cursor, insert a ' = {};'.", 33, "E:\\dev\\4coder_ziv\\4coder_qol\\custom\\4coder_combined_write_commands.cpp", 70, 100 },
{ PROC_LINKS(zk_go_to_definition_other_panel, 0), 2, false, "zk_go_to_definition_other_panel", 31, "[ZK] Jump to the definition of identifier at the cursor other panel", 67, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_commands.cpp", 50, 341 },
{ PROC_LINKS(zk_go_to_definition_same_panel, 0), 2, false, "zk_go_to_definition_same_panel", 30, "[ZK] Jump to the definition of identifier at the cursor", 55, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_commands.cpp", 50, 335 },
{ PROC_LINKS(zk_jump_to_definition_lister, 0), 0, true, "zk_jump_to_definition_lister", 28, "List all definitions in the code index and jump to one chosen by the user.", 74, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_commands.cpp", 50, 40 },
{ PROC_LINKS(zk_kill_rectangle, 0), 0, false, "zk_kill_rectangle", 17, "[QOL] Prompt deletion of text in the cursor/mark rectangle", 58, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_commands.cpp", 50, 411 },
{ PROC_LINKS(zk_list_all_locations, 0), 0, false, "zk_list_all_locations", 21, "[zk] Queries the user for a string and lists all exact case-insensitive matches found in all open buffers.", 106, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_search.cpp", 48, 280 },
{ PROC_LINKS(zk_mouse_column_toggle, 0), 2, false, "zk_mouse_column_toggle", 22, "[ZK] Toggles the column for bumping and selects hovered char at mouse position", 78, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_commands.cpp", 50, 350 },
{ PROC_LINKS(zk_reverse_search, 0), 0, false, "zk_reverse_search", 17, "[ZK] I-search up", 16, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_search.cpp", 48, 1195 },
{ PROC_LINKS(zk_search, 0), 0, false, "zk_search", 9, "[ZK] I-search down", 18, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_search.cpp", 48, 1189 },
{ PROC_LINKS(zk_startup, 0), 0, false, "zk_startup", 10, "ZK command for responding to a startup event", 44, "E:\\dev\\4coder_ziv\\4coder_zk\\4coder_zk_hooks.cpp", 47, 2 },
};

static i32 fcoder_metacmd_ID_MC_add_at_pos = 0;
static i32 fcoder_metacmd_ID_MC_begin_multi = 1;
static i32 fcoder_metacmd_ID_MC_begin_multi_block = 2;
static i32 fcoder_metacmd_ID_MC_del_at_pos = 3;
static i32 fcoder_metacmd_ID_MC_down_trail = 4;
static i32 fcoder_metacmd_ID_MC_end_multi = 5;
static i32 fcoder_metacmd_ID_MC_error_fade = 6;
static i32 fcoder_metacmd_ID_MC_up_trail = 7;
static i32 fcoder_metacmd_ID_TAB_close = 8;
static i32 fcoder_metacmd_ID_TAB_new = 9;
static i32 fcoder_metacmd_ID_TAB_next = 10;
static i32 fcoder_metacmd_ID_TAB_prev = 11;
static i32 fcoder_metacmd_ID_allow_mouse = 12;
static i32 fcoder_metacmd_ID_auto_indent_line_at_cursor = 13;
static i32 fcoder_metacmd_ID_auto_indent_range = 14;
static i32 fcoder_metacmd_ID_auto_indent_whole_file = 15;
static i32 fcoder_metacmd_ID_backspace_alpha_numeric_boundary = 16;
static i32 fcoder_metacmd_ID_backspace_char = 17;
static i32 fcoder_metacmd_ID_basic_change_active_panel = 18;
static i32 fcoder_metacmd_ID_begin_clipboard_collection_mode = 19;
static i32 fcoder_metacmd_ID_begin_tutorial = 20;
static i32 fcoder_metacmd_ID_build_in_build_panel = 21;
static i32 fcoder_metacmd_ID_build_search = 22;
static i32 fcoder_metacmd_ID_casey_delete_to_end_of_line = 23;
static i32 fcoder_metacmd_ID_center_view = 24;
static i32 fcoder_metacmd_ID_change_active_panel = 25;
static i32 fcoder_metacmd_ID_change_active_panel_backwards = 26;
static i32 fcoder_metacmd_ID_change_to_build_panel = 27;
static i32 fcoder_metacmd_ID_clean_all_lines = 28;
static i32 fcoder_metacmd_ID_clean_trailing_whitespace = 29;
static i32 fcoder_metacmd_ID_clear_all_themes = 30;
static i32 fcoder_metacmd_ID_clear_clipboard = 31;
static i32 fcoder_metacmd_ID_click_set_cursor = 32;
static i32 fcoder_metacmd_ID_click_set_cursor_and_mark = 33;
static i32 fcoder_metacmd_ID_click_set_cursor_if_lbutton = 34;
static i32 fcoder_metacmd_ID_click_set_mark = 35;
static i32 fcoder_metacmd_ID_clipboard_record_clip = 36;
static i32 fcoder_metacmd_ID_close_all_buffers = 37;
static i32 fcoder_metacmd_ID_close_all_code = 38;
static i32 fcoder_metacmd_ID_close_build_panel = 39;
static i32 fcoder_metacmd_ID_close_panel = 40;
static i32 fcoder_metacmd_ID_command_documentation = 41;
static i32 fcoder_metacmd_ID_command_lister = 42;
static i32 fcoder_metacmd_ID_comment_line = 43;
static i32 fcoder_metacmd_ID_comment_line_toggle = 44;
static i32 fcoder_metacmd_ID_copy = 45;
static i32 fcoder_metacmd_ID_cursor_mark_swap = 46;
static i32 fcoder_metacmd_ID_custom_api_documentation = 47;
static i32 fcoder_metacmd_ID_cut = 48;
static i32 fcoder_metacmd_ID_decrease_face_size = 49;
static i32 fcoder_metacmd_ID_default_file_externally_modified = 50;
static i32 fcoder_metacmd_ID_default_startup = 51;
static i32 fcoder_metacmd_ID_default_try_exit = 52;
static i32 fcoder_metacmd_ID_default_view_input_handler = 53;
static i32 fcoder_metacmd_ID_delete_alpha_numeric_boundary = 54;
static i32 fcoder_metacmd_ID_delete_char = 55;
static i32 fcoder_metacmd_ID_delete_current_scope = 56;
static i32 fcoder_metacmd_ID_delete_file_query = 57;
static i32 fcoder_metacmd_ID_delete_line = 58;
static i32 fcoder_metacmd_ID_delete_range = 59;
static i32 fcoder_metacmd_ID_display_key_codes = 60;
static i32 fcoder_metacmd_ID_display_text_input = 61;
static i32 fcoder_metacmd_ID_double_backspace = 62;
static i32 fcoder_metacmd_ID_duplicate_line = 63;
static i32 fcoder_metacmd_ID_execute_any_cli = 64;
static i32 fcoder_metacmd_ID_execute_previous_cli = 65;
static i32 fcoder_metacmd_ID_exit_4coder = 66;
static i32 fcoder_metacmd_ID_go_to_user_directory = 67;
static i32 fcoder_metacmd_ID_goto_beginning_of_file = 68;
static i32 fcoder_metacmd_ID_goto_end_of_file = 69;
static i32 fcoder_metacmd_ID_goto_first_jump = 70;
static i32 fcoder_metacmd_ID_goto_first_jump_same_panel_sticky = 71;
static i32 fcoder_metacmd_ID_goto_jump_at_cursor = 72;
static i32 fcoder_metacmd_ID_goto_jump_at_cursor_same_panel = 73;
static i32 fcoder_metacmd_ID_goto_line = 74;
static i32 fcoder_metacmd_ID_goto_next_jump = 75;
static i32 fcoder_metacmd_ID_goto_next_jump_no_skips = 76;
static i32 fcoder_metacmd_ID_goto_prev_jump = 77;
static i32 fcoder_metacmd_ID_goto_prev_jump_no_skips = 78;
static i32 fcoder_metacmd_ID_hide_filebar = 79;
static i32 fcoder_metacmd_ID_hide_scrollbar = 80;
static i32 fcoder_metacmd_ID_hit_sfx = 81;
static i32 fcoder_metacmd_ID_hsplit = 82;
static i32 fcoder_metacmd_ID_if0_off = 83;
static i32 fcoder_metacmd_ID_if_read_only_goto_position = 84;
static i32 fcoder_metacmd_ID_if_read_only_goto_position_same_panel = 85;
static i32 fcoder_metacmd_ID_increase_face_size = 86;
static i32 fcoder_metacmd_ID_interactive_kill_buffer = 87;
static i32 fcoder_metacmd_ID_interactive_new = 88;
static i32 fcoder_metacmd_ID_interactive_open = 89;
static i32 fcoder_metacmd_ID_interactive_open_or_new = 90;
static i32 fcoder_metacmd_ID_interactive_switch_buffer = 91;
static i32 fcoder_metacmd_ID_jump_to_definition = 92;
static i32 fcoder_metacmd_ID_jump_to_definition_at_cursor = 93;
static i32 fcoder_metacmd_ID_jump_to_last_point = 94;
static i32 fcoder_metacmd_ID_keyboard_macro_finish_recording = 95;
static i32 fcoder_metacmd_ID_keyboard_macro_replay = 96;
static i32 fcoder_metacmd_ID_keyboard_macro_start_recording = 97;
static i32 fcoder_metacmd_ID_kill_buffer = 98;
static i32 fcoder_metacmd_ID_kill_tutorial = 99;
static i32 fcoder_metacmd_ID_left_adjust_view = 100;
static i32 fcoder_metacmd_ID_list_all_functions_all_buffers = 101;
static i32 fcoder_metacmd_ID_list_all_functions_all_buffers_lister = 102;
static i32 fcoder_metacmd_ID_list_all_functions_current_buffer = 103;
static i32 fcoder_metacmd_ID_list_all_functions_current_buffer_lister = 104;
static i32 fcoder_metacmd_ID_list_all_locations = 105;
static i32 fcoder_metacmd_ID_list_all_locations_case_insensitive = 106;
static i32 fcoder_metacmd_ID_list_all_locations_of_identifier = 107;
static i32 fcoder_metacmd_ID_list_all_locations_of_identifier_case_insensitive = 108;
static i32 fcoder_metacmd_ID_list_all_locations_of_selection = 109;
static i32 fcoder_metacmd_ID_list_all_locations_of_selection_case_insensitive = 110;
static i32 fcoder_metacmd_ID_list_all_locations_of_type_definition = 111;
static i32 fcoder_metacmd_ID_list_all_locations_of_type_definition_of_identifier = 112;
static i32 fcoder_metacmd_ID_list_all_substring_locations = 113;
static i32 fcoder_metacmd_ID_list_all_substring_locations_case_insensitive = 114;
static i32 fcoder_metacmd_ID_load_project = 115;
static i32 fcoder_metacmd_ID_load_theme_current_buffer = 116;
static i32 fcoder_metacmd_ID_load_themes_default_folder = 117;
static i32 fcoder_metacmd_ID_load_themes_hot_directory = 118;
static i32 fcoder_metacmd_ID_loco_jump_between_yeet = 119;
static i32 fcoder_metacmd_ID_loco_load_yeet_snapshot_1 = 120;
static i32 fcoder_metacmd_ID_loco_load_yeet_snapshot_2 = 121;
static i32 fcoder_metacmd_ID_loco_load_yeet_snapshot_3 = 122;
static i32 fcoder_metacmd_ID_loco_save_yeet_snapshot_1 = 123;
static i32 fcoder_metacmd_ID_loco_save_yeet_snapshot_2 = 124;
static i32 fcoder_metacmd_ID_loco_save_yeet_snapshot_3 = 125;
static i32 fcoder_metacmd_ID_loco_yeet_clear = 126;
static i32 fcoder_metacmd_ID_loco_yeet_remove_marker_pair = 127;
static i32 fcoder_metacmd_ID_loco_yeet_reset_all = 128;
static i32 fcoder_metacmd_ID_loco_yeet_selected_range_or_jump = 129;
static i32 fcoder_metacmd_ID_loco_yeet_surrounding_function = 130;
static i32 fcoder_metacmd_ID_loco_yeet_tag = 131;
static i32 fcoder_metacmd_ID_make_directory_query = 132;
static i32 fcoder_metacmd_ID_miblo_decrement_basic = 133;
static i32 fcoder_metacmd_ID_miblo_decrement_time_stamp = 134;
static i32 fcoder_metacmd_ID_miblo_decrement_time_stamp_minute = 135;
static i32 fcoder_metacmd_ID_miblo_increment_basic = 136;
static i32 fcoder_metacmd_ID_miblo_increment_time_stamp = 137;
static i32 fcoder_metacmd_ID_miblo_increment_time_stamp_minute = 138;
static i32 fcoder_metacmd_ID_mouse_wheel_change_face_size = 139;
static i32 fcoder_metacmd_ID_mouse_wheel_scroll = 140;
static i32 fcoder_metacmd_ID_move_down = 141;
static i32 fcoder_metacmd_ID_move_down_10 = 142;
static i32 fcoder_metacmd_ID_move_down_textual = 143;
static i32 fcoder_metacmd_ID_move_down_to_blank_line = 144;
static i32 fcoder_metacmd_ID_move_down_to_blank_line_end = 145;
static i32 fcoder_metacmd_ID_move_down_to_blank_line_skip_whitespace = 146;
static i32 fcoder_metacmd_ID_move_left = 147;
static i32 fcoder_metacmd_ID_move_left_alpha_numeric_boundary = 148;
static i32 fcoder_metacmd_ID_move_left_alpha_numeric_or_camel_boundary = 149;
static i32 fcoder_metacmd_ID_move_left_token_boundary = 150;
static i32 fcoder_metacmd_ID_move_left_whitespace_boundary = 151;
static i32 fcoder_metacmd_ID_move_left_whitespace_or_token_boundary = 152;
static i32 fcoder_metacmd_ID_move_line_down = 153;
static i32 fcoder_metacmd_ID_move_line_up = 154;
static i32 fcoder_metacmd_ID_move_right = 155;
static i32 fcoder_metacmd_ID_move_right_alpha_numeric_boundary = 156;
static i32 fcoder_metacmd_ID_move_right_alpha_numeric_or_camel_boundary = 157;
static i32 fcoder_metacmd_ID_move_right_token_boundary = 158;
static i32 fcoder_metacmd_ID_move_right_whitespace_boundary = 159;
static i32 fcoder_metacmd_ID_move_right_whitespace_or_token_boundary = 160;
static i32 fcoder_metacmd_ID_move_up = 161;
static i32 fcoder_metacmd_ID_move_up_10 = 162;
static i32 fcoder_metacmd_ID_move_up_to_blank_line = 163;
static i32 fcoder_metacmd_ID_move_up_to_blank_line_end = 164;
static i32 fcoder_metacmd_ID_move_up_to_blank_line_skip_whitespace = 165;
static i32 fcoder_metacmd_ID_multi_paste = 166;
static i32 fcoder_metacmd_ID_multi_paste_interactive = 167;
static i32 fcoder_metacmd_ID_multi_paste_interactive_quick = 168;
static i32 fcoder_metacmd_ID_music_start = 169;
static i32 fcoder_metacmd_ID_music_stop = 170;
static i32 fcoder_metacmd_ID_open_all_code = 171;
static i32 fcoder_metacmd_ID_open_all_code_recursive = 172;
static i32 fcoder_metacmd_ID_open_file_in_quotes = 173;
static i32 fcoder_metacmd_ID_open_in_other = 174;
static i32 fcoder_metacmd_ID_open_long_braces = 175;
static i32 fcoder_metacmd_ID_open_long_braces_break = 176;
static i32 fcoder_metacmd_ID_open_long_braces_semicolon = 177;
static i32 fcoder_metacmd_ID_open_matching_file_cpp = 178;
static i32 fcoder_metacmd_ID_open_panel_hsplit = 179;
static i32 fcoder_metacmd_ID_open_panel_vsplit = 180;
static i32 fcoder_metacmd_ID_page_down = 181;
static i32 fcoder_metacmd_ID_page_up = 182;
static i32 fcoder_metacmd_ID_paste = 183;
static i32 fcoder_metacmd_ID_paste_and_indent = 184;
static i32 fcoder_metacmd_ID_paste_next = 185;
static i32 fcoder_metacmd_ID_paste_next_and_indent = 186;
static i32 fcoder_metacmd_ID_place_in_scope = 187;
static i32 fcoder_metacmd_ID_play_with_a_counter = 188;
static i32 fcoder_metacmd_ID_profile_clear = 189;
static i32 fcoder_metacmd_ID_profile_disable = 190;
static i32 fcoder_metacmd_ID_profile_enable = 191;
static i32 fcoder_metacmd_ID_profile_inspect = 192;
static i32 fcoder_metacmd_ID_project_command_F1 = 193;
static i32 fcoder_metacmd_ID_project_command_F10 = 194;
static i32 fcoder_metacmd_ID_project_command_F11 = 195;
static i32 fcoder_metacmd_ID_project_command_F12 = 196;
static i32 fcoder_metacmd_ID_project_command_F13 = 197;
static i32 fcoder_metacmd_ID_project_command_F14 = 198;
static i32 fcoder_metacmd_ID_project_command_F15 = 199;
static i32 fcoder_metacmd_ID_project_command_F16 = 200;
static i32 fcoder_metacmd_ID_project_command_F2 = 201;
static i32 fcoder_metacmd_ID_project_command_F3 = 202;
static i32 fcoder_metacmd_ID_project_command_F4 = 203;
static i32 fcoder_metacmd_ID_project_command_F5 = 204;
static i32 fcoder_metacmd_ID_project_command_F6 = 205;
static i32 fcoder_metacmd_ID_project_command_F7 = 206;
static i32 fcoder_metacmd_ID_project_command_F8 = 207;
static i32 fcoder_metacmd_ID_project_command_F9 = 208;
static i32 fcoder_metacmd_ID_project_command_lister = 209;
static i32 fcoder_metacmd_ID_project_fkey_command = 210;
static i32 fcoder_metacmd_ID_project_go_to_root_directory = 211;
static i32 fcoder_metacmd_ID_project_reprint = 212;
static i32 fcoder_metacmd_ID_qol_bview_active_to_bottom = 213;
static i32 fcoder_metacmd_ID_qol_bview_bottom_to_active = 214;
static i32 fcoder_metacmd_ID_qol_bview_close = 215;
static i32 fcoder_metacmd_ID_qol_bview_open = 216;
static i32 fcoder_metacmd_ID_qol_bview_scroll_down = 217;
static i32 fcoder_metacmd_ID_qol_bview_scroll_up = 218;
static i32 fcoder_metacmd_ID_qol_bview_toggle = 219;
static i32 fcoder_metacmd_ID_qol_char_backward = 220;
static i32 fcoder_metacmd_ID_qol_char_forward = 221;
static i32 fcoder_metacmd_ID_qol_clear_jumps = 222;
static i32 fcoder_metacmd_ID_qol_column_toggle = 223;
static i32 fcoder_metacmd_ID_qol_ctrl_backspace = 224;
static i32 fcoder_metacmd_ID_qol_ctrl_backwards = 225;
static i32 fcoder_metacmd_ID_qol_ctrl_delete = 226;
static i32 fcoder_metacmd_ID_qol_ctrl_forwards = 227;
static i32 fcoder_metacmd_ID_qol_explorer = 228;
static i32 fcoder_metacmd_ID_qol_find_divider_down = 229;
static i32 fcoder_metacmd_ID_qol_find_divider_up = 230;
static i32 fcoder_metacmd_ID_qol_format_all_buffers = 231;
static i32 fcoder_metacmd_ID_qol_home = 232;
static i32 fcoder_metacmd_ID_qol_jump_down = 233;
static i32 fcoder_metacmd_ID_qol_jump_to_definition = 234;
static i32 fcoder_metacmd_ID_qol_jump_up = 235;
static i32 fcoder_metacmd_ID_qol_kill_rectangle = 236;
static i32 fcoder_metacmd_ID_qol_loc = 237;
static i32 fcoder_metacmd_ID_qol_modal_return = 238;
static i32 fcoder_metacmd_ID_qol_move_selection_down = 239;
static i32 fcoder_metacmd_ID_qol_move_selection_up = 240;
static i32 fcoder_metacmd_ID_qol_reformat_current = 241;
static i32 fcoder_metacmd_ID_qol_reload_bindings = 242;
static i32 fcoder_metacmd_ID_qol_reload_config = 243;
static i32 fcoder_metacmd_ID_qol_reload_project = 244;
static i32 fcoder_metacmd_ID_qol_reopen_all_buffers = 245;
static i32 fcoder_metacmd_ID_qol_reverse_search = 246;
static i32 fcoder_metacmd_ID_qol_scroll_hovered = 247;
static i32 fcoder_metacmd_ID_qol_search = 248;
static i32 fcoder_metacmd_ID_qol_search_identifier = 249;
static i32 fcoder_metacmd_ID_qol_snippet_begin = 250;
static i32 fcoder_metacmd_ID_qol_snippet_end = 251;
static i32 fcoder_metacmd_ID_qol_startup = 252;
static i32 fcoder_metacmd_ID_qol_try_exit = 253;
static i32 fcoder_metacmd_ID_qol_view_input_handler = 254;
static i32 fcoder_metacmd_ID_qol_write_space = 255;
static i32 fcoder_metacmd_ID_qol_write_text_and_auto_indent = 256;
static i32 fcoder_metacmd_ID_qol_write_text_input = 257;
static i32 fcoder_metacmd_ID_query_replace = 258;
static i32 fcoder_metacmd_ID_query_replace_identifier = 259;
static i32 fcoder_metacmd_ID_query_replace_selection = 260;
static i32 fcoder_metacmd_ID_quick_swap_buffer = 261;
static i32 fcoder_metacmd_ID_redo = 262;
static i32 fcoder_metacmd_ID_redo_all_buffers = 263;
static i32 fcoder_metacmd_ID_rename_file_query = 264;
static i32 fcoder_metacmd_ID_reopen = 265;
static i32 fcoder_metacmd_ID_replace_in_all_buffers = 266;
static i32 fcoder_metacmd_ID_replace_in_buffer = 267;
static i32 fcoder_metacmd_ID_replace_in_range = 268;
static i32 fcoder_metacmd_ID_reverse_search = 269;
static i32 fcoder_metacmd_ID_reverse_search_identifier = 270;
static i32 fcoder_metacmd_ID_save = 271;
static i32 fcoder_metacmd_ID_save_all_dirty_buffers = 272;
static i32 fcoder_metacmd_ID_save_to_query = 273;
static i32 fcoder_metacmd_ID_search = 274;
static i32 fcoder_metacmd_ID_search_identifier = 275;
static i32 fcoder_metacmd_ID_seek_beginning_of_line = 276;
static i32 fcoder_metacmd_ID_seek_beginning_of_textual_line = 277;
static i32 fcoder_metacmd_ID_seek_end_of_line = 278;
static i32 fcoder_metacmd_ID_seek_end_of_textual_line = 279;
static i32 fcoder_metacmd_ID_select_all = 280;
static i32 fcoder_metacmd_ID_select_next_scope_absolute = 281;
static i32 fcoder_metacmd_ID_select_next_scope_after_current = 282;
static i32 fcoder_metacmd_ID_select_prev_scope_absolute = 283;
static i32 fcoder_metacmd_ID_select_prev_top_most_scope = 284;
static i32 fcoder_metacmd_ID_select_surrounding_scope = 285;
static i32 fcoder_metacmd_ID_select_surrounding_scope_maximal = 286;
static i32 fcoder_metacmd_ID_set_eol_mode_from_contents = 287;
static i32 fcoder_metacmd_ID_set_eol_mode_to_binary = 288;
static i32 fcoder_metacmd_ID_set_eol_mode_to_crlf = 289;
static i32 fcoder_metacmd_ID_set_eol_mode_to_lf = 290;
static i32 fcoder_metacmd_ID_set_face_size = 291;
static i32 fcoder_metacmd_ID_set_face_size_this_buffer = 292;
static i32 fcoder_metacmd_ID_set_mark = 293;
static i32 fcoder_metacmd_ID_set_mode_to_notepad_like = 294;
static i32 fcoder_metacmd_ID_set_mode_to_original = 295;
static i32 fcoder_metacmd_ID_setup_build_bat = 296;
static i32 fcoder_metacmd_ID_setup_build_bat_and_sh = 297;
static i32 fcoder_metacmd_ID_setup_build_sh = 298;
static i32 fcoder_metacmd_ID_setup_new_project = 299;
static i32 fcoder_metacmd_ID_show_filebar = 300;
static i32 fcoder_metacmd_ID_show_scrollbar = 301;
static i32 fcoder_metacmd_ID_show_the_log_graph = 302;
static i32 fcoder_metacmd_ID_snipe_backward_whitespace_or_token_boundary = 303;
static i32 fcoder_metacmd_ID_snipe_forward_whitespace_or_token_boundary = 304;
static i32 fcoder_metacmd_ID_snippet_lister = 305;
static i32 fcoder_metacmd_ID_string_repeat = 306;
static i32 fcoder_metacmd_ID_suppress_mouse = 307;
static i32 fcoder_metacmd_ID_swap_panels = 308;
static i32 fcoder_metacmd_ID_theme_lister = 309;
static i32 fcoder_metacmd_ID_to_lowercase = 310;
static i32 fcoder_metacmd_ID_to_uppercase = 311;
static i32 fcoder_metacmd_ID_toggle_code_peek = 312;
static i32 fcoder_metacmd_ID_toggle_filebar = 313;
static i32 fcoder_metacmd_ID_toggle_fps_meter = 314;
static i32 fcoder_metacmd_ID_toggle_fullscreen = 315;
static i32 fcoder_metacmd_ID_toggle_function_tooltip = 316;
static i32 fcoder_metacmd_ID_toggle_highlight_enclosing_scopes = 317;
static i32 fcoder_metacmd_ID_toggle_highlight_line_at_cursor = 318;
static i32 fcoder_metacmd_ID_toggle_line_numbers = 319;
static i32 fcoder_metacmd_ID_toggle_line_wrap = 320;
static i32 fcoder_metacmd_ID_toggle_mouse = 321;
static i32 fcoder_metacmd_ID_toggle_paren_matching_helper = 322;
static i32 fcoder_metacmd_ID_toggle_pproc_anchor = 323;
static i32 fcoder_metacmd_ID_toggle_show_whitespace = 324;
static i32 fcoder_metacmd_ID_toggle_virtual_whitespace = 325;
static i32 fcoder_metacmd_ID_tutorial_maximize = 326;
static i32 fcoder_metacmd_ID_tutorial_minimize = 327;
static i32 fcoder_metacmd_ID_uncomment_line = 328;
static i32 fcoder_metacmd_ID_undo = 329;
static i32 fcoder_metacmd_ID_undo_all_buffers = 330;
static i32 fcoder_metacmd_ID_view_buffer_other_panel = 331;
static i32 fcoder_metacmd_ID_view_jump_list_with_lister = 332;
static i32 fcoder_metacmd_ID_vsplit = 333;
static i32 fcoder_metacmd_ID_word_complete = 334;
static i32 fcoder_metacmd_ID_word_complete_drop_down = 335;
static i32 fcoder_metacmd_ID_word_complete_prev = 336;
static i32 fcoder_metacmd_ID_write_block = 337;
static i32 fcoder_metacmd_ID_write_hack = 338;
static i32 fcoder_metacmd_ID_write_note = 339;
static i32 fcoder_metacmd_ID_write_space = 340;
static i32 fcoder_metacmd_ID_write_text_and_auto_indent = 341;
static i32 fcoder_metacmd_ID_write_text_input = 342;
static i32 fcoder_metacmd_ID_write_todo = 343;
static i32 fcoder_metacmd_ID_write_underscore = 344;
static i32 fcoder_metacmd_ID_write_zero_struct = 345;
static i32 fcoder_metacmd_ID_zk_go_to_definition_other_panel = 346;
static i32 fcoder_metacmd_ID_zk_go_to_definition_same_panel = 347;
static i32 fcoder_metacmd_ID_zk_jump_to_definition_lister = 348;
static i32 fcoder_metacmd_ID_zk_kill_rectangle = 349;
static i32 fcoder_metacmd_ID_zk_list_all_locations = 350;
static i32 fcoder_metacmd_ID_zk_mouse_column_toggle = 351;
static i32 fcoder_metacmd_ID_zk_reverse_search = 352;
static i32 fcoder_metacmd_ID_zk_search = 353;
static i32 fcoder_metacmd_ID_zk_startup = 354;
#endif
