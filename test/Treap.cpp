#include <iostream>
using namespace std;

#include "../include/Treap.h"

int main()
{
    Treap<int, int, int> t, t1, t2;

    int choice, key, value, priority;
    do {
        cin >> choice;

        switch (choice)
        {
        case 1:
            cin >> key >> value >> priority;
            t.insert(key, int(value), priority);
            break;
        case 2:
            cin >> key;
            t.erase(key);
            break;
        case 3:
            cin >> key;
            cout << boolalpha << key << endl;
            break;
        case 4:
            t1 = t;
            t2 = Treap<int, int, int>(t);
            break;
        }
    } while (choice != 0);

    return 0;
}
