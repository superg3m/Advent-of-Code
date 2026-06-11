from typing import Tuple

class Point:
    x: int = 0
    y: int = 0

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

class LineSegment:
    p0: Point
    p1: Point

    def __init__(self, p0: Point, p1: Point ):
        self.p0 = p0
        self.p1 = p1

def print_board(board: list[list[int]]):
    for row in board:
        print(row)

def calculate_max_dimensions(segments: list[LineSegment]) -> int:
    max_width = 0
    max_height = 0
    for segment in segments:
        max_width = max(max_width, segment.p0.x)
        max_width = max(max_width, segment.p1.x)

        max_height = max(max_height, segment.p0.y)
        max_height = max(max_height, segment.p1.y)

    return max(max_width, max_height)

def mark_board_part1(board: list[list[int]], segment: LineSegment):
    dx = -1 if segment.p0.x - segment.p1.x > 0 else 1
    dy = -1 if segment.p0.y - segment.p1.y > 0 else 1

    if segment.p0.x == segment.p1.x:
        for i in range(segment.p0.y, segment.p1.y + dy, dy):
            board[i][segment.p0.x] += 1

    if segment.p0.y == segment.p1.y:
        for i in range(segment.p0.x, segment.p1.x + dx, dx):
            board[segment.p0.y][i] += 1

def part_one(lines: list[str]) -> int:
    segments: list[LineSegment] = []
    for line in lines:
        points = line.split(" -> ")
        p0_str: list[str] = points[0].split(",")
        p1_str: list[str] = points[1].split(",")

        p0: Point = Point(int(p0_str[0]), int(p0_str[1]))
        p1: Point = Point(int(p1_str[0]), int(p1_str[1]))
        segments.append(LineSegment(p0, p1))

    dim = calculate_max_dimensions(segments)

    board: list[list[int]] = []
    for i in range(dim + 1):
        board.append([0] * (dim + 1))

    for segment in segments:
        mark_board_part1(board, segment)

    count = 0
    for row in board:
        for num in row:
            if num >= 2:
                count += 1

    return count

def mark_board_part2(board: list[list[int]], segment: LineSegment):
    dx = -1 if segment.p0.x - segment.p1.x > 0 else 1
    dy = -1 if segment.p0.y - segment.p1.y > 0 else 1

    if segment.p0.x == segment.p1.x:
        for i in range(segment.p0.y, segment.p1.y + dy, dy):
            board[i][segment.p0.x] += 1

    if segment.p0.y == segment.p1.y:
        for i in range(segment.p0.x, segment.p1.x + dx, dx):
            board[segment.p0.y][i] += 1


    delta_x = segment.p0.x - segment.p1.x
    delta_y = segment.p0.y - segment.p1.y

    if abs(delta_x) == abs(delta_y):
        dx = -1 if segment.p0.x - segment.p1.x > 0 else 1
        dy = -1 if segment.p0.y - segment.p1.y > 0 else 1

        for i in range(abs(delta_x) + 1):
            x = segment.p0.x + (dx * i)
            y = segment.p0.y + (dy * i)
            board[y][x] += 1

def part_two(lines: list[str]) -> int:
    segments: list[LineSegment] = []
    for line in lines:
        points = line.split(" -> ")
        p0_str: list[str] = points[0].split(",")
        p1_str: list[str] = points[1].split(",")

        p0: Point = Point(int(p0_str[0]), int(p0_str[1]))
        p1: Point = Point(int(p1_str[0]), int(p1_str[1]))
        segments.append(LineSegment(p0, p1))

    dim = calculate_max_dimensions(segments)

    board: list[list[int]] = []
    for i in range(dim + 1):
        board.append([0] * (dim + 1))

    for segment in segments:
        mark_board_part2(board, segment)

    count = 0
    for row in board:
        for num in row:
            if num >= 2:
                count += 1

    return count

if __name__ == "__main__":
    f = open("../Day5.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
