#include "simulate.hpp"
#include "simulate.cpp"
#include "Scheduler.hpp"
#include "Scheduler.cpp"
#include "Process.hpp"
#include "Process.cpp"
#include "LinkedList.hpp"
#include "LinkedListNode.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;


static void write_csv_row(const string& label, int nCPU, int nIO, int cycles, const double* r) {
    
    double ratio;
    if (r[1] != 0.0) {
        ratio = r[3] / r[1];
    } else {
        ratio = 0.0;
    }
    cout << label << "," << nCPU << "," << nIO << "," << cycles << ","
        << r[0] << "," << r[1] << "," << r[2] << "," << r[3] << "," << r[4] << "," << ratio << endl;
}


static double* run_one(Scheduler* s, int nCPU, int nIO, int cycles) {
    return simulate(s, nCPU, nIO, cycles); 
}

int main(int argc, char** argv)
{
    

    if (argc >= 2 && string(argv[1]) == "--series") {
       
        int numIO;
        if (argc >= 3) {
            numIO = atoi(argv[2]);
        } else {
            numIO = 10;
        }
        int cycles;
        if (argc >= 4) {
            cycles = atoi(argv[3]);
        } else {
            cycles = 1000000;
        }

        vector<int> CPUvals = {2000,3000,4000,5000,6000,7000,8000,9000,10000};

        
        vector<Scheduler*> scheds;
        vector<string> labels;
        scheds.push_back(new RoundRobin());
        labels.push_back("Round Robin (Array List)");
        scheds.push_back(new FastRoundRobin());
        labels.push_back("Round Robin (Linked List)");

        for (int i = 0; i < CPUvals.size(); ++i) {
            int nCPU = CPUvals[i];
            cout << "Running tests for nCPU=" << nCPU << "..." << endl;
            for (size_t i = 0; i < scheds.size(); ++i) {
                cout << "  Testing " << labels[i] << "..." << endl;
                double* r = run_one(scheds[i], nCPU, numIO, cycles);
                write_csv_row(labels[i], nCPU, numIO, cycles, r);
                delete[] r;
            }
            cerr << "Finished nCPU=" << nCPU << endl;
        }

        
        for (int i = 0; i < scheds.size(); ++i) {
            delete scheds[i];
        }

        cout << "Completed analysis ("
             << CPUvals.front() << " .. " << CPUvals.back()
             << ", IO=" << numIO << ", cycles=" << cycles << ")." << endl;
        return 0;
    }

   
    if (argc != 4) {
        cerr << "Usage:" << endl
             << "  " << argv[0] << " <numCPUBound> <numIOBound> <numCycles>" << endl
             << "  " << argv[0] << " --series [numIOBound] [numCycles]" << endl;
        return 1;
    }

    int numCPUBound = atoi(argv[1]);
    int numIOBound  = atoi(argv[2]);
    int numCycles   = atoi(argv[3]);

    Scheduler* schedArr[] = { new RoundRobin(), new FastRoundRobin() };
    string labels[] = { "Round Robin (Array List)", "Round Robin (Linked List)" };

    for (int i = 0; i < 2; ++i)
    {
        double* results = simulate(schedArr[i], numCPUBound, numIOBound, numCycles);
        cout << "=== " << labels[i] << " ===" << endl;
        cout << "Time per scheduler call: " << results[0] << endl;
        cout << "CPU-bound avg CPU time: " << results[1] << endl;
        cout << "CPU-bound avg WAIT time: " << results[2] << endl;
        cout << "IO-bound  avg CPU time: " << results[3] << endl;
        cout << "IO-bound  avg WAIT time: " << results[4] << endl << endl;
        delete[] results;
        delete schedArr[i];
    }
    return 0;
}


