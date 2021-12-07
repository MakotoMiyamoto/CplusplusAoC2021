def main():
    with open("in.txt") as f:
        raw_bingo = f.readlines()
    bingo = [thing.strip("\n") for thing in raw_bingo]
    called_numbers = bingo[0].split(",")
    bingo_rows = []
    all_numbers = []
    sum_of_rems = 0
    for line_number, row in enumerate(bingo[1:]):
        if line_number % 6 != 0:
            bingo_rows.append([value for value in row.split(" ") if value != ""])
    bingo_boards = [bingo_rows[n:n+5] for n in range(0, len(bingo_rows), 5)]

    for board in bingo_boards:
        for row in board:
            for space in row:
                all_numbers.append(space)

    def check_last_winner():
        for just_called in called_numbers:
            for index, number in enumerate(all_numbers):
                if number == just_called:
                    all_numbers[index] = "X"
            updated_rows = [all_numbers[n:n+5] for n in range(0, len(all_numbers), 5)]
            updated_boards = [updated_rows[n:n+5] for n in range(0, len(updated_rows), 5)]
            for index, board in enumerate(updated_boards):
                for i in range(5):
                    if (board[i][0] == board[i][1] == board[i][2] == board[i][3] == board[i][4] == "X")\
                            or (board[0][i] == board[1][i] == board[2][i] == board[3][i] == board[4][i] == "X"):
                        updated_boards[index] = None
                    remaining_boards = [last for last in updated_boards if last is not None]
                    if len(remaining_boards) == 1:
                        return remaining_boards, just_called

    last_board, last_number = check_last_winner()[0][0], check_last_winner()[1]
    remaining_calls = called_numbers[called_numbers.index(last_number):]

    def determine_last_score():
        for just_called in remaining_calls:
            for row_index, row in enumerate(last_board):
                for number_index, number in enumerate(row):
                    if number == just_called:
                        last_board[row_index][number_index] = "X"
            for i in range(5):
                if (last_board[i][0] == last_board[i][1] == last_board[i][2] == last_board[i][3] == last_board[i][4] == "X")\
                        or (last_board[0][i] == last_board[1][i] == last_board[2][i] == last_board[3][i] == last_board[4][i] == "X"):
                    print(last_board)
                    return last_board, int(just_called)

    results = determine_last_score()
    for row in results[0]:
        for item in row:
            try:
                sum_of_rems += int(item)
            except ValueError:
                pass

    print(f"Sum of remaining numbers: {sum_of_rems}\n"
          f"Last number called:       {results[1]}\n"
          f"Board score:              {sum_of_rems * results[1]}\n")


if __name__ == "__main__":
    main()