#include <iostream>
#include <array>
#include <vector>
#include <iomanip>
#include <fstream>
#include <math.h>
#include"Matrix.h"


Matrix::Matrix() : Matrix(0,0,false)
{
    //std::cout<< "matrix: default constructor is created" << std::endl;
    
}

Matrix::Matrix(const Matrix& mat) : size{mat.size}, data{mat.data} 
{
    //std::cout<< "matrix: copy constructor is created" << std::endl;
}

Matrix::Matrix(std::vector<std::vector<double>> data)
{   
    //std::cout<< "matrix: vector to vector constructor is created" << std::endl;
    this->data = data;
    size[0] = data.size(); // row number 
    size[1] =data[0].size(); //col number

}

Matrix::Matrix(size_t m, size_t n,bool ones)  //hanuz tamum nashode
{
    size[0] = m;
    size[1] = n;
    //std::cout<<"boolian matrix is created"<<std::endl;
    //bool ones{true}; 
    if (ones) 
    {
        for (size_t i = 0; i < size[0]; i++)
        {
           data.push_back(std::vector<double>(size[1], 1));
        } 
    }
    else
    {
        for (size_t i = 0; i < size[0]; i++)
        {
           data.push_back(std::vector<double>(size[1], 0));
        } 
    }
}

Matrix::~Matrix()
{

}
/////////////////////////////////////////////functions//////////////////////////////////////////////

/* getSize function*/
std::array<size_t , 2> Matrix::getSize() const
{
    return size;
}

/*determinant of Matrix*/
double Matrix::det()
{
    if (!(size[0] - size[1] == 0))
    {
        std::cout << " Your matrix is not in the square form! " << std::endl;
        return 0;
    }

    if (!(size[0] - 1))
        return data[0][0];

    double Det{0};
    Matrix new_matrix = this->delRow(0);
    for (size_t c = 0; c < size[1]; c++)
    {
        Matrix matrix_prime = new_matrix.delCol(c);
        if (c % 2)
            Det += (-1) * (data[0][c]) * matrix_prime.det();
        else
            Det += (data[0][c]) * matrix_prime.det();
    }
    return Det;
};

/*Matrix inverse*/
Matrix Matrix::inv()
{
    if (!(size[0] - size[1] == 0))
    {
        std::cout << " Your matrix is not in the square form! " << std::endl;
        return Matrix(size[0], size[1], false);
    }
    double Det{this->det()};
    std::vector<std::vector<double>> new_data(size[0], std::vector<double>(size[1], 0));
    for (size_t r = 0; r < size[0]; r++)
    {
        for (size_t c = 0; c < size[1]; c++)
        {
            Matrix mat = this->delCol(c);
            mat = mat.delRow(r);
            new_data[r][c] = pow(-1, r + c)*(mat.det()) /Det;
        }
    }
    return Matrix(new_data).T();
};

/*deleting an special column in Matrix object*/
Matrix Matrix::delCol(size_t i)
{
    std::vector<std::vector<double>> new_data(size[0], std::vector<double>(size[1] - 1, 0));
    for (size_t r = 0; r < size[0]; r++)
    {
        for (size_t c = 0; c < size[1] - 1; c++)
        {
            if (c < i)
                new_data[r][c] = data[r][c];
            else
                new_data[r][c] = data[r][c + 1];
        }
    }

    Matrix mat(new_data);
    return mat;
};

/*deleting an special row in Matrix object*/
Matrix Matrix::delRow(size_t j)
{
    std::vector<std::vector<double>> new_data(size[0] - 1, std::vector<double>(size[1], 0));
    for (size_t r = 0; r < size[0] - 1; r++)
    {
        for (size_t c = 0; c < size[1]; c++)
        {
            if (r < j)
                new_data[r][c] = data[r][c];
            else
                new_data[r][c] = data[r + 1][c];
        }
    }

    Matrix mat(new_data);
    return mat;
};

Matrix Matrix::col(size_t i)
{
    std::vector<std::vector<double>> new_data(size[0], std::vector<double>(1,0));
    for (size_t r = 0; r < size[0]; r++)
    {
        new_data[r][0] = data[r][i]; 
    }
    Matrix mat(new_data);
    return mat;
};

/* Matrix Transpose*/
Matrix Matrix::T()
{
    std::vector<std::vector<double>> new_data{size[1], std::vector<double>(size[0], 0)};
    for (size_t r = 0; r < size[1]; r++)
    {
        for (size_t c = 0; c < size[0]; c++)
        {
            new_data[r][c] = data[c][r];
        }
    }
    return Matrix(new_data);
};

/* save the matrix as a csv file*/
void Matrix::save(const char *name)
{
    std::string fileType{".csv"};
    std::string fileName{name + fileType};
    std::ofstream out(fileName);
    size_t rowsCounter{0}, colsCounter{0};
    for (auto &row : data)
    {
        for (auto col : row)
            if (col - data[rowsCounter][size[1] - 1])
            {
                out << col << ',';
                colsCounter++;
            }
            else
            {
                out << col;
                colsCounter = 0;
            }
        out << '\n';
        rowsCounter++;
    }
};

/* load the dataset*/
void Matrix::load(const char *fileName)
{
    std::ifstream file{fileName};
    if (file.is_open())
        std::cout << " OK! " << std::endl;

    std::string line;
    std::string item;
    std::vector<std::vector<double>> dataset;
    while (getline(file, line))
    {
        std::vector<double> LineItems;
        std::stringstream ss(line);
        while (ss)
        {
            getline(ss, item, ',');
            LineItems.push_back(stod(item));
        }
        LineItems.pop_back();
        dataset.push_back(LineItems);
    }
    file.close();
    data = dataset;
    size = {dataset.size(), dataset[0].size()};
};

