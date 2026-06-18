import math
import sys
from typing import Tuple, Dict

def perform_polymer_insertion_step(polymer_template: str, pair_insertion_rules: Dict[str, str]) -> str:
    to_insert = []
    for i in range(len(polymer_template) - 1):
        compound = polymer_template[i:i+2]
        if compound in pair_insertion_rules:
            to_insert.append((i, pair_insertion_rules[compound]))

    ret = polymer_template[:]
    for index in range(len(to_insert)):
        i, insert = to_insert[(len(to_insert) - 1) - index]
        ret = ret[:i + 1] + insert + ret[i + 1:]

    return ret

def most_common_element_least_common_element(polymer_template: str) -> Tuple[int, int]:
    elements_to_occurrences = {}

    for c in polymer_template:
        if c in elements_to_occurrences:
            elements_to_occurrences[c] += 1
        else:
            elements_to_occurrences[c] = 1


    max_element_occurrences: int = 0
    min_element_occurrences: int = int(sys.maxsize)
    for key, value in elements_to_occurrences.items():
        max_element_occurrences = max(max_element_occurrences, value)
        min_element_occurrences = min(min_element_occurrences, value)

    return max_element_occurrences, min_element_occurrences

def part_one(lines: list[str]) -> int:
    polymer_template = lines[0]

    pair_insertion_rules: Dict[str, str] = {}
    for i in range(2, len(lines)):
        left, right = lines[i].split(" -> ")

        pair_insertion_rules[left] = right

    # print(f"Template: {polymer_template}")
    for step in range(10):
        polymer_template = perform_polymer_insertion_step(polymer_template, pair_insertion_rules)
        # print(f"After step {step + 1}: {polymer_template}")

    most_common, least_common = most_common_element_least_common_element(polymer_template)


    return most_common - least_common

def perform_polymer_insertion_step2(polymer_template: str, pair_insertion_rules: Dict[str, str]) -> str:
    to_insert = []
    for i in range(len(polymer_template) - 1):
        compound = polymer_template[i:i+2]
        if compound in pair_insertion_rules:
            to_insert.append((i, pair_insertion_rules[compound]))

    ret = polymer_template[:]
    for index in range(len(to_insert)):
        i, insert = to_insert[(len(to_insert) - 1) - index]
        ret = ret[:i + 1] + insert + ret[i + 1:]

    return ret

def part_two(lines: list[str]) -> int:
    polymer_template = lines[0]

    pair_insertion_rules: Dict[str, str] = {}
    for i in range(2, len(lines)):
        left, right = lines[i].split(" -> ")

        pair_insertion_rules[left] = right

    # print(f"Template: {polymer_template}")
    for step in range(14):
        polymer_template = perform_polymer_insertion_step2(polymer_template, pair_insertion_rules)
        # print(f"After step {step + 1}: {polymer_template}")

    most_common, least_common = most_common_element_least_common_element(polymer_template)

    return most_common - least_common

if __name__ == "__main__":
    f = open("../Day14.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
