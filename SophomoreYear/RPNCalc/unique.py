#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]

    -c      Prefix lines by the number of occurences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines

By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    ''' Count the line frequencies from the data in the specified stream while
    ignoring case if specified. '''
    frequencies = {}
    for line in stream:
        line = line.rstrip()
        if ignore_case:
            line = line.lower()
        frequencies[line] = frequencies.get(line,0) + 1

    return frequencies


def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):
    ''' Display line information based on specified parameters:

    - occurrences:  if True, then prefix lines with number of occurrences
    - duplicates:   if True, then only print duplicate lines
    - unique_only:  if True, then only print unique lines
    '''
    for line, count in frequencies.items():
        if duplicates and frequencies[line] > 1:
            if occurrences:
                print(f'{count:>7} {line}')
            else:
                print(f'{line}')
        elif unique_only and frequencies[line] == 1:
            if occurrences:
                print(f'{count:>7} {line}')
            else:
                print(f'{line}')
        elif not duplicates and not unique_only:
            if occurrences:
                print(f'{count:>7} {line}')
            else:
                print(f'{line}')

def main():
    ''' Process command line arguments, count frequencies from standard input,
    and then print lines. '''

    occurrences = False
    duplicates = False
    unique_only = False
    ignore_case = False
    arguments = sys.argv[1:]
    
    while len(arguments) and arguments[0].startswith('-'):
        argument = arguments.pop(0)
        if argument == '-i':
            ignore_case = True
        elif argument == '-c':
            occurrences = True
        elif argument == '-d':
            duplicates = True
        elif argument == '-u':
            unique_only = True
        elif argument == '-h':
            usage(0)
        else:
            usage(1)

    frequencies = count_frequencies(sys.stdin, ignore_case)
    print_lines(frequencies, occurrences, duplicates, unique_only)



# Main Execution

if __name__ == '__main__':
    main()

