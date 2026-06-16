from typing import Tuple


def part_one(lines: list[str]) -> int:
    height_map: list[list[int]] = []
    for line in lines:
        height_map.append([int(c) for c in line])

    low_points = []
    for i in range(len(height_map)):
        for j in range(len(height_map[i])):
            # left, up, right, down

            if j > 0:
                if height_map[i][j] >= height_map[i][j - 1]: # left check
                    continue

            if i > 0:
                if height_map[i][j] >= height_map[i - 1][j]: # up check
                    continue

            if j < (len(height_map[i]) - 1):
                if height_map[i][j] >= height_map[i][j + 1]: # right check
                    continue

            if i < (len(height_map) - 1):
                if height_map[i][j] >= height_map[i + 1][j]: # down check
                    continue

            low_points.append(height_map[i][j])

    return sum(low_points) + len(low_points)

def flood_fill(i: int, j: int, count: int, visited: dict[tuple[int, int], bool], height_map: list[list[int]]) -> int:
    if (i, j) in visited or height_map[i][j] == 9:
        return count - 1

    visited[(i, j)] = True
    if j > 0: # left
        count = flood_fill(i, j - 1, count+1, visited, height_map)

    if i > 0:
        count = flood_fill(i - 1, j, count+1, visited, height_map)

    if j < (len(height_map[i]) - 1):
        count = flood_fill(i, j + 1, count+1, visited, height_map)

    if i < (len(height_map) - 1):
        count = flood_fill(i + 1, j, count+1, visited, height_map)

    return count

def part_two(lines: list[str]) -> int:
    height_map: list[list[int]] = []
    for line in lines:
        height_map.append([int(c) for c in line])

    low_points: list[Tuple[int, int]] = []
    for i in range(len(height_map)):
        for j in range(len(height_map[i])):
            # left, up, right, down

            if j > 0:
                if height_map[i][j] >= height_map[i][j - 1]: # left check
                    continue

            if i > 0:
                if height_map[i][j] >= height_map[i - 1][j]: # up check
                    continue

            if j < (len(height_map[i]) - 1):
                if height_map[i][j] >= height_map[i][j + 1]: # right check
                    continue

            if i < (len(height_map) - 1):
                if height_map[i][j] >= height_map[i + 1][j]: # down check
                    continue

            low_points.append((i, j))

    basins = []
    for low_point in low_points:
        i, j = low_point
        visited = {}
        basins.append(flood_fill(i, j, 1, visited, height_map))

    three_largest_basins: list[int] = [0] * 3
    for basin in basins:
        if basin >= three_largest_basins[2]:
            three_largest_basins[0] = three_largest_basins[1]
            three_largest_basins[1] = three_largest_basins[2]
            three_largest_basins[2] = basin
        elif basin >= three_largest_basins[1]:
            three_largest_basins[0] = three_largest_basins[1]
            three_largest_basins[1] = basin
        elif basin > three_largest_basins[0]:
            three_largest_basins[0] = basin

    solution = 1
    for basin in three_largest_basins:
        solution *= basin

    return solution

if __name__ == "__main__":
    f = open("../Day9.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
