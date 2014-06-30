#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <nodob.h>
#include <QDebug>
#include <cmath>
#include <list>
#include <vector>

using namespace std;

class FibonacciHeap
{
public:
    FibonacciHeap();
    void insert(FibonacciHeap &fh,NodoB *aNode);
    NodoB *findMin(NodoB &aNode);
    FibonacciHeap* unionHeap(FibonacciHeap &fh1,FibonacciHeap &fh2);
    void link(FibonacciHeap &fh,NodoB &a,NodoB &b);
    void consolidate(FibonacciHeap &fh);
    int nodes;
    NodoB *min;
    int getDegree(int nodes);
    //list<NodoB*> heap;
    NodoB *head;
    NodoB *extractMin(FibonacciHeap *fh);
};

#endif // FIBONACCIHEAP_H
