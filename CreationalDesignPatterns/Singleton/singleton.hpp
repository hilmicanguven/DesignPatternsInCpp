/*

Singleton Design Pattern

Aralarında en sevilmeyen ve bu kalıplardan bir tanesi kaldırılacak olsa bu olurmuş :(

Bazı sistem bileşenlerinin tüm sistemde yalnızca bir tane olması yeterli olabilir
- Database Repository
- Object Factory

Constructor'ı yalnızca bir kere çağırılır ve tekrar istenirse bir arayüz ile instantiate olmuş sınıfı döndürmemiz gerekir.
Bu kalıbı kullanıyorken yalnızca bir tane nesne oluşturulduğunu kontrol etmemiz gerekir.
    Bunun için "constructor" private yapılır ve "Copy Constructor" ve "Copy Assignment operator=" delete edilir.
Bu kalıbı kullanıyorken thread-safety olup olmadığını kontrol etmemiz gereklidir.

    | Singleton : A component which is instantiated only once

*/

/*
Single kalıbını office örneğimize uygulayalım. 

Bu esnada projemiz için bir test yazacağımızı düşünelim. Örneğin, istediğimiz ofislerin toplam çalışan sayısını hesaplayan
bir fonksiyonumuz var ve bunu test etmek istiyoruz. Bu fonksiyon, ofislere ait database bilgisini ancak ve ancak SingleOfficeDatabase
sınıfından alacağı için "tigth couple" olmuş olur ve fonksiyonun çalışması ve testin geçmesi bu sınıfın doğruluğunu olduğu sürece
geçerli bir test olacaktır.

Buna çözüm olarak bir yöntem düşünülebilir -> Dependency Injection

    | Dependency injection is a programming technique that makes a class independent of its dependencies

Kendi örneğimizde, tek bir SingletonDatabaseClass oluşturmak yerine "base" Office class'ı oluşturup bunu inherit
ederek SingletonDatabaseClass oluşturmak daha mantıklıdır. Test esnasında kullanmak üzere yeni bir databaseClass
oluşturabiliriz yine Office sınıfını inherit eden ve içerisinde tuttuğumuz database bilgisini (normalde dosyadan okuyup, 
bir map içerisinde depoladığımız) yine bir Map içerisinde ancak tamamen bu test sınıfı içerisinde oluşturduğumuz random
bilgiler'den oluşturabiliriz.

class SingletonTestDatabase : public Office
{
    std::map<std::string, int> offices;

    offices["Test_Center_Office"] = 1;
    offices["Test_Production_Office"] = 2;
}
*/

/*

Multiton: Bu kalıp ise bir instance oluşturmak yerine kendi kontrol edebileceğimiz kadar oluşturulmasını sağladığımız yapıdır.
Kendi oluşturacağımız algoritma ile bir sınıfın sahip olabileceği özelliklere göre farklı tiplerde ancak yalnız birer tane oluşturulabilir.
(Genellikle template class yapısını uygulayarak)
Örneğin, ofis bilgilerimizi tutan sınıf içerisinde, içerisine alacağı database dosya formatı template parametresi ile .txt dosya
türü için bir tane ve ".csv" dosya formatı için birer tane instance yaratabiliriz. 

*/

/**
 * 
 * Summary  |   Making a 'safe' singleton is easy
 *                 - Hide or Delete the type's constructor, copy constructor and copy assignemnt operator
 *                 - Create static method that returns a reference to a static member
 *                 - Guaranteed to ve thread-safe since C++11
 *              Consider depending on an abstraction instead of directly using a singleton class
 * 
 * Important Note: The pattern requires special treatment in a multithreaded environment so that multiple threads won’t create a singleton object several times.
 * 
 */


#include <iostream>
#include <map>
#include <string>
#include <boost/lexical_cast.hpp>
#include <fstream>

class Office{
    private:
        int employee_number{};
        int cooler_type{};
        int computer_brand{};
        std::string office_name{};
    
    public:
        Office(){}
        virtual int get_total_employee(const std::string& office_name) = 0;
        
};

class SingletonOfficeDatabase : public Office {
    private:

        SingletonOfficeDatabase()
        {
            std::cout << "Database is fetched and initializing...\n";
    
            std::ifstream db_file("/home/hilmi/repo/DesignPatternsInCpp/CreationalDesignPatterns/Singleton/office_database.txt");

            if (!db_file.is_open()) {
                std::cerr << "Error opening db_file!" << std::endl;
            }

            std::string office_name;
            int total_employee;

            while (std::getline(db_file, office_name) && db_file >> total_employee) 
            {
                db_file.ignore(); // Skip the newline after reading the number
                offices[office_name] = total_employee;
            }
            // while (std::getline(db_file, office_name)) {
            //     std::string populationLine;
            //     if (!std::getline(db_file, populationLine)) {
            //         std::cerr << "Missing total_employee for office_name: " << office_name << std::endl;
            //         break;
            //     }

            //     try {
            //         total_employee = std::stoi(populationLine);
            //     } catch (const std::invalid_argument& e) {
            //         std::cerr << "Invalid total_employee value for office_name: " << office_name << std::endl;
            //         continue;
            //     }

            //     offices[office_name] = total_employee;
            // }
        }

        std::map<std::string, int> offices;
    public:
        void display_database()
        {
            for (auto &o : offices)
            {
                std::cout << "Office Name: " << o.first << " Total Population: " << o.second << "\n";
            }
        }

        // sometimes named "get_instance"
        static SingletonOfficeDatabase& get_reference()
        {
            static SingletonOfficeDatabase db;
            return db;
        }

        int get_total_employee(const std::string& office_name) override {
            return 100;
        }

};


#include "singleton.hpp"

int main() {

    SingletonOfficeDatabase::get_reference().display_database();

    return 0;
}

