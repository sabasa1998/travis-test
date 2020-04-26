#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "aphw3.h"
#include "Matrix.h"
#include "dataset.h"
#include "neuralnet.h"

std::vector<std::vector<double>> getData(const char* filename) 
{
    std::ifstream file{ filename };
    std::vector<std::vector<double>> data;
    char temp_char{','};
    double temp_double{};
    size_t counter{};
    while(temp_char==','){
        file >> temp_double;
        file >> temp_char;
        counter++;
    }
    file.close();
    file.open(filename);
    char delimiter;
    std::vector<double> features(counter , 1);
    while (!file.eof()) {
        for (size_t i = 0; i < counter ; i++)
            if (i < counter+1)
                file >> features[i] >> delimiter;
            else
                file >> features[counter];
        data.push_back(features);
    }
    return data;
}

Dataset loadFuncDataset(const char* filename)
{
    //std::cout<<"load function dataset is created"<<std::endl;

    char buf[] = "APHW3Data1.csv";
    std::vector<std::vector<double>> Data;
    Data = getData(&buf[0]);
    std::vector<std::vector<double>> input_Data{};
    for (size_t r = 0; r <  Data.size()-1 ; r++)
    {  
        std::vector<double> temp;
        for (size_t c = 0; c < Data[0].size(); c++)
        {
            temp.push_back(Data[r][c]);
        }
        input_Data.push_back(temp);
    }
    Matrix input = input_Data;

    std::vector<std::vector<double>> target_Data;
    for (size_t r = Data.size()- 1 ; r < Data.size(); r++)
    {
        std::vector<double> temp;
        for (size_t c = 0; c < Data[0].size(); c++)
        {
            temp.push_back(Data[r][c]);
        }
        target_Data.push_back(temp);
    }
    
    Matrix target = target_Data;
    Dataset dataset(input , target);
    return dataset;
}

std::vector<Result> testNeuralNets(Dataset& dataset, std::vector<size_t>& hidden_neurons, 
                                    double lr, size_t max_iters, const char* af1, const char* af2)
{
    dataset = dataset;
    hidden_neurons = hidden_neurons;
    lr = lr;
    max_iters = max_iters;
    af1 = af1;
    af2 = af2;
    std::vector<Result> result;
    std::cout<<"**********"<<std::endl;
    for (size_t i = 0; i < hidden_neurons.size(); i++)
    {
       NeuralNet nn(dataset , hidden_neurons[i]);
       
       Result Train(nn.testLoss());
       Train = nn.fit();
       result.push_back(Train); 
    }
    return result;
}

Result findBestNeuralNet(Dataset& dataset, std::vector<size_t>& hidden_neurons,
                             double lr, size_t max_iters, const char* af1, const char* af2)
{
    std::vector<Result> test_NN{};
    Result temp{0};
    test_NN = testNeuralNets(dataset,hidden_neurons);
    for (size_t i = 0; i < test_NN.size(); i++)
    {
        
        if (temp.getTestLoss() > test_NN[i].getTestLoss())
            temp = test_NN[i].getTestLoss();
        else
            return temp;  
    }
    return temp;
}


void estimateFunction(const char* filename, size_t hidden_neurons_no)
{
    Dataset dataset{};
    dataset = loadFuncDataset(filename);
    NeuralNet nn_estimation(dataset, hidden_neurons_no);
    Result estimate{};
    estimate = nn_estimation.fit();
    Matrix input_test{};
    input_test = dataset.getInputs();
    Matrix estimated{};
    estimated = nn_estimation.forwardPropagate(input_test);
    
    
    //show the estimated result of test samples:
    std::cout << std::left << std::setw(6) << "";
    std::cout << std::left << std::setw(20) << "No";
    std::cout << std::left << std::setw(20) << "Target";
    std::cout << std::left << std::setw(14) << "Estimated";
    std::cout << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    for (size_t i = 0; i < dataset.getNoOfSamples(); i++)       //tedade sotoon haye matrix e test inputs
    {
        
        std::cout << std::left << std::setw(20) << i+1;   //cout No if samples
        for (size_t j = 0; j < dataset.getInputs().getSize()[0]; j++)
        {
            //cout Targets of sample data
            std::cout << std::left << std::setw(20) << dataset.getTargets().getMatrixData()[j][i];
            //cout estimated from Neural Network
            std::cout << std::left << std::setw(20) << estimated[j][i];
        }
        std::cout << std::endl;
    }
}   


