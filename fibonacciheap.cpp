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
        this->nodes = this->nodes + 1;
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
    NodoB *tempExchange;

    do{
        NodoB *x=current; //w es current
        int grade=x->degree;

        while(a.at(grade)){

            NodoB *y = a.at(grade); //null

            if(x->key > y->key){
                if(y->key==8 && x->key==15){
                       qDebug()<<":D";

                }
                if(y->child == fh.min)
                    fh.min = y;
                exchange(*x,*y);
                tempExchange=x;
                x=y;
                y=tempExchange;
                current =x;

//                if(fh.min == x){
//                    fh.min = y;
//                }
                //x=x->parent;
                //current =x;
            }

            link(fh,*y,*x);
//            else{
//                link(fh,*y,*x); //segundo(x) es el menor
//                //x=x->parent; //actualizamos para q x se quede arriba
//                //current =x;
//                if(fh.min == y){
//                    fh.min = x;
//                }
//            }
            if(x->child == fh.min)
                fh.min = x;
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

    if(x.siblingDer == &y || x.siblingIzq == &y){
//        y.siblingDer = y.siblingIzq;
//        x.siblingDer  = tempPrev;
//        tempPrev->siblingIzq = x;
//        tempNext->siblingIzq = tempPrev;

        //

        tempPrev->siblingDer = tempNext;
        tempNext->siblingIzq=tempPrev;
        tempPrev->siblingIzq= &x;
        x.siblingDer = tempPrev;
        x.siblingIzq=tempNext;
        tempNext->siblingDer = &x;
        return ;

    }

    x.siblingDer=y.siblingDer;
    y.siblingIzq->siblingDer = &x;
    x.siblingIzq = y.siblingIzq;
    tempNext->siblingIzq = &y;
    y.siblingDer = tempNext;
    tempPrev->siblingDer=&y;
    y.siblingIzq=tempPrev;

    tempPrev->siblingIzq=&x;


}

void FibonacciHeap::cut(FibonacciHeap &fh, NodoB &x,NodoB &y)
{
    NodoB *tempPrevX=x.siblingIzq;
    NodoB *tempNextX =x.siblingDer;
    x.siblingDer=&x;
    x.siblingIzq=&x;
    tempPrevX->siblingDer=tempNextX;
    tempNextX->siblingIzq=tempPrevX;
    x.parent = NULL;
    insert(fh,&x);
}

void FibonacciHeap::cascadingCut(FibonacciHeap &fh, NodoB &y)
{
    NodoB *z = y.parent;
    if(z){
        if(!y.marked){
            y.marked = true;
        }
        else{
            cut(fh,y,*z);
            cascadingCut(fh,*z);
        }
    }
}

void FibonacciHeap::decreaseKey(FibonacciHeap &fh, NodoB &x, int k)
{
    NodoB * y;

    if(k>x.key){
           qDebug()<<"error";
           return;
    }
    x.key = k;
    y=x.parent;
    if(y!=NULL && x.key < y->key){
        cut(fh,x,*y);
        cascadingCut(fh,*y);
    }
    if(x.key < fh.min->key){
        fh.min = &x;
    }
    return;

}

NodoB *FibonacciHeap::bfs(NodoB &b, int value)
{
    //NodoB *x=b.pChild.begin();
    NodoB *result=NULL;
    if(b.key == value) //preorder operation
        return &b;

        NodoB *child= b.child;

        if(!child) return NULL;

        do{
            result = bfs(*child,value);
            if(result) return result;
            child=child->siblingDer;
        }while(child != b.child);


    return result;

}

NodoB *FibonacciHeap::findNode(NodoB &b, int value)
{
    NodoB *currentNode = &b;
    NodoB *result=NULL;
    do{
        if(currentNode->key == value)
            return currentNode;

        result = bfs(*currentNode,value);
//        NodoB *child= currentNode->child;
//        do{
//            bfs(*child,value);
//            child=child->siblingDer;
//        }while(child == b.child);

        currentNode = currentNode->siblingDer;
    }while(currentNode!=&b);

    return result;
}

NodoB *FibonacciHeap::deleteNode(FibonacciHeap &fh, int target)
{
    NodoB *foundNode = findNode(*fh.min,target);
    decreaseKey(fh,*foundNode,-INT_MAX);
    extractMin(&fh);
}

void FibonacciHeap::fibonacciHeap2file(FibonacciHeap &fh)
{

    file = new QFile("out.dot");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    out = new QTextStream(file);

    *out<<"digraph G { "<<endl;

    NodoB *currentNode = fh.min;
    //NodoB *result=NULL;
    do{
        if(currentNode->siblingDer){
            *out<<"\"\\"<<currentNode<<"\" [label = \""<<currentNode->key<<"\"] "<<endl;
            *out<<"\"\\"<<currentNode->siblingDer<< "\" [ label=\""<<currentNode->siblingDer->key<<"\"] ;" <<endl ;
            *out<<"\"\\"<<currentNode<<"\""<<" -> \"\\"<<currentNode->siblingDer<< "\" [constraint=false] "<<endl ;
        }


        if(currentNode->siblingIzq){
            *out<<"\"\\"<<currentNode<<"\" [label = \""<<currentNode->key<<"\"] "<<endl;
            *out<<"\"\\"<<currentNode->siblingIzq<< "\" [ label=\""<<currentNode->siblingIzq->key<<"\"] ;"<<endl;
            *out<<"\"\\"<<currentNode<<"\""<<" -> \"\\"<<currentNode->siblingIzq<< "\" [constraint=false] "<<endl ;
        }
        if(currentNode->child){
            *out<<"\"\\"<<currentNode->child<<"\" [label = \""<<currentNode->child->key<<"\"] "<<endl;
            *out<<"\"\\"<<currentNode->child<<"\" [label=\""<<currentNode->child->key<<"\" ]"<<endl;
        }


       // bfsPrint(*currentNode,value);
//        NodoB *child= currentNode->child;
//        do{
//            bfs(*child,value);
//            child=child->siblingDer;
//        }while(child == b.child);

        currentNode = currentNode->siblingDer;
    }while(currentNode!=fh.min);

    *out<<"} "<<endl;
    file->close();

}
