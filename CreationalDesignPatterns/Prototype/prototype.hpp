/*

Prototype Design Pattern

Projeler oluşturuldukça ve üzerine eklemeler yapıldıkça yeni eklenen özellikler veya sınıflar, sıfırdan (from scratch) yazılmaz.
Mevcut nesnelerin üzerine eklentiler yapılarak geliştirildiği durumlar olabilir.
Bu gibi durumlar için "Cloning" adı verilen bir işlem uygulanarak mevcut nesneden yeni bir nesne oluşturulabilir.

Prototype: Partially or fully initialized object that you copy (clone) and make use of for your benefit

Herhangi bir pattern kullanılmadığı senaryoyu değerlendirdiğimizde 
bir nesneyi diğerine kopyalayıp sonrasında istediğimiz field'ları değiştirebiliriz.
    "
        Person yılmaz{.name = "yılmaz", ... }
        Person ilkkan = yılmaz;
        ilkkan.name = "ilkkan"
    "
Ancak herhangi bir field "pointer" olduğunda bir nesnede yapılan değişiklik diğerini değiştireceği için hata oluşturacaktır.
Üstteki kopyalama biçimine "Shallow Copy" adı veriliyor.
Bu gibi hatalar oluşmaması adına "Deep Copy" olarak adlandırılan biçimde bir kopyalama yapılması gerekmektedir.
Bunu yapmak adına sınıf içerisine "Copy Constructor" eklenir.
    "
        Person(const Person &p)
        {
            .id = p.id
            .name_ptr = {new Name {p.name,p.surname,...}}
        }
    "

Bu işlemleri desteklediği varsayıldığında, bizden bunu kopyalamak/replicate edecek API'ya nesneleri nasıl vereceğimizi belirlemek gerekli.
Örneğin, bir nesneyi global scope içerisinde tanımlayarak verebiliriz, ancak elbette bu pek mantıklı bir yöntem değildir.
Bunun yerine bir PrototypeFactory oluşturabiliriz.

    "
        struct EmployeeFactory
        {
            std::unique_ptr<Person> new_x_employee(string& name, age, .. , )
            {
                Person prototype(....)

                Person p = create_new_employee(name, age, prototype);
                return p;
            }
        }
    "

Sınıfa ait member vb. kopyalama esnasında "serialization/deserialization" adı verilen bir konsept de kullanılabilir.
Serialize/Deserialize : Store/Restore all the aspects of an object
Bunun için oluşturulan bir kütüphane mevcut -> "boost/serialization.hpp"
İki yöntemden (deep copy or serialize) bir tanesi kullanılabilir.

*/

/**
 * My Example: Create new Office from the existing one.
 */

#include <iostream>
#include <string>
#include <memory>


// Address Class
class Address {
public:
    std::string city;
    std::string street;

    Address(std::string c, std::string s) : city(c), street(s) {}

    void show_address() const {
        std::cout << "Office Address        is: " << street << ", " << city << std::endl;
    }
};

class Office{
    public:
        
        virtual std::unique_ptr<Office> clone() const = 0;
        virtual void display_office_properties() const = 0;
        virtual ~Office() = default;
};

class CenterRDOffice: public Office {
    public:

        CenterRDOffice(int cooler, int computer, std::string name, std::string city, std::string street, std::string motto) : 
                                                                    cooler_type(cooler), 
                                                                    computer_brand(computer), 
                                                                    office_name(name),
                                                                    address(city, street),
                                                                    motto(new std::string(motto)){}

        // Clone Method (Deep Copy)
        std::unique_ptr<Office> clone() const override
        {
            return std::make_unique<CenterRDOffice>(cooler_type, computer_brand, office_name, address.city, address.street, *motto);
        }

        void set_address(std::string city, std::string street)
        {
            address.city = city;
            address.street = street;
        }

        void set_motto(std::string new_motto)
        {
            *motto = new_motto;
        }

        void set_office_name(std::string new_office_name)
        {
            office_name = new_office_name;
        }


        void display_office_properties() const override
        {
            std::cout << "Office Office   Name  is: " << office_name << "\n";
            std::cout << "Office Cooler   Type  is: " << cooler_type << "\n";
            std::cout << "Office Computer Brand is: " << computer_brand << "\n";
            address.show_address();
            std::cout << "Office Motto          is: " << *motto << "\n";
            std::cout << "------------------------------------ "<< "\n";
        }

    private:
        int cooler_type{};
        int computer_brand{};
        std::string office_name{};
        Address address{"null", "null"};
        std::string* motto;
};

