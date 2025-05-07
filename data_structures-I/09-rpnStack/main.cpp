//*****************************************************************************************************
//
//      This program reads in a file of RPN expressions and instantiates an array-based list stack of
//      integers to store and evaluate the expressions. 
//      RPN (Reverse Polish Notation) is a postfix notation where the operator follows the operands. 
//      For example, the infix expression (3 + 4) * 5 is written in RPN as 3 4 + 5 *.
//
//      Other files required:
//        1.	 stack.h - header file for the Stack class
//        2.	 expressions.txt - file containing RPN expressions
//
//*****************************************************************************************************

#include "stack.h" // Include the stack class for managing the stack operations
// ispunct() checks whether a given character is a punctuation character (like !, ?, +, -, etc.). 
#include <cctype>  // For character classification functions like isdigit() and ispunct()
#include <cstdlib> // For atoi() to convert strings to integers
#include <fstream> // For file input and output
#include <iostream> // For console input and output
using namespace std;

//*****************************************************************************************************

// Function to output the current token to the results file
void outputToken(char token[], ofstream &resultsFile);

// Function to process a number token and push it onto the stack
void processNumber(char token[], Stack<int> &intStack, ofstream &resultsFile);

// Function to process an operator token and perform the operation on the stack
bool processOperator(char token[], Stack<int> &intStack, ofstream &resultsFile);

// Function to display the result of the RPN expression or report errors
void display(Stack<int> &intStack, ofstream &resultsFile, bool &isValid);

// Function to reset the stack and validation flag for the next expression
void resetFlagStack(Stack<int> &intStack, bool &isValid);

//*****************************************************************************************************

int main() {
    Stack<int> intStack; // Create a stack to store integers for RPN evaluation
    bool isValid = true; // Flag to track if the current RPN expression is valid
    char token[5];       // Array to store the current token being read from the file

    /*
    ifstream is a class provided by the <fstream> header for handling input file streams.
    in is the variable name for the input stream object.
    The constructor is passed the file name "expressions.txt", which opens the file for reading.
    ofstream out("results.txt");

    ofstream is a class provided by the <fstream> header for handling output file streams.
    out is the variable name for the output stream object.
    The file "results.txt" is opened for writing. If the file does not exist, it is created; if it exists, its contents are typically overwritten.
    */
    ifstream in("expressions.txt"); // Open the input file containing RPN expressions
    ofstream out("results.txt");    // Open the output file to write results

    // Read tokens from the input file one by one
    while (in >> token) {
        outputToken(token, out); // Output the current token to the results file

        if (token[0] == ';') { // If the token is ';', it marks the end of an RPN expression
            display(intStack, out, isValid); // Display the result or error for the current expression
            resetFlagStack(intStack, isValid); // Reset the stack and validation flag for the next expression
        } else if ((isValid) && (isdigit(token[0]))) { // If the token is a number and the expression is valid
            processNumber(token, intStack, out); // Process the number and push it onto the stack
        } else if ((isValid) && (ispunct(token[0]))) { // If the token is an operator and the expression is valid
            isValid = processOperator(token, intStack, out); // Process the operator and update the validity flag
        }
    }

    in.close(); // Close the input file
    out.close(); // Close the output file

    return 0; // Exit the program
}

//*****************************************************************************************************

// Output the current token to the results file and optionally to the console
void outputToken(char token[], ofstream &resultsFile) {
    resultsFile << endl << "(Token: " << token << ")\t\t"; // Write the token to the results file

    if (token[0] != ';') // If the token is not ';', output it to the console
        cout << token << " ";
}

//*****************************************************************************************************

// Process a number token by converting it to an integer and pushing it onto the stack
void processNumber(char token[], Stack<int> &intStack, ofstream &resultsFile) {
    int num;

    num = atoi(token); // Convert the token to an integer

    intStack.push(num); // Push the integer onto the stack
    resultsFile << "Push " << num; // Write the push operation to the results file
}

//*****************************************************************************************************

// Process an operator token by performing the operation on the top two stack elements
bool processOperator(char token[], Stack<int> &intStack, ofstream &resultsFile) {
    bool success = false; // Flag to track if the operation was successful
    int op1, op2, result; // Variables to store the operands and the result

    // Pop the top two elements from the stack
    if ((intStack.pop(op2)) && (intStack.pop(op1))) {
        resultsFile << "Pop  " << op2 << "\tPop  " << op1; // Write the pop operations to the results file

        // Perform the operation based on the operator token
        switch (token[0]) {
            case '*':
                result = op1 * op2;
                break;
            case '+':
                result = op1 + op2;
                break;
            case '-':
                result = op1 - op2;
                break;
            case '/':
                result = op1 / op2;
                break;
            case '%':
                result = op1 % op2;
                break;
        }

        intStack.push(result); // Push the result back onto the stack
        resultsFile << "\tPush " << result; // Write the push operation to the results file

        success = true; // Mark the operation as successful
    }

    return success; // Return whether the operation was successful
}

//*****************************************************************************************************

// Display the result of the RPN expression or report errors
void display(Stack<int> &intStack, ofstream &resultsFile, bool &isValid) {
    int result;

    if (isValid) { // If the expression is valid
        if (intStack.getNumValues() == 1) { // If there is exactly one value on the stack
            intStack.pop(result); // Pop the result from the stack
            resultsFile << "Pop  " << result << "\n\t\tValid:  result = " << result << "\n" << endl;
            cout << "= " << result << endl; // Output the result to the console
        } else if (intStack.getNumValues() > 1) { // If there are too many values on the stack
            resultsFile << "\n\t\tInvalid RPN expression - too many operands\n" << endl;
            cerr << "\t\tinvalid\n"; // Output an error message to the console

            isValid = false; // Mark the expression as invalid
        }
    } else { // If the expression is invalid
        resultsFile << "\n\t\tInvalid RPN expression - not enough operands\n" << endl;
        cerr << "\t\tinvalid\n"; // Output an error message to the console
    }
}

//*****************************************************************************************************

// Reset the stack and validation flag for the next expression
void resetFlagStack(Stack<int> &intStack, bool &isValid) {
    int popVal;

    while (intStack.pop(popVal)); // Pop all values from the stack

    isValid = true; // Reset the validation flag
}

//*****************************************************************************************************
//*****************************************************************************************************
/*

2 4 * 5 + = 13
13 5 % 5 + = 8
15 1 + 2 / 1 - = 7
15 + 1 + 2 / 1 -                invalid
3 4 + 15 10 - * = 35
3 4 + 6 15 10 - *               invalid
2 13 + 14 6 - - 5 * 4 + = 39
35 6 4 2 2 / + * - = 5
3 4 + 1 2 - * 4 2 / 3 - + = -8
3 14 1 2 4 2 3 + % * + - + = 8

*/