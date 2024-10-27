import csv
from cs50 import SQL


db = SQL("sqlite:///roster.db")

with open("students.csv") as file:
    dbReader = csv.DictReader(file)
    for row in dbReader:
        house = row["house"]
        name = row["student_name"]

        student_id = db.execute("SELECT id FROM students WHERE student_name = ?", name)
        house_id = db.execute("SELECT id FROM houses WHERE house = ?", house)

        db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student_id[0]["id"], house_id[0]["id"])


