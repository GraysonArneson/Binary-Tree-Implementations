// Project2.cpp : Defines the entry point for the console application.
//
#ifndef _AVL_H_
#define _AVL_H_
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace cop3530 {
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	class AVL {
	public:
		AVL();
		~AVL();
		struct node {
			k key;
			v value;
			node* left;
			node* right;
			int height;
			/*
			node() : left(nullptr), right(nullptr) {}
			node(key, value) : key(key), value(value), left(nullptr), right(nullptr) {}
			*/
		};
		node* root;
		void insert(k key, v value);
		void remove(k key);
		void remove_help(k key);
		v& lookup(k key);
		void rotate_right(node*& root);
		void rotate_left(node*& root);
		void insert_rotate(k key, v value, node*& root);
		int get_Heights(node* temp);
		int max(int curr1, int curr2);
		int getBal(node* n);

		void inorder();
		void inorder_help(node* curr);
		void preorder();
		void preorder_help(node* curr);
		void destruct_help(node*& temp);
	};
	//=========CONSTRUCTOR=======
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	AVL<k, v, compare, equals>::AVL() {
		root = nullptr;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	AVL<k, v, compare, equals>::~AVL() {
		destruct_help(root);
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
		AVL<k, v, compare, equals>::destruct_help(node*& temp) {
		if (temp == nullptr)
			return;
		else {
			destruct_help(temp->left);
			destruct_help(temp->right);
			delete temp;
		}
	}
	//========FUNCTION==========
	//Rotate Left
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::rotate_left(node*& root) {
		node* temp = root->right;
		root->right = temp->left;
		temp->left = root;

		root->height = 1 + max(get_Heights(root->left), get_Heights(root->right));
		temp->height = 1 + max(get_Heights(temp->left), get_Heights(temp->right));

		root = temp;
	}

	//Rotate Right
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::rotate_right(node*& root) {
		node* temp = root->left;
		root->left = temp->right;
		temp->right = root;

		root->height = 1 + max(get_Heights(root->left), get_Heights(root->right));
		temp->height = 1 + max(get_Heights(temp->left), get_Heights(temp->right));

		root = temp;
	}

	//Insert
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::insert(k key, v value) {
		insert_rotate(key, value, root);
	}

	//Insert based on rotation
	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::insert_rotate(k key, v value, node*& temp) {
		if (temp == nullptr) {
			temp = new node;
			temp->key = key;
			temp->value = value;
			temp->left = nullptr;
			temp->right = nullptr;
			temp->height = 1;
			return;
		}
		if (equals(key, temp->key)) {
			temp->value = value;
		}
		else if (compare(key, temp->key)) {
			insert_rotate(key, value, temp->left);
		}
		else {
			insert_rotate(key, value, temp->right);
		}
		//Get height of node
		temp->height = 1 + max(get_Heights(temp->left), get_Heights(temp->right));
		int bal = getBal(temp);
		//Dave's 4 cases for unbalance
		//LL
		if (bal > 1 && compare(key, temp->left->key)) {
			rotate_right(temp);
		}
		//RR
		else if (bal < -1 && compare(temp->right->key, key)) {
			rotate_left(temp);
		}
		//LR
		else if (bal > 1 && compare(temp->left->key, key)) {
			rotate_left(temp->left);
			rotate_right(temp);
		}
		//RL
		else if (bal < -1 && compare(key, temp->right->key)) {
			rotate_right(temp->right);
			rotate_left(temp);
		}
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::remove(k key) {
		remove_help(key);
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::remove_help(k key) {
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
		else
			throw std::runtime_error("Valid key not found");
		//Get height of node
		temp->height = 1 + max(get_Heights(temp->left), get_Heights(temp->right));
		int bal = getBal(temp);
		//Dave's 4 cases for unbalance
		//LL
		if (bal > 1 && compare(key, temp->left->key)) {
			rotate_right(temp);
		}
		//RR
		else if (bal < -1 && compare(temp->right->key, key)) {
			rotate_left(temp);
		}
		//LR
		else if (bal > 1 && compare(temp->left->key, key)) {
			rotate_left(temp->left);
			rotate_right(temp);
		}
		//RL
		else if (bal < -1 && compare(key, temp->right->key)) {
			rotate_right(temp->right);
			rotate_left(temp);
		}
		throw std::runtime_error("Valid key not found!");
		return;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	v&
	AVL<k, v, compare, equals>::lookup(k key) {
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
	int
	AVL<k, v, compare, equals>::get_Heights(node* temp) {
		if (temp == nullptr) {
			return 0;
		}
		return temp->height;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	int
	AVL<k, v, compare, equals>::max(int curr1, int curr2) {
		return (curr1 > curr2) ? curr1 : curr2;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	int
	AVL<k, v, compare, equals>::getBal(node* n) {
		if (n == nullptr) {
			return 0;
		}
		return get_Heights(n->left) - get_Heights(n->right);
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::inorder() {
		inorder_help(root);
		std::cout << std::endl;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::inorder_help(node* curr) {
		if (curr) {
			inorder_help(curr->left);
			cout << curr->value << " ";
			inorder_help(curr->right);
		}
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::preorder() {
		preorder_help(root);
		std::cout << std::endl;
	}

	template <typename k, typename v, bool(*compare)(const k&, const k&), bool(*equals)(const k&, const k&)>
	void
	AVL<k, v, compare, equals>::preorder_help(node* curr) {
		if (curr) {
			cout << curr->value << " ";
			preorder_help(curr->left);
			preorder_help(curr->right);
		}
	}
};
#endif

