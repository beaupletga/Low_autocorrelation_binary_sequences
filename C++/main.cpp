#include "test.h"
#include "project.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // vector<double> tmp;
    // auto start = std::chrono::high_resolution_clock::now();
    // tmp=EA(101,(double)1/101,10000);
    // tmp=simulated_annealing(101,1000000,25,"log");
    // cout<<"Last solution : "<<tmp.back()<<endl;
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = finish - start;
    // std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    // display_vector(tmp);

    // tmp=RLS_restart(101, 100000, 2, 404);
    // write_in_csv(tmp,"test.csv");

    // vector<vector<int>> tmp;
    // tmp[0].push_back(1);

    // SA
    // test_tmax(101,10,40,10000);
    // test_growth(101,50000);

    // RLS Restart
    // test_nb_flip_restart(101,10000);
    // test_no_change(101,10000);

    // RLS
    test_nb_flip(101,100000);

    // EA
    // test_p(101,10000);
    return 0;
}