#ifndef DATA_H
#define DATA_H
#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;
typedef size_t class_index;
const double LargeNum=10000000000000;
inline bool min(double data1,double data2)
{
     return data1>data2?data1:data2;
}
const double operator*(const vector<double>& lfh, const vector<double>& rgh)
{
     double sum;
     assert(lfh.size()==rgh.size());
     int size=min(lfh.size(),rgh.size());
     for(int i=0;i<size;i++)
     {
         sum+=lfh[i]*rgh[i];
     }
     return sum;
}
const vector<double> operator-(const vector<double>& lfh, const vector<double>& rgh)
{
     vector<double> result;
     assert(lfh.size()==rgh.size());
     int size=min(lfh.size(),rgh.size());
     result.resize(size);
     for(int i=0;i<size;i++)
     {
         result[i]=lfh[i]-rgh[i];
     }
     return result;
}
const vector<double> operator+(const vector<double>& lfh, const vector<double>& rgh)
{
     vector<double> result;
     assert(lfh.size()==rgh.size());
     int size=min(lfh.size(),rgh.size());
     result.resize(size);
     for(int i=0;i<size;i++)
     {
         result[i]=lfh[i]+rgh[i];
     }
     return result;
}

const vector<double> operator*(double lfh, const vector<double>& rgh)
{
     vector<double> result;
     result.resize(rgh.size());
     for(int i=0;i<rgh.size();i++)
     {
         result[i]=lfh*rgh[i];
     }
     return result;     
}
vector<double> operator/(const vector<double>& lfh,double rgh)
{
     vector<double> result;
     result.resize(lfh.size());
     for(int i=0;i<lfh.size();i++)
     {
         result[i]+=lfh[i]/rgh;
     }
     return result;     
}
void operator+=(vector<double>& lfh, const vector<double>& rgh)
{
     lfh=lfh+rgh;
}
void operator-=(vector<double>& lfh, const vector<double>& rgh)
{
     lfh=lfh-rgh;
}

double norm(const vector<double>& vec)
{
     return sqrt(vec*vec);
}
class Data
{
public:
     vector<double> input;
     virtual void read(string filename)=0;
     virtual void write(string filename)=0;
};
class ClusterData:public Data
{
public:
     class_index data_class;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
class ClassificationData:public Data
{
public:
     bool output;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
class MultiClassificationData:public Data
{
public:
     class_index data_class;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
class ReagressionData:public Data
{
public:
     double output;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
#endif
