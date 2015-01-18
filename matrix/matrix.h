#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
//矩阵类
class Matrix
{
public:
    double * p;
    //矩阵宽度
    int width;
    //矩阵高度
    int height;
public:
    int getHeight() const;
    int getWidth() const;
    bool isVector() const;//如果是false，那就是一个数
    double Arg() const;//求行列式
    bool isPtv();//是否正定
    Matrix  T();//转置
    Matrix subMatrix(int offset);
    void Test();//测试函数
    /***********重载部分-Overloaded Part*****************/
    Matrix operator+(const Matrix &) const;
    Matrix operator-(const Matrix &) const;
    Matrix operator*(const Matrix &) const;
    friend Matrix operator*(double alpha,const Matrix &);//实数与矩阵相乘
    Matrix operator*(double alpha) const;//矩阵与实数相乘
    Matrix operator/(Matrix &);//实际是实数相除或矩阵和实数相除
    Matrix operator/(double sub) const ;
    Matrix operator+=(Matrix &);
    Matrix operator-=(Matrix &);
    Matrix operator*=(double alpha);//矩阵与实数相乘
    friend Matrix  sqrt(Matrix m);//开方
    friend double abs(Matrix &);//取绝对值
    Matrix& operator=(Matrix m);
    double * operator[](int heightPos);//用于实现用[][]操作矩阵元素
    const double * operator[](int heightPos) const;//用于实现用[][]操作矩阵元素
    friend ostream & operator<<(ostream &,Matrix &) ;
    Matrix(void);//default constructor
    Matrix(int n);//单位矩阵
    Matrix(int arrWidth,int arrHeight);//构造一维矩阵
    Matrix(const double * arrAddress,int arrWidth,int arrHeight);
    Matrix(const Matrix &);//copy constructor
    ~Matrix(void);//default destructor
    /***********重载部分-Overloaded Part*****************/
};

#endif // MATRIX_H