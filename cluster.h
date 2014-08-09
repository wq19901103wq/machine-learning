#ifndef CLUSTER_H
#define CLUSTER_H
#include<iostream>
#include<map>
#include"data.h"
using namespace std;
class Cluster
{
public:
     virtual void init(map<string,string>& parameters)=0;
     virtual void train(vector<ClusterData>& dataset)=0;
     virtual ~Cluster();
};
#endif
