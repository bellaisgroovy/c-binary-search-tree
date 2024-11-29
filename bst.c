#include <stdio.h>
#include<stdlib.h>

//contract
typedef struct node_t {
	int value;
	struct node_t * left;
	struct node_t * right;
} node_t;

node_t * search(node_t * node, int toFind);
void destroyTree(node_t * node);
void delete(node_t node, int elem);

void insert(node_t * node, int elem) {
	node_t * current = node;

	node_t* new = malloc(sizeof(node_t));
	new->value = elem;

	while (1) {
		if (current->value == elem) {
			printf("current value = elem\n");
			return;
		}

		else if (elem < current->value) {
			if (current->left == NULL) {
				current->left = new;
				printf("inserting at left\n");
				return;
			} else {
				current = current->left;
				printf("navigating left\n");
			}
		} 

		else {
			if (current->right == NULL) {
				printf("inserting at right\n");
				current->right = new;
				return;
			} else {
				current = current->right;
				printf("navigating right\n");
			}
		}
	}
}

node_t * createTree(int firstElem) {
	node_t * node = (node_t*) malloc(sizeof(node_t));
	node->value = firstElem;
	return node;
}

#include <stdbool.h>

int test_insert_create() {
	node_t * node = createTree(3);
	insert(node, 2);
	insert(node, 1);
	insert(node, 5);
	insert(node, 4);
	
	bool valid = true;
	if (node->left->value != 2) {valid = false;}
	if (node->left->left->value != 1) {valid = false;}
	if (node->right->value != 5) {valid = false;}
	if (node->right->left->value != 4) {valid = false;}
	return valid;
}

int test_suite() {
	bool valid = true;
	if (!test_insert_create()) {valid = false; printf("test_insert_create() failed\n");} else {printf("test_insert_create() passed\n");}
	return valid;
}
	
int main() {
	test_suite();
}
