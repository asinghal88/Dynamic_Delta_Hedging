#include "Simulate_Price.h"
#include "Stock.h"
#include "Option.h"
#include "Option_Price.h"
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

Simulate_Price::Simulate_Price()
{
    //ctor
}

Simulate_Price::~Simulate_Price()
{
    //dtor
}

double Simulate_Price::simulate_save_results(Stock &stock, Option& option, int steps, int total_paths, double maturity_time) {
    default_random_engine generator;
    normal_distribution<double> normal(0.0,1.0);

    Option_Price op{};

	double dT = maturity_time/steps;
    double simulated_price[steps+1], call_price[steps+1], delta[steps+1], hed_error[steps+1], portfolio[steps+1];
    simulated_price[0] = stock.Getspot_p();
    hed_error[0] = 0.1;  // verify this assumption - this is not accurate, only an approximation
    ofstream hedgefile;
    hedgefile.open("hedging_error_new.csv", ios_base::app);
    ofstream stockfile;
    stockfile.open("stock_path_new.csv", ios_base::app);

    while (total_paths>0) {
        for(int i = 1; i <= steps ;i++) {
                // verify the formulaes
            double normalVar = normal(generator);
            simulated_price[i] = simulated_price[i-1]*(1.0 + stock.Getmu()*dT + option.Getsigma()*sqrt(dT)*normalVar);
            call_price[i] = op.BSM_Option_Price(option, stock, maturity_time - (i+1)*dT);
            delta[i] = op.BSM_Option_Delta(option, stock, maturity_time - (i+1)*dT);
            hed_error[i] = delta[i-1]*simulated_price[i] + hed_error[i-1]*exp(stock.Getrate()*dT) - delta[i]*simulated_price[i];
            portfolio[i] = delta[i-1]*simulated_price[i] + hed_error[i-1]*exp(stock.Getrate()*dT) - call_price[i];
            stockfile << to_string(simulated_price[i]) << ",";
        }
//        std::cout << simulated_price[steps-1] << " " << portfolio[steps-1] << std::endl;
        sample_path_file << endl;
        hedgefile << to_string(portfolio[steps-1]) << endl;
        total_paths -= 1
    }
}
