#include <iostream>
#include "matrix.h"
#include <math.h>
#include <assert.h>

Matrix::Matrix(void)
{
    p=new double[1];
    width=0;
    height=0;
}
Matrix::Matrix(int n)
{
    height=width=n;
    p=new double[n*n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) *(p+n*i+j)=1;
            else *(p+n*i+j)=0;
        }
    }
}
Matrix::Matrix(const double * arrAddress,int arrWidth,int arrHeight)
{
    p=new double[arrWidth*arrHeight];
    for(int i=0;i<arrHeight;i++){
        for(int j=0;j<arrWidth;j++){
            *(p+arrWidth*i+j)=*(arrAddress+arrWidth*i+j);
        }
    }
    width=arrWidth;
    height=arrHeight;
}
Matrix::Matrix(int arrWidth,int arrHeight)
{
    p=new double[arrWidth*arrHeight];
    for(int i=0;i<arrHeight;i++){
        for(int j=0;j<arrWidth;j++){
            *(p+arrWidth*i+j)=0;
        }
    }
    width=arrWidth;
    height=arrHeight;
}
Matrix::Matrix(const Matrix & m)//copy constructor
{
    height=m.height;
    width=m.width;
    p=new double[height*width];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            *(p+width*i+j)=*(m.p+width*i+j);
        }
    }
}
int Matrix::getWidth() const 
{
    return width;
}
int Matrix::getHeight() const 
{
    return height;
}
bool Matrix::isVector() const
{
    return !(width==1 && height==1);
}
Matrix Matrix::subMatrix(int offset)
{
    assert(height==width && offset<=width && offset>=0);
    double * t=new double[offset*offset];
    for(int i=0;i<offset;i++){
        for(int j=0;j<offset;j++){
            *(t+offset*i+j)=*(p+width*i+j);
        }
    }
    Matrix m(t,offset,offset);
    delete [] t;
    return m;
}
double Matrix::Arg() const//矩阵的行列式
{
    assert(width==height);
    double result=1;
    double k;
    Matrix m=*this;
    for(int i=0;i<height-1;i++){//Gauss消去法，变换成上三角矩阵
        for(int j=i+1;j<height;j++){
            k=m[j][i]/m[i][i];
            m[j][i]=0;
            for(int n=i+1;n<width;n++){
                m[j][n]=m[j][n]-k*m[i][n];
            }
        }
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(i==j) result*=m[i][j];
        }
    }
    return result;
}
bool Matrix::isPtv()
{
    assert(width==height);//是方阵才可以计算
    bool result=true;
    Matrix m;
    for(int i=1;i<=height;i++){
        m=this->subMatrix(i);
        if(m.Arg()<=0){
            result=false;
            break;
        }
    }
    return result;
}
Matrix  Matrix::T()
{
    double * t=new double[width*height];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            *(t+height*j+i)=*(p+width*i+j);
        }
    }
    Matrix m(t,height,width);
    delete [] t;
    return m;
}
Matrix Matrix::operator +(const Matrix &m1) const
{
    assert(m1.height==height && m1.width==width);
    int tmpHeight=m1.height;
    int tmpWidth=m1.width;
    double * t=new double[tmpWidth*tmpHeight];
    for(int i=0;i<tmpHeight;i++){
        for(int j=0;j<tmpWidth;j++){
            *(t+tmpWidth*i+j)=*(m1.p+tmpWidth*i+j)+*(p+tmpWidth*i+j);
        }
    }
    Matrix m(t,tmpWidth,tmpHeight);
    delete [] t;
    return m;
}
Matrix Matrix::operator -(const Matrix &m1) const
{
    assert(m1.height==height && m1.width==width);
    int tmpHeight=m1.height;
    int tmpWidth=m1.width;
    double * t=new double[tmpWidth*tmpHeight];
    for(int i=0;i<tmpHeight;i++){
        for(int j=0;j<tmpWidth;j++){
            *(t+tmpWidth*i+j)=*(p+tmpWidth*i+j)-*(m1.p+tmpWidth*i+j);
        }
    }
    Matrix m(t,tmpWidth,tmpHeight);
    delete [] t;
    return m;
}
Matrix Matrix::operator *(const Matrix &m1) const
{
    if(!this->isVector() && m1.isVector()){//左为数,右为矩阵
        Matrix m;
        m=p[0]*m1;
        return m;
    }else if(this->isVector() && !m1.isVector()){//左为矩阵,右为数
        Matrix m;
        m=*this*m1[0][0];
        return m;
    }else if(!this->isVector() && m1.isVector()){//左右都为数
        double * t=new double[1];
        t[0]=p[0]*m1[0][0];
        Matrix m(t,1,1);
        delete [] t;
        return m;
    }else if(this->isVector() && m1.isVector() && width==m1.height){//左为矩阵,右为矩阵
        double sum;
        double * t=new double[height*m1.width];
        for(int i=0;i<height;i++){
            for(int j=0;j<m1.width;j++){
                sum=0;
                for(int k=0;k<width;k++){
                    sum+=(*(p+width*i+k))*(m1[k][j]);
                }
                *(t+m1.width*i+j)=sum;
            }
        }
        Matrix m(t,m1.width,height);
        delete [] t;
        return m;
    }else{
        assert(0);//未知运算
        return *this;
    }
}
Matrix operator*(double alpha,const Matrix & m1)
{
    Matrix m=m1;
    for(int i=0;i<m.height;i++){
        for(int j=0;j<m.width;j++){
            m[i][j]=alpha*m1[i][j];
        }
    }
    return m;
}
Matrix Matrix::operator*(double alpha) const
{
    return alpha*(*this);
}
Matrix Matrix::operator+=(Matrix & m)
{
    return *this+m;
}
Matrix Matrix::operator-=(Matrix & m)
{
    return *this-m;
}
Matrix Matrix::operator *=(double alpha)
{
    return *this*alpha;
}
Matrix sqrt(Matrix m)
{
    m[0][0]=sqrt(m[0][0]);
    return m;
}
double abs(Matrix & m)
{
    double sum=0;
    for(int i=0;i<m.height;i++){
        for(int j=0;j<m.width;j++){
            sum+=m[i][j]*m[i][j];
        }
    }
    return sqrt(sum);
}
Matrix Matrix::operator /(Matrix &m1)
{
    assert(m1.width==1 && m1.height==1);
    return *this/m1[0][0];
}
Matrix Matrix::operator /(double sub) const
{
    Matrix m=*this;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            m[i][j]=*(p+width*i+j)/sub;
        }
    }
    return m;
}
Matrix& Matrix::operator=(Matrix m)
{
    if(&m==this) return *this;
    height=m.height;
    width=m.width;
    delete [] p;
    p=new double[height*width];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            *(p+width*i+j)=*(m.p+width*i+j);
        }
    }
    return *this;
}
double* Matrix::operator [](int heightPos)
{
    assert(heightPos>=0 && heightPos<height);
    return p+width*heightPos;
}
const double* Matrix::operator [](int heightPos) const
{
    assert(heightPos>=0 && heightPos<height);
    return p+width*heightPos;
}
ostream & operator<<(ostream & os,Matrix & m)
{
    os<<"Matrix:height="<<m.height<<endl;
    os<<"Matrix:width="<<m.width<<endl;
    for(int i=0;i<m.height;i++){
        for(int j=0;j<m.width;j++){
            os<<m[i][j]<<" "; 
        } 
        os<<endl;
    }
    return os;
}
Matrix::~Matrix(void)
{
    delete [] p;
}