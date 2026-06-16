from typing import Tuple

def part_one(lines: list[str]) -> int:
    closing_syntax_stack = []

    open_to_closing = {
        "(": ")",
        "[": "]",
        "{": "}",
        "<": ">"
    }

    closing_to_open = {
        ")": "(",
        "]": "[",
        "}": "{",
        ">": "<"
    }

    close_syntax_to_points = {
        ")": 3,
        "]": 57,
        "}": 1197,
        ">": 25137
    }

    invalid_points = []
    for line in lines:
        for c in line:
            if c in ["(", "[", "{", "<"]:
                closing_syntax_stack.append(open_to_closing[c])

            if c in [")", "]", "}", ">"]:
                expected = closing_syntax_stack.pop()
                if c != expected:
                    invalid_points.append(close_syntax_to_points[c])
                    break

    return sum(invalid_points)

def part_two(lines: list[str]) -> int:
    closing_syntax_stack = []

    open_to_closing = {
        "(": ")",
        "[": "]",
        "{": "}",
        "<": ">"
    }

    close_syntax_to_points = {
        ")": 1,
        "]": 2,
        "}": 3,
        ">": 4
    }

    points = []
    for line in lines:
        closing_syntax_stack = []
        invalid = False
        for c in line:
            if c in ["(", "[", "{", "<"]:
                closing_syntax_stack.append(open_to_closing[c])

            if c in [")", "]", "}", ">"]:
                expected = closing_syntax_stack.pop()
                if c != expected:
                    invalid = True
                    break

            if invalid:
                break

        if not invalid and len(closing_syntax_stack) != 0:
            total_points = 0
            while len(closing_syntax_stack) != 0:
                total_points *= 5
                total_points += close_syntax_to_points[closing_syntax_stack.pop()]

            points.append(total_points)

    points.sort()

    return points[(len(points) - 1) // 2]

if __name__ == "__main__":
    f = open("../Day10.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()