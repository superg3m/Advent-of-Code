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

def consume_packet_binary_literal(packet: str) -> Tuple[str, str]:
    i: int = 0
    while True:
        first = int(packet[i])
        i += 5
        if first == 0:
            break

    return packet[i:len(packet)], packet[0:i]

def decimal_from_binary_literal_bits(binary_literal_bits: str) -> int:
    groups = []

    i: int = 0
    while True:
        first = int(binary_literal_bits[i])
        if first == 0:
            groups.append(binary_literal_bits[i + 1:i + 5])
            break

        groups.append(binary_literal_bits[i + 1:i+5])
        i += 5

    return binary_str_to_decimal("".join(groups))

# get the next index
def consume_packet_header(packet: str) -> Tuple[str, int, int]:
    return packet[6:len(packet)], binary_str_to_decimal(packet[0:3]), binary_str_to_decimal(packet[3:6])

def consume_packet_length_type_id(packet: str) -> Tuple[str, int]:
    return packet[1:len(packet)], int(packet[0])

def consume_packet_length_of_sub_packets_in_bits(packet: str) -> Tuple[str, int]:
    return packet[15:len(packet)], binary_str_to_decimal(packet[0:15])

def consume_packet_count_of_sub_packets(packet: str) -> Tuple[str, int]:
    return packet[11:len(packet)], binary_str_to_decimal(packet[0:11])

HEADER_LENGTH = 6

def consume_packet(VERSION_ARRAY: list[int], packet: str) -> Tuple[str, str]:
    packet, version, type_id = consume_packet_header(packet)
    VERSION_ARRAY.append(version)

    if type_id == 4: #literal
        packet, binary_literal_bits = consume_packet_binary_literal(packet)
        return packet, binary_literal_bits
    else:
        packet, length_type_id_bit = consume_packet_length_type_id(packet)
        if length_type_id_bit == 0:
            packet, bit_length = consume_packet_length_of_sub_packets_in_bits(packet)
            total_sub_packets_bits = 0
            while total_sub_packets_bits < bit_length:
                packet, sub_packet = consume_packet(VERSION_ARRAY, packet)
                total_sub_packets_bits += HEADER_LENGTH + len(sub_packet)
        else:
            packet, sub_packet_count = consume_packet_count_of_sub_packets(packet)
            total_sub_packets_count = 0
            while total_sub_packets_count < sub_packet_count:
                packet, sub_packet = consume_packet(VERSION_ARRAY, packet)
                total_sub_packets_count += 1

    return packet, ""

def part_one(lines: list[str]) -> int:
    hex = lines[0]
    packet = hex_to_binary_string(hex)
    VERSION_ARRAY = []
    consume_packet(VERSION_ARRAY, packet)

    return sum(VERSION_ARRAY)

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day16.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
