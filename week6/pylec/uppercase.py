before = input("Before: ")
print("After: ", end="")
for c in before:
    print(c.upper(), end="")
print()

#or

before = input("Before: ")
after = before.upper()
print(f"After: {after}")