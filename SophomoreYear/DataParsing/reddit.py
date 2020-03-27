#!/usr/bin/env python3

import os
import sys

import requests

# Constants

ISGD_URL = 'http://is.gd/create.php'

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    print('''Usage: {} [options] URL_OR_SUBREDDIT

    -s          Shorten URLs using (default: False)
    -n LIMIT    Number of articles to display (default: 10)
    -o ORDERBY  Field to sort articles by (default: score)
    -t TITLELEN Truncate title to specified length (default: 60)
    '''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

def load_reddit_data(url):
    ''' Load reddit data from specified URL into dictionary

    >>> len(load_reddit_data('https://reddit.com/r/nba/.json'))
    27

    >>> load_reddit_data('linux')[0]['data']['subreddit']
    'linux'
    '''
    # TODO: Verify url parameter (if it starts with http, then use it,
    # otherwise assume it is just a subreddit).

    if url.startswith("http"):
        pass 
    else:
        url = "https://reddit.com/r/"+url+"/.json"
    
    response_json = {}

    headers = {'user-agent': 'reddit-{}'.format(os.environ.get('USER', 'cse-20289-sp20'))}
    response = requests.get(url, headers=headers)
    response_json = response.json()
     
    reddit_data = []

    for item in response_json['data']['children']:
        reddit_data.append(item)

    return reddit_data

def shorten_url(url):
    ''' Shorten URL using is.gd service

    >>> shorten_url('https://reddit.com/r/aoe2')
    'https://is.gd/dL5bBZ'

    >>> shorten_url('https://cse.nd.edu')
    'https://is.gd/3gwUc8'
    '''
    # TODO: Make request to is.gd service to generate shortened url.
    
    response = requests.get(ISGD_URL, params={'format': 'json', 'url': url})
    shorturl = response.json()['shorturl']
    
    return shorturl

def print_reddit_data(data, limit=10, orderby='score', titlelen=60, shorten=False):
    ''' Dump reddit data based on specified attributes '''
    # TODO: Sort articles stored in data list by the orderby key, and then
    # print out each article's index, title, score, and url using the following
    # format:
    #
    #   print(f'{index:4}.\t{title} (Score: {score})\n\t{url}')
    #
    # Note: Trim or modify the output based on the keyword arguments to the function.
    
    if orderby == 'score':
        articles = sorted(data, key=lambda i: i['data']['score'], reverse=True)
    elif orderby == 'title':
        articles = sorted(data, key=lambda i: i['data']['title'])
    elif orderby == 'url':
        articles = sorted(data, key=lambda i: i['data']['url'])

    articles = articles[0:int(limit)]
    
    for index, item in enumerate(articles):
        item['data']['title'] = item['data']['title'] [0:int(titlelen)]
        if shorten:
            item['data']['url'] = shorten_url(item['data']['url'])
        if index:
            print()
        print(f"{index+1:4}.\t{item['data']['title']} (Score: {item['data']['score']})\n\t{item['data']['url']}")




def main():
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    url       = None
    limit     = 10
    orderby   = 'score'
    titlelen  = 60
    shorten   = False

    while len(arguments) and arguments[0].startswith('-'):
        argument = arguments.pop(0)
        if argument == '-s':
            shorten = True
        elif argument == '-n':
            limit = arguments.pop(0)
        elif argument == '-o':
            orderby = arguments.pop(0)
        elif argument == '-t':
            titlelen = arguments.pop(0)
        elif argument == '-h':
            usage(0)
        else:
            usage(1)

    if len(arguments):
        url = arguments.pop(0)
    else:
        usage(1)
    

    # TODO: Load data from url and then print the data
    print_reddit_data(load_reddit_data(url),limit,orderby,titlelen,shorten)
    
# Main Execution

if __name__ == '__main__':
    main()
