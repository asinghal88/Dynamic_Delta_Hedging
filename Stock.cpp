#include "Stock.h"

Stock::Stock()
{
    //ctor
}

Stock::Stock(double spot_p, double mu, double div, double rate)
{
    this -> spot_p = spot_p;
    this -> mu = mu;
    this -> div = div;
    this -> rate = rate;
}

Stock::~Stock()
{
    //dtor
}
