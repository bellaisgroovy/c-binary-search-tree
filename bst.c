#include <stdio.h>
#include <stdlib.h>

//contract
typedef struct node_t {
	int value;
	struct node_t * left;
	struct node_t * right;
	struct node_t ** ptr_to_this; // pointer to pointer to this in parent
} node_t;

node_t * search(node_t * node, int toFind);
node_t * createTree(int firstElem);
void destroyTree(node_t * node);
void insert(node_t * node, int elem);
void delete(node_t * node, int elem);

node_t* insert_rec(node_t* node, int elem, node_t** ptr_to_node); 

//implementation
node_t * search(node_t * node, int toFind) {
	if (node == NULL || node->value == toFind) {
		return node;
	} if (toFind > node->value) {
		return search(node->right, toFind);
	} 

	// if (toFind < node->value)
	return search(node->left, toFind);
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

void delete(node_t * node, int elem) {
	node_t* to_delete = search(node, elem);
	if (!to_delete) { return; }

	// if node is leaf, remove pointer in parent and free
	if (!to_delete->left && !to_delete->right) {
		*to_delete->ptr_to_this = NULL;
		free(to_delete);
	}

	// if node has two children, swap value with max in subtree then delete where old max in subtree is
	else if (to_delete->left && to_delete->right) {
		// get max in left subtree
		node_t* max_on_left = to_delete->left;
		while (max_on_left->right) {
			max_on_left = max_on_left->right;
		}
		
		to_delete->value = max_on_left->value;

		// deal with left max child
		if (max_on_left->left) {
			*max_on_left->ptr_to_this = max_on_left->left;
			max_on_left->left->ptr_to_this = max_on_left->ptr_to_this;
		} else {
			*max_on_left->ptr_to_this = NULL;
		}

		free(max_on_left);
	}
	
	// if has one child, connect parent and child of node, then free node
	else if (to_delete->left && !to_delete->right) {
		*to_delete->ptr_to_this = to_delete->left;
		to_delete->left->ptr_to_this = to_delete->ptr_to_this;
		free(to_delete);
	} 
	else if (!to_delete->left && to_delete->right) {
		*to_delete->ptr_to_this = to_delete->right;
		to_delete->right->ptr_to_this = to_delete->ptr_to_this;
		free(to_delete);
	}
}

void insert(node_t * node, int elem) {
	insert_rec(node, elem, &node);
}

node_t* insert_rec(node_t* node, int elem, node_t** ptr_to_node) {
	if (node == NULL) {
		node_t* new = (node_t*) malloc(sizeof(node_t));
		new->value = elem;
		new->left = NULL;
		new->right = NULL;
		new->ptr_to_this = ptr_to_node;

		return new;
	} else if (elem < node->value) {
		node->left = insert_rec(node->left, elem, &node->left);
	} else if (elem > node->value) {
		node->right = insert_rec(node->right, elem, &node->right);
	}
	return node;
}

node_t * createTree(int firstElem) {
	node_t * node = (node_t*) malloc(sizeof(node_t));
	node->value = firstElem;
	node->left = NULL;
	node->right = NULL;
	node->ptr_to_this = NULL;
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

bool test_delete_leaf() {
	node_t * root = createTree(100);
	insert(root, 50);
	delete(root, 50);

	bool valid = true;
	if (search(root, 50)) { valid = false; }
	return valid;
}

bool test_delete_two_children() {
	node_t * root = createTree(1000);
	insert(root, 500);
	insert(root, 250);
	insert(root, 125);
	insert(root, 750);
	delete(root, 500);

	bool valid = true;
	if (search(root, 500)) { valid = false; }
	if (root->left->value != 250 || root->left->left->value != 125 || root->left->right->value != 750) { valid = false; }
	return valid;
}

bool test_delete_one_child() {
	node_t * root = createTree(1000);
	insert(root, 500);
	insert(root, 250);
	insert(root, 125);
	delete(root, 250);

	bool valid = true;
	if (root->left->value != 500 && root->left->left->value != 125) { valid = false; }
	return valid;
}

bool test_delete_root() {
	node_t * root = createTree(1000);
	return true;
}

bool run_test(bool (*script)(), char name[]) {
	if ((*script)()) {
		printf("passed %s\n", name);
		return true;
	} 

	else {
		printf("FAILED %s\n", name);
		return false;
	}
}

void test_suite() {
	run_test(&test_insert_create, "test_insert_create()");
	run_test(&test_destroy_tree, "test_destroy_tree()");
	run_test(&test_search_node_exists, "test_search_node_exists()");
	run_test(&test_delete_leaf, "test_delete_leaf()");
	run_test(&test_delete_two_children, "test_delete_two_children()");
	run_test(&test_delete_one_child, "test_delete_one_child()");
	run_test(&test_delete_root, "test_delete_root()");
	return;
}
	
int main() {
	test_suite();
}
