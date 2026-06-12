class LanternFish:
    timer: int

    def __init__(self, timer: int):
        self.timer = timer

    def tick(self) -> bool:
        self.timer -= 1
        if self.timer < 0:
            self.timer = 6
            return True

        return False

def part_one(lines: list[str]) -> int:
    fish_strs = lines[0].split(",")

    fishes: list[LanternFish] = []
    for fish_str in fish_strs:
        fishes.append(LanternFish(int(fish_str)))

    for day in range(80):
        initial_count = len(fishes)
        for i in range(initial_count):
            fish = fishes[i]
            if fish.tick():
                fishes.append(LanternFish(8))

    return len(fishes)

def part_two(lines: list[str]) -> int:
    fish_strs = lines[0].split(",")

    fishes: list[int] = [0] * 9
    for fish_str in fish_strs:
        fishes[int(fish_str)] += 1

    for day in range(256):
        lantern_fish_to_add = fishes[0]
        fishes[0] = fishes[1]
        fishes[1] = fishes[2]
        fishes[2] = fishes[3]
        fishes[3] = fishes[4]
        fishes[4] = fishes[5]
        fishes[5] = fishes[6]
        fishes[6] = fishes[7]
        fishes[7] = fishes[8]
        fishes[8] = 0

        fishes[8] += lantern_fish_to_add
        fishes[6] += lantern_fish_to_add

    return sum(fishes)

if __name__ == "__main__":
    f = open("../Day6.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
