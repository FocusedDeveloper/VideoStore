#ifndef ACCTTYPE_H
#define ACCTTYPE_H


class AcctType
{
    public:

        static constexpr double BASE_PRICE = 7.99;      // Base price for services per month
        static constexpr int MAX_DVDS = 3;          // Maximum number of DVD's and Devices available to customers
        static constexpr int MAX_DEVICES = 3;

        AcctType();

        void initAccount();
        // Function for initializing the account
        // Post: account has is either dvds, streaming or both

        void addFeatures();
        // Function to add features to the account
        // Post: Features updated. Price updated

        void removeFeatures();
        // Function to remove features from the account
        // Post: Features updated. Price updated

        void removeAllFeatures();
        // Function to remove all features from account
        // Post: all features removed from account. Price updated

        void addAllFeatures();
        // Function to add all features to account
        // Post: all available features are added to account. Price updated

        double getPrice() const;
        // returns price

        void print() const;

        int getMaxDvds() const;

        int getMaxDevices() const;

        bool getBluRayAccess() const;

        bool getHDAccess() const;

    private:

        int maxDvds;
        int maxDevices;
        bool bluRayAccess;
        bool xHDAccess;
        double price;

        double calcPrice() const;
        // Function calculates the price of the account type depending on features
        // Post: price is updated

};

#endif // ACCTTYPE_H
