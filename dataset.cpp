#include <iostream>
#include <ostream>
#include <iomanip>
#include <cmath>
#include "dataset.h"

Dataset::Dataset()
{
    std::cout<< "dataset: default Dataset constructor is created"<<std::endl;
    percentage = 0;
    no_of_samples = 0;
    input_dim = 0;
    target_dim = 0;
}

Dataset::Dataset(Matrix inputs, Matrix targets, double percentage)
{
    std::cout<<"first constructor is created"<<std::endl;
    this-> inputs = inputs;
    this-> targets = targets;
    this-> percentage = percentage;

    //train_inputs
    std::vector<std::vector<double>> data_input;
    for (size_t i = 0; i <inputs.getSize()[0]; i++)
    {
        std::vector<double> temp;
        for (size_t j = 0; j <ceil(inputs.getSize()[1] * (percentage/100)) ; j++)
        {
            temp.push_back(inputs.getMatrixData()[i][j]);
            
        }
        data_input.push_back(temp);
    }
    
    Matrix m1{data_input};
    train_inputs = m1;
    
    //train targets
    std::vector<std::vector<double>> data2;
    for (size_t i = 0; i <targets.getSize()[0]; i++)
    {   
        std::vector<double> temp;
        for (size_t j = 0; j <ceil(targets.getSize()[1] *(percentage/100)) ; j++)
        {
            temp.push_back(targets.getMatrixData()[i][j]);
        }
        data2.push_back(temp);
    }
    Matrix m2{data2};
    train_targets = m2;

    //test inputs
    std::vector<std::vector<double>> data3;
    for (size_t i = 0; i <inputs.getSize()[0]; i++)
    {
        std::vector<double> temp;
        for (size_t j = ceil(inputs.getSize()[1] * (percentage/100)); j <inputs.getSize()[1] ; j++)
        {
            temp.push_back(inputs.getMatrixData()[i][j]);
        }
        data3.push_back(temp);
    }
    Matrix m3{data3};
    test_inputs = m3;

   //test targets
   std::vector<std::vector<double>> data4;
    for (size_t i = 0; i <targets.getSize()[0]; i++)
    {
        std::vector<double> temp;
        for (size_t j = ceil(targets.getSize()[1] *(percentage/100)); j <targets.getSize()[1] ; j++)
        {
            temp.push_back(targets.getMatrixData()[i][j]);
        }
        data4.push_back(temp);
        
    }
    Matrix m4{data4};
    test_targets = m4;

    no_of_samples = inputs.getSize()[1];
    input_dim = inputs.getSize()[0];     //number of rows in inputs matrix
    target_dim = targets.getSize()[0];   //number of rows in targets matrix
}

Dataset::Dataset(Matrix inputs, Matrix targets, Matrix train_inputs, Matrix train_targets, Matrix test_inputs, Matrix test_targets)
{
    this->inputs = inputs;
    this->targets = targets;
    this->train_inputs = train_inputs;
    this->train_targets = train_targets;
    this->test_inputs = test_inputs;
    this->test_targets = test_targets;
    no_of_samples = inputs.getSize()[1];
    input_dim = inputs.getSize()[0];     //number of rows in inputs matrix
    target_dim = targets.getSize()[0];   //number of rows in targets matrix      
   
}

//////////////////////////////////////////////functions//////////////////////////////////////////////////

size_t Dataset::getNoOfSamples()
{
    return no_of_samples;
}
size_t Dataset::getNoOfTrainSamples() const
{
    std::array<size_t, 2> getNoOfTrainSamples{train_inputs.getSize()};
    return getNoOfTrainSamples[1];

    // std::array<size_t , 2> train_inputs_size = train_inputs.getSize();
    // return train_inputs_size[1];
}

size_t Dataset::getNoOfTestSamples() const
{
    size_t getNoOfTestSamples = no_of_samples - getNoOfTrainSamples();
    return getNoOfTestSamples;

    // std::array<size_t , 2> test_inputs_size = test_inputs.getSize();
    // return test_inputs_size[1];
}
size_t Dataset::getInputDim() const
{
    return input_dim;
}
size_t Dataset::getTargetDim() const
{
    return target_dim;
}

Matrix Dataset::getInputs()
{
    return inputs;
}
Matrix Dataset::getTargets()
{
    return targets;
}
Matrix  Dataset::getTrainInputs()
{
    return train_inputs;
}
Matrix  Dataset::getTrainTargets()
{
    return train_targets;
}
Matrix  Dataset::getTestInputs()
{
    return test_inputs;
}
Matrix  Dataset::getTestTargets()
{
    return test_targets;
}
/*
void Dataset::shuffle()
{
    srand(time(NULL));
    
    std::vector<std::vector<double>> shuffle;
    
    for (size_t c = 0; c < inputs.getSize()[1]; c++)
    {   
        int column{rand()% inputs.getSize()[1]};        //be tedade sotoon haE ke matrix e ma dare
        int empty[no_of_samples] {column};
        if(column == empty[c])
        {
            std::vector<double> temp;
            for (size_t r = 0; r < inputs.getSize()[0]; r++)
            {
                temp.push_back(inputs.getMatrixData()[r][column]);
            }
            shuffle.push_back(temp);       
        }  
        else
        {
            column = rand()% inputs.getSize()[1];  
            std::vector<double> temp;
            for (size_t r = 0; r < inputs.getSize()[0]; r++)
            {
                temp.push_back(inputs.getMatrixData()[r][column]);
            }
            shuffle.push_back(temp);   
        }
    }
    Matrix m{shuffle};
    inputs = m.T();
    inputs.show();
}*/


