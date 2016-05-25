/*************************************************************************
Software Developer: Charles Johnson
Professor: Scott Davis
Course: CS210
Date: 5/04/2016

Title: VideoStore
Function: simulate a video store's transactions keeping track
    of movie database (linked list class),
    customer database (linked list class),
    and movies rented out (vectors).
    Store allows for both DVD Rentals and Streaming

TBD: 1) Store all list to text files, and read upon store opening
     2) Fully implement use of date to send out monthly bills to customers
     3) Implement customer pay functionality

***************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "videoType.h"
#include "videoListType.h"
#include "accttype.h"
#include "persontype.h"
#include "customertype.h"
#include "customerListType.h"
#include "rentedmoviestore.h"

using namespace std;

// functoin for creating video list
void createVideoList(ifstream& infile,
                     videoListType& videoList);

// function for displaying menu
void displayMenu();

// class testing functions
/*
void testAcct();
void testPerson();
void testCustomer();
*/

// Function to sign customers into the store
customerType& customerSignIn(customerListType& customerList);

// Function to add dummy customers to the store
void supplyCustomers(customerListType& customerList);

// Function to handle customer transactions
void customerMenu(customerType* customer, videoListType& videoList, vector<RentedMovieStore> &rentedMovieList);

//void saveVideoList(videoListType& videoList);
const int ESCAPE_VAL = -1;
const int BASE_ACC_NUM = 10000;

int main()
{
//    testCustomer();
//    testPerson();
//    testAcct();

    customerType* currentCustomer;              // create a pointer to a customer type

    videoListType videoList;                    // list for holding stores videos
    customerListType customerList;              // list for holding stores customers

    linkedListIterator<customerType> it;
    vector<RentedMovieStore> rentedMovieList;   // list for holding stores DVDs that are rented out

    supplyCustomers( customerList);             // put some users in customer List


    bool quit = false;

    ifstream infile;
           //open the input file
    infile.open("videoDat.txt");
    if (!infile)
    {
        cout << "The input file does not exist. "
             << "The program terminates!!!" << endl;
        return 1;
    }
    //create the video list
    createVideoList(infile, videoList);
    infile.close();


    do      // keep sending customers to the store...
    {
        currentCustomer = &customerSignIn(customerList);        // get a valid customer from the database, or sign up new client

        if(currentCustomer->getAccNum() == ESCAPE_VAL)          // if the customer has the escape value
        {
            customerList.deleteNode(ESCAPE_VAL);                // remove it from the list...
            quit = true;                                        // prepare to quit program
        }
        else
        {
            cout<<"Hello "<<currentCustomer->getFirstName()<<endl;

            customerMenu(currentCustomer, videoList, rentedMovieList);  // send customer into the store
        }


    }while(!quit);  // until we find the escape value

    return 0;
}

// Handles customer store transactions
// PRE: customer is a current customer of the store
        // videoList is defined and populated
        // rentedMovieList is defined and populated
