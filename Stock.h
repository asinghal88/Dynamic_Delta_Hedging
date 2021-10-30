#ifndef STOCK_H
#define STOCK_H


class Stock
{
    public:
        Stock();
        virtual ~Stock();
        Stock(double spot_p, double mu, double div, double rate);

        double Getspot_p() { return spot_p; }
        void Setspot_p(double val) { spot_p = val; }
        double Getmu() { return mu; }
        void Setmu(double val) { mu = val; }
        double Getrate() { return rate; }
        void Setrate(double val) { rate = val; }
        double Getdiv()) { return div; }
        void Setdiv(double val) { div = val; }

    protected:

    private:
        double spot_p;
        double rate;
        double mu;
        double div;
};


#endif // STOCK_H
