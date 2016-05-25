#ifndef CUSTOMERLISTTYPE_H
#define CUSTOMERLISTTYPE_H

#include "../unorderedLinkedList.h"

#include "customertype.h"


class customerListType: public unorderedLinkedList<customerType>
{

    public:
//        customerListType();
//        virtual ~customerListType();

        int nameSearch(std::string fName,std::string lName);
        // function to check if a duplicate customer name is already in the list
        // Post: If found, return the index of the customer in the list
                // else return -1


    protected:
    private:
};

#endif // CUSTOMERLISTTYPE_H
