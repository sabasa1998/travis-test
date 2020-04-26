#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <vector>

class Matrix
{
private:
    //const size_t satr{};
    
    std::array<size_t,2> size{};                    //size[0] equal to number of cols and size[1] equal to number of rows
    std::vector<std::vector<double>> data;
    
    
public:
    //constructors:
    Matrix();
    Matrix(const Matrix& mat);                      // Copy constructor
    Matrix(std::vector<std::vector<double>> data);
    Matrix(size_t m, size_t n, bool ones = true); 
    ~Matrix();
    //optional ro nazadam  
    //functions:
    std::array<size_t , 2> getSize() const; 
    double det();                                   // determinant              
    Matrix inv();                                   // inverse the matrix  
    Matrix delCol(size_t);                          // delete an special Column
    Matrix delRow(size_t);                          // delete an speacial Row
    Matrix col(size_t i);                           //return an special column  //sefraE ke barmigardunaro che konam?
    Matrix T();                                     // transpose matrix
    void save(const char *);                        // save the matrix as a csv file
    void load(const char *);                        // load the matrix
    void show();
    std::vector<std::vector<double>> getMatrixData() const;
    Matrix randShuffle_byColumn();
    Matrix randShuffle_twoSameOrderMatrix(Matrix m);
    //operators:
    Matrix operator+(const Matrix &m);            //summation 
    Matrix operator-(const Matrix &m);            //subtraction  
    Matrix operator*(Matrix m);            //multipication
    std::vector<double>& operator[](size_t i);      //[]
    Matrix operator * (double d);
    // Matrix operator=(Matrix const &obj);
};
  

  //get matrix data return
#endif