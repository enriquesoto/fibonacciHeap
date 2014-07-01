#include <QtCore/QCoreApplication>
#include <QDebug>
#include <fibonacciheap.h>
#include <nodob.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FibonacciHeap *fh1 = new FibonacciHeap;

    NodoB *aNode=new NodoB();
    aNode->setKey(5);
    NodoB *aNode1=new NodoB();
    aNode1->setKey(25);
    NodoB *aNode2=new NodoB();
    aNode2->setKey(15);

    fh1->insert(*fh1,aNode);
    qDebug()<<"insert 5";
    fh1->insert(*fh1,aNode1);
    qDebug()<<"insert 25";
    fh1->insert(*fh1,aNode2);
    qDebug()<<"insert 15";

    //fh1->link(*fh1,*aNode2,*aNode); //segundo es el menor

    NodoB *bNode=new NodoB();
    bNode->setKey(3);
    NodoB *bNode1=new NodoB();
    bNode1->setKey(9);
    NodoB *bNode2=new NodoB();
    bNode2->setKey(8);

    FibonacciHeap *fh2 = new FibonacciHeap();

    fh2->insert(*fh2,bNode);
    qDebug()<<"insert 3";
    fh2->insert(*fh2,bNode1);
    qDebug()<<"insert 9";
    fh2->insert(*fh2,bNode2);
    qDebug()<<"insert 8";



    //fh2->link(*fh2,*bNode2,*bNode);

    FibonacciHeap *fh = fh1->unionHeap(*fh1,*fh2);
    //FibonacciHeap *fh
    //fh1->consolidate(*fh1);
    fh->extractMin(fh);

   // int grado = fh1->getDegree(14);


    qDebug()<<"xD";

    return a.exec();
}
