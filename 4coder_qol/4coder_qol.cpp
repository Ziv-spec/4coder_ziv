
#include "../4coder_zk/4coder_zk_microsoft_crazyness.h"

#include "4coder_default_include.h"
global f32 g_double_click_t;

//#define SNIPPET_EXPANSION "path/to/snippet.inc"

//#define AUTO_CENTER_AFTER_JUMPS false

#include "4coder_qol_lister.h"
#include "4coder_qol_bview.h"

function Lister_Result zk_run_lister(Application_Links *app, Lister *lister);
#define run_lister zk_run_lister

CUSTOM_ID(colors, defcolor_type);
CUSTOM_ID(colors, defcolor_function);
CUSTOM_ID(colors, defcolor_macro);
CUSTOM_ID(colors, defcolor_enum);
CUSTOM_ID(colors, defcolor_global);
CUSTOM_ID(colors, defcolor_control);
CUSTOM_ID(colors, defcolor_primitive);
CUSTOM_ID(colors, defcolor_struct);
CUSTOM_ID(colors, defcolor_non_text);
CUSTOM_ID(colors, defcolor_operator);

function b32 MC_filter_command(Custom_Command_Function *func);

// Ideally this could be defined in 4coder_multi_cursor.cpp
#if !defined(META_PASS)
#define CUSTOM_COMMAND_MC_SIG(name, kind)  void name(struct Application_Links *app)
#else
#define CUSTOM_COMMAND_MC_SIG(name, kind)  CUSTOM_COMMAND(name, __FILE__, __LINE__, Normal, kind)
#endif
#define CUSTOM_COMMAND_MC_CURSOR_SIG(name) CUSTOM_COMMAND_MC_SIG(name, 1) // 1 == MC_Command_Cursor
#define CUSTOM_COMMAND_MC_GLOBAL_SIG(name) CUSTOM_COMMAND_MC_SIG(name, 2) // 2 == MC_Command_Global
#define CUSTOM_COMMAND_MC_COPY_SIG(name)   CUSTOM_COMMAND_MC_SIG(name, 3) // 3 == MC_Command_CursorCopy
#define CUSTOM_COMMAND_MC_PASTE_SIG(name)  CUSTOM_COMMAND_MC_SIG(name, 4) // 4 == MC_Command_CursorPaste

#include "languages/qol_parser_helper.h"
#include "languages/qol_languages.h"
#include "4coder_default_include.cpp"
#include "languages/cpp_parser.cpp"
#include "languages/lua_parser.cpp"

#include "4coder_qol_jumps.cpp"

global b32 qol_opened_brace = false;
global u8 qol_target_char;
global Buffer_Cursor qol_col_cursor = {-1};
global Buffer_ID qol_col_buffer;

global Vec2_f32 qol_cur_cursor_pos;
global Vec2_f32 qol_nxt_cursor_pos;
global Vec2_f32 qol_cur_mark_pos;
global Vec2_f32 qol_nxt_mark_pos;


#define HOVER_TIME 0.25f
global f32 g_hover_dt;
global b32 g_use_minimap_hover;

#include "plugins/4coder_multi_cursor.cpp"
#include "plugins/4coder_tabs.cpp"
#include "plugins/4coder_minimap.cpp"

global Color_Table qol_cur_colors;
global Color_Table qol_nxt_colors;

global Face_ID qol_small_face;

global Buffer_ID qol_temp_buffer;

global View_ID qol_try_exit_view;

global u8 g_qol_bot_buffer[1024];
global String_u8 g_qol_bot_string = Su8(g_qol_bot_buffer, 0, sizeof(g_qol_bot_buffer));

global Character_Predicate character_predicate_word = {};
global Character_Predicate character_predicate_non_word = {};

global View_ID g_qol_lister_view;
global Lister* g_qol_lister;
global Lister_Node* g_qol_mouse_node;

#include "4coder_qol_helper.h"
#include "4coder_qol_block.cpp"

#include "4coder_qol_colors.cpp"
#include "4coder_qol_token.cpp"

#include "languages/qol_languages.cpp"
#include "languages/non_code.cpp"

#pragma warning(disable : 4706)
#include "4coder_qol_bindings.cpp"
#include "4coder_qol_commands.cpp"
#include "4coder_qol_reformat.cpp"

#include "4coder_qol_isearch.cpp"
#include "4coder_qol_draw.cpp"

#include "4coder_qol_lister.cpp"
#include "4coder_qol_bview.cpp"
#include "4coder_qol_snippets.cpp"

#include "4coder_qol_hooks.cpp"


#include "../4coder_zk/4coder_loco_yeets.cpp" // actually this can be places as if it is a plugin (since it really is written like one)
#include "../4coder_zk/4coder_zk_search.cpp"
#include "../4coder_zk/4coder_zk_commands.cpp"
#include "../4coder_zk/4coder_zk_bindings.cpp"
#include "../4coder_zk/4coder_zk_draw.cpp"
#include "../4coder_zk/4coder_zk_hooks.cpp"
#include "../4coder_zk/4coder_zk_lister.cpp"

