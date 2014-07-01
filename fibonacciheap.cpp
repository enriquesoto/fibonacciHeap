#include "fibonacciheap.h"

FibonacciHeap::FibonacciHeap()
{
    this->nodes = 0;
    this->min=NULL;

}

void FibonacciHeap::insert(FibonacciHeap &fh, NodoB *aNode)
{
    if (this->min == NULL){
        //fh.heap.push_front(aNode);
        this->min = aNode;
        //fh.head = aNode;
        return;
    }
    else {

        //fh.heap.push_front(aNode);
        this->min->siblingIzq->siblingDer = aNode;
        aNode->siblingIzq = this->min->siblingIzq;
        aNode->siblingDer = this->min;
        this->min->siblingIzq = aNode;
    }


    if(this->min==NULL || aNode->key < this->min->key){
        this->min = aNode;
    }
    this->nodes = this->nodes + 1;
}



NodoB *FibonacciHeap::findMin(NodoB &aNode)
{
    //myIterator it= heap.begin();
    NodoB *ith = &aNode;
    NodoB *itNexth;
    NodoB *minTemp;
    int min= aNode.key;


    ith = &aNode;
    minTemp = &aNode;
    do{
        if(ith->key<min){
            //min = ith->key;
            minTemp = ith;
        }
        ith=ith->siblingDer;
    }while(ith!=&aNode);

//    while(ith){
//        if(ith->key<min){
//            //min = ith->key;
//            minTemp = ith;
//        }
//        ith = ith->siblingDer;
//    }

//    for(;heap.end();it++){
//        if(*it.key<min){
//            min = *it.key;
//            minTemp = &(*it);
//        }
//    }
    return minTemp;
}

FibonacciHeap * FibonacciHeap::unionHeap(FibonacciHeap &fh1, FibonacciHeap &fh2)
{
    FibonacciHeap *fh = new FibonacciHeap();
    fh->min = fh1.min;


    fh2.min->siblingIzq->siblingDer = fh1.min->siblingDer;
    fh1.min->siblingDer->siblingIzq = fh2.min->siblingIzq;


    fh1.min->siblingDer = fh2.min;
    fh2.min->siblingIzq = fh1.min;
    //&fh2=NULL;
    if(fh1.min->key == NULL || (fh2.min->key != NULL && fh2.min->key < fh1.min->key)){
        fh->min = fh2.min;
    }
    fh->nodes = fh1.nodes + fh2.nodes;

    return fh;

}

void FibonacciHeap::link(FibonacciHeap &fh, NodoB &a, NodoB &b) //y,x
{
    a.parent = &b;
    //b.child = a;
    a.siblingDer->siblingIzq = a.siblingIzq;
    a.siblingIzq->siblingDer = a.siblingDer;
    a.siblingDer = &a;  //:D
    a.siblingIzq = &a;

    if(b.child){
        //b.child->siblingDer->siblingIzq = &a; //observacion
        b.child->siblingIzq->siblingDer = &a;
        a.siblingDer = b.child;
        a.siblingIzq = b.child->siblingIzq;


        //a.siblingIzq=b.child->siblingDer;

        b.child->siblingIzq = &a;
        //b.child->siblingIzq->siblingDer=&a;
    }
    b.child = &a;

    b.degree ++;

    a.marked=false;

}

void FibonacciHeap::consolidate(FibonacciHeap &fh)
{
    int gradoMax = getDegree(fh.nodes)+1;
    vector<NodoB*> a(gradoMax);
    for(int i= 0; i<a.size();i++){
        a.at(i) = NULL;
    }
    NodoB *current = fh.min;

    do{
        NodoB *x=current; //w es current
        int grade=x->degree;

        while(a.at(grade)){

            NodoB *y = a.at(grade); //null

            if(x->key > y->key){
                if(y->key==8 && x->key==15){
                       qDebug()<<":D";
                       exchange(*x,*y);
                }

                link(fh,*y,*x);

//                if(fh.min == x){
//                    fh.min = y;
//                }
                //x=x->parent;
                //current =x;
            }
//            else{
//                link(fh,*y,*x); //segundo(x) es el menor
//                //x=x->parent; //actualizamos para q x se quede arriba
//                //current =x;
//                if(fh.min == y){
//                    fh.min = x;
//                }
//            }
            a.at(grade) = NULL;
            grade++;
            if(grade>a.size()-1)//mmm
                break;

        }
        if(grade<a.size())
            a.at(grade) = x;

        current=current->siblingDer;


    }while(current!=fh.min);


    fh.min = findMin(*fh.min);
    qDebug()<<"xD";

//    while(current!=fh.min){
//        NodoB *x=current; //w es current
//        int grade=x->degree;
//        while(a.at(grade)!=NULL){

//            NodoB *y = a.at(grade); //null

//            if(x->key > y->key){
//                link(fh,*x,*y);
//            }
//            else{
//                link(fh,*y,*x);
//            }
//            a.at(grade) = NULL;
//            grade++;

//        }
//        a.at(grade) = x;

//        current=current->siblingDer;

//    }
    //NodoB *minimo = findMin(fh.min);

    //fh.min==NULL;

//    for(int i=0; i<gradoMax;i++){
//        if(a.at(i) != NULL){

//        }
//    }

}

int FibonacciHeap::getDegree(int nodes)
{
    int index = ceil(log2(nodes));
    //qDebug()<<"degree";
    int a[]={1,1,2,3,5,8,13,21,34,55,89};
    return a[index-1];
}

NodoB *FibonacciHeap::extractMin(FibonacciHeap *fh)
{
    NodoB *z = fh->min;
    if(z!=NULL){
        if(z->child){
            NodoB *x=z->child->siblingDer;

            do{
                z->siblingIzq->siblingDer=x;
                x->siblingIzq->siblingDer=z->siblingDer;
                //z->siblingDer->siblingDer=z->siblingIzq;
                z->siblingDer->siblingIzq=x;

                x->siblingIzq = z->siblingIzq;
                x->parent = NULL;


                x=x->siblingDer;
                qDebug()<<"xD";

            }while(x->parent == z);

        }
        else{
            z->siblingIzq->siblingDer=z->siblingDer;
            z->siblingDer->siblingIzq=z->siblingIzq;
        }


        if(z==z->siblingDer)
            fh->min = NULL;
        else{
            fh->min=z->siblingDer;
            consolidate(*fh);
        }
        this->nodes--;
    }
    return z;
}

void FibonacciHeap::exchange(NodoB &x, NodoB &y)
{
    NodoB *tempNext = x.siblingDer;
    NodoB *tempPrev = x.siblingIzq;

    x.siblingDer=y.siblingDer;
    y.siblingIzq->siblingDer = &x;
    x.siblingIzq = y.siblingIzq;
    tempNext->siblingIzq = &y;
    y.siblingDer = tempNext;
    tempPrev->siblingDer=&y;
    y.siblingIzq=tempPrev;

    tempPrev->siblingIzq=&x;


}
