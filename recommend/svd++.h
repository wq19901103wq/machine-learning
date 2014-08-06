#include"recommender.h"
using namespace Eigen;
using namespace std;
class SVDPlusPlus:public Recommender
{
     vector<score_type> user_bias;
     vector<score_type> item_bias;
     MatrixXf user_factor_matrix;//TODO
     MatrixXf item_factor_matrix;
     double average_bias;
     double lamda4;//正则参数
public:
     score_type predict(user_index u,item_index i) const
     {
        //  return average_bias+user_bias[u]+item_bias[i]+user_factor_matrix(u).dot(item_factor_matrix(i));//TODO
     }
     void train()
     {
     }
     double loss_function()
     {
     }
private:
     double regularization() const 
     {
           return lamda4*(user_bias*user_bias+item_bias*item_bias+pow(user_factor_matrix.norm(),2)+pow(item_factor_matrix.norm(),2));
     }
     double predict_error(user_index u,item_index i) const
     {
           return access(u,i)-predict(u,i);
     }
};
      
