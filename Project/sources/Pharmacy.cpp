#include <iostream>

class Pharmacy {
public:
    void displayInfo() {
        std::cout << "Welcome to the Pharmacy system!" << std::endl;
    }
};

int main() {
    Pharmacy pharmacy;
    pharmacy.displayInfo();
    return 0;
}