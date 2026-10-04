
// TODO(ziv): Since this is a tiny modification but I had to copy a lot to do it, consider just editing the default custom layer to allow for this smart swapping 
#if !defined(_lister_get_filtered)
#define _lister_get_filtered zk_lister_get_filtered
#endif

function void
zk_lister_render(Application_Links *app, Frame_Info frame_info, View_ID view){
  Scratch_Block scratch(app);
  
  Lister *lister = view_get_lister(app, view);
  if (lister == 0){
    return;
  }
  
  Face_ID face_id = get_face_id(app, 0);
  Face_Metrics metrics = get_face_metrics(app, face_id);
  f32 line_height = metrics.line_height;
  f32 block_height = lister_get_block_height(line_height);
  f32 text_field_height = lister_get_text_field_height(line_height);
  
  b64 showing_file_bar = false;
  b32 hide_file_bar_in_ui = def_get_config_b32(vars_save_string_lit("hide_file_bar_in_ui"));
  Rect_f32 region = view_get_screen_rect(app, view);
  if (view_get_setting(app, view, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar && !hide_file_bar_in_ui){
    b32 on_top = def_get_config_b32(vars_save_string_lit("filebar_on_top"));
    Rect_f32_Pair pair = (on_top ?
                          layout_file_bar_on_top(region, line_height) :
                          layout_file_bar_on_bot(region, line_height));
    zk_draw_file_bar(app, view, view_get_buffer(app, view, Access_Always), face_id, pair.e[1-on_top]);
    region = pair.e[on_top];
  }
  draw_rectangle_fcolor(app, region, 0.f, fcolor_id(defcolor_back));
  Rect_f32 prev_clip = draw_set_clip(app, region);
  
  
  lister->visible_count = (i32)((rect_height(region)/block_height)) - 3;
  lister->visible_count = clamp_bot(1, lister->visible_count);
  
  f32 padding = metrics.normal_advance * .75f;
  Rect_f32_Pair pair = lister_get_top_level_layout(region, text_field_height + 2*padding);
  Rect_f32 text_field_rect = pair.min;
  Rect_f32 list_rect = pair.max;
  
  FColor pop1_color = fcolor_id(defcolor_pop1);
  FColor pop2_color = fcolor_id(defcolor_pop2);
  FColor text_color = fcolor_id(defcolor_text_default);
  FColor margin_color = fcolor_id(defcolor_margin);
  
  {
    // from Long_Lister_RenderHUD
    Vec2_f32 p; 
    
    f32 margin_size = 3.f;
    i32 item_count = lister->filtered.count;
    {
      Rect_f32 margin_rect = pair.min;
      margin_rect.y0 = margin_rect.y1 - margin_size;
      draw_rectangle(app, margin_rect, 0, fcolor_resolve(margin_color));
    }
    
    Fancy_Line query = {};
    Rect_f32 query_rect = rect_inner(pair.min, padding);
    {
      push_fancy_string(scratch,  &query, pop1_color, lister->query.string);
      push_fancy_stringf(scratch, &query, pop1_color, " (%d/%d) ", lister->item_index + !!item_count, item_count);
      p = draw_fancy_line(app, face_id, fcolor_zero(), &query, query_rect.p0);
    }
    
    Fancy_Line text_field = {};
    {
      push_fancy_string(scratch, &text_field, text_color, lister->text_field.string);
      
      f32 cap_width =(query_rect.x1 - p.x);
      f32 overflow = get_fancy_line_width(app, face_id, &text_field) - cap_width;
      if (overflow > 0)
      {
        // NOTE(long): We don't need to reset the clip after draw_fancy_line
        draw_set_clip(app, Rf32(If32_size(p.x, cap_width), rect_range_y(query_rect)));
        p.x -= overflow;
      }
      draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);
    }
  }
  
  Range_f32 x = rect_range_x(list_rect);
  draw_set_clip(app, list_rect);
  
  // NOTE(allen): auto scroll to the item if the flag is set.
  f32 scroll_y = lister->scroll.position.y;
  
  Mouse_State mouse = get_mouse_state(app);
  Vec2_f32 m_p = V2f32(mouse.p);
  if (lister->set_vertical_focus_to_item){
    lister->set_vertical_focus_to_item = false;
    Range_f32 item_y = If32_size(lister->item_index*block_height, block_height);
    f32 view_h = rect_height(list_rect);
    Range_f32 view_y = If32_size(scroll_y, view_h);
    if (view_y.min > item_y.min || item_y.max > view_y.max){
      f32 item_center = (item_y.min + item_y.max)*0.5f;
      f32 view_center = (view_y.min + view_y.max)*0.5f;
      f32 margin = view_h*.3f;
      margin = clamp_top(margin, block_height*3.f);
      if (item_center < view_center){
        lister->scroll.target.y = item_y.min - margin;
      }
      else{
        f32 target_bot = item_y.max + margin;
        lister->scroll.target.y = target_bot - view_h;
      }
    }
  }
  
  // NOTE(allen): clamp scroll target and position; smooth scroll rule
  i32 count = lister->filtered.count;
  Range_f32 scroll_range = If32(0.f, clamp_bot(0.f, count*block_height - block_height));
  lister->scroll.target.y = clamp_range(scroll_range, lister->scroll.target.y);
  lister->scroll.target.x = 0.f;
  
  Vec2_f32_Delta_Result delta = delta_apply(app, view,
                                            frame_info.animation_dt, lister->scroll);
  lister->scroll.position = delta.p;
  if (delta.still_animating){
    animate_in_n_milliseconds(app, 0);
  }
  
  lister->scroll.position.y = clamp_range(scroll_range, lister->scroll.position.y);
  lister->scroll.position.x = 0.f;
  
  scroll_y = lister->scroll.position.y;
  f32 y_pos = list_rect.y0 - scroll_y;
  
  i32 first_index = (i32)(scroll_y/block_height);
  y_pos += first_index*block_height;
  
  for (i32 i = first_index; i < count; i += 1){
    Lister_Node *node = lister->filtered.node_ptrs[i];
    
    if (y_pos >= region.y1){ break; }
    Range_f32 y = If32(y_pos, y_pos + block_height);
    y_pos = y.max;
    
    Rect_f32 item_rect = Rf32(x, y);
    Rect_f32 item_inner = rect_inner(item_rect, 3.f);
    
    b32 hovered = rect_contains_point(item_rect, m_p);
    UI_Highlight_Level highlight = UIHighlight_None;
    if (node == lister->highlighted_node){
      highlight = UIHighlight_Active;
    }
    else if (node->user_data == lister->hot_user_data){
      if (hovered){
        highlight = UIHighlight_Active;
      }
      else{
        highlight = UIHighlight_Hover;
      }
    }
    else if (hovered){
      highlight = UIHighlight_Hover;
    }
    
    u64 lister_roundness_100 = def_get_config_u64(app, vars_save_string_lit("lister_roundness"));
    f32 roundness = block_height*lister_roundness_100*0.01f;
    draw_rectangle_fcolor(app, item_rect, roundness, get_item_margin_color(highlight));
    draw_rectangle_fcolor(app, item_inner, roundness, get_item_margin_color(highlight, 1));
    
    Fancy_Line line = {};
    push_fancy_string(scratch, &line, fcolor_id(defcolor_text_default), node->string);
    push_fancy_stringf(scratch, &line, " ");
    push_fancy_string(scratch, &line, fcolor_id(defcolor_pop2), node->status);
    
    Vec2_f32 p = item_inner.p0 + V2f32(3.f, (block_height - line_height)*0.5f);
    draw_fancy_line(app, face_id, fcolor_zero(), &line, p);
  }
  
  draw_set_clip(app, prev_clip);
}