//shuffle dataset=> both of input and target matrices with the same order
void Dataset::shuffle()
{
    inputs.randShuffle_byColumn();
    targets.randShuffle_byColumn();
    train_inputs.randShuffle_byColumn();
    train_targets.randShuffle_byColumn();
    test_inputs.randShuffle_byColumn();
    test_targets.randShuffle_byColumn();
}

void Dataset::show()
{
    std::cout<<"Dataset: "<<std::endl;
    std::cout<<"\t"<< "Number of samples: "<<no_of_samples<<std::endl;
    std::cout<<"\t"<< "Train samples: "<< getNoOfTrainSamples()<<std::endl;
    std::cout<<"\t"<< "Test samples: "<<getNoOfTestSamples()<<std::endl;
    std::cout<<"\t"<< "Input dimensions: "<<getInputDim()<<std::endl;
    std::cout<<"\t"<< "Target dimensions: "<<getTargetDim()<<std::endl;
}

////////////////////////////////////////operators////////////////////////////////////////////////////////

// Dataset Dataset::operator=(const Dataset& d)
// {
//     std::cout << " operator = is created" << std::endl; 
//      inputs = d.inputs;
//     targets = d.targets;
//     percentage = d.percentage;
//     train_inputs = d.train_inputs;
//     train_targets = d.train_targets;
//     test_inputs = d.test_inputs;
//     test_targets = d.test_targets;
//     no_of_samples = d.no_of_samples;
//     input_dim = d.input_dim;
//     target_dim = d.target_dim;
//     return d;
// }


//[]_first 
/*
std::vector<Matrix> Dataset::operator[](size_t i)
{
    //Matrix inp{1,inputs.getSize()};
    //Matrix targ{};
    
    std::vector<Matrix>p {inputs.getMatrixData(), targets.getMatrixData()};
    for (size_t i = 0; i < inputs.getSize()[1]; i++)
    {
       std::vector<Matrix> p2{inputs[0][i], targets[0][i]};
       p2[0][i]= inputs[0][i];
       p2[1][i] = targets[0][i];
       return p;
    }

    
}*/

//[]_second
std::vector<Matrix> Dataset::operator [] (size_t j)
{
    std::vector<Matrix> v;
    std::vector<std::vector<double>> temp1;
    std::vector<std::vector<double>> m1_data;
    std::array<size_t, 2> size;
    size = inputs.getSize();
    m1_data = inputs.getMatrixData();
    for (size_t i = 0; i < size[0]; i++)
    {
        std::vector<double> temp;
        temp.push_back(m1_data[i][j]);
        temp1.push_back(temp);
    } 
    Matrix m1{temp1};
    v.push_back(m1);

    std::vector<std::vector<double>> temp2;
    std::vector<std::vector<double>> m2_data;
    std::array<size_t, 2> Size;
    Size = targets.getSize();
    m2_data = targets.getMatrixData();
    for (size_t i = 0; i < Size[0]; i++)
    {
        std::vector<double> temp;
        temp.push_back(m2_data[i][j]);
        temp2.push_back(temp);
    }
    Matrix m2{temp2};
    v.push_back(m2);
    return v;
}



/* first try
Dataset Dataset::operator+(const Dataset& dataset)
{
    //inputs
    Matrix inp(1,no_of_samples + dataset.no_of_samples , true);
    for (size_t i = 0; i < no_of_samples; i++)
    {   
        
        inp[i][0]= inputs[i][0];
        
    }
    for (size_t i = no_of_samples; i < no_of_samples+dataset.no_of_samples; i++)
    {
        inp[i][0] = dataset.inputs[i][0];
    }


    //targets
    Matrix targ(1,no_of_samples,true);
    for (size_t i = 0; i < no_of_samples; i++)
    {   
        
        targ[i][0]= targets[i][0];
        
    }
    for (size_t i = no_of_samples; i < no_of_samples+dataset.no_of_samples; i++)
    {
        targ[i][0] = dataset.targets[i][0];
    }
     Dataset d(inp,targ,70);
    return d;
    
    

    // Matrix inputs1(m1,n1,true );
    // Matrix targets1(std::vector<std::vector<double>> data2);
    // Dataset d1{inputs1,targets1,70};
    
    // Matrix inputs_new(inputs.getSize()+ inputs1.getSize())

}*/