// POST: customer file, videoList, and rentedMovieList all reflect any transactions made by the customer
void customerMenu(customerType* customer, videoListType& videoList, vector<RentedMovieStore> &rentedMovieList)
{
    int choice;
    char ch;
    string title;
    RentedMovieStore rentedMovie;
    time_t now;
    now = time(NULL);

        //show the menu
    displayMenu();
    cout << "Enter your choice: ";
    cin >> choice;    //get the request
    cin.get(ch);
    cout << endl;

        //process the requests
    while (choice != 99)
    {
        switch (choice)
        {
        case 0: customer->printInfo();
                break;

        case 1:
            cout << "Enter the title: ";
            getline(cin, title);
            cout << endl;

            if (videoList.videoSearch(title))
                cout << "The store carries " << title
                     << endl;
            else
                cout << "The store does not carry "
                     << title << endl;
            break;

        case 2:
            cout << "Enter the title: ";
            getline(cin, title);
            cout << endl;

            if (videoList.videoSearch(title))           // is movie in the database?
            {
                if (videoList.isVideoAvailable(title))  // is there a copy available?
                {
                    if(customer->rentMovie(title) )  // if the customer is able to rent the movie...
                    {
                        videoList.videoCheckOut(title);                                     // check it out of the store (update copies)
                        rentedMovie = RentedMovieStore(title,now,customer->getAccNum() );   // create a rented movie object with title user account #
                        rentedMovieList.push_back(rentedMovie);                             // add movie to rented list
                        cout << "Enjoy your movie: "
                         << title << endl;
                    }

                }
                else
                    cout << "Currently " << title
                         << " is out of stock." << endl;
            }
            else
                cout << "The store does not carry "
                     << title << endl;
            break;

        case 3:
            cout << "Enter the title: ";
            getline(cin, title);
            cout << endl;

            if (videoList.videoSearch(title))                           // if the movie is in the database
            {
                if( customer->returnMovie(title) )                      // and the customer returns it successfully...
                {
                    videoList.videoCheckIn(title);                      // check movie back in (update copies in store)

                    for(int i = 0; i < rentedMovieList.size(); i++)             // search the entire move list...
                    {
                        // find the movie on the rented list
                        if( rentedMovieList[i].getAccNum() == customer->getAccNum() )       // if the movie was checked out by this customer
                        {
                            if( rentedMovieList[i].getTitle() == title)  // and the title is found...
                            {
                                rentedMovieList.erase(rentedMovieList.begin() + i);               // remove it from the list
                                break;                                                            // exit loop once found
                            }
                        }
                    }
                    cout << "Thanks for returning "
                     << title << endl;
                }

            }
            else
                cout << "The store does not carry "
                     << title << endl;
            break;

        case 4:
            cout << "Enter the title: ";
            getline(cin, title);
            cout << endl;

            if (videoList.videoSearch(title))
            {
                if (videoList.isVideoAvailable(title))
                    cout << title << " is currently in "
                         << "stock." << endl;
                else
                    cout << title << " is currently out "
                         << "of stock." << endl;
            }
            else
                cout << "The store does not carry "
                     << title << endl;
            break;

        case 5:
            videoList.videoPrintTitle();
            break;

        case 6:
            videoList.print();

//            for (it = videoList.begin(); it != videoList.end(); ++it)                  //Line 36
//                cout << *it << " ";
            break;
        case 7:
            cout << "Enter the title: ";
            getline(cin, title);
            cout << endl;

            if (videoList.videoSearch(title))       // if the store carries the movie, we can stream it!
            {
                if(customer->streamMovie(title) )  // if the customer is able to rent the movie...
                {
                    cout << "Enjoy your movie: "
                     << title << endl;
                }
            }
            else
                cout << "The store does not carry "
                     << title << endl;
            break;
        case 8:
            cout << "Enter the title: ";
            getline(cin, title);
            cout << endl;

            if (videoList.videoSearch(title))     // is the movie in the store database?
            {
                if(customer->stopStream(title) )  // if the customer is able to rent the movie...
                {
                    cout << "Thank you for watching: "
                     << title << endl;
                }
                else
                {
                    cout << "You are not streaming: "
                        << title <<endl;
                }

            }
            else
                cout << "The store does not carry "
                     << title << endl;
            break;
        case 9: customer->updatePersonalInfo();     // allow user to update personal information Name, Address, ect...
                break;
        case 10: customer->changeAccount();         // allow user to change their account type
                break;
        case 11:
            if(rentedMovieList.size() > 0)
            {
                cout<<"Movies Currently Rented: "<<endl;
                for(int i = 0; i < rentedMovieList.size(); i++)
                    cout<<"Account Number: "<<rentedMovieList[i].getAccNum()<<" Title: "<<rentedMovieList[i].getTitle()<<endl;
            }
            else
                cout<<"No DVD's are checked out... (Sad Face)"<<endl;
            break;
        default:
            cout << "Invalid selection." << endl;
        }//end switch

        displayMenu();     //display menu

        cout << "Enter your choice: ";
        cin >> choice;     //get the next request
        cin.get(ch);
        if(!cin)
        {
            cin.clear();
            cin.ignore(500,'\n');
        }

        cout << endl;
    }//end while
}


// Function to get a valid user for use in the store
// PRE: customerList already defined
// POST: reference to valid customer returned from function
        // OR, customer with Escape Val set to acc#
