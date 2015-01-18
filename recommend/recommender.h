#ifndef RECOMMENDER_H
#define RECOMMENDER_H
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include"../data.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;
using namespace std;
typedef int user_index ;
typedef int item_index;
typedef double score_type;
const score_type not_given=-1.0;
class Recommender
{
public:
     SparseMatrix<score_type>& user_item_matrix;
     virtual ~Recommender();
     virtual score_type predict(user_index u,item_index i) const=0;
     virtual void train()=0;
     virtual double loss_function()=0;
     inline double access(user_index u,item_index i) const//TODO
     {
         // return user_item_matrix(u,i);
     }
     inline bool is_given(score_type s) const 
     {
          return (s>-0.99)||(s<-1.01);
     }
     inline user_index get_user_num() const 
     {
          return user_item_matrix.rows();
     }
     inline item_index get_item_num() const 
     {
          return user_item_matrix.cols();
     }
};


#endif
