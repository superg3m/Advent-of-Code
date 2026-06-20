import heapq
from typing import Tuple

from idna import valid_label_length

def create_index_from_i_and_j(i, j, width) -> int:
    return (i * width) + j

def compute_adjacency_list_from_grid(adj: list[list[Tuple[int, float]]], grid: list[list[int]]):
    width = len(grid[0])

    for i in range(len(grid)):
        for j in range(len(grid[i])):
            index = (i * len(grid[i])) + j

            if j > 0:
                adj[index].append((create_index_from_i_and_j(i, j - 1, width), float(grid[i][j - 1]))) # left

            if i > 0:
                adj[index].append((create_index_from_i_and_j(i - 1, j, width), float(grid[i - 1][j]))) # up

            if j < len(grid[i]) - 1:
                adj[index].append((create_index_from_i_and_j(i, j + 1, width), float(grid[i][j + 1])))  # right

            if i < len(grid[i]) - 1:
                adj[index].append((create_index_from_i_and_j(i + 1, j, width), float(grid[i + 1][j])))  # down

def dijkstra(adj: list[list[Tuple[int, float]]], width: int, height: int):
    # wow i i'm just not smart at times...

    pass

def part_one(lines: list[str]) -> int:
    height = len(lines)
    width = len(lines[0])

    grid: list[list[int]] = []
    for line in lines:
        row: list[int] = []
        for element in line:
            row.append(int(element))

        grid.append(row)

    adj = [[] for _ in range(len(grid) * len(grid[0]))]
    compute_adjacency_list_from_grid(adj, grid)
    min_distances = dijkstra(adj, width, height)
    print(min_distances)

    return 0

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day15.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
