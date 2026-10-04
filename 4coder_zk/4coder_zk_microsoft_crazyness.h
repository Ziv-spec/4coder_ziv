/* date = October 4th 2026 8:48 pm */

#ifndef ZK_MICROSOFT_CRAZYNESS_H
#define ZK_MICROSOFT_CRAZYNESS_H

// NOTE(ziv): I basically just copied his code, thanks Jon!

#if OS_WINDOWS
#pragma comment(lib, "Advapi32.lib")
#pragma warning(disable: 4267)

// From:     https://github.com/janivanecky/builder/blob/master/microsoft_craziness.h
// Author:   Jonathan Blow
// Version:  1
// Date:     31 August, 2018
//
// This code is released under the MIT license, which you can find at
//
//          https://opensource.org/licenses/MIT
//
//
//
// See the comments for how to use this library just below the includes.
//

#include <windows.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// The beginning of the actual code that does things.

typedef struct {
  int32_t best_version[4];  // For Windows 8 versions, only two of these numbers are used.
  wchar_t *best_name;
} Version_Data;

bool os_file_exists(wchar_t *name) {
  // @Robustness: What flags do we really want to check here?

  auto attrib = GetFileAttributesW(name);
  if (attrib == INVALID_FILE_ATTRIBUTES) return false;
  if (attrib & FILE_ATTRIBUTE_DIRECTORY) return false;

  return true;
}

#define concat2(a, b) concat(a, b, NULL, NULL)
#define concat3(a, b, c) concat(a, b, c, NULL)
#define concat4(a, b, c, d) concat(a, b, c, d)
wchar_t *concat(wchar_t *a, wchar_t *b, wchar_t *c, wchar_t *d) {
  // Concatenate up to 4 wide strings together. Allocated with malloc.
  // If you don't like that, use a programming language that actually
  // helps you with using custom allocators. Or just edit the code.

  auto len_a = wcslen(a);
  auto len_b = wcslen(b);

  auto len_c = 0;
  if (c) len_c = wcslen(c);

  auto len_d = 0;
  if (d) len_d = wcslen(d);

  wchar_t *result = (wchar_t *)malloc((len_a + len_b + len_c + len_d + 1) * 2);
  memcpy(result, a, len_a*2);
  memcpy(result + len_a, b, len_b*2);

  if (c) memcpy(result + len_a + len_b, c, len_c * 2);
  if (d) memcpy(result + len_a + len_b + len_c, d, len_d * 2);

  result[len_a + len_b + len_c + len_d] = 0;

  return result;
}

typedef void (*Visit_Proc_W)(wchar_t *short_name, wchar_t *full_name, Version_Data *data);
bool visit_files_w(wchar_t *dir_name, Version_Data *data, Visit_Proc_W proc) {

  // Visit everything in one folder (non-recursively). If it's a directory
  // that doesn't start with ".", call the visit proc on it. The visit proc
  // will see if the filename conforms to the expected versioning pattern.

  WIN32_FIND_DATAW find_data;

  wchar_t *wildcard_name = concat2(dir_name, L"\\*");
  HANDLE handle = FindFirstFileW(wildcard_name, &find_data);
  free(wildcard_name);

  if (handle == INVALID_HANDLE_VALUE) return false;

  while (true) {
    if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (find_data.cFileName[0] != '.')) {
      wchar_t *full_name = concat3(dir_name, L"\\", find_data.cFileName);
      proc(find_data.cFileName, full_name, data);
      free(full_name);
    }

    BOOL success = FindNextFileW(handle, &find_data);
    if (!success) break;
  }

  FindClose(handle);

  return true;
}

wchar_t *find_windows_kit_root_with_key(HKEY key, wchar_t *version) {
  // Given a key to an already opened registry entry,
  // get the value stored under the 'version' subkey.
  // If that's not the right terminology, hey, I never do registry stuff.

  DWORD required_length;
  auto rc = RegQueryValueExW(key, version, NULL, NULL, NULL, &required_length);
  if (rc != 0)  return NULL;

  DWORD length = required_length + 2;  // The +2 is for the maybe optional zero later on. Probably we are over-allocating.
  wchar_t *value = (wchar_t *)malloc(length);
  if (!value)  return NULL;

  rc = RegQueryValueExW(key, version, NULL, NULL, (LPBYTE)value, &length);  // We know that version is zero-terminated...
  if (rc != 0)  return NULL;

  // The documentation says that if the string for some reason was not stored
  // with zero-termination, we need to manually terminate it. Sigh!!

  if (value[length/2]) {
    value[length/2] = 0;
  }

  return value;
}

