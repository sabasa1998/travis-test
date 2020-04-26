#ifndef NEURALNET_H
#define NEURALNET_H
#include "Matrix.h"
#include "dataset.h"
#include "result.h"

class NeuralNet
{
private:
    Matrix w1; // Weights of layer 1
    Matrix w2; // Weights of layer 2
    Matrix b1; // Biases of layer 1
    Matrix b2; // Biases of layer 2
    Matrix a1; // Output of layer 1
    Matrix a2; // Output of layer 2
    Matrix n1; // n vector for layer 1
    Matrix n2; // n vector for layer 2
    Matrix s1; // s vector for layer 1
    Matrix s2; // s vector for layer 2 
    const char* af1{"Sigmoid"};
    const char* af2{"Sigmoid"};
    size_t hidden_layer_neurons{3}; //No of neurons in the hidden layer of the network.
    double lr{0.01};
    size_t max_iters{1000};
    double min_loss{0.01};
    Dataset dataset;


public:
    //constructors:
    NeuralNet();
    NeuralNet(Dataset dataset, size_t hidden_layer_neurons, const char* f1 = "Sigmoid", const char* f2 = "Linear", double lr = 0.1, size_t max_iters = 10000, double min_loss=0.01);
    //~NeuralNet();

    //other functions:
    Matrix sigmoid(Matrix& m);
    //Matrix sigmoid_derivative(Matrix& m);
    double sigmoid_derivative(double d);
    Matrix linear(Matrix& m);
    Matrix linear_derivative(Matrix& m);
    //functions:
    Matrix forwardPropagate(Matrix& input); //mage nabayd ghablesh tabe e af ro benevisam ke baad w*vurudi + bias ro befrestam tush ke bere vurudie layeye baad?
    void backPropagate(Matrix& input, Matrix& target);
    double trainLoss();
    double testLoss();
    //setters:
    void setW1(Matrix& w);
    void setW2(Matrix& w);
    void setB1(Matrix& b);
    void setB2(Matrix& b);
    //getters:
    Matrix getW1();
    Matrix getW2();
    Matrix getB1();
    Matrix getB2();

    Result fit();
    void show();
    friend std::ostream& operator<<(std::ostream& os, const NeuralNet &nn);
    
};
#endif