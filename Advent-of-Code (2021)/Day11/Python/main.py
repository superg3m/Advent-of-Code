from typing import Tuple

SIZE = 10
FLASH_COUNT = 0

def perform_octopus_update(octopus_energy: list[int], flashed_this_step: list[bool], i: int, j: int):
    global FLASH_COUNT

    index = (i * SIZE) + j
    if flashed_this_step[index]:
        return

    octopus_energy[index] += 1
    if octopus_energy[index] == 10: #flash
        FLASH_COUNT += 1
        octopus_energy[index] = 0
        flashed_this_step[index] = True

        if i != 0 and j != 0: # diagonal_top_left
            perform_octopus_update(octopus_energy, flashed_this_step, i - 1, j - 1)

        if i != 0 and j != SIZE - 1: # diagonal_top_right
            perform_octopus_update(octopus_energy, flashed_this_step, i - 1, j + 1)

        if i != SIZE - 1 and j != 0:  # diagonal_bottom_left
            perform_octopus_update(octopus_energy, flashed_this_step, i + 1, j - 1)

        if i != SIZE - 1 and j != SIZE - 1:  # diagonal_bottom_right
            perform_octopus_update(octopus_energy, flashed_this_step, i + 1, j + 1)

        if j != 0:
            perform_octopus_update(octopus_energy, flashed_this_step, i, j - 1) # left

        if i != 0:
            perform_octopus_update(octopus_energy, flashed_this_step, i - 1, j) # up

        if j != SIZE - 1:
            perform_octopus_update(octopus_energy, flashed_this_step, i, j + 1) # right

        if i != SIZE - 1:
            perform_octopus_update(octopus_energy, flashed_this_step, i + 1, j) # down

def part_one(lines: list[str]) -> int:
    octopus_energy: list[int] = [0] * (SIZE*SIZE)
    for i, line in enumerate(lines):
        for j, c in enumerate(line):
            octopus_energy[(i*SIZE) + j] = int(c)

    for step in range(100):
        flashed_this_step: list[bool] = [False] * (SIZE*SIZE)
        for index, _ in enumerate(octopus_energy):
            i = index // SIZE
            j = index % SIZE

            perform_octopus_update(octopus_energy, flashed_this_step, i, j)

    return FLASH_COUNT


def perform_octopus_update(octopus_energy: list[int], flashed_this_step: list[bool], i: int, j: int):
    global FLASH_COUNT

    index = (i * SIZE) + j
    if flashed_this_step[index]:
        return

    octopus_energy[index] += 1
    if octopus_energy[index] == 10: #flash
        FLASH_COUNT += 1
        octopus_energy[index] = 0
        flashed_this_step[index] = True

        if i != 0 and j != 0: # diagonal_top_left
            perform_octopus_update(octopus_energy, flashed_this_step, i - 1, j - 1)

        if i != 0 and j != SIZE - 1: # diagonal_top_right
            perform_octopus_update(octopus_energy, flashed_this_step, i - 1, j + 1)

        if i != SIZE - 1 and j != 0:  # diagonal_bottom_left
            perform_octopus_update(octopus_energy, flashed_this_step, i + 1, j - 1)

        if i != SIZE - 1 and j != SIZE - 1:  # diagonal_bottom_right
            perform_octopus_update(octopus_energy, flashed_this_step, i + 1, j + 1)

        if j != 0:
            perform_octopus_update(octopus_energy, flashed_this_step, i, j - 1) # left

        if i != 0:
            perform_octopus_update(octopus_energy, flashed_this_step, i - 1, j) # up

        if j != SIZE - 1:
            perform_octopus_update(octopus_energy, flashed_this_step, i, j + 1) # right

        if i != SIZE - 1:
            perform_octopus_update(octopus_energy, flashed_this_step, i + 1, j) # down

def part_two(lines: list[str]) -> int:
    octopus_energy: list[int] = [0] * (SIZE*SIZE)
    for i, line in enumerate(lines):
        for j, c in enumerate(line):
            octopus_energy[(i*SIZE) + j] = int(c)

    step = 0
    while True:
        step += 1

        flashed_this_step: list[bool] = [False] * (SIZE*SIZE)
        for index, _ in enumerate(octopus_energy):
            i = index // SIZE
            j = index % SIZE

            perform_octopus_update(octopus_energy, flashed_this_step, i, j)

        if sum(octopus_energy) == 0:
            return step


if __name__ == "__main__":
    f = open("../Day11.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
