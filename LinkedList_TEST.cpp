#include "LinkedList.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
    LinkedList<int> L;
    L.pushBack(1);
    L.pushBack(2);
    L.pushFront(0); 
    cout<<"Front="<<L.getFront()<<" Back="<<L.getBack()<<" Size="<<L.getSize()<< endl;
    L.insert(1,99); 
    cout<<"After insert idx1: "<<L.getItem(0)<<" "<<L.getItem(1)<<" "<<L.getItem(2)<<" "<<L.getItem(3)<< endl;
    L.remove(2);    
    cout<<"After remove idx2: "<<L.getItem(0)<<" "<<L.getItem(1)<<" "<<L.getItem(2)<< endl;
    L.popFront();   
    L.popBack();    
    cout<<"Remaining: "<<L.getItem(0)<<" size="<<L.getSize()<< endl;

    LinkedList<string> S;
    S.pushBack("a"); S.pushBack("b"); S.pushFront("z"); 
    S.setItem(1,"A"); 
    cout<<"Strings: "<<S.getItem(0)<<" "<<S.getItem(1)<<" "<<S.getItem(2)<< endl;
    return 0;
}
