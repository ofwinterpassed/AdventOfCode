#!/usr/bin/python

import sys

def main():
    two_letters = 0
    three_letters = 0
    chars = []
    unique_chars = set()
    seen = {}

    for box_id in open(sys.argv[1]):
        chars = []
        chars.extend(box_id)

        #first, check if there are any repeating characters in the string
        #if not, take the next string

        unique_chars = set(chars)

        if len(chars) == len(unique_chars):
            break

        #when confirmed there are repeating characters, count how many times each letter is repeated

        seen = {}
        for letter in chars:
            if letter not in seen:
                seen[letter] = 1
            else:
                seen[letter] += 1

        # check if there are letters that are repeated two times
        for x in seen:
            if seen[x] == 2:
                two_letters += 1
                break

        # check if there are letters that are repeated two times
        for x in seen:
            if seen[x] == 3:
                three_letters += 1
                break

    checksum = two_letters * three_letters

    print(checksum)

main()