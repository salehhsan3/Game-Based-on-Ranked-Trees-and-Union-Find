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
        // hash_table<shared_ptr<Company>> companies_hash; // for the companies only includes the "owners"
        // instead of using a hashtable we'll just save the root of the group in the union find as the company_id of employee
        MultiStructures employees;
        int max_id;
    public:
        Industry(int number_of_companies):
            number_of_companies(number_of_companies),
            companies_union(UnionFind(number_of_companies)),
            // companies_hash(),
            employees(),
            max_id(0)
        {
            // for (int i = 1; i <= number_of_companies; i++)
            // {
            //     companies_hash.addElement(i,shared_ptr<Company>(companies_union.elements[i]->data)); // gets companies from the elements array and makes them shared_ptr! - correct implementation?
            //     // maybe consider inserting Company* into the hashtable instead of shared_ptr
            //     // we just initialized the UnionFind above therefore we can use elements as if it hasn't been altered yet!
            // }
        }

        ~Industry() = default;

        Industry(const Industry& ind) = default;

        Industry& operator=(const Industry& ind) = default;

        MultiStructures* getEmployeesMultiStructures();

        StatusType AddEmployee(int employeeID, int companyID, int grade);

        int getNumberOfCompanies();

        StatusType RemoveEmployee(int employeeID);

        StatusType AcquireCompany(int companyID1, int companyID2, double factor);

        StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease);

        StatusType PromoteEmployee(int employeeID, int bumpGrade);

        StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);

        StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary);

        StatusType CompanyValue(int companyID);
        double findSpecificCompanyValue(Company* comp,int companyID);

        // 20 point Bonus function:
        StatusType BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade);
    };
    
}

#endif //LIBRARY2_H_INDUSTRY_H
