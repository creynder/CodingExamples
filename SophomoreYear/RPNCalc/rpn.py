#!/usr/bin/env python3

import os
import sys

# Globals

OPERATORS = {'+', '-', '*', '/', '^'}

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname}

By default, {progname} will process expressions from standard input.''')

    sys.exit(status)

def error(message):
    ''' Display error message and exit with error. '''
    print(message, file=sys.stderr)
    sys.exit(1)

def evaluate_operation(operation, operand1, operand2):
    ''' Return the result of evaluating the operation with operand1 and
    operand2.

    >>> evaluate_operation('+', 4, 2)
    6

    >>> evaluate_operation('-', 4, 2)
    2

    >>> evaluate_operation('*', 4, 2)
    8

    >>> evaluate_operation('/', 4, 2)
    2.0

    >>> evaluate_operation('^', 2, 3)
    8
    '''
    if operation == '+':
        return operand1+operand2
    elif operation == '-':
        return operand1-operand2
    elif operation == '*':
        return operand1*operand2
    elif operation == '/':
        return operand1/operand2
    elif operation == '^':
        baseNum = operand1
        while operand2 > 1:
            operand1=operand1*baseNum
            operand2 = operand2-1
        return operand1

def evaluate_expression(expression):
    ''' Return the result of evaluating the RPN expression.

    >>> evaluate_expression('4 2 +')
    6.0

    >>> evaluate_expression('4 2 -')
    2.0

    >>> evaluate_expression('4 2 *')
    8.0

    >>> evaluate_expression('4 2 /')
    2.0

    >>> evaluate_expression('2 3 ^')
    8.0

    >>> evaluate_expression('4 +')
    Traceback (most recent call last):
    ...
    SystemExit: 1

    >>> evaluate_expression('a b +')
    Traceback (most recent call last):
    ...
    SystemExit: 1
    '''
    stack = []
    expression = expression.split()

    for word in expression:
        if word in OPERATORS:
            operation = word
            if len(stack) < 2:
                error('Not enough operands')
            else:
                operand2 = stack.pop()
                operand1 = stack.pop()
                stack.append(evaluate_operation(operation,operand1,operand2)) 
        else:
            try:
                float(word)
            except ValueError:
                error('Unable to convert')
           
            stack.append(float(word))

    return stack.pop()

def main():
    ''' Parse command line arguments and process expressions from standard
    input. '''

    arguments = sys.argv[1:]

    #check if there are any arguments, if so run the argument loop
    while len(arguments) and arguments[0].startswith('-'):
        argument = arguments.pop(0)
        if argument == '-h':
        #display usage message and exit
            usage(0)
        else:
            usage(1)
    
    for line in sys.stdin:
    # read from sys.stdin and pass each line to evaluate expression 
        answer = evaluate_expression(line)
        print(f'{answer}')

# Main Execution

if __name__ == '__main__':
    main()


