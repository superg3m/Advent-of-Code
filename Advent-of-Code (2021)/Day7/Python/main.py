from idlelib.macosx import hideTkConsole
from typing import Tuple
from xmlrpc.client import MAXINT


def calculate_fuel_cost(crabs: list[int], middle_index: int) -> int:
    target: int = crabs[middle_index]

    fuel_cost = 0
    for i in range(0, len(crabs)):
        fuel_cost += abs(target - crabs[i])

    return fuel_cost

def binary_search_lease_fuel(crabs: list[int]) -> int:
    left_index = 0
    right_index = len(crabs) - 1
    middle_index = left_index + ((right_index - left_index) // 2)
    lease_fuel_cost = calculate_fuel_cost(crabs, middle_index)

    return lease_fuel_cost

def part_one(lines: list[str]) -> int:
    str_crabs = lines[0].split(",")
    crabs: list[int] = [int(str_crab) for str_crab in str_crabs]
    crabs.sort()

    return binary_search_lease_fuel(crabs)


def calculate_fuel_cost_part2(crabs: list[int], target: int) -> int:
    fuel_cost = 0
    for i in range(0, len(crabs)):
        n = abs(target - crabs[i])
        fuel_cost += (n * (n + 1)) // 2

    return fuel_cost

def calculate_left_middle_right_fuel(crabs: list[int], left_index: int, right_index: int) -> Tuple[int, int, int]:
    cached_right_index = right_index
    middle_index = left_index + ((right_index - left_index) // 2)
    cached_middle_index = middle_index

    middle_fuel = calculate_fuel_cost_part2(crabs, middle_index)

    right_index = middle_index-1
    middle_index = left_index + ((right_index - left_index) // 2)
    left_fuel = calculate_fuel_cost_part2(crabs, middle_index)

    right_index = cached_right_index
    middle_index = cached_middle_index
    left_index = middle_index+1
    middle_index = left_index + ((right_index - left_index) // 2)
    right_fuel = calculate_fuel_cost_part2(crabs, middle_index)

    return left_fuel, middle_fuel, right_fuel


def binary_search_lease_fuel_part2(crabs: list[int]) -> int:
    left_index = 0
    right_index = len(crabs) - 1

    lease_fuel_cost = MAXINT
    for i in range(crabs[0], crabs[len(crabs) - 1]):
        fuel = calculate_fuel_cost_part2(crabs, i)
        if fuel >= lease_fuel_cost:
            break
        else:
            lease_fuel_cost = fuel

    return lease_fuel_cost

def part_two(lines: list[str]) -> int:
    str_crabs = lines[0].split(",")
    crabs: list[int] = [int(str_crab) for str_crab in str_crabs]
    crabs.sort()

    return binary_search_lease_fuel_part2(crabs)


def part_two_improved(lines: list[str]) -> int:
    str_crabs = lines[0].split(",")
    crabs: list[int] = [int(str_crab) for str_crab in str_crabs]

    left = min(crabs)
    right = max(crabs)
    while left < right:
        middle = (left + right) // 2

        cost_middle = calculate_fuel_cost_part2(crabs, middle)
        cost_next = calculate_fuel_cost_part2(crabs, middle + 1)

        if cost_middle > cost_next:
            left = middle + 1
        else:
            right = middle

    return calculate_fuel_cost_part2(crabs, left)

if __name__ == "__main__":
    f = open("../Day7.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    print(f"part2_improved: {part_two_improved(lines)}")
    f.close()
