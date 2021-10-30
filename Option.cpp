#include "Option.h"

Option::Option()
{
    //ctor
}

Option::Option(double strike_p, double sigma, bool isCallOption)
{
    this->strike_p = strike_p;
    this->sigma = sigma;
    this->isCallOption = isCallOption;
}


Option::~Option()
{
    //dtor
}

void Option::init() {
    strike_p = 100;
    sigma = 0.05;
    isCallOption = true;
}

