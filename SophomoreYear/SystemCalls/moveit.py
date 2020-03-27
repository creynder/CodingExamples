#!/usr/bin/env python3

import atexit
import os
import sys
import tempfile
import time

# Functions

def usage(status=0):
    ''' Display usage message for program and exit with specified status. '''
    print(f'Usage: {os.path.basename(sys.argv[0])} files...')
    sys.exit(status)

def save_files(files):
    ''' Save list of files to a temporary file and return the name of the
    temporary file. '''
    with tempfile.NamedTemporaryFile(delete=False,mode='w+t') as tf:
        for fileName in files:
            if fileName == files[-1]:
                tf.write(fileName)
            else:
                tf.write(fileName)
                tf.write("\n")
        return tf.name

def edit_files(path):
    ''' Fork a child process to edit the file specified by path using the user's
    default EDITOR (use "vim" if not set).  Parent waits for child process and
    returns whether or not the child was successful. '''
    try:
        pid = os.fork()
        time.sleep(5)
    except OSError:
        sys.exit(1)
    
    if 'EDITOR' in os.environ:
        editor = os.environ['EDITOR']
    else:
        editor = 'vim'
    
    if pid == 0:
        try:            
            os.execlp(editor,editor,path)           
        except OSError:
            sys.exit(1)
    else:
        try:
            pid, status = os.wait()
        except OSError:
            pass
        
        if not os.WIFEXITED(status):
             sys.exit(1)
            

def move_files(files, path):
    ''' For each file in files and the corresponding information from the file
    specified by path, rename the original source file to the new target path
    (if the names are different).  Return whether or not all files were
    successfully renamed. '''
    newNames = []
    for fileName in open(path):
        fileName = fileName.rstrip()
        newNames.append(fileName)

    originalNames = files

    for pair in zip(originalNames,newNames):
        nameOld, nameNew = pair
        if nameOld != nameNew:
            try:
                os.rename(nameOld, nameNew)
            except OSError:
                sys.exit(1)

def main():
    ''' Parse command line arguments, save arguments to temporary file, allow
    the user to edit the temporary file, move the files, and remove the
    temporary file. '''
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    path = ''
    files = []
    
    if len(arguments):
        while len(arguments):
            argument = arguments.pop(0)
            if argument == '-h':
                usage(0)
            elif argument.startswith('-'):
                usage(1)
            else:
                files.append(argument)               
    else:
        usage(1)


    # TODO: Save files (arguments)
    tempFileName = save_files(files)

    # TODO: Register unlink to cleanup temporary file
    atexit.register(os.remove,tempFileName)

    # TODO: Edit files stored in temporary file
    edit_files(tempFileName)
   
    # TODO: Move files stored in temporary file
    move_files(files,tempFileName)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
