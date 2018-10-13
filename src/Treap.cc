
template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap() : root(nullptr), size(0)
{}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &other)
{
    size = other.size;
    if(other->root == nullptr)
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
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::~Treap()
{
    // TODO : Implement this
}


template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>& Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::operator=(Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> other)
{
    size = other.size;
    if(other->root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        root = other->root;
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
}

template<typename KeyType, typename ValueType , typename PriorityType, class KeyCompare, class PriorityCompare>
unsigned Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::getSize() const
{
    return size;
}

template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare,class PriorityCompare>
bool Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::isEmpty() const
{
    if(size == 0)
    {
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
