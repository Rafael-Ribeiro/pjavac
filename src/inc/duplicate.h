#ifndef DUPLICATE_H
#define DUPLICATE_H

is_type_decl* duplicate_type_decl(is_type_decl* type);
is_type_object* duplicate_type_object(is_type_object* object);
is_array_decl* duplicate_array_decl(is_array_decl* array);
is_type_decl * encapsulate_type_decl(is_type_decl *type);
is_dims_empty_list* duplicate_dims_empty_list(is_dims_empty_list* list);
is_func_def_arg* duplicate_func_def_arg(is_func_def_arg* arg);
is_id* duplicate_id(is_id *id);

#endif
