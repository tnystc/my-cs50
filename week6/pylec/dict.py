#or dict()
people = {
    "Carter": "+1-333-444-5555"
    "David": "+1-222-111-4444"
}
name = input("Name: ")
if name in people:
    print(f"Number: {people[name]}")

