#ifndef __STACK_H__
#define __STACK_H__
#define STACK_SIZE 1000
typedef union
{
    int x;
    char y;
    float z;
    int *a;
} element_t;

typedef enum 
{
    INT,
    CHAR,
    FLOAT,
    INT_PTR
} stype_t;

class stack
{
    private:
        stype_t S[STACK_SIZE];
        int top;
    
    public:
        stack();
        element_t pop();
        void push(stype_t i);
        bool isEmpty();
};

#endif