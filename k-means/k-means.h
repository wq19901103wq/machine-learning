#ifndef KMEANS_H
#define KMEANS_H
#include<iostream>
#include<vector>
#include"../data.h"
using namespace std;
typedef int ClassID;
class KMeans:public Cluster
{
public:
     enum INITIALMETHOD{KMEANSPLUSPLUS,MAXMINCHARACTERISTIC,NAIVEMETHOD};
     class InitialMethod
     {
      public:
           virtual vector<ClusterData> initial_point_generate(const vector<ClusterData>& data,ClassID k)=0;
           virtual ~InitialMethod()=0;
     };
     class KMeansPlusPlus:public InitialMethod
     {
      public:
           vector<ClusterData> initial_point_generate(const vector<ClusterData>& data,ClassID k)
           {
                vector<ClusterData> ret;
                ret.push_back(data[rand()%k]);
                vector<double> distance(data.size(),LargeNum);
                while(true)
                {
                     update_distance(ret[ret.size()-1],data,distance);
                     ret.push_back(data[sampling_by_probabilities(distance)]);
                     if(ret.size()>=k) 
                          break;
                }
                return ret;
           }
      private:
           double min_distance(const ClusterData& p1,const vector<ClusterData>& points) const //NO USE
           {
                double min_distance=LargeNum;
                for(int i=0;i<points.size();i++)
                {
                    if(euclid_distance(points[i],p1)<min_distance)
                    {
                        min_distance=euclid_distance(points[i],p1);
                    }
                }
                return min_distance;
          }
          void update_distance(const ClusterData& p,const vector<ClusterData>& points,vector<double>& distance) const
          {
                for(int i=0;i<points.size();i++)
                {
                    distance[i]=min(distance[i],euclid_distance(points[i],p));
                }
          }
          ClassID sampling_by_probabilities(const vector<double>& distance)
          {
                double total=sum(distance);
                double rand=random()*total;//TODO
                int k=-1;
                do
                {
                     k++;
                     rand-=distance[k];
                }while(total>=0);
                return k;
          }
     };
     class MaxMinCharacteristic:public InitialMethod
     {
      public:
           vector<ClusterData> initial_point_generate(const vector<ClusterData>& data,ClassID k)
           {
                vector<ClusterData> ret;
                vector<double> max_feature_value(data[0].input.size(),SmallNum);
                vector<double> min_feature_value(data[0].input.size(),LargeNum);
                for(SampleID i=0;i<data.size();i++)
                {
                    for(FeatureID k=0;k<data[0].input.size();k++)
                    {
                        max_feature_value[k]=max(max_feature_value[k],data[i].input[k]);
                        min_feature_value[k]=min(min_feature_value[k],data[i].input[k]);
                    }
                }
                for(int i=0;i<k;i++)
                {
                    ret.push_back(random_generate(max_feature_value,min_feature_value,i));
                }
           }
      private:
           ClusterData random_generate(const vector<double>& max_feature_value,const vector<double>& min_feature_value,ClassID clid)
           {
                ClusterData center;
                center.input.resize(max_feature_value.size());
                center.data_class=clid;
                for(FeatureID k=0;k<max_feature_value.size();k++)
                {
                      center.input[k]=rand()%2?max_feature_value[k]:min_feature_value[k];
                }
                return center;
           }
     };
     class NaiveMethod:public InitialMethod
     {
      public:
           vector<ClusterData> initial_point_generate(const vector<ClusterData>& data,ClassID k)
           {
                 vector<ClusterData> ret;
                 for(int i=0;i<k;i++)
                 {
                     ret.push_back(data[rand()%k]);
                 }
                 return ret;
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
     ClassID k;//class_number
     vector<ClusterData>& data;
     vector<ClusterData> cluster_center;
     InitialPointFacotry inital_point_factory;
     bool stop_condition;
public:
     KMeans(vector<ClusterData>& inputdata,int class_num,enum INITIALMETHOD initialtype):data(inputdata),k(class_num),stop_condition(false)
     {

          InitialMethod* inital_point_func=inital_point_factory.create_initial_point_factory(initialtype);
          cluster_center=inital_point_func->initial_point_generate(data,k);
          delete inital_point_func;
     }
     ~KMeans()
     {
     }
     void init(const map<string,string>& parameters)
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
          for(ClassID i=0;i<cluster_sum.size();i++)
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
               ClassID cl=nearest_center(data[i],cluster_center);
               if(data[i].data_class!=cl)
                      stop_condition=false;
               data[i].data_class=cl;
          }
     }
     ClassID nearest_center(const ClusterData& p1,const vector<ClusterData>& points) const
     {
          double min_distance=LargeNum;
          ClassID nearest_center;
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
#endif
