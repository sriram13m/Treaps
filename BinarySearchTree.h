#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <ostream>


template<typename KeyType, typename ValueType>
class BinarySearchTree
{
protected:
	struct Node;

public:
	/* Iterator class defnition */
	 class iterator {
	 private:
		Node *pointer;
	 public:
		iterator();
		iterator(Node*);

		const ValueType& operator*() const;
		iterator& operator++();
		iterator& operator--();
		iterator& operator++(int);
		iterator& operator--(int);

		friend bool operator==(const BinarySearchTree<KeyType, ValueType>::iterator &iterator_1, const BinarySearchTree<KeyType, ValueType>::iterator &iterator_2) {
			if (iterator_1.pointer == iterator_2.pointer) {
				return true;
			}
			return false;
		}
		friend bool operator!=(const BinarySearchTree<KeyType, ValueType>::iterator &iterator_1, const BinarySearchTree<KeyType, ValueType>::iterator &iterator_2) {
			if (iterator_1.pointer != iterator_2.pointer) {
				return true;
			}
			return false;
		}
	};
	static const iterator invalid_iterator;

	/* Constructors & Destructors */
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree&);
	BinarySearchTree(BinarySearchTree&&);

	~BinarySearchTree();

	BinarySearchTree& operator=(BinarySearchTree);

	/* Modifiers */
	virtual inline bool insert(const KeyType&, ValueType&&);
	virtual ValueType erase(const KeyType&);

	/* Capacity */
	inline bool isEmpty() const;
	inline unsigned int getSize() const;

	/* Accessors */
	inline iterator search(const KeyType&) const;
	ValueType& operator[](const KeyType&);

	/* Iterators */
	iterator begin() const;
	iterator end() const;

protected:
	struct Node {
		KeyType key;
		ValueType value;
		Node *left_child, *right_child, *parent;

		Node(const KeyType&, ValueType&&, Node*, Node*, Node*);
		Node(const Node&) = delete;
		Node& operator=(Node) = delete;
	};

	Node *root;
	unsigned int size;

	/* Utilites */
	Node* transplant(Node*, Node*);
	Node* insertHelper(const KeyType&);
};


template<typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream&, const BinarySearchTree<KeyType, ValueType>&);


#include "BinarySearchTree.cc"


#endif /* BINARY_SEARCH_TREE_H */
