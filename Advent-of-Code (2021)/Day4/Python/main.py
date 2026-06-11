from typing import Tuple

class Board:
    data: list[list[str]]

    def __init__(self, ):
        self.data = []

    def check_row_win(self) -> bool:
        for i, row in enumerate(self.data):
            bingo = True
            for j, num in enumerate(row):
                if num != "x":
                    bingo = False
                    break

            if bingo:
                return True

        return False

    def check_column_win(self) -> bool:
        for col_index in range(len(self.data[0])):
            bingo = True
            for row in self.data:
                if row[col_index] != "x":
                    bingo = False
                    break

            if bingo:
                return True

        return False

    def check_diagonal_win(self) -> bool:
        for i, row in enumerate(self.data):
            if row[i] != "x":
                break

        for i, row in reversed(list(enumerate(self.data))):
            if row[i] != "x":
                return False

        return True

    def calculate_unmarked_sum(self) -> int:
        unmarked_sum = 0
        for row in self.data:
            for element in row:
                if element != "x":
                    unmarked_sum += int(element)

        return unmarked_sum

    def check_win(self) -> bool:
        return self.check_row_win() or self.check_column_win() or self.check_diagonal_win()

    def mark_winning_number(self, winning_number: str):
        for i, row in enumerate(self.data):
            for j, num in enumerate(row):
                if num == winning_number:
                    self.data[i][j] = "x"

def create_board(lines: list[str], start_line_index: int) -> Tuple[Board, int]:
    ret: Board = Board()

    index = start_line_index
    while lines[index] != "":
        ret.data.append(lines[index].split())
        index += 1

        if index >= len(lines):
            return ret, index

    return ret, index+1


def print_board(board: Board):
    for row in board.data:
        print(row)

def part_one(lines: list[str]) -> int:
    winning_numbers = lines[0].split(",")

    index = 2
    boards: list[Board] = []
    while index < len(lines):
        board, index = create_board(lines, index)
        boards.append(board)

    winning_boards: list[Tuple[int, Board]] = []
    for winning_number in winning_numbers:
        for i, board in enumerate(boards):
            board.mark_winning_number(winning_number)
            if board.check_win():
                unmarked_sum = board.calculate_unmarked_sum()
                winning_boards.append((i, board))
                return unmarked_sum * int(winning_number)

    return 0

def part_two(lines: list[str]) -> int:
    winning_numbers = lines[0].split(",")

    index = 2
    boards: list[Board] = []
    while index < len(lines):
        board, index = create_board(lines, index)
        boards.append(board)

    winning_boards: list[Tuple[int, Board]] = []
    winning_board_indices: list[int] = []
    for winning_number in winning_numbers:
        for i, board in enumerate(boards):
            if i in winning_board_indices:
                continue

            board.mark_winning_number(winning_number)
            if board.check_win():
                winning_board_indices.append(i)
                winning_boards.append((int(winning_number), board))

    last_winning_number, last_board = winning_boards[len(winning_boards) - 1]
    unmarked_sum = last_board.calculate_unmarked_sum()
    return unmarked_sum * last_winning_number

if __name__ == "__main__":
    f = open("../Day4.txt")
    lines = f.read().splitlines()
    print(f"part1: {part_one(lines)}")
    print(f"part2: {part_two(lines)}")
    f.close()
