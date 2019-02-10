#include <iostream>
#include <fstream>
#include <vector>
#include "project.h"
using namespace std;


vector<double> mean_2d_vector(vector<vector<auto>> v)
{
    vector<double> results;
    double somme=0;
    for (int j=0;j<v[0].size();j++)
    {
        somme=0;
        for (int i=0;i<v.size();i++)
        {
            somme+=v[i][j];
        }
        results.push_back(somme/v.size());
    }
    return results;
}

///////////////////////////////
// RLS
void test_nb_flip(int N,int epochs)
{
    ofstream myfile;
    myfile.open ("test.csv");
    vector<double> tmp;
    for (int nb_flip=1;nb_flip<8;nb_flip+=1)
    {
        vector<vector<double>> results;
        for (int i=0;i<20;i++)
        {
            tmp=RLS(N,epochs,nb_flip);
            results.push_back(tmp);
        }
        tmp=mean_2d_vector(results);
        myfile << nb_flip << ";";
        for (int i=0;i<tmp.size();i++)
        {
            myfile << tmp[i]<<";";
        }
        myfile <<"\n";
    }
    myfile.close();
}


///////////////////////////////
// RLS Restart

void test_nb_flip_restart(int N,int epochs)
{
    ofstream myfile;
    myfile.open ("test.csv");
    vector<double> tmp;
    vector<int> restart_list = {-1,2,7,12,17};
    for (int restart : restart_list)
    {
        vector<vector<double>> results;
        for (int i=0;i<20;i++)
        {
            tmp=RLS_restart(N,epochs,restart,101);
            results.push_back(tmp);
        }
        tmp=mean_2d_vector(results);
        myfile << restart << ";";
        for (int i=0;i<tmp.size();i++)
        {
            myfile << tmp[i]<<";";
        }
        myfile <<"\n";
    }
    myfile.close();
}

void test_no_change(int N,int epochs)
{
    ofstream myfile;
    myfile.open ("test.csv");
    vector<double> tmp;
    for (int no_change=1;no_change<5;no_change++)
    {
        vector<vector<double>> results;
        for (int i=0;i<20;i++)
        {
            tmp=RLS_restart(N,epochs,2,no_change*101);
            results.push_back(tmp);
        }
        tmp=mean_2d_vector(results);
        myfile << no_change*101 << ";";
        for (int i=0;i<tmp.size();i++)
        {
            myfile << tmp[i]<<";";
        }
        myfile <<"\n";
    }
    myfile.close();
}


////////////////////////////////
// EA

void test_p(int N,int epochs)
{
    ofstream myfile;
    myfile.open ("test.csv");
    vector<double> tmp;
    vector<double> p_list={0,20,40,60,-1};
    for (double p :p_list)
    {
        vector<vector<double>> results;
        for (int i=0;i<20;i++)
        {
            if (p==-1)
            {
                tmp=RLS(N,epochs,1);
                results.push_back(tmp);
            }
            else
            {
                tmp=EA(N,1/(N-p),epochs);
                results.push_back(tmp);
            }
        }
        tmp=mean_2d_vector(results);
        myfile << p << ";";
        for (int i=0;i<tmp.size();i++)
        {
            myfile << tmp[i]<<";";
        }
        myfile <<"\n";
    }
    myfile.close();
}


////////////////////////////////
// Simulated Anealing

void test_tmax(int N,int t_max_min,int t_max_max, int epochs)
{
    ofstream myfile;
    myfile.open ("test.csv");
    vector<double> tmp;
    for (int t_max=t_max_min;t_max<t_max_max;t_max+=4)
    {
        vector<vector<double>> results;
        for (int i=0;i<20;i++)
        {
            tmp=simulated_annealing(N,epochs,t_max,"log");
            results.push_back(tmp);
        }
        tmp=mean_2d_vector(results);
        myfile << t_max << ";";
        for (int i=0;i<tmp.size();i++)
        {
            myfile << tmp[i]<<";";
        }
        myfile <<"\n";
    }
    myfile.close();
}

void test_growth(int N,int epochs)
{
    ofstream myfile;
    myfile.open ("test.csv");
    vector<double> tmp;
    vector<string> growth_list ={"linear","log","exp"};
    for (string growth : growth_list)
    {
        vector<vector<double>> results;
        for (int i=0;i<20;i++)
        {
            tmp=simulated_annealing(N,epochs,22,growth);
            results.push_back(tmp);
        }
        tmp=mean_2d_vector(results);
        for (int i=0;i<tmp.size();i++)
        {
            myfile << tmp[i]<<";";
        }
        myfile <<"\n";
    }
    myfile.close();
}