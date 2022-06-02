//
// Created by Saleh on 01/06/2022.
//

#include "Industry.h"

namespace ULIFB
{
    int Industry::getNumberOfCompanies()
    {
        return
        (this->number_of_companies);
    }

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

    StatusType Industry::RemoveEmployee(int employeeID)
    {
        // complexity is O(log(n)) on average
        if (employeeID <= 0)
        {
            return INVALID_INPUT;
        }
        shared_ptr<Employee> emp_to_find =  this->getEmployeesMultiStructures().findEmployee(employeeID);
        if (emp_to_find == nullptr)
        {
            return FAILURE;
        }
        int company_id = emp_to_find->getEmployersid();
        this->companies_hash.Find(company_id)->data->get()->getEmployeesMultiStructures().removeEmployee(employeeID); // remove from company
        this->getEmployeesMultiStructures().removeEmployee(employeeID); // remove from Industry
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
        // complexity is O(log(n))! on average
        if (employeeID <= 0  || salaryIncrease <= 0)
        {
            return INVALID_INPUT;
        }
        shared_ptr<Employee> emp_to_find =  this->getEmployeesMultiStructures().findEmployee(employeeID);
        if (emp_to_find == nullptr)
        {
            return FAILURE;
        }
        int company_id = emp_to_find->getEmployersid();
        this->companies_hash.Find(company_id)->data->get()->getEmployeesMultiStructures().IncreaseEmployeeSalary(employeeID,salaryIncrease); // increasesalary in company
        this->getEmployeesMultiStructures().IncreaseEmployeeSalary(employeeID,salaryIncrease); // increasesalary in Industry
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
        // complexity is O(log*(k) + log(n)) amortized on average
        if (companyID < 0 || companyID > this->getNumberOfCompanies() || m <= 0)
        {
            return INVALID_INPUT;
        }
        MultiStructures multi =  companyID == 0 ? this->employees : companies_union.find(companyID)->data->getEmployeesMultiStructures(); // get the correct multistructure to work with!
        // now we need to find the employee whose rank is m!
        int sum = multi.SumOfBumpGradeBetweenTopWorkersByGroup(m);
        if (sum == -1)
        {
            return FAILURE;
        }
        
        (*(int *)sumBumpGrade) = sum;
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
        // complexity is O(log*(k)) amortized
        if (standing == nullptr || companyID <= 0 || (companyID > this->getNumberOfCompanies()) )
        {
            return INVALID_INPUT;
        }

        Company* comp_to_find = companies_union.find(companyID)->data;
        // we know that the company has to exist because its ID is legal therefore there's no need to check if it was found.
        double owner_value = comp_to_find->getCompanyValue();
        double offset = companies_union.findOffSet(companyID);
        double real_value = owner_value - offset;
        (*(double *)standing) = real_value;

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
}