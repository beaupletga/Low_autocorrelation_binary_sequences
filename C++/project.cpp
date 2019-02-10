#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <iterator>
#include <string>
#include "test.h"
#include <time.h> //Ne pas oublier d'inclure le fichier time.h
// #include "Tree.h"
using namespace std;

void display_vector(const vector<auto> v)
{
    for (int i=0;i<v.size();i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int correlations(const vector<int> sequence,const int k)
{
    int sum=0;
    for (int i=0;i<sequence.size()-k;i++)
    {
        sum+=sequence[i]*sequence[i+k];
    }
    return sum;
}

int energy(const vector<int> sequence)
{
    int sum=0;
    for (int k=1;k<sequence.size();k++)
    {
        sum+=pow(correlations(sequence,k),2);
    }
    return sum;
}

vector<int> generate_sequence(const int N)
{
    vector<int> sequence;
    for (int i=0;i<N;i++)
    {
        if ((double)(rand()%100)/100<0.5){
            sequence.push_back(-1);
        }
        else{
            sequence.push_back(1);
        }
    }
    return sequence;
}

float merit_factor(const vector<int> sequence)
{
    return pow(sequence.size(),2)/(2*energy(sequence));
}

vector<int> sbm(vector<int> sequence,int nb_flip)
{
    for (int i=0;i<nb_flip;i++)
    {
        int index = rand() % sequence.size();
        sequence[index]*=-1;
    }
    return sequence;
}

vector<double> RLS(int N, int epochs,int nb_flip)
{
    vector<double> history;
    vector<int> x=generate_sequence(N);
    double fx=merit_factor(x);
    vector<int> y;
    double fy;
    for (int i=0;i<epochs;i++)
    {
        y=sbm(x,nb_flip);
        fy=merit_factor(y);
        if (fy>=fx){
            x=y;
            fx=fy;
        }
        history.push_back(fx);
    }
    return history;
}

vector<double> RLS_restart(int N, int epochs, int restart,int no_change_threshold)
{
    vector<double> history;
    vector<int> x=generate_sequence(N);
    double fx=merit_factor(x);
    vector<int> y;
    double fy;
    int no_change=0;
    for (int i=0;i<epochs;i++)
    {
        y=sbm(x,1);
        fy=merit_factor(y);
        if (fy>=fx){
            x=y;
            fx=fy;
        }
        else if (fy<fx)
        {
            no_change++;
            if (no_change==no_change_threshold){
                if (restart==-1){
                    x=generate_sequence(N);
                }
                else{
                    for (int j=0;j<restart;j++)
                    {
                        int random=rand()%x.size();
                        x[random]*=-1;
                    }
                    fx=merit_factor(x);
                    no_change=0;
                }
            }
        }
        history.push_back(fx);
    }
    return history;
}

vector<double> EA(int N, double p, int epochs)
{
    vector<double> history;
    vector<int> x=generate_sequence(N);
    double fx=merit_factor(x);
    vector<int> y;
    double fy;
    for (int i=0;i<epochs;i++)
    {
        y=x;
        for (int j=0;j<x.size();j++)
        {
            double random=(double)(rand()%1000)/1000;
            if (random<p){
                y[j]*=-1;
            }
        }
        fy=merit_factor(y);
        if (fy>=fx){
            x=y;
            fx=fy;
        }
        history.push_back(fx);
    }
    return history;
}


vector<double> simulated_annealing(int N, int epochs, double t_max, string t_growth)
{
    vector<double> history;
    vector<int> x=generate_sequence(N);
    double fx=merit_factor(x);
    vector<int> y;
    double fy;
    double t=1;
    double best_solution=0;
    vector<int> best_solution_sequence;
    double step=0;
    double random;
    for (int i=0;i<epochs;i++)
    {
        y=sbm(x,1);
        fy=merit_factor(y);
        random=(double)(rand()%1000)/1000;
        // cout<<random<<endl;
        if (fy>=fx)
        {
            x=y;
            fx=fy;
            if (fy>best_solution)
            {
                best_solution=fy;
                best_solution_sequence=y;
            }
        }
        else if (random<exp((fy-fx)*t))
        {
            x=y;
            fx=fy;
        }

        if (t_growth=="linear")
        {
            t+=t_max/epochs;
        }
        else if (t_growth=="exp")
        {
            step+=log(t_max)/epochs;
            t=exp(step);
        }
        else if (t_growth=="log")
        {
            if (step<1){
                step=1;
            }
            step+=exp(t_max)/epochs;
            t=log(step);
        }
        history.push_back(fx);
    }
    // cout<<"Best solution : "<<best_solution<<" "<<t<<endl;
    return history;
}

void write_in_csv(vector<double> v, string filename)
{
    ofstream output_file(filename);
    ostream_iterator<double> output_iterator(output_file, "\n");
    copy(v.begin(), v.end(), output_iterator);
}

