// Employee class implementation
#include <string>

class Employee {
private:
    std::string name;
    int id;
public:
    Employee(std::string empName, int empId) : name(empName), id(empId) {}

    std::string getName() const { return name; }
    int getId() const { return id; }
};
