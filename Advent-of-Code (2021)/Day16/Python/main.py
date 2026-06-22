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

class Packet:
    version: int = -1
    type_id: int = -1

    string_bits: str = ""

    def calculate_version_sum(self):
        total_version_sum = 0
        total_version_sum += self.version
        if isinstance(self, OperatorPacket):
            for sub_packet in self.sub_packets:
                total_version_sum += sub_packet.calculate_version_sum()

        return total_version_sum

class LiteralValuePacket(Packet):
    value: int = 0

    def __init__(self, string_bits: str, version: int, type_id: int, value: int):
        self.string_bits = string_bits
        self.version = version
        self.type_id = type_id
        self.value = value

class OperatorPacket(Packet):
    length_type_id: int = 0
    sub_packets: list[Packet] = []

    def __init__(self, string_bits: str, version: int, type_id: int, length_type_id: int, sub_packets: list[Packet]):
        self.string_bits = string_bits
        self.version = version
        self.type_id = type_id
        self.length_type_id = length_type_id
        self.sub_packets = sub_packets

def binary_to_version_type_id(binary_str: str) -> Tuple[int, int, str]:
    return binary_str_to_decimal(binary_str[0:3]), binary_str_to_decimal(binary_str[3:6]), binary_str[6:len(binary_str)]

def get_packet_binary_literal(packet_binary: str) -> str:
    packet_without_header = consume_packet_header(packet_binary)

    i: int = 0
    while True:
        first = int(packet_without_header[i])
        i += 5
        if first == 0:
            break

    return packet_without_header[0:i]

def binary_literal_bits_to_decimal(binary_literal_bits: str) -> int:
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
def get_packet_header(packet_binary: str) -> Tuple[int, int]:
    return binary_str_to_decimal(packet_binary[0:3]), binary_str_to_decimal(packet_binary[3:6])

def get_packet_length_of_sub_packets_in_bits(packet_binary: str) -> int:
    return binary_str_to_decimal(packet_binary[8:22])

def get_packet_count_of_sub_packets(packet_binary: str) -> int:
    return binary_str_to_decimal(packet_binary[8:18])

def consume_packet_header(packet_binary: str) -> str:
    return packet_binary[6:len(packet_binary)]

"""
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
"""

def create_packet(packet_binary: str) -> Packet:
    version, type_id = get_packet_header(packet_binary)
    if type_id == 4:
        binary_literal_bits = get_packet_binary_literal(packet_binary)
        bit_length = 6 + len(binary_literal_bits)
        value = binary_literal_bits_to_decimal(binary_literal_bits)

        return LiteralValuePacket(packet_binary[0:bit_length], version, type_id, value)

    sub_packets: list[Packet] = []
    length_type_id = int(packet_binary[6])
    total_sub_packets_bits = 0
    if length_type_id == 0:
        sub_packets_bit_length = get_packet_length_of_sub_packets_in_bits(packet_binary)

        while total_sub_packets_bits < sub_packets_bit_length:
            sub_packet = create_packet(packet_binary[22 + total_sub_packets_bits:len(packet_binary)])
            total_sub_packets_bits += len(sub_packet.string_bits)
            sub_packets.append(sub_packet)

        return OperatorPacket(packet_binary[0:22 + total_sub_packets_bits], version, type_id, length_type_id, sub_packets)

    sub_packet_count = get_packet_count_of_sub_packets(packet_binary)
    total_sub_packets_count = 0
    while total_sub_packets_count < sub_packet_count:
        sub_packet = create_packet(packet_binary[18 + total_sub_packets_bits:len(packet_binary)])
        sub_packets.append(sub_packet)
        total_sub_packets_bits += len(sub_packet.string_bits)
        total_sub_packets_count += 1

    return OperatorPacket(packet_binary[0:18 + total_sub_packets_bits], version, type_id, length_type_id, sub_packets)

def part_one(lines: list[str]) -> int:
    hex = lines[0]
    packet_binary = hex_to_binary_string(hex)
    packet = create_packet(packet_binary)

    return packet.calculate_version_sum()

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day16.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
