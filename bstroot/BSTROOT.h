// Project2.cpp : Defines the entry point for the console application.
//
#ifndef _BSTROOT_H_
#define _BSTROOT_H_
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace cop3530 {
	 template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	class BSTROOT {
	public:
		BSTROOT();
		~BSTROOT();
		struct node {
			k key;
			v value;
			node* left;
			node* right;
		};
		node* root;
		void insert(k key, v value);
		void remove(k key);
		v& lookup(k key);
		void rotate_right(node*& curr);
		void rotate_left(node*& curr);
		void insert_at_root(k key, v value, node*& temp);
		void inorder();
		void inorder_help(node* curr);
		void destruct_help(node*& temp);
	};
	//=========CONSTRUCTOR=======
	 template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	BSTROOT<k, v, compare, equals>::BSTROOT() {
		root = nullptr;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	BSTROOT<k, v, compare, equals>::~BSTROOT() {
		destruct_help(root);
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::destruct_help(node*& temp) {
		if (temp == nullptr)
			return;
		else {
			destruct_help(temp->left);
			destruct_help(temp->right);
			delete temp;
		}
	}
	//========FUNCTIONS==========
	 template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::rotate_left(node*& curr) {
		node* temp = curr;
		curr = curr->right;
		temp->right = curr->left;
		curr->left = temp;
	}

	 template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::rotate_right(node*& curr) {
		node* temp = curr;
		curr = curr->left;
		temp->left = curr->right;
		curr->right = temp;
	}

	 template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::insert(k key, v value) {
		if (root == nullptr) {
			root = new node;
			root->key = key;
			root->value = value;
			root->left = nullptr;
			root->right = nullptr;
		}
		else
			insert_at_root(key, value, root);
	}

	//Insert_at_root
	 template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::insert_at_root(k key, v value, node*& temp) {
		if (temp == nullptr) {
			temp = new node;
			temp->key = key;
			temp->value = value;
			temp->left = nullptr;
			temp->right = nullptr;
			return;
		}
		//If key is not unique, replace value
		if (equals(key, temp->key)) {
			temp->value = value;
		}
		//Actual insert if unique key
		else if (compare(key, temp->key)) {
			insert_at_root(key, value, temp->left);
			rotate_right(temp);
		}
		else {
			insert_at_root(key, value, temp->right);
			rotate_left(temp);
		}
	}
	//Remove
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::remove(k key) {
		if (root == nullptr) {
			throw std::runtime_error("Empty tree, no nodes to remove");
		}
		node* temp = root;
		node* prev = temp;
		bool found = false;
		int i = 0;
		while (found == false) {
			if (temp == nullptr) {
				break;
			}
			if (equals(key, temp->key))
				found = true;
			else if (compare(key, temp->key)) {
				prev = temp;
				temp = temp->left;
			}
			else if (compare(temp->key, key)) {
				prev = temp;
				temp = temp->right;
			}
		}
		cout << endl;
		if (found == true) {
			//Case if deleting a leaf
			//
			if (temp->left == nullptr && temp->right == nullptr) {
				if (temp == root) {
					root = nullptr;
				}
				else if (prev->left == temp)
					prev->left = nullptr;
				else
					prev->right = nullptr;
				delete temp;
				return;
			}
			//Case if deleting node with one child
			else if ((temp->left == nullptr && temp->right) || (temp->left && temp->right == nullptr)) {
				//Node that we're replacing has a left child
				if (temp->left && temp->right == nullptr) {
					if (temp == root) {
						root = temp->left;
					}
					else if (prev->left == temp)
						prev->left = temp->left;
					else
						prev->right = temp->left;
				}
				//Node that we're replacing has a right child
				else {
					if (temp == root) {
						root = temp->right;
					}
					else if (prev->left == temp)
						prev->left = temp->right;
					else
						prev->right = temp->right;
				}
				delete temp;
				return;
			}
			//Node to remove has two children
			else {
				node* temp_right = temp->right;
				//Nodes right child has no children
				if (!(temp_right->left) && !(temp_right->right)) {
					temp->key = temp_right->key;
					temp->value = temp_right->value;
					delete temp_right;
					temp->right = nullptr;
					return;
				}
				//Nodes right child has children
				else {
					if (temp_right->left) {
						node* mem = root;
						bool toMem = false;
						node* temp_left_prev = temp->right;
						node* temp_left = temp_right->left;
						while (temp_left->left) {
							temp_left_prev = temp_left;
							temp_left = temp_left->left;
						}
						temp->key = temp_left->key;
						temp->value = temp_left->value;
						if (temp_left->right) {
							mem = temp_left->right;
							toMem = true;
						}
						delete temp_left;
						if (toMem == true) {
							temp_left_prev->left = mem;
						}
						else
							temp_left_prev->left = nullptr;
						return;
					}
					else {
						node* change = temp->right;
						temp->key = change->key;
						temp->value = change->value;
						temp->right = change->right;
						delete change;
						return;
					}
				}
			}
		}
		throw std::runtime_error("Key to delete not found!");
		return;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	v&
	BSTROOT<k, v, compare, equals>::lookup(k key) {
		if (root == nullptr) {
			throw std::runtime_error("Empty tree, no nodes to look up");
		}
		node* temp = root;
		bool found = false;
		while (!found) {
			if (temp == nullptr) {
				break;
			}
			if (equals(key, temp->key))
				found = true;
			else if (compare(key, temp->key))
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (found == true) {
			return temp->value;
		}
		throw std::runtime_error("Key does not exist in the tree");
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::inorder() {
		inorder_help(root);
		std::cout << std::endl;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	BSTROOT<k, v, compare, equals>::inorder_help(node* curr) {
		if (curr) {
			inorder_help(curr->left);
			cout << curr->value << " ";
			inorder_help(curr->right);
		}
	}

};
#endif