/* show matrices */
void Matrix::show()
{
    std::cout<< "Matrix: "<< std::endl;
    for (size_t i = 0; i < size[0]; i++)
    {
        for (size_t j = 0; j < size[1]; j++)
        {
            std::cout<<std::setw(12)<< data[i][j];
        }
        std::cout<< std::endl<<std::endl<< std::endl;
    }
    
}

/* To access data of a matrix*/
std::vector<std::vector<double>> Matrix::getMatrixData() const
{
    return data;
}

//shuffle a simple Matrix by column
Matrix Matrix::randShuffle_byColumn() 
{
    srand(time(NULL));
    std::vector<std::vector<double>> Data{data};
    std::vector<size_t> Columns;
    for (size_t i = 0; i < size[1]; i++)
       Columns.push_back(0);
    int r{}, counter{};

    for (size_t i = 0; i < size[1]; i++)
    {
        r = rand()%size[1];
        if( Columns[r] )        //it shows that this column is empty and wants to be filled
        {
            while( Columns[r] )
                r = rand()%size[1];
        }
        if( !Columns[r] )       //columns[r] = 1 it means r th column is filled and we should make another random variable
        {
            Columns[r] = 1;
            for (size_t i = 0; i < size[0]; i++)
                Data[i][counter] = data[i][r];
            counter++;
        } 
    }
    data = Data;
    return Matrix(data);
}

//shuffles two matrices with the same order
Matrix Matrix::randShuffle_twoSameOrderMatrix(Matrix m) 
{
    //number of columns should be equal.
    srand(time(NULL));
    std::vector<std::vector<double>> Data{data};
    std::vector<std::vector<double>> Data2{m.data};
    std::vector<size_t> Columns;
    for (size_t i = 0; i < size[1]; i++)
       Columns.push_back(0);
    int r{}, counter{};

    for (size_t i = 0; i < size[1]; i++)
    {
        r = rand()%size[1];
        if( Columns[r] )
        {
            while( Columns[r] )
                r = rand()%size[1];
        }
        if( !Columns[r] )
        {
            Columns[r] = 1;
            for (size_t i = 0; i < size[0]; i++)
                Data[i][counter] = data[i][r];
            for (size_t i = 0; i < m.size[0]; i++)
                Data2[i][counter] = m.data[i][r];
            
            counter++;
        } 
    }
    data = Data;
    return Matrix{Data2};
}
///////////////////////////////////////operators/////////////////////////////////////

//summation 
Matrix Matrix::operator+(const Matrix &m)                
{
    //std::cout<<"+ operator is created"<<std::endl;
    std::vector<std::vector<double>> v;
    std::array<size_t, 2> s;
    s = m.size;
    v = m.data;
    Matrix summation{size[0], size[1], false};   
    if (s[0] == size[0])                                //if dimensions are equal
    {
        for(size_t i{}; i<size[0]; i++){
            for(size_t j{}; j<size[1]; j++)  
            {
                summation.data[i][j] = data[i][j] + v[i][j] ;  
            }
        }
    }
    else
    {
        std::cout<< "Dimensions are not equal in summation " << std::endl;
    }
  return summation;
}

//subtraction
Matrix Matrix::operator-(const Matrix &m)                    
{
    //std::cout<<"- operator is created"<<std::endl;
    std::vector<std::vector<double>> v;
    std::array<size_t, 2> s;
    s = m.size;
    v = m.data;
    Matrix subtraction{size[0], size[1], false};   
    if (s[0] == size[0]) 
    {
        for(size_t i{}; i<size[0]; i++){ 
            for(size_t j{}; j<size[1]; j++)  
            {
                subtraction.data[i][j] = data[i][j] - v[i][j] ; 
            }
        }
    }
    else
    {
        std::cout<< "Dimensions are not equal in subtraction" << std::endl;
    }
  return subtraction;
}

//multipication
Matrix Matrix::operator*(Matrix m)                    
{
    //std::cout<<"* operator is created"<<std::endl;
    std::vector<std::vector<double>> v; 
    std::array<size_t, 2> s;
    s = m.size;
    v = m.data;
    Matrix multipication{data.size(), s[1], false};
    if(data[0].size() == s[0]) {
        for(size_t k{}; k < data.size(); k++) 
        {
            for(size_t i{}; i<s[1]; i++) 
            {
                double temp{0.0}; 
                for(size_t j{}; j<data[0].size(); j++)   
                {
                    temp += data[k][j] * v[j][i]  ;  
                }
                multipication.data[k][i] = temp; 
            }
        }
    }
    else
    {
        std::cout<< "Dimensions are not equal in multipication"<<std::endl; 
    }
    return multipication; 
}

//[]
std::vector<double>& Matrix::operator[](size_t i){
    //std::cout<<"[] operator is created"<<std::endl;
    return data[i];
}

//multipication with double
Matrix Matrix::operator * (double d)
{
   // std::cout<<"* integer operator is created"<<std::endl;
    std::vector<std::vector<double>> Data;   
    for (size_t i = 0; i < size[0]; i++)
    {
        std::vector<double> temp;
        for (size_t j = 0; j < size[1]; j++)
            temp.push_back(data[i][j] * d);
        Data.push_back(temp); 
    }
    return Matrix(Data);
    
}

//=
// Matrix Matrix::operator=(Matrix const &obj)
// {
//     size = obj.size;
//     data = obj.data;
// }