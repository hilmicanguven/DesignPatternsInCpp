#include "adapter.hpp"

int main() 
{

    std::cout << "Legacy Cooler: \n";
    LegacyCooler legacy_cooler;
    client_cooler_app(legacy_cooler);
    
    std::cout << "--------------------------\n";
    
    std::cout << "New cooler is set up.\n";
    CoolerAdapter adapted_legacy_cooler;
    client_cooler_app(adapted_legacy_cooler);


    return 0;
}