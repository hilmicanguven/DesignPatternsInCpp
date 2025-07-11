/*

Flyweight Design Pattern

Bu kalıp "Space Optimization" ile ilgilidir. Gereksiz yere depolanan verilerden kaçınılması hedeflenir.
Örnek olarak -> aynı isim ve soyisme sahip birçok ismin bulunduğu bir veritabanında tüm bu isimler için yer tutmaya gerek yok.
                bir pointer ve isimlerin listesi ile daha verimli bir şekilde bu bilgiyi depolayabiliriz.

            -> yine daha basit örnek verelim, daha önceki örneklerimizde "Office" sınıfını uyarlıyorduk. farz edelim ki çalışan ve ailelerin bilgilerini tutuyoruz.
                her birini Person sınıfından oluşturduğumuzu varsayalım. bir ailedeki kişilerin adresleri çok büyük oranda ayno olacaktır.
                bu durumda her bir aile üyesinin adresini ayrı ayrı Person sınıfı içinde tutmak çok da akıllıca olmayacaktır. 
                çünkü bu adresin bir kere oluşturulup (RAM içerisinde) diğerlerinde de aynı adresin referansı (RAM deki aynı adresi) kullanması mantıklıdır.

Genele yayarsak, ortak sahip olunan özelliklerin her bir nesne için saklanması yerine ortak bir noktadan paylaşılmasıdır.

bu ortak yerde oluşturma ve paylaşma işlemini kendimiz yapabileceğimiz gibi bazı kütüphaneler bunu halihazırda sağlıyor olabilir 
    (ör. Boost kütüphanesi doğrudan "flyweight" ismiyle bir stl sağlıyor ve doğrudan bu kullanılabilir (bir çeşit dictionary))

Bir genel kültür bilgisi -> Flyweight ismi Box sporunda "Sinek Siklet" yani 51kg (111 lbs) altındaki siklete verilen isim. İsmi de buradan geliyor.

Flyweight kalıbını incelerken şu iki terim sıkça karşımıza çıkıyor: 

+ Intrinsic State: İçsel özellik, tüm nesnelerde benzer/aynı olan özelliklere bu ad verilebilir.
                    bir basketbol oyununda tüm basketbol topları aynı şekilde olacaktır (renk, boyut vb)
+ Extrinsic State: Dışsal olarak değişiklik gösteren özelliklerdir. Basketbol oyuncuları boy, kilo vb farklı olacaktır.
                    Bu özelliklerin ana nesneden ayrılması gerekmektedir.

Ya da bir savaş oyununda, "Savaşçı" sınıfına ait tüm nesnelerin türü aynı isimde (savaşçı) ve silahları aynı (kılıç) olacaktır.
    Ancak savaşçıların fiziksel özellikleri (güç, sağlık, dayanıklılık vb) farklı olacaktır.


*/

#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/flyweight/key_value.hpp>

using namespace std;

struct EmployeeFamilyMember
{
  EmployeeFamilyMember(const string& first_name, const string& last_name)
    : first_name{add(first_name)}, last_name{add(last_name)}
  {
  }

  const string& get_first_name() const
  {
    return names.left.find(last_name)->second;
  }

  const string& get_last_name() const
  {
    return names.left.find(last_name)->second;
  }

  static void info()
  {
    for (auto entry : names.left)
    {
      cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
    }
  }

  friend ostream& operator<<(ostream& os, const EmployeeFamilyMember& obj)
  {
    return os
      << "first_name: " << obj.first_name << " " << obj.get_first_name()
      << " last_name: " << obj.last_name << " " << obj.get_last_name();
  }
protected:
  static boost::bimap<int, string> names;
  static int seed;

  static int add(const string& s)
  {
    auto it = names.right.find(s);
    if (it == names.right.end())
    {
      // add it
      int id = ++seed;
      names.insert(boost::bimap<int, string>::value_type(seed, s));
      return id;
    }
    return it->second;
  }
  int first_name, last_name;
};

int EmployeeFamilyMember::seed = 0;
boost::bimap<int, std::string> EmployeeFamilyMember::names{};