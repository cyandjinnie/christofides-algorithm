#!/usr/bin/python3

import sys
import os
import random

def usage():
    """Prints usage string for this application"""
    print("Usage:")
    print("testgen.py <NUMBER OF RANDOM EUCLIDEAN TESTS>")


def gen_random_tests(num_tests):
    seed = 43
    random.seed(43)

    for i in range(3, num_tests + 3):
        file_name = "test" + str(i) + ".txt"
        test_name = "Euclidean plane " + str(i)
        file = open(file_name, "w")

        num_vertices = random.randint(3, 10)

        print(test_name, file=file)
        print("edges", file=file)
        print(num_vertices, file=file)

        for i in range(num_vertices):
            x, y = random.uniform(-10, 10), random.uniform(-10, 10)
            print(str(x) + ' ' + str(y), file=file)

        file.close()

if __name__ == "__main__":
    if len(sys.argv) <= 1 or len(sys.argv) > 3:
        usage()
        exit()

    num_tests = int(sys.argv[1])

    gen_random_tests(num_tests)
