#ifndef PERSONTYPE_H
#define PERSONTYPE_H
#include <string>

class PersonType
{
    public:

        PersonType(std::string fName = "", std::string lName = "");
        // constructor

        void print() const;
        // function to print name

        void setName( std::string, std::string);
        // function to set name
        // Post: firstName = first, lastName = last;

        std::string getFirstName() const;
        // returns firstname

        std::string getLastName() const;
        // returns lastName



    protected:
        std::string firstName;
        std::string lastName;

    private:
};

#endif // PERSONTYPE_H
