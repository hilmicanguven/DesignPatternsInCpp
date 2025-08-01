#include "memento.hpp"

int main()
{

    BankAccount bank_account{ 200 };
    bank_account.deposit(100);
    bank_account.deposit(50);

    cout << bank_account << "\n"; // should expect 350

    /*
    
    Timeline -->             (current)
                                ^  
        [deposit-100       deposit-50   ]
    */
    // undo is applied current, and move current to previous one
    bank_account.undo();
    cout << "Undo 1: " << bank_account << "\n"; // undo depoziting 50, should be 300
    

    /*
    
    New Timeline -->     (current)
                            ^  
                        [deposit-100       deposit-50   ]
    */
    bank_account.undo();
    cout << "Undo 2: " << bank_account << "\n"; // again undo depoziting 100, should be 200
    
    bank_account.redo();
    cout << "Redo 2: " << bank_account << "\n"; // redo depoziting 100, should be again 300

    bank_account.undo();
    cout << "Undo 3: " << bank_account << "\n"; // undo depoziting 100 again, should be again 200


    return 0;
}