function Lister_Filtered
zk_lister_get_filtered(Arena *arena, Lister *lister){
  i32 node_count = lister->options.count;
  
  Lister_Filtered filtered = {};
  filtered.exact_matches.node_ptrs = push_array(arena, Lister_Node*, 1);
  filtered.before_extension_matches.node_ptrs = push_array(arena, Lister_Node*, node_count);
  filtered.substring_matches.node_ptrs = push_array(arena, Lister_Node*, node_count);
  
  Temp_Memory_Block temp(arena);
  
  String_Const_u8 key = lister->key_string.string;
  if (key.size == 0)
  {
    // NOTE(long): This is both for optimizing and preventing an empty key from matching with an empty item
    // The latter is important if you want to match the order of Lister:filtered with the order of Lister:options
    for (Lister_Node* node = lister->options.first; node; node = node->next)
      filtered.substring_matches.node_ptrs[filtered.substring_matches.count++] = node;
    return filtered;
  }
  
  key = push_string_copy(arena, key);
  string_mod_replace_character(key, '_', '*');
  string_mod_replace_character(key, ' ', '*');
  
  List_String_Const_u8 absolutes = {};
  string_list_push(arena, &absolutes, string_u8_litexpr(""));
  List_String_Const_u8 splits = string_split(arena, key, (u8*)"*", 1);
  b32 has_wildcard = (splits.node_count > 1);
  string_list_push(&absolutes, &splits);
  string_list_push(arena, &absolutes, string_u8_litexpr(""));
  
  // Setting up the filter for tags
  String8Node *last_node = NULL;
  String8List include_tags = {}, exclude_tags = {};
  for (String8Node *node = absolutes.first; node != NULL; node = node->next) {
    String8 string = node->string;
    String8List* list = (string.str[0] == '\\' ? &include_tags : 
                         string.str[0] == '~'  ? &exclude_tags : NULL);
    if (list) {
      absolutes.node_count--;
      node->string = string_skip(string, 1);
      
      if (last_node)  last_node->next = node->next; // skipping current node 
      string_list_push(list, node); // NOTE(ziv): THIS MODIFYS THE NODE (uhhhh if I had known this before)
      node = last_node; // at the end of the loop we go to the next one
    }
    last_node = node;
  }
  
  // NOTE(Ziv): COPYPASTA Long layer
  for (Lister_Node* node = lister->options.first; node; node = node->next)
  {
    for (String8Node* tag = include_tags.first; tag; tag = tag->next)
      if (!string_has_substr(node->status, tag->string, StringMatch_CaseInsensitive)) goto NEXT;
    
    for (String8Node* tag = exclude_tags.first; tag; tag = tag->next)
      if (string_has_substr(node->status, tag->string, StringMatch_CaseInsensitive))  goto NEXT;
    
    String8 string = node->string;
    if (key.size == 0 || string_wildcard_match_insensitive(absolutes, string))
    {
      if (string_match_insensitive(string, key) && filtered.exact_matches.count == 0)
        filtered.exact_matches.node_ptrs[filtered.exact_matches.count++] = node;
      else if (key.size > 0 && !has_wildcard && string_match_insensitive(string_prefix(string, key.size), key) &&
               node->string.size > key.size && node->string.str[key.size] == '.')
        filtered.before_extension_matches.node_ptrs[filtered.before_extension_matches.count++] = node;
      else
        filtered.substring_matches.node_ptrs[filtered.substring_matches.count++] = node;
    }
    
    NEXT:;
  }
  
  return(filtered);
}

