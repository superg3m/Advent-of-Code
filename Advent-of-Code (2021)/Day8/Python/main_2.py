def part_one(lines: list[str]) -> int:
    signals: list[list[str]] = []
    outputs: list[list[str]] = []

    for line in lines:
        signals_output = line.split(" | ")
        signals.append(signals_output[0].split(" "))
        outputs.append(signals_output[1].split(" "))

    count = 0
    for output in outputs:
        for s in output:
            if len(s) in [2, 3, 4, 7]:
                count += 1

    return count

def missing_segment_count(group: str, unique_segment: str) -> bool:
    missing_count = 0
    for s in unique_segment:
        if s not in group:
            missing_count += 1

    return missing_count

def contains_segment(group: str, unique_segment: str) -> bool:
    for s in unique_segment:
        if s not in group:
            return False

    return True

def index_from_digits(group: str, digits: list[str]):
    for i, s in enumerate(digits):
        if len(s) != len(group):
            continue

        has = True
        for c in s:
            if c not in group:
                has = False
                break

        if has:
            return i

    return -1

def part_two(lines: list[str]) -> int:
    signals: list[list[str]] = []
    outputs: list[list[str]] = []

    for line in lines:
        signals_output = line.split(" | ")
        signals.append(signals_output[0].split(" "))
        outputs.append(signals_output[1].split(" "))

    numbers = []
    for i in range(len(signals)):
        signal = signals[i]
        output = outputs[i]

        digits: list[str] = [""] * 10
        for group in signal:
            length = len(group)

            if length == 2:  # 1
                digits[1] = group
            elif length == 3:  # 7
                digits[7] = group
            elif length == 4:  # 4
                digits[4] = group
            elif length == 7:  # 8
                digits[8] = group

        for group in signal:
            length = len(group)

            if length == 5: # 2, 3, 5
                if contains_segment(group, digits[7]):
                    digits[3] = group
                elif missing_segment_count(group, digits[4]) == 1:
                    digits[5] = group
                else:
                    digits[2] = group

            elif length == 6: # 0, 6, 9
                if contains_segment(group, digits[4]):
                    digits[9] = group
                elif contains_segment(group, digits[7]):
                    digits[0] = group
                else:
                    digits[6] = group

        digit = 0
        mult = 1
        for group in reversed(list(output)):
            index = index_from_digits(group, digits)
            digit += index * mult
            mult *= 10


        numbers.append(digit)


    return sum(numbers)

if __name__ == "__main__":
    f = open("../Day8.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
