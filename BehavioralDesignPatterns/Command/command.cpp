#include "BehavioralDesignPatterns/Command/command.hpp"

int main()
{

    // BankAccount ba;

    // CompositeBankAccountCommand commands{
    // BankAccountCommand{ ba, BankAccountCommand::deposit, 100 },
    // BankAccountCommand{ ba, BankAccountCommand::withdraw, 200 }
    // };

    // cout << ba.balance << endl;
    // commands.call();
    // cout << ba.balance << endl;
    // commands.undo();
    // cout << ba.balance << endl;

    BankAccount sender, receiver;

    MoneyTransferCommand transfer(receiver, sender, 300);
    transfer.call();
    
    cout << "sender balance   : " << sender.balance << endl;
    cout << "receiver balance :" << receiver.balance << endl;

    transfer.undo();
    
    cout << "sender balance   : " << sender.balance << endl;
    cout << "receiver balance :" << receiver.balance << endl;

    cout << "--------------------------------------------" << endl;
    cout << "INVALID TRANSFER::" << endl;

    MoneyTransferCommand transfer_invalid(receiver, sender, 3000);
    transfer_invalid.call();
    
    cout << "sender balance   : " << sender.balance << endl;
    cout << "receiver balance :" << receiver.balance << endl;

    transfer_invalid.undo();
    
    cout << "sender balance   : " << sender.balance << endl;
    cout << "receiver balance :" << receiver.balance << endl;

    return 0;
}