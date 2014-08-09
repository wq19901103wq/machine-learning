#ifndef TREE_H
#define TREE_H
#include <vector>
using namespace std;

typedef std::vector< std::vector<TreeValuetype> > TreeValueMatrix;
typedef std::vector<TreeValuetype> TreeValueVector;
struct TreeNode
{
      FeatureIndex select_feature; 
      TreeValuetype select_value; 
      double prediction;
      TreeNode* left_node; 
      TreeNode* right_node; 
      vector<TrainSampleIndex> train_sample; 
      int depth;
      bool leaf;
public:
      TreeNode(int d):depth(d),leaf(true)
      {
      }
      TreeNode(const vector<TrainSampleIndex>& t,int d): train_sample(t),depth(d)
      {
      }
      bool is_leaf()
      {
            return leaf;
      }
      void spilit()
      {
            leaf=false;
      }
      size_t train_sample_size()
      {
            return train_sample.size();
      }
      TreeValuetype get_value()
      {
            return select_value;
      }
      FeatureIndex get_select_feature()
      {
            return select_feature;
      }
      double get_prediction()
      {
            return prediction;
      }
      void set_prediction(double p)
      {
            prediction=p;
      }
      void set_spilit_feature(FeatureIndex s, TreeValuetype v)
      {
           select_feature=s; 
           select_value=v;
      }
};
#endif 
