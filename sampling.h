#ifndef SAMPLING_H
#define SAMPLING_H
#include<iostream>
#include<vector>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
double uniform()   //均匀分布
{
    return rand()/double(RAND_MAX);
}
double exponential(double pow)  //指数分布
{
    return -log((1-uniform())*pow)/pow;
}
double normal()  //正态分布 Box-Muller变换
{
    double U1=uniform(), U2=uniform();
    double R = sqrt(-2 * log(U2));
    double theta= 2 * M_PI* U1;
    return R*cos(theta);//or R* sin(theta)
}
double uniform_generate_by_normal()
{
    double N1=normal(),N2=normal();
    return atan2(N1,N2)/(2*M_PI)+0.5;
}
void test(int num,int experient_num)
{
    double k;
    vector<int> result;
    result.resize(num+10);
    double d=double(1)/num;
    for(int i=0;i<experient_num;i++)
    {
        k=uniform_generate_by_normal();
        result[floor(k/d)]++;
    }
    for(int i=0;i<num;i++)
    {
        cout<<double(result[i])/experient_num<<endl;
    }         
}
#endif

