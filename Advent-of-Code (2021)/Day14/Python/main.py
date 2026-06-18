import math
import sys
from collections import defaultdict
from typing import Tuple, DefaultDict, Dict

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

def perform_polymer_insertion_step2(polymer_template_map: DefaultDict[str, int], occurrence_map: DefaultDict[str, int], pair_insertion_rules: Dict[str, str]):
    polymer_template_map_temp = polymer_template_map.copy()

    for insertion_rule in pair_insertion_rules:
        if insertion_rule in polymer_template_map_temp and polymer_template_map_temp[insertion_rule] > 0:
            to_insert: str = pair_insertion_rules[insertion_rule]
            value = polymer_template_map_temp[insertion_rule]
            occurrence_map[to_insert] += value
            polymer_template_map[insertion_rule[0] + to_insert] += value
            polymer_template_map[to_insert + insertion_rule[1]] += value
            polymer_template_map[insertion_rule] -= value

def most_common_element_least_common_element2(occurrence_map: Dict[str, int]) -> Tuple[int, int]:
    length = 0
    max_element_occurrences: int = 0
    min_element_occurrences: int = int(sys.maxsize)
    for key, value in occurrence_map.items():
        length += value
        max_element_occurrences = max(max_element_occurrences, value)
        min_element_occurrences = min(min_element_occurrences, value)

    return max_element_occurrences, min_element_occurrences

def part_two(lines: list[str]) -> int:
    polymer_template = lines[0]

    pair_insertion_rules: Dict[str, str] = {}
    for i in range(2, len(lines)):
        left, right = lines[i].split(" -> ")

        pair_insertion_rules[left] = right

    # print(f"Template: {polymer_template}")

    occurrence_map: defaultdict[str, int] = defaultdict(int)
    polymer_template_map: DefaultDict[str, int] = defaultdict(int)
    for i in range(len(polymer_template) - 1):
        compound = polymer_template[i:i+2]
        occurrence_map[compound[0]] += 1

        if i == len(polymer_template) - 2:
            occurrence_map[compound[1]] += 1

        polymer_template_map[compound] += 1

    for step in range(40):
        perform_polymer_insertion_step2(polymer_template_map, occurrence_map, pair_insertion_rules)

    most_common, least_common = most_common_element_least_common_element2(occurrence_map)
    return most_common - least_common

if __name__ == "__main__":
    f = open("../Day14.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
