
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
    if(size == 0)
    {
        return true;
    }

    return false;
}
