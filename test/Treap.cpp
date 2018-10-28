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
            cout<<"Enter key,value,priority"<<endl;
            cin >> key >> value >> priority;
            cout<<"Inserted Successfully"<<endl;
            t.insert(key, int(value), priority);
            break;
        case 2:
            cin >> key;
            t.erase(key);
            break;
        case 3:
            cin >> key;
            try {
                cout << boolalpha << t.search(key) << endl;
            }
            catch (const char *e) {
                cout << e << endl;
            }
            break;
        case 4:
            t.levelorder();
        case 5:
            t1 = t;
            t2 = Treap<int, int, int>(t);
            break;
        }
    } while (choice != 0);

    return 0;
}
