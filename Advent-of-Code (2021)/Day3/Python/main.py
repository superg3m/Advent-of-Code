
def set_bit(x: int, n: int) -> int:
    return x | (1 << n)

def part_one(lines: list[str]) -> int:
    bitmask = set_bit(0, len(lines[0])) - 1

    one_bits_set: list[int] = [0] * len(lines[0])
    for line in lines:
        for i in range(len(line)):
            bit = line[i]
            one_bits_set[i] += int(bit)


    gamma_rate = 0
    for i in range(len(one_bits_set)):
        num = one_bits_set[i]
        if num > (len(lines) // 2):
            gamma_rate = set_bit(gamma_rate, (len(one_bits_set) - 1) - i)

    epsilon_rate = bitmask & ~gamma_rate
    return gamma_rate * epsilon_rate


def part_two(lines: list[str]) -> int:
    return 0


if __name__ == "__main__":
    f = open("../Day3.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
