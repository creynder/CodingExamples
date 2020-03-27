#!/usr/bin/env python3

import os
import signal
import sys
import time

# Functions

def usage(status=0):
    ''' Display usage message for program and exit with specified status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [options] command...
Options:
    -t SECONDS  Timeout duration before killing command (default is 10)
''')
    sys.exit(status)

def error(message, status=1):
    ''' Display error message and exit with specified status. '''
    print(message, file=sys.stderr)
    sys.exit(status)

def alarm_handler(signum, frame):
    ''' Alarm handler that raises InterruptedError '''
    raise InterruptedError()

def timeit(argv, timeout=10):
    ''' Run command specified by argv for at most timeout seconds.
    
    - After forking, the child executes the specified command.

    - After forking, the parent does the following:
        - Registers a handler for SIGALRM
        - Set alarm for specified timeout
        - Waits for child process
        - If wait is interrupted, kills the child process and wait again
        - Prints total elapsed time
        - Exits with the status of the child process
    '''

    try:
        pid = os.fork()
    except OSError:
        sys.exit(1)

    if pid == 0:      
        try:
            os.execvp(argv[0],argv)
        except OSError:
            sys.exit(1)
    else:
        signal.signal(signal.SIGALRM, alarm_handler)
        signal.alarm(timeout)

        timeStart = time.time()
       
        try:
            _, status = os.wait()
        except InterruptedError:
            pass
            
        try:
            os.kill(pid, signal.SIGKILL)
            _, status = os.wait()
            print(f'Time Elapsed: {time.time()-timeStart:.2f}')
            sys.exit(os.WTERMSIG(status))
        except ProcessLookupError:
            pass
                
        if os.WIFEXITED(status):
            print(f'Time Elapsed: {time.time()-timeStart:.2f}')
            sys.exit(os.WEXITSTATUS(status))
        
            

def main():
    ''' Parse command line options and then execute timeit with specified
    command and timeout. '''
    arguments = sys.argv[1:]
    argv = []
    timeout = 10;
    if len(arguments):
        while len(arguments):           
            argument = arguments.pop(0)
            if argument == '-h':
                usage(0)
            elif argument == '-t':
                timeout = int(arguments.pop(0))
            elif argument.startswith('-'):
                usage(1)
            else: 
                argv.append(argument)
        if not argv:
            usage(1)
    else:
        usage(1)

    timeit(argv,timeout)


# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
