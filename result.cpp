#include <iostream>
#include "result.h"

///////////!!!!!!!!!!!!!!!!operator is not created yet !!!!!!!!!!!!!!!!!!!!!!


////////////////////////////////////////////////constructors////////////////////////////////////////
Result::Result()
{
    std::cout<<"default result constructor is created: "<<std::endl;
}
Result::Result(double train_loss, double test_loss, size_t no_of_hidden_neurons,
                 double lr, size_t iters, const char* af1 , const char* af2)
{
    std::cout << "result obj is created"<<std::endl;
    this -> train_loss = train_loss;
    this -> test_loss = test_loss;
    this -> no_of_hidden_neurons = no_of_hidden_neurons;
    this ->lr = lr;
    this -> iters = iters;
    this -> af1 = af1;
    this -> af2 = af2;
}
Result::Result(double test_loss)
{
    this -> test_loss = test_loss;
    train_loss = -1;
    no_of_hidden_neurons = 0;
    lr = 0.01;
    iters = 10000;
    af1 = "sigmoid";
    af2 = "linear";
}
//////////////////////////////////////////////functions///////////////////////////////////////////
double Result::getTestLoss()
{
    return test_loss;
}

void Result::show()
{
    std::cout<<"Result: "<<std::endl;
    std::cout<<"\t"<< "Train loss: "<<train_loss<<std::endl;
    std::cout<<"\t"<< "Test loss: "<<test_loss<<std::endl;
    std::cout<<"\t"<< "Layer 1 activation function: "<<af1<<std::endl;
    std::cout<<"\t"<< "Layer 2 activation function: "<<af2<<std::endl;
}
/////////////////////////////////////////////////////////operators/////////////////////////////////////////////////////////////
bool Result::operator<(const Result& r) const
{
    std::cout <<"operator < is created"<< std::endl;

    return this -> test_loss < r.test_loss;
}

bool Result::operator>(const Result& r) const
{
    std::cout <<"operator > is created"<< std::endl;

    return this -> test_loss > r.test_loss;
}

bool Result::operator>=(const Result& r) const
{
    std::cout <<"operator >= is created"<< std::endl;

    return this -> test_loss >= r.test_loss;
}

//overloading of << operator as a friend function of class
std::ostream &operator<<(std::ostream &os, const Result &r)
{ 
    os <<"Result: ****"<< std::endl;
    os <<"\t" << "Train loss: " <<r.train_loss<< std::endl;
    os << "\t" << "Test loss: " <<r.test_loss<< std::endl;
    os << "\t" <<"Layer 1 activation function: " <<r.af1<< std::endl;
    os << "\t" << "Layer 2 activation function: "<<r.af2<< std::endl;
    return os;
}

