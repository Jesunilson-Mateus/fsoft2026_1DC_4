#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
private:
    int id;
    std::string name;
    double salary;

public:
    Employee(int id, std::string name, double salary);
    int getId();
    std::string getName();
    double getSalary();
    void setSalary(double newSalary);
};

#endif // EMPLOYEE_H
