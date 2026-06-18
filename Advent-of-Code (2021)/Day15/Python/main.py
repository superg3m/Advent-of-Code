from typing import get_origin


def dp(grid: list[list[int]], memo: list[list[int]], value: int, i: int, j: int):
    value += grid[i][j]
    if memo[i][j] == 0:
        memo[i][j] = value
    elif value < memo[i][j]:
        memo[i][j] = value
    else:
        return

    if j < len(grid[0]) - 1:
        dp(grid, memo, value, i, j + 1)  # right

    if i < len(grid) - 1:
        dp(grid, memo, value, i + 1, j)  # left

def part_one(lines: list[str]) -> int:
    height = len(lines)
    width = len(lines[0])

    grid: list[list[int]] = []
    memo: list[list[int]] = [[0 for _ in range(width)] for _ in range(height)]
    for line in lines:
        row: list[int] = []
        for element in line:
            row.append(int(element))

        grid.append(row)


    dp(grid, memo, 0, 0, 0)

    for row in memo:
        print(row)

    return 0

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day15.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
