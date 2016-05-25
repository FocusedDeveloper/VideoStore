#include "customertype.h"
#include "persontype.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

customerType::customerType(int accountNumber, std::string fName,  std::string lName, std::string address, std::string myEmail, std::string phoneNum)
: PersonType(fName, lName)
// constructor, calls the super class constructor for name
{
    accNum = accountNumber;
    billAddress = address;
    email = myEmail;
    phone = phoneNum;
    vector<RentedMovie> rentedMovieList;
}

customerType::~customerType()
{
    //dtor
}

ostream& operator<< (ostream& osObject, const customerType& customer)
{
    osObject << endl;
    osObject<< "Name: "<<customer.firstName<<" "<<customer.lastName<<endl
            << "Account #: "<<customer.accNum <<endl
            << "Address: "<<customer.billAddress <<endl
            << "Email: "<<customer.email<<endl
            << "Phone Number"<<customer.phone<<endl;
    osObject << endl;
    osObject << "_____________________________________"
             << endl;

    return osObject;
}

// Function to print the complete customer information
// including name, address, email, phone number, account type and movies out
void customerType::printInfo() const
{
    PersonType::print();
    cout<< "Account #: "<<accNum <<endl
        << "Address: "<<billAddress <<endl
        << "Email: "<<email<<endl
        << "Phone Number"<<phone<<endl;
    account.print();
    printRentedMovies();
}

// function to set up customers personal information
        // Post: All member variables are set to their corresponding parameters
void customerType::setInfo(std::string fName, std::string lName, std::string address,
                     std::string myEmail , std::string phoneNum)
{
    PersonType::setName(fName,lName);
    billAddress = address;
    email = myEmail;
    phone = phoneNum;
}

// Function to print the list of movies that are currently in possession of the customer
void customerType::printRentedMovies() const
{
    cout<<"Movies Currently Rented: "<<endl;
    for(int i = 0; i < rentedMovieList.size(); i++)
        cout<<"    "<<rentedMovieList[i].getTitle()<<endl;
}

// Returns customer account Number;
int customerType::getAccNum() const
{
    return accNum;
}

 // Function to print the account number
void customerType::printAccNum() const
{
    cout<<accNum;
}

// Function to set the account number
void customerType::setAccNum(int num)
{
    accNum = num;
}

 // Function to rent a movie from the store
        // PRE: Customer Account type must allow for dvd rentals
        // and there must be room for a rental on the account
        // POST: Movie added to the list of customers rented movies
        // returns true if successful
bool customerType::rentMovie(std::string title)
{
    time_t rentedDate;
    rentedDate = time(NULL);        // set rented date to the current time
    RentedMovie myMovie;

    if(rentedMovieList.size() < account.getMaxDvds() )       // if the size of the list is less than the maximum size...
    {
        myMovie = RentedMovie(title, rentedDate );       // set the rented DVD to the title of the param and todays date
        rentedMovieList.push_back(myMovie );                                 // add the Movie to the list
        return true;
    }
    else
    {
        if(account.getMaxDvds() == 0)                    // If they can't rent DVDs at all....
            cout<<"This Account is not set up for DVD Rentals.  Add the feature first."<< endl;
        else if(account.getMaxDvds() == account.MAX_DVDS)
            cout<<"You current have the max number of DVDs out at this time."<< endl;
        else
            cout<<"You can't checkout any more DVDs at this time.  Add feature to increase the available amount."<<endl;
    }
    return false;
}

// Function to return a Movie to the store;
        // Post: if given title is found, it is removed from the rented list
        // returns true if successful
bool customerType::returnMovie(std::string title )
{
    for(int i = 0; i < rentedMovieList.size(); i++)
    {
        if( rentedMovieList[i].getTitle() == title)  // if the movie is found
        {
            rentedMovieList.erase(rentedMovieList.begin() + i);               // remove it from the list

            return true;                            // function successfully found the movie
        }
    }
    return false;                                   // the movie was not in the list, return false
}

// Function to set the address
void customerType::setAddress(std::string myAddress)
{
    billAddress = myAddress;
}

// Function to set email
void customerType::setEmail(std::string myEmail)
{
    email = myEmail;
}

// Function to set phone number
void customerType::setPhone(std::string myPhone)
{
    phone = myPhone;
}

// Function to setup customers account type
        // Post: All features turned off, account is reset
        // and user is prompted to add features
