
// TOP

#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.h"

#include "4coder_qol_bview.h"

#define run_lister default_run_lister

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

#include "languages/qol_parser_helper.h"
#include "languages/qol_languages.h"
#include "4coder_default_include.cpp"
#include "languages/cpp_parser.cpp"
#include "languages/lua_parser.cpp"

#include "4coder_qol_helper.h"
#include "4coder_qol_block.cpp"

#include "4coder_qol_colors.cpp"
#include "4coder_qol_token.cpp"

#include "languages/qol_languages.cpp"
#include "languages/non_code.cpp"



// NOTE(allen): Users can declare their own managed IDs here.

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

void
custom_layer_init(Application_Links *app){
  Thread_Context *tctx = get_thread_context(app);

  // NOTE(allen): setup for default framework
  default_framework_init(app);

  // NOTE(allen): default hooks and command maps
  set_all_default_hooks(app);
  mapping_init(tctx, &framework_mapping);
  String_ID global_map_id = vars_save_string_lit("keys_global");
  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");
  #if OS_MAC
  setup_mac_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
  #else
  setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
  #endif
  setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
}

#endif //FCODER_DEFAULT_BINDINGS

// BOTTOM

