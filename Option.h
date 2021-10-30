#ifndef OPTION_H
#define OPTION_H


class Option
{
    public:
        Option();
        Option( double strike_p, double sigma, bool isCallOption)
        virtual ~Option();
        double Getstrike_p() { return strike_p; }
        void Setstrike_p(double val) { strike_p = val; }
        double Getsigma() { return sigma; }
        void Setsigma(double val) { sigma = val; }
        bool GetisCallOption() { return isCallOption; }
        void SetisCallOption(bool val) { isCallOption = val; }

    protected:


    private:
        void init();
        double strike_p;
        bool isCallOption;
        double sigma;
};

#endif // OPTION_H
