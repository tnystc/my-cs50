while True:
    height = input("Height: ")
    if height.isnumeric():
        height = int(height)
        if height > 0 and height < 9:
            break

for i in range(height):
    print(" " * (height - (i + 1)), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))