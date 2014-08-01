#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;

inline bool min(double data1,double data2)
{
     return data1>data2?data1:data2;
}
double operator*(const vector<double>& lfh, const vector<double>& rgh)
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
vector<double> operator-(const vector<double>& lfh, const vector<double>& rgh)
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
vector<double> operator+(const vector<double>& lfh, const vector<double>& rgh)
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
vector<double> operator*(double lfh, const vector<double>& rgh)
{
     vector<double> result;
     result.resize(rgh.size());
     for(int i=0;i<rgh.size();i++)
     {
         result[i]+=lfh*rgh[i];
     }
     return result;     
}
double norm(const vector<double>& vec)
{
     return sqrt(vec*vec);
}

struct Data
{
     vector<double> input;
     bool output;
};
class LogisticRegression
{
     vector<double> weight;
     int dimension;
     double lamda;
     double step_size;
     double stop_threshold;
     enum optimization_algorithm{SGD,LBFGS};
public:
     LogisticRegression(double lamda_para,double step_size_para,double stop_threshold_para):lamda(lamda_para),step_size(step_size_para),stop_threshold(stop_threshold_para)
     {
     }
     ~LogisticRegression()
     {
     }
     double predict(const vector<double>& input) const
     {
          assert(input.size()==dimension);
          return sigmoid(input*weight);
     }
     void train(const vector<Data>& train_data)
     {
          sgd(train_data);
     }
     void sgd(const vector<Data>& train_data)
     {
          int size=train_data.size();
          vector<double> gradient;
          do
          {
              int random_index=rand()%train_data.size();
              gradient=loss_function_gradient(train_data[random_index].input,train_data[random_index].output);
              weight=weight-(lamda*gradient);
          }while(norm(gradient)>stop_threshold);
     }
private:
     double loss_function(const vector<double>& input,bool output) const
     {
          double probability=predict(input);
          return log(output?probability:1-probability);
     }
     inline double sigmoid(double s) const
     {
          return 1/(1+exp(0-s));
     }
     inline double sigmoid_derivative(double s) const
     {
          return sigmoid(s)*(1-sigmoid(s));
     }
     vector<double> loss_function_gradient(const vector<double>& input,bool output) const 
     {
          double probability=predict(input);
          double coefficient=output?(1/probability):1/(probability-1);
          return (coefficient*sigmoid_derivative(input*weight))*input+lamda*weight;
     }
};
