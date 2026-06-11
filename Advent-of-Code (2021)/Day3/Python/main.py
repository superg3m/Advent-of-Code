
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

def create_valid_list(lines: list[str], bit_position: int, bit: int) -> list[str]:
    ret: list[str] = []

    for line in lines:
        if int(line[bit_position]) == bit:
            ret.append(line)

    return ret

def part_two(lines: list[str]) -> int:
    data = lines
    for bit_position in range(len(data[0])):
        if len(data) == 1:
            break

        one_bits_set: list[int] = [0] * len(data[0])
        for line in data:
            for i in range(len(line)):
                bit = line[i]
                one_bits_set[i] += int(bit)

        for i, num in enumerate(one_bits_set):
            one_bits_set[i] = num >= ((len(data) + 1) // 2)

        data = create_valid_list(data, bit_position, one_bits_set[bit_position])

    oxygen_rating = 0
    for i in range(len(data[0])):
        num = int(data[0][i])
        if num:
            oxygen_rating = set_bit(oxygen_rating, (len(data[0]) - 1) - i)

    data = lines
    for bit_position in range(len(data[0])):
        if len(data) == 1:
            break

        one_bits_set: list[int] = [0] * len(data[0])
        for line in data:
            for i in range(len(line)):
                bit = line[i]
                one_bits_set[i] += int(bit)

        for i, num in enumerate(one_bits_set):
            one_bits_set[i] = num < ((len(data) + 1) // 2)

        data = create_valid_list(data, bit_position, one_bits_set[bit_position])

    co2_rating = 0
    for i in range(len(data[0])):
        num = int(data[0][i])
        if num:
            co2_rating = set_bit(co2_rating, (len(data[0]) - 1) - i)

    return oxygen_rating * co2_rating


if __name__ == "__main__":
    f = open("../Day3.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
