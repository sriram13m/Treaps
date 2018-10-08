#include "../DSA/Stack.h"
#include <utility>



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::Node::Node(const KeyType &key, ValueType &&value, Node *left_child, Node *right_child, Node *parent)
{
	this->key = key;
	this->value = value;
	this->left_child = left_child;
	this->right_child = right_child;
	this->parent = parent;
}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree()
{
	this->root = nullptr;
	this->size = 0;
}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree(const BinarySearchTree &other)
{
	this->size = other.size;
	if (other.size == 0) {
		this->root = nullptr;
		return;
	}
	this->root = new Node(other.root->key, ValueType(other.root->value), nullptr, nullptr, nullptr);

	data_structures::Stack<BinarySearchTree::Node *> parent_stack, other_tree_parent_stack;
	Node *other_tree_iterator = other.root;
	Node *tree_iterator = this->root;
	parent_stack.push(this->root);
	other_tree_parent_stack.push(other.root);
	while (!parent_stack.isEmpty())
	{
		if (other_tree_iterator->left_child != nullptr) {
			tree_iterator->left_child = new Node(other_tree_iterator->left_child->key, ValueType(other_tree_iterator->left_child->value), nullptr, nullptr, tree_iterator);
			parent_stack.push(tree_iterator->left_child);
			other_tree_parent_stack.push(other_tree_iterator->left_child);
		}
		if (other_tree_iterator->right_child != nullptr) {
			tree_iterator->right_child = new Node(other_tree_iterator->right_child->key, ValueType(other_tree_iterator->right_child->value), nullptr, nullptr, tree_iterator);
			parent_stack.push(tree_iterator->right_child);
			other_tree_parent_stack.push(other_tree_iterator->right_child);
		}
		other_tree_iterator = other_tree_parent_stack.pop();
		tree_iterator = parent_stack.pop();
	}
}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree(BinarySearchTree &&other)
{
	this->size = other.size;
	this->root = other.root;
	other.root = nullptr;
	other.size = 0;
}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>& BinarySearchTree<KeyType, ValueType>::operator=(BinarySearchTree<KeyType, ValueType> other)
{
	swap(other, *this);
	return *this;
}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::~BinarySearchTree()
{
	Node *tree_iterator = this->root;

	data_structures::Stack<std::pair<BinarySearchTree::Node *, bool>> parent_stack;

	while (tree_iterator) {
		if (tree_iterator->left_child == nullptr && tree_iterator->right_child == nullptr) {
			delete tree_iterator;
			try {
				auto parent = parent_stack.pop();
				tree_iterator = parent.first;
				if (parent.second) {
					tree_iterator->left_child = nullptr;
				}
				else {
					tree_iterator->right_child = nullptr;
				}
				continue;
			}
			catch (...) {
				break;
			}
		}

		if (tree_iterator->left_child != nullptr) {
			parent_stack.push(std::make_pair(tree_iterator, true));
			tree_iterator = tree_iterator->left_child;
		}
		else if (tree_iterator->right_child != nullptr) {
			parent_stack.push(std::make_pair(tree_iterator, false));
			tree_iterator = tree_iterator->right_child;
		}
	}
}



template<typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::isEmpty() const
{
	if (this->size == 0) {
		return true;
	}
	return false;
}



template<typename KeyType, typename ValueType>
unsigned int BinarySearchTree<KeyType, ValueType>::getSize() const
{
	return this->size;
}



/* Modifiers */

template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node* BinarySearchTree<KeyType, ValueType>::insertHelper(const KeyType &key)
{
	Node *node = this->root;

	while (true) {
		if (key < node->key && node->left_child != nullptr) {
			node = node->left_child;
			continue;
		}
		if (key >= node->key && node->right_child != nullptr) {
			node = node->right_child;
			continue;
		}
		break;
	}

	return node;
}



