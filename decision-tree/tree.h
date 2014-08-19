#ifndef TREE_H
#define TREE_H
#include <vector>
using namespace std;

typedef std::vector< std::vector<FeatureValue> > TreeValueMatrix;
typedef std::vector<FeatureValue> TreeValueVector;
struct TreeNode
{
      FeatureID select_feature; 
      FeatureValue select_value; 
      double prediction;
      TreeNode* left_node; 
      TreeNode* right_node; 
      vector<SampleID> train_sample; 
      int depth;
      bool leaf;
public:
      TreeNode(int d):depth(d),leaf(true)
      {
      }
      TreeNode(const vector<SampleID>& t,int d): train_sample(t),depth(d)
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
      FeatureValue get_value()
      {
            return select_value;
      }
      FeatureID get_select_feature()
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
      void set_spilit_feature(FeatureID s, FeatureValue v)
      {
           select_feature=s; 
           select_value=v;
      }
};
#endif 
