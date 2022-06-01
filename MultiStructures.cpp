//
// Created by Saleh on 01/06/2022.
//

#include "MultiStructures.h"


namespace ULIFB
{
    void MultiStructures::addEmployee(SalaryID sal_id,shared_ptr<Employee>& emp_to_add)
    {
        
    }

    shared_ptr<Employee> MultiStructures::findEmployee(int emp_id)
    {
        // complexity is O(1) on average!
        Node<int,shared_ptr<Employee>>* emp_to_find =  this->employees.Find(emp_id);
        if (emp_to_find != nullptr)
        {
            return(*(emp_to_find->data)); // returns the data if the emp was found!
        }
        return nullptr; // emp was not found!
    }

    void MultiStructures::removeEmployee(int emp_id)
    {
        // complexity is O(log(n))!
        shared_ptr<Employee> emp_to_find = this->findEmployee(emp_id);
        if (emp_to_find == nullptr)
        {
            return;
        }

        if (emp_to_find->getEmployeeSalary() == 0) //different case depending on the employee's salary!
        {
            this->number_of_employees_with_no_salary--;
            this->sum_of_grades_for_emp_with_no_salary-=emp_to_find->getEmployeeGrade();
            return;
        }
        // else if salary is bigger than zero remove him from the tree!
        employees_with_salary.removeNode(SalaryID(emp_to_find->getEmployeeSalary(),emp_id));
    }

    void MultiStructures::IncreaseEmployeeSalary(int emp_id, int increase)
    {
        // complexity is O(log(n))!
        shared_ptr<Employee> emp_to_find =  this->findEmployee(emp_id);
        if (emp_to_find == nullptr)
        {
            return; // should never get here!
        }
        if (emp_to_find->getEmployeeSalary() == 0)
        {
            this->number_of_employees_with_no_salary--;
            this->sum_of_grades_for_emp_with_no_salary-=emp_to_find->getEmployeeGrade();
            emp_to_find->increaseSalary(increase);
            this->employees_with_salary.addNode(SalaryID(emp_to_find->getEmployeeSalary(),emp_id),emp_to_find,emp_to_find->getEmployeeGrade()); // im not sure if this is the correct implementation. ie, maybe we should pass salary or something else instead of level!
        }
        else if (emp_to_find->getEmployeeSalary() > 0)
        {
            emp_to_find->increaseSalary(increase);
            this->employees_with_salary.removeNode(SalaryID(emp_to_find->getEmployeeSalary(),emp_id)); // remove old node!
            this->employees_with_salary.addNode(SalaryID(emp_to_find->getEmployeeSalary(),emp_id),emp_to_find,emp_to_find->getEmployeeGrade()); // im not sure if this is the correct implementation. ie, maybe we should pass salary or something else instead of level!
        }
        
    }

    void MultiStructures::promoteEmployee(int emp_id, int bump)
    {

    }

    int MultiStructures::SumOfBumpGradeBetweenTopWorkersByGroup(int number_of_top_workers)
    {
        shared_ptr<Employee> *emp_to_find =  this->employees_with_salary.Select(employees_with_salary.root,number_of_top_workers)->data;
        if (emp_to_find == nullptr)
        {
            return -1; // only returns this if the employee was not found!
        }
        return(this->employees_with_salary.findSumSmaller(emp_to_find->get()->getEmployeeSalaryID())); // is this the correct implementation of finding the sum of sons?
        
    }

    double MultiStructures::AverageBumpGradeBetweenSalaryByGroup(int lowerSalary, int higherSalary)
    {

    }

} // namespace ULIFB
