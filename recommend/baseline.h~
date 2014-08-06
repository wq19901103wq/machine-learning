#include"recommender.h"

class BaselinePredictor:public Recommender
{
     vector<score_type> user_bias;
     vector<score_type> item_bias;
     double average_bias;
     double lamda;//正则参数
public:
     score_type predict(user_index u,item_index i)
     {
          return average_bias+user_bias[u]+item_bias[i];
     }
     void train()
     {
     }
     double loss_function()
     {
          double sum=0;
          for (int k=0; k<user_item_matrix.outerSize(); ++k)
          {
                 for (SparseMatrix<double>::InnerIterator it(user_item_matrix,k); it; ++it)
                 {
                     user_index u=it.row(); // row index
                     item_index i=it.col(); // col index 
                     sum+= pow((it.value()-predict(u,i)),2);
                 }
          }
          sum+= regularization();
          return sum;
     }
private:
     double regularization() const
     {
           return lamda*(user_bias*user_bias+item_bias*item_bias);
     }
};
      

