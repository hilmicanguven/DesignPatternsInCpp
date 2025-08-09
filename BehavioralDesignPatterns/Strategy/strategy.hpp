/*

Strategy Design Pattern

Sistemin davranışının kısmen run-time da belli olmasına dayanır.
birçok algoritma genelde high ve low level olmak üzere parçalara ayrılabilir
high level genel ve ortak işlemler olarak düşünürken
low-level işlemler belli sınıfa/ürüne vb spesifik olur.

sistemin kesin davranışını run-time (dynamic) ve compile-time (static) olarak değiştirebiliriz
C++ literatüründe buna "policy" ismi de verilmektedir.

Örnek üzerinden nasıl yapılacağını daha iyi açıklayalım. Kurstaki örnek şu şekilde

farklı formatlarda (markdown ve html) bir output sağlayacağımızı varsayalım.

Dynamic Strategy (Hangi formatta output üreteceğini sahip olacağı bir member ile yapar)
    bu durumda kod halihazırda çalışıyorken main içerisinde "TextProcessor" sınıfının nasıl bir davranış
    sergileyeceği değiştirilebilir oldu. bunu Strategy olarak belirlenen output formatterlar aracılığı ile yaptık

Static Strategy (Hangi formatta output üreteceğini Template ile yapar)

*/

// Dynamic Strategy

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

enum class OutputFormat
{
  Markdown,
  Html
};

struct outputFormatStrategies
{
  virtual ~outputFormatStrategies() = default;
  virtual void add_list_item(ostringstream& oss, const string& item) = 0;
  virtual void start(ostringstream& oss) {};
  virtual void end(ostringstream& oss) {};
};

struct MarkdownoutputFormatStrategies : outputFormatStrategies
{
  void add_list_item(ostringstream& oss, const string& item) override
  {
    oss << " * " << item << endl;
  }
};

struct HtmloutputFormatStrategies : outputFormatStrategies
{
  void start(ostringstream& oss) override
  {
    oss << "<ul>" << endl;
  }

  void end(ostringstream& oss) override
  {
    oss << "</ul>" << endl;
  }

  void add_list_item(ostringstream& oss, const string& item) override
  {
    oss << "\t<li>" << item << "</li>" << endl;
  }
};

struct TextProcessor
{
  void clear()
  {
    oss.str("");
    oss.clear();
  }
  void append_list(const vector<string> items)
  {
    list_strategy->start(oss);
    for (auto& item : items)
      list_strategy->add_list_item(oss, item);
    list_strategy->end(oss);
  }

  void set_output_format(const OutputFormat format)
  {
    switch(format)
    {
    case OutputFormat::Markdown: 
      list_strategy = make_unique<MarkdownoutputFormatStrategies>();
      break;
    case OutputFormat::Html: 
      list_strategy = make_unique<HtmloutputFormatStrategies>();
      break;
    default:
      throw runtime_error("Unsupported strategy.");
    }
  }
  string str() const { return oss.str(); }
private:
  ostringstream oss;
  unique_ptr<outputFormatStrategies> list_strategy;
};

// Static Strategy

template<typename LS>
struct StaticTextProcessor
{
  void clear()
  {
    oss.str("");
    oss.clear();
  }
  void append_list(const vector<string> items)
  {
    list_strategy.start(oss);
    for (auto& item : items)
      list_strategy.add_list_item(oss, item);
    list_strategy.end(oss);
  }

  string str() const { return oss.str(); }
private:
  ostringstream oss;
  LS list_strategy;
};