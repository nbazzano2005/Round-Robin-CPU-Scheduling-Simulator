#include "Process.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;


// constructor: make a process with a given ID.
// starts with 0 cpuTime, 0 waitTime, and 0 lastTime .
Process::Process(int id) : id(id), cpuTime(0), waitTime(0), lastTime(0) {}



// Input : none
// Effect: none 
// Return: this process's unique integer ID.
int Process::getID() const
{
   return id;
}


// Input : none
// Effect: none 
// Return: total number of CPU cycles this process has actually used so far
int Process::getCPUTime() const
{
   return cpuTime;
}


// Input : curCycleNum = the current simulated cycle 
// Effect: none
// Return: the total time this process has been ready but waiting up to now.
//         In this implementation we store the past wait time in waitTime,
//         and add the current waiting since lastTime.
int Process::getWaitTime(int curCycleNum) const
{
   return waitTime + (curCycleNum - lastTime);
}

// constructor: make a CPU-bound process with the given id
// Input : id
// Effect: calls base Process ctor; no extra fields to set here
CPUBoundProcess::CPUBoundProcess(int id) : Process(id) {}


// Input : curCycleNum 
// Effect: none
// Return: false .
bool CPUBoundProcess::isBlocked(int curCycleNum) const
{
   return false; 
}


// Input : curCycleNum = cycle when the time slice starts
//         sliceSize   = max cycles we are allowed to run this turn
// Effect: consumes the full slice on the CPU 
//         adds to cpuTime, and advances lastTime by sliceSize.
// Return: number of cycles actually used 
int CPUBoundProcess::useCPU(int curCycleNum, int sliceSize)
{
   cpuTime += sliceSize;
   lastTime = curCycleNum + sliceSize;
   return sliceSize; // uses full slice
}



// constructor: makes an IO-bound process with the given id and default I/O behavior
// Input : id
// Effect: sets up burst/IO timing ranges and internal counters
IOBoundProcess::IOBoundProcess(int id)
    : Process(id), minBurst(1), maxBurst(10), minIO(5), maxIO(20),
      blockedUntil(0), remainingBurst(5) {}



// Input : curCycleNum = the time now
// Effect: none
// Return: true if this process is still waiting on I/O (blocked) at curCycleNum.
bool IOBoundProcess::isBlocked(int curCycleNum) const
{
   return curCycleNum < blockedUntil;
}



// Input : curCycleNum = when the CPU slice begins
//         sliceSize   = how many cycles we may run at most right now
// Effect:
//   - If currently blocked does nothing and uses 0 cycles
//   - Otherwise runs up to min(sliceSize, remainingBurst)
//   - Updates cpuTime, remainingBurst, and lastTime
//   - If the CPU burst finishes it schedules an I/O wait
//     by setting blockedUntil and reset remainingBurst for next time
// Return: number of CPU cycles actually used this call 
int IOBoundProcess::useCPU(int curCycleNum, int sliceSize)
{
   if (isBlocked(curCycleNum))
      return 0;

   int used;
if (sliceSize < remainingBurst) {
    used = sliceSize;
} else {
    used = remainingBurst;
}
cpuTime += used;
remainingBurst -= used;
lastTime = curCycleNum + used;

   if (remainingBurst <= 0)
   {
      
      blockedUntil = curCycleNum + used + minIO; 
      remainingBurst = maxBurst;                
   }

   return used;
}