Dataset Dataset::operator+(const Dataset& dataset)
{
    //creating concatenation of inputs
    std::vector<std::vector<double>> data_input,data_dataset_input,data;
    data_input = inputs.getMatrixData();
    data_dataset_input = dataset.inputs.getMatrixData();

    std::array<size_t, 2> input_size, input_dataset_size;
    input_size = inputs.getSize();
    input_dataset_size = dataset.inputs.getSize();

    for (size_t i = 0; i < input_size[0]; i++)
    {
        std::vector<double> temp;
        for (size_t j = 0; j < input_size[1]; j++)
            temp.push_back(data_input[i][j]);

        for (size_t j = 0; j < input_dataset_size[1]; j++)
            temp.push_back(data_dataset_input[i][j]);
        data.push_back(temp);    
    }
    Matrix Input(data);
    

    //creating concatenation of targets
    std::vector<std::vector<double>> data_input_prime,data_dataset_input_prime,data_prime;

    data_input_prime = targets.getMatrixData();
    data_dataset_input_prime = dataset.targets.getMatrixData();

    std::array<size_t, 2> target_size, target_dataset_size;
    target_size = targets.getSize();
    target_dataset_size = dataset.targets.getSize();

    for (size_t i = 0; i < target_size[0]; i++)
    {
        std::vector<double> temp;
        for (size_t j = 0; j < target_size[1]; j++)
            temp.push_back(data_input_prime[i][j]);
        for (size_t j = 0; j < target_dataset_size[1]; j++)
            temp.push_back(data_dataset_input_prime[i][j]);
        data_prime.push_back(temp);    
    }
    Matrix Target(data_prime);
    
    //now we have to shuffle Input and Target matrices with the same order
    Matrix Random_Input{Input};
    Matrix Random_Target = Random_Input.randShuffle_twoSameOrderMatrix(Target);  
    
    //creating train_inputs
    std::vector<std::vector<double>> Random_Input_Data{Random_Input.getMatrixData()};
    std::vector<std::vector<double>> train_Buffer;
    size_t train_Size = static_cast<size_t> ( ( input_size[1] + input_dataset_size[1] ) * (percentage/100));
    for (size_t i = 0; i < input_size[0]; i++)   
    {
        std::vector<double> temp;
        for (size_t j = 0; j < train_Size; j++)
            temp.push_back(Random_Input_Data[i][j]);
        train_Buffer.push_back(temp);  
    }
    Matrix Train_Input{train_Buffer};
    
    //creating test_inputs
    std::vector<std::vector<double>> test_Buffer;
    for (size_t i = 0; i < input_size[0]; i++)   
    {
        std::vector<double> temp;
        for (size_t j = train_Size; j < ( input_size[1] + input_dataset_size[1] ); j++)
            temp.push_back(Random_Input_Data[i][j]);
        test_Buffer.push_back(temp);  
    }
    Matrix Test_Input{test_Buffer};
    
    //creating train_targets
    std::vector<std::vector<double>> Random_Target_Data{Random_Target.getMatrixData()};
    std::vector<std::vector<double>> train_Buffer_prime;
    size_t trainSize2 = static_cast<size_t> ( ( target_size[1] + target_dataset_size[1] ) * (percentage/100));
    for (size_t i = 0; i < target_size[0]; i++)   
    {
        std::vector<double> temp;
        for (size_t j = 0; j < trainSize2; j++)
            temp.push_back(Random_Target_Data[i][j]);
        train_Buffer_prime.push_back(temp);  
    }
    Matrix Train_Target{train_Buffer_prime};
    
    //creating test_targets
    std::vector<std::vector<double>> test_Buffer_prime;
    for (size_t i = 0; i < target_size[0]; i++)   
    {
        std::vector<double> temp;
        for (size_t j = trainSize2; j < ( target_size[1] + target_dataset_size[1] ); j++)
            temp.push_back(Random_Target_Data[i][j]);
        test_Buffer_prime.push_back(temp);  
    }
    Matrix Test_Target{test_Buffer_prime};
    

    return Dataset(Input, Target, Train_Input, Train_Target, Test_Input, Test_Target);
}

//overloading of << operator as a friend function of class
std::ostream &operator<<(std::ostream &os, const Dataset &d)
{ 
    os <<"Dataset:"<< std::endl;
    os <<"\t" <<"Number of samples: " << d.no_of_samples<< std::endl;
    os << "\t" << "Train samples: " <<d.getNoOfTrainSamples()<< std::endl;
    os <<  "\t" <<"Test samples: " << d.getNoOfTestSamples()<< std::endl;
    os << "\t" << "Input dimensions: " <<d.input_dim<< std::endl;
    os << "\t" << "Target dimensions: "<<d.target_dim<< std::endl;
    return os;
}
