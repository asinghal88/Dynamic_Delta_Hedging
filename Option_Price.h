#ifndef OPTION_PRICE_H
#define OPTION_PRICE_H
#include "Stock.h"
#include "Option.h"

class Option_Price
{
    public:
        Option_Price();
        virtual ~Option_Price();
        double BSM_Option_Price(Option& option, Stock& stock, double maturity_time);
        double BSM_Option_Delta(Option& option, Stock& stock, double maturity_time);
        double BSM_Option_Price(double spot, double time, double sigma, double rate, double strike, bool isCallOption);
        double BSM_Option_Delta(double spot, double time, double sigma, double rate, double strike, bool isCallOption);

    protected:

    private:
};

#endif // OPTION_PRICE_H
