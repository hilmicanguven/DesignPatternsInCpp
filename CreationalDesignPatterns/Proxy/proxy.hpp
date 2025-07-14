/*

Proxy Design Pattern

Bir kaynağa erişmek için ayrı bir Sınıf oluştulur ve bu kaynağa yapılacak erişim bu sınıf yardımıyla olur.
Bir diğer deyiş ile, farklı bir nesneye erişmek için ara bir nesne (substitute or placeholder). 
Bu nesne yardımıyla asıl nesneye erişmeden önce veya sonra yapılacak işlemler arka planda hallediliyor olur.

    | The Proxy pattern suggests that you create a new proxy class with the same interface as an original service object. 


Proxy örneğinin birçok farklı alanda uygulaması bulunur. 
    - Lazy Initialization (Virtual Proxy)
        Bu kullanıma bir örneği -> Bir sınıf bir görseli yükler(Constructor'da bilgilerini (bitmap) Databaseden okuyor olsun) ve sonrasında ekrana bastırır.
        Eğer ki bir bu görsel hiç ekrana bastırılmıyor ise DB'den okunmasına gerek yoktur, ta ki ekrana bastırılana kadar.
        Bunun için bir Proxy sınıf oluşturularak ne zaman "ekrana bastırma" arayüzü çağırılırsa arka planda Proxy DB'den bitmap'i okur ve ekrana bastırır.
        Client kod yine aynı arayüz ile çalışmaya devam eder.

    - Access Control (Protection Proxy)
        Ana nesneye doğrudan erişim yapılmasını engeller. Kontrol ederek yalnızca belirli sınıflara bu erişim iznini verir.
    - Local execution of a remote service (remote proxy).
    - Logging requests (logging proxy)
    - Caching request results (caching proxy)
    - Smart reference (Smart pointers)


    |   Proxy is a structural design pattern that provides an object that acts as a substitute for a real service object used by a client. 
    |   A proxy receives client requests, does some work (access control, caching, etc.) and then passes the request to a service object.
                                                                                    ... refactoring.guru

*/

#include <string.h>
#include <iostream>

// Advertisement Material
class Catalog 
{
    public:
        virtual void display() = 0;
};

// RealSubject
class AdvertisementCatalog : public Catalog 
{
    private: 
    
        void load_image_from_database() 
        {
            std::cout << "Loading image: " << m_filename << " from the database \n";
        }
    
    public:

        std::string m_filename;
        
        AdvertisementCatalog(std::string filename)
        {
            m_filename = filename;
            load_image_from_database();
        }
        
        void display() override
        {
            std::cout << "Displaying image: " << m_filename << " on the website of the company...\n";
        }
};

// Proxy Class
class ProxyCatalog : public Catalog 
{
    private:
        AdvertisementCatalog * real_catalog;
        std::string m_filename;

    public:
        ProxyCatalog(std::string filename) 
        {
            m_filename = filename;
        }

        // Exactly the same interface for actual object
        void display() override
        {
            // If catolog is get from the database, no need to fetched it again (caching proxy)
            if (real_catalog == nullptr) 
            {
                // New catalog is not created until it is not displayed...(lazy initialization, virtual proxy)
                real_catalog = new AdvertisementCatalog(m_filename);
            }

            real_catalog->display();
        }
};


