#ifndef APHW3_H
#define APHW3_H
#include <iostream>
#include "dataset.h"
#include "result.h"

std::vector<std::vector<double>> getData(const char* filename); //check
Dataset loadFuncDataset(const char* filename);  //check
std::vector<Result> testNeuralNets(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr=0.01, size_t max_iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear");  // check(faghat dimension a moshkel daran)
Result findBestNeuralNet(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr=0.01, size_t max_iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear"); //check(faghat dimension a moshkel daran)
void estimateFunction(const char* filename, size_t hidden_neurons_no);

#endif