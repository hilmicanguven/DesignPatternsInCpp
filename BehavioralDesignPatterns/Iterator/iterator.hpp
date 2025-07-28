/*

Iterator Design Pattern

Farklı data struct'ların dolaşılmasını (traversal) kolaylaştıran bir "iterator" sınıfı oluşturulabilir.
Şu şekilde gerçekleşir, şu anki elemana ait referansı tutar, ve bir sonraki elemana nasıl gideceğini bilir.

Explicit şekilde bir sınıfı kendi operatörümüzü yazarak iterate edebileceğimiz gibi explicit olarak aslında farkında olmasak da kullanırız
bunlara örnek, range-based for loops, coroutines.

*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// iterators in standard library

void iterators_in_stl()
{
    vector<string> names{ "yilmaz", "ilkkan", "ersoy", "umran" };

    vector<string>::iterator it = names.begin();
    cout << "first name is " << *it << "\n";


    ++it; // go next item
    // modify the iterations
    it->append(string(" yedinci"));
    cout << "second name is " << *it << "\n"; // should expect "ilkkan yedinci"

    // names.end(), iterator'un gosterdigi son elemanin bir sonraki bellek adresini gosterir.
    // "yilmaz", "ilkkan", "ersoy", "umran"  
    //                                      ^ (names.end())
    while (++it != names.end())
    {
        cout << "Others name: " << *it << "\n";
    }

    // traversing the entire vector backwards... rend = reverse end
    //                              "yilmaz", "ilkkan", "ersoy", "umran" 
    // ^ rend (reverse end)                                         ^ (rbegin) = reverse begin

    for (auto ri = rbegin(names); ri != rend(names); ++ri)  // ++ goes previous element
    {
        cout << *ri;
        if (ri + 1 != rend(names)) // iterator arithmetic
            cout << ", ";
    }

    cout << endl;

    // other type of iterators : Constant iterators
    // we can not modify underlying element what we traverse.
    vector<string>::const_reverse_iterator jack = crbegin(names);
    // won't work
    //*jack += "test";


    for(auto&& character : names)
    {
        cout << "Character Name: " << character << "\n";
    }
}

// Binary Tree iterator



// Tree iterator with coroutines


// Boost iterators

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include <boost/iterator/iterator_facade.hpp>

//single linked list iterator

struct Node
{
    string value;
    Node* next = nullptr;

    explicit Node(const string& value) : value(value) { }


    Node(const string& value, Node* const parent) : value(value)
    {
        parent->next = this;
    }
};

struct ListIterator : boost::iterator_facade<ListIterator, 
Node, boost::forward_traversal_tag> /* only forward is meaningful for single linked list*/
{
    Node* current = nullptr;

    ListIterator()
    {
    }

    explicit ListIterator(Node* const current) : current(current)
    {
    }

private:
    friend class boost::iterator_core_access;

    void increment() // should override this since iterator expects
    {
        current = current->next; 
    }
  
    bool equal(const ListIterator& other) const // should override this since iterator expects
    {
        return other.current == current; // compare content (data) of the nodes
    };

    Node& dereference() const // should override this since iterator expects
    { 
        return *current; 
    }
};

void iterator_in_boost()
{
    // boost library examples

    Node wizard{" Gandalf"};
    Node archer{" Legolas", &wizard};
    Node half_elvish{" Elrond" , &archer};

    for_each(ListIterator{ &wizard }, ListIterator{},  [](const Node& iter)
    {
        cout << iter.value << endl;
    });
}