void customerType::setupAccount()
{
    account.removeAllFeatures();       // Remove all features
    account.initAccount();          // Initialize the account
    account.addFeatures();          // Add additional features
}

// Function to cancel the account
        // POST: account features turned off
void customerType::cancelAccount()
{
    account.removeAllFeatures();

}

// Function to make changes to a users account,
        // via adding and removing features
void customerType::changeAccount()
{
    int option;
    do
    {
        cout<<"Make Changes to Account"<<endl
            <<"1) Add Features" << endl
            <<"2) Remove Features" <<endl
            <<"3) Add All Features" << endl
            <<"4) Remove All Features" <<endl
            <<"9) Exit" <<endl;
        cin>>option;

        if(!cin)        // on invalid input
        {
            cin.clear();                // clear the line
            cin.ignore(500,'\n');       // ignore all the invalid
        }

        switch(option)
        {
            case 1: account.addFeatures();
                    break;
            case 2: account.removeFeatures();
                    break;
            case 3: account.addAllFeatures();
                    break;
            case 4: account.removeAllFeatures();
                    break;
            default: cout<<"Invalid selection."<<endl;
                    break;
        }
    }while(option != 9);
}

// Function to display the due date and total amount of the next bill
void customerType::currentBill()
{
        // TBD: parse date and display it with the account price
}

void customerType::updatePersonalInfo()
{
    int option;
    string input1, input2;
    do
    {

        cout<<"Personal Information Changes"<<endl
            <<"1) Name"<<endl
            <<"2) Address"<<endl
            <<"3) Phone"<<endl
            <<"4) Email"<<endl
            <<"9) Exit"<<endl;

        cin>>option;

        if(!cin)
        {
            cin.clear();
            cin.ignore(500,'\n');
        }

        switch(option)
        {
            case 1:
                cout<<"First Name: ";
                cin>>input1;
                cout<<"Last Name: ";
                cin>>input2;

                setName(input1, input2);
                cout<<"Name updated"<<endl;
                break;
            case 2:
                cout<<"Address: ";
                cin>>input1;

                setAddress(input1);
                cout<<"Address updated"<<endl;
                break;
            case 3:
                cout<<"Phone #: ";
                cin>>input1;

                setPhone(input1);
                cout<<"Phone # updated"<<endl;
                break;
            case 4:
                cout<<"Email: ";
                cin>>input1;

                setEmail(input1);
                cout<<"Email updated"<<endl;
                break;
            case 9: break;
            default: cout<<"Invalid input"<<endl;
        }
    }while(option != 9);

}

// Function to stream a movie from the video store
        // Post: Moving added to streamingMovieList if the feature is available
        // on this users account
bool customerType::streamMovie(std::string title)
{
    time_t rentedDate;
    rentedDate = time(NULL);        // set rented date to the current time
    RentedMovie myMovie;

    if(streamingMovieList.size() < account.getMaxDevices() )       // if the size of the list is less than the maximum size...
    {
        myMovie = RentedMovie(title, rentedDate );       // set the rented movie to the title of the param and todays date
        streamingMovieList.push_back(myMovie );                                 // add the Movie to the list
        return true;
    }
    else
    {
        if(account.getMaxDevices() == 0)                    // If they can't stream Movies at all....
            cout<<"This Account is not set up for Video Streaming.  Add the feature first."<< endl;
        else if(account.getMaxDevices() == account.MAX_DEVICES)
            cout<<"You are currently using the max number of video streaming devices."<< endl;
        else
            cout<<"You can't videos from any additional devices.  Add feature to increase the available amount."<<endl;
    }
    return false;
}

// Function to stop the stream via prompting user
        // Post: selected movie removed from streamingMovieList
bool customerType::stopStream(string title)
{
    for(int i = 0; i < streamingMovieList.size(); i++)
    {
        if( streamingMovieList[i].getTitle() == title)  // if the movie is found
        {
            streamingMovieList.erase(streamingMovieList.begin() + i);               // remove it from the list

            return true;                            // function successfully found the movie
        }
    }
    return false;                                   // the movie was not in the list, return false
}

void customerType::returnAllMovies()
{
    rentedMovieList.clear();
}

bool customerType::operator==(const customerType& other)
{
    if(accNum == other.accNum)      // customers are unique only by account number
        return true;

    return false;
}

bool customerType::operator!=(const customerType& other)
{
    if(accNum != other.accNum)      // customers are unique only by account number
        return true;

    return false;
}