customerType& customerSignIn(customerListType& customerList)
{

    int option;
    string input1, input2;
    int accNumber;

    customerType newCustomer;

    string fName, lName, address, phone, email;


    linkedListIterator<customerType> it;

    do
    {
        cout<<"Welcome Menu"<<endl
        <<"1) Sign in with account #"<<endl
        <<"2) Sign in by name"<<endl
        <<"3) Create a new account"<<endl
        <<"5) Display full customer list (store use only)"<<endl
        <<"9) Exit"<<endl;

        cin>>option;
        cin.ignore (500, '\n');

        if(!cin)
        {
            cin.clear();
            cin.ignore(500,'\n');
        }

       switch(option)
       {
           case 1:  cout<<"Account Number: ";
                    cin>>accNumber;
                    if(!cin)
                    {
                        cin.clear();
                        cin.ignore(500,'\n');
                        accNumber = 0;
                    }
                    for(it = customerList.begin(); it!=customerList.end(); ++it)        //traverse list using iterator...
                    {
                        if( (*it).getAccNum() == accNumber )                                // if account number is found
                        {
                            return it.getElementRef();                                      // return reference to object
                            //return &(*it);
                        }
                    }
                    cout<<"The Account Number: "<<accNumber<<" is not in the database."<<endl;    // not found... display a message
                    break;

           case 2:  cout<<"First Name: ";       // prompt user for information...
                    cin>>fName;
                    cout<<"Last Name: ";
                    cin>>lName;
                    for(it = customerList.begin(); it != customerList.end(); ++it)  // use iterator to traverse the list
                    {
                        if( (*it).getLastName() == lName )                         // If the last name matches that of this element...
                        {
                            if( (*it).getFirstName() == fName )                    // And the first name matches....
                            {
                                return it.getElementRef();                          // user found, return user by ref
                            }
                        }
                    }
                    cout<<"The user: "<<fName<<" "<<lName<<" is not in the database."<<endl;    // not found... display a message
                    break;
            case 3: cout<<"First Name: ";               // Prompt User for information
                    cin>>fName;
                    cout<<"Last Name: ";
                    cin>>lName;
                    cout<<"Address: ";
                    cin>>address;
                    cout<<"Phone #: ";
                    cin>>phone;
                    cout<<"Email: ";
                    cin>>email;

                    // set customer's info into object instance
                    newCustomer.setInfo(fName,lName, address, email, phone);
                    newCustomer.setupAccount();
                    accNumber = customerList.length() + BASE_ACC_NUM;         // Account numbers is size +BASE
                    newCustomer.setAccNum(accNumber);

                    customerList.insertFirst(newCustomer);              // add object to the front of the list
                    it = customerList.begin();                          // set iterator to front of the list
                    return it.getElementRef();                          // return the new object by reference
                    break;
            case 5: if(customerList.length() == 0)
                        cout<< "We have no customers...  (Sad Face)."<<endl;
                    else
                        customerList.print();
                    break;

            case 9: newCustomer.setAccNum(ESCAPE_VAL);                  // create a customer with an escape value for account#
                    customerList.insertFirst(newCustomer);              // insert into the front of the list...
                    it = customerList.begin();
                    return it.getElementRef();                          // return a reference to the object
                    break;

            default: cout<<"Invalid input"<<endl;
                    break;
        }
   }while(option != 9);
}

void createVideoList(ifstream& infile,
                     videoListType& videoList)
{
    string title;
    string star1;
    string star2;
    string producer;
    string director;
    string productionCo;
    char ch;
    int inStock;

    videoType newVideo;

    getline(infile, title);

    while (infile)
    {
        getline(infile, star1);
        getline(infile, star2);
        getline(infile, producer);
        getline(infile, director);
        getline(infile, productionCo);
        infile >> inStock;
        infile.get(ch);
        newVideo.setVideoInfo(title, star1, star2, producer,
                              director, productionCo, inStock);
        videoList.insertFirst(newVideo);

        getline(infile, title);
    }//end while
}//end createVideoList



void displayMenu()
{
    cout << "Select one of the following:" << endl;
    cout << "0: To review your full account information." <<endl;
    cout << "1: To check whether the store carries a "
         << "particular video." << endl;
    cout << "2: To check out a video." << endl;
    cout << "3: To check in a video." << endl;
    cout << "4: To check whether a particular video is "
         << "in stock." << endl;
    cout << "5: To print only the titles of all the videos."
         << endl;
    cout << "6: To print a list of all the videos." << endl;
    cout << "7: To stream a video to a device"<<endl;
    cout << "8: To stop streaming a video to a device"<<endl;
    cout << "9: To update personal account information"<<endl;
    cout << "10: To make changes to your account."<<endl;
    cout << "11: To view full list of movies currently checked out (store use only)"<<endl;
    cout << "99: To exit" << endl;
} //end displayMenu

