/*
Bridge Design Pattern


Bridge is a structural design pattern that lets you 
split a large class or a set of closely related classes into two separate hierarchies—abstraction and implementation—
which can be developed independently of each other.
                                            - @ref refactoring.guru

Bridge tasarım kalıbı genellikle şu örnek probleme çözüm olmak için kullanılır:
 
Ürünlerimizin tanıtımını yapacağımız bir internet sitesi düşünelim. 
bu tanıtım görsellerini oluştururken gerçek resimler ile, animasyon resimleri ile ve yapay zeka tarafından üretilen görseller ile yapabildiğimizi varsayalım. 
bu durumda "Renderer Sınıf Sayısı = toplam ürün sayısı (N) x toplam görsel çeşidi sayısı (M)" kadar olmalı ki bu büyük bir problem (Multiplication Product Problem)

Böyle yapmak yerine Bridge patterni uygulayarak toplam sınıf sayısını azaltabiliriz.

---------------------------------------------------
Pimpl Idiom (Pointer to Implementation): 

    Sınıfın implementasyonunu arayüzden ayırma işlemidir.
    Interface class içerisinde asıl davranış farklı bir implementation sınıfına taşınır ve 
    bu yeni sınıf pointer aracılığı ile ana sınıfın interface sınıfında bulunur.
    şunu fark edelim ki, gizlemek istediğimiz detayları bu "exampleImpl" sınıfı içerisine koyup (hatta yalnızca Cpp dosyasına) kullanıcıya açmayabiliriz. 
    Bu durumda yalnızca ana sınıfın header dosyası paylaşıldığında gizlemek istediğimiz "member" lar paylaşılmamış olur.

        | hiding certain implementation details and making sure that they don't appear as part of the header.

        |   "Pointer to implementation" or "pImpl" is a C++ programming technique 
        |    that removes implementation details of a class from its object representation by placing them in a separate class, 
        |    accessed through an opaque pointer...
        |                                                cppreference.com
---------------------------------------------------

*/

/*

Örnek problem için elimizdeki ürünler Kitap ve Kalem olsun.
Görsel tipi olarak da "AI-Generated Picture" ve "Animation Picture" olsun.

Her bir product-renderer tipi için ayrı class oluşturmak yerine Render sınıfından türeyen Renderer türlerini
ürünler içerisine veririz ve doğrudan bu renderer nesnelerini kullanarak görsel oluşturma işlemlerini (implementation specific)
ana ürün sınıfından uzaklaştırmış oluruz. Ayrıca her bir olasıkombinasyon için ayrı sınıf oluşturmamıza gerek kalmaz.

Örneğin, yeni bir product ("Pen" sınıfı) geldiğinde ek bir Renderer sınıfı eklemek yerine 
mevcutta bulunan renderer sınıflarının içerisine implementation specific özellikleri ekledik.
yani "pencil_renderer" arayüzlerini ekledik.
*/

#include <iostream>


// Renderers - determine how an object is created
// Products  - determine what to create

// Bridge class to products with their renderers
class Renderer
{
    public:
        virtual void render_book(int page_number, int color_type) = 0;
        virtual void render_pen(int material, int color_type) = 0;
};

class AIBasedRenderer : public Renderer
{
    public:

        void render_book(int page, int color) override
        {
            std::cout << "Rendering Book with AI Tool (ChatGPT) -> Page: " << page << " and Color: " << color << "\n";
        }

        void render_pen(int material, int color) override
        {
            std::cout << "Rendering Book with AI Tool (ChatGPT) -> Material: " << material << " and Color: " << color << "\n";
        }
};

class AnimationBasedRenderer : public Renderer
{
    public:
        void render_book(int page, int color) override
        {
            std::cout << "Rendering Book with Animation Environment (Unity) -> Page: " << page << " and Color: " << color << "\n";
        }
        void render_pen(int material, int color) override
        {
            std::cout << "Rendering Pen with Animation Environment (Unity) -> Material: " << material << " and Color: " << color << "\n";
        }
};

class Product{

    protected:
        Renderer& renderer;
        Product(Renderer& r) : renderer(r) {}
    public:
        virtual void create_images() = 0;                                   // specific to implementation   (how images are created/rendered)
        virtual void change_feature(int feature, int new_color_type) = 0;  // specific to abstraction      (depends on products)
};

class Book : public Product
{

public:
    Book(Renderer& r, int pn, int ct) : Product{r}, page_number{pn}, color_type{ct} {}

    void create_images() override
    {
        renderer.render_book(page_number, color_type);
    }

    void change_feature(int page_num, int new_color_type) override
    {
        page_number = page_num;
        color_type = new_color_type;
    }

    int page_number = 0;
    int color_type  = 0xFF;
};

class Pen : public Product
{

public:
    Pen(Renderer& r, int material, int ct) : Product{r}, m_material{material}, color_type{ct} {}

    void create_images() override
    {
        renderer.render_pen(m_material, color_type);
    }

    void change_feature(int material, int new_color_type) override
    {
        m_material = material;
        color_type = new_color_type;
    }

    int m_material = 0;
    int color_type  = 0xFF;
};

#include "bridge.hpp"

int main()
{

    AnimationBasedRenderer anim_render{};
    Book book{anim_render, 150, 2};

    book.create_images();

    Pen pen(anim_render, 41, 67);
    pen.create_images();

    AIBasedRenderer ai_render{};
    Pen pen_2{ai_render, 06, 75};
    pen_2.create_images();

    return 0;
}