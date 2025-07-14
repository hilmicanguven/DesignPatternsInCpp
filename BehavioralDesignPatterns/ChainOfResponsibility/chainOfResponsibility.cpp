#include "BehavioralDesignPatterns/ChainOfResponsibility/chainOfResponsibility.hpp"

int main()
{
    Employee ersoy{"Ersoy", 3, 50000};
    ersoy.display();

    EmployeePromoter root{ersoy};
    HumanResourcesPromoter hr_promoter{ersoy};
    AccountPromoter acc_promoter{ersoy};
    DirectorPromoter dir_promoter{ersoy};

    root.add_promoter(&hr_promoter);
    root.add_promoter(&acc_promoter);
    root.add_promoter(&dir_promoter); 
    root.add_promoter(&acc_promoter); // this is not called anoymore since Director is the last promoter
                                        // determined in DirectorPromoter class itself.

    root.handle();
    ersoy.display();

    return 0;
}