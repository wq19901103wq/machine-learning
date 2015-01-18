#ifndef SVM_H
#define SVM_H
#include<iostream>
#include"../classifier.h"
#include"../data.h"

class SVM : public Classifier
{
      vector<double> weight;
      double bias;
      vector<vector<double> > support_vector;
      double margin_upper_bound;   //C in paper   st. 0<ai<C
public: 
     SVM()
     {
     }
     ~SVM()
     {
     }
     void init(map<string,string>& parameters) //TODO
     {

     }
     bool predict(const vector<double>& input) const
     {
          return (weight*input-bias)>0;
     }
     void train(const vector<ClassificationData>& train_data)
     {
     }
private:
     bool match_kkt(double y, double f, double a) 
     {
     }
};

#endif
