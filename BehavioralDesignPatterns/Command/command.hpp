/*

Command Design Pattern

Bir operasyonu (veya bir "request" i, bir "intruction"ı) bir obje olarak nesne ile temsil edilmesidir. 
Gerekecek tüm aksiyonlar için gerekli tüm bilgiyi içerir.
Bu pattern açıklanırken şu iki terim sık kullanılıyor ve karıştırılmaması önemlidir. GoF literatüründe her ikisi decommand design pattern i açıklar.
    - Command   : Bir aksiyon alma veya değişiklik yapma isteği (Bir önceki örneğimizde bir çalışanın kıdem alması ve maaşının artması emridir)
    - Query     : Bilgiye ulaşmak için yapılan sorgudur (çalışanın o anki maaşı) 

Bir sınıf üzerinde bir işlem yapılmak istendiği durumda, doğrudan sınıfa ait arayüzü çağırmak yerine yeni bir Command sınıfı oluşturularak
yapılmak istenen işlem ilgili sınıfa bu Command sınıfı ile yapılır.

Command sınıfı, tek bir işlem yapabileceği üzere genellikle yapılan işlemi iptal etme (undo) yapmak için de arayüzleri bulunur.

Yine ek bir iyileştirme olarak birden fazla Command'in bir arada bulunduğu bir sınıf daha oluşturarak birden fazla işlemin tek bir komut ile yapılmasına
olanak sağlanmış olur (Command Queue olarak adlandırabiliriz)  -> "Composite Command"

Üstte açıkladığımız konseptleri şöyle bir gerçek hayat örneği verelim
    - Banka hesapları üzerinde işlemler yapıyor olalım
    - Command örneği olarak -> işlem yapma      (call) :: "para yatırma" a.k.a. "deposit"  işlemini verebiliriz
    - Command örneği olarak -> işlemi geri alma (undo) :: "para çekme"   a.k.a. "withdraw" işlemini verebiliriz.
    - Composite Command örneği olarak ise -> hesaplar arası para transferi yapılırken önce bir hesaptan para çekilir sonra diğerine para yatırılır.
                                                yani birden fazla command bir işlem için oluşturulmuş olur.
                                                
Dikkat edilmesi gereken çok önemli bir nokta şudur ki eğer bir işlem yapılamazsa/hata oluşursa devamında gelen diğer Command'leri yapmıyor olmalıyız.
Yukarıda açıklanan composite command örneğinde, 
    transfer esnasında eğer ki gönderici hesabında transfer etmek istenen miktarda para bulunmuyorsa 1.para çekme işlemi hataya düşecektir
    bu durumda 2.para yatırma işlemi yapılmaması gerekmektedir. Yani Command'ler (Queue'daki) birbirlerinin sonuçları bağımlıdır.
    Bu durumda yeni bir terim -> "Dependent Composite Command"

Bu noktada Command'lerin birbirleri ile olan etkileşimi, hangi hata durumları oluşuyor ve birbirlerini nasıl etkiliyor "Dependent Composite Command" 
sınıfı içerisinde yönetilmelidir. uygulamadan uygulamaya karmaşıklığı değişecektir.

*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount
{
public:
  int balance = 0;
  int overdraft_limit = -500;

  void deposit(int amount)
  {
    balance += amount;
    cout << "deposited " << amount << ", balance now " <<
      balance << "\n";
  }

  bool withdraw(int amount)
  {
    if (balance - amount >= overdraft_limit)
    {
      balance -= amount;
      cout << "withdrew " << amount << ", balance now " <<
        balance << "\n";
      return true;
    }
    return false;
  }
};

struct Command
{
  bool succeeded;
  virtual void call() = 0;
  virtual void undo() = 0;
};

// Generic Command for Bank Account operations
struct BankAccountCommand : Command
{
  BankAccount& account;
  enum Action { deposit, withdraw } action;
  int amount;

  BankAccountCommand(BankAccount& account, const Action action, const int amount) 
                                    : account(account), action(action), amount(amount)
  {
    succeeded = false;
  }

  void call() override
  {
    switch (action)
    {
    case deposit:
      account.deposit(amount);
      succeeded = true;
      break;
    case withdraw:
      succeeded = account.withdraw(amount);
      break;
    }
  }

  void undo() override
  {
    if (!succeeded) return;

    switch (action)
    {
    case withdraw:
      if (succeeded)
        account.deposit(amount);
      break;
    case deposit:
      account.withdraw(amount);
      break;
    }
  }
};

// Composite Command Queue contains multiple commands for one operation (money transfer)
// it has a downside, consecutive commands do not depend each other. it may cause fatal errors.
// see dependent composite command class below
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
  CompositeBankAccountCommand(const initializer_list<value_type>& _Ilist)
    : vector<BankAccountCommand>(_Ilist)
  {
  }

  void call() override
  {
    for (auto& cmd : *this)
      cmd.call();
  }

  void undo() override
  {
    for (auto it = rbegin(); it != rend(); ++it)
      it->undo();
  }
};

// ona command can disable consecutive command (rest of the queue)
struct DependentCompositeCommand : CompositeBankAccountCommand
{

  explicit DependentCompositeCommand(
    const initializer_list<value_type>& _Ilist)
    : CompositeBankAccountCommand{ _Ilist } {}

  void call() override
  {
    bool ok = true;
    for (auto& cmd : *this)
    {
      if (ok)
      {
        cmd.call();
        ok = cmd.succeeded;
      }
      else
      {
        cmd.succeeded = false;
      }
    }
  }
};

// example operation to use dependent composite command
struct MoneyTransferCommand : DependentCompositeCommand
{
  MoneyTransferCommand(BankAccount& from,
    BankAccount& to, int amount): 
    DependentCompositeCommand
    {
      BankAccountCommand{from, BankAccountCommand::withdraw, amount},
      BankAccountCommand{to, BankAccountCommand::deposit, amount}
    } {}
};