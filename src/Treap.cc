/* Node defnition */
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Node::Node(const KeyType &key, ValueType &&value, const PriorityType &priority, Node *left_child, Node *right_child, Node *parent) : key(key), value(value), priority(priority), left_child(left_child), right_child(right_child), parent(parent)
{}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Node::Node(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Node &other)
{
    key = other.key;
    value = other.value;
    priority = other.priority;
    left_child = other.left_child;
    right_child = other.right_child;
    parent = other.parent;
}
/* End Node defnition */



// ctors and dtors
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap() : root(nullptr), size(0)
{}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &other)
{
    size = other.size;
    if(other.root == nullptr)
    {
        root = nullptr;
        return;
    }
    root = other.root;
    Node* node_ptr = root;
    Node* other_ptr = other.root;
    while(other_ptr != nullptr)
    {
        if(other_ptr->left_child != nullptr && node_ptr->left_child == nullptr )
        {
            node_ptr->left_child =  other_ptr->left_child;
            node_ptr = node_ptr->left_child;
            other_ptr = other_ptr->left_child;
        }
        else if(other_ptr->right_child != nullptr && node_ptr->right_child == nullptr)
        {
            node_ptr->right_child =  other_ptr->right_child;
            node_ptr = node_ptr->right_child;
            other_ptr = other_ptr->right_child;
        }
        else
        {
            node_ptr = node_ptr->parent;
            other_ptr = other_ptr->parent;
        }
    }

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
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Node *node)
{
    root = node;
    size = 1;
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::~Treap()
{
    // TODO : Implement this
}


template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::operator=(Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> other)
{
    size = other.size;
    if(other.root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        root = other.root;
        Node* node_ptr = root;
        Node* other_ptr = other.root;
        while(other_ptr != nullptr)
        {
            if(other_ptr->left_child != nullptr && node_ptr->left_child == nullptr )
            {
                node_ptr->left_child =  other_ptr->left_child;
                node_ptr = node_ptr->left_child;
                other_ptr = other_ptr->left_child;
            }
            else if(other_ptr->right_child != nullptr && node_ptr->right_child == nullptr)
            {
                node_ptr->right_child =  other_ptr->right_child;
                node_ptr = node_ptr->right_child;
                other_ptr = other_ptr->right_child;
            }
            else
            {
                node_ptr = node_ptr->parent;
                other_ptr = other_ptr->parent;
            }
        }
    }
    return *this;
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
bool Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator==(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator &other) const
{
    return (other.pointer == this->pointer);
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
bool Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator::operator!=(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::iterator &other) const
{
    return (other.pointer != this->pointer);
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



/* Modifiers */
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::insert(const KeyType &key, ValueType &&value, const PriorityType &priority)
{
    insertHelper(root, new Node{key, std::move(value), priority, nullptr, nullptr, nullptr});
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::erase(const KeyType &key)
{
    // TODO : Implement this
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
ValueType& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::search(const KeyType &key) const
{
    Node *node = this->root;

	while (node) {
		if (key == node->key) {
			return node->value;
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

	throw "Element not found";
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::merge(Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &&other)
{
    if (root->key <= other.root->key) {
        left_treap_root = root;
        right_treap_root = other.root;
    }
    else {
        right_treap_root = root;
        left_treap_root = other.root;
    }
    this->root = mergeHelper(right_treap_root, left_treap_root, right_treap_root);
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
std::pair<Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>, Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>> Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::split(const KeyType &key)
{
    left_treap_root = nullptr;
    right_treap_root = nullptr;
    splitHelper(root, key);
    return {{left_treap_root}, {right_treap_root}};
}



/* Helper Functions */
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



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::splitHelper(Node *split_root, const KeyType &split_key)
{
    if (split_root == nullptr) {
        return;
    }
    else if (split_key <= split_root->key) {
        auto child = split_root->right_child;

        split_root->parent = left_treap_root;
        split_root->right_child = nullptr;

        child->parent = right_treap_root;

        left_treap_root = split_root;
        splitHelper(child, split_key);
        left_treap_root = split_root;
    }
    else {
        auto child = split_root->left_child;

        split_root->parent = right_treap_root;
        split_root->left_child = nullptr;

        if (child) {
            child->parent = left_treap_root;
        }

        right_treap_root = split_root;
        splitHelper(child, split_key);
        right_treap_root = split_root;
    }
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
typename Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Node* Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::mergeHelper(Node *node, Node *left_treap_root, Node *right_treap_root)
{
    if (left_treap_root == nullptr || right_treap_root == nullptr) {
        if (left_treap_root == nullptr) {
            return right_treap_root;
        }
        else {
            return left_treap_root;
        }
    }
    else if (left_treap_root->priority > right_treap_root->priority) {
        auto merged_subtree_root = mergeHelper(left_treap_root->right_child, right_treap_root);
        left_treap_root->right_child = merged_subtree_root;
        merged_subtree_root->parent = left_treap_root;
        return left_treap_root;
    }
    else {
        auto merged_subtree_root = mergeHelper(left_treap_root, right_treap_root->right_child);
        right_treap_root->left_child = merged_subtree_root;
        merged_subtree_root->parent = right_treap_root;
        return right_treap_root;
    }
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
void Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::insertHelper(Node *&node, Node *it)
{
    if (!node) {
        node = it;
    }
    else if (it->priority > node->priority) {
        auto parent = node->parent;
        auto node_hook = node;
        
        left_treap_root = it->left_child;
        right_treap_root = it->right_child;
        
        splitHelper(node, it->key);
        
        it->left_child = left_treap_root;
        if (left_treap_root != nullptr) {
            left_treap_root->parent = it;
        }
        
        it->right_child = right_treap_root;
        if (right_treap_root != nullptr) {
            right_treap_root->parent = it;
        }
        
        it->parent = parent;
        if (parent != nullptr) {
            (node_hook == parent->left_child) ? parent->left_child = it : parent->right_child = it;
        }
    }
    else {
        if (node->value < it->key) {
            insertHelper(node->right_child, it);
        }
        else {
            insertHelper(node->left_child, it);
        }
    }
}
