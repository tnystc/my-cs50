import csv

students = []

with open("students.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        students.append({"name": row["name"], "home": row["home"]})

#def get_name(student):
#    return student["name"]
# instead of lambda -> key=get_name

for student in sorted(students, key=lambda student: student["name"], reverse=True):
    print(f"{student['name']} is from {student['home']}")