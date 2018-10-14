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
        KeyType key;
        ValueType value;
        PriorityType priority;
        Node* left_child;
        Node* right_child;
        Node* parent;
        Node(KeyType&, ValueType&, PriorityType&);
        Node(const Node&);
    };

    Node* root;
    unsigned int size;

    /* Helper functions */
    void leftRotate(Node*);
    void rightRotate(Node*);

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

        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
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
    void insert(const KeyType&, ValueType&&, const PriorityType&);
    void erase(const KeyType&);
    ValueType& search(const KeyType&) const;
};


#include "../src/Treap.cc"


#endif /* TREAP_H */