void win10_best(wchar_t *short_name, wchar_t *full_name, Version_Data *data) {
  // Find the Windows 10 subdirectory with the highest version number.

  int i0, i1, i2, i3;
  auto success = swscanf_s(short_name, L"%d.%d.%d.%d", &i0, &i1, &i2, &i3);
  if (success < 4) return;

  if (i0 < data->best_version[0]) return;
  else if (i0 == data->best_version[0]) {
    if (i1 < data->best_version[1]) return;
    else if (i1 == data->best_version[1]) {
      if (i2 < data->best_version[2]) return;
      else if (i2 == data->best_version[2]) {
        if (i3 < data->best_version[3]) return;
      }
    }
  }

  // we have to copy_string and free here because visit_files free's the full_name string
  // after we execute this function, so Win*_Data would contain an invalid pointer.
  if (data->best_name) free(data->best_name);
  data->best_name = _wcsdup(full_name);

  if (data->best_name) {
    data->best_version[0] = i0;
    data->best_version[1] = i1;
    data->best_version[2] = i2;
    data->best_version[3] = i3;
  }
}

void win8_best(wchar_t *short_name, wchar_t *full_name, Version_Data *data) {
  // Find the Windows 8 subdirectory with the highest version number.

  int i0, i1;
  auto success = swscanf_s(short_name, L"winv%d.%d", &i0, &i1);
  if (success < 2) return;

  if (i0 < data->best_version[0]) return;
  else if (i0 == data->best_version[0]) {
    if (i1 < data->best_version[1]) return;
  }

  // we have to copy_string and free here because visit_files free's the full_name string
  // after we execute this function, so Win*_Data would contain an invalid pointer.
  if (data->best_name) free(data->best_name);
  data->best_name = _wcsdup(full_name);

  if (data->best_name) {
    data->best_version[0] = i0;
    data->best_version[1] = i1;
  }
}

// NOTE(ziv): I only modified from searching "Lib" as a root to "Include"
wchar_t *find_windows_kit_root() {
  // Information about the Windows 10 and Windows 8 development kits
  // is stored in the same place in the registry. We open a key
  // to that place, first checking preferntially for a Windows 10 kit,
  // then, if that's not found, a Windows 8 kit.

  HKEY main_key;

  LSTATUS rc = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots",
                             0, KEY_QUERY_VALUE | KEY_WOW64_32KEY | KEY_ENUMERATE_SUB_KEYS, &main_key);
  if (rc != S_OK) return NULL;

  // Look for a Windows 10 entry.
  wchar_t *windows10_root = find_windows_kit_root_with_key(main_key, L"KitsRoot10");

  if (windows10_root) {
    wchar_t *windows10_lib = concat2(windows10_root, L"Include");
    free(windows10_root);

    Version_Data data = {};
    visit_files_w(windows10_lib, &data, win10_best);
    free(windows10_lib);

    if (data.best_name) {
      RegCloseKey(main_key);
      return data.best_name;
    }
  }

  // Look for a Windows 8 entry.
  wchar_t *windows8_root = find_windows_kit_root_with_key(main_key, L"KitsRoot81");

  if (windows8_root) {
    wchar_t *windows8_lib = concat2(windows8_root, L"Include");
    free(windows8_root);

    Version_Data data = {0};
    visit_files_w(windows8_lib, &data, win8_best);
    free(windows8_lib);

    if (data.best_name) {
      RegCloseKey(main_key);
      return data.best_name;
    }
  }

  // If we get here, we failed to find anything.
  RegCloseKey(main_key);
  return NULL;
}

#pragma warning(default: 4267)
#endif


#endif //ZK_MICROSOFT_CRAZYNESS_H