function void
zk_lister_update_filtered_list(Application_Links *app, Lister *lister){
  Arena *arena = lister->arena;
  Scratch_Block scratch(app, arena);
  
  Lister_Filtered filtered = _lister_get_filtered(scratch, lister);
  
  Lister_Node_Ptr_Array node_ptr_arrays[] = {
    filtered.exact_matches,
    filtered.before_extension_matches,
    filtered.substring_matches,
  };
  
  end_temp(lister->filter_restore_point);
  
  i32 total_count = 0;
  for (i32 array_index = 0; array_index < ArrayCount(node_ptr_arrays); array_index += 1){
    total_count += node_ptr_arrays[array_index].count;
  }
  
  Lister_Node **node_ptrs = push_array(arena, Lister_Node*, total_count);
  lister->filtered.node_ptrs = node_ptrs;
  lister->filtered.count = total_count;
  for (i32 array_index = 0, counter = 0; array_index < ArrayCount(node_ptr_arrays); array_index += 1){
    Lister_Node_Ptr_Array node_ptr_array = node_ptr_arrays[array_index];
    for (i32 node_index = 0; node_index < node_ptr_array.count; node_index += 1){
      Lister_Node *node = node_ptr_array.node_ptrs[node_index];
      node_ptrs[counter] = node;
      counter += 1;
    }
  }
  
  lister_update_selection_values(lister);
}

function void
zk_lister_call_refresh_handler(Application_Links *app, Lister *lister){
  if (lister->handlers.refresh != 0){
    lister->handlers.refresh(app, lister);
    lister->filter_restore_point = begin_temp(lister->arena);
    zk_lister_update_filtered_list(app, lister);
  }
}

