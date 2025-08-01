/*

Observer Design Pattern

Belirli bir olay olduğunda bilgilendirilmeye yönelik bir pattern'dir.
Bu olaylara "Event", bunu dinleyen ve gerçekleştiğinden haberdar olmak isteyene "Subscriber" denilmektedir.
Farklı dillerde "Signal" ve "Slot" kavramları da benzer amacı tariflemek için kullanılır.

Bunu kendi örneğimiz ile güzelce pekiştirelim.
İnsan Kaynakları (HR) departmanı, çalışanların yıl dönümleri bazı yan haklar sağlayacağını varsayalım ve bu tarih geldiğinde
yazdığımız yazılım aracılığı ile bilgilendirilsin. Ör,
    - işe giriş yıl dönümü (1 yıllık deneyim kazandığında)  ->  maaşında 10% oranında artış gerçekleşecektir
    - doğum günü olduğunda                                  ->  yıllık iznine +1 gün ilave olacaktır

Burada, 
    + Observer = HR departmanı
    + Observable = Employee
olacaktır.

Ayrıca pub-sub pattern'de olduğu gibi Topic bazlı bilgilendirme yapabiliriz. 

İki ayrı observer class'ı implemente edilmiş olarak gözükmektedir. bu pattern uygulanırken
thread safety ve re-entrancy konularına dikkat edilmesi gerekmektedir.

- thread safety: notify, subscribe veya un-subscribe işlemleri mutex ile korunmalıdır.
                    birbirleri olan senkronizasyon bu şekilde sağlanabilir.
- re-entrancy: mutex scpe lock ile koruma altına alınan bir kod bloğu içerisindeyken
                farklı bir fonksiyonda tekrar mutex lock ile sağlanan farklı bir kod bloğuna girildiği 
                durumda oluşur. buna çözüm "recursive mutex" olarak gösterilmekte ancak pek hoş karşılaşılan
                bir çözüm olmadığından bahsedilir.
*/

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <algorithm>

using namespace std;

namespace Topics
{
    std::string birthday = "birthday";
    std::string anniversary = "anniversary";
    std::string board_member_status = "board-member-status";
}

template <typename> struct Observer;

// Observable
// template <typename T>
// struct Observable
// {
//     std::vector<Observer<T>*> observers;
//     typedef std::recursive_mutex mutex_t;
//     mutex_t mtx;
// public:
//     void notify(T& source, const std::string& field_name)
//     {
//         for (auto observer : observers)
//         observer->updated(source, field_name);
//     }

//     void subscribe(Observer<T>& observer)
//     {
//         observers.push_back(&observer);
//     }

//     void unsubscribe(Observer<T>& observer)
//     {
//         observers.erase(
//         remove(observers.begin(), observers.end(), &observer),
//         observers.end()
//         );
//     }
// };

// Observable with thread-safe machanism

template <typename T>
struct SaferObservable
{
    std::vector<Observer<T>*> observers;
    typedef std::recursive_mutex mutex_t;
    mutex_t mtx;
public:
    void notify(T& source, const std::string& field_name)
    {
        std::scoped_lock<mutex_t> lock{mtx};
        for (auto observer : observers)
        {
            if (observer)
            {
                observer->updated(source, field_name);
            }
        }
    }

    void subscribe(Observer<T>& observer)
    {
        std::scoped_lock<mutex_t> lock{mtx};
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer)
    {
        auto it = std::find(begin(observers), end(observers), &observer);
        if (it != end(observers))
        *it = nullptr;
    //    std::scoped_lock<mutex_t> lock{mtx};
    //    observers.erase(
    //      remove(observers.begin(), observers.end(), &observer),
    //      observers.end()
    //    );
    }
};


// Observer
template <typename T> struct Observer
{
    virtual void updated( T& source, const std::string& field_name) = 0;
};


class Employee : public SaferObservable<Employee>
{
    int age{0};
    int annual_leave{14};
    int salary{1000};

public:
    Employee(){}
    Employee(int age, int salary) : age(age), salary(salary) {}

    int get_age() const { return age; }
    int get_salary() const { return salary; }
    int get_annual_leave() const { return annual_leave; }

    void set_age(int age)
    {
        if (this->age == age) return;

        this->age = age;
    }
    
    void promote_salary() { salary= salary*1.10; }
    void increase_annual() { annual_leave++; }

    void birthday()
    { 
        notify(*this, Topics::birthday); 
    }

    void anniversary()
    { 
        notify(*this, Topics::anniversary); 
    }
};


struct HRAnnualObserver : public Observer<Employee>
{
    private:
    
    void updated(Employee &source, const std::string &field_name) override
    {
        std::cout << "Employee's " << field_name << " is today! \n";
        
        if (field_name == Topics::anniversary)
        {
            source.promote_salary();            
            
            cout << "New Salary: " << source.get_salary() << " \n";
        }
    }
};

struct HRBirthdayObserver : Observer<Employee>
{
  void updated(Employee &source, const std::string &field_name) override
  {
    if (field_name == Topics::birthday)
    {
        if (source.get_age() < 25)
        {
            source.set_age(source.get_age() + 1);
            cout << "welcome young friend, take this extra holiday for birthday!\n";
            cout << source.get_age() << " years old! \n";
            source.increase_annual();
            cout << "new annual leave day: " << source.get_annual_leave() << "\n";
        }
        else
        {
            cout << "no longer care your birthday!\n Do not add additional annual leave  ";
            source.unsubscribe(*this);
        }
    }
  }
};