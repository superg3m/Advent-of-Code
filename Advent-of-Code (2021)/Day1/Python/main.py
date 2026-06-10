def part_one(lines: list[str]) -> int:
    previous: int = int(lines[0])
    increasing_count = 0
    for line in lines:
        number = int(line)
        if previous < number:
            increasing_count += 1

        previous = number

    return increasing_count

def part_two(lines: list[str]) -> int:
    new_input: list[str] = []
    for i in range(len(lines) - 2):
        n1 = int(lines[i + 0])
        n2 = int(lines[i + 1])
        n3 = int(lines[i + 2])
        new_input.append(str(n1 + n2 + n3))

    return part_one(new_input)


if __name__ == "__main__":
    f = open("../Day1.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()