template<typename KeyType, typename ValueType>
inline bool BinarySearchTree<KeyType, ValueType>::insert(const KeyType &key, ValueType &&value)
{
	if (this->root == nullptr) {
		this->root = new Node(key, std::move(value), nullptr, nullptr, nullptr);
		this->size++;
		return this->root;
	}

	auto node = insertHelper(key);

	if (key < node->key) {
		node->left_child = new Node(key, std::move(value), nullptr, nullptr, node);
	}
	else {
		node->right_child = new Node(key, std::move(value), nullptr, nullptr, node);
	}

	this->size++;
	return true;
}



template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node* BinarySearchTree<KeyType, ValueType>::transplant(typename BinarySearchTree<KeyType, ValueType>::Node *node_1, typename BinarySearchTree<KeyType, ValueType>::Node *node_2)
{
	if (node_1->parent == nullptr) {
		this->root = node_2;
	}
	else if (node_1 == node_1->parent->left_child) {
		node_1->parent->left_child = node_2;
	}
	else {
		node_1->parent->right_child = node_2;
	}

	if (node_2 != nullptr) {
		node_2->parent = node_1->parent;
	}

	return node_1;
}



template<typename KeyType, typename ValueType>
ValueType BinarySearchTree<KeyType, ValueType>::erase(const KeyType &key)
{
	if (this->root == nullptr) {
		throw "Element not found";
	}

	Node *tree_iterator = this->root;

	while (true) {
		if (key < tree_iterator->key && tree_iterator->left_child != nullptr) {
			tree_iterator = tree_iterator->left_child;
			continue;
		}
		if (key > tree_iterator->key && tree_iterator->right_child != nullptr) {
			tree_iterator = tree_iterator->right_child;
			continue;
		}
		break;
	}

	if (key == tree_iterator->key) {
		if (tree_iterator->left_child == nullptr) {
			Node *node_to_erase = transplant(tree_iterator, tree_iterator->right_child);
			ValueType deleted_element(std::move(node_to_erase->value));
			--(this->size);
			delete node_to_erase;
			return deleted_element;
		}
		else if (tree_iterator->right_child == nullptr) {
			Node *node_to_erase = transplant(tree_iterator, tree_iterator->left_child);
			ValueType deleted_element(std::move(node_to_erase->value));
			--(this->size);
			delete node_to_erase;
			return deleted_element;
		}
		else {
			Node *y = tree_iterator->right_child;
			while (y->left_child != nullptr) {
				y = y->left_child;
			}

			if (y->parent != tree_iterator) {
				transplant(y, y->right_child);
				y->right_child = tree_iterator->right_child;
				y->right_child->parent = y;
			}
			Node *node_to_erase = transplant(tree_iterator, y);
			ValueType deleted_element(std::move(node_to_erase->value));
			y->left_child = tree_iterator->left_child;
			y->left_child->parent = y;
			--(this->size);
			delete node_to_erase;
			return deleted_element;
		}
	}

	throw "Element not found";
}



/* Accessors */

template<typename KeyType, typename ValueType>
inline typename BinarySearchTree<KeyType, ValueType>::iterator BinarySearchTree<KeyType, ValueType>::search(const KeyType &key) const
{
	Node *node = this->root;

	while (node) {
		if (key == node->key) {
			return iterator(node);
		}
		if (key < node->key) {
			node = node->left_child;
			continue;
		}
		if (key > node->key) {
			node = node->right_child;
			continue;
		}
		break;
	}

	return iterator(nullptr);
}



template<typename KeyType, typename ValueType>
ValueType& BinarySearchTree<KeyType, ValueType>::operator[](const KeyType &key)
{
	Node *tree_iterator = this->root;

	while (tree_iterator) {
		if (key == tree_iterator->key) {
			return tree_iterator->value;
		}
		if (key < tree_iterator->key) {
			tree_iterator = tree_iterator->left_child;
			continue;
		}
		if (key > tree_iterator->key) {
			tree_iterator = tree_iterator->right_child;
			continue;
		}
		break;
	}

	if (tree_iterator == nullptr) {
		throw "Element not found";
	}
	return tree_iterator->value;
}



/* Iterators */

template<typename KeyType, typename ValueType>
const typename BinarySearchTree<KeyType, ValueType>::iterator BinarySearchTree<KeyType, ValueType>::invalid_iterator = {nullptr};


