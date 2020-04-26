#include<iostream>
#include <math.h>
#include <string.h>
#include <time.h>
#include "neuralnet.h"
#include "Matrix.h"


//////////////////////////////////////////////////constructors//////////////////////////////////////
NeuralNet::NeuralNet()
{
    std::cout<<"NN default constructor is created"<<std::endl;
}

NeuralNet::NeuralNet(Dataset dataset, size_t hidden_layer_neurons, 
                        const char* f1 , const char* f2, 
                            double lr , size_t max_iters, double min_loss)
{
    
    std::cout<<"NN first constructor is created"<<std::endl;
    this-> dataset = dataset;
    this-> hidden_layer_neurons = hidden_layer_neurons;
    af1 = f1;
    af2 = f2;
    this-> lr = lr;
    this-> max_iters = max_iters;
    this-> min_loss = min_loss;
    
    //LAYER ONE
    Matrix m1(hidden_layer_neurons, dataset.getInputDim());
    w1 = m1; // Weights of layer 1

    Matrix m3(hidden_layer_neurons,1);
    b1 = m3; // Biases of layer 1 //(hidden , 1)

    Matrix m5(hidden_layer_neurons,1);
    a1 = m5; // Output of layer 1(hidden , 1)

    Matrix m7(hidden_layer_neurons,1);
    n1 = m7; // n vector for layer 1

    // Matrix m9(hidden_layer_neurons,1);
    // s1 = m9; // s vector for layer 1()

    //LAYER TWO
    
    Matrix m2(1,hidden_layer_neurons);
    w2 = m2; // Weights of layer 2
    
    Matrix m4(1,1);
    b2 = m4; // Biases of layer 2
    
    Matrix m6(1,1);
    a2 = m6; // Output of layer 2
    
    Matrix m8(1,1);
    n2 = m8; // n vector for layer 2
    
    // Matrix m10(hidden_layer_neurons,1);
    // s2 = m10; // s vector for layer 2    
}

//////////////////////////////////////////////////////functions/////////////////////////////////////
//sigmoid as an activation function
Matrix NeuralNet::sigmoid(Matrix& m)
{
    //std::cout << "sigmoid function is created"<<std::endl;
    Matrix sig(m.getSize()[0] , m.getSize()[1] , true);
    std::vector<std::vector<double>> d;
    for( size_t i = 0; i < m.getSize()[0]; i++ ) 
    {
        for (size_t j = 0; j < m.getSize()[1]; j++)
        {
           sig[i][j] = 1 / (1 + exp(- m[i][j]));
        }
    }
    
    return sig;
}
// Matrix NeuralNet::sigmoid_derivative(Matrix& m)
// {
//     Matrix sig_d(m.getSize()[0] , m.getSize()[1] , false);
//     for( size_t i = 0; i < m.getSize()[0]; i++ ) 
//     {
//         for (size_t j = 0; j < m.getSize()[1]; j++)
//         {
//             sig_d[i][j] = m[i][j] / (1 - m[i][j]);
//         }
//     }
//     return sig_d;

// }
double NeuralNet::sigmoid_derivative(double d)
{
    double sig{};
    sig = d/(1-d);
    return sig;
}


//linear as an activation function
Matrix NeuralNet::linear(Matrix& m)
{
    Matrix lin(m.getSize()[0] , m.getSize()[1] , true);
    for( size_t i = 0; i < m.getSize()[0]; i++ ) 
    {
        for (size_t j = 0; j < m.getSize()[1]; j++)
        {
           lin[i][j] = m[i][j];
        }
    }
    return lin;
}
// Matrix NeuralNet::linear_derivative(Matrix& m)
// {
//     Matrix lin_d(m.getSize()[0] , m.getSize()[1] , false);
//     for( size_t i = 0; i < m.getSize()[0]; i++ ) 
//     {
//         for (size_t j = 0; j < m.getSize()[1]; j++)
//         {

