#ifndef REGRESSION_TREE_H
#define REGRESSION_TREE_H
#include<iostream>
#include<vector>
#include<queue>
#include"../data.h"
#include"tree.h"

using namespace std;

class RegressionTree:public Classifier
{
     int min_leaf_size;
     int max_depth;
     TreeNode* root;
public:
     void init(const map<string,string>& parameters)
     {
     }
     void save_model(string path) const
     {
     }
     void load_model(string path)
     {
     }
     double predict(ReagressionData& data) const
     {
     }
     void train(const vector<ReagressionData>& dataset)
     {
     }
private:
     TreeNode* predict_by_single_tree(ReagressionData& data)
     {
          TreeNode* node=root;
          TreeNode* last_node;
          while(node!=NULL)
          {
                node=(data.input[node->select_feature]<= node->get_value())?(node->left_node):(node->right_node);
                last_node=node;
          }
          return last_node;
     }
     void build_tree(const vector<ReagressionData>& dataset)
     {
          std::queue<TreeNode*> node_to_spilit;
          vector<TrainSampleIndex> train_sample; 
          root=new TreeNode();
     }
     void split_node(const vector<ReagressionData>& dataset,TreeNode* node,  std::queue<TreeNode*> node_to_spilit)
     {
          if ( node->depth >= max_depth )
          {
                return;
          }
          FeatureIndex select_feature; 
          TreeValuetype select_value; 
          find_best_spilit(dataset, node, select_feature,select_value);
          node->set_spilit_feature(select_feature, select_value);
	  node->left_node = new TreeNode();
          node->right_node = new TreeNode();
          int left_count=0,right_count=0;
          double left_sum=0,right_sum=0;
          for (int i=0;i<(node->train_sample).size();i++)
          {
               if(dataset[node->train_sample[i]].input[node->select_feature]<node->get_value() )
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
          if( node->left_node->train_sample_size() > min_leaf_size)
          {
               node->left_node->set_prediction(left_sum/left_count);
               node_to_spilit.push(node->left_node);
          }
          if( node->right_node->train_sample_size() > min_leaf_size)
          {
               node->left_node->set_prediction(right_sum/right_count);
               node_to_spilit.push(node->right_node);
          }
     }
     void find_best_spilit(const vector<ReagressionData>& dataset,TreeNode* node,  FeatureIndex select_feature, TreeValuetype select_value)
     {
     }



};




#endif
