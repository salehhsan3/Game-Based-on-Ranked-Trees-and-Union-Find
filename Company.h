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
        long long int id;
        long double value;
        long double enterprise_value;
        MultiStructures employees;
    public:
        Company(long long int id = 0):
            id(id),
            value((long double)id), // maybe better to convert the integer into a double
            enterprise_value( (long double)id),
            employees()
        {}
        ~Company() = default;
        Company(const Company& comp) = default;
        Company& operator=(const Company& comp) = default;
        MultiStructures* getEmployeesMultiStructures();
        long long int getCompanyId();
        long double getCompanyValue();
        long double getEnterpriseValue();
        void updateEnterpriseValue(long double new_value);
        void setCompanyValue( long double value);
        void IncreaseCompanyValue(long double increase);
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
