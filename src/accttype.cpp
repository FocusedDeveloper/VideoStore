#include "accttype.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

AcctType::AcctType()
{
    maxDevices = 0;
    maxDvds = 0;
    bluRayAccess = false;
    xHDAccess = false;
    price = 0.0;

    //initAccount();
    //price = calcPrice();
    //ctor
}

void AcctType::initAccount()
{
    bool valid = false;
    int option;

    do
    {
        // customer must have either a dvd or streaming account
        cout<< "Account Type:" << endl
            << "1: DVD Rentals " << endl
            << "2: Moving Streaming" << endl
            << "3: DVDs and Streaming" << endl
            << endl;
        cin >> option;

        if(!cin)
        {
            cin.clear();
            cin.ignore(500,'\n');
        }

        switch(option)
        {
            case 1: maxDvds = 1;        // Initialize maxAvailable Dvds
                    valid = true;
                    break;
            case 2: maxDevices = 1;             // and or devices to 1
                    valid = true;
                    break;
            case 3: maxDvds = 1;
                    maxDevices = 1;
                    valid = true;
                    break;
            default:
                    cout << "Invalid input.  Please try again." << endl;
                    break;
        }
    }while(!valid);
    price = calcPrice();
}

double AcctType::calcPrice() const
{
    int totalFeatures = 0;

    double tempPrice = 0.0;

    totalFeatures += (maxDevices + maxDvds );   // add the number of devices and the number of dvds
                                                    // each is one feature
    if( xHDAccess)
        totalFeatures++;                        // add 1 feature for extreme HD
    if( bluRayAccess)
        totalFeatures++;                        // add 1 feature for blu-ray access

    if( totalFeatures > 0)                      // if there is at least one feature, incur the base price
        tempPrice = BASE_PRICE;

    if(totalFeatures > 1 )                      // 2nd feature is $3
        tempPrice+= 3.0;

    if( totalFeatures > 2 )                     // add price of the 3rd feature
        tempPrice+= 2.0;

    if( totalFeatures > 3 )                     // buy four features, get the rest free
        tempPrice+= 1.0;

    return tempPrice;
}

void AcctType::print() const
{
    cout << "DVD Service: ";
    if( maxDvds > 0 )                               // if DVDs are available...
    {
        cout << "True." << endl                         // display true
            <<"    Total Dvds: " << maxDvds<<endl
            <<"    Blu-ray Access: ";                   // check blu-rays
        if(bluRayAccess)
            cout<<"True"<<endl;
        else
            cout << "False" <<endl;
    }
    else
        cout <<"False."<<endl;
    cout<< "Streaming Service: ";
    if( maxDevices > 0 )                                    // Check if streaming is available...
    {
        cout << "True." <<endl
            <<"    Total Devices: " << maxDevices<<endl
            <<"    Extreme HD Streaming Access: ";
        if(xHDAccess)
            cout<<"True"<<endl;
        else
            cout << "False" <<endl;
    }
    else
        cout<<"False."<<endl;

    cout<<fixed<<setprecision(2)<< "Total Monthly Price: $"<<price;
    cout<<endl;

}

void AcctType::addFeatures()
{
    int option;
    string message1 = "This feature is currently active.";
    string message2 = "Feature is currently at maximum allowed.";
    string message3 = "You don't have the prerequisite for this feature.";
    double tempPrice = price;

    do
    {
        cout<< "Add Features"<<endl
            << "0: Review Your Account Setup"<<endl
            << "1: Rent DVDs"<<endl
            << "2: Rent Blu-rays"<<endl
            << "3: Increase Disc per day"<<endl
            << "4: Video Streaming"<<endl
            << "5: Extreme HD Video Streams"<<endl
            << "6: Increase Devices at a Time"<<endl
            << "9: Exit"<<endl;
            cin>>option;

            if(!cin)
            {
                cin.clear();
                cin.ignore(500,'/n');
            }

            switch(option)
            {
                case 0:
                        price = calcPrice();
                        print();
                        break;

                case 1:
                    if(maxDvds > 0 )
                        cout<<message1<<endl;
                    else
                        maxDvds = 1;
                    break;
                case 2:
                    if(maxDvds > 0)             // If we have access to DVDs...
                    {
                        if(bluRayAccess )           // and we already have access to blu-rays...
                            cout<<message1<<endl;       // nothing to change.  print message
                        else
                            bluRayAccess = true;    // else, turn on blu-ray
                    }
                    else
                        cout<<message3<<endl;

                    break;
                case 3:
                    if(maxDvds == MAX_DVDS )
                        cout<<message2<<endl;
                    else
                        maxDvds++;
                    break;

                case 6:
                    if(maxDevices == MAX_DEVICES )      // if streaming devices is at max
                        cout<<message2<<endl;               // display a message
                    else
                        maxDevices++;                   // else, increase
                    break;
                case 5:
                    if(maxDevices > 0)              // if we have access to streaming...
                    {
                        if(xHDAccess )                  // if streaming is already on, print message
                            cout<<message1<<endl;
                        else
                            xHDAccess = true;
                    }
                    else
                        cout<<message3<<endl;
                    break;
                case 4:
                    if(maxDevices > 0 )
                        cout<<message1<<endl;
                    else
                        maxDevices = 1;
                    break;
                case 9: break;

                default:
                    cout<<"Invalid input.  Please try again."<<endl;
                    break;
            }

    }while(option != 9);

    price = calcPrice();

    if(tempPrice == price)
        cout<<"No changes were made to this account"<<endl;
    else
    {
        cout<<"This account has been updated."<<endl;
        cout<<"Your new monthly bill: $"<<fixed<<setprecision(2)<<price<<endl;
    }

}

