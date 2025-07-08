/*

Composite Design Pattern

Sahip olduğumuz nesneler ister tek bir nesne isterse bir grup nesnenin koleksiyonu olsun aynı şekilde davranılmasını hedefler.
Bu kalıbı şu durumda kullanılması mantıklıdır -> Eğer ki problemi bir "tree" yapısı ile açıklayabiliyorsak.

Bu tarz bir probleme örnekler vermek istersek:
    - Kutular ve içlerine koyulan ürünler olabilir. her kutu içerisinde daha küçük farklı bir kutu daha içerebilir.
        En büyük kutuya bakıldığında toplam kaç kutu/her birinin ağırlığı/ fiyatı gibi hesaplamaları yapmamız gerektiğinde işler karışabilir.
        her bir kutu veya ürün kendi içinde bulunduğu veya içerisinde bir şey yoksa kendi özelliği döndürmesi yaklaşımı benimsenebilir.
    - Askeri ordu düzeninde de farklı hiyerarşik yapılar(tugay, bölük, takım, asker grubu) bulunur ve emirler en yukarıdan verildiğinde en aşağıya kadar iletilir 
    - Office programlarında bir şekil tek veya birden fazla şekil bir grup haline getirilmiş olabilir. her ikisine de aynı davranış ile
        kontrol edilmesi yaklaşımıdır.

Bu durumlarda tek(individual) nesneler de kompleks(group of individuals) nesneler de aynı arayüzlere sahiptir.
Individual nesne (Leaf node in a tree) yapılacak operasyonu kendisi yaparken, Compound nesne "recursive" biçimde kendi altındaki child'lara işin
yapılmasını (delegate) söyler ve onların sonuçlarını bir araya getirir.

Client kod tüm nesnelere aynı davranır ve hangisi tek hangisi compound bilmesine gerek kalmadan hayatına devam eder.

Doğrudan kalıp ile ilgili olmasa da bir yaklaşımı daha açıklayalım
Array-Backed Properties:
- Bir sınıfın sahip olduğu özellikleri (birbirleri ile ilişkili) ayrı ayrı field halinde tutmak yerine bir array içerisinde tutulmasıdır
    hep kullandığım Ofis örneğinden yola çıkarsak:
        + Ofisin ne kadar verimli olduğunu niteleyen "üretim kapasitesi", "malzeme depolama alanı" vb özelliklerimiz olsun.
        + Ofisleri kıyaslarken (örneğin hepsinin ortalaması) yapılacak hesaplama esnasında yapılacak işlemlerin tek tek field'lar üzerinden yapılması çok zordur
            çünkü her yeni eklenen özellik için yapılacak hesaplar değişecektir (ortalama aldığımız durumda fazladan bir toplama ve bölme işlemi n yerine n+1 yapılmalıdır).
        + Ancak bu özellikler bir Enum, enum'un son elemanı "count" olduğunda ve bir Array içerisinde depoladığımızda artık yapılan işlemler daha basit ve
            dinamil hale gelecektir. Örneğin,   int total_prod() { return accumulate(features_array.begin(), features_array.end(),0);}
- Şu örnek daha mantıklı olacaktır -> Bir sporcunun sahip olduğu özellikler (yetenek, hız, dayanıklılık, disiplin vb) ve ortalama güç hesabı


*/

#include <vector>
#include <numeric> // for std::accumulate


struct TotalProduction
{
  virtual int get_production() = 0;
};

struct SingleOffice : TotalProduction
{
  int production{0};

  SingleOffice() = default;

  explicit SingleOffice(const int p)
    : production{p}
  {
  }

  int get_production() override {
    return production;
  }
};

// there might be more than one office in a production
struct ProductionPlant : TotalProduction
{
    std::vector<int> productions{};

    void add_production(const int value)
    {
        productions.push_back(value);
    }

    int get_production() override 
    {
    return std::accumulate(productions.begin(), productions.end(), 0);
    }
};

