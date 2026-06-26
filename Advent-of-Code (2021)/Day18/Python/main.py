from __future__ import annotations

class SnailFish:
    parent: SnailFish|None = None
    left: int|SnailFish = 0 # not really optional because to have a SnailFish you must have a left element
    right: int|SnailFish|None
    depth: int = 0

    def set_left(self, left: int|SnailFish):
        if isinstance(left, SnailFish):
            left.depth = self.depth + 1
            left.parent = self

        self.left = left

    def set_right(self, right: int|SnailFish|None):
        if isinstance(right, SnailFish):
            right.depth = self.depth + 1
            right.parent = self

        self.right = right

    def explode(self):
        current = self.parent
        while current:
            if isinstance(current.left, int) and isinstance(self.left, int):
                current.left += self.left

            if isinstance(current.right, int) and isinstance(self.right, int):
                current.right += self.right

            current = current.parent

        if self.parent.left == self:
            self.parent.set_left(self.parent.right)
            self.parent = None

        if self.parent and self.parent.right == self:
            self.parent.set_right(None)
            self.parent = None

    def split(self):
        pass

    def simulate(self):
        if self.depth == 4:
            self.explode()

    def __str__(self):
        if self.left and self.right:
            return f"[{self.left}, {self.right}]"

        return f"[{self.left}]"

def part_one(lines: list[str]) -> int:
    root = SnailFish()

    parent = SnailFish()

    parent_left = SnailFish()
    parent_left.set_left(1)
    parent_left.set_right(2)

    parent.set_left(parent_left)
    parent.set_right(3)

    root.set_left(53)
    root.set_right(parent)

    print(root)
    parent_left.explode()
    print(root)

    return 0

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day18.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