void AcctType::removeFeatures()
{
    int option;
    string message1 = "This feature is not currently active.";
    string message2 = "Feature is currently at its minimum.";
    double tempPrice = price;

    do          // Menu Loop
    {
        cout<< "Remove Features"<< endl
            << "0: Review Your Account Setup"<<endl
            << "1: Discontinue DVDs"<<endl
            << "2: Discontinue Blu-rays"<<endl
            << "3: Decrease Disc per day"<<endl
            << "4: Discontinue Video Streaming"<<endl
            << "5: Discontinue Extreme HD Video Streams"<<endl
            << "6: Decrease Streaming Devices at a Time"<<endl
            << "9: Exit"<<endl;
            cin>>option;

            if(!cin)                    // reset cin on invalid input
            {
                cin.clear();
                cin.ignore(500,'/n');
            }

            switch(option)
            {
                case 0: price = calcPrice();
                        print();
                        break;
                case 1:
                    if(maxDvds == 0 )
                        cout<<message1<<endl;
                    else
                    {
                        maxDvds = 0;                // loss of DVD acess == loss of blu-ray also
                        bluRayAccess = false;
                    }

                    break;
                case 2:
                    if(!bluRayAccess )
                        cout<<message1<<endl;
                    else
                        bluRayAccess = false;
                    break;
                case 3:
                    if(maxDvds <= 1 )
                        cout<<message2<<endl;
                    else
                        maxDvds--;
                    break;

                case 4:
                    if(maxDevices == 0 )
                        cout<<message2<<endl;
                    else
                    {
                        maxDevices = 0;         // loss of streaming == loss of HD Streaming
                        xHDAccess = false;
                    }
                    break;
                case 5:
                    if(!xHDAccess )
                        cout<<message1<<endl;
                    else
                        xHDAccess = true;
                    break;
                case 6:
                    if(maxDevices <= 1 )
                        cout<<message1<<endl;
                    else
                        maxDevices--;
                    break;
                case 9: break;

                default:
                    cout<<"Invalid input.  Please try again."<<endl;
                    break;
            }

    }while(option != 9);

    price = calcPrice();        // recalculate the price

    if(tempPrice == price)
        cout<<"No changes were made to this account"<<endl;
    else
    {
        cout<<"This account has been updated."<<endl;
        cout<<"Your new monthly bill: $"<<fixed<<setprecision(2)<<price<<endl;
    }
}

void AcctType::removeAllFeatures()
{
    maxDevices = 0;
    maxDvds = 0;
    bluRayAccess = false;
    xHDAccess = false;
    price = 0.0;
}

void AcctType::addAllFeatures()
{
    maxDevices = MAX_DEVICES;
    maxDvds = MAX_DVDS;
    bluRayAccess = true;
    xHDAccess = true;
    price = calcPrice();
}

double AcctType::getPrice() const
{
    return price;
}

int AcctType::getMaxDvds() const
{
    return maxDvds;
}

int AcctType::getMaxDevices() const
{
    return maxDevices;
}

bool AcctType::getBluRayAccess() const
{
    return bluRayAccess;
}

bool AcctType::getHDAccess() const
{
    return xHDAccess;
}
