/*

"Factory" ve "Abstract Factory" birbirine benzediğiiçin bir grup gibi düşenebiliriz.

Factory : A component responsible solely for the wholesale (not piecewise) creation of objects.

Farklı bir sınıf veya fonksiyon oluşturularak nesne yaratma işlemi bu komponent altına taşınır.
Bu durumda oluşturulacak nesnelerin yaratılması da "ctor" dan bu fonksiyon altına taşınır.
Halihazırda bir sınıf için yazılan uygulama kodu ikinci bir sınıf geldiği zaman değişikliğe uğraması gerekir
ve yeni sınıfı entegre etmesi oldukça zordur.
Bu factory sınıfı içerisinde aynı Base Class'dan türeyen Derived Class'ların üretimi gerçekleştirilebilir.
Bu durumda Factory class kullanılarak nesnelerimiz hazır bir şekilde oluşturularak client code'a verilir.
ancak elbette bu durumda nesne içinde set edilen propert'ler nedir bilinmez.

"
        The Factory Method separates product construction code from the code that actually uses the product. 
        Therefore it’s easier to extend the product construction code independently from the rest of the code.

        For example, to add a new product type to the app, you’ll only need to create a new creator subclass and 
        override the factory method in it.

        - https://refactoring.guru/design-patterns/factory-method
"


#include <cmath>

// do not need this for factory
enum class PointType
{
  cartesian,
  polar
};

class Point
{
//   Point(float a, float b, PointType type = PointType::cartesian)
//   {
//   if (type == PointType::cartesian)
//   {
//   x = a; b = y;
//   }
//   else
//   {
//   x = a*cos(b);
//   y = a*sin(b);
//   }
//   }

  // use a factory method
  Point(float x, float y) : x(x), y(y) {}

  class PointFactory
  {
    PointFactory() {}
  public:
    static Point NewCartesian(float x, float y)
    {
      return { x,y };
    }
    static Point NewPolar(float r, float theta)
    {
      return{ r*cos(theta), r*sin(theta) };
    }
  };
public:
  float x, y;
  static PointFactory Factory;
};

int main_2()
{
  // will not work
  // Point p{ 1,2 };

  // nope!
  // Point::PointFactory pf;

  // if factory is public, then
  //auto p = Point::PointFactory::NewCartesian(3, 4);

  // at any rate, use this
  auto pp = Point::Factory.NewCartesian(2, 3);

  return 0;
}

*/

/*

Abstract Factory:

Abstract Factory'de ise birden fazla Product'ı virtul interface yardımıyla tek bir Factory'de üretme işidir.
Birden fazla sınıf, aynı aile içerisinde değerlendiriliyorsa bu kalıbın kullanılması daha uygundur.
Birden fazla "factory" i ortak bir sınıf içerisinde toplayarak birlikte üretilmelerini sağlar.
Örneğin, windows ve mac işletim sistemlerindeki "button" ve "checkbox" sınıfları OS'a özgüdür.

----------------------------------------------------------------------------------
Feature	        |   Factory Method	         |  Abstract Factory
----------------------------------------------------------------------------------
Products	    |   One product	             |  Multiple related products
Flexibility	    |   Simple creation logic	 |  Grouping families of objects
Interface	    |   Single factory method	 |  Factory interface with multiple methods
Complexity	    |   Less complex	         |  More complex and extensible
---------------------------------------------------------------------------------- 

 You can be sure that the products you’re getting from a factory are compatible with each other.
 You avoid tight coupling between concrete products and client code.
 Single Responsibility Principle. You can extract the product creation code into one place, making the code easier to support.
 Open/Closed Principle. You can introduce new variants of products without breaking existing client code.

                                        Abstract GUI Factory
                                                |
                                                |
                    Windows Factory                                          MAC Factory
                ---------------------                                   ---------------------                       
                |                   |                                   |                   |
    win10 checkbox create    win10 button create           MAC checkbox create    MAC button create




- Chatgpt Code example (also in refactoring.guru)
// Abstract Products
class Button {
public:
    virtual void draw() = 0;
};

class Checkbox {
public:
    virtual void check() = 0;
};

// Concrete Products for Windows
class WindowsButton : public Button {
public:
    void draw() override {
        std::cout << "Drawing Windows Button" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void check() override {
        std::cout << "Checking Windows Checkbox" << std::endl;
    }
};

// Concrete Products for Mac
class MacButton : public Button {
public:
    void draw() override {
        std::cout << "Drawing Mac Button" << std::endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void check() override {
        std::cout << "Checking Mac Checkbox" << std::endl;
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
};

// Concrete Factory for Windows
class WindowsFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WindowsButton();
    }
    Checkbox* createCheckbox() override {
        return new WindowsCheckbox();
    }
};

// Concrete Factory for Mac
class MacFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new MacButton();
    }
    Checkbox* createCheckbox() override {
        return new MacCheckbox();
    }
};

// Usage
int main() {
    GUIFactory* factory = new MacFactory(); // Or WindowsFactory

    Button* btn = factory->createButton();
    Checkbox* chk = factory->createCheckbox();

    btn->draw();    // Drawing Mac Button
    chk->check();   // Checking Mac Checkbox

    delete btn;
    delete chk;
    delete factory;
}

*/


