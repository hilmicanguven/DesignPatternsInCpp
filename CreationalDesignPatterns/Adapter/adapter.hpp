/*

Adapter Design Pattern

Gerçek hayatta karşımıza çıkan bir problem ile daha iyi anlayamaya çalışalım.
Güç adaptöleri her ülke/kıtada farklı voltaj seviyesine ve priz girişine sahiptir.
Aldığımız elektrnik ürünler hepsine uyacak şekilde bir tasarıma sahip değildir.
Bunun yerine bir çeşit güç adaptörü kullanarak aynı ürünümüzü farklı ülkelerde de kullanabiliriz.

Adapter tasarım kalıbı da benzer uyumlandırmayı yazılım parçaları için yapar.

    |   Adapter : a construct which adapts an existing interface X to conform to the required interface Y.


Adapter, Client ve uygulamalar arasında hem çalıştıkları "data type" dönüşümleri yapabilir hem de farklı
arayüzlere sahipseler bunlar arasında köprü oluşturabilir. 
Adapter sınıfı mevcut class'ları ve yeni eklenecek class'ları (new class, 3rd party app etc) inherit edebilir.
Sonrasında sahip olduğu arayüzler ile mevcut class'ı kullanarak yeni class'ın talep ettiği formatta çağrı yapabilir.

Adapter kalıbını farklı şekilde gerçekleyebiliriz. 
- class adapter (inheritance based)     : multiple inheritance destekleniyorsa (C++)
- object adapter (composition based)
- two-way adapter (composition based)
- interface adapter (default adapter)

*/

// Adapter Design Pattern Example Code

#include <iostream>

// Base Interface for Cooler, each should support this (existing and newly comings)
class Cooler {
public:
    virtual void cool() = 0;
};

// Adaptee
class LegacyCooler : public Cooler{
public:
    void cool() override 
    {
        std::cout << "* Cooler is cooling the room." << std::endl;
    }
};

// Adapter to adapt new cooler with existing system
class CoolerAdapter : public Cooler {
private:
    LegacyCooler legacy_cooler;

public:
    CoolerAdapter()
    {
        std::cout << "\tChange power adaptor..." << std::endl;
        std::cout << "\tNew cabling..." << std::endl;
        std::cout << "\tModify discharge system..." << std::endl;
        std::cout << "\tIt is ready..." << std::endl;
    }
    void cool() override 
    {
        legacy_cooler.cool();
    }
};

// Client Code
void client_cooler_app(Cooler& cooler) 
{
    cooler.cool();
}

