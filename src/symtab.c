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
SYMBOL* symbolNew(char* id /*, ...*/)
{
	SYMBOL* symbol = (SYMBOL*)malloc(sizeof(SYMBOL));
	symbol->id = __strdup(id);

	return symbol;
}

void symbolDelete(SYMBOL* symbol)
{
	free(symbol->id);
	/* free(...) */

	free(symbol);
}

SYMBOL* symbolLookup(NODE* node, char* id)
{
	int result = strcmp(id, node->symbol->id);

	if (result < 0)
		return symbolLookup(node->left,id);
	else if (result > 0)
		return symbolLookup(node->right,id);

	return node->symbol;
}

/*
	SCOPES
*/
SCOPE* scopeNew(SCOPE* parent)
{
	SCOPE* scope = (SCOPE*)malloc(sizeof(SCOPE));
	scope->parent = parent;
	scope->node = NULL;

	return scope;
}

void scopeDelete(SCOPE* scope)
{
	nodeDelete(scope->node);
	free(scope);
}

void scopeInsert(SCOPE* scope, SYMBOL* symbol)
{
	scope->node = nodeInsert(scope->node, symbol);
}

SYMBOL* scopeLookup(SCOPE* scope, char *id)
{
	return symbolLookup(scope->node, id);
}

/*
	NODE
*/
NODE* nodeNew(SYMBOL *symbol)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->symbol = symbol;

	node->height = 0;

	node->left = NULL;
	node->right = NULL;

	return node;
}

/*
	SCOPE DELETION
*/

void nodeDelete(NODE* node)
{
	symbolDelete(node->symbol);

	if (node->left)
		nodeDelete(node->left);

	if (node->right)
		nodeDelete(node->right);

	free(node);
}

/*
	SCOPE FUNCTIONS
*/
NODE* nodeInsert(NODE* node, SYMBOL *symbol)
{
	NODE *root;
	int balance;
	int cmp, cmpchild;
	root = node;

	if (node == NULL)
		return nodeNew(symbol);
	
	cmp = strcmp(symbol->id, node->symbol->id);
	if (cmp < 0)
	{	 
		/* Left */
		node->left = nodeInsert(node->left, symbol);
		
		balance = nodeHeight(node->left) - nodeHeight(node->right);
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
		node->right = nodeInsert(node->right, symbol);

		balance = nodeHeight(node->right) - nodeHeight(node->left);		
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

	node->height = max(nodeHeight(node->left), nodeHeight(node->right))+1;
	return root;
}

/*
	SCOPE HELPERS
*/
int nodeHeight(NODE* node)
{
	if (node)
		return node->height;
	else
		return -1;
}

/*
	SCOPE ROTATIONS
*/

/* right rotation is always on the left of the root so we dont need to pass the pivot as a param */
NODE* RightRot(NODE* root, NODE* pivot)
{
	root->left = pivot->right;
	pivot->right = root;	

	/* update heights */
	root->height = max(nodeHeight(root->left), nodeHeight(root->right))+1;
	pivot->height = max(nodeHeight(pivot->left), nodeHeight(pivot->right))+1;

	return pivot;
}

/* same for left */
NODE* LeftRot(NODE* root, NODE* pivot)
{
	root->right = pivot->left;
	pivot->left = root;

	/* update heights */
	root->height = max(nodeHeight(root->left), nodeHeight(root->right))+1;
	pivot->height = max(nodeHeight(pivot->left), nodeHeight(pivot->right))+1;

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
