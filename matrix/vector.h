#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "matrix.h"
#include <math.h>
#include <assert.h>
#include <boost/lambda/lambda.hpp>
#include "../data.h"



class RowVector 
{
    Matrix m;
public: 
    RowVector(int n):m(n,1)
    {}
    RowVector(const std::vector<double>& vec):m(&vec[0], vec.size(),1)
    {}
    explicit RowVector(const Matrix& m1):m(m1)
    {}
    double& operator [](int dim)
    {
        return m[dim][1];
    }
    size_t size() const 
    {
        return m.getWidth();
    }
    const double& operator [](int dim) const
    {
        return m[dim][1];
    }
    RowVector operator*(const Matrix &matrix) const
    {
        RowVector r=(*this);
        r.m = m * matrix;
        return r;
    }
    RowVector operator-(const RowVector r) const
    {
        return RowVector(m-r.m);
    }
    RowVector operator/(double s) const
    {
        return RowVector(m/s);
    }
    friend RowVector sigmoid(const RowVector& r);
    friend RowVector exp(const RowVector& r);
    friend double sum(const RowVector& r);
    friend RowVector softmax(const RowVector& r);
};
RowVector sigmoid(const RowVector& r)
{
    RowVector r1=r;
    for(int i=0;i<r.size();i++)
    {
        r1[i]=sigmoid(r1[i]);
    }
    return r1;    
}
RowVector exp(const RowVector& r)
{
    RowVector r1=r;
    for(int i=0;i<r.size();i++)
    {
        r1[i]=exp(r1[i]);
    }
    return r1;    
}
double sum(const RowVector& r)
{
    int s;
    for(int i=0;i<r.size();i++)
    {
        s+=r[i];
    }
    return s;    
}
RowVector softmax(const RowVector& r)
{
    RowVector r1=exp(r);
    return r1/sum(r1);
}
class ColumnVector
{
    Matrix m;
public: 
    ColumnVector(int n):m(1,n)
    {}
    ColumnVector(const std::vector<double>& vec):m(&vec[0], 1, vec.size())
    {}
    ColumnVector(const Matrix& m1):m(m1)
    {}
    double& operator [](int dim)
    {
        return m[1][dim];
    }
    size_t size() const 
    {
        return m.getHeight();
    }
    ColumnVector operator*(const Matrix &matrix) const
    {
        ColumnVector r=(*this);
        r.m = m * matrix;
        return r;    
    }
    const double& operator [](int dim) const
    {
        return m[1][dim];
    }
    ColumnVector operator-(const ColumnVector &r) const
    {
        return ColumnVector(m-r.m);
    }
    ColumnVector operator/(double s) const
    {
        return ColumnVector(m/s);
    }
    friend ColumnVector sigmoid(const ColumnVector& r);
    friend ColumnVector exp(const ColumnVector& r);
    friend double sum(const ColumnVector& r);
    friend ColumnVector softmax(const ColumnVector& r);
};
ColumnVector sigmoid(const ColumnVector& r)
{
    ColumnVector r1=r;
    for(int i=0;i<r.size();i++)
    {
        r1[i]=sigmoid(r1[i]);
    }
    return r1;    
}
ColumnVector exp(const ColumnVector& r)
{
    ColumnVector r1=r;
    for(int i=0;i<r.size();i++)
    {
        r1[i]=exp(r1[i]);
    }
    return r1;    
}
double sum(const ColumnVector& r)
{
    int s;
    for(int i=0;i<r.size();i++)
    {
        s+=r[i];
    }
    return s;    
}
ColumnVector softmax(const ColumnVector& r)
{
    ColumnVector r1=exp(r);
    return r1/sum(r1);
}

#endif //  VECTOR_H