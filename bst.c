#include <stdio.h>
#include<stdlib.h>

//contract
typedef struct node_t {
	int value;
	struct node_t * left;
	struct node_t * right;
} node_t;

node_t * search(node_t * node, int toFind) {
	if (node->left) {
		node_t* found_node = search(node->left, toFind);
		if (found_node) { return found_node; }
	}
	if (node->right) {
		node_t* found_node = search(node->right, toFind);
		if (found_node) { return found_node; }

	}
	if (node->value == toFind) {
		return node;
	} else {
		return NULL;
	}
}

void destroyTree(node_t * node) {
	if (node->left) {
		destroyTree(node->left);
	}
	if (node->right) {
		destroyTree(node->right);
	}
	free(node);
}

void delete(node_t node, int elem);

void insert(node_t * node, int elem) {
	node_t * current = node;

	node_t* new = malloc(sizeof(node_t));
	new->value = elem;

	while (1) {
		if (current->value == elem) {
			return;
		}

		else if (elem < current->value) {
			if (current->left == NULL) {
				current->left = new;
				return;
			} else {
				current = current->left;
			}
		} 

		else {
			if (current->right == NULL) {
				current->right = new;
				return;
			} else {
				current = current->right;
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

bool test_insert_create() {
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

bool test_destroy_tree() {
	node_t * node = createTree(99);
	insert(node, 102);
	insert(node, 5);
	insert(node, -99);
	insert(node, 8);
	insert(node, 14);

	destroyTree(node);
	
	return true;
}

bool test_search_node_exists() {
	node_t * node = createTree(100);
	insert(node, 50);
	insert(node, 25);
	insert(node, 75);
	insert(node, 150);
	insert(node, 125);
	insert(node, 175);

	bool valid = true;
	if(!search(node, 25)) { valid = false; }
	if(!search(node, 150)) {valid = false; }
	return valid;
}

int test_suite() {
	bool valid = true;
	if (!test_insert_create()) {valid = false; printf("test_insert_create() failed\n");} else {printf("test_insert_create() passed\n");}
	if (!test_destroy_tree()) {valid = false; printf("test_destroy_tree() failed\n");} else {printf("test_destroy_tree() passed\n");}
	if (!test_search_node_exists()) {valid = false; printf("test_search_node_exists() failed\n");} else {printf("test_search_node_exists() passed\n");}
	return valid;
}
	
int main() {
	test_suite();
}
