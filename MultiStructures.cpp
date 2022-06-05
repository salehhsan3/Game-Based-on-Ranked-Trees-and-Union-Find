//
// Created by Saleh on 01/06/2022.
//

#include "MultiStructures.h"


namespace ULIFB
{
    void MultiStructures::addEmployee(SalaryID sal_id,shared_ptr<Employee> emp_to_add)
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
            this->employees_with_salary.addNode(emp_to_find->getEmployeeSalaryID(),emp_to_find,emp_to_find->getEmployeeGrade()); // im not sure if this is the correct implementation. ie, maybe we should pass salary or something else instead of level!
            return;
        }
        else if (emp_to_find->getEmployeeSalary() > 0)
        {
            emp_to_find->increaseSalary(increase);
            this->employees_with_salary.removeNode(emp_to_find->getEmployeeSalaryID()); // remove old node!
            this->employees_with_salary.addNode(emp_to_find->getEmployeeSalaryID(),emp_to_find,emp_to_find->getEmployeeGrade()); // im not sure if this is the correct implementation. ie, maybe we should pass salary or something else instead of level!
        }
        
    }

    void MultiStructures::promoteEmployee(int emp_id, int bump)
    {
        // saleh's code to test other functions - remove later
        // complexity is O(log(n))!
        if (bump <= 0)
        {
            return;
        }
        
        shared_ptr<Employee> emp_to_find =  this->findEmployee(emp_id);
        if (emp_to_find == nullptr)
        {
            return; // should never get here!
        }
        if (emp_to_find->getEmployeeSalary() == 0)
        {
            this->sum_of_grades_for_emp_with_no_salary -= emp_to_find->getEmployeeGrade();
            emp_to_find->bumpGrade(bump);
            this->sum_of_grades_for_emp_with_no_salary += emp_to_find->getEmployeeGrade();
            return;
        }
        if (emp_to_find->getEmployeeSalary() > 0)
        {
            this->employees_with_salary.removeNode(emp_to_find->getEmployeeSalaryID()); // remove old node!
            emp_to_find->bumpGrade(bump);
            this->employees_with_salary.addNode( emp_to_find->getEmployeeSalaryID() , emp_to_find,emp_to_find->getEmployeeGrade()); // im not sure if this is the correct implementation. ie, maybe we should pass salary or something else instead of level!
        }
    }

    int MultiStructures::SumOfBumpGradeBetweenTopWorkersByGroup(int number_of_top_workers)
    {
        // complexity is O(log*(k) + log(n))  
        if( this->employees_with_salary.Select(employees_with_salary.root,(employees_with_salary.size - number_of_top_workers)) == nullptr)
        {
            // was not found!
            return -1; // only returns this if the employee was not found! ie, there's no employee whose rank in number_of_top_worker!
        }
        shared_ptr<Employee> *emp_to_find = this->employees_with_salary.Select(employees_with_salary.root,number_of_top_workers)->data;
        return(this->employees_with_salary.findSumSmaller(emp_to_find->get()->getEmployeeSalaryID())); // is this the correct implementation of finding the sum of sons?
        
    }

    hash_table<shared_ptr<Employee>>* MultiStructures::getEmployesHashTable()
    {
        return(&(this->employees));
    }

    AVL_Tree<SalaryID,shared_ptr<Employee>>* MultiStructures::getEmployessWithSalaryTree()
    {
        return(&(this->employees_with_salary));
    }

    void MultiStructures::MoveTreeToArray(shared_ptr<Employee> * array, tree_node<SalaryID, shared_ptr<Employee> >* node, int* counter_ptr, int num){
        if (node == nullptr || *counter_ptr == num ) {
            return;
        }
        /* first recur on left child */
        MoveTreeToArray(array, node->left_son, counter_ptr, num);
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
        MoveTreeToArray(array, node->right_son, counter_ptr, num);
    }

    // tree_node<SalaryID, shared_ptr<Employee>> *MultiStructures::createTreeFromSortedArrAuxForSalary(shared_ptr<Employee> array[], int start,
    //                                                     int end, tree_node<SalaryID, shared_ptr<Employee>> *parent){
    //     if(start > end)
    //         return nullptr;
    //     int mid = (start+end)/2;
    //     tree_node<SalaryID, shared_ptr<Employee>> *new_node = new tree_node<SalaryID, shared_ptr<Employee>>(array[mid]->getEmployeeSalaryID(),array[mid],parent, nullptr, nullptr, 0);
    //     new_node->left_son = createTreeFromSortedArrAuxForSalary(array, start, mid-1, new_node);
    //     new_node->right_son = createTreeFromSortedArrAuxForSalary(array, mid+1, end, new_node);
    //     new_node->updateHeight();
    //     return new_node;
    // }

    // void MultiStructures::merge_func(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,
    //                 shared_ptr<Employee>  arr3[]){
    //     int i = 0, j = 0, k = 0;

    //     while (i<n1 && j <n2)
    //     {
    //         if ((arr1[i]->getEmployeeSalaryID()) < (arr2[j]->getEmployeeSalaryID()))
    //             arr3[k++] = arr1[i++];
    //         else
    //             arr3[k++] = arr2[j++];
    //     }

    //     // Store remaining elements of first array
    //     while (i < n1)
    //         arr3[k++] = arr1[i++];

    //     // Store remaining elements of second array
    //     while (j < n2)
    //         arr3[k++] = arr2[j++];
    // }

    // void MultiStructures::UpdataRankTreeFields(tree_node<SalaryID, shared_ptr<Employee>>* root)
    // {
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

        
    // }

    void MultiStructures::MergeHashTable(hash_table<shared_ptr<Employee>> *other) // saleh
    {
        LList<int,shared_ptr<Employee>>* current_list = other->arr[0];
        for (int i = 0; i < other->arr_size; i++) // maybe arr_size+1
        {
            current_list = other->arr[i];
            Node<int, shared_ptr<Employee>>* current_node = current_list->head->next;
            while (current_node != current_list->tail)
            {
                this->getEmployesHashTable()->addElement(current_node->key,*(current_node->data));
                current_node = current_node->next;
            }
        }
    }

    void MultiStructures::UpdateOwnerIdInHash(int new_owner) // saleh
    {
        LList<int,shared_ptr<Employee>>* current_list = this->employees.arr[0];
        for (int i = 0; i < this->employees.arr_size; i++) // maybe arr_size+1
        {
            current_list = this->employees.arr[i];
            Node<int, shared_ptr<Employee>>* current_node = current_list->head->next;
            while (current_node != current_list->tail)
            {
                current_node->data->get()->UpdateCompanyID(new_owner);
                current_node = current_node->next;
            }
        }
    }

    // void MultiStructures::MergeStructures(MultiStructures *other, int new_owner)
    // {
    //     // numbers merge
    //     this->number_of_employees_with_no_salary += other->number_of_employees_with_no_salary;
    //     this->sum_of_grades_for_emp_with_no_salary += other->sum_of_grades_for_emp_with_no_salary;

    //     // hashtable merge
    //     int hash_elements = this->employees.getNumberOfElements() + other->employees.getNumberOfElements();
    //     if (hash_elements == 0)
    //     {
    //         return; // there's nothing to merge!
    //     }
        
    //     // this->employees.MergeHashTable(other->getEmployesHashTable());
    //     this->MergeHashTable(other->getEmployesHashTable());
    //     // should destroy the hashtable in other!
    //     // other->getEmployesHashTable()->DeleteHashTable();
    //     this->UpdateOwnerIdInHash(new_owner);
        
    //     //tree merge
    //     int acquirer_num = this->employees_with_salary.size;
    //     int target_num = other->employees_with_salary.size;
    //     int after_num = acquirer_num + target_num;

    //     AVL_Tree<SalaryID, shared_ptr<Employee>>* acquirer_employee_tree = this->getEmployessWithSalaryTree();
    //     AVL_Tree<SalaryID, shared_ptr<Employee>>* target_employee_tree = other->getEmployessWithSalaryTree();

    //     shared_ptr<Employee> *acquirer_employees_arr = new shared_ptr<Employee>[acquirer_num]();
    //     shared_ptr<Employee> *target_employees_arr = new shared_ptr<Employee>[target_num]();

    //     int counter = 0;
    //     int *counter_ptr = &counter;
    //     MoveTreeToArray(acquirer_employees_arr, acquirer_employee_tree->root, &counter, acquirer_num);
    //     *counter_ptr = 0;
    //     MoveTreeToArray(target_employees_arr, target_employee_tree->root, &counter, target_num);
    //     counter_ptr = nullptr;

    //     shared_ptr<Employee> *new_arr = new shared_ptr<Employee>[after_num](); //potential memory leaks?
    //     // merge_func should be adjusted for the new rank_tree!
    //     merge_func(target_employees_arr, acquirer_employees_arr, target_num, acquirer_num, new_arr);
    //     tree_node<SalaryID, shared_ptr<Employee>>* new_tree = createTreeFromSortedArrAuxForSalary(new_arr, 0, acquirer_num+target_num-1,nullptr);
    //     this->employees_with_salary.treeClear(); // updating the tree to be the new one!
    //     this->employees_with_salary.root = new_tree;
    //     this->employees_with_salary.max = new_tree->findMax();
    //     this->employees_with_salary.min = new_tree->findMin();
    //     this->employees_with_salary.size = this->employees_with_salary.size;

    //     delete[] acquirer_employees_arr;
    //     delete[] target_employees_arr;
    //     delete[] new_arr;
        
    // }

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
