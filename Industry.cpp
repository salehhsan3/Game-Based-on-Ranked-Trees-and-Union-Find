//
// Created by Saleh on 01/06/2022.
//

#include "Industry.h"

namespace ULIFB
{

    void mergeGroupData(Company* new_root, Company* old_root){
        new_root->getEmployeesMultiStructures().MergeStructures(old_root->getEmployeesMultiStructures(), new_root->getCompanyId() );
    }

    //************************************************************************************************************
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

        if(employees.findEmployee(employeeID)){
            return FAILURE;
        }

        shared_ptr<Employee> emp_to_add = make_shared<Employee>(employeeID,0,grade,companyID);
        SalaryID sal_id = SalaryID(0, employeeID);
        employees.addEmployee(sal_id, emp_to_add);

        Company* company = companies_union.find(companyID)->data;
        company->getEmployeesMultiStructures().addEmployee(sal_id, emp_to_add);
        if (max_id < employeeID){
            max_id = employeeID;
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
        //both of the companies are in the same group already
        Up_Tree_node<int, Company*>* root1 = companies_union.find(companyID1);
        Up_Tree_node<int, Company*>* root2 = companies_union.find(companyID2);
        if(root1 == root2){
            return SUCCESS;
        }

        //union
        Up_Tree_node<int, Company*>* new_root = companies_union.UnionGroups(companyID1, companyID2);

        //update value
        double value1 = root1->data->getCompanyValue();
        double value2 = root2->data->getCompanyValue();
        double new_value = ((value1 + value2)*factor);///////////////////////////
        new_root->data->setCompanyValue(new_value);

        //find old root
        Up_Tree_node<int, Company*>* old_root = nullptr;
        if(root1->parent){
            old_root = root1;
        }
        else{
            old_root = root2;
        }

        //merge MultiStructure
        mergeGroupData(new_root->data, old_root->data);

        ////////something must be done with the external hash table of the companies

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

        if(employees.findEmployee(employeeID)){
            return FAILURE;
        }

        if(bumpGrade < 0 ){ //CHECK THIS
            return SUCCESS;
        }
        shared_ptr<Employee> employee_to_promote = employees.findEmployee(employeeID);
        Company* comp = companies_union.find(employee_to_promote->getEmployersid())->data;
        employee_to_promote->bumpGrade(bumpGrade);
        if (employee_to_promote->getEmployeeSalary() == 0 ){
            comp->getEmployeesMultiStructures().bumpGradeForSumOfGradesForEmpWhithNoSalary(bumpGrade);
            employees.bumpGradeForSumOfGradesForEmpWhithNoSalary(bumpGrade);
            return SUCCESS;
        }
        AVL_Tree<SalaryID,shared_ptr<Employee>>* comp_tree_to_update = companies_union.find(employee_to_promote->getEmployersid())->data
                                                                ->getEmployeesMultiStructures().getEmployeesWithSalaryTree();
        comp_tree_to_update->removeNode(employee_to_promote->getEmployeeSalaryID());
        comp_tree_to_update->addNode(employee_to_promote->getEmployeeSalaryID(), employee_to_promote, employee_to_promote->getEmployeeGrade());

        AVL_Tree<SalaryID,shared_ptr<Employee>>* external_tree_to_update = employees.getEmployeesWithSalaryTree();
        external_tree_to_update->removeNode(employee_to_promote->getEmployeeSalaryID());
        external_tree_to_update->addNode(employee_to_promote->getEmployeeSalaryID(), employee_to_promote, employee_to_promote->getEmployeeGrade());

        return SUCCESS;
        //we need to find the root of the tree that includes
        //company in order to update the employee grade in employees tree
        //after we get the tree of the employees remove the employee and add it again updated


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

        if (companyID == 0){
            shared_ptr<Employee> fake_max = make_shared<Employee>(max_id+1,0,0,higherSalary);
            SalaryID max_sal_id = SalaryID(0, max_id+1);
            shared_ptr<Employee> fake_min = make_shared<Employee>(0,0,0,lowerSalary);
            SalaryID min_sal_id = SalaryID(0, 0);

            //add fakes to tree
            AVL_Tree<SalaryID,shared_ptr<Employee>>* tree = employees.getEmployeesWithSalaryTree();
            tree->addNode(max_sal_id, fake_max, 0);
            tree->addNode(min_sal_id, fake_min, 0);

            int num_of_employees_in_bounds = 0;
            int sum_of_grades = 0;

            int rank1 = tree->findRank(max_sal_id);
            int rank2 = tree->findRank(min_sal_id);

            int sum1 = tree->findSumSmaller(max_sal_id);
            int sum2 = tree->findSumSmaller(min_sal_id);

            num_of_employees_in_bounds = rank1 - rank2 -1;
            sum_of_grades = sum1 - sum2;

            if (lowerSalary == 0){
                num_of_employees_in_bounds += employees.getNumOfEmployeesWithNoSalary();
                sum_of_grades += employees.getSumOfGradesForEmployeesWithNoSalary();
            }
            tree->removeNode(max_sal_id);
            tree->removeNode(min_sal_id);
            if (num_of_employees_in_bounds == 0){
                return FAILURE;
            }
            *(double*)averageBumpGrade = (sum_of_grades/num_of_employees_in_bounds);
            return SUCCESS;
        }

        Company* company = companies_union.find(companyID)->data;
        shared_ptr<Employee> fake_max = make_shared<Employee>(max_id+1,0,0,higherSalary);
        SalaryID max_sal_id = SalaryID(0, max_id+1);
        shared_ptr<Employee> fake_min = make_shared<Employee>(0,0,0,lowerSalary);
        SalaryID min_sal_id = SalaryID(0, 0);

        //add fakes to tree
        AVL_Tree<SalaryID,shared_ptr<Employee>>* tree = company->getEmployeesMultiStructures().getEmployeesWithSalaryTree();
        tree->addNode(max_sal_id, fake_max, 0);
        tree->addNode(min_sal_id, fake_min, 0);

        int num_of_employees_in_bounds = 0;
        int sum_of_grades = 0;

        int rank1 = tree->findRank(max_sal_id);
        int rank2 = tree->findRank(min_sal_id);

        int sum1 = tree->findSumSmaller(max_sal_id);
        int sum2 = tree->findSumSmaller(min_sal_id);

        num_of_employees_in_bounds = rank1 - rank2 -1;
        sum_of_grades = sum1 - sum2;

        if (lowerSalary == 0){
            num_of_employees_in_bounds += company->getEmployeesMultiStructures().getNumOfEmployeesWithNoSalary();
            sum_of_grades += company->getEmployeesMultiStructures().getSumOfGradesForEmployeesWithNoSalary();
        }
        tree->removeNode(max_sal_id);
        tree->removeNode(min_sal_id);
        if (num_of_employees_in_bounds == 0){
            return FAILURE;
        }
        *(double*)averageBumpGrade = (sum_of_grades/num_of_employees_in_bounds);/////////////check
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