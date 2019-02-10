#ifndef Tree_H
#define Tree_H

#include <vector>
using namespace std;

vector<double> mean_2d_vector(vector<vector<auto>> v);
void test_tmax(int N,int t_max_min,int t_max_max, int epochs);
void test_growth(int N,int epochs);
void test_nb_flip_restart(int N,int epochs);
void test_nb_flip(int N,int epochs);
void test_no_change(int N,int epochs);
void test_p(int N,int epochs);

#endif