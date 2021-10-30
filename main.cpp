#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include "Option.h"
#include "Stock.h"
#include "Simulate_Price.h"
#include <string>
#include "vector"
#include "Option_Price.h"
#include <bits/stdc++.h>
#include "PF_PnL.h"

using namespace std;

vector<double> getVectorFromMap(map<string, double> anyMap) {
    vector<double> returnMap;
    map<string, double>::iterator itr;
    for (itr = anyMap.begin(); itr != anyMap.end(); ++itr) {
        returnMap.push_back(itr->second);
    }
    return returnMap;
}

vector<double> getDailyTimeToMaturities(map<string, double> anyMap, string expiry) {
    vector<double> tmts;
    map<string, double>::iterator itr;
    for (itr = anyMap.begin(); itr != anyMap.end(); ++itr) {
        tmts.push_back(getDiffDates(itr->first, expiry));  // Here will come the getBusinessDay difference function
    }
    return tmts;
}

int main()
{
    cout << "Part 1 of the Assignment: Simulated Prices and Portfolio PnL" << endl;

    // Define the parameters for the simulation: Underlying Stock, Option details, period, time to maturity and number of sample paths to generate
    Stock stock{100,0.05, 0.0, 0.025};
    Option option{105,0.24,true};
    int period = 100;
    int number_of_paths = 100;
    double maturity_time = 0.4;

    // Run the simulation and store outputs
    Simulate_price sp{};
    sp.simulate_and_save_results(stock, option, period, number_of_paths, maturity_time);


    cout << "Part 1 of Completed: Check the results in Results.csv" << endl;
    cout << "Part 2 of the assignment: BS Model on Real data and PnL" << endl;

    cout << getDiffDates("2011-01-04", "2011-01-06") << endl;
    bool isAllDataCorrect = false;
    string window_start;
    string window_end;
    string expiry_option;
    string strike_price;

    cin >> window_start >> window_end >> expiry_option >> strike_price;
    map<string, double> interest_rates = readRate_StockPrice(window_start, window_end, "./data/interest.csv");
    map<string, double> stock_prices = readRate_StockPrice(window_start, window_end, "./data/sec_GOOG.csv");
    map<string, double> option_prices = readOptionData(window_start,window_end,expiry_option,"C",strike_price);

    if(interest_rates.size() != stock_prices.size() || option_prices.size() != stock_prices.size())
        {cout << "Something is going wrong, please check" << endl;
        cout << interest_rates.size() << " " << stock_prices.size() << " " << option_prices.size() << endl;}

    PF_PnL pnl_book{};
    pnl_book.calculate_bsm_pnl_and_save(getVectorFromMap(interest_rates), getVectorFromMap(stock_prices), getVectorFromMap(option_prices), getDailyTimeToMaturities(interest_rates,expiry_option),
                                        stod(strike_price), true, interest_rates);

    return 0;
}
// Interest rate and sotck price have structure so the function can be used interchangeably for both
map<string, double> readRate_StockPrice(string startDate, string endDate, string path) {
    //Assuming yyyy-mm-dd
    map<string,double> rate_map;
    ifstream infile(path);
    int read_flag = 0;
    string line;
    getline( infile, line );
    while (getline( infile, line )){

        stringstream current_line(line);
        string token;
        getline(current_line, token, ',');
        string cur_date = token;
        if (getDiffDates(startDate, cur_date) < 0) {
            continue;
        }

        if (getDiffDates(endDate, cur_date) > 0) {
            break;
        }

        getline(current_line, token, ',');
        rate_map.insert(make_pair(cur_date, stod(token)));
    }
    infile.close();
    return rate_map;
}


map<string, double> readOptionData(string startDate, string endDate, string expiry, string option_flag, string strike) {
    map<string,double> option_map;
    ifstream infile("./data/op_GOOG.csv");
    int read_flag = 0;
    string line;
    getline( infile, line );
    while (getline( infile, line )){

        stringstream current_line(line);
        string token;
        getline(current_line, token, ',');
        string cur_date = token;
        if (getDiffDates(startDate, cur_date) < 0) {
            continue;
        }

        if (getDiffDates(endDate, cur_date) > 0) {
            break;
        }

        getline(current_line, token, ',');
        string ex_date = token;
        getline(current_line, token, ',');
        string op_flag = token;
        getline(current_line, token, ',');
        //cout << cur_date << " " << ex_date << " " << op_flag << " " << token << endl;
        if (getDiffDates(ex_date, expiry) == 0 && op_flag == option_flag && token == strike) {
            getline(current_line, token, ',');
            double bid = stod(token);
            getline(current_line, token, ',');
            double ask = stod(token);
            option_map.insert(make_pair(cur_date, (bid+ask)/2));

        } else {
            continue;
        }
    }
    infile.close();
    return option_map;
}

tm make_tm(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    return tm;
}

double getDiffDates(string date1, string date2) {

    tm tm1 = make_tm(stoi(date1.substr(0, 4)),stoi(date1.substr(5, 6)),stoi(date1.substr(8,9)));    // April 2nd, 2012
    tm tm2 = make_tm(stoi(date2.substr(0, 4)),stoi(date2.substr(5, 6)),stoi(date2.substr(8,9)));

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    return difftime(time2, time1) / (365*60*60*24);
