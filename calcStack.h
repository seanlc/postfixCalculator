#ifndef CALCSTACK_H
#define CALCSTACK_H
#include <string>

using namespace std;

class fullStack
{};     /// exception that will be thrown if an invalid operation is performed on a full stack

class emptyStack
{};     /// exception that will be thrown if an invalid operation is performed on empty stack

class calcStack
{
    public:
        calcStack(int maxItems);    /// constructor with maximum size specified
        calcStack();                /// default constructor with maximum size of 500
        ~calcStack();               /// destructor that deletes dynamically allocated stack
        bool isEmpty() const;       /// returns true if the stack is empty
        bool isFull() const;        /// returns true if the stack is full
        void push(double);          /// adds a double to the top of the stack as long as the stack is not full
        void pop();                 /// removes the top value from the stack assuming the stack is not empty
        double top() const;         /// returns the item on the top of the stack assuming stack is not empty
        bool isNumber(char);        /// returns true if the input char is a number 0-9
        bool isOperator(char);      /// returns true if the input char is arithmetic operator: + - *  /
        bool isSpaceCharac(char);   /// returns true if the input char is ' ' character
        bool isTermCharac(char);    /// returns true if the input char is '#'
        bool isEqualsChar(char);    /// return true if the input char is '='
        double makeNumber(int, int&);   /// takes digit char as input, finds associated digits and returns number as double
        void processExpression();       /// processes string expression and performs calculator operations using class functions
        void promptforExpression();     /// prompts user to enter a postfix expression, calls processException
    protected:
    private:
        int topIndex;       /// represents the array index which holds the top value of the stack
        int maxStack;       /// max number of elements that can placed on the stack
        double * nums;      /// pointer which will point to head of dynamically allocated array that is the stack
        string expression;  /// stores the postfix expression entered by the user to be evaluated by the calculator
        bool terminate;     /// set to true when the user has entered the terminator character '#'
};

#endif // CALCSTACK_H
