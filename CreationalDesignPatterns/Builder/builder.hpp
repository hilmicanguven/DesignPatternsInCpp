/*

Bazı nesneler kompleks değil de basit özelliklere sahip olduğunda tek bir "ctor" çağrısı ile oluşturulabilir. Ancak nesneler
büyüdükçe "ctor" içerisine çok sayıda argüman vermek etkili olmayabilir. bu durumda nesneleri adım adım (step-by-step) 
oluşturmak gerekir. Nesne, tek bir fonksiyon çağrısı ile değil, bir dizi aşamalı fonksiyonla oluşturulur. 
Bu şekilde nesneleri oluşturmak için bir Builder sınıfı kullanılır.

Ne zaman kullanılmalı:
    Nesne oluşturma süreci karmaşıksa ve farklı konfigürasyonlara sahipse.
    Nesne oluşturma süreci benzer adımları içeren ancak detayları farklı ise
    Aynı türden ama farklı özelliklere sahip nesneler oluşturulacaksa. (Ahşap Ev ve Taş Ev)

"Builder" sınıfı desteklediği arayüzlere ve dönüş değerlerine göre farklı isimlendirilir.
    - Fluent Builder: Farklı "attribute"ları set eden fonksiyonları ardıardına zincir şeklinde çağırıldığı duruma verilen addır.
                        Özellik set eden arayüzler bu durumda void dönmek yerine, nesnenin kendisini dönmelidir.

    - Builder Facets: Nesne gitgide karmaşık hale geldiğinde tek bir builder yerine birden fazla builder kullanılabilir. 
                        Bu şekilde gerçeklenirse "Faceted Builder" adı verilir. 


Builder Pattern'i ile nesnelerin oluşturulma kodu değiştirilmeden farklı türde nesne üretebiliriz.

"   The Builder pattern suggests that you extract the object construction code out of its own class and 
    move it to separate objects called builders.
                        - refactoring.guru/design-patterns/builder
"

*/

/*

// Simple Car Builder example

#include <iostream>
#include <string>

class Car {
public:
    std::string brand;
    std::string model;
    int year;

    void show() {
        std::cout << "Car: " << brand << " " << model << " (" << year << ")" << std::endl;
    }
};

// Builder sınıfı (Fluent Builder)
class CarBuilder {
private:
    Car car;
public:
    CarBuilder& setBrand(const std::string& brand) {
        car.brand = brand;
        return *this;
    }

    CarBuilder& setModel(const std::string& model) {
        car.model = model;
        return *this;
    }

    CarBuilder& setYear(int year) {
        car.year = year;
        return *this;
    }

    Car build() {
        return car;
    }
};

int main() {
    Car myCar = CarBuilder().setBrand("Skoda").setModel("Kamiq Premium").setYear(2022).build();
    myCar.show();
    return 0;
}

*/

/* Faceted Builder Example */

#include <iostream>
#include <string>

#include<iostream>

class OfficeBaseBuilder;
class OfficeCoolerBuilder;
class OfficeHardwareBuilder;

class Office{
    private:
        int cooler_type{};
        int computer_brand{};
        Office(){}
    
    public:
        
        static OfficeBaseBuilder Builder();

        void display_office_properties()
        {
            std::cout << "Office Cooler   Type  is: " << cooler_type << "\n";
            std::cout << "Office Computer Brand is: " << computer_brand << "\n";
            std::cout << "------------------------------------ "<< "\n";
        }
        
        friend class OfficeBaseBuilder;
        friend class OfficeCoolerBuilder;
        friend class OfficeHardwareBuilder;
};

class OfficeBaseBuilder{
    protected:
        Office office;
    
    public:
        OfficeBaseBuilder(Office &office):office(office){}

        OfficeCoolerBuilder cooler_builder();
        OfficeHardwareBuilder hw_builder();

        operator Office()
        {
            return this->office;
        }
};

class OfficeHardwareBuilder : public OfficeBaseBuilder
{
    public:
        OfficeHardwareBuilder(Office &office) : OfficeBaseBuilder(office){}

        OfficeHardwareBuilder& set_computer_brand(int brand){
            
            office.computer_brand = brand;
            return *this;
        }
};


class OfficeCoolerBuilder: public OfficeBaseBuilder{
    public:
        OfficeCoolerBuilder(Office &office) : OfficeBaseBuilder(office){}
        
        OfficeCoolerBuilder& set_cooler_type(int type)
        {
            this->office.cooler_type = type;
            return *this;
        }
};

OfficeBaseBuilder Office::Builder()
{
    Office p;
    return OfficeBaseBuilder(p);
}
  
OfficeCoolerBuilder OfficeBaseBuilder::cooler_builder()
{
     return OfficeCoolerBuilder(this->office);
}

OfficeHardwareBuilder OfficeBaseBuilder::hw_builder()
{
     return OfficeHardwareBuilder(this->office);
}



