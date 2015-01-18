#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <boost/lexical_cast.hpp>  
#include"../classifier.h"
#include"../data.h"
typedef int ClassID;
using namespace std;

class LogisticRegression:public Classifier
{
     vector<double> weight;
     int dimension;
     double lamda;
     double learning_rate;
     double stop_threshold;
     enum optimization_algorithm{SGD,LBFGS};
public:
     LogisticRegression()
     {
     }
     ~LogisticRegression()
     {
     }
     void init(map<string,string>& parameters) //TODO
     {
          lamda = boost::lexical_cast<double>(parameters["lamda"]); //regularization-coefficient
          learning_rate = boost::lexical_cast<double>(parameters["learning-rate"]); 
          stop_threshold = boost::lexical_cast<double>(parameters["stop-threshold "]); 
     }
     bool predict(const vector<double>& input) const
     {
          return probability(input)>0.5;
     }
     double probability(const vector<double>& input) const
     {
          assert(input.size()==dimension);
          return sigmoid(input*weight);
     }
     void train(const vector<ClassificationData>& train_data)
     {
          sgd(train_data);
     }
private:
     inline double sigmoid(double s) const
     {
          return 1/(1+exp(0-s));
     }
     inline double sigmoid_derivative(double s) const
     {
          return sigmoid(s)*(1-sigmoid(s));
     }
     void sgd(const vector<ClassificationData>& train_data)
     {
          int size=train_data.size();
          assert(size>0);
          init_weight(train_data);
          vector<double> gradient;
          do
          {
              int random_index=rand()%size;
              gradient=loss_function_gradient(train_data[random_index].input,train_data[random_index].output);
              weight=weight-(learning_rate*gradient);
          }while(norm(gradient)>stop_threshold);
     }
     void init_weight(const vector<ClassificationData>& train_data)
     {
          weight.resize(train_data[0].input.size());
     }
     double loss_function(const vector<double>& input,bool output) const
     {
          double probability=predict(input);
          return log(output?probability:1-probability);
     }
     vector<double> loss_function_gradient(const vector<double>& input,bool output) const 
     {
          double probability=predict(input);
          double coefficient=output?(1/probability):1/(probability-1);
          return (coefficient*sigmoid_derivative(input*weight))*input+lamda*weight;
     }
};
#endif
