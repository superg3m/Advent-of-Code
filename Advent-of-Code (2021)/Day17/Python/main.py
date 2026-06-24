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

def hit_target(p: Point, target_min: Point, target_max: Point) -> bool:
    return target_min.x <= p.x <= target_max.x and target_min.y <= p.y <= target_max.y

def summation(n: int) -> int:
    if n == 0:
        return 0

    return n + summation(n - 1)

"""
def launch_probe(initial_velocity: Point, target_min: Point, target_max: Point) -> int:
    max_y = 0
    position = Point(0, 0)
    velocity = Point(0, 0)

    while True:
        position.x += velocity.x
        position.y += velocity.y
        velocity.x = move_toward(velocity.x, 0, 1)
        velocity.y -= 1

        position_snapshots.append(Point(position.x, position.y))

        if hit_target(position, target_min, target_max):
            max_y = max(max_y, position.y)
            break

        if position.y < target_min.y:
            break

    return max_y
"""

def part_one(lines: list[str]) -> int:
    line = lines[0]
    first_half, second_half = line[13:len(line)].split(", ")
    target_min = Point(int(first_half.split("..")[0].replace("x=", "")), int(second_half.split("..")[0].replace("y=", "")))
    target_max = Point(int(first_half.split("..")[1].replace("x=", "")), int(second_half.split("..")[1].replace("y=", "")))

    best_velocity = Point(0, 0)
    best_x = 0

    while True:
        if best_x != 0 and not hit_target(Point(summation(best_velocity.x), target_min.y), target_min, target_max):
            break
        elif hit_target(Point(summation(best_velocity.x), target_max.y), target_min, target_max):
            best_x = best_velocity.x

        best_velocity.x += 1

    best_velocity.x = best_x
    final_position_snapshots = []

    initial_velocity = Point(best_velocity.x, best_velocity.y)
    for _ in range(1000):
        position = Point(0, 0)
        velocity = Point(initial_velocity.x, initial_velocity.y)
        position_snapshots: list[Point] = [Point(position.x, position.y)]
        while True:
            position.x += velocity.x
            position.y += velocity.y

            velocity.x = move_toward(velocity.x, 0, 1)
            velocity.y -= 1

            position_snapshots.append(Point(position.x, position.y))

            if hit_target(position, target_min, target_max):
                best_velocity = Point(initial_velocity.x, initial_velocity.y)
                final_position_snapshots = position_snapshots
                break

            if position.y < target_min.y:
                break

        initial_velocity.y += 1

    print(best_velocity)
    print_grid(final_position_snapshots, target_min, target_max)

    max_y = 0
    for pos in final_position_snapshots:
        max_y = max(max_y, pos.y)

    return max_y

def part_two(lines: list[str]) -> int:
    line = lines[0]
    first_half, second_half = line[13:len(line)].split(", ")
    target_min = Point(int(first_half.split("..")[0].replace("x=", "")), int(second_half.split("..")[0].replace("y=", "")))
    target_max = Point(int(first_half.split("..")[1].replace("x=", "")), int(second_half.split("..")[1].replace("y=", "")))

    best_velocity = Point(0, 0)
    best_x = 0

    while True:
        if best_x != 0 and not hit_target(Point(summation(best_velocity.x), target_min.y), target_min, target_max):
            break
        elif hit_target(Point(summation(best_velocity.x), target_max.y), target_min, target_max):
            best_x = best_velocity.x

        best_velocity.x += 1

    best_velocity.x = best_x
    initial_velocities: list[Point] = []
    initial_velocity = Point(best_velocity.x, best_velocity.y)
    for _ in range(1000):
        position = Point(0, 0)
        velocity = Point(initial_velocity.x, initial_velocity.y)
        position_snapshots: list[Point] = [Point(position.x, position.y)]
        while True:
            position.x += velocity.x
            position.y += velocity.y

            velocity.x = move_toward(velocity.x, 0, 1)
            velocity.y -= 1

            position_snapshots.append(Point(position.x, position.y))

            if hit_target(position, target_min, target_max):
                initial_velocities.append(Point(initial_velocity.x, initial_velocity.y))
                break

            if position.y < target_min.y:
                break

        initial_velocity.y += 1

    return len(initial_velocities)

if __name__ == "__main__":
    f = open("../Day17.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