function void
zk_lister__backspace_text_field__default(Application_Links *app){
  View_ID view = get_active_view(app, Access_Always);
  Lister *lister = view_get_lister(app, view);
  User_Input input = get_current_input(app);
  b32 mod_ctl = has_modifier(&input, KeyCode_Control);
  b32 mod_sft = has_modifier(&input, KeyCode_Shift);
  if (lister != 0){
    lister->text_field.string = (mod_ctl &&  mod_sft ? string_prefix(lister->text_field.string, 0) :
                                 mod_ctl && !mod_sft ? qol_ctrl_backspace_string(app, lister->text_field.string) :
                                 backspace_utf8(lister->text_field.string));
    lister->key_string.string = (mod_ctl &&  mod_sft ? string_prefix(lister->key_string.string, 0) :
                                 mod_ctl && !mod_sft ? qol_ctrl_backspace_string(app, lister->key_string.string) :
                                 backspace_utf8(lister->key_string.string));
    lister->item_index = 0;
    lister_zero_scroll(lister);
    zk_lister_call_refresh_handler(app, lister); 
    //zk_lister_update_filtered_list(app, lister);
  }
}

function void
zk_lister__backspace_text_field__file_path(Application_Links *app){
  View_ID view = get_this_ctx_view(app, Access_Always);
  Lister *lister = view_get_lister(app, view);
  User_Input input = get_current_input(app);
  b32 mod_ctl = has_modifier(&input, KeyCode_Control);
  b32 mod_sft = has_modifier(&input, KeyCode_Shift);
  if (lister != 0){
    if (lister->text_field.size > 0){
      String_Const_u8 string = lister->text_field.string;
      char last_char = string.str[string.size - 1];
      lister->text_field.string = (mod_ctl &&  mod_sft ? string_prefix(string, string_find_first_slash(string)) :
                                   mod_ctl && !mod_sft ? qol_ctrl_backspace_string(app, string) :
                                   backspace_utf8(string));
      if (character_is_slash(last_char)){
        String_Const_u8 text_field = lister->text_field.string;
        String_Const_u8 new_hot = string_remove_last_folder(text_field);
        b32 use_mod_ctl = def_get_config_b32(vars_save_string_lit("lister_whole_word_backspace_when_modified"));
        if (use_mod_ctl && (mod_ctl && !mod_sft)){
          lister->text_field.size = new_hot.size;
        }
        set_hot_directory(app, new_hot);
        // TODO(allen): We have to protect against lister_call_refresh_handler
        // changing the text_field here. Clean this up.
        String_u8 dingus = lister->text_field;
        zk_lister_call_refresh_handler(app, lister);
        lister->text_field = dingus;
      }
      else{
        String_Const_u8 text_field = lister->text_field.string;
        String_Const_u8 new_key = string_front_of_path(text_field);
        lister_set_key(lister, new_key);
      }
      
      lister->item_index = 0;
      lister_zero_scroll(lister);
      zk_lister_call_refresh_handler(app,lister); 
      //zk_lister_update_filtered_list(app, lister);
    }
  }
}

function Custom_Command_Function*
zk_lister_backspace_replace(Custom_Command_Function *func){
  return (func == lister__backspace_text_field__default   ? zk_lister__backspace_text_field__default   :
          func == lister__backspace_text_field__file_path ? zk_lister__backspace_text_field__file_path : func);
}

function Lister_Activation_Code
zk_lister__write_string(Application_Links *app){
  Lister_Activation_Code result = ListerActivation_Continue;
  View_ID view = get_active_view(app, Access_Always);
  Lister *lister = view_get_lister(app, view);
  if (lister != 0){
    User_Input in = get_current_input(app);
    String_Const_u8 string = to_writable(&in);
    if (string.str != 0 && string.size > 0){
      lister_append_text_field(lister, string);
      lister_append_key(lister, string);
      lister->item_index = 0;
      lister_zero_scroll(lister);
      zk_lister_update_filtered_list(app, lister);
    }
  }
  return(result);
}

