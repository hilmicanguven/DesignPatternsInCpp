/*

Bazı nesneler kompleks değil de basit özelliklere sahip olduğunda tek bir "ctor" çağrısı ile oluşturulabilir. Ancak nesneler
büyüdükçe "ctor" içerisine çok sayıda argüman vermek etkili olmayabilir. bu durumda nesneleri adım adım (step-by-step) 
oluşturmak gerekir. Nesne, tek bir fonksiyon çağrısı ile değil, bir dizi aşamalı fonksiyonla oluşturulur. 
Bu şekilde nesneleri oluşturmak için bir Builder sınıfı kullanılır.
Abstracy Factory ile kıyaslarsak orada nesneler bir bütün halinde oluşturulurken burada adım adım oluşturulur.

Base builder sınıfı, nesne yaratırken olabilecek tüm adımları tanımlar (ev örneğin -> havuz, ısıtma sistemi, gider sistemi, bahçe peyzajı vb) 
concrete builders ise bu adımları üretilecek ana sınıfa/ürüne göre özelleştirir. 
Client kod ise hangi ev oluşturulacak veya hangi sıra ile yapılacak buna karar verir.

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


class OfficeBaseBuilder;
class OfficeCoolerBuilder;
class OfficeHardwareBuilder;

class Office{
    private:
        Office(){}
        int cooler_type{};
        int computer_brand{};
        std::string office_name{};
    
    public:
        
        static OfficeBaseBuilder Builder(std::string name);

        void display_office_properties()
        {
            std::cout << "Office Office   Name  is: " << office_name << "\n";
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
        Office m_office;
    
    public:
        OfficeBaseBuilder(Office &office) : m_office(office){
            
        }
        OfficeBaseBuilder(Office &office, std::string name) : m_office(office){
            m_office.office_name = name;
        }

        OfficeCoolerBuilder cooler_builder();
        OfficeHardwareBuilder hw_builder();


        Office get_office(){

            return this->m_office;
        }

        /* 
        * Alternative to get_office interface, Below call can be used.
          The compiler automatically calls it to convert the builder into a Office object when assigning it to object of Office, e.g. in the main function
        */
        operator Office()
        {
            return this->m_office;
        }

};

class OfficeHardwareBuilder : public OfficeBaseBuilder
{
    public:
        OfficeHardwareBuilder(Office &office) : OfficeBaseBuilder(office){}

        OfficeHardwareBuilder& set_computer_brand(int brand){
            
            m_office.computer_brand = brand;
            return *this;
        }
};


class OfficeCoolerBuilder: public OfficeBaseBuilder{
    public:
        OfficeCoolerBuilder(Office &office) : OfficeBaseBuilder(office){}
        
        OfficeCoolerBuilder& set_cooler_type(int type)
        {
            m_office.cooler_type = type;
            return *this;
        }
};

OfficeBaseBuilder Office::Builder(std::string name)
{
    Office o;
    if(name.length() < 100)
    {
        return OfficeBaseBuilder(o, name);
    }

    // invalid name, initalize office with default id values.
    return OfficeBaseBuilder(o);
}
  
OfficeCoolerBuilder OfficeBaseBuilder::cooler_builder()
{
    auto t =OfficeCoolerBuilder(this->m_office);
    return t;
}

OfficeHardwareBuilder OfficeBaseBuilder::hw_builder()
{
    auto t = OfficeHardwareBuilder(this->m_office); 
    return t;
}



