#ifndef TREE_H
#define TREE_H
#include <vector>
using namespace std;
typedef int FeatureIndex;
typedef int TrainSampleIndex;
typedef double TreeValuetype;
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
public:
      TreeNode()
      {
      }
      TreeNode(const vector<TrainSampleIndex>& t,int d): train_sample(t),depth(d)
      {
      }
      size_t train_sample_size()
      {
            return train_sample.size();
      }
      size_t get_value()
      {
            return select_value;
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
