#!/usr/bin/env python3

import os
import sys
import signal
import time

def printGoose():
    print('                                                        _...--.')
    print('                                        _____......----\'     .\'')
    print('                                  _..-\'\'                   .\'')
    print('                                .\'                       ./')
    print('                        _.--._.\'                       .\' |')
    print('                     .-\'                           .-.\'  /')
    print('                   .\'   _.-.                     .  \   \'')
    print('                 .\'  .\'   .\'    _    .-.        / `./  :')
    print('               .\'  .\'   .\'  .--\' `.  |  \  |`. |     .\'')
    print('            _.\'  .\'   .\' `.\'       `-\'   \ / |.\'   .\'')
    print('         _.\'  .-\'   .\'     `-.            `      .\'')
    print('       .\'   .\'    .\'          `-.._ _ _ _ .-.    :')
    print('      /    /o _.-\'               .--\'   .\'   \   |')
    print('    .\'-.__..-\'                  /..    .`    / .\'')
    print('  .\'   . \'                       /.\'/.\'     /  |')
    print(' `---\'                                   _.\'   \'')
    print('                                       /.\'    .\'')
    print('                                        /.\'/.\'')

def handler(signum, frame):
    signal.signal(signum,signal.SIG_IGN)
    print('HONK! HONK! HONK! HONK!')


#signal.signal(signal.SIGINT, handler)
#signal.signal(signal.SIGTERM, handler)

while True:
    signal.signal(signal.SIGINT, handler)
    signal.signal(signal.SIGTERM, handler)
    printGoose()
    time.sleep(5)
