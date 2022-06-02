//
// Created by Saleh on 01/06/2022.
//

#include "Company.h"

namespace ULIFB
{

    MultiStructures& Company::getEmployeesMultiStructures()
    {
        return(this->employees);
    }

    int Company::getCompanyId()
    {
        return(this->id);
    }

    double Company::getCompanyValue()
    {
        return(this->value);
    }

    void Company::IncreaseCompanyValue(double increase)
    {
        this->value+=increase;
    }
    
    
    // void Company::addEmployee(SalaryID sal_id, shared_ptr<Employee>& emp_to_add)
    // {

    // }

    // shared_ptr<Employee>& Company::findEmployee(SalaryID sal_id)
    // {

    // }

    // void Company::removeEmployee(int emp_id)
    // {

    // }

    // void Company::IncreaseEmployeeSalary(int emp_id, int increase)
    // {

    // }

    // void Company::promoteEmployee(int emp_id, int bump)
    // {

    // }

    // int Company::SumOfBumpGradeBetweenTopWorkersByGroup(int number_of_top_workers)
    // {

    // }

    // double Company::AverageBumpGradeBetweenSalaryByGroup(int lowerSalary, int higherSalary)
    // {

    // }

}