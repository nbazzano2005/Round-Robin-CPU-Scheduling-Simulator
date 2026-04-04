#include "Scheduler.hpp"
#include <climits>

// RoundRobin

RoundRobin::RoundRobin() {
    procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin() {
    delete procQueue;
    procQueue = nullptr;
}

void RoundRobin::addProcess(Process* proc) {
    procQueue->pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle) {
    int n = procQueue->getSize();
    for (int i = 0; i < n; ++i) {
        Process* p = procQueue->getFront();
        procQueue->popFront();
        if (!p->isBlocked(curCycle)) {
            return p; 
        }
        procQueue->pushBack(p); 
    }
    return nullptr; 
}

// FastRoundRobin 

FastRoundRobin::FastRoundRobin() {
    // Replace the ArrayList with a LinkedList for better performance
    delete procQueue;
    procQueue = new LinkedList<Process*>();
}

// CompletelyFair 

CompletelyFair::CompletelyFair() {
    procQueue = new ArrayList<Process*>();
}

CompletelyFair::~CompletelyFair() {
    delete procQueue;
    procQueue = nullptr;
}

void CompletelyFair::addProcess(Process* proc) {
    procQueue->pushBack(proc);
}

Process* CompletelyFair::popNext(int curCycle) {
    // Select process with least CPU time for fairness
    Process* selectedProcess = nullptr;
    int selectedIndex = -1;
    int minCPUTime = INT_MAX;

    // Find the process with minimum CPU time that is not blocked
    for (int i = 0; i < procQueue->getSize(); ++i) {
        Process* p = procQueue->getItem(i);
        if (!p->isBlocked(curCycle)) {
            if (p->getCPUTime() < minCPUTime) {
                minCPUTime = p->getCPUTime();
                selectedProcess = p;
                selectedIndex = i;
            }
        }
    }

    
    if (selectedProcess != nullptr) {
        procQueue->remove(selectedIndex);
        return selectedProcess;
    }

    return nullptr; 
}
