//
// Created by Saleh on 01/06/2022.
//

#ifndef EMPLOYEE_H_MULTISTRUCTURES_H
#define EMPLOYEE_H_MULTISTRUCTURES_H

#include "Employee.h"
#include "AO_AVL_Tree.h"
//#include "AO_AVL_Tree_Modified.h"
#include "hashtable.h"

namespace ULIFB
{
    class MultiStructures
    {
    private:
        hash_table<shared_ptr<Employee>> employees; // hashtable for all the employees 
        // AVL_Tree_Modified<SalaryID,shared_ptr<Employee>> employees_with_salary_bonus; //ranktree for employees with salary>0 bonus version
        AVL_Tree<SalaryID,shared_ptr<Employee>> employees_with_salary; //ranktree for employees with salary>0
        int number_of_employees_with_no_salary;
        int sum_of_grades_for_emp_with_no_salary;
        int total_num_of_employees;
        //int grade_bump_for_zero_salary;//omima ****no need for this
    public:
        MultiStructures() = default; // is default the correct implementation?
        ~MultiStructures() = default;
        MultiStructures(const MultiStructures& multistruct) = default;
        MultiStructures& operator=(const MultiStructures& multistruct) = default;
        shared_ptr<Employee> findEmployee(int emp_id); // unchanged even after bonus changes!
                                        // non bonus functions //
        void addEmployee(SalaryID sal_id ,shared_ptr<Employee> emp_to_add);
        void removeEmployee(int emp_id);
        void UpdateOwnerIdInHash(int new_owner);
        hash_table<shared_ptr<Employee>>* getEmployesHashTable();
        void MergeHashTable(hash_table<shared_ptr<Employee>> *other);
        AVL_Tree<SalaryID,shared_ptr<Employee>>* getEmployessWithSalaryTree();
        void MoveTreeToArray(shared_ptr<Employee> * array, tree_node<SalaryID, shared_ptr<Employee> >* node, int* counter_ptr, int num);
        void visitInOrder3(shared_ptr<Employee> * array, tree_node<SalaryID, shared_ptr<Employee> >* node, int* counter_ptr, int num);
        tree_node<SalaryID, shared_ptr<Employee>> *createTreeFromSortedArrAuxForSalary(shared_ptr<Employee> array[], int start,
                                                                    int end, tree_node<SalaryID, shared_ptr<Employee>> *parent);
        void merge_func(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,shared_ptr<Employee>  arr3[]);
        void UpdataRankTreeFields(tree_node<SalaryID, shared_ptr<Employee>>* root);
        void MergeStructures(MultiStructures& other, int root_id);
        void IncreaseEmployeeSalary(int emp_id, int increase);
        void promoteEmployee(int emp_id, int bump);
        int SumOfBumpGradeBetweenTopWorkersByGroup(int number_of_top_workers);
        void bumpGradeForSumOfGradesForEmpWhithNoSalary(int bumpGrade);
        AVL_Tree<SalaryID,shared_ptr<Employee>>* getEmployeesWithSalaryTree();
        int getNumOfEmployeesWithNoSalary();
        int getSumOfGradesForEmployeesWithNoSalary();
        double AverageBumpGradeBetweenSalaryByGroup(int lowerSalary, int higherSalary);
                                       // bonus functions // may not be needed!

    };
    
    
    
} // namespace ULIFB


#endif //EMPLOYEE_H_MULTISTRUCTURES_H
