#include <stdio.h>

typedef struct {
	int value;
	node_t * left;
	node_t * right;
} node_t;

node_t * search(node_t * node, int toFind);
node_t * createTree(int firstElem);
void destroyTree(node_t * node);
void insert(node_t * node, int elem);
void delete(node_t node, int elem);


