#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include<iostream>
#include<map>
#include"data.h"
using namespace std;
class Classifier 
{

public:
     virtual void init(map<string,string>& parameters)=0;
     virtual void save_model(string path) const=0;
     virtual void load_model(string path)=0;
     virtual bool predict(ClassificationData& data)=0;
     virtual void train(const vector<ClassificationData>& dataset)=0;
     virtual ~Classifier();
};
class MultiClassifier 
{
public:
     virtual void init(const map<string,string>& parameters)=0;
     virtual void save_model(string path) const=0;
     virtual void load_model(string path)=0;
     virtual ClassID predict(MultiClassificationData& data)=0;
     virtual void train(const vector<MultiClassificationData>& dataset)=0;
     virtual ~MultiClassifier();
};
#endif
