#include "factories.hpp"

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