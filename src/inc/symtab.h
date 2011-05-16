#ifndef NODE_H
#define NODE_H

typedef struct _SYMBOL
{
	char *id;
	/* TODO */

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

SYMBOL* symbolNew(char* id /*, ...*/);
void symbolDelete(SYMBOL* symbol);
SYMBOL* symbolLookup(NODE* node, char* id);

SCOPE* scopeNew(SCOPE* parent);
void scopeDelete(SCOPE* scope);
void scopeInsert(SCOPE* scope, SYMBOL *symbol);
SYMBOL* scopeLookup(SCOPE* scope, char *id);

/* AVL utils */
NODE* nodeNew(SYMBOL *symbol);
void nodeDelete(NODE* node);
NODE* nodeInsert(NODE* node, SYMBOL *symbol);

int nodeHeight(NODE* node);
NODE* RightRot(NODE* root, NODE* pivot);
NODE* LeftRot(NODE* root, NODE* pivot);
NODE* LL(NODE* root);
NODE* RR(NODE* root);
NODE* LR(NODE* root);
NODE* RL(NODE* root);

#endif
