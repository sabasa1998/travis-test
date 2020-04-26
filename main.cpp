#include <iostream>
#include "Matrix.h"
#include "dataset.h"
#include"neuralnet.h"
#include "result.h"
#include "aphw3.h"



int main()
{
    
    std::cout<< "hello world"<<std::endl;
    //std::vector<std::vector<double>> data1, data2;
    // std::vector<double> a1{7,8,9,10,11,12};
    // std::vector<double> a2{7,8,9,10,11,12};
    // std::vector<double> a3{7,8,9,10,11,12};
    // std::vector<double> b1{1,2,3,4,5,6};
    // std::vector<double> b2{1,2,3,4,5,6};
    // data1.push_back(a1);
    // data1.push_back(a2);
    // data1.push_back(a3);
    // data2.push_back(b1);
    // data2.push_back(b2);
    
    // std::vector<std::vector<double>> data1 {{33,56,12,3}, {34,56,7,2},{23,3,5,54}, {5,8,98,70}};
    // std::vector<std::vector<double>> data2 {{33,56,12,3}, {34,56,7,2},{23,3,5,54},{67,43,2,4}};
    // Matrix m1{data1};
    // Matrix m2{data2};
    // m1.show();

    
    // 
    
    // //ds.shuffle();
    // NeuralNet nn{ds, 2};
  
    // Matrix w1{2, 1}, w2{1, 2}, b1{2, 1}, b2{1, 1};
    // b1[0][0] = -.48;
    // b1[1][0] = -0.13;
    // w1[0][0] = -.27;
    // w1[1][0] = -0.41;
    // b2[0][0] = 0.48;
    // w2[0][0] = 0.09;
    // w2[0][1] = -0.17;
    // nn.setW1(w1);
    // nn.setW2(w2);
    // nn.setB1(b1);
    // nn.setB2(b2);
    
    // std::cout<< " fit is calling:  "<< std::endl;
    // Result r{nn.fit()};
    // std::cout<< " fit is ending:  "<<std::endl;
    // std::cout<<"are you here? "<<std::endl;
    // char buf[] = "APHW3Data1.csv";
    // Dataset ds{loadFuncDataset("APHW3Data1.csv")};
    // std::cout<< ds.getNoOfSamples() <<"     "<<ds.getInputs().getSize()[0] <<"  *  "<< ds.getInputs().getSize()[1]<<std::endl;
    // std::cout<< ds.getNoOfSamples() <<"     "<<ds.getTargets().getSize()[0] <<"  *  "<< ds.getTargets().getSize()[1]<<std::endl;

   /*
    Result r1{6.23};
    Result r2{6.23};
    if(r1 >= r2)
        std::cout<<"test loss of*** r1 is smaller than r2's"<<std::endl;
    else
        std::cout<<"test loss of r1 is larger than r2's"<<std::endl;


    std::cout<< (r1 < r2) << std::endl;
    Result r3{15};
    if (r3<10)
        std::cout<<"Hi there!"<<std::endl;
    //std::cout<< result_A >= result_B << std::endl;

    */

    // Result r1{15};
    // if (r1>10)
    //     std::cout<<"Hi there!"<<std::endl;
     char buf[] = "APHW3Data1.csv";
     Dataset ds{loadFuncDataset("APHW3Data1.csv")};
    // std::cout<< ds.getInputDim() << std::endl;
    ds.show();
    // std::cout<<"**************"<< ds <<std::endl;

   

    return 0;
}