/* My Example 
Office creation for both R&D and Production Plant.
*/

#include <iostream>
#include <string>
#include <memory>

class Office{
    private:
        Office(){}
        int cooler_type{};
        int computer_brand{};
        std::string office_name{};
    
    public:
        

        void display_office_properties()
        {
            std::cout << "Office Office   Name  is: " << office_name << "\n";
            std::cout << "Office Cooler   Type  is: " << cooler_type << "\n";
            std::cout << "Office Computer Brand is: " << computer_brand << "\n";
            std::cout << "------------------------------------ "<< "\n";
        }
};

// Abstract product families
class Cooler {
public:
    virtual void cool() = 0;
    virtual ~Cooler() = default;
};

class Computer {
public:
    virtual void compute() = 0;
    virtual ~Computer() = default;
};

// Concrete product variants
class SoftwareDepartmentCooler : public Cooler {
public:
    void cool() override { std::cout << "Small Office cooled with Fan (ventilator)!\n"; }
};

class ProductionFactoryCooler : public Cooler {
public:
    void cool() override { std::cout << "Big production atelier cooled with Air Conditioning!\n"; }
};

class SoftwareDepartmentComputer : public Computer {
public:
    void compute() override { std::cout << "SW Department has powerful computers with fancy GPUs\n"; }
};

class ProductionFactoryComputer : public Computer {
public:
    void compute() override { std::cout << "Production Factory has Siemens PLC Computers!\n"; }
};

// Abstract factory
class OfficeFactory {
public:
    virtual std::unique_ptr<Cooler> createCooler() = 0;
    virtual std::unique_ptr<Computer> createComputer() = 0;
    virtual ~OfficeFactory() = default;
};

class RDCenterOfficeFactory : public OfficeFactory {
  public:
    // std::unique_ptr<Cooler> createCooler(){
    //   return new SoftwareDepartmentCooler();
    // }
    // std::unique_ptr<Computer> createComputer(){
    //   return new ProductionFactoryCooler();
    // }
    std::unique_ptr<Cooler> createCooler() override { return std::make_unique<SoftwareDepartmentCooler>(); }
    std::unique_ptr<Computer> createComputer() override { return std::make_unique<SoftwareDepartmentComputer>(); }
};

class ProductionFactoryFactory : public OfficeFactory {
  public:
    // std::unique_ptr<Cooler> createCooler() {
    //   return new ProductionFactoryCooler();
    // }
    // std::unique_ptr<Computer> createComputer(){
    //   return new ProductionFactoryComputer();
    // }
    std::unique_ptr<Cooler> createCooler() override { return std::make_unique<ProductionFactoryCooler>(); }
    std::unique_ptr<Computer> createComputer() override { return std::make_unique<ProductionFactoryComputer>(); }
};

