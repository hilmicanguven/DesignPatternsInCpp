#include "observer.hpp"

int main()
{

    Employee e{20, 1100};

    HRAnnualObserver hr_salary_observer;
    e.subscribe(hr_salary_observer);
    
    HRBirthdayObserver hr_anniversary_observer;
    e.subscribe(hr_anniversary_observer);

    e.birthday(); // 21
    e.anniversary();

    e.unsubscribe(hr_salary_observer);
    e.anniversary();    // do not care since this is unsubscribed

    e.birthday(); 
    e.birthday();
    e.birthday();
    e.birthday();   // age 25, last annual leave gift is given.
                    // then unsubscribe annual leave topic and
                    // no further notify is updated
    e.birthday();
    e.birthday();
    e.birthday();
    e.birthday();
    return 0;
}