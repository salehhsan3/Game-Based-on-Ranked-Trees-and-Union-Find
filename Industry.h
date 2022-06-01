//
// Created by Saleh on 01/06/2022.
//

#ifndef LIBRARY2_H_INDUSTRY_H
#define LIBRARY2_H_INDUSTRY_H

#include "library2.h"
#include "Company.h"
// #include "UnionFind.h"

namespace ULIFB
{
    class Industry
    {
    private:
        int number_of_companies;
        // UnionFind companies_union; // for the companies
        // Hashtable companies_hash; // for the companies only includes the "owners"
        MultiStructures employees;
    public:
        Industry(int number_of_companies):
            number_of_companies(number_of_companies)

        {}

        ~Industry() = default;

        Industry(const Industry& ind) = default;

        Industry& operator=(const Industry& ind) = default;

        MultiStructures& getEmployeesMultiStructures();

        StatusType AddEmployee(int employeeID, int companyID, int grade);

        int getNumberOfCompanies();

        StatusType RemoveEmployee(int employeeID);

        StatusType AcquireCompany(int companyID1, int companyID2, double factor);

        StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease);

        StatusType PromoteEmployee(int employeeID, int bumpGrade);

        StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void * sumBumpGrade);

        StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade);

        StatusType CompanyValue(int companyID, void * standing);

        // 20 point Bonus function:
        StatusType BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade);
    };
    
}

#endif //LIBRARY2_H_INDUSTRY_H
