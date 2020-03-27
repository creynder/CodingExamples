#!/usr/bin/env python3

import collections
import os
import sys
import csv

import requests

# Constants

URL     = 'https://yld.me/raw/axPa'
TAB     = ' '*8
GENDERS = ('M', 'F')
ETHNICS = ('B', 'C', 'N', 'O', 'S', 'T', 'U')

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [options] [URL]

    -y  YEARS   Which years to display (default: all)
    -p          Display data as percentages.
    -G          Do not include gender information.
    -E          Do not include ethnic information.
    ''')
    sys.exit(status)

def load_demo_data(url=URL):
    ''' Load demographics from specified URL into dictionary

    >>> load_demo_data('https://yld.me/raw/ilG').keys()
    dict_keys(['2013', '2014', '2015', '2016', '2017', '2018', '2019'])

    >>> load_demo_data('https://yld.me/raw/ilG')['2013']
    {'M': 1, 'B': 2, 'F': 1, 'TOTAL': 2}

    >>> load_demo_data('https://yld.me/raw/ilG')['2019']
    {'M': 1, 'U': 2, 'F': 1, 'TOTAL': 2}
    '''
    # TODO: Request data from url and load it into dictionary organized in the
    # following fashion:
    #
    #   {'year': {'gender': count, 'ethnic': count}}
    
    year_data = {}
    response = requests.get(url) 
    csvreader = csv.reader(response.text.splitlines())
    next(csvreader)

    for row in csvreader:
        if row[0] not in year_data.keys():
            year_data[row[0]] = {}

        year = row[0]

        for col in row:
            if col in GENDERS:
                if col in year_data[year].keys():
                    year_data[year][col] += 1
                else:
                    year_data[year][col] = 1
            elif col in ETHNICS:
                if col in year_data[year].keys():
                    year_data[year][col] += 1
                else:
                    year_data[year][col] = 1 
    
    # TODO: Add up total number of students for each year and store in
    # dictionary.
    for year in year_data.keys():        
        year_data[year]['TOTAL'] = year_data[year]['M'] + year_data[year]['F'] 
    
    return year_data

def print_demo_separator(years, char='='):
    ''' Print demographics separator

    Note: The row consists of the 8 chars for each item in years + 1.

    >>> print_demo_separator(['2012', '2013'])
    ========================
    '''
    # TODO: Print row of separator characters
    row = ''
    for year in years:
        row += char*8
    print(row+char*8)

def print_demo_years(years):
    ''' Print demographics years row

    Note: The row is prefixed by 4 spaces and each year is right aligned to 8
    spaces ({:>8}).

    >>> print_demo_years(['2012', '2013'])
            2012    2013
    '''
    # TODO: Print row of years
    row = '    '
    for year in years:
        row += f'{str(year):>8}'
    print(row)
        
def print_demo_fields(data, years, fields, percent=False):
    ''' Print demographics information (for particular fields)

    Note: The first column should be a 4-spaced field name ({:>4}), followed by
    8-spaced right aligned data columns ({:>8}).  If `percent` is True, then
    display a percentage ({:>7.1f}%) rather than the raw count.

    >>> data  = load_demo_data('https://yld.me/raw/ilG')
    >>> years = sorted(data.keys())
    >>> print_demo_fields(data, years, GENDERS, False)
       M       1       1       1       1       1       1       1
       F       1       1       1       1       1       1       1
    '''
    # TODO: For each field, print out a row consisting of data from each year.
    for field in fields:
        for year in years:
            if field not in data[year].keys():
                data[year][field] = 0
        row = ''
        row += f'{field:>4}'
        for year in years:
            if percent:
                data[year][field] = data[year][field]/data[year]['TOTAL']*100
                row += f'{data[year][field]:>7.1f}%'
            else:
                row += f'{data[year][field]:>8}'
        print(f'{row}')

def print_demo_data(data, years=None, percent=False, gender=True, ethnic=True):
    ''' Print demographics data for the specified years and attributes '''
    # TODO: Verify the years parameter (if None then extract from data,
    # otherwise use what is given).  Ensure years is sorted.
    year_display = []
    if years:
        if "," in years:
            for year in years.split(","):
                year_display.append(year)
        else:
            year_display = [years]
        year_display = sorted(year_display)
    else:
        year_display = sorted(data.keys())

    # TODO: Print years header with separator
    print_demo_years(year_display)
    print_demo_separator(year_display)

    # TODO: Print gender and ethnic data if enabled
    if gender:
        print_demo_gender(data, year_display, percent)
    
    if ethnic:
        print_demo_ethnic(data, year_display, percent)

def print_demo_gender(data, years, percent=False):
    ''' Print demographics gender information '''
    print_demo_fields(data, years, GENDERS, percent)
    print_demo_separator(years, '-')

def print_demo_ethnic(data, years, percent=False):
    ''' Print demographics ethnic information '''
    print_demo_fields(data, years, ETHNICS, percent)
    print_demo_separator(years, '-')

def main():
    ''' Parse command line arguments, load data from url, and then print
    demographic data. '''
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    url       = URL
    years     = None
    gender    = True
    ethnic    = True
    percent   = False
    
    while len(arguments) and arguments[0].startswith('-'):
        argument = arguments.pop(0)
        if argument == '-y':
            years = arguments.pop(0)
        elif argument == '-p':
            percent = True
        elif argument == '-G':
            gender = False
        elif argument == '-E':
            ethnic = False
        elif argument == '-h':
            usage(0)
        else:
            usage(1)

    if len(arguments):
       url = arguments.pop(0)

    # TODO: Load data from url and then print demograpic data with specified
    # arguments
    data = load_demo_data(url)
    print_demo_data(data, years, percent, gender, ethnic)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
