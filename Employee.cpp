//
// Created by Saleh on 01/06/2022.
//

#include "Employee.h"

namespace ULIFB
{
    long long int Employee::getEmployeeID()
    {
        return id;
    }
    long long int Employee::getEmployeeGrade()
    {
        return grade;
    }
    long long int Employee::getEmployeeSalary()
    {
        return salary;
    }
    long long int Employee::getEmployersid()
    {
        return company_id;
    }
    void Employee::increaseSalary(long long int increase)
    {
        (this->salary)+=increase;
        return;
    }

    void Employee::bumpGrade(long long int bump)
    {
        if (bump > 0)
        {
            this->grade+= bump;
        }
        return;
    }

    void Employee::changeGrade(long long int change)
    {
        (this->grade += change);
        return;
    }
    
    void Employee::UpdateCompanyID(long long int NewID)
    {

        this->company_id = NewID;
    }
    SalaryID Employee::getEmployeeSalaryID()
    {
        SalaryID to_ret = SalaryID(salary, id);
        return to_ret;
    }
}