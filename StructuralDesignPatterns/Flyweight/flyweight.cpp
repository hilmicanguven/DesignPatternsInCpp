#include "flyweight.hpp"

int main()
{

    EmployeeFamilyMember yilmaz{ "Yilmaz", "Gibi" };
    EmployeeFamilyMember ilkkan{ "Ilkkan", "Gibi" };

    cout << "Yilmaz -> " << yilmaz << endl;
    cout << "Ilkkan -> " << ilkkan << endl;

    EmployeeFamilyMember::info();
    return 0;
}