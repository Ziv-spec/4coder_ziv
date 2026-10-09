/*
4coder_code_index.cpp - Generic code indexing system for layout, definition jumps, etc.
*/

// TOP

global Code_Index global_code_index = {};

////////////////////////////////
// NOTE(allen): Lookups

// TODO(allen): accelerator for these nest lookups?
// Looks like the only one I ever actually use is the file one, not the array one.
function Code_Index_Nest*
code_index_get_nest_(Code_Index_Nest *nest, i64 pos){
  // binary search?
  for (i32 i = 0; i < nest->nest_array.count; i += 1){
    Code_Index_Nest *n = nest->nest_array.ptrs[i];
    if (n->open.min <= pos && pos <= n->close.min){
      return code_index_get_nest_(n, pos);
      // tail-call equiv of `return(sub_nest != 0 ? sub_nest : nest)`
    }
  }
  return nest;
}

function Code_Index_Nest*
nest_next_in_order(Code_Index_Nest *nest, i64 pos, u64 mask){
  if (nest == NULL){ return NULL; }
  if (pos <= nest->open.min && HasFlag(mask, 1ull << nest->kind)){ return nest; }

  for (int i=0; i < nest->nest_array.count; i++){
    Code_Index_Nest *n = nest->nest_array.ptrs[i];
    Code_Index_Nest *next = nest_next_in_order(n, pos, mask);
    if (next != NULL){ return next; }
  }

  if (pos <= nest->close.min && HasFlag(mask, 1ull << nest->kind)){ return nest; }
  return NULL;
}

function Code_Index_Nest*
nest_prev_in_order(Code_Index_Nest *nest, i64 pos, u64 mask){
  if (nest == NULL){ return NULL; }
  if (nest->close.min <= pos && HasFlag(mask, 1ull << nest->kind)){ return nest; }

  for (int i=0; i < nest->nest_array.count; i++){
    Code_Index_Nest *n = nest->nest_array.ptrs[nest->nest_array.count-1-i];
    Code_Index_Nest *prev = nest_prev_in_order(n, pos, mask);
    if (prev != NULL){ return prev; }
  }

  if (nest->open.min <= pos && HasFlag(mask, 1ull << nest->kind)){ return nest; }
  return NULL;
}

function Code_Index_Nest*
code_index_get_nest(Code_Index_File *file, i64 pos){
  return(file==NULL ? NULL : code_index_get_nest_(&file->root, pos));
}

function Code_Index_Nest*
code_index_nest_walk(Code_Index_Nest *nest, i64 pos){
  Code_Index_File *file = nest->file;
  for(;;){
    if (nest == NULL){
      return code_index_get_nest(file, pos);
    }
    if (nest->open.min <= pos && pos < nest->close.max){
      return code_index_get_nest_(nest, pos);
    }
    nest = nest->parent;
  }
}

function Code_Index_Note_List*
code_index__list_from_string(String_Const_u8 string){
  u64 hash = table_hash_u8(string.str, string.size);
  Code_Index_Note_List *result = &global_code_index.name_hash[hash % ArrayCount(global_code_index.name_hash)];
  return(result);
}

function Code_Index_Note*
code_index_note_from_string(String_Const_u8 string){
  Code_Index_Note_List *list = code_index__list_from_string(string);
  Code_Index_Note *result = 0;
  for (Code_Index_Note *node = list->first;
       node != 0;
       node = node->next_in_hash){
    if (string_match(string, node->text)){
      result = node;
      break;
    }
  }
  return(result);
}

internal Token_Iterator_Array
token_iterator(Generic_Parse_State *state, Token *token){
  return(token_iterator(state->it.user_id, state->it.tokens, state->it.count, token));
}


////////////////////////////////
// NOTE(allen): Global Code Index

function void
code_index_init(void){
  global_code_index.mutex = system_mutex_make();
  global_code_index.node_arena = make_arena_system(KB(4));
  global_code_index.buffer_to_index_file = make_table_u64_u64(global_code_index.node_arena.base_allocator, 500);
}

function Code_Index_File_Storage*
code_index__alloc_storage(void){
  Code_Index_File_Storage *result = global_code_index.free_storage;
  if (result == 0){
    result = push_array_zero(&global_code_index.node_arena, Code_Index_File_Storage, 1);
  }
  else{
    sll_stack_pop(global_code_index.free_storage);
  }
  zdll_push_back(global_code_index.storage_first, global_code_index.storage_last, result);
  global_code_index.storage_count += 1;
  return(result);
}

function void
code_index__free_storage(Code_Index_File_Storage *storage){
  zdll_remove(global_code_index.storage_first, global_code_index.storage_last, storage);
  global_code_index.storage_count -= 1;
  sll_stack_push(global_code_index.free_storage, storage);
}

function void
code_index_push_nest(Code_Index_Nest_List *list, Code_Index_Nest *nest){
  sll_queue_push(list->first, list->last, nest);
  list->count += 1;
}

