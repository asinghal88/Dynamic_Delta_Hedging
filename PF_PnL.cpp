#include "PF_PnL.h"
#include <map>
#include <ctime>
#include "Option_Price.h"
#include "vector"
#include "math.h"
#include <fstream>

using namespace std;

PF_PnL::PF_PnL()
{
    //ctor
}

PF_PnL::~PF_PnL()
{
    //dtor
}

double caluclate_imp_vol(double target_p,  double strike_p, double spot_p, double interest_rate, double maturity_time, bool isCallOption) {
    double epsilon = 0.000001;
    double a = 0.0, b = 1.0;

    Option_Price op{};
    double sigma_x = 0.5 * (a + b);
    double BSMprice = op.BSM_Option_Price(spot_p, maturity_time, sigma_x, interest_rate, strike_p, isCallOption);

    int n=0;
    double y = BSMprice;
    while (abs(y-target_p) > epsilon){
        n++;
        if(n>1000000){
            return sigma_x;
        }
        if (y < target_p) {
            a = sigma_x;
        }
        if (y > target_p) {
            b = sigma_x;
        }

        sigma_x = 0.5 * (a + b);
        y = op.BSM_Option_Price(spot_p, maturity_time, sigma_x, interest_rate, strike_p, isCallOption);
    }

        return sigma_x;
}

void PF_PnL::calculate_bsm_pnl_and_save(vector<double> interest_rates, vector<double> stock_prices , vector<double> option_prices, vector<double> maturity_time,
                                        double strike_p, bool isCallOption, map<string, double> rates_map)
{
    vector<double> imp_vol;
    vector<double> delta;
    vector<double> hed_error;
    vector<double> pnl;
    vector<double> pnl_with_hedge;
    vector<double> portfolio;

    double dT = 1/252.0;

    hed_error.push_back(0);
    pnl_with_hedge.push_back(0);

    Option_Price op{};

    for (int i = 0; i < interest_rates.size(); ++i) {

        imp_vol.push_back(caluclate_imp_vol(option_prices[i], strike_p, stock_prices[i],interest_rates[i], maturity_time[i], isCallOption));
        delta.push_back(op.BSM_Option_Delta(stock_prices[i], maturity_time[i], imp_vol[i], interest_rates[i], strike_p, isCall));
        pnl.push_back(option_prices[0] - option_prices[i]);
        double portfolioVal;

        if(i < 1)
            portfolioVal = option_prices[i] - delta[i]*stock_prices[i];
        else {
            portfolioVal = delta[i-1]*stock_prices[i] + portfolio[i-1]*exp(interest_rates[i]*dT) - delta[i]*stock_prices[i];
            double hedge_error = delta[i-1]*stock_prices[i] + portfolio[i-1]*exp(interest_rates[i-1]*dT) - option_prices[i];
            hed_error.push_back(hedge_error);
            pnl_with_hedge.push_back(hedge_error);

        }
        portfolio.push_back(portfolioVal);
    }

    ofstream output;
    output.open("results.csv", ios_base::app);

    map<string, double>::iterator itr;
    output << "Date,Stock Price, Option Price, Implied Volatility, Delta, Hedging Error, PNL, PNL with hedge" << endl;
    int i = 0;
    for (itr = rates_map.begin(); itr != rates_map.end(); ++itr, i++) {
        output << itr->first << "," << stock_prices[i] << "," << option_prices[i] << "," << imp_vol[i] << "," << delta[i] << "," << hed_error[i] << "," << pnl[i]<< "," <<pnl_with_hedge[i] << endl;
    }
}


