<<<<<<< HEAD
//
// Created by Saleh on 01/06/2022.
//

#include "Employee.h"

namespace ULIFB
{
    int Employee::getEmployeeID()
    {
        return id;
    }
    int Employee::getEmployeeGrade()
    {
        return grade;
    }
    int Employee::getEmployeeSalary()
    {
        return salary;
    }
    int Employee::getEmployersid()
    {
        return company_id;
    }
    void Employee::increaseSalary(int increase)
    {
        (this->salary)+=increase;
        return;
    }

    void Employee::bumpGrade(int bump)
    {
        if (bump > 0)
        {
            this->grade++;
        }
        return;
    }

    void Employee::changeGrade(int change)
    {
        (this->grade += change);
        return;
    }
    
    void Employee::UpdateCompanyID(int NewID)
    {

        this->company_id = NewID;
    }
    SalaryID Employee::getEmployeeSalaryID()
    {
        SalaryID to_ret = SalaryID(salary, id);
        return to_ret;
    }
=======
//
// Created by Saleh on 01/06/2022.
//

#include "Employee.h"

namespace ULIFB
{
    int Employee::getEmployeeID()
    {
        return id;
    }
    int Employee::getEmployeeGrade()
    {
        return grade;
    }
    int Employee::getEmployeeSalary()
    {
        return salary;
    }
    int Employee::getEmployersid()
    {
        return company_id;
    }
    void Employee::increaseSalary(int increase)
    {
        (this->salary)+=increase;
        return;
    }

    void Employee::bumpGrade(int bump)
    {
        if (bump > 0)
        {
            this->grade++;
        }
        return;
    }

    void Employee::changeGrade(int change)
    {
        (this->grade += change);
        return;
    }
    
    void Employee::UpdateCompanyID(int NewID)
    {

        this->company_id = NewID;
    }
    SalaryID Employee::getEmployeeSalaryID()
    {
        SalaryID to_ret = SalaryID(salary, id);
        return to_ret;
    }
>>>>>>> 84c35b72e8d73b7153f47da86a8583f92bbecf0a
}