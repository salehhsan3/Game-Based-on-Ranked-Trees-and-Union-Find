//
// Created by Saleh on 01/06/2022.
//

#ifndef LIBRARY2_H_INDUSTRY_H
#define LIBRARY2_H_INDUSTRY_H

#include "library2.h"
#include "Company.h"
#include "Union-Find.h"

namespace ULIFB
{
    class Industry
    {
    private:
        int number_of_companies;
        UnionFind companies_union; // for the companies
        hash_table<shared_ptr<Company>> companies_hash; // for the companies only includes the "owners"
        MultiStructures employees;
    public:
        Industry(int number_of_companies):
            number_of_companies(number_of_companies),
            companies_union(UnionFind(number_of_companies)),
            companies_hash(),
            employees()
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
