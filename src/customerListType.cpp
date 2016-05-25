#include "customerListType.h"
#include "customertype.h"
#include <string>

using namespace std;


int customerListType::nameSearch(std::string fName,std::string lName)
{
    int index = 0;
    nodeType<customerType>* current;
    current = GetFirst(); //set current to point to the first node
                     //in the list

    while (current != nullptr)     //search the list
    {
        if (current->info.getLastName() == lName) //the item is found
            if (current->info.getFirstName() == fName) //the item is found
            {
                return index;
            }
        else
        {
            index++;
            current = current->link; //advance current to
                                     //the next node
        }
    }
    return -1;      // Not in the list
}
