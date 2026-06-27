from __future__ import annotations

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
    def explode(self, special_snail_left_explode: bool) -> bool:
        if not special_snail_left_explode and self.depth != 4:
            return False

        modified: bool = False
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

    def split(self) -> bool:
        modified: bool = False

        if isinstance(self.left, IntegerReference) and self.left.value >= 10:
            new_pair = SnailFish(self.depth + 1)
            new_pair.set_left(IntegerReference(self.left.value // 2))
            new_pair.set_right(IntegerReference(int((self.left.value / 2) + 0.5)))
            self.set_left(new_pair)
            modified = True

        if isinstance(self.right, IntegerReference) and self.right.value >= 10:
            new_pair = SnailFish(self.depth + 1)
            new_pair.set_left(IntegerReference(self.right.value // 2))
            new_pair.set_right(IntegerReference(int((self.right.value / 2) + 0.5)))
            self.set_right(new_pair)
            modified = True

        return modified

    def is_regular_pair(self) -> bool:
        return isinstance(self.left, IntegerReference) and  isinstance(self.right, IntegerReference)

    def simulate(self):
        modified: bool = True

        while modified:
            modified = False
            current = self
            while isinstance(current, SnailFish):
                if current.depth >= 4 and current.is_regular_pair():
                    modified = current.explode(True)
                    break

                current = current.left

            modified = self.split() or modified

        if isinstance(self.left, SnailFish):
            modified = self.left.simulate()

        if isinstance(self.right, SnailFish):
            modified = self.right.simulate() or modified

        current = self
        while isinstance(current, SnailFish):
            if current.depth >= 4 and current.is_regular_pair():
                modified = current.explode(True) or modified
                break

            current = current.left

        modified = self.split() or modified

        if modified:
            self.simulate()

        return modified

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

            return self.parent.right.first_integer_reference()
        elif self.parent.right == self:
            previous = self
            current = self.parent
            while current is not None:
                if previous == current.left:
                    if isinstance(current.right, IntegerReference):
                        return current.right

                    return current.right.first_integer_reference()

                previous = current
                current = current.parent

        return None


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

def part_one(lines: list[str]) -> int:
    """
    left: SnailFish = parse_str_to_create_snail_fish("[[[[4,3],4],4],[7,[[8,4],9]]]")
    right: SnailFish = parse_str_to_create_snail_fish("[1,1]")
    root: SnailFish = snail_fish_add(left, right)

    print(root)
    root.simulate()
    print(root)
    """

    left: SnailFish = parse_str_to_create_snail_fish(lines[0])
    for i in range(1, len(lines)):
        line = lines[i]
        right = parse_str_to_create_snail_fish(line)
        left = snail_fish_add(left, right)

    left.simulate()
    print(left)

    return 0

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day18.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
