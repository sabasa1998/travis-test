#ifndef DATASET_H
#define DATASET_H
#include <ostream>
#include "Matrix.h"

class Dataset
{
private:
    Matrix inputs;
    Matrix targets;
    Matrix train_inputs;
    Matrix train_targets;
    Matrix test_inputs;
    Matrix test_targets;
    double percentage{70};
    size_t no_of_samples;
    size_t input_dim;
    size_t target_dim;

public:

    //constructors:
    Dataset();
    Dataset(Matrix inputs, Matrix targets, double percentage=70);
    Dataset(Matrix inputs, Matrix targets, Matrix train_inputs, Matrix train_targets, Matrix test_inputs, Matrix test_targets);


    //functions:
    size_t getNoOfSamples();
    size_t getNoOfTrainSamples() const;
    size_t getNoOfTestSamples() const;
    size_t getInputDim() const;
    size_t getTargetDim() const;
    Matrix getInputs();
    Matrix getTargets();
    Matrix getTrainInputs();
    Matrix getTrainTargets();
    Matrix getTestInputs();
    Matrix getTestTargets();
    void shuffle();    //col hsh ghati mishan 

    void show();
   // Dataset operator=(const Dataset&); //be kar nayumad
    std::vector<Matrix> operator[](size_t i);
    Dataset operator+(const Dataset& dataset);
    friend std::ostream& operator<<(std::ostream& os, const Dataset &d);
};

#endif