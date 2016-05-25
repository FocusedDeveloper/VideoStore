#ifndef RENTEDMOVIE_H
#define RENTEDMOVIE_H

#include <ctime>
#include <string>

class RentedMovie
{
    public:
        RentedMovie(std::string myTitle = "", time_t time = 0 );

        std::string getTitle() const;
        // Function to return movies title

        time_t getDate() const;
        // Function to return movie's checkOutDate;

    protected:
        std::string title;
        time_t checkOutDate;

};

#endif // RENTEDMOVIE_H
