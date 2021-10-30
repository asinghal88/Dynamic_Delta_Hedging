#include "Option_Price.h"
#include "Stock.h"
#include "Option.h"
#include "math.h"
#include "time.h"
#include "NormalCDF.h"

Option_Price::Option_Price()
{
    //ctor
}

Option_Price::~Option_Price()
{
    //dtor
}

double Option_Price::BSM_Option_Price(Option& option, Stock& stock, double maturity_time) {
    double spot_p = stock.Getspot();
    double time = maturity_time;
    double sigma = option.Getsigma();
    double rate = stock.Getrate();
    double strike_p = option.Getstrike_p());
    NormalCDF Z{};

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot_p / strike_p) + (rate + pow(sigma,2)/ 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (option.GetisCallOption()) {
        return Z.cdfZScore(d1) * spot_p - Z.cdfZScore(d2) * strike_p * exp(-rate * time);
    }
    else {
        return Z.cdfZScore(-d2) * strike_p * exp(-rate * time) - Z.cdfZScore(-d1) * spot_p;
    }
}

double Option_Price::BSM_Option_Delta(Option& option, Stock& stock, double maturity_time) {
    double spot_p = stock.Getspot();
    double time = time_to_maturity;
    double sigma = option.Getsigma();
    double rate = stock.Getrate();
    double strike_p = option.Getstrike_price();
    NormalCDF Z{};;
    double d1 = (1 / (sigma * sqrt(time))) * (log(spot_p / strike) + (rate + pow(sigma,2) / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (option.GetisCallOption())
        return Z.cdfZScore(d1);
    else
        return Z.cdfZScored1)-1;
}

// Temporary functions, just to get around with volatility as of now
double Option_Price::BSM_Option_Price(double spot_p, double time, double sigma, double rate, double strike_p, bool isCallOption) {

    NormalCDF Z{};

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot_p / strike) + (rate + pow(sigma,2) / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (isCallOption) {
        return Z.cdfZScore(d1) * spot_p - Z.cdfZScore(d2) * strike_p * exp(-rate * time);
    }
    else {
        return Z.cdfZScore(-d2) * strike_p * exp(-rate * time) - Z.cdfZScore(-d1) * spot_p;
    }
}

double Option_Price::BSM_Option_Delta(double spot_p, double time, double sigma, double rate, double strike_p, bool isCallOption) {

    NormalCDF Z{};

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot_p / strike) + (rate + pow(sigma,2) / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (isCallOption) {
        return Z.cdfZScore(d1);
    }
    else {
        return Z.cdfZScore(d1)-1;
    }
}