//             lin_d[i][j] = 1;
//         }
//     }
//     return lin_d;
// }
//forward propagation : this function gets input data in size of 1*inputdim => in this project: 1*1
Matrix NeuralNet::forwardPropagate(Matrix& input)
{
    //std::cout<<"forward propagate function is created"<<std::endl;
    
    const char* s1{"Sigmoid"};
    const char* s2{"Linear"};



    int af1_sig{strcmp(af1 , s1)};
    int af1_lin{strcmp(af1 , s2)};

    int af2_sig{strcmp(af2 , s1)};
    int af2_lin{strcmp(af2 , s2)};
    

    n1 = w1 * input + b1;       //before activation functions, so this is the same for all
    if ((af1_sig==0) && (af2_sig==0))
    {
        a1 = sigmoid(n1);
        n2 = w2 * a1 + b2;
        a2 = sigmoid(n2);
        return a2;
    }
    else if ((af1_sig==0) && (af2_lin==0))
    {
        a1 = sigmoid(n1);
        n2 = w2 * a1 + b2;
        a2 = linear(n2);
        return a2;
    }

    else if ((af1_lin==0) && (af2_sig==0))
    {
        a1 = linear(n1);
        n2 = w2 * a1 + b2;
        a2 = sigmoid(n2);
        return a2;
    }

    else if ((af1_lin==0) && (af2_lin==0))
    {
        a1 = linear(n1);
        n2 = w2 * a1 + b2;
        a2 = linear(n2);
        return a2;
    }
    return a2;
}    
 
    
    


/*
    //layer one
    if(strcmp(af1 , s1) == 0){
        std::cout<<"a1 of linear af1: "<<std::endl;
        a1 = linear(n1) ;
        a1.show();
    }
    else if (strcmp(af1 , s2) == 0){
        std::cout<<"a1 of sigmoid af1: "<<std::endl;
        a1 = sigmoid(n1);
        a1.show();
        std::cout<< a1.getSize()[0]<<" * "<< a1.getSize()[1] <<std::endl;}
    //layer two
    n2 = w2 * a1 + b2;      //it has two problems here: n2 sabet 3 mishe p a2 sabet 1
    std::cout<<"a2 is strating: "<<std::endl;
    std::cout<<"n2: "<<std::endl;
    n2.show();
    if(strcmp(af2 ,s1) == 0){
        std::cout<<"linear af2"<<std::endl;
        a2 = linear(n2);
        }
    else if (strcmp(af2 , s2) == 0){
        std::cout<<"sigmoid af2"<<std::endl;
        a2 = sigmoid(n2);
        }
    return a2;
    */


//Backpropagation
void NeuralNet::backPropagate(Matrix& input, Matrix& target)
{
    // std::cout<<"back propagate is starting: "<<std::endl;
    //F_derivative_n1 
    Matrix F1_derivate{hidden_layer_neurons,hidden_layer_neurons,false};
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if(i == j)
            {
                if(strcmp(af1 , "Linear") == 0)
                {
                    F1_derivate[i][j] = 1;
                }
                else if(strcmp(af1 , "Sigmoid") == 0)
                {
                    F1_derivate[i][j] = sigmoid_derivative(n1[i][j]);
                }
            }
        }
    }
    //F_derivative_n2
    Matrix F2_derivate{1,1,false};
    //std::cout<< "is problem here?  "<<std::endl;
    if(strcmp(af2 , "Linear") == 0)
    {
        F2_derivate[0][0] = 1;
    }
    
    else if(strcmp(af2 , "Sigmoid") == 0)
    {
        F2_derivate[0][0] = sigmoid_derivative(n2[0][0]);
    }
    //s2 is creating:
    s2 = (F2_derivate) * (target - a2) * (-2);   
    s1 = (F1_derivate) * (w2.T()) * s2;     //f1_f must be 2*2 ghotri ba ghotre mohasebe shode o baghie sefr -> (2*2) * (2*1) * (1*1) = (2*1)
    
    //updating weights:
    w1 = w1 - (s1 * input.T() * lr);
    w2 = w2 - (s2 * a1.T() * lr);

    //updating biases:
    b1 = b1 - (s1 * lr);
    b2 = b2 - (s2 *lr);
}

