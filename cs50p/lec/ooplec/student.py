class Student():
    def __init__(self, name, house, patronus):
        if not name:
            raise ValueError("Missing name")
        if house not in ["Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"]:
            raise ValueError("Invalid house")
        self.name = name
        self.house = house
        self.patronus = patronus

    def __str__(self):
        return f"{self.name} from {self.house}"


    #Getter
    @property
    def house(self):
        return self._house

    #Setter
    @house.setter
    def house(self, house):
        if house not in ["Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"]:
            raise ValueError("Invalid house")
        self._house = house


    def charm(self):
        match self.patronus:
            case "Stag":
                return "Semoji"
            case "Otter":
                return "Oemoji"
            case "Jack Russel terrier":
                return "Jemoji"
            case _:
                return "wand"


def main():
    student = get_student()
    print(f"{student.name} from {student.house}")
    print("Expecto Patronum!")
    print(student.charm())


def get_student():
    name = input("Name: ")
    house = input("House: ")
    patronus = input("Patronus: ")
    try:
        return Student(name, house, patronus)
    except ValueError:
        ...


if __name__ == "__main__":
    main()