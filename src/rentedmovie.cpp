#include "rentedmovie.h"
#include <iostream>

using namespace std;

RentedMovie::RentedMovie(std::string myTitle , time_t time )
{
    title = myTitle;
    checkOutDate = time;
    //ctor
}

std::string RentedMovie::getTitle() const
{
    return title;
}

time_t RentedMovie::getDate() const
{
    return checkOutDate;
}


