#include "CreationalDesignPatterns/Builder/builder.hpp"

int main(){

    int temp = 0;

    Office center_office = Office::Builder()
        .cooler_builder()
            .set_cooler_type(100)
        .hw_builder()
            .set_computer_brand(101);

    center_office.display_office_properties();
    
    OfficeBaseBuilder o_builder = Office::Builder();

    Office production_office = o_builder.cooler_builder()
                            .set_cooler_type(10)
                         .hw_builder()
                            .set_computer_brand(11);

    production_office.display_office_properties();

    Office o = Office::Builder();
    o.display_office_properties();

    return 0;

}