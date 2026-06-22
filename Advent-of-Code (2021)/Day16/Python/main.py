from typing import Dict, Tuple


def hex_to_binary_string(hex: str) -> str:
    hex_to_binary: Dict[str, str] = {
        "0": "0000",
        "1": "0001",
        "2": "0010",
        "3": "0011",
        "4": "0100",
        "5": "0101",
        "6": "0110",
        "7": "0111",
        "8": "1000",
        "9": "1001",
        "A": "1010",
        "B": "1011",
        "C": "1100",
        "D": "1101",
        "E": "1110",
        "F": "1111",
    }

    ret = ""

    for c in hex:
        ret += hex_to_binary[c]

    return ret

def binary_str_to_decimal(binary_str: str) -> int:
    ret = 0
    for i, c in enumerate(binary_str):
        bit_value: int = int(c)

        ret |= bit_value << ((len(binary_str) - 1) - i)

    return ret

def binary_to_version_type_id(binary_str: str) -> Tuple[int, int, str]:
    return binary_str_to_decimal(binary_str[0:3]), binary_str_to_decimal(binary_str[3:6]), binary_str[6:len(binary_str)]

def rest_of_binary_to_packet_binary_literal_value(rest_of_binary_str: str) -> str:
    groups = []

    i: int = 0
    while True:
        first = rest_of_binary_str[i]
        if int(first) == 0:
            groups.append(rest_of_binary_str[i + 1:i + 5])
            break

        groups.append(rest_of_binary_str[i + 1:i+5])
        i += 5

    print(groups)

    return "".join(groups)

def part_one(lines: list[str]) -> int:
    hex = lines[0]
    binary = hex_to_binary_string(hex)
    version, type_id, rest_of_binary_str = binary_to_version_type_id(binary)
    if type_id == 4:
        binary_literal_value = rest_of_binary_to_packet_binary_literal_value(rest_of_binary_str)
        print("bin: ", binary_literal_value, binary_str_to_decimal(binary_literal_value))


    return 0

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day16.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