function Lister_Result
zk_run_lister(Application_Links *app, Lister *lister){
  lister->handlers.backspace = zk_lister_backspace_replace(lister->handlers.backspace);
  if (lister->handlers.write_character == lister__write_string__default) {
    lister->handlers.write_character = zk_lister__write_string;
  }
  lister->filter_restore_point = begin_temp(lister->arena);
  zk_lister_update_filtered_list(app, lister);
  
  View_ID view = get_this_ctx_view(app, Access_Always);
  View_Context ctx = view_current_context(app, view);
  ctx.render_caller = zk_lister_render;
  ctx.hides_buffer = true;
  View_Context_Block ctx_block(app, view, &ctx);
  
  qol_bot_text_set(lister->query.string);
  
  for (;;){
    User_Input in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
    if (in.abort){
      block_zero_struct(&lister->out);
      lister->out.canceled = true;
      break;
    }
    
    Lister_Activation_Code result = ListerActivation_Continue;
    b32 handled = true;
    switch (in.event.kind){
      case InputEventKind_TextInsert:{
        if (lister->handlers.write_character != 0){
          result = lister->handlers.write_character(app);
          lister->handlers.navigate(app, view, lister, 0);
        }
      }break;
      
      case InputEventKind_KeyStroke:{
        Key_Code code = in.event.key.code;
        switch (code){
          case KeyCode_Return:{
            void *user_data = lister_get_user_data(lister, lister->raw_item_index);
            if (user_data != 0){
              qol_bot_text_append(string_u8_litexpr(" "));
              qol_bot_text_append(lister->highlighted_node->string);
            }
            lister_activate(app, lister, user_data, false);
            result = ListerActivation_Finished;
          }break;
          
          case KeyCode_Backspace:{
            if (lister->handlers.backspace != 0){
              lister->handlers.backspace(app);
              lister->handlers.navigate(app, view, lister, 0);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;
          
          case KeyCode_Tab:{
            if (lister->handlers.navigate != 0){
              i32 delta = (has_modifier(&in.event.key.modifiers, KeyCode_Shift) ? -1 : 1);
              lister->handlers.navigate(app, view, lister, delta);
            }
          }break;
          
          case KeyCode_PageUp:
          case KeyCode_PageDown:
          case KeyCode_Up:
          case KeyCode_Down:{
            if (lister->handlers.navigate != 0){
              i32 delta = (code == KeyCode_PageUp   ? -lister->visible_count :
                           code == KeyCode_PageDown ?  lister->visible_count :
                           code == KeyCode_Up       ? -1 :
                           code == KeyCode_Down     ?  1 : 0);
              lister->handlers.navigate(app, view, lister, delta);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;
          
          default:{
            if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;
        }
      }break;
      
      case InputEventKind_MouseButton:{
        switch (in.event.mouse.code){
          case MouseCode_Left:{
            Vec2_f32 p = V2f32(in.event.mouse.p);
            void *clicked = lister_user_data_at_p(app, view, lister, p);
            lister->hot_user_data = clicked;
          }break;
          
          default:{ handled = false; }break;
        }
      }break;
      
      case InputEventKind_MouseButtonRelease:{
        switch (in.event.mouse.code){
          case MouseCode_Left:{
            if (g_qol_mouse_node){
              qol_bot_text_append(string_u8_litexpr(" "));
              qol_bot_text_append(g_qol_mouse_node->string);
              lister_activate(app, lister, g_qol_mouse_node->user_data, true);
              result = ListerActivation_Finished;
            }
            lister->hot_user_data = 0;
          }break;
          
          default:{ handled = false; }break;
        }
      }break;
      
      case InputEventKind_MouseWheel:{
        Mouse_State mouse = get_mouse_state(app);
        lister->scroll.target.y += mouse.wheel;
        zk_lister_update_filtered_list(app, lister);
      }break;
      
      case InputEventKind_MouseMove:{
        zk_lister_update_filtered_list(app, lister);
      }break;
      
      case InputEventKind_Core:{
        switch (in.event.core.code){
          case CoreCode_Animate:{
            zk_lister_update_filtered_list(app, lister);
          }break;
          
          default:{ handled = false; }break;
        }
      }break;
      
      default:{ handled = false; }break;
    }
    
    if (result == ListerActivation_Finished){
      break;
    }
    
    if (!handled){
      Mapping *mapping = lister->mapping;
      Command_Map *map = lister->map;
      
      Fallback_Dispatch_Result disp_result =
        fallback_command_dispatch(app, mapping, map, &in);
      if (disp_result.code == FallbackDispatch_DelayedUICall){
        call_after_ctx_shutdown(app, view, disp_result.func);
        break;
      }
      if (disp_result.code == FallbackDispatch_Unhandled){
        leave_current_input_unhandled(app);
      }
      else{
        zk_lister_call_refresh_handler(app, lister);
      }
    }
    
    view_set_active(app, view); // TODO(ziv): Consider whether I want this
  }
  
  return(lister->out);
}
