#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "List.hpp"
#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "Process.hpp"


class Scheduler {
public:
    virtual ~Scheduler() {}
    virtual void addProcess(Process* proc) = 0;
    virtual Process* popNext(int curCycle) = 0;
};

// Round Robin - List backed queue 
class RoundRobin : public Scheduler {
protected:
    List<Process*>* procQueue;

public:
    RoundRobin();
    virtual ~RoundRobin();  

    virtual void addProcess(Process* proc);
    virtual Process* popNext(int curCycle);
};

// FastRoundRobin
class FastRoundRobin : public RoundRobin {
public:
    FastRoundRobin();
    virtual ~FastRoundRobin() {}
};

// CompletelyFair
class CompletelyFair : public Scheduler {
private:
    List<Process*>* procQueue;

public:
    CompletelyFair();
    virtual ~CompletelyFair();

    virtual void addProcess(Process* proc);
    virtual Process* popNext(int curCycle);
};

#endif

