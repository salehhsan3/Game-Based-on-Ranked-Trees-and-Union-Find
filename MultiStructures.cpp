//
// Created by Saleh on 01/06/2022.
//

#include "MultiStructures.h"


namespace ULIFB
{
    void MultiStructures::addEmployee(SalaryID sal_id,shared_ptr<Employee>& emp_to_add)
    {
        employees.addElement(emp_to_add->getEmployeeID(), emp_to_add);
        number_of_employees_with_no_salary++;
        sum_of_grades_for_emp_with_no_salary += emp_to_add->getEmployeeGrade();
        total_num_of_employees++;

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
            this->total_num_of_employees;
            this->sum_of_grades_for_emp_with_no_salary-=emp_to_find->getEmployeeGrade();
            return;
        }
        // else if salary is bigger than zero remove him from the tree!
        employees_with_salary.removeNode(SalaryID(emp_to_find->getEmployeeSalary(),emp_id));
        this->total_num_of_employees;
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
            return;
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
        // complexity is O(log*(k) + log(n))
        shared_ptr<Employee> *emp_to_find =  this->employees_with_salary.Select(employees_with_salary.root,number_of_top_workers)->data;
        if (emp_to_find == nullptr)
        {
            return -1; // only returns this if the employee was not found! ie, there's no employee whose rank in number_of_top_worker!
        }
        return(this->employees_with_salary.findSumSmaller(emp_to_find->get()->getEmployeeSalaryID())); // is this the correct implementation of finding the sum of sons?
        
    }

    double MultiStructures::AverageBumpGradeBetweenSalaryByGroup(int lowerSalary, int higherSalary)
    {
        return 0;
    }


    //********************************************helper_Functions_for_Acquire***********************************
    void merge_func(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,
                              shared_ptr<Employee>  arr3[]){
        int i = 0, j = 0, k = 0;

        while (i<n1 && j <n2)
        {
            if ((arr1[i]->getEmployeeSalaryID()) < (arr2[j]->getEmployeeSalaryID()))//ommmmm
                arr3[k++] = arr1[i++];
            else
                arr3[k++] = arr2[j++];
        }

        // Store remaining elements of first array
        while (i < n1)
            arr3[k++] = arr1[i++];

        // Store remaining elements of second array
        while (j < n2)
            arr3[k++] = arr2[j++];
    }

    tree_node<SalaryID, shared_ptr<Employee>>* createFromSortedArrAuxForSalary(shared_ptr<Employee> array[], int start,
                                                                                         int end, tree_node<SalaryID, shared_ptr<Employee>> *parent){
        if(start > end)
            return nullptr;
        int mid = (start+end)/2;
        tree_node<SalaryID, shared_ptr<Employee>> *new_node = new tree_node<SalaryID, shared_ptr<Employee>>(array[mid]->getEmployeeSalaryID(),array[mid],parent, nullptr, nullptr, 0);
        new_node->left_son = createFromSortedArrAuxForSalary(array, start, mid-1, new_node);
        new_node->right_son = createFromSortedArrAuxForSalary(array, mid+1, end, new_node);
        new_node->updateHeight();
        return new_node;
    }

    AVL_Tree<SalaryID, shared_ptr<Employee>>* createFromSortedArrForSalary(shared_ptr<Employee> array[], int start, int end){
        AVL_Tree<SalaryID, shared_ptr<Employee>> *new_tree = new AVL_Tree<SalaryID, shared_ptr<Employee>>();
        new_tree->root = createFromSortedArrAuxForSalary(array, start, end, nullptr);
        new_tree->max = new_tree->root->findMax();
        new_tree->min = new_tree->root->findMin();
        new_tree->size = end+1;
        return new_tree;
    }

    void visitInOrder3(shared_ptr<Employee> * array, tree_node<SalaryID, shared_ptr<Employee> >* node, int* counter_ptr, int num){
        if (node == nullptr || *counter_ptr == num ) {
            return;
        }
        /* first recur on left child */
        visitInOrder3(array, node->left_son, counter_ptr, num);
        // added by - saleh
        if (*counter_ptr == num ) {
            return;
        }
        if (node->data)
        {
            array[*counter_ptr] = *(node->data);
            (*counter_ptr)++;
        }
        else
        {
            return;
        }
        if (*counter_ptr == num) {
            return;
        }
        /* now recur on right child */
        visitInOrder3(array, node->right_son, counter_ptr, num);
    }

    tree_node<SalaryID,shared_ptr<Employee>>* mergeTrees(AVL_Tree<SalaryID,shared_ptr<Employee>>* acquirer_tree,
                                                        AVL_Tree<SalaryID,shared_ptr<Employee>>* target_tree,
                                                        int root_id){
        int size1 = acquirer_tree->size;
        int size2 = target_tree->size;

        shared_ptr<Employee> *acquire_employees_arr_salary = new shared_ptr<Employee>[size1]();
        shared_ptr<Employee> *target_employees_arr_salary = new shared_ptr<Employee>[size2]();

        int counter = 0;
        visitInOrder3(acquire_employees_arr_salary, acquirer_tree->root, &counter, size1);
        int* counter_ptr = &counter;
        *counter_ptr = 0;
        visitInOrder3(target_employees_arr_salary, target_tree->root, &counter, size2);
        counter_ptr = nullptr;

        shared_ptr<Employee> *new_arr_salary = new shared_ptr<Employee>[size1+size2](); //potential memory leaks?
        merge_func(target_employees_arr_salary, acquire_employees_arr_salary, size2, size1, new_arr_salary);

        for(int i=0; i<size1+size2; i++){
            new_arr_salary[i]->UpdateCompanyID(root_id);
        }
        tree_node<SalaryID, shared_ptr<Employee>>* new_tree_by_salary = createFromSortedArrAuxForSalary(new_arr_salary, 0, size2+size1-1,nullptr);

        delete[] acquire_employees_arr_salary;
        delete[] target_employees_arr_salary;
        delete[] new_arr_salary;
        delete acquirer_tree;
        delete target_tree;

        return new_tree_by_salary;
    }
    //************************************************************************************************************

    void MultiStructures::MergeStructures(MultiStructures& other, int root_id){
        //merge trees
        tree_node<SalaryID,shared_ptr<Employee>>* new_root = mergeTrees(&employees_with_salary, &other.employees_with_salary, root_id);
        employees_with_salary.treeClear();
        employees_with_salary.root = new_root;
        employees_with_salary.max = new_root->findMax();
        employees_with_salary.min = new_root->findMin();

        int size1 = employees_with_salary.size;
        int size2 = other.employees_with_salary.size;
        employees_with_salary.size = size1+size2 ;


        //merge_hash_tables
        int other_hash_size = other.employees.arr_size;
        for (int i = 0; i < other_hash_size; i++) {
            Node<int, shared_ptr<Employee>>* tmp = other.employees.arr[i]->head->next;
            while(tmp != other.employees.arr[i]->tail){
                int id = tmp->key;
                tmp->data->get()->UpdateCompanyID(root_id);
                employees.addElement(id, *tmp->data);
                tmp = tmp->next;
            }
        }
        //delete the hash of the target company
        for (int i = 0; i < other_hash_size; i++) {
            delete(other.employees.arr[i]);
        }
        delete[](other.employees.arr);
    }
    void MultiStructures::bumpGradeForSumOfGradesForEmpWhithNoSalary(int bumpGrade){
        sum_of_grades_for_emp_with_no_salary+=bumpGrade;
    }

    AVL_Tree<SalaryID,shared_ptr<Employee>>* MultiStructures::getEmployeesWithSalaryTree(){
        return &employees_with_salary;
    }

    int MultiStructures::getNumOfEmployeesWithNoSalary(){
        return number_of_employees_with_no_salary;
    }

    int MultiStructures::getSumOfGradesForEmployeesWithNoSalary(){
        return sum_of_grades_for_emp_with_no_salary;
    }

} // namespace ULIFB
