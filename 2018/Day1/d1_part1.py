#!/usr/bin/python

import sys

def main():
	frequency = 0
	for tuning in open(sys.argv[1]):
		frequency = frequency + int(tuning)
	print(frequency)
  
main()