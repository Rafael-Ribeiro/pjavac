#include <stdlib.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/duplicate.h"

is_type_decl* duplicate_type_decl(is_type_decl* type)
{
	is_type_decl* newtype;
	
	newtype = (is_type_decl*)malloc(sizeof(is_type_decl));
	newtype->type = type->type;
	newtype->line = type->line; /* needed? */

	switch (newtype->type)
	{
		case t_type_decl_type_object:
			newtype->data.type_object = duplicate_type_object(type->data.type_object);
			break;

		case t_type_decl_array_decl:
			newtype->data.array = duplicate_array_decl(type->data.array);
			break;
	}

	return newtype;
}

is_type_object* duplicate_type_object(is_type_object* object)
{
	is_type_object* newobject;
	
	newobject = (is_type_object*)malloc(sizeof(is_type_object));
	newobject->line = object->line;
	newobject->type = object->type;
	
	return newobject;
}

is_array_decl* duplicate_array_decl(is_array_decl* array)
{
	is_array_decl* newarray;

	newarray = (is_array_decl*)malloc(sizeof(is_array_decl));
	newarray->line = array->line;
	newarray->type = duplicate_type_object(array->type);
	newarray->dims = duplicate_dims_empty_list(array->dims);

	return newarray;
}

is_dims_empty_list* duplicate_dims_empty_list(is_dims_empty_list* list)
{
	is_dims_empty_list* newlist;

	newlist = (is_dims_empty_list*)malloc(sizeof(is_dims_empty_list));
	newlist->line = list->line;
	newlist->size = list->size;

	return newlist;
}
