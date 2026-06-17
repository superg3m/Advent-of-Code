from typing import Tuple, Dict

def part_one(lines: list[str]) -> int:
    vertices_to_edges: Dict[str, list[str]] = {}
    visited_small_caves: dict[str, bool] = {}
    for line in lines:
        v1, v2 = line.split("-")

        if v1 not in vertices_to_edges:
            vertices_to_edges[v1] = []
            visited_small_caves[v1] = False
        if v2 not in vertices_to_edges:
            vertices_to_edges[v2] = []
            visited_small_caves[v2] = False

        vertices_to_edges[v1].append(v2)
        vertices_to_edges[v2].append(v1)

    result: list[list[str]] = []
    def backtrack(vertex: str, path: list[str], vertices_to_edges: Dict[str, list[str]], visited_small_caves: Dict[str, bool]) -> bool:
        if vertex == "end":
            return True

        edges = vertices_to_edges[vertex]
        for e in edges:
            if visited_small_caves[e] or e == "start":
                continue

            if e.islower():
                visited_small_caves[e] = True

            path.append(e)
            if backtrack(e, path, vertices_to_edges, visited_small_caves):
                result.append(path.copy())

            visited_small_caves[e] = False
            path.pop()


        return False

    path = ["start"]
    backtrack("start", path, vertices_to_edges, visited_small_caves)

    return len(result)

def part_two(lines: list[str]) -> int:
    vertices_to_edges: Dict[str, list[str]] = {}
    visited_small_caves: dict[str, int] = {}
    for line in lines:
        v1, v2 = line.split("-")

        if v1 not in vertices_to_edges:
            vertices_to_edges[v1] = []
            visited_small_caves[v1] = 0
        if v2 not in vertices_to_edges:
            vertices_to_edges[v2] = []
            visited_small_caves[v2] = 0

        vertices_to_edges[v1].append(v2)
        vertices_to_edges[v2].append(v1)

    result: list[list[str]] = []
    def backtrack(has_visit_small_cave_twice: bool, vertex: str, path: list[str], vertices_to_edges: Dict[str, list[str]], visited_small_caves: Dict[str, int]) -> bool:
        if vertex == "end":
            return True

        edges = vertices_to_edges[vertex]
        for e in edges:
            if (visited_small_caves[e] >= 1 and has_visit_small_cave_twice) or (e == "start"):
                continue
            elif visited_small_caves[e] == 1 and not has_visit_small_cave_twice:
                has_visit_small_cave_twice = True

            if e.islower():
                visited_small_caves[e] += 1

            path.append(e)
            if backtrack(has_visit_small_cave_twice, e, path, vertices_to_edges, visited_small_caves):
                result.append(path.copy())

            visited_small_caves[e] -= 1
            if visited_small_caves[e] == 1:
                has_visit_small_cave_twice = False

            path.pop()

        return False

    path = ["start"]
    backtrack(False, "start", path, vertices_to_edges, visited_small_caves)

    return len(result)


if __name__ == "__main__":
    f = open("../Day12.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
