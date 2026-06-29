from __future__ import annotations

from os.path import split
from typing import Tuple

class IntegerReference:
    value: int = 0

    def __init__(self, value: int):
        self.value = value

    def __str__(self):
        return f"{self.value}"

class SnailFish:
    parent: SnailFish|None = None
    left: IntegerReference|SnailFish = 0 # not really optional because to have a SnailFish you must have a left element
    right: IntegerReference|SnailFish|None = None
    depth: int = 0

    def __init__(self, depth: int):
        self.depth = depth

    def fix_depth(self):
        if isinstance(self.left, SnailFish):
            self.left.depth = self.depth + 1
            self.left.fix_depth()

        if isinstance(self.right, SnailFish):
            self.right.depth = self.depth + 1
            self.right.fix_depth()

    def set_left(self, left: IntegerReference|SnailFish):
        if isinstance(left, SnailFish):
            left.depth = self.depth + 1
            left.parent = self

        self.left = left
        self.fix_depth()

    def set_right(self, right: IntegerReference|SnailFish|None):
        if isinstance(right, SnailFish):
            right.depth = self.depth + 1
            right.parent = self

        self.right = right
        self.fix_depth()

    # just fix this shit man
    def explode(self) -> bool:
        modified: bool = False

        if self.is_regular_pair():
            leftmost = self.first_integer_reference_to_the_left_of_me()
            if leftmost is not None:
                modified = True
                leftmost.value += self.left.value

            rightmost = self.first_integer_reference_to_the_right_of_me()
            if rightmost is not None:
                modified = True
                rightmost.value += self.right.value

            if self.parent is not None and self.parent.left == self:
                self.parent.set_left(IntegerReference(0))
                self.parent = None
                modified = True

            if self.parent is not None and self.parent.right == self:
                self.parent.set_right(IntegerReference(0))
                self.parent = None
                modified = True

        return modified

    # TODO(Jovanni): split is wrong because it should split the leftmost regular number first!
    def split(self) -> bool:
        modified: bool = False

        leftmost_integer_reference, parent = self.get_leftmost_integer_reference_greater_than_9_and_parent()
        if leftmost_integer_reference is not None:
            new_pair = SnailFish(parent.depth + 1)
            new_pair.set_left(IntegerReference(leftmost_integer_reference.value // 2))
            new_pair.set_right(IntegerReference(int((leftmost_integer_reference.value / 2) + 0.5)))
            if parent.left == leftmost_integer_reference:
                parent.set_left(new_pair)
            else:
                parent.set_right(new_pair)

            modified = True

        return modified

    def is_regular_pair(self) -> bool:
        return isinstance(self.left, IntegerReference) and  isinstance(self.right, IntegerReference)

    def get_topmost_parent(self) -> SnailFish:
        current = self
        while current.parent is not None:
            current = current.parent

        return current

    def get_leftmost_regular_pair_ge_to_4_depth(self) -> SnailFish|None:
        if self.is_regular_pair() and self.depth >= 4:
            return self

        if isinstance(self.left, SnailFish):
            maybe_left = self.left.get_leftmost_regular_pair_ge_to_4_depth()
            if maybe_left is not None:
                return maybe_left

        if isinstance(self.right, SnailFish):
            maybe_right = self.right.get_leftmost_regular_pair_ge_to_4_depth()
            if maybe_right is not None:
                return maybe_right

        return None

    def get_leftmost_integer_reference_greater_than_9_and_parent(self) -> Tuple[IntegerReference|None, SnailFish|None]:
        if isinstance(self.left, IntegerReference) and self.left.value > 9:
            return self.left, self

        if isinstance(self.left, SnailFish):
            maybe_left, parent = self.left.get_leftmost_integer_reference_greater_than_9_and_parent()
            if maybe_left is not None:
                return maybe_left, parent

        if isinstance(self.right, IntegerReference) and self.right.value > 9:
            return self.right, self

        if isinstance(self.right, SnailFish):
            maybe_right, parent = self.right.get_leftmost_integer_reference_greater_than_9_and_parent()
            if maybe_right is not None:
                return maybe_right, parent

        return None, None

    def simulate(self):
        modified: bool = True

        while modified:
            modified = False
            leftmost_regular_pair = self.get_leftmost_regular_pair_ge_to_4_depth()
            if leftmost_regular_pair is not None:
                leftmost_regular_pair.explode()
                # print(f"After Explode:  {self.get_topmost_parent()}")
                modified = True
                continue

            if self.split():
                # print(f"After Split:    {self.get_topmost_parent()}")
                modified = True

        return self

    def first_integer_reference(self) -> IntegerReference|None:
        if isinstance(self.left, IntegerReference):
            return self.left
        elif isinstance(self.left, SnailFish):
            left_snail = self.left.first_integer_reference()
            if left_snail is not None:
                return left_snail

        if isinstance(self.right, IntegerReference):
            return self.right
        if isinstance(self.right, SnailFish):
            right_snail = self.right.first_integer_reference()
            if right_snail is not None:
                return right_snail

    def last_integer_reference(self) -> IntegerReference | None:
        if isinstance(self.right, IntegerReference):
            return self.right
        if isinstance(self.right, SnailFish):
            right_snail = self.right.last_integer_reference()
            if right_snail is not None:
                return right_snail

        if isinstance(self.left, IntegerReference):
            return self.left
        elif isinstance(self.left, SnailFish):
            left_snail = self.left.last_integer_reference()
            if left_snail is not None:
                return left_snail

        return None

    def first_integer_reference_to_the_left_of_me(self) -> IntegerReference|None:
        if self.parent is None:
            return None

        if self.parent.right == self:
            if isinstance(self.parent.left, IntegerReference):
                return self.parent.left

            return self.parent.left.last_integer_reference()
        elif self.parent.left == self:
            previous = self
            current = self.parent
            while current is not None:
                if previous == current.right:
                    if isinstance(current.left, IntegerReference):
                        return current.left

                    return current.left.last_integer_reference()

                previous = current
                current = current.parent

        return None

    def first_integer_reference_to_the_right_of_me(self) -> IntegerReference|None:
        if self.parent is None:
            return None

        if self.parent.left == self:
            if isinstance(self.parent.right, IntegerReference):
                return self.parent.right

            if isinstance(self.parent.right, SnailFish):
                return self.parent.right.first_integer_reference()
        elif self.parent.right == self:
            previous = self
            current = self.parent
            while current is not None:
                if previous == current.left:
                    if isinstance(current.right, IntegerReference):
                        return current.right

                    if isinstance(current.right, SnailFish):
                        return current.right.first_integer_reference()

                previous = current
                current = current.parent

        return None

    def magnitude(self) -> int:
        mag: int = 0

        if isinstance(self.left, SnailFish):
            mag += 3 * self.left.magnitude()
        elif isinstance(self.left, IntegerReference):
            mag += 3 * self.left.value

        if isinstance(self.right, SnailFish):
            mag += 2 * self.right.magnitude()
        elif isinstance(self.right, IntegerReference):
            mag += 2 * self.right.value

        return mag

    def __str__(self):
        if self.left is not None and self.right is not None:
            return f"[{self.left},{self.right}]"

        return f"[{self.left}]"

def snail_fish_add(left: SnailFish|None, right: SnailFish|None) -> SnailFish:
    if left.right is None:
        left.right = right
        return left
    else:
        root: SnailFish = SnailFish(0)
        root.set_left(left)
        root.set_right(right)
        return root

def consume_next_digit_literal(s: str, start: int) -> Tuple[int, int]:
    i: int = start
    ret = ""
    while s[i].isdigit():
        ret += s[i]
        i += 1

    return int(ret), i - 1

def parse_str_to_create_snail_fish_helper(to_parse: str, depth: int, start: int) -> Tuple[SnailFish, int]:
    root: SnailFish = SnailFish(depth)
    character_stack = [to_parse[start]]
    should_set_right: bool = False

    i: int = start + 1
    while len(character_stack) > 0:
        c = to_parse[i]
        if c.isdigit():
            integer, i = consume_next_digit_literal(to_parse, i)

            if should_set_right:
                root.set_right(IntegerReference(integer))
            else:
                root.set_left(IntegerReference(integer))
        elif c == "[":
            new_pair, i = parse_str_to_create_snail_fish_helper(to_parse, depth + 1, i)
            if should_set_right:
                root.set_right(new_pair)
            else:
                root.set_left(new_pair)
        elif c == "]":
            character_stack.pop()
            i -= 1
        elif c == ",":
            should_set_right = True

        i += 1

    return root, i

# [2, 3]
def parse_str_to_create_snail_fish(to_parse: str) -> SnailFish:
    root, _ = parse_str_to_create_snail_fish_helper(to_parse, 0,0)
    return root

def validation_check(topmost: SnailFish, snail: SnailFish):
    if snail != topmost and snail.parent is None:
        exit(-1)

    if isinstance(snail.left, SnailFish):
        validation_check(topmost, snail.left)

    if isinstance(snail.right, SnailFish):
        validation_check(topmost, snail.right)

def part_one(lines: list[str]) -> int:
    left: SnailFish = parse_str_to_create_snail_fish(lines[0])
    for i in range(1, len(lines)):
        line = lines[i]
        right = parse_str_to_create_snail_fish(line)
        left = snail_fish_add(left, right)
        # print(f"After Addition: {left}")
        left.simulate()
        #print()

    #print(left)
    return left.magnitude()

def part_two(lines: list[str]) -> int:
    snail_sum_permutations: list[SnailFish] = []

    for i in range(len(lines) - 1):
        for j in range(i+1, len(lines)):
            l1 = parse_str_to_create_snail_fish(lines[i])
            l2 = parse_str_to_create_snail_fish(lines[i])

            r1 = parse_str_to_create_snail_fish(lines[j])
            r2 = parse_str_to_create_snail_fish(lines[j])

            snail_sum_permutations.append(snail_fish_add(l1, r1).simulate())
            snail_sum_permutations.append(snail_fish_add(r2, l2).simulate())

    max_magnitude = 0
    for snail in snail_sum_permutations:
        max_magnitude = max(max_magnitude, snail.magnitude())

    return max_magnitude

if __name__ == "__main__":
    f = open("../Day18.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
