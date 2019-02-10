#ifndef project_H
#define project_H
#include <vector>
#include <string>
using namespace std;


vector<double> simulated_annealing(int N, int epochs, double t_max, string t_growth);
vector<double> RLS_restart(int N, int epochs, int restart,int no_change_threshold);
vector<double> RLS(int N, int epochs,int nb_flip);
vector<double> EA(int N, double p, int epochs);

#endif