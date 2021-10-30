#ifndef PF_PNL_H
#define PF_PNL_H
#include <map>
#include "vector"

class PF_PnL
{
    public:
        PF_PnL();
        virtual ~PF_PnL();
        void calculate_bsm_pnl_and_save(vector<double> int_rates, vector<double> stock_prices, vector<double> option_prices, vector<double> maturity_time, double strike_prices, bool isCallOption, map<string, double> rates_map);

    protected:

    private:
};

#endif // PF_PNL_H
