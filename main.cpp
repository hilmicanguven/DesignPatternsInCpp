// #include "CreationalDesignPatterns/Builder/builder.hpp"

// int main(){

//     int temp = 0;

//     Office center_office = Office::Builder("R&D Center Office")
//         .cooler_builder()
//             .set_cooler_type(100)
//         .hw_builder()
//             .set_computer_brand(101).get_office();

//     center_office.display_office_properties();
    
    
    
//     OfficeBaseBuilder o_builder = Office::Builder("Production Plant");

//     Office production_office = o_builder.cooler_builder()
//                             .set_cooler_type(10)
//                          .hw_builder()
//                             .set_computer_brand(11);

//     production_office.display_office_properties();


//     return 0;

// }

#include "CreationalDesignPatterns/Factories/factories.hpp"

int main() {
    {
        std::unique_ptr<OfficeFactory> factory_sw_department = std::make_unique<RDCenterOfficeFactory>();
        auto cooler = factory_sw_department->createCooler();
        auto computers = factory_sw_department->createComputer();
        
        cooler->cool();
        computers->compute();
    }

    {
        std::unique_ptr<ProductionFactoryFactory> production_plant = std::make_unique<ProductionFactoryFactory>();
        auto cooler = production_plant->createCooler();
        auto computers = production_plant->createComputer();
        
        cooler->cool();
        computers->compute();
    }
}