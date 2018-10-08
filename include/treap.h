#ifndef TREAP_H
#define TREAP_H

#include<utility>
#include <functional>

template<typename KeyType, typename ValueType, typename PriorityType, class KeyCompare=std::less<KeyType>, class PriorityCompare = std::less<PriorityType>>
class Treap
{
private:
    struct Node
    {
        KeyType Key;
        ValueType Value;
        unsigned priority;
        Node* left_child;
        Node* right_child;
        Node* parent;
    };
    unsigned size;
    Node* root;

    //Node* transplant(Node*, Node*);


public:

    class iterator {
    private:
        Node* pointer;

    public:
        iterator (arguments);
        ~iterator ();
    };

    Treap();
    Treap(const Treap&);
    Treap(Treap&&);

    ~Treap();

    Treap& operator=(Treap);

    bool isEmpty() const;
    unsigned getSize() const;

    iterator begin() const;
    iterator end() const;

    void merge(Treap&&);
    std::pair<Treap, Treap> split();

    void insert(const KeyType&, ValueType value);
    void erase(const KeyType&);
    ValueType& search(const KeyType&) const;


};


#endif
