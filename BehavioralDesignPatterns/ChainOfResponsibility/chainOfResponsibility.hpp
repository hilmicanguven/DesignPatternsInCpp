/*

Chain of Responsibility (CoR, Chain of Command)

Yapılması gereken bir iş geldiğinde, bu iş birtakım "handler" lardan geçerek eğer gerekiyorsaüstüne düşen görevi yapmalı
veya bir sonraki "handler" a ileterek işin yapılmasını paslamalıdır.

Yapılacak iş genellikle nihai amaca ulaştıran bir dizi görev parçaları olarak değerlendirilebilir.
                     
                               Chain of Responsibility
                      |------------------------------------|   
    +-----------+     | +------------+     +------------+  |   +--------------+
    |  Request  | --> | |  Handler A | --> | Handler B  |  | --> |  EndSystem   |
    +-----------+     | +------------+     +------------+  |   +--------------+


Günlük hayattan bir probleme benzetecek olursak çağrı merkezlerini değerlendirebiliriz.

CoR pattern'i 2 şekilde implemente edilebilir.
1- a chain of pointers/references (singly linked list)
2- Centralized List (event brokes, similar to pub/sub architecture)


*/

/* Pointer Chain

Kendi örneğimizi oluşturalım. Office örneğimiz için şöyle bir senaryo düşünelim.
Bir çalışanın şirketteki birinci yılı dolduğunda farklı departman'ların yapması gereken görevleri yönettiğimiz bir sistem düşünelim.

Promoter: Farklı departmanlar bu şekilde adlandırıldı ve bir çalışan için birden fazla promoter olabilir
            Örneğin,    İnsan Kaynakları    -> 1.yılı dolunca +5 gün yıllık izin gününü artırır
                        Muhasebe            -> 1. yıl dolunca +5% maaş artışı olur
                        Yazılım Bölünü      -> Her yıl sonu değerlendirme yaparak gerekirse ek ünvan ekler. (Uzman, Kıdemli Uzman vb.)
                        Direkörlük          -> diğer departmanlardan bağımsız Çalışan incelenir ve gerekliyse iyileştirmeler yapılır.
                                                Diğer departmanlar herhangi bir işlem yapmaz.

*/

#include <iostream>
#include <string>
using namespace std;

// class EmployeePromoter;
// class HumanResourcesPromoter;
// class AccountPromoter;
// class AccountPromoter;

struct Employee
{

    public:
        friend class EmployeePromoter;
        friend class HumanResourcesPromoter;
        friend class AccountPromoter;
        friend class DirectorPromoter;

        Employee(const string& name, const int total_year, const int salary)
        : m_name(name),
            m_total_year(total_year),
            m_salary(salary)
        {
            if(total_year > 10) m_annual_leave = 21;
            else m_annual_leave = 14;
        }

        void display()
        {
            cout << "Name: " << m_name << "   --> Total Experience (in years): " << m_total_year << "  --> Salary: " << m_salary << " \n";
        }

    private:
        string m_name;
        int m_total_year, m_salary, m_annual_leave;
};

class EmployeePromoter
{
    private:
        EmployeePromoter* m_next_promoter{nullptr};
    protected:
        Employee& m_employee;
    public:
        
        explicit EmployeePromoter(Employee& employee) : m_employee(employee)
        {
        }
        virtual ~EmployeePromoter() = default;

        // Add promoter departmens
        void add_promoter(EmployeePromoter* ep)
        {
            
            if (m_next_promoter)
            {
                m_next_promoter->add_promoter(ep);
            }
            else
            {
                m_next_promoter = ep;
            }     
        }

        virtual void handle()
        {
            if (m_next_promoter) 
            {
                m_next_promoter->handle();
            }
        }

};

class HumanResourcesPromoter : public EmployeePromoter
{
public:
  explicit HumanResourcesPromoter(Employee& e)
    : EmployeePromoter(e)
  {
  }

  void handle() override
  {
    // Do HR specific promotions
    m_employee.m_total_year++;
    m_employee.m_annual_leave += 1;

    // Call next promoter department if available
    EmployeePromoter::handle();
  }
};

class AccountPromoter : public EmployeePromoter
{
public:
  explicit AccountPromoter(Employee& e)
    : EmployeePromoter(e)
  {
  }

  void handle() override
  {
    // Do Salary Account specific promotions
    m_employee.m_salary *= 1.05;

    // Call next promoter department if available
    EmployeePromoter::handle();
  }
};

class DirectorPromoter : public EmployeePromoter
{
public:
  explicit DirectorPromoter(Employee& e)
    : EmployeePromoter(e)
  {
  }

  void handle() override
  {
    if(0 < m_employee.m_total_year < 5)
    {
        m_employee.m_name = "Specialist " + m_employee.m_name;
    }
  
    else if(5 < m_employee.m_total_year < 10)
    {
        m_employee.m_name = "Senior Specialist" + m_employee.m_name;
    }

    // IMPORTANT
    // no further promoting. 
  }
};

/*
Broker Chain

Biraz daha karmaşık yapıda bir implementasyon. Birden fazla pattern'in birleşimi ile yapılır.(mediator, observer)
*/