//first train loss:

double NeuralNet::trainLoss()
{
    double loss{};
    for (size_t i = 0; i < dataset.getNoOfTrainSamples(); i++) // in chera hezar taEe?
    {
        Matrix a(1,1);
        a[0][0] = dataset.getTrainInputs().getMatrixData()[0][i];
        //std::cout<<std::endl;
        // std::cout<< "a[0][i]:  " << a[0][i] <<"    forwardPropagate(a)[0][0]     "<< forwardPropagate(a)[0][0] <<
        //                      "   " << "train targets: "<< dataset.getTrainTargets()[0][i]<<std::endl;
        loss += pow(forwardPropagate(a)[0][0] - dataset.getTrainTargets()[0][i], 2);  
            //std::cout<<std::endl;
           // std::cout<< i <<" th train loss is " << loss <<std::endl;
    }
    size_t m{dataset.getNoOfTrainSamples()};
    //std::cout<< "mean of train loss: " <<loss/m<<std::endl;
    return loss/m;
    
}

//first test loss:
double NeuralNet::testLoss()
{
    
    double loss{};
    for (size_t i = 0; i < dataset.getNoOfTestSamples(); i++) // in chera hezar taEe?
    {
        Matrix a(1,1);
        a[0][0] = dataset.getTestInputs().getMatrixData()[0][i];
        //std::cout<<std::endl;
        // std::cout<< "a[0][i]:  " << a[0][i] <<"    forwardPropagate(a)[0][0]     "<< forwardPropagate(a)[0][0] <<
        //                      "   " << "train targets: "<< dataset.getTrainTargets()[0][i]<<std::endl;
        loss += pow(forwardPropagate(a)[0][0] - dataset.getTestTargets()[0][i], 2);  
            //std::cout<<std::endl;
            
    }
    
    size_t m{dataset.getNoOfTestSamples()};
    return loss/m;
    
}

/*
double NeuralNet::trainLoss()
{
    std::cout<<"train Loss function is starting!" <<std::endl;
    double loss{};
    size_t m = dataset.getTrainInputs().getSize()[1];
    Matrix inp{dataset.getTrainInputs(). T()};
    Matrix fw_propagate{inp};
    for (size_t i = 0; i < inp.getSize()[0]; i++)
    {
        Matrix temp1{1,1};
        Matrix temp2{1,1};
        temp1[0][0] = inp[i][0];
        temp2 = this -> forwardPropagate(temp1);
        fw_propagate[i][0] = temp2[0][0];
    }
    Matrix l{(dataset.getTrainTargets(). T() - fw_propagate)};
    for (size_t i = 0; i < m; i++)
    {
        loss += l[i][0];
        std::cout<< i <<" th train loss is " << loss <<std::endl;
    }
    return loss/m;  
}

double NeuralNet::testLoss()
{
    double loss{};
    size_t m = dataset.getTestInputs().getSize()[1];
    Matrix inp{dataset.getTestInputs(). T()};
    Matrix fw_propagate{inp};
    for (size_t i = 0; i < inp.getSize()[0]; i++)
    {
        Matrix temp1{1,1};
        Matrix temp2{1,1};
        temp1[0][0] = inp[i][0];
        temp2 = this -> forwardPropagate(temp1);
        fw_propagate[i][0] = temp2[0][0];
    }
    Matrix l{(dataset.getTestTargets(). T() - fw_propagate)};
    for (size_t i = 0; i < m; i++)
    {
        loss += l[i][0];
    }
    return loss/m;  
}
*/
/*
//first fit function: 
Result NeuralNet::fit()
{
    std::cout<<"fit function in NN class is created"<<std::endl;
    Result r{};
    double loss_train{};
    double loss_test{};
    
    for (size_t i = 0; i < max_iters; i++)
    {
        Matrix input{dataset.getInputs()};
        Matrix Train_target{dataset.getTrainTargets()};
        Matrix Train_input{dataset.getTrainInputs()};
        Matrix shuffled_Train_input {Train_target.randShuffle_twoSameOrderMatrix(Train_input)};       //train input that shoufled

        Matrix Train_sample{shuffled_Train_input.col(i)};
        Matrix fw_propagate{};
        fw_propagate = forwardPropagate(Train_sample);

        Matrix targets{Train_target.col(i)};    

        backPropagate(fw_propagate , targets); 
        loss_train = this -> trainLoss();

        if(abs(loss_train) < min_loss )
        break;
    }
    loss_train = this-> trainLoss();
    loss_test = this -> testLoss();
    Result R{loss_train,loss_test,2};
    return R;
}*/

