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

// #include "CreationalDesignPatterns/Factories/factories.hpp"

// int main() {
//     {
//         std::unique_ptr<OfficeFactory> factory_sw_department = std::make_unique<RDCenterOfficeFactory>();
//         auto cooler = factory_sw_department->createCooler();
//         auto computers = factory_sw_department->createComputer();
        
//         cooler->cool();
//         computers->compute();
//     }

//     {
//         std::unique_ptr<ProductionFactoryFactory> production_plant = std::make_unique<ProductionFactoryFactory>();
//         auto cooler = production_plant->createCooler();
//         auto computers = production_plant->createComputer();
        
//         cooler->cool();
//         computers->compute();
//     }
// }


// #include "CreationalDesignPatterns/Prototype/prototype.hpp"

// int main() {
    
//     // Creating a base prototype
//     std::unique_ptr<Office> center_office = std::make_unique<CenterRDOffice>(6000,8086,"R&D Center", "Ankara", "Tunali Hilmi", "It happens when you work.");
//     center_office->display_office_properties();

//     std::unique_ptr<Office> second_office = center_office->clone();
//     dynamic_cast<CenterRDOffice*>(second_office.get())->set_office_name("R&D Center (Additional Service Building)"); // Adjust address for the new office
//     dynamic_cast<CenterRDOffice*>(second_office.get())->set_address("Ardahan", "Cumhuriyet"); // Adjust address for the new office
//     dynamic_cast<CenterRDOffice*>(second_office.get())->set_motto("get up! stand up! dont give up the fight."); // Adjust address for the new office
//     second_office->display_office_properties();

// }

// #include "CreationalDesignPatterns/Singleton/singleton.hpp"

// int main() {

//     SingletonOfficeDatabase::get_reference().display_database();

//     return 0;
// }

// #include "CreationalDesignPatterns/Adapter/adapter.hpp"

// int main() 
// {

//     std::cout << "Legacy Cooler: \n";
//     LegacyCooler legacy_cooler;
//     client_cooler_app(legacy_cooler);
    
//     std::cout << "--------------------------\n";
    
//     std::cout << "New cooler is set up.\n";
//     CoolerAdapter adapted_legacy_cooler;
//     client_cooler_app(adapted_legacy_cooler);


//     return 0;
// }