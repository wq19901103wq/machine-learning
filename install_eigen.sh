#! /bin/sh 

#install boost
wget http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.bz2/download
tar -jxvf  download -C /opt
cd /opt/boost*
sh ./bootstrap.sh
./b2
./b2 install --prefix=/usr/local

#install eigen
wget http://bitbucket.org/eigen/eigen/get/3.2.1.tar.bz2
tar -jxvf  3.2.1.tar.bz2 -C /usr/include
cd  /usr/include
mv eigen-* Eigen

