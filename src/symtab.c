#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/symtab.h"

/*
	SYMBOLS
*/
SYMBOL* symbol_new_var(char* id, is_type_decl *type)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));

	symbol->id = __strdup(id);
	symbol->type = t_symbol_var;

	symbol->data.var.type = type;
	symbol->data.var.initialized = false;

	return symbol;
}

SYMBOL* symbol_new_func(char* id /*, ...*/)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));
	symbol->id = __strdup(id);
	symbol->type = t_symbol_func;

	/* TODO */

	return symbol;
}

SYMBOL* symbol_new_label(char* id /*, ...*/)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));
	symbol->id = __strdup(id);
	symbol->type = t_symbol_label;

	/* TODO */

	return symbol;
}

SYMBOL* symbol_new_class(char* id /*, ...*/)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));
	symbol->id = __strdup(id);
	symbol->type = t_symbol_class;

	/* TODO */

	return symbol;
}

void symbol_delete(SYMBOL* symbol)
{
	free(symbol->id);
	/* free(...) */

	free(symbol);
}

SYMBOL* symbol_lookup(NODE* node, char* id)
{
	int result = strcmp(id, node->symbol->id);

	if (result < 0)
		return symbol_lookup(node->left,id);
	else if (result > 0)
		return symbol_lookup(node->right,id);

	return node->symbol;
}

/*
	SCOPES
*/
SCOPE* scope_new(SCOPE* parent)
{
	SCOPE* scope = (SCOPE*)malloc(sizeof(SCOPE));
	scope->parent = parent;
	scope->node = NULL;

	return scope;
}

void scope_delete(SCOPE* scope)
{
	node_delete(scope->node);
	free(scope);
}

void scope_insert(SCOPE* scope, SYMBOL* symbol)
{
	scope->node = node_insert(scope->node, symbol);
}

SYMBOL* scope_lookup(SCOPE* scope, char *id)
{
	return symbol_lookup(scope->node, id);
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
