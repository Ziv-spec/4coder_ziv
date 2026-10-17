
global View_ID build_footer_panel_view_id = 0;

// NOTE(ziv): Honestly I don't support 100% coverage on all the functions you would want
// since for porgramming I do use the bview and for writing I don't need a compilation
// buffer. If you do care about that, just add the appropriate commands down here.

function void
zk_build_panel_init(Application_Links *app) {
  b32 show_bview = !def_get_config_b32(vars_save_string_lit("filebar_on_top"));
  if (show_bview) {
    if (!g_qol_b_view) {
      qol_bview_init(app);
    }
  }
  else {
    view_close(app, g_qol_b_view);
    Panel_ID root = panel_get_root(app);
    if (root == 1) {
      panel_set_split(app, root, PanelSplitKind_FixedPixels_Max, 0.f);
    }
    g_qol_b_view = 0;
  }

}

function View_ID
zk_open_footer_panel(Application_Links *app, View_ID view){
  if (!g_qol_b_view) {
    View_ID special_view = open_view(app, view, ViewSplit_Bottom);
    new_view_settings(app, special_view);
    Buffer_ID buffer = view_get_buffer(app, special_view, Access_Always);
    Face_ID face_id = get_face_id(app, buffer);
    Face_Metrics metrics = get_face_metrics(app, face_id);
    view_set_split_pixel_size(app, special_view, (i32)(metrics.line_height*14.f));
    view_set_passive(app, special_view, true);
    return(special_view);
  }
  else {
    qol_bview_open(app);
    return g_qol_b_view;
  }
}

function void
zk_close_build_footer_panel(Application_Links *app){
  if (!g_qol_b_view) {
    if (view_exists(app, build_footer_panel_view_id)){
      view_close(app, build_footer_panel_view_id);
    }
    build_footer_panel_view_id = 0;
  }
  else {
    qol_bview_close(app);
  }
}

function View_ID
zk_open_build_footer_panel(Application_Links *app){
  if (!g_qol_b_view) {
    if (!view_exists(app, build_footer_panel_view_id)){
      View_ID view = get_active_view(app, Access_Always);
      build_footer_panel_view_id = zk_open_footer_panel(app, view);
      view_set_active(app, view);
    }
    return(build_footer_panel_view_id);
  }
  else {
    build_footer_panel_view_id = 0;
    qol_bview_open(app);
    return g_qol_b_view;
  }
}

function View_ID
zk_get_or_open_build_panel(Application_Links *app){
  View_ID view = 0;
  Buffer_ID buffer = get_comp_buffer(app);
  if (buffer != 0){
    view = get_first_view_with_buffer(app, buffer);
  }
  if (view == 0){
    view = zk_open_build_footer_panel(app);
  }
  return(view);
}

CUSTOM_COMMAND_MC_GLOBAL_SIG(zk_build_in_build_panel)
CUSTOM_DOC("Looks for a build.bat, build.sh, or makefile in the current and parent directories.  Runs the first that it finds and prints the output to *compilation*.  Puts the *compilation* buffer in a panel at the footer of the current view.")
{
  View_ID view = get_active_view(app, Access_Always);
  Buffer_ID buffer = view_get_buffer(app, view, Access_Always);

  View_ID build_view = zk_get_or_open_build_panel(app);
  if (g_qol_b_view) qol_bview_set_buffer(app, buffer_identifier_to_id(app, standard_build_build_buffer_identifier));

  standard_search_and_build(app, build_view, buffer);

  block_zero_struct(&prev_location);
  lock_jump_buffer(app, string_u8_litexpr("*compilation*"));
}

CUSTOM_COMMAND_MC_GLOBAL_SIG(zk_close_build_panel)
CUSTOM_DOC("If the special build panel is open, closes it.")
{
  zk_close_build_footer_panel(app);
}
