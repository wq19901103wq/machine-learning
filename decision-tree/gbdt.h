#ifndef GBDT_H
#define GBDT_H
#include "regression-tree.h"
using namespace std;
class GradientBoostingDescentTree:public Regressor 
{
     vector<RegressionTree> regression_trees;
     double shrink;
public:
     void init(map<string,string>& parameters)
     {
          int tree_count= boost::lexical_cast<int>(parameters["tree-count"]); 
          shrink = boost::lexical_cast<double>(parameters["learning-rate"]); 
          regression_trees.resize(tree_count);
          for(int i=0;i<tree_count;i++)
                regression_trees[i].init(parameters);
     }
     void save_model(string path) const //TODO 
     {
     }
     void load_model(string path)
     {
     }
     double predict( ReagressionData& data) const
     {
	   double ret = 0;
           for (int tree_id=0;tree_id < regression_trees.size();tree_id++)
           {
                ret += shrink * regression_trees[tree_id].predict(data);
           }
           return ret;
     }
     void train(const vector<ReagressionData>& dataset)
     {
           vector<ReagressionData> temp_dataset=dataset; 
           for (int tree_id=0;tree_id < regression_trees.size();tree_id++)
           {
                regression_trees[tree_id].train(temp_dataset);
                for (int data_id=0;data_id < temp_dataset.size();data_id++)
                {
                      temp_dataset[data_id].output -= shrink * regression_trees[tree_id].predict(temp_dataset[data_id]);
                }
           }
     }
private:
     double RMSE(const vector<ReagressionData>& dataset) 
     {
           double rmse = 0;
           for (int data_id=0;data_id < dataset.size();data_id++)
           {
                rmse += (dataset[data_id].output) * (dataset[data_id].output);//output 其实是残差
           }
           return sqrt( rmse / dataset.size() );
     }
};
#endif
