#include "Scheduler.cpp"
#include "Process.cpp"
#include <iostream>
using namespace std;

int main() {
    cout << "Running CompletelyFair scheduler test..." << endl;

    CompletelyFair cf;

    // Create processes with different IDs
    CPUBoundProcess* p1 = new CPUBoundProcess(10); // Higher ID
    CPUBoundProcess* p2 = new CPUBoundProcess(5);  // Lower ID
    CPUBoundProcess* p3 = new CPUBoundProcess(15); // Highest ID

    // Add them to scheduler
    cf.addProcess(p1);
    cf.addProcess(p2);
    cf.addProcess(p3);

    int cycle = 0;
    
    // Give p2 (ID=5) some CPU time first
    p2->useCPU(cycle, 20);
    cycle += 20;

    // Now test scheduler - should pick process with least CPU time (p1 or p3)
    Process* selected = cf.popNext(cycle);
    
    cout << "Selected process ID: " << selected->getID() << endl;
    cout << "Process CPU times - p1: " << p1->getCPUTime() 
         << ", p2: " << p2->getCPUTime() 
         << ", p3: " << p3->getCPUTime() << endl;

    if (selected->getID() == 5) {
        cout << "❌ Test FAILED: Selected process with most CPU time (old behavior)" << endl;
        cout << "The scheduler is still using process ID instead of CPU time!" << endl;
    } else {
        cout << "✅ Test PASSED: Selected process with least CPU time" << endl;
        cout << "CompletelyFair scheduler is working correctly!" << endl;
    }

    // Clean up
    cf.addProcess(selected); // Put it back for cleanup
    delete p1;
    delete p2; 
    delete p3;

    return 0;
}