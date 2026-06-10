def part_one(lines: list[str]) -> int:
    horizontal_count = 0
    depth = 0
    for line in lines:
        direction_value = line.split(" ")
        direction = direction_value[0]
        value = int(direction_value[1])

        if direction == "forward":
            horizontal_count += value
        elif direction == "down":
            depth += value
        elif direction == "up":
            depth -= value

    return horizontal_count * depth


def part_two(lines: list[str]) -> int:
    aim: int = 0
    depth: int = 0
    horizontal_count: int = 0
    for line in lines:
        direction_value = line.split(" ")
        direction = direction_value[0]
        x = int(direction_value[1])

        if direction == "forward":
            horizontal_count += x
            depth += aim * x
        elif direction == "down":
            aim += x
        elif direction == "up":
            aim -= x

    return horizontal_count * depth


if __name__ == "__main__":
    f = open("../Day2.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
