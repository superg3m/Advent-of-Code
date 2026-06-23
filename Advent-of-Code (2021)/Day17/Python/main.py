class Point:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"

    def __eq__(self, other) -> bool:
        return self.x == other.x and self.y == other.y

def move_toward(value: int, target: int, delta: int) -> int:
    if value < target:
        return value + delta
    elif value > target:
        return value - delta

    return target

def print_grid(position_snapshots: list[Point], target_min: Point, target_max: Point):
    min_point: Point = Point(target_min.x, target_min.y)
    max_point: Point = Point(target_max.x, target_max.y)

    for pos in position_snapshots:
        min_point.x = min(min_point.x, pos.x)
        min_point.y = min(min_point.y, pos.y)

        max_point.x = max(max_point.x, pos.x)
        max_point.y = max(max_point.y, pos.y)

    total_y = abs(min_point.y) + abs(max_point.y) + 1
    total_x = abs(min_point.x) + abs(max_point.x) + 1

    for i in range(total_y):
        y = max_point.y - i
        for j in range(total_x):
            x = j - min_point.x

            p = Point(x, y)

            if y == 0 and x == 0:
                print("S", end="")
            elif p in position_snapshots:
                print("#", end="")
            elif target_min.x <= p.x <= target_max.x and target_min.y <= p.y <= target_max.y:
                print("T", end="")
            else:
                print(".", end="")

        print()

    pass

def part_one(lines: list[str]) -> int:
    line = lines[0]
    first_half, second_half = line[13:len(line)].split(", ")
    target_min = Point(int(first_half.split("..")[0].replace("x=", "")), int(second_half.split("..")[0].replace("y=", "")))
    target_max = Point(int(first_half.split("..")[1].replace("x=", "")), int(second_half.split("..")[1].replace("y=", "")))

    print(target_min, target_max)

    position = Point(0, 0)
    velocity = Point(7, 2)

    print(position)
    print(velocity)

    position_snapshots: list[Point] = [Point(position.x, position.y)]
    for step in range(7):
        position.x += velocity.x
        position.y += velocity.y

        velocity.x = move_toward(velocity.x, 0, 1)
        velocity.y -= 1

        position_snapshots.append(Point(position.x, position.y))

    print_grid(position_snapshots, target_min, target_max)

    return 0

def part_two(lines: list[str]) -> int:
    return 0

if __name__ == "__main__":
    f = open("../Day17.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
