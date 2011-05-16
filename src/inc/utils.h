#ifndef UTILS_H
#define UTILS_H

int max(int x, int y);

int pretty_error(int line, char* format, ...);
char* __strdup(const char* data);

bool type_int_like(is_type_decl* s_type);
bool type_bool_like(is_type_decl* s_type);

#endif
