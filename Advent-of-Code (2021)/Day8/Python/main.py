from typing import Tuple, Dict

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

def try_to_narrow_possibility_space_for_group(resolved_bindings: set[str], possibility_space: dict[str, list[str]], group: str):
    for c1 in group:
        potential_solution_set = set(possibility_space[c1])
        for c2 in group:
            if len(potential_solution_set) == 0:
                break

            if c1 == c2:
                continue

            possibility_set2 = set(possibility_space[c2])
            potential_solution_set = potential_solution_set - potential_solution_set.intersection(possibility_set2)

        if len(potential_solution_set) == 1:
            resolved_bindings.add(list(potential_solution_set)[0])
            possibility_space[c1] = list(potential_solution_set)

def remove_resolved_bindings_from_possibility_space(resolved_bindings: set[str], possibility_space: dict[str, list[str]]):
    for key, arr in possibility_space.items():
        if len(arr) == 1:
            continue

        possibility_space[key] = list(set(arr) - set(arr).intersection(resolved_bindings))

def resolve_possibility_space_list(resolved_bindings: set[str], possibility_space: dict[str, list[str]], possibility_space_lists: list[list[str]], group: str):
    temp_resolution: set[str] = set(resolved_bindings)
    for s in group:
        if s not in possibility_space:
            continue

        same_possibility_space_count = 0
        l1 = possibility_space[s]
        for s1 in group:
            if s1 not in possibility_space:
                continue

            l2 = possibility_space[s1]
            if set(l1) == set(l2):
                same_possibility_space_count += 1

        if same_possibility_space_count == len(l1):
            for e in l1:
                temp_resolution.add(e)

    if len(temp_resolution) == 0:
        return possibility_space_lists[0], True

    ret = []
    resolution_count = 0
    for possibility_list in possibility_space_lists:
        intersection = list(set(temp_resolution).intersection(set(possibility_list)))
        if len(intersection) == len(temp_resolution):
            ret = possibility_list
            resolution_count += 1

    return ret, resolution_count == 1

def try_to_narrow_possibility_space_via_cascade(possibility_space: dict[str, list[str]]):
    for key, arr in possibility_space.items():
        same_possibility_space_count = 0
        for key2, arr2 in possibility_space.items():
            if set(arr) == set(arr2):
                same_possibility_space_count += 1

        if same_possibility_space_count == len(arr):
            for key2, arr2 in possibility_space.items():
                if set(arr) == set(arr2):
                    continue

                possibility_space[key2] = list(set(arr2) - set(arr))
            pass

def decode_group_to_number(possibility_space: dict[str, list[str]], group: str) -> int:
    mapping = {
        0: ["a", "b", "c", "e", "f", "g"],
        1: ["c", "f"],
        7: ["a", "c", "f"],
        4: ["b", "c", "d", "f"],
        2: ["a", "c", "d", "e", "g"],
        3: ["a", "c", "d", "f", "g"],
        5: ["a", "b", "d", "f", "g"],
        6: ["a", "b", "d", "e", "f", "g"],
        8: ["a", "b", "c", "d", "e", "f", "g"],
        9: ["a", "b", "c", "d", "f", "g"]
    }

    match: list[str] = []
    for s in group:
        match.append(possibility_space[s][0])


    for integer, arr in mapping.items():
        if set(arr) == set(match):
            return integer

    exit(-1)

def decode_list_to_number(possibility_space: dict[str, list[str]], output: list[str]) -> int:
    num_str = ""
    for group in output:
        num_str += str(decode_group_to_number(possibility_space, group))

    return int(num_str)

def part_two(lines: list[str]) -> int:
    signals: list[list[str]] = []
    outputs: list[list[str]] = []
    for line in lines:
        signals_output = line.split(" | ")
        signals.append(signals_output[0].split(" "))
        outputs.append(signals_output[1].split(" "))

    str_length_to_possibility_space_mapping: Dict[int, list[list[str]]] = {
        2: [["c", "f"]], #1
        3: [["a", "c", "f"]], #7
        4: [["b", "c", "d", "f"]], #4
        5: [["a", "c", "d", "e", "g"], ["a", "c", "d", "f", "g"], ["a", "b", "d", "f", "g"]], #2, 3, 5
        6: [["a", "b", "c", "e", "f", "g"], ["a", "b", "d", "e", "f", "g"], ["a", "b", "c", "d", "f", "g"]], #0, 6, 9
        7: [["a", "b", "c", "d", "e", "f", "g"]], #8
    }

    numbers_to_sum = []
    for i in range(len(signals)):
        signal = signals[i]
        output = outputs[i]
        combined: list[str] = signal + output
        possibility_space: dict[str, list[str]] = {}
        resolved_bindings: set[str] = set()

        unique = []
        for string in combined:
            if len(string) in [2, 3, 4, 7]:
                unique.append(string)

        for group in unique:
            resolved_list, ok = resolve_possibility_space_list(resolved_bindings, possibility_space, str_length_to_possibility_space_mapping[len(group)], group)
            if not ok:
                continue

            for c in group:
                if c in possibility_space:
                    possible_shape_set = set(resolved_list)
                    possible_set = set(possibility_space[c])
                    possibility_space[c] = list(possible_shape_set.intersection(possible_set))
                else:
                    possibility_space[c] = resolved_list

        for group in unique:
            try_to_narrow_possibility_space_for_group(resolved_bindings, possibility_space, group)

        remove_resolved_bindings_from_possibility_space(resolved_bindings, possibility_space)
        try_to_narrow_possibility_space_via_cascade(possibility_space)

        unresolved = []

        combined_no_unique = list(set(combined) - set(unique))
        for group in combined_no_unique:
            resolved_list, ok = resolve_possibility_space_list(resolved_bindings, possibility_space, str_length_to_possibility_space_mapping[len(group)], group)
            if not ok:
                unresolved.append(group)
                continue

            for c in group:
                if c in possibility_space:
                    possible_shape_set = set(resolved_list)
                    possible_set = set(possibility_space[c])
                    possibility_space[c] = list(possible_shape_set.intersection(possible_set))
                else:
                    possibility_space[c] = resolved_list

        for group in combined_no_unique:
            try_to_narrow_possibility_space_for_group(resolved_bindings, possibility_space, group)

        remove_resolved_bindings_from_possibility_space(resolved_bindings, possibility_space)
        try_to_narrow_possibility_space_via_cascade(possibility_space)

        while len(unresolved) != 0:
            should_finish = True
            for key, arr in possibility_space.items():
                if len(arr) != 1:
                    should_finish = False
                    break

            if should_finish:
                break

            group = unresolved.pop(0)
            resolved_list, ok = resolve_possibility_space_list(resolved_bindings, possibility_space, str_length_to_possibility_space_mapping[len(group)], group)
            if not ok:
                unresolved.append(group)
                continue

            for c in group:
                if c in possibility_space:
                    possible_shape_set = set(resolved_list)
                    possible_set = set(possibility_space[c])
                    possibility_space[c] = list(possible_shape_set.intersection(possible_set))
                else:
                    possibility_space[c] = resolved_list

            for group in unresolved:
                try_to_narrow_possibility_space_for_group(resolved_bindings, possibility_space, group)

            remove_resolved_bindings_from_possibility_space(resolved_bindings, possibility_space)
            try_to_narrow_possibility_space_via_cascade(possibility_space)

        numbers_to_sum.append(decode_list_to_number(possibility_space, output))

    return sum(numbers_to_sum)

if __name__ == "__main__":
    f = open("../Day8.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
