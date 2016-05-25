#include "persontype.h"
#include <string>
#include <iostream>

using namespace std;



PersonType::PersonType(std::string fName, std::string lName)
{
    firstName = fName;
    lastName = lName;
}

void PersonType::setName(string first, string last)
{
    firstName = first;
    lastName = last;
}

void PersonType::print() const
{
    cout<<"Name: "<<firstName<<" "<<lastName<<endl;
}

string PersonType::getFirstName() const
{
    return firstName;
}

string PersonType::getLastName() const
{
    return lastName;
}
