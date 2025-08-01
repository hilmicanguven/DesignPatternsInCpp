/*

Memento Design Pattern

Memento is a behavioral design pattern that 
        lets you save and restore the previous state of an object without explaning the details of its implementation.

Daha önce "Commander" design pattern'inde benzer durumu görmüştük (do ve undo arayüzleri ile)
Burada ise farklı bir yapı (token/handle) ile sistemin durumunu tutabilir ve o state'e geçiş yapılabilir.

Daha önce açıkladığımız BankAccount örneğini düşünürsek, hesapta bulunan para miktarını "Memento Class" aracılığı ile
geçmişe dönük, o anki durumunu öğrenebiliriz. Yani bir timeline'da belirli bir duruma gidebiliriz.
Ancak bunu implemente ederken immutable olmasına dikkat etmeliyiz ki Memento
aracılığı ile geçmişe dönük/sistemi etkileyen bir değişiklik yapılamasın.

*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Memento
{
    int m_balance;

public:
    Memento(int balance) : m_balance(balance) {}

    int get_balance() { return m_balance;}
};

class BankAccount // supports undo/redo
{
    int balance = 0;
    // memento list to keep track history
    vector<shared_ptr<Memento>> changes_timeline;
    // currently which state we are in
    int current;

public:
    explicit BankAccount(const int balance) : balance(balance)
    {
        changes_timeline.emplace_back(make_shared<Memento>(balance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = make_shared<Memento>(balance);
        changes_timeline.push_back(m);
        ++current;
        
        return m;
    }

    void restore(const shared_ptr<Memento>& m)
    {
        if (m)
        {
            balance = m->get_balance();
            changes_timeline.push_back(m);
            current = changes_timeline.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes_timeline[current];
            balance = m->get_balance();
            return m;
        }

        return{};
    }

    shared_ptr<Memento> redo()
    {
        if (current + 1 < changes_timeline.size())
        {
            ++current;
            auto m = changes_timeline[current];
            balance = m->get_balance();
            
            return m;
        }

        return{};
    }

    friend ostream& operator<<(ostream& os, const BankAccount& obj)
    {
        return os << "balance: " << obj.balance;
    }
};