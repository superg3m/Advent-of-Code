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

def dijkstra(start_index: int, adj: list[list[Tuple[int, float]]]):
    distance: list[float] = [float('inf') for _ in range(len(adj))]
    minHeap: list[Tuple[float, int]] = []

    distance[start_index] = 0
    heapq.heappush(minHeap, (0, start_index))

    while len(minHeap):
        d, u = heapq.heappop(minHeap)

        if d > distance[u]:
            continue

        for v, w in adj[u]:
            if distance[u] + w < distance[v]:
                distance[v] = distance[u] + w
                heapq.heappush(minHeap, (distance[v], v))

    return distance

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
    min_distances = dijkstra(0, adj)

    return int(min_distances[-1])

def part_two(lines: list[str]) -> int:
    height = len(lines)
    width = len(lines[0])

    original_grid: list[list[int]] = []
    for line in lines:
        row: list[int] = []
        for element in line:
            row.append(int(element))

        original_grid.append(row)


    grid: list[list[int]] = [[0 for _ in range(width * 5)] for _ in range(height * 5)]
    for l in range(5):
        for i in range(5):
            for j, row in enumerate(original_grid):
                for k, element in enumerate(row):
                    value = (element + l + i)
                    if value > 9:
                        value = ((element + l + i) % 10) + 1

                    grid[(l * height) + j][(i * width) + k] = value


    adj = [[] for _ in range(len(grid) * len(grid[0]))]
    compute_adjacency_list_from_grid(adj, grid)
    min_distances = dijkstra(0, adj)

    return int(min_distances[-1])

if __name__ == "__main__":
    f = open("../Day15.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
