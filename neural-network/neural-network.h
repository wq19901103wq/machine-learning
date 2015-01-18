#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include <iostream>
#include "../matrix/matrix.h"
#include "../matrix/vector.h"
#include "../classifier.h"
#include "../data.h"
#include "../sampling.h"

typedef int ClassID;

struct NeuralNetworkParams
{
      double learning_rate;
      double learning_rate_discount;
      double regularization;
      int hidden; 
      int steps;
      int verbose;  
};
struct TwoLayerWeights
{
      Matrix L2;
      Matrix L1;
};
class NeuralNetwork: public MultiClassifier
{
     TwoLayerWeights model;
     NeuralNetworkParams params;
     int max_label;  
public:
     NeuralNetwork()
     {
     }
     ~NeuralNetwork()
     {
     }
     void init(map<string,string>& parameters)
     {
        params.learning_rate = boost::lexical_cast<double>(parameters["learning-rate"]);
        params.learning_rate_discount = boost::lexical_cast<double>(parameters["learning-rate-discount"]);
        params.regularization = boost::lexical_cast<double>(parameters["regularization"]);
        params.steps = boost::lexical_cast<int>(parameters["steps"]);
        params.hidden = boost::lexical_cast<int>(parameters["hidden"]);
        params.verbose = boost::lexical_cast<int>(parameters["verbose"]);
     }
     void save_model(const string& path) const //TODO 
     {
     }
     void load_model(const string& path)
     {
     }
     void  train(const vector<MultiClassificationData>& data) 
     {
         int input_dim=get_dim_of(data);
         int class_num=get_class_num_of(data);
         model.L1 = Matrix(input_dim,params.hidden);
         model.L2 = Matrix(params.hidden,class_num);  
         int counter=0;
         for (int i=0;i<input_dim;i++)
         {
              for(int j=0;j<params.hidden; j++)
              {
                    model.L1[i][j]= (uniform() - 0.5) / sqrt(double(params.hidden));              
              }
         }
         for (int i=0;i<params.hidden;i++)
         {
              for(int j=0;j<class_num; j++)
              {
                    model.L2[i][j]= (uniform() / sqrt(double(class_num) + 1.0));
              }
         }
         for(int step = 0; step < params.steps; step++)
         {
              for (int k=0;k<data.size();k++)
              {
                   RowVector error(class_num);
                   RowVector y(params.hidden);
                   RowVector z(class_num);
                   RowVector delta_hidden(params.hidden);
                   error[data[k].data_class]=1;
                   y=sigmoid(RowVector(data[k].input)*model.L1);
                   z=softmax(y*model.L2);
                   error = error - z;
                   for (int i=0;i<params.hidden;i++)
                   {
                      double delta=0; 
                      for (int j=0;j<class_num;j++)
                      {
                           double wij = model.L2[i][j];
                           double sig_ij = error[j] * (1-z[j]) * z[j];
                           delta += sig_ij * wij;
                           wij += params.learning_rate * (y[i] * sig_ij - params.regularization * wij);
                           model.L2[i][j]= wij;
                      }
                      delta_hidden[i]=delta;
                   }
                   for (int i=0;i<params.hidden;i++)
                   {
                       for (int j=0;j<input_dim;j++)
                       {
                           double wji = model.L1[j][i];
                           wji += params.learning_rate* (delta_hidden[i] * data[k].input[j] * y[i] * (1-y[i]) - params.regularization* wji);
                           model.L1[j][i]=wji;
                       }
                   }
                   counter++;
                   if (params.verbose > 0 && counter % 2000 == 0 )
                   {
                       printf("Epoch %d\n", step+1);
                   }
              }            
              params.learning_rate *= params.learning_rate_discount;
         }
     }
     RowVector predict_multi_class(const RowVector& input)
     {
          return softmax(sigmoid(input*model.L1)*model.L2);
     }
     ClassID predict(const RowVector& input) 
     {
          return argmax_index(predict_multi_class(input));
     }

private:
     ClassID argmax_index(const RowVector& z)
     {
          ClassID max_id=0;
          double max_probability=0;
          for(int i=0;i<z.size();i++)
          {
              if(max_probability<z[i])
              {
                   max_id=i;
                   max_probability=z[i];
              }
          }
          return max_id;
     }
     RowVector random_init_vector(int dim) 
     {
         RowVector v (dim);
         for (int i = 0; i < dim; i++)
         {
             v[i] = (rand()/double(RAND_MAX)- 0.5) / sqrt(double(dim));
         }
         return v;
     }

};



#endif