function Code_Index_Nest_Ptr_Array
code_index_nest_ptr_array_from_list(Arena *arena, Code_Index_Nest_List *list){
  Code_Index_Nest_Ptr_Array array = {};
  array.ptrs = push_array_zero(arena, Code_Index_Nest*, list->count);
  array.count = list->count;
  i32 counter = 0;
  for (Code_Index_Nest *node = list->first;
       node != 0;
       node = node->next){
    array.ptrs[counter] = node;
    counter += 1;
  }
  return(array);
}

function Code_Index_Note_Ptr_Array
code_index_note_ptr_array_from_list(Arena *arena, Code_Index_Note_List *list){
  Code_Index_Note_Ptr_Array array = {};
  array.ptrs = push_array_zero(arena, Code_Index_Note*, list->count);
  array.count = list->count;
  i32 counter = 0;
  for (Code_Index_Note *node = list->first;
       node != 0;
       node = node->next){
    array.ptrs[counter] = node;
    counter += 1;
  }
  return(array);
}

function void
code_index_lock(void){
  system_mutex_acquire(global_code_index.mutex);
}

function void
code_index_unlock(void){
  system_mutex_release(global_code_index.mutex);
}

function void
code_index__hash_file(Code_Index_File *file){
  for (Code_Index_Note *node = file->root.note_list.first;
       node != 0;
       node = node->next){
    Code_Index_Note_List *list = code_index__list_from_string(node->text);
    zdll_push_back_NP_(list->first, list->last, node, next_in_hash, prev_in_hash);
    list->count += 1;
  }
}

function void
code_index__clear_file(Code_Index_File *file){
  for (Code_Index_Note *node = file->root.note_list.first;
       node != 0;
       node = node->next){
    Code_Index_Note_List *list = code_index__list_from_string(node->text);
    zdll_remove_NP_(list->first, list->last, node, next_in_hash, prev_in_hash);
    list->count -= 1;
  }
}

function void
code_index_set_file(Buffer_ID buffer, Arena arena, Code_Index_File *index){
  Code_Index_File_Storage *storage = 0;
  Table_Lookup lookup = table_lookup(&global_code_index.buffer_to_index_file, buffer);
  if (lookup.found_match){
    u64 val = 0;
    table_read(&global_code_index.buffer_to_index_file, lookup, &val);
    storage = (Code_Index_File_Storage*)IntAsPtr(val);
    code_index__clear_file(storage->file);
    linalloc_clear(&storage->arena);
  }
  else{
    storage = code_index__alloc_storage();
    table_insert(&global_code_index.buffer_to_index_file, buffer, (u64)PtrAsInt(storage));
  }
  storage->arena = arena;
  storage->file = index;

  code_index__hash_file(index);
}

function void
code_index_erase_file(Buffer_ID buffer){
  Table_Lookup lookup = table_lookup(&global_code_index.buffer_to_index_file, buffer);
  if (lookup.found_match){
    u64 val = 0;
    table_read(&global_code_index.buffer_to_index_file, lookup, &val);
    Code_Index_File_Storage *storage = (Code_Index_File_Storage*)IntAsPtr(val);

    code_index__clear_file(storage->file);

    linalloc_clear(&storage->arena);
    table_erase(&global_code_index.buffer_to_index_file, lookup);
    code_index__free_storage(storage);
  }
}

function Code_Index_File*
code_index_get_file(Buffer_ID buffer){
  Code_Index_File *result = 0;
  Table_Lookup lookup = table_lookup(&global_code_index.buffer_to_index_file, buffer);
  if (lookup.found_match){
    u64 val = 0;
    table_read(&global_code_index.buffer_to_index_file, lookup, &val);
    Code_Index_File_Storage *storage = (Code_Index_File_Storage*)IntAsPtr(val);
    result = storage->file;
  }
  return(result);
}

function void
index_shift(i64 *ptr, Range_i64 old_range, u64 new_size){
  i64 i = *ptr;
  if (old_range.min <= i && i < old_range.max){
    *ptr = old_range.first;
  }
  else if (old_range.max <= i){
    *ptr = i + new_size - (old_range.max - old_range.min);
  }
}

function void
code_index_shift(Code_Index_Nest_Ptr_Array *array, Range_i64 old_range, u64 new_size){
  i32 count = array->count;
  Code_Index_Nest **nest_ptr = array->ptrs;
  for (i32 i = 0; i < count; i += 1, nest_ptr += 1){
    Code_Index_Nest *nest = *nest_ptr;
    index_shift(&nest->open.min, old_range, new_size);
    index_shift(&nest->open.max, old_range, new_size);
    if (nest->is_closed){
      index_shift(&nest->close.min, old_range, new_size);
      index_shift(&nest->close.max, old_range, new_size);
    }
    code_index_shift(&nest->nest_array, old_range, new_size);
  }
}

function void
code_index_shift(Code_Index_File *file, Range_i64 old_range, u64 new_size){
  code_index_shift(&file->root.nest_array, old_range, new_size);
}