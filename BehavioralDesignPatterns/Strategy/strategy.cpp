#include "strategy.hpp"

int main()
{
    vector<string> msgs{"yilmaz", "ilkkan", "ersoy"};
    
    TextProcessor text_processor;
    
    text_processor.set_output_format(OutputFormat::Markdown);
    text_processor.append_list(msgs);
    cout << text_processor.str() << endl;
    text_processor.clear();
    
    // now switch different format
    
    text_processor.set_output_format(OutputFormat::Html);
    text_processor.append_list(msgs);
    cout << text_processor.str() << endl;
    text_processor.clear();
    
    
    StaticTextProcessor<HtmloutputFormatStrategies> static_html_text_processor;
    
    vector<string> msgs_static{"aragorn", "legolas", "gimli"};
    static_html_text_processor.append_list(msgs_static);
    cout << static_html_text_processor.str() << endl;
    
    StaticTextProcessor<MarkdownoutputFormatStrategies> static_md_text_processor;
    
    vector<string> msgs_static2{"frodo", "samwise", "pipping", "merry"};
    static_md_text_processor.append_list(msgs_static2);
    cout << static_md_text_processor.str() << endl;


    return 0;
}