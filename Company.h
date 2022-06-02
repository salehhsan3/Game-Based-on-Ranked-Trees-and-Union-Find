//
// Created by Saleh on 01/06/2022.
//

#ifndef LIBRARY2_H_COMPANY_H
#define LIBRARY2_H_COMPANY_H

#include "MultiStructures.h"

namespace ULIFB
{
    class Company
    {
    private:
        int id;
        double value;
        MultiStructures employees;
    public:
        Company(int id = 0):
            id(id),
            value((double)id), // maybe better to convert the integer into a double
            employees()
        {}
        ~Company() = default;
        Company(const Company& comp) = default;
        Company& operator=(const Company& comp) = default;
        MultiStructures& getEmployeesMultiStructures();
        int getCompanyId();
        double getCompanyValue();
        void IncreaseCompanyValue(double increase);
                                // the following fuctions are potentially not needed! //
        // shared_ptr<Employee>& findEmployee(SalaryID sal_id); 
        // void addEmployee(SalaryID sal_id, shared_ptr<Employee>& emp_to_add);
        // void removeEmployee(int emp_id);
        // void IncreaseEmployeeSalary(int emp_id, int increase);
        // void promoteEmployee(int emp_id, int bump);
        // int SumOfBumpGradeBetweenTopWorkersByGroup(int number_of_top_workers);
        // double AverageBumpGradeBetweenSalaryByGroup(int lowerSalary, int higherSalary);
    };
    
    
}

#endif //LIBRARY2_H_COMPANY_H
