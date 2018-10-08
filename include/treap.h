#ifndef TREAP_H
#define TREAP_H

#include <utility>
#include <functional>


template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare = std::less<KeyType>, class PriorityCompare = std::less<PriorityType>>
class Treap
{
private:
    struct Node
    {
        KeyType Key;
        ValueType Value;
        PriorityType priority;
        Node* left_child;
        Node* right_child;
        Node* parent;
    };

    unsigned int size;
    Node* root;

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

    /* Constructors & Destructors */
    Treap();
    Treap(const Treap&);
    Treap(Treap&&);

    ~Treap();

    Treap& operator=(Treap);

    /* Capacity */
    bool isEmpty() const;
    unsigned getSize() const;

    /* Iterators */
    iterator begin() const;
    iterator end() const;

    /* Modifiers */
    void merge(Treap&&);
    std::pair<Treap, Treap> split();
    void insert(const KeyType&, ValueType value);
    void erase(const KeyType&);
    ValueType& search(const KeyType&) const;
};


#endif /* TREAP_H */