// Function to add dummy customers to the store
void supplyCustomers(customerListType& customerList)
{
    int accNum = customerList.length() + BASE_ACC_NUM;
    customerType customer1 = customerType(accNum,"Scott","Davis");
    customerType customer2 = customerType(accNum+1,"Tony","Stark");
    customerType customer3 = customerType(accNum+2,"Peter","Parker");
    customerType customer4 = customerType(accNum+3,"Steve","Rogers");
    customerType customer5 = customerType(accNum+4,"Bruce","Banner");

    customerList.insertFirst(customer1);
    customerList.insertFirst(customer2);
    customerList.insertFirst(customer3);
    customerList.insertFirst(customer4);
    customerList.insertFirst(customer5);

}

/*
void testCustomer()
{
   customerType customer1;
    string title;
    char choice;
    int option;
    videoType myMovie;

    do{
        customer1.printInfo();
        do
        {
            cout<<"Customer Menu "<<endl
            <<"1: Rent Movie"<<endl
            <<"2: Return Movie"<<endl
            <<"3: Stream Movie"<<endl
            <<"4: Stop Movie Stream"<<endl
            <<"5: Account Changes"<<endl
            <<"6: Update Customer Info"<<endl
            <<"9: Exit"<<endl;
            cin>>option;
            cin.ignore (500, '\n');

            if(!cin)
            {
                cin.clear();
                cin.ignore (500, '\n');
            }

            switch(option)
            {
                case 1: cout<<"Rent Movie Title: "<<endl;

                        getline(cin,title);
                        myMovie = videoType(title);
                        customer1.rentMovie(title );
                        break;
                case 2: customer1.printRentedMovies();
                        cout<<"Return Movie Title: "<<endl;

                        getline(cin,title);
                      //  myMovie = videoType(title);
                        customer1.returnMovie(title);
                        break;
                case 3: cout<<"Stream Movie Title: "<<endl;
                        getline(cin,title);
                        myMovie = videoType(title);
                        customer1.rentMovie(title );
                        break;
                        customer1.streamMovie(title);
                        break;
                case 4: customer1.stopStream(title);
                        break;
                case 5: customer1.changeAccount();
                        break;
                case 6: customer1.updatePersonalInfo();
                        break;
                case 9: break;
                default: cout<<"Invalid input"<<endl;
                        break;
            }
            customer1.printInfo();
        }while(option!=9);

        cout<<"Continue Yes(Y) No(N)"<<endl;
        cin>>choice;
        choice = toupper(choice);

    }while(choice != 'N' );
}

void testPerson()
{
    PersonType myPerson;
    string first, last;
    char choice;

    do{
        cout<<"First and Last name: ";
        cin>>first;
        cin>>last;
        myPerson.setName(first,last);
        myPerson.print();
        cout<<"First and Last name: ";
        cin>>first;
        cin>>last;
        myPerson = PersonType(first,last);
        myPerson.print();
        cout<<myPerson.getLastName()<<", "<<myPerson.getFirstName()<<endl;


        cout<<"Continue Yes(Y) No(N)"<<endl;
        cin>>choice;
        choice = toupper(choice);

    }while(choice != 'N' );
}

void testAcct()
{
    int option;
    char choice;
    AcctType myAccount;

    do{
        myAccount.print();

        do
        {
            cout<<"Menu "<<endl
            <<"1: Add feature"<<endl
            <<"2: Remove Feature"<<endl
            <<"3: Add All Features"<<endl
            <<"4: Remove All Features"<<endl
            <<"5: Display Price"<<endl
            <<"9: Exit"<<endl;
            cin>>option;

            if(!cin)
            {
                cin.clear();
                cin.ignore(500,'\n');
            }

            switch(option)
            {
                case 1: myAccount.addFeatures();
                        break;
                case 2: myAccount.removeFeatures();
                        break;
                case 3: myAccount.addAllFeatures();
                        break;
                case 4: myAccount.removeAllFeatures();
                        break;
                case 5: cout<<"Price: "<<myAccount.getPrice()<<endl;
                        break;
                case 9: break;
                default: cout<<"Invalid input"<<endl;
                        break;
            }
            myAccount.print();
        }while(option!=9);


        cout<<"Continue Yes(Y) No(N)"<<endl;
        cin>>choice;
        choice = toupper(choice);

        if(choice != 'N')
            myAccount = AcctType();
    }while(choice != 'N' );
}
*/
