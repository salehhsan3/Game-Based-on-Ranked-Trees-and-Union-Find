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
            int salary;
            int ID;
            SalaryID(int salary,int id):
                    salary(salary),
                    ID(id)
            {}
            SalaryID(const SalaryID& other) = default;
            bool operator==(const SalaryID& other)const
            {
                return ID == other.ID && salary == other.salary;
            }
            bool operator!=(const SalaryID& other)const
            {
                return ID != other.ID;
            }
            bool operator<(const SalaryID& other) const
            {
                if (salary == other.salary)
                {
                   return (this->ID < other.ID);
                }
                return salary < other.salary;
            }
            bool operator>(const SalaryID& other) const
            {
                return( (! ( (*this) < other) ) && (! ( (*this) == other) ) );
            }
            int getSalary()
            {
                return this->salary;
            }
            int getID()
            {
                return this->ID;
            }
    };
    class Employee
    {
    private:
        int id;
        int company_id;
        int grade;
        int salary;
    public:
        Employee(int id,int company_id, int grade,int salary=0):
            id(id),
            company_id(company_id),
            grade(grade),
            salary(salary)
        {}
        Employee(const Employee& emp) = default;
        Employee& operator=(const Employee& emp) = default;
        ~Employee() = default;
        int getEmployeeID();
        int getEmployeeGrade();
        int getEmployeeSalary();
        int getEmployersid();
        void increaseSalary(int increase);
        void bumpGrade(int bump);
        void changeGrade(int change);
        void UpdateCompanyID(int NewID);
        SalaryID getEmployeeSalaryID();

    };
    
    
}

#endif //LIBRARY2_H_EMPLOYEE_H
