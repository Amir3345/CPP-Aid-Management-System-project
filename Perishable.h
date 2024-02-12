#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include <string>
#include "Item.h"


namespace sdds {
    class Perishable : public Item {
        std::string m_expiry;
        char* m_handling;
    
    public:
        // Rule of three constructors
        Perishable();
        Perishable(const Perishable& other);
       virtual ~Perishable();

       const std::string& expiry();
       virtual Perishable& operator=(const Perishable& other) ;
       virtual int readSku(std::istream& is) override;
       virtual std::ostream& display(std::ostream& os) const override;
       virtual std::ofstream& save(std::ofstream& file) const override;
       virtual std::ifstream& load(std::ifstream& file) override;
       virtual std::istream& read(std::istream& is) override ;
    };
}

#endif // SDDS_PERISHABLE_H
    