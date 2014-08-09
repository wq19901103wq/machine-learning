#ifndef REGRESSION_TREE_H
#define REGRESSION_TREE_H
#include<iostream>
#include<vector>
#include<queue>
#include"../data.h"
#include"tree.h"
#include <boost/lexical_cast.hpp>  
using namespace std;
//TODO 考虑数据缺失的情况
class RegressionTree:public Regressor 
{
     int min_leaf_size;
     int max_depth;
     TreeNode* root;
public:
     RegressionTree()
     {
     }
     ~RegressionTree()//TODO
     {
     }
     void init(map<string,string>& parameters)
     {
          min_leaf_size = boost::lexical_cast<int>(parameters["min-leaf-size"]); 
          max_depth = boost::lexical_cast<int>(parameters["max-depth"]); 
     }
     void save_model(string path) const //TODO 
     {
     }
     void load_model(string path)
     {
     }
     double predict(ReagressionData& data) const
     {
          return predict_by_single_tree(data)->get_prediction();
     }
     void train(const vector<ReagressionData>& dataset)
     {
          build_tree(dataset);
     }
private:
     TreeNode* predict_by_single_tree(const ReagressionData& data) const
     {
          TreeNode* node=root;
          while(!node->is_leaf())
          {
                node=(data.input[node->get_select_feature()]<= node->get_value())?(node->left_node):(node->right_node);
          }
          return node;
     }
     void build_tree(const vector<ReagressionData>& dataset)
     {
          std::queue<TreeNode*> node_to_spilit;
          vector<TrainSampleIndex> train_sample; 
          root=new TreeNode(1);
          for (int k=0;k<dataset.size();k++)
          {
	        root->train_sample.push_back(k);
          }
          node_to_spilit.push(root);
          TreeNode* temp_node;
          while(!node_to_spilit.empty())
          {
                temp_node=node_to_spilit.front();
                node_to_spilit.pop();
                split_node(dataset,temp_node,node_to_spilit);
          }
     }
     void split_node(const vector<ReagressionData>& dataset,TreeNode* node,  std::queue<TreeNode*>& node_to_spilit)
     {
          if ( stop_spilit(node) )
          {
                return;
          }
          std::pair<FeatureIndex,TreeValuetype> select_feature_and_spilt_value=find_best_spilit(dataset, node);
          node->set_spilit_feature(select_feature_and_spilt_value.first, select_feature_and_spilt_value.second);
          node->spilit();
	  node->left_node = new TreeNode(node->depth+1);
          node->right_node = new TreeNode(node->depth+1);
          int left_count=0,right_count=0;
          double left_sum=0,right_sum=0;
          for (int i=0;i<(node->train_sample).size();i++)
          {
               if(dataset[node->train_sample[i]].input[node->get_select_feature()]<node->get_value() )
               {
	             node->left_node->train_sample.push_back(node->train_sample[i]);
                     left_count++;
                     left_sum+=dataset[node->train_sample[i]].output;
               }
               else
               {
	             node->right_node->train_sample.push_back(node->train_sample[i]);
                     right_count++;
                     right_sum+=dataset[node->train_sample[i]].output;
               }
          }
          //TODO 清空已分裂节点的train_sample
          node->left_node->set_prediction(left_sum/left_count);
          node->right_node->set_prediction(right_sum/right_count);
          node_to_spilit.push(node->left_node);
          node_to_spilit.push(node->right_node);
     }
     bool stop_spilit(TreeNode* node)
     {
          if ( node->train_sample_size() < min_leaf_size)
               return  true;
          if ( node->depth >= max_depth )
               return  true;
          return false;
     }
     std::pair<FeatureIndex,TreeValuetype> find_best_spilit(const vector<ReagressionData>& dataset,TreeNode* node)
     {
          FeatureIndex feature_size=dataset[0].input.size();
	  vector<std::vector<std::pair<TreeValuetype,double> > > feature_value_map(feature_size);
          double sum_total = 0;
          double square_sum_total = 0;
          int count_total = 0;
          FeatureIndex select_feature;
          TreeValuetype select_value;
          for (int i=0;i<node->train_sample_size();i++)
          {
               sum_total += dataset[node-> train_sample[i]].output;
               square_sum_total += dataset[node-> train_sample[i]].output * dataset[node-> train_sample[i]].output;
               count_total ++;
          }
          for (int sampleid=0;sampleid<node->train_sample_size();sampleid++)
          {
               for (int featureid=0;featureid<feature_size;featureid++) 
               {
	              feature_value_map[featureid].push_back(make_pair(dataset[node->train_sample[sampleid]].input[featureid], dataset[node->train_sample[sampleid]].output));
               }
          }
          double min_error=LargeNum;
          for (int featureid=0;featureid<feature_size;featureid++) 
          {
               std::vector<std::pair<TreeValuetype,double> >& feaure_try_to_spilit=feature_value_map[featureid];
               std::sort(feaure_try_to_spilit.begin(),feaure_try_to_spilit.end());
               std::pair<FeatureIndex,TreeValuetype> best_spilt_value_error_pair=best_spilit_by_square_error(feaure_try_to_spilit, square_sum_total, sum_total) ;
	       if (min_error > best_spilt_value_error_pair.second)
               {
                    min_error=best_spilt_value_error_pair.second;
                    select_feature= featureid;
                    select_value = best_spilt_value_error_pair.first;
               }
          }
          return make_pair(select_feature,select_value);
     }



};




#endif
