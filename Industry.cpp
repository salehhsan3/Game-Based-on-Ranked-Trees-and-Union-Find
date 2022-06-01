<<<<<<< HEAD
//
// Created by Saleh on 01/06/2022.
//

#include "Industry.h"

namespace ULIFB
{

    MultiStructures& Industry::getEmployeesMultiStructures()
    {
        return(this->employees);
    }

    StatusType Industry::AddEmployee(int employeeID, int companyID, int grade)
    {
        if (employeeID <= 0 || companyID <= 0 |( companyID > this->getNumberOfCompanies()) || grade < 0)
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS;
    }

    int Industry::getNumberOfCompanies()
    {
        return
        (this->number_of_companies);
    }

    StatusType Industry::RemoveEmployee(int employeeID)
    {
        if (employeeID <= 0)
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS;
    }

    StatusType Industry::AcquireCompany(int companyID1, int companyID2, double factor)
    {
        if (companyID1 <= 0 || (companyID1 > this->getNumberOfCompanies()) 
                || companyID2 <=0 || (companyID2 > this->getNumberOfCompanies())
                || factor <= 0)
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS;
    }

    StatusType Industry::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
    {
        if (employeeID < 0  || salaryIncrease < 0)
        {
            return INVALID_INPUT;
        }
        return SUCCESS;
    }

    StatusType Industry::PromoteEmployee(int employeeID, int bumpGrade)
    {
        if (employeeID <= 0 )
        {
            return INVALID_INPUT;
        }

        return SUCCESS;
    }

    StatusType Industry::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void * sumBumpGrade)
    {
        if (companyID < 0 || companyID > this->getNumberOfCompanies() || m <= 0)
        {
            return INVALID_INPUT;
        }
        return SUCCESS;
    }

    StatusType Industry::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade)
    {
        if (higherSalary < 0 || lowerSalary < 0 || (lowerSalary > higherSalary) || companyID < 0 || (companyID > this->getNumberOfCompanies()) || averageBumpGrade == nullptr)
        {
            return INVALID_INPUT;
        }

        
        return SUCCESS;
        
        
    }

    StatusType Industry::CompanyValue(int companyID, void * standing)
    {
        if (standing == nullptr || companyID <= 0 || (companyID > this->getNumberOfCompanies()) )
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS; 
        
    }

    StatusType Industry::BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade)//bonus
    {
        if ((lowerSalary > higherSalary) || (bumpGrade <= 0) )
        {
            return INVALID_INPUT;
        }
        
        
        return SUCCESS;
    }
=======
//
// Created by Saleh on 01/06/2022.
//

#include "Industry.h"

namespace ULIFB
{

    MultiStructures& Industry::getEmployeesMultiStructures()
    {
        return(this->employees);
    }

    StatusType Industry::AddEmployee(int employeeID, int companyID, int grade)
    {
        if (employeeID <= 0 || companyID <= 0 |( companyID > this->getNumberOfCompanies()) || grade < 0)
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS;
    }

    int Industry::getNumberOfCompanies()
    {
        return
        (this->number_of_companies);
    }

    StatusType Industry::RemoveEmployee(int employeeID)
    {
        if (employeeID <= 0)
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS;
    }

    StatusType Industry::AcquireCompany(int companyID1, int companyID2, double factor)
    {
        if (companyID1 <= 0 || (companyID1 > this->getNumberOfCompanies()) 
                || companyID2 <=0 || (companyID2 > this->getNumberOfCompanies())
                || factor <= 0)
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS;
    }

    StatusType Industry::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
    {
        if (employeeID < 0  || salaryIncrease < 0)
        {
            return INVALID_INPUT;
        }
        return SUCCESS;
    }

    StatusType Industry::PromoteEmployee(int employeeID, int bumpGrade)
    {
        if (employeeID <= 0 )
        {
            return INVALID_INPUT;
        }

        return SUCCESS;
    }

    StatusType Industry::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void * sumBumpGrade)
    {
        if (companyID < 0 || companyID > this->getNumberOfCompanies() || m <= 0)
        {
            return INVALID_INPUT;
        }
        return SUCCESS;
    }

    StatusType Industry::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade)
    {
        if (higherSalary < 0 || lowerSalary < 0 || (lowerSalary > higherSalary) || companyID < 0 || (companyID > this->getNumberOfCompanies()) || averageBumpGrade == nullptr)
        {
            return INVALID_INPUT;
        }

        
        return SUCCESS;
        
        
    }

    StatusType Industry::CompanyValue(int companyID, void * standing)
    {
        if (standing == nullptr || companyID <= 0 || (companyID > this->getNumberOfCompanies()) )
        {
            return INVALID_INPUT;
        }
        
        return SUCCESS; 
        
    }

    StatusType Industry::BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade)//bonus
    {
        if ((lowerSalary > higherSalary) || (bumpGrade <= 0) )
        {
            return INVALID_INPUT;
        }
        
        
        return SUCCESS;
    }
>>>>>>> 84c35b72e8d73b7153f47da86a8583f92bbecf0a
}