#include "Scheduler.cpp"

#include "Process.cpp"
#include <iostream>
using namespace std;

int main() {

	cout << " Running RoundRobin smoke test " << endl;

    RoundRobin rr;

    CPUBoundProcess*  c1 = new CPUBoundProcess(1);
    CPUBoundProcess*  c2 = new CPUBoundProcess(2);
    IOBoundProcess*   io = new IOBoundProcess(3);

    rr.addProcess(c1);
    rr.addProcess(c2);
    rr.addProcess(io);

    int cycle = 0;

    
    while (!io->isBlocked(cycle)) {
        io->useCPU(cycle, 10);
        cycle += 10;
    }

	cout << " IO process blocked at cycle " << cycle << endl;
    Process* p = rr.popNext(cycle);
    if (!p || p->getID() != 1) {
        cout << " 1st Test failed " << endl;
        delete c1; delete c2; delete io;
        return 1;
    }
    rr.addProcess(p);

	cout << " Returned process " << p->getID() << endl;

    p = rr.popNext(cycle);
    if (!p || p->getID() != 2) {
        cout << " 2nd Test failed "  << endl;
        delete c1; delete c2; delete io;
        return 1;
    }
    rr.addProcess(p);

	cout << " Returned process " << p->getID() << endl;

    
    p = rr.popNext(cycle);
    if (p == nullptr || (p->getID() != 1 && p->getID() != 2)) {
        cout << " 3rd Test failed " << endl;
        delete c1; delete c2; delete io;
        return 1;
    }
    cout << " Got process " << p->getID() << endl;

	
    delete c1;
    delete c2;
    delete io;

    cout << " RoundRobin test completed successfully." << endl;
    return 0;
}

