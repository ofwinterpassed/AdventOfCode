#!/usr/bin/python

import sys
import itertools

def main():
    two_letters = 0
    three_letters = 0
    ids = []
    unique_chars = set()
    seen = {}

    for box_id in open(sys.argv[1]):
        ids.append(box_id.rstrip())

    for pair in itertools.combinations(ids, r=2):
        words = zip(pair[0], pair[1])
        if len([c for c,d in words if c!=d]) == 1:
            break

    print(''.join([c for c,d in words if c == d]))

main()

