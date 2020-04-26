#ifndef RESULT_H
#define RESULT_H
#include <iostream>


class Result
{
private:
    double train_loss;
    double test_loss;
    size_t no_of_hidden_neurons;
    double lr{};
    size_t iters{};
    const char* af1;
    const char* af2;
public:
    //constructors:
    Result();
    Result(double train_loss, double test_loss, size_t no_of_hidden_neurons, double lr = 0.01, size_t iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear");
    Result(double test_loss);

    //functions:
    double getTestLoss();
    void show();
    

    //operators:
    bool operator<(const Result&) const;
    bool operator>(const Result&) const;
    bool operator>=(const Result& r) const;
    friend std::ostream& operator<<(std::ostream& os, const Result &r);
    


};
#endif