#include "nodob.h"

NodoB::NodoB()
{
    //this->key=key;
    this->degree=0;
    this->siblingDer=this;
    this->siblingIzq=this;
    this->parent=NULL;
    this->marked=false;
    this->child = NULL;
}

void NodoB::setKey(int key)
{
    this->key=key;
}

NodoB::~NodoB()
{
}
