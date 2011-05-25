#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SYMTAB_C

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/symtab.h"
#include "inc/duplicate.h"
#include "inc/free.h"

/*
	SYMBOLS
*/
SYMBOL* symbol_new_var(char* id, int line, is_type_decl *type)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));

	symbol->id = __strdup(id);
	symbol->type = t_symbol_var;
	symbol->line = line;

	symbol->data.var_data.type = duplicate_type_decl(type);
	symbol->data.var_data.initialized = false;

	return symbol;
}

SYMBOL* symbol_new_func(char* id, int line, is_type_decl *retval, is_func_def_args* args)
{
	int i;
	int length;
	SYMBOL* symbol;
	is_func_def_arg_list* arg;

	symbol = (SYMBOL*)malloc(sizeof(SYMBOL));

	symbol->id = __strdup(id);
	symbol->type = t_symbol_func;
	symbol->line = line;

	symbol->data.func_data.type = duplicate_type_decl(retval);
	if (args)
		length = symbol->data.func_data.nArgs = args->length;
	else
		length = symbol->data.func_data.nArgs = 0;

	symbol->data.func_data.args = (is_func_def_arg**)malloc(sizeof(is_func_def_arg*)*length);
	for (i = 0, arg = args; i < length; i++, arg = arg->next)
		symbol->data.func_data.args[0] = duplicate_func_def_arg(arg->node);

	return symbol;
}

/* TODO: store is_loop_stmt* for code generation */ 
SYMBOL* symbol_new_loop(int line/*, is_loop_stmt* loop*/)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));

	symbol->id = NULL;
	symbol->type = t_symbol_loop;
	symbol->line = line;

	return symbol;
}

SYMBOL* symbol_new_class(char* id, int line)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));
	symbol->id = __strdup(id);
	symbol->type = t_symbol_class;
	symbol->line = line;

	return symbol;
}

void symbol_delete(SYMBOL* symbol)
{
	free(symbol->id);	

	switch (symbol->type)
	{
		case t_symbol_var:
			free_type_decl(symbol->data.var_data.type);
			break;

		case t_symbol_class:
			
			break;

		case t_symbol_loop:
			break;

		case t_symbol_func:
			break;
	}

	free(symbol);
}

SYMBOL* symbol_lookup(NODE* node, char* id)
{
	int result;

	if (!node)
		return NULL;

	result = strcmp(id, node->symbol->id);

	if (result < 0)
		return symbol_lookup(node->left,id);
	else if (result > 0)
		return symbol_lookup(node->right,id);

	return node->symbol;
}

/*
	SCOPES
*/
SCOPE* scope_new(SYMBOL* name,bool global)
{
	int i;

	SCOPE* scope = (SCOPE*)malloc(sizeof(SCOPE));
	scope->parent = NULL;
	scope->global = global;
	scope->symbol = name;

	for (i = 0; i < MAX_SYMBOL_TYPES; i++)
		scope->node[i] = NULL;

	return scope;
}

void scope_push(SCOPE* scope)
{
	scope->parent = symtab;
	symtab = scope;
}

void scope_pop()
{
	symtab = symtab->parent;
}

void scope_delete(SCOPE* scope)
{
	int i;
	for (i = 0; i < MAX_SYMBOL_TYPES; i++)
		node_delete(scope->node[i]);
	free(scope);
}

SYMBOL* scope_insert(SCOPE* scope, SYMBOL* symbol)
{
	scope->node[symbol->type] = node_insert(scope->node[symbol->type], symbol);
	return symbol;
}

SYMBOL* scope_lookup(SCOPE* scope, char *id, type_symbol type)
{
	SYMBOL* symbol = NULL;

	symbol = symbol_lookup(scope->node[type], id);
	if (!symbol && scope->parent)
		return scope_lookup(scope->parent, id, type);

	return symbol;
}

SYMBOL* scope_local_lookup(SCOPE* scope, char *id, type_symbol type)
{
	SYMBOL* symbol = NULL;

	symbol = symbol_lookup(scope->node[type], id);
	if (!symbol && scope->parent && !scope->parent->global)
		return scope_lookup(scope->parent, id, type);

	return symbol;
}

SCOPE* scope_get_by_name(SCOPE* scope, char *id, type_symbol type)
{
	SYMBOL* name = NULL;

	name = scope->symbol;
	if (name && name->type == type && ((id == NULL) || (name-> id  && strcmp(id, name->id) == 0)))
		return scope;

	else if (scope->parent)
		return scope_get_by_name(scope, id, type);
	
	return NULL;
}

/*
	AVL
*/
NODE* node_new(SYMBOL *symbol)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->symbol = symbol;

	node->height = 0;

	node->left = NULL;
	node->right = NULL;

	return node;
}

void node_delete(NODE* node)
{
	if (!node)
		return;

	symbol_delete(node->symbol);

	if (node->left)
		node_delete(node->left);

	if (node->right)
		node_delete(node->right);

	free(node);
}

NODE* node_insert(NODE* node, SYMBOL *symbol)
{
	NODE *root;
	int balance;
	int cmp, cmpchild;
	root = node;

	if (node == NULL)
		return node_new(symbol);
	
	cmp = strcmp(symbol->id, node->symbol->id);
	if (cmp < 0)
	{	 
		/* Left */
		node->left = node_insert(node->left, symbol);
		
		balance = node_height(node->left) - node_height(node->right);
		if (balance == 2)
		{
			cmpchild = strcmp(symbol->id, node->left->symbol->id);
			if (cmpchild < 0)
				root = LL(node);
			else if (cmpchild > 0)
				root = LR(node);
		}

	} else if (cmp > 0)
	{
		/* Right */
		node->right = node_insert(node->right, symbol);

		balance = node_height(node->right) - node_height(node->left);		
		if (balance == 2)
		{
			cmpchild = strcmp(symbol->id, node->right->symbol->id);
			if (cmpchild < 0)
				root = RL(node);
			else if (cmpchild > 0)
				root = RR(node);
		}
 
	}/* else 
	{
		the implementation doesn't allow duplicates, since a lookup is ALWAYS performed first
	} */

	node->height = max(node_height(node->left), node_height(node->right))+1;
	return root;
}

int node_height(NODE* node)
{
	if (node)
		return node->height;
	else
		return -1;
}

/* right rotation is always on the left of the root so we dont need to pass the pivot as a param */
NODE* RightRot(NODE* root, NODE* pivot)
{
	root->left = pivot->right;
	pivot->right = root;	

	/* update heights */
	root->height = max(node_height(root->left), node_height(root->right))+1;
	pivot->height = max(node_height(pivot->left), node_height(pivot->right))+1;

	return pivot;
}

/* same for left */
NODE* LeftRot(NODE* root, NODE* pivot)
{
	root->right = pivot->left;
	pivot->left = root;

	/* update heights */
	root->height = max(node_height(root->left), node_height(root->right))+1;
	pivot->height = max(node_height(pivot->left), node_height(pivot->right))+1;

	return pivot;
}

NODE* LL(NODE* root)
{
	return RightRot(root, root->left);
}

NODE* RR(NODE* root)
{
	return LeftRot(root, root->right);
}

NODE* LR(NODE* root)
{
	root->left = LeftRot(root->left, root->left->right);
	return RightRot(root, root->left);
}

NODE* RL(NODE* root)
{
	root->right = RightRot(root->right, root->right->left);
	return LeftRot(root, root->right);
}
