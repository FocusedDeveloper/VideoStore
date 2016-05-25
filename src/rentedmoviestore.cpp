#include "rentedmoviestore.h"
#include <string>
#include <iostream>

using namespace std;

RentedMovieStore::RentedMovieStore( std::string myTitle, time_t time, int acctNum) : RentedMovie(myTitle,time)
{
    customerAccNum = acctNum;
    //ctor
}

int RentedMovieStore::getAccNum()
{
    return customerAccNum;
}

bool RentedMovieStore::operator==(const RentedMovieStore& other)
{
    if(other.customerAccNum == customerAccNum)     // account number and...
        if(other.title == title)           // title are the same..
            return true;                            // return true

    return false;
}

bool RentedMovieStore::operator!=(const RentedMovieStore& other)
{
    if(other.customerAccNum != customerAccNum)     // account #s don't equal, objects don't equal
        return true;

    if(other.title != title)               // titles don't equal... objects don't equal
        return true;

    return false;
}


void RentedMovieStore::printStore()
{
    cout<<"Title: "<<title<<endl;
    cout<<"Customer Acct#: "<<customerAccNum<<endl;
    cout<<endl;
}
