#!/usr/bin/python

import sys
from datetime import datetime

def second(a):
    return a[1]


def first(a):
    return a[0]

def maxfirst(a):
    if len(a[0]) == 0:
        return 0
    else:
        return max(a[0].values())

def print_iterator(it):
    for x in it:
        print(x, end=' ')
    print('')  # for new line

def main():
    frequency = 0
    unique_frequency = set()
    l = 0
    guard = {}

    log = [(datetime.strptime(a[1:17], "%Y-%m-%d %H:%M"), a[:-1]) for a in open(sys.argv[1])]

    log.sort()

    for entry in log:
        tmp = entry[-1].split(" ")
        if tmp[-1] == "shift":
            guard_id = tmp[-3]
            if guard_id not in guard.keys():
                guard[guard_id] = [{}, 0]

        elif tmp[-1] == "asleep":
            asleep = int(entry[0].minute) #int(tmp[-3][-3:-1])

        elif tmp[-1] == "up":
            awake = int(entry[0].minute) #int(tmp[-3][-3:-1])
            guard[guard_id][1] += awake - asleep
            for x in range(asleep,awake):
                if x not in guard[guard_id][0].keys():
                    guard[guard_id][0][x] = 0
                guard[guard_id][0][x] += 1

    firsts = map(maxfirst,guard.values())
    #maxs = map(max, firsts)
    #print(list(firsts))
    firsts_list = list(firsts)
    max_value = max(firsts_list)
    max_guard_id = [k for k, v in guard.items() if len(first(v).values()) != 0 and max(first(v).values()) == max_value]

    for id in max_guard_id:
        max_value = max(guard[id][0].values())
        max_minute = [k for k, v in guard[id][0].items() if v == max_value]

        print(max_minute[0])
        print(int(id[1:]))

        print(max_minute[0] * int(id[1:]))






main()