void custom_layer_init(Application_Links *app){
  Thread_Context *tctx = get_thread_context(app);

  default_framework_init(app);

  MC_init(app);

  MC_register(command_lister,   MC_Command_Global);
  MC_register(theme_lister,     MC_Command_Global);

  //qol_lang_register(Lang_None, lang_lex_async_nop, lang_lex_sync_nop, lang_parse_nop, lang_paint_nop);
  qol_lang_register(Lang_None, lex_full_input_async_none, lex_full_input_none, lang_parse_nop, qol_get_token_color_none);  // none_parse_file
  qol_lang_register(Lang_Cpp,  lex_full_input_async_cpp,  lex_full_input_cpp,  cpp_parse_file, qol_get_token_color_cpp);
  qol_lang_register(Lang_4ed,  lex_full_input_async_cpp,  lex_full_input_cpp,  cpp_parse_file, qol_get_token_color_cpp);
  qol_lang_register(Lang_XSL,  lex_full_input_async_cpp,  lex_full_input_cpp,  cpp_parse_file, qol_get_token_color_cpp);
  qol_lang_register(Lang_Cpp,  lex_full_input_async_cpp,  lex_full_input_cpp,  cpp_parse_file, qol_get_token_color_cpp);
  qol_lang_register(Lang_Lua,  lex_full_input_async_lua,  lex_full_input_lua,  lua_parse_file, qol_get_token_color_lua);

  // Set up custom layer hooks
  {
    set_custom_hook(app, HookID_BufferViewerUpdate, default_view_adjust);

    set_custom_hook(app, HookID_ViewEventHandler, qol_view_input_handler);
    set_custom_hook(app, HookID_Tick, zk_tick);
    set_custom_hook(app, HookID_RenderCaller, zk_render_caller);
    set_custom_hook(app, HookID_WholeScreenRenderCaller, zk_whole_screen_render_caller);

    set_custom_hook(app, HookID_DeltaRule, zk_delta_rule);
    set_custom_hook_memory_size(app, HookID_DeltaRule,
                                delta_ctx_size(fixed_time_cubic_delta_memory_size));

    set_custom_hook(app, HookID_BufferNameResolver, default_buffer_name_resolution);

    set_custom_hook(app, HookID_BeginBuffer, zk_begin_buffer);
    set_custom_hook(app, HookID_EndBuffer, zk_end_buffer_close_jump_list);
    set_custom_hook(app, HookID_NewFile, default_new_file);
    set_custom_hook(app, HookID_SaveFile, qol_file_save);
    set_custom_hook(app, HookID_BufferEditRange, zk_buffer_edit_range);
    set_custom_hook(app, HookID_BufferRegion, qol_buffer_region);
    set_custom_hook(app, HookID_ViewChangeBuffer, default_view_change_buffer);

    set_custom_hook(app, HookID_Layout, layout_unwrapped);
  }

  // def_set_config_b32(vars_save_string_lit("use_function_tooltip"), true);

  mapping_init(tctx, &framework_mapping);
  String_ID global_map_id = vars_save_string_lit("keys_global");
  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");
  zk_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
  zk_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
}

// [x] Removing all vim related stuff
// [x] Old file bar but with progress percent (just like in BYP layer)
// [x] move tooltip to the bottom of the view / have a setting for switching between the two
// [x] lister item counter just like in the 4coder_long implementation that is great
//   [x] draw the lister item counter
//   [x] handle filtering of tags
// [x] Integrate https://github.com/perky/4coder_loco/blob/main/4coder_loco_yeets.cpp to codebase
//   NOTE: In 'zk_begin_buffer' I give *yeet* a default Lexer for cpp. This is not robust and is a hack
//         for now. I should probably implement a way of lexing/coloring each section individually.
// [x] Show Mini Map on mouse hover (also created a hover time to activate)
// [ ] zk_go_to_definition_same_panel
//   [x] uses fleury logic for intuitive function/type finding
//   [x] make that you can jump to folder in string & in #include <windows.h> you can jump to it
//   [ ] fix bug with get next intitive node
// [ ] search
// [x] add selection range to cursor
// [ ] notepad cursor full support
//   [x] selection across all neccesary commands
//   [ ] double click to select token, triple click to select line
//
// Review the behavior of 'quick_swap_buffer' I remember I Had problems with it at some point
// yeah. So the beahvior that I don't like is that when I am jumping around many files, one after
// another, I usually just want to jump back to the first location that I began with, not caring about
// all other intermediate buffers I went through. For example: a function that has another function
// which i jump to, then a type. I want to return back to the first function quickly since I don't really
// care about any of the intermediate steps I took. I should think whetehr I will just accept my faith that
// jump_to_prev is just fine, or have a good intuitition about what should truly happen instead.


// TODO(ziv): Recover Fleury's layer capabilities
// In the parser: ( I truly consider whether it is worthwhile to pursue this, since this is a very searchable thing )
//  - Add tags
//  - Add TODO's
//  - Add forward declorations / think about how to render it
// In jump_to_definition:
//  - ability to jump to tag?
//  - add ability to show forward declorations of functions
//  - also filter results by their tag name
//  - ability to jump from one decloration/implementation to another under the same name in a sequence (instead of locking to the first one never releasing it)
//
// New ideas to think about
// -  allow different panel search continueation.
//     The idea: I search something in a panel, switch to a different one, continue to search there (likely in a different file)
//     This is i guess implemented in vim as I saw in the wookash pod. I need to think about how useful it is to me.
//

// - long cool history stuff panel thingy look into it
// - Alt+LeftClick to begin rect select
//
// @zk_wow_cool