#/bin/bash/python

version = open('VERSION', 'r').readlines()[0].split()

version[2]=str(int(version[2])+1)

open('VERSION', 'w').write(' '.join(version) + '\n')
