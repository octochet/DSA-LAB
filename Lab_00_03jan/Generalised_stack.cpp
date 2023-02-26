#include "myStack.h"
#include<iostream>
using namespace std;

stack::stack()
{
    top=-1;
}

stack::pop()
{
    return S[top--];
}
