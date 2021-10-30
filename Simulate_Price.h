#ifndef SIMULATE_PRICE_H
#define SIMULATE_PRICE_H
#include "Stock.h"
#include "Option.h"

class Simulate_Price
{
    public:
        Simulate_Price();
        virtual ~Simulate_Price();
        double simulate_save_results(Stock &stock, Option& option, int steps, int total_paths, double maturity_time);
    protected:

    private:
};

#endif // SIMULATE_PRICE_H
