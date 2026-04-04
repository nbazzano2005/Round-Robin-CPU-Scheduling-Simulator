#include "simulate.hpp"
#include "Scheduler.hpp" 
#include "Process.hpp"
#include <vector>
#include <chrono>
#include <cassert>
using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{
    assert(sched != nullptr);
    const int SLICE = 10;

    vector<Process*> cpu;
    vector<Process*> io;
    cpu.reserve(numCPUBound);
    io.reserve(numIOBound);

    int nextID = 1;
    for (int i = 0; i < numCPUBound; ++i) {
        auto* p = new CPUBoundProcess(nextID++);
        cpu.push_back(p);
        sched->addProcess(p);
    }
    for (int i = 0; i < numIOBound; ++i) {
        auto* p = new IOBoundProcess(nextID++);
        io.push_back(p);
        sched->addProcess(p);
    }

    long long sched_calls = 0;
    auto t0 = chrono::system_clock::now();

    int cycles = 0;
    while (cycles < numCycles) {
        Process* p = sched->popNext(cycles);
        ++sched_calls;

        if (p == nullptr) {
            cycles += SLICE; 
            continue;
        }

        int used = p->useCPU(cycles, SLICE);

        if (used > 0) {
            cycles += used;
            
            sched->addProcess(p);
        } else {
            
            cycles += 1;
        }
    }

    chrono::system_clock::time_point t1 = chrono::system_clock::now();
    long long dur_ns = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    double ns_per_call;
    if (sched_calls > 0) {
        ns_per_call = (double)dur_ns / (double)sched_calls;
    } else {
        ns_per_call = 0.0;
    }

    double cpu_avg_cpu_time = 0.0;
    double cpu_avg_wait_time = 0.0;
    double io_avg_cpu_time = 0.0;
    double io_avg_wait_time = 0.0;

    if (!cpu.empty()) {
        long long sum = 0;
        for (int i = 0; i < cpu.size(); i++) {
            sum += cpu[i]->getCPUTime();
        }
        cpu_avg_cpu_time = (double)sum / (double)cpu.size();
        
        sum = 0;
        for (int i = 0; i < cpu.size(); i++) {
            sum += cpu[i]->getWaitTime(cycles);
        }
        cpu_avg_wait_time = (double)sum / (double)cpu.size();
    }

    if (!io.empty()) {
        long long sum = 0;
        for (int i = 0; i < io.size(); i++) {
            sum += io[i]->getCPUTime();
        }
        io_avg_cpu_time = (double)sum / (double)io.size();
        
        sum = 0;
        for (int i = 0; i < io.size(); i++) {
            sum += io[i]->getWaitTime(cycles);
        }
        io_avg_wait_time = (double)sum / (double)io.size();
    }

    double* out = new double[5];
    out[0] = ns_per_call;
    out[1] = cpu_avg_cpu_time;
    out[2] = cpu_avg_wait_time;
    out[3] = io_avg_cpu_time;
    out[4] = io_avg_wait_time;

    
    for (auto* p : cpu) delete p;
    for (auto* p : io) delete p;

    return out;
}
