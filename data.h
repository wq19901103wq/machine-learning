#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <set>

using namespace std;

typedef int ClassID;
typedef int FeatureID;
typedef int SampleID;
typedef double FeatureValue;

const double LargeNum=10000000000000;
const double SmallNum=-10000000000000;

inline double min(double data1,double data2)
{
     return data1<data2?data1:data2;
}
inline double max(double data1,double data2)
{
     return data1>data2?data1:data2;
}
const double operator*(const vector<double>& lfh, const vector<double>& rgh)
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
const vector<double> operator-(const vector<double>& lfh, const vector<double>& rgh)
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
const vector<double> operator+(const vector<double>& lfh, const vector<double>& rgh)
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

const vector<double> operator*(double lfh, const vector<double>& rgh)
{
     vector<double> result;
     result.resize(rgh.size());
     for(int i=0;i<rgh.size();i++)
     {
         result[i]=lfh*rgh[i];
     }
     return result;     
}
vector<double> operator/(const vector<double>& lfh,double rgh)
{
     vector<double> result;
     result.resize(lfh.size());
     for(int i=0;i<lfh.size();i++)
     {
         result[i]+=lfh[i]/rgh;
     }
     return result;     
}
void operator+=(vector<double>& lfh, const vector<double>& rgh)
{
     lfh=lfh+rgh;
}
void operator-=(vector<double>& lfh, const vector<double>& rgh)
{
     lfh=lfh-rgh;
}
double norm2(const vector<double>& vec)
{
     return sqrt(vec*vec);
}
double norm1(const vector<double>& vec)
{
     double sum=0;
     for(vector<double>::const_iterator iter=vec.begin();iter!=vec.end();iter++)
            sum+=abs(*iter);
     return sum;
}
double norm(const vector<double>& vec)
{
     return norm2(vec);
}
double sum(const vector<double>& vec)
{
     double sum=0;
     for(vector<double>::const_iterator iter=vec.begin();iter!=vec.end();iter++)
            sum+=(*iter);
     return sum;
}
double mean(const vector<double>& vec)
{
     return sum(vec)/double(vec.size());
}
double variance(const vector<double>& vec)
{
     return norm(vec)/vec.size()-mean(vec)*mean(vec);
}
double sigmoid(double s)
{
     return 1/(1+exp(0-s));
}
double square_error(double sum_left, double square_sum_left, int count_left,double sum_right,double square_sum_right, double count_right) 
{
     double error=0;
     if(count_left!=0)
     {
            double mean_left = sum_left / count_left;
            error+=(square_sum_left - mean_left * mean_left * count_left );
     }
     if(count_right!=0)
     {
            double mean_right = sum_right / count_right;
            error+=(square_sum_right- mean_right * mean_right * count_right);
     }
     return error;
}
std::pair<FeatureValue, double> best_spilit_by_square_error(const vector<std::pair<FeatureValue,double> >& feature_value_map,double square_sum,double sum) 
{
     double sum_left=0, square_sum_left=0, sum_right=square_sum, square_sum_right=sum;
     int count_left=0,count_right=feature_value_map.size();
     double min_error=LargeNum,error;
     FeatureValue spilit_value;
     while(count_right>0)
     {
            error=square_error(sum_left,square_sum_left, count_left,sum_right, square_sum_right, count_right) ;
            if(error<min_error)
            {
                 min_error=error;
                 spilit_value=feature_value_map[count_left].first;
            }
            count_left++;
            sum_left+=feature_value_map[count_left].second;
            square_sum_left+=feature_value_map[count_left].second*feature_value_map[count_left].second;
            count_right--;
            sum_right-=feature_value_map[count_left].second;
            square_sum_right-=feature_value_map[count_left].second*feature_value_map[count_left].second;
     }
     return make_pair(spilit_value,error);

}


class Data
{
public:
     vector<double> input;
     virtual void read(string filename)=0;
     virtual void write(string filename)=0;
};
class ClusterData:public Data
{
public:
     ClassID data_class;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
class ClassificationData:public Data
{
public:
     bool output;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
class MultiClassificationData:public Data
{
public:
     ClassID data_class;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
class ReagressionData:public Data
{
public:
     double output;
     virtual void read(string filename)
     {
     }
     virtual void write(string filename)
     {
     }
};
const double euclid_distance(const ClusterData& p1,const ClusterData& p2)
{
     return norm(p1.input-p2.input);
}

int get_dim_of(std::vector<MultiClassificationData> data)
{
    if(data.empty())
        return 0;
    else
        return data[0].input.size();
}
int get_class_num_of(std::vector<MultiClassificationData> data)
{
    std::set<ClassID> class_ids;
    for(size_t i=0;i<data.size();i++)
    {
        class_ids.insert(data[i].data_class);
    }
    return class_ids.size();
}
#endif
