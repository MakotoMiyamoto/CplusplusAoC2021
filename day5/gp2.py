def main():
    with open("in.txt") as f:
        lines = f.readlines()
    lines = [thing.strip("\n") for thing in lines]
    lines = [thing.split(" -> ") for thing in lines]
    lines = [point.split(',') for direction in lines for point in direction]
    lines = [lines[n:n + 2] for n in range(0, len(lines), 2)]

    rows, cols = (1000, 1000)
    vent_map = [[0 for i in range(cols)] for j in range(rows)]

    for two_points in lines:
        x1 = int(two_points[0][0])
        y1 = int(two_points[0][1])
        x2 = int(two_points[1][0])
        y2 = int(two_points[1][1])
        if x1 == x2:
            if y1 < y2:
                for y in range(y1, y2 + 1):
                    vent_map[y][x1] += 1
            else:
                for y in range(y2, y1 + 1):
                    vent_map[y][x1] += 1
        elif y1 == y2:
            if x1 < x2:
                for x in range(x1, x2 + 1):
                    vent_map[y1][x] += 1
            else:
                for x in range(x2, x1 + 1):
                    vent_map[y1][x] += 1
        else:
            if x1 < x2:
                if y1 < y2:
                    for x in range(x1, x2 + 1):
                        vent_map[y1][x] += 1
                        y1 += 1
                else:
                    for x in range(x1, x2 + 1):
                        vent_map[y1][x] += 1
                        y1 -= 1
            else:
                if y1 < y2:
                    for x in range(x2, x1 + 1):
                        vent_map[y2][x] += 1
                        y2 -= 1
                else:
                    for x in range(x2, x1 + 1):
                        vent_map[y2][x] += 1
                        y2 += 1
                        
    print(f"There are a total of {len([point for row in vent_map for point in row if point > 1])} intersections.")


if __name__ == "__main__":
    main()
