#include "prototype.hpp"

int main() {
    
    // Creating a base prototype
    std::unique_ptr<Office> center_office = std::make_unique<CenterRDOffice>(6000,8086,"R&D Center", "Ankara", "Tunali Hilmi", "It happens when you work.");
    center_office->display_office_properties();

    std::unique_ptr<Office> second_office = center_office->clone();
    dynamic_cast<CenterRDOffice*>(second_office.get())->set_office_name("R&D Center (Additional Service Building)"); // Adjust address for the new office
    dynamic_cast<CenterRDOffice*>(second_office.get())->set_address("Ardahan", "Cumhuriyet"); // Adjust address for the new office
    dynamic_cast<CenterRDOffice*>(second_office.get())->set_motto("get up! stand up! dont give up the fight."); // Adjust address for the new office
    second_office->display_office_properties();

}