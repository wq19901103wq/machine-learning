#include<iostream>
#include<vector>
#include"../data.h"
using namespace std;
const double euclid_distance(const ClusterData& p1,const ClusterData& p2)
{
     return norm(p1.input-p2.input);
}

class KMeans
{
public:
     enum INITIALMETHOD{KMEANSPLUSPLUS,MAXMINCHARACTERISTIC,NAIVEMETHOD};
     class InitialMethod
     {
      public:
           virtual vector<ClusterData> InitialPointGenerate()=0;
           virtual ~InitialMethod()=0;
     };
     class KMeansPlusPlus:public InitialMethod
     {
      public:
           vector<ClusterData> InitialPointGenerate()
           {
           }
     };
     class MaxMinCharacteristic:public InitialMethod
     {
      public:
           vector<ClusterData> InitialPointGenerate()
           {
           }
     };
     class NaiveMethod:public InitialMethod
     {
      public:
           vector<ClusterData> InitialPointGenerate()
           {
           }
     };
     class InitialPointFacotry
     {
      public:
           InitialMethod* create_initial_point_factory(enum INITIALMETHOD initialtype)    
           {    
               if(initialtype == KMEANSPLUSPLUS)    
                    return new KMeansPlusPlus();    
               else if(initialtype == MAXMINCHARACTERISTIC)    
                    return new MaxMinCharacteristic(); 
               else if(initialtype == NAIVEMETHOD)    
                    return new NaiveMethod(); 
               else    
                    return NULL;    
           }    

     };
private:
     class_index k;//class_number
     vector<ClusterData>& data;
     vector<ClusterData> cluster_center;
     InitialPointFacotry inital_point_factory;
     bool stop_condition;
public:
     KMeans(vector<ClusterData>& inputdata,int class_num,enum INITIALMETHOD initialtype):data(inputdata),k(class_num),stop_condition(false)
     {

          InitialMethod* inital_point_func=inital_point_factory.create_initial_point_factory(initialtype);
          cluster_center=inital_point_func->InitialPointGenerate();
          delete inital_point_func;
     }
     ~KMeans()
     {
     }
     void train()
     {
          do
          {
              MStep();
              EStep();
          }while(!stop_condition);
     }
private:
     void EStep()
     {
          vector<std::pair<ClusterData,int> > cluster_sum;//cluster_sum.first->sum of value,cluster_sum.first->cluster total nums
          cluster_sum.resize(k);
          for(int i=0;i<data.size();i++)
          {
                cluster_sum[data[i].data_class].first.input+=data[i].input;
                cluster_sum[data[i].data_class].second++;
          }
          for(class_index i=0;i<cluster_sum.size();i++)
          {
                cluster_center[i].input=cluster_sum[i].first.input/double(cluster_sum[i].second);
                cluster_center[i].data_class=i;
          }
     }
     void MStep()
     {
          stop_condition=true;
          for(int i=0;i<data.size();i++)
          {
               class_index cl=nearest_center(data[i],cluster_center);
               if(data[i].data_class!=cl)
                      stop_condition=false;
               data[i].data_class=cl;
          }
     }
     class_index nearest_center(const ClusterData& p1,const vector<ClusterData>& points) const
     {
          double min_distance=LargeNum;
          class_index nearest_center;
          for(int i=0;i<points.size();i++)
          {
               if(euclid_distance(points[i],p1)<min_distance)
               {
                     min_distance=euclid_distance(points[i],p1);
                     nearest_center=i;
               }
          }
          return nearest_center;
     }

     
};

int main()
{
}
