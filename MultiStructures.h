//
// Created by Saleh on 01/06/2022.
//

#ifndef EMPLOYEE_H_MULTISTRUCTURES_H
#define EMPLOYEE_H_MULTISTRUCTURES_H

#include "Employee.h"
#include "AO_AVL_Tree.h"
#include "AO_AVL_Tree_Modified.h"

namespace ULIFB
{
    class MultiStructures
    {
    private:
        // Hash_Table employees; // hashtable for all the employees 
        AVL_Tree_Modified<SalaryID,shared_ptr<Employee>> employees_with_salary; //ranktree for employees with salary>0 bonus version
        AVL_Tree<SalaryID,shared_ptr<Employee>> employees_with_salary; //ranktree for employees with salary>0
        int number_of_employees_with_no_salary;
        int sum_of_grades_for_emp_with_no_salary;
        int grade_bump_for_zero_salary;
    public:
        MultiStructures() = default; // is default the correct implementation?
        ~MultiStructures() = default;
        MultiStructures(const MultiStructures& multistruct) = default;
        MultiStructures& operator=(const MultiStructures& multistruct) = default;
        shared_ptr<Employee>& findEmployee(SalaryID sal_id); // unchanged even after bonus changes!
                                        // non bonus functions //
        void addEmployee(SalaryID sal_id ,shared_ptr<Employee>& emp_to_add);
        void removeEmployee(int emp_id);
        void MergeStructures(MultiStructures& other);
        void IncreaseEmployeeSalary(int emp_id, int increase);
        void promoteEmployee(int emp_id, int bump);
        int SumOfBumpGradeBetweenTopWorkersByGroup(int number_of_top_workers);
        double AverageBumpGradeBetweenSalaryByGroup(int lowerSalary, int higherSalary);
                                       // bonus functions // may not be needed!
    };
    
    
    
} // namespace ULIFB


#endif //EMPLOYEE_H_MULTISTRUCTURES_H
