//
// Created by Saleh on 01/06/2022.
//

#ifndef LIBRARY2_H_EMPLOYEE_H
#define LIBRARY2_H_EMPLOYEE_H

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
using std::shared_ptr;
using std::make_shared;

namespace ULIFB
{
    class SalaryID
    {
        public:
            long long int salary;
            long long int ID;
            SalaryID(int salary,int id):
                    salary(salary),
                    ID(id)
            {}
            SalaryID(const SalaryID& other) = default;
            bool operator==(const SalaryID& other)const
            {
                return ( (this->ID == other.ID) && (this->salary == other.salary) );
            }
            bool operator!=(const SalaryID& other) const
            {
                return ID != other.ID;
            }
            bool operator<(const SalaryID& other) const
            {
                if (salary == other.salary)
                {
                   return (this->ID < other.ID);
                }
                return (salary < other.salary);
            }
            bool operator>(const SalaryID& other) const
            {
                return( (! ( (*this) < other) ) && (! ( (*this) == other) ) );
            }
            bool operator<=(const SalaryID& other) const
            {
                return(! ( (*this) > other) );
            }
            bool operator>=(const SalaryID& other) const
            {
                return(! ( (*this) < other) );
            }
            long long int getSalary()
            {
                return this->salary;
            }
            long long int getID()
            {
                return this->ID;
            }
    };
    class Employee
    {
    private:
        long long int id;
        long long int company_id;
        long long int grade;
        long long int salary;
    public:
        Employee(long long int id,long long int company_id, int grade,long long int salary=0):
            id(id),
            company_id(company_id),
            grade(grade),
            salary(salary)
        {}
        Employee(const Employee& emp) = default;
        Employee& operator=(const Employee& emp) = default;
        ~Employee() = default;
        long long int getEmployeeID();
        long long int getEmployeeGrade();
        long long int getEmployeeSalary();
        long long int getEmployersid();
        void increaseSalary(long long int increase);
        void bumpGrade(long long int bump);
        void changeGrade(long long int change);
        void UpdateCompanyID(long long int NewID);
        SalaryID getEmployeeSalaryID();

    };
    
    
}

#endif //LIBRARY2_H_EMPLOYEE_H
