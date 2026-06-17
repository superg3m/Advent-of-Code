from typing import Tuple, Dict

def print_grid(grid: list[list[str]], width: int, height: int):
    for i in range(height):
        print(grid[i][0:width])

    print()

def perform_fold(grid: list[list[str]], width: int, height: int, axis: str, value: int) -> Tuple[int, int]:
    if axis == "x":
        start = width
        for i in range(height + 1):
            for j in range(start, value, -1):
                if grid[i][j] != "#":
                    continue

                grid[i][value - (j - value)] = grid[i][j]

        return value, height

    elif axis == "y":
        start = height
        for i in range(start, value, -1):
            for j in range(width + 1):
                if grid[i][j] != "#":
                    continue

                grid[value - (i - value)][j] = grid[i][j]

        return width, value


def part_one(lines: list[str]) -> int:
    i = 0
    width = 0
    height = 0

    while lines[i] != "":
        line = lines[i]
        x, y = line.split(",")
        width = max(width, int(x))
        height = max(height, int(y))
        i += 1

    i = 0
    grid: list[list[str]] = [["." for _ in range(width + 1)] for _ in range(height + 1)]
    while lines[i] != "":
        line = lines[i]
        x, y = line.split(",")
        grid[int(y)][int(x)] = "#"
        i += 1

    for k in range(i + 1, i + 2):
        line = lines[k]
        axis, value = line[11:len(line)].split("=")
        width, height = perform_fold(grid, width, height, axis, int(value))

    count = 0
    for i in range(height + 1):
        for j in range(width + 1):
            if grid[i][j] == "#":
                count += 1

    return count

def part_two(lines: list[str]) -> int:
    i = 0
    width = 0
    height = 0

    while lines[i] != "":
        line = lines[i]
        x, y = line.split(",")
        width = max(width, int(x))
        height = max(height, int(y))
        i += 1

    i = 0
    grid: list[list[str]] = [["." for _ in range(width + 1)] for _ in range(height + 1)]
    while lines[i] != "":
        line = lines[i]
        x, y = line.split(",")
        grid[int(y)][int(x)] = "#"
        i += 1

    for k in range(i + 1, len(lines)):
        line = lines[k]
        axis, value = line[11:len(line)].split("=")
        width, height = perform_fold(grid, width, height, axis, int(value))

    print_grid(grid, width, height)

    return 0


if __name__ == "__main__":
    f = open("../Day13.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
