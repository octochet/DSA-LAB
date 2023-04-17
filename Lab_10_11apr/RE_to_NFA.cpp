#include <iostream>
#include <regex>

using namespace std;

/*
input:
a regular expression, R, in the form of a string

output:
the corresponding NFA

solution:
1. create a new NFA, N
2. for each character in R
    if the character is a literal
        create a new state, s
        add a transition from the current state to s on the character
        make s the current state
    else if the character is a concatenation operator
        do nothing
    else if the character is a union operator
        create a new state, s
        add a transition from the current state to s on the empty string
        make s the current state
    else if the character is a kleene star operator
        create a new state, s
        add a transition from the current state to s on the empty string
        add a transition from s to the current state on the empty string
        make s the current state
3. add a final state to N
4. add a transition from the current state to the final state on the empty string
5. return N
*/
