<<<<<<< HEAD
#include "Industry.h"

    void *Init(int k)
    {
        
        return (k > 0) ? static_cast<void*>(new ULIFB::Industry(k)) : NULL; // if k <= 0 it's considered as FAILURE!
    }

    StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->AddEmployee(employeeID,companyID,grade);
    }

    StatusType RemoveEmployee(void *DS, int employeeID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->RemoveEmployee(employeeID);
    }

    StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->AcquireCompany(companyID1,companyID2,factor);
    }

    StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->EmployeeSalaryIncrease(employeeID,salaryIncrease);
    }

    StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->PromoteEmployee(employeeID,bumpGrade);
    }

    StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m, void * sumBumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->SumOfBumpGradeBetweenTopWorkersByGroup(companyID,m,sumBumpGrade);
    }

    StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->AverageBumpGradeBetweenSalaryByGroup(companyID,lowerSalary,higherSalary,averageBumpGrade);
    }

    StatusType CompanyValue(void *DS, int companyID, void * standing)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->CompanyValue(companyID,standing);
    }

    StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->BumpGradeToEmployees(lowerSalary,higherSalary,bumpGrade);
    }

    void Quit(void** DS)
    {
        if (DS == NULL || (*DS) == NULL)
        {
            return;
        }
        delete static_cast<ULIFB::Industry*>(*DS);
        *DS =nullptr;
    }
=======
#include "Industry.h"

    void *Init(int k)
    {
        
        return (k > 0) ? static_cast<void*>(new ULIFB::Industry(k)) : NULL; // if k <= 0 it's considered as FAILURE!
    }

    StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->AddEmployee(employeeID,companyID,grade);
    }

    StatusType RemoveEmployee(void *DS, int employeeID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->RemoveEmployee(employeeID);
    }

    StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->AcquireCompany(companyID1,companyID2,factor);
    }

    StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->EmployeeSalaryIncrease(employeeID,salaryIncrease);
    }

    StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->PromoteEmployee(employeeID,bumpGrade);
    }

    StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m, void * sumBumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->SumOfBumpGradeBetweenTopWorkersByGroup(companyID,m,sumBumpGrade);
    }

    StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->AverageBumpGradeBetweenSalaryByGroup(companyID,lowerSalary,higherSalary,averageBumpGrade);
    }

    StatusType CompanyValue(void *DS, int companyID, void * standing)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->CompanyValue(companyID,standing);
    }

    StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<ULIFB::Industry*>(DS)->BumpGradeToEmployees(lowerSalary,higherSalary,bumpGrade);
    }

    void Quit(void** DS)
    {
        if (DS == NULL || (*DS) == NULL)
        {
            return;
        }
        delete static_cast<ULIFB::Industry*>(*DS);
        *DS =nullptr;
    }
>>>>>>> 84c35b72e8d73b7153f47da86a8583f92bbecf0a
