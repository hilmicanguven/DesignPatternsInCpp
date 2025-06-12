/*

Bazı nesneler kompleks değil de basit özelliklere sahip olduğunda tek bir "ctor" çağrısı ile oluşturulabilir. Ancak nesneler
büyüdükçe "ctor" içerisine çok sayıda argüman vermek etkili olmayabilir. bu durumda nesneleri adım adım (step-by-step) 
oluşturmak gerekir. Nesne, tek bir fonksiyon çağrısı ile değil, bir dizi aşamalı fonksiyonla oluşturulur. 
Bu şekilde nesneleri oluşturmak için bir Builder sınıfı kullanılır.

Ne zaman kullanılmalı:
    Nesne oluşturma süreci karmaşıksa ve farklı konfigürasyonlara sahipse.
    Aynı türden ama farklı özelliklere sahip nesneler oluşturulacaksa.

"Builder" sınıfı desteklediği arayüzlere ve dönüş değerlerine göre farklı isimlendirilir.
    - Fluent Builder: Farklı "attribute"ları set eden fonksiyonları ardıardına zincir şeklinde çağırıldığı duruma verilen addır.
                        Özellik set eden arayüzler bu durumda void dönmek yerine, nesnenin kendisini dönmelidir.


*/

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
    Car myCar = CarBuilder().setBrand("Toyota").setModel("Corolla").setYear(2023).build();
    myCar.show();
    return 0;
}