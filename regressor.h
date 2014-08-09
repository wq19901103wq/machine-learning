#ifndef REGRESSOR_H
#define REGRESSOR_H
#include<iostream>
#include<map>
#include"data.h"
using namespace std;
class Regressor 
{
public:
     virtual void init(map<string,string>& parameters)=0;
     virtual void save_model(string path) const=0;
     virtual void load_model(string path)=0;
     virtual double predict(ReagressionData& data) const=0;
     virtual void train(const vector<ReagressionData>& dataset)=0;
     virtual ~Regressor();
};
#endif
