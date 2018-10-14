
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap() : root(nullptr), size(0)
{}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &other)
{

}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &&other)
{
    root = other.root;
    size = other.size;
    other.root = nullptr;
    other.size = 0;
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::~Treap()
{
    // TODO : Implement this
}


template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::operator=(Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> other)
{
    // TODO : Implement this
}



template<typename KeyType, typename ValueType , typename PriorityType, class KeyCompare, class PriorityCompare>
unsigned Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::getSize() const
{
    return size;
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare,class PriorityCompare>
bool Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::isEmpty() const
{
    if(size == 0) {
        return true;
    }
    return false;
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::leftRotate(Node *node)
{
    auto parent = node->parent;
    auto A = node;
    auto B = node->right_child;
    auto y = B->left_child;

    if (parent) {
        if (parent->left_child == A) {
            parent->left_child = B;
        }
        else {
            parent->right_child = B;
        }
    }
    else {
        root = B;
    }

    A->right_child = y;
    if (y) {
        y->parent = A;
    }

    B->left_child = A;
    A->parent = B;

    B->parent = parent;
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::rightRotate(Node *node)
{
    auto parent = node->parent;
    auto A = node;
    auto B = node->left_child;
    auto y = B->right_child;

    if (parent) {
        if (parent->left_child == A) {
            parent->left_child = B;
        }
        else {
            parent->right_child = B;
        }
    }
    else {
        root = B;
    }

    A->left_child = y;
    if (y) {
        y->parent = A;
    }

    B->right_child = A;
    A->parent = B;

    B->parent = parent;
}


/* Iterators */

// ctors
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::iterator() : pointer(nullptr)
{}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::iterator(typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Node *node) : pointer(node)
{}
// !ctors



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
const ValueType& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator*() const
{
    return pointer->value;
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator++()
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



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator++(int)
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



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator--()
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



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator--(int)
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



// begin() and end()
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::begin() const
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



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::end() const
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