template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator BinarySearchTree<KeyType, ValueType>::begin() const
{
	if (this->root == nullptr) {
		return iterator(nullptr);
	}

	Node *tree_iterator = this->root;

	while (tree_iterator->left_child != nullptr) {
		tree_iterator = tree_iterator->left_child;
	}

	return iterator(tree_iterator);
}



template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator BinarySearchTree<KeyType, ValueType>::end() const
{
	if (this->root == nullptr) {
		return iterator(nullptr);
	}

	Node *tree_iterator = this->root;

	while (tree_iterator->right_child != nullptr) {
		tree_iterator = tree_iterator->right_child;
	}

	return iterator(tree_iterator);
}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::iterator::iterator() : pointer(nullptr){}



template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::iterator::iterator(Node *pointer)
{
	this->pointer = pointer;
}



template<typename KeyType, typename ValueType>
const ValueType& BinarySearchTree<KeyType, ValueType>::iterator::operator*(void) const
{
	return this->pointer->value;
}



template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator& BinarySearchTree<KeyType, ValueType>::iterator::operator++()
{
	if (this->pointer->right_child != nullptr) {
		Node *tree_iterator = this->pointer->right_child;

		while (tree_iterator->left_child != nullptr) {
			tree_iterator = tree_iterator->left_child;
		}

		this->pointer = tree_iterator;
		return *this;
	}

	Node *tree_iterator = this->pointer->parent;
	while (tree_iterator != nullptr && this->pointer == tree_iterator->right_child) {
		this->pointer = tree_iterator;
		tree_iterator = tree_iterator->parent;
	}

	this->pointer = tree_iterator;
	return *this;
}



template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator& BinarySearchTree<KeyType, ValueType>::iterator::operator++(int)
{
	if (this->pointer->right_child != nullptr) {
		Node *tree_iterator = this->pointer->right_child;

		while (tree_iterator->left_child != nullptr) {
			tree_iterator = tree_iterator->left_child;
		}

		this->pointer = tree_iterator;
		return *this;
	}

	Node *tree_iterator = this->pointer->parent;
	while (tree_iterator != nullptr && this->pointer == tree_iterator->right_child) {
		this->pointer = tree_iterator;
		tree_iterator = tree_iterator->parent;
	}

	auto old_pointer{this->pointer};
	this->pointer = tree_iterator;
	return old_pointer;
}



template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator& BinarySearchTree<KeyType, ValueType>::iterator::operator--()
{
	if (this->pointer->left_child != nullptr) {
		Node *tree_iterator = this->pointer->left_child;

		while (tree_iterator->right_child != nullptr) {
			tree_iterator = tree_iterator->right_child;
		}

		this->pointer = tree_iterator;
		return *this;
	}

	Node *tree_iterator = this->pointer->parent;
	while (tree_iterator != nullptr && this->pointer == tree_iterator->left_child) {
		this->pointer = tree_iterator;
		tree_iterator = tree_iterator->parent;
	}

	this->pointer = tree_iterator;
	return *this;
}



template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator& BinarySearchTree<KeyType, ValueType>::iterator::operator--(int)
{
	if (this->pointer->left_child != nullptr) {
		Node *tree_iterator = this->pointer->left_child;

		while (tree_iterator->right_child != nullptr) {
			tree_iterator = tree_iterator->right_child;
		}

		this->pointer = tree_iterator;
		return *this;
	}

	Node *tree_iterator = this->pointer->parent;
	while (tree_iterator != nullptr && this->pointer == tree_iterator->left_child) {
		this->pointer = tree_iterator;
		tree_iterator = tree_iterator->parent;
	}

	auto old_pointer{this->pointer};
	this->pointer = tree_iterator;
	return old_pointer;
}



template<typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream &out, const BinarySearchTree<KeyType, ValueType> &tree)
{
	typename BinarySearchTree<KeyType, ValueType>::iterator tree_iterator = tree.begin();
	register unsigned int max = tree.getSize();
	
	for (register unsigned int i = 0; i < max; ++i) {
		out << *tree_iterator << " ";
		++tree_iterator;
	}

	return out;
}
