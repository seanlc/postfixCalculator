#include "calcStack.h"
#include <math.h>
#include <iostream>
#include <iomanip>

///********************************
///Function: Constructor
///Task: creates stack using dynamically allocated array with the input maxItems used as the size of the stack
/// sets topIndex to be -1 to indicate the stack is empty, initializes maxStack variable as maxItems input
/// sets terminate condition to be false
///Returns: nothing
///********************************
calcStack::calcStack(int maxItems)
{
    maxStack = maxItems;
    topIndex = -1;
    nums = new double[maxStack];
    terminate = false;
}
///********************************
///Function: Default Constructor
///Task: creates stack using dynamically allocated array with 500 used as the size of the stack
/// sets topIndex to be -1 to indicate the stack is empty, initializes maxStack variable as 500
/// sets terminate condition to be false
///Returns: nothing
///********************************
calcStack::calcStack()
{
    maxStack = 500;
    topIndex = -1;
    nums = new double[maxStack];
    terminate = false;
}
///********************************
///Function: Destructor
///Task:   deletes dynamically allocated array used to implement the stack
///Returns: nothing
///********************************
calcStack::~calcStack()
{
    delete [] nums;
}
///********************************
///Function: isEmpty
///Task: checks if the top of the stack is equal to -1 to determine if the stack is empty
///Returns: true if the stack is empty, false if the stack is not empty
///********************************
bool calcStack::isEmpty() const
{
    return topIndex == -1;
}
///********************************
///Function: isFull
///Task: checks if the top of the stack is equal to 1 less than the maximum to determine if the stack is full
///Returns: true if the stack is full, false if the stack is not full
///********************************
bool calcStack::isFull() const
{
    return topIndex == maxStack - 1;
}
///********************************
///Function: push
///Task: if the stack is not full, increments the topIndex int and adds an element to the top of the stack
///Returns: nothing
///********************************
void calcStack::push(double number)
{
    if (isFull())
    {
        throw fullStack();
    }
    topIndex++;
    nums[topIndex] = number;
}
///********************************
///Function: pop
///Task: as long as the stack is not empty, removes the top element from the stack by decrementing topIndex
///Returns: nothing
///********************************
void calcStack::pop()
{
    if (isEmpty())
    {
        throw emptyStack();
    }
    topIndex--;
}
///********************************
///Function: top
///Task: as long as the stack is not empty, returns the double on the top of the stack
///Returns: top element from the stack
///********************************
double calcStack::top() const
{
    if (isEmpty())
    {
        throw emptyStack();
    }
    return nums[topIndex];
}
///********************************
///Function: isNumber
///Task:
///Returns: nothing
///********************************
bool calcStack::isNumber(char test)
{
    if (test == '1' ||
        test == '2' ||
        test == '3' ||
        test == '4' ||
        test == '5' ||
        test == '6' ||
        test == '7' ||
        test == '8' ||
        test == '9' ||
        test == '0' )
    {
        return true;
    }
    else
    {
        return false;
    }
}
///********************************
///Function: isOperator
///Task: determines whether the input character is a valid calculator operation
///Returns: true if the input is an operation, false if the character is not an operation
///********************************
bool calcStack::isOperator(char input)
{
    if (input == '+' || input == '-' || input == '*' || input == '/')
    {
        return true;
    }
    return false;
}
///********************************
///Function: isTermCharac
///Task:   determines whether the input character is the terminator '#'
///Returns: true if the input is a terminator, false otherwise
///********************************
bool calcStack::isTermCharac(char input)
{
    if (input == '#')
    {
        return true;
    }
    return false;
}
///********************************
///Function: isEqualsChar
///Task: determines whether the input char is an equals character '='
///Returns: true if the input is an equals sign, false if the input is not an equals sign
///********************************
bool calcStack::isEqualsChar(char input)
{
    if (input == '=')
    {
        return true;
    }
    return false;
}
///********************************
///Function: makeNumber
///Task: takes an index and a reference integer and returns the double form of the number indicated in the expression
///Returns: a double representing the single or multi-digit number in the expression string
///********************************
double calcStack::makeNumber(int i, int& nlength)
{
    double returnNumber;;
    int stringLength = expression.length();
    bool decPresent = false;
    int decLength = 0;
    nlength = 0;
    int initialI = i;
    int numLength = 0;
    while(i != (stringLength - 1) && isNumber(expression[i+1]))
    {   /// counts the digit length of the number to be evaluated
        numLength++;
        i++;
    }
    i = initialI;   /// resets i back to the initial value in function call
    /// sets a double number to be the digit multiplied by the appropriate power of 10 based on position of the digit
    returnNumber = (expression[i] - '0') * pow(10,numLength);
    numLength--;    /// decrement numLength before evaluating the rest of the number
    while (i != (stringLength - 1) && isNumber(expression[i+1]))
    {   /// while the number has digits left, add the appropriate value to floatReturn
        returnNumber += (  pow(10, numLength) * (expression[i+1] - '0'));
        i++;
        nlength++;
        numLength--;
    }
    if (expression[i + 1] == '.')
    {   /// if a decimal point is present, set the decPresent flag to true
        decPresent = true;
        i++;
        nlength++;
    }
    while (i != (stringLength - 1) && decPresent && isNumber(expression[i + 1]))
    {   /// while there are digits left in the decimal portion, add the appropriate value to the return number
        returnNumber += (pow(10, -(decLength + 1)) * (expression[i+1] - '0'));
        decLength++;
        i++;
        nlength++;
    }
    return returnNumber;
}
///********************************
///Function: processExpression
///Task: process every character in the expression string provided by the user and make appropriate function calls
///Returns: nothing
///********************************
void calcStack::processExpression()
{
    bool numberPres = false;    /// flag set to true when the character being considered is a number
    int elength = expression.length();
    double number = 0.0;    /// variable used to hold number formed from the string
    int numberLength = 0;   /// index adjuster based on length of number obtained from string
    double leftNumber = 0;  /// left operand for calculations
    double rightNumber = 0; /// right operand for calculations
    double resultNumber = 0; /// double used to store the result of calculations

    for (int i = 0; i < elength; i++)   /// loop through each character of the expression to be evaluated
    {
        numberPres = isNumber(expression[i]);   /// sets boolean numberPres to true if expression[i] is a digit
        if (numberPres)
        {
            number = makeNumber(i, numberLength);   /// converts expression[i] to a number in the form of a double
            push(number);   /// push number to the top of the stack
            i += numberLength;  /// adjusted the i index based on the number of digits in number
            numberPres = false; /// sets numberPres to false for next iteration of loop
        }
        else if(isOperator(expression[i]))
        {
            rightNumber = top();    /// set right operand to be top value of the stack
            pop();          /// remove the top value from the stack
            leftNumber = top();     /// set left operand to be the new top value of stack
            pop();      /// remove the top value from the stack
            if (expression[i] == '+')
            {
                resultNumber = leftNumber + rightNumber;    /// add operands if operator is +
            }
            else if (expression[i] == '-')
            {
                resultNumber = leftNumber - rightNumber;    /// subtracts operands if operator is -
            }
            else if (expression[i] == '*')
            {
                resultNumber = leftNumber * rightNumber;    /// multiplies operands if operator is *
            }
            else if (expression[i] == '/')
            {
                resultNumber = leftNumber / rightNumber;    /// divides operands if operator is /
            }
            push(resultNumber);
        }
        else if (isEqualsChar(expression[i]))
        {                           /// pop the result from the stack and print it to the console
            resultNumber = top();
            pop();
            cout << "result= " << setw(8) << setprecision(4) << fixed <<resultNumber << endl;
        }
        else if (isTermCharac(expression[i]))
        {                   /// set terminate condition to true
            cout << "goodbye" << endl;
            terminate = true;
        }
    }
}
///********************************
///Function: promptforExpression
///Task: as long as terminate condition is not true, prompt user to enter a postfix expression and call processExpression
///Returns: nothing
///********************************
void calcStack::promptforExpression()
{
    while (!terminate)
    {
        cout << "Enter expression to evaluate or a # to quit" << endl;
        getline(cin, expression);
        processExpression();
    }
}
