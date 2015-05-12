#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define print_get_lasterror_string(X)  _print_get_lasterror_string(X, __FILE__, __LINE__)

extern BOOL get_lasterror_string(char *buf, int buf_size);
extern void _print_get_lasterror_string(char *func_name, char *file_name, int line_num);
#ifdef __cplusplus
}
#endif
