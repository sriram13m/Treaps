template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap() : root(nullptr), size(0)
{}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(const Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &other)
{
    // TODO : Implement this
}



template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare, class PriorityCompare>
Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare>::Treap(Treap<KeyType, ValueType, PriorityType, KeyCompare, PriorityCompare> &&other)
{
    // TODO : Implement this
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
