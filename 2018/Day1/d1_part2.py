#!/usr/bin/python

import sys


def main():
    frequency = 0
    unique_frequency = set()
    l = 0
    is_found = False
    while not is_found:
        for tuning in open(sys.argv[1]):
            frequency = frequency + int(tuning)
            unique_frequency.add(frequency)
            if len(unique_frequency) == l:
                print(frequency)
                is_found = True
                break
            else:
                l = l+1

main()