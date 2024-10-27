from sys import argv

if len(argv) == 2:
    print(f"Hello, {argv[1]}")
else:
    print("Hello, world")

for arg in argv[1:2]:
    print(arg)
