#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <nodob.h>
#include <QDebug>
#include <cmath>
#include <list>
#include <vector>
#include <QFile>

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
    void exchange(NodoB &x,NodoB &y);
    void cut(FibonacciHeap &fh,NodoB &x, NodoB &y);
    void cascadingCut(FibonacciHeap &fh,NodoB &y);
    void decreaseKey(FibonacciHeap &fh,NodoB &x,int k);
    NodoB *bfs(NodoB &b, int value);
    NodoB *findNode(NodoB &b,int value);
    NodoB *deleteNode(FibonacciHeap &fh,int target);

    void fibonacciHeap2file(FibonacciHeap &bh);
    void bfsPrint(NodoB &aNode);

    QFile *file;
    QTextStream *out;


};

#endif // FIBONACCIHEAP_H
