#ifndef NODE_H
#define NODE_H

typedef enum
{
	t_symbol_var,
	t_symbol_func,
	t_symbol_label,
	t_symbol_class
} type_symbol;

typedef struct _SYMBOL
{
	char *id;
	type_symbol type;

	union
	{
		struct
		{
			is_type_decl *type;
			bool initialized;
		} var;
		struct
		{
			is_type_decl *type;
			int nArgs;
			is_type_decl **args;
		} func;
	} data;
} SYMBOL;

typedef struct _NODE
{
	SYMBOL* symbol;

	/* AVL */
	int height;
	struct _NODE* left;
	struct _NODE* right;
} NODE;

typedef struct _SCOPE
{
	struct _SCOPE *parent;
	NODE *node;
} SCOPE;

/*
	SYMBOLS
*/
SYMBOL* symbol_new(char* id /*, ...*/);
void symbol_delete(SYMBOL* symbol);
SYMBOL* symbol_lookup(NODE* node, char* id);

/*
	SCOPES
*/
SCOPE* scope_new(SCOPE* parent);
void scope_delete(SCOPE* scope);
void scope_insert(SCOPE* scope, SYMBOL* symbol);
SYMBOL* scope_lookup(SCOPE* scope, char *id);

/*
	AVL
*/
NODE* node_new(SYMBOL *symbol);
void node_delete(NODE* node);
NODE* node_insert(NODE* node, SYMBOL *symbol);
int node_height(NODE* node);

NODE* RightRot(NODE* root, NODE* pivot);
NODE* LeftRot(NODE* root, NODE* pivot);
NODE* LL(NODE* root);
NODE* RR(NODE* root);
NODE* LR(NODE* root);
NODE* RL(NODE* root);

#endif
