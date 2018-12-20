#!/usr/bin/python

import sys
from datetime import datetime

def second(a):
    return a[1]

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

    max_value = max(map(second,guard.values()))
    max_guard_id = [k for k, v in guard.items() if second(v) == max_value]

    for id in max_guard_id:
        max_value = max(guard[id][0].values())
        max_minute = [k for k, v in guard[id][0].items() if v == max_value]

        print(max_minute[0])
        print(int(id[1:]))

        print(max_minute[0] * int(id[1:]))






main()