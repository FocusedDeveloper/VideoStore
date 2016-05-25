#ifndef CUSTOMERTYPE_H
#define CUSTOMERTYPE_H

#include <vector>
#include "persontype.h"
#include "rentedmovie.h"
//#include "videoType.h"
#include "../videoType.h"
#include "accttype.h"

class customerType :public PersonType
{
    friend ostream& operator<< (ostream&, const customerType&);
    //overload the insertion operator

    public:
        customerType(int accountNumber = 0, std::string fName = "",  std::string lName = "", std::string address = "",
                     std::string email = "", std::string phoneNum = "");
        ~customerType();

        bool operator==(const customerType&);
        // overload the equals operator

        bool operator!=(const customerType&);
        // overload the not equals operator

        void printInfo() const;
        // Function to print the complete customer information
        // including name, address, email, phone number, account type and movies out

        void setInfo(std::string fName, std::string lName, std::string address = "",
                     std::string email = "", std::string phoneNum = "");
        // function to set up customers personal information
        // Post: All member variables are set to their corresponding parameters

        void printRentedMovies() const;
        // Function to print the list of movies that are currently in possession of the customer

        int getAccNum() const;
        // Returns customer account Number;

        void printAccNum() const;
        // Function to print the account number

        void setAccNum(int);
        // Function to set the account number

        bool rentMovie(std::string);
        // Function to rent a movie from the store
        // PRE: Customer Account type must allow for dvd rentals
        // and there must be room for a rental on the account
        // POST: Movie added to the list of customers rented movies
        // returns true if successful

        bool returnMovie(std::string title = "");
        // Function to return a Movie to the store;
        // Post: if given title is found, it is removed from the rented list
        // returns true if successful

        void setAddress(std::string);
        // Function to set the address

        void setEmail(std::string);
        // Function to set email

        void setPhone(std::string);
        // Function to set phone number

        void setupAccount();
        // Function to setup customers account type
        // Post: All features turned off, account is reset
        // and user is prompted to add features

        void cancelAccount();
        // Function to cancel the account
        // POST: account features turned off

        void changeAccount();
        // Function to make changes to a users account,
        // via adding and removing features

        void currentBill();
        // Function to display the due date and total amount of the next bill

        void updatePersonalInfo();
        // Function to change a customers personal information

        bool streamMovie(std::string);
        // Function to stream a movie from the video store
        // Post: Moving added to streamingMovieList if the feature is available
        // on this users account

        bool stopStream(std::string);
        // Function to stop the stream via prompting user
        // Post: selected movie removed from streamingMovieList

        void returnAllMovies();
        // Function to return all rented movies at once
        // Post: rentedMovieList is empty

    protected:

    private:

        int accNum;
        std::string billAddress;
        std::string email;
        std::string phone;
        std::vector<RentedMovie> rentedMovieList;       // keeps track of dvds rented
        std::vector<RentedMovie> streamingMovieList;    // keeps track of videos currently streaming
        int totCurrStreaming;
        AcctType account;

};

#endif // CUSTOMERTYPE_H
