#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include<iostream>
#include"../classifier.h"
#include"../data.h"
using namespace std;
class Layer
{  
}
class WeightMatrix
{
}
class NeuralNetwork
{
     Layer input;
     vector<Layer> hidden_layer;
     vector<WeightMatrix> weight;
     Layer output;   
public:
     NeuralNetwork()
     {
     }
     ~NeuralNetwork()
     {
     }
     void init(map<string,string>& parameters) //TODO
     {
     }
     bool predict(const vector<double>& input) const
     {
     }
     void train(const vector<ClassificationData>& train_data)
     {
     }
private:
     void back_propagation()  //BP
     {
     }
     void loss_function()
     {
     }
}



#endif
