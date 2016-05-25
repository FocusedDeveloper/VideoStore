#ifndef RENTEDMOVIESTORE_H
#define RENTEDMOVIESTORE_H

#include <string>
#include "rentedmovie.h"

class RentedMovieStore: public RentedMovie
{
    public:
        RentedMovieStore(std::string title = "", time_t time = 0, int acctNum = 0);

        bool operator==(const RentedMovieStore&);
        // overloading the equals operator

        bool operator!=(const RentedMovieStore&);
        // overloading the not equals operator

        int getAccNum();
        // Returns account number

        void printStore();
        // Prints the title and account number of the movie

    private:

        int customerAccNum;
};

#endif // RENTEDMOVIESTORE_H