//second fit function wuth rand
Result NeuralNet::fit()
{
    //std::cout<<"fit function is created"<<std::endl;
    size_t random{};
    double loss_train{}, loss_test{};
    Matrix random_input{1,1} , random_output{1,1};      //because forward and back propagate get the 1*1 Matrix in each iteration  
    size_t number_of_train_sample{dataset.getTrainInputs().getSize()[1]};       //number of train samples

    srand((unsigned)time(0));
    for (size_t i = 0; i < max_iters; i++)
    {
        random = (rand() % number_of_train_sample) + 1;
        random_input[0][0] = dataset.getTrainInputs()[0][random];       //pick the random sample of train set 
        random_output[0][0] = dataset.getTrainTargets()[0][random];     //pick the target of random input 

        //produce the forward propagate of random input as a output
        Matrix fw_propagate{};
        fw_propagate = forwardPropagate(random_input);   
        
        backPropagate(fw_propagate , random_output); 
    
        loss_train = this -> trainLoss();

        if(abs(loss_train) < min_loss )
        break; 
    }
    loss_test = this -> testLoss();
    Result R{loss_train,loss_test,hidden_layer_neurons};
    return R;

}


//show the neural Network features
void NeuralNet::show()
{
    std::cout<<"Neural Network: "<<std::endl;
    std::cout<<"\t"<< "No of hidden neurons: "<<hidden_layer_neurons<<std::endl;
    std::cout<<"\t"<< "Input dimension: "<<dataset.getInputDim()<<std::endl;
    std::cout<<"\t"<< "Output dimension: "<<dataset.getTargetDim()<<std::endl;
    std::cout<<"\t"<< "Layer 1 activation function: "<<af1<<std::endl;
    std::cout<<"\t"<< "Layer 2 activation function: "<<af2<<std::endl;
}
//setters:
void NeuralNet::setW1(Matrix& w)
{
    w1 = w;
}
void NeuralNet::setW2(Matrix& w)
{
    w2 = w;
}
void NeuralNet::setB1(Matrix& b)
{
    b1 = b;
}
void NeuralNet::setB2(Matrix& b)
{
    b2 = b;
}

//getters
Matrix NeuralNet::getW1()
{
    return w1;
}
Matrix NeuralNet::getW2()
{
    return w2;
}
Matrix NeuralNet::getB1()
{
    return b1;
}
Matrix NeuralNet::getB2()
{
    return b2;
}

//overloading of << operator as a friend function of class
std::ostream &operator<<(std::ostream &os, const NeuralNet &nn)
{ 
    os <<"Neural Network: ***** "<< std::endl;
    os <<"\t" <<"No of hidden neurons: " <<nn.hidden_layer_neurons<< std::endl;
    os << "\t" << "Input dimension: " <<nn.dataset.getInputDim()<< std::endl;
    os <<  "\t" <<"Output dimension: " <<nn.dataset.getTargetDim()<< std::endl;
    os << "\t" <<"Layer 1 activation function: " <<nn.af1<< std::endl;
    os << "\t" << "Layer 2 activation function: "<<nn.af2<< std::endl;
    return os;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

