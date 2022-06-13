//
// Created by Saleh on 01/06/2022.
//

#include "Company.h"

namespace ULIFB
{

    MultiStructures* Company::getEmployeesMultiStructures()
    {
        return(&(this->employees));
    }

    long long int Company::getCompanyId()
    {
        return(this->id);
    }

    long double Company::getCompanyValue()
    {
        return(this->value);
    }

    void Company::updateEnterpriseValue(long double new_value)
    {
        this->enterprise_value = new_value;
    }

    long double Company::getEnterpriseValue()
    {
        return(this->enterprise_value);
    }

    void Company::IncreaseCompanyValue(long double increase)
    {
        //correct implementation?
        this->value+=increase;
    }

    void Company::setCompanyValue(long double value) {
        value = value;
    }

}