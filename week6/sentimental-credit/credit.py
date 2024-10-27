import cs50
import sys


def main():
    cardnumber = cs50.get_int("Number: ")
    cardlenght = len(str(cardnumber))
    if cardlenght != 16 and cardlenght != 15 and cardlenght != 13:
        print("INVALID")
        sys.exit()

    if luhn_algorithm(cardnumber) % 10 != 0:
        print("INVALID")
        sys.exit()

    check = int(str(cardnumber)[:2])
    if (check // 10 == 3) and (check % 10 == 4 or check % 10 == 7):
        print("AMEX")
    elif check // 10 == 4:
        print("VISA")
    elif (check // 10 == 5) and (check % 10 <= 5 and check % 10 >= 1):
        print("MASTERCARD")
    else:
        print("INVALID")


def luhn_algorithm(cardnumber):
    sum = 0
    for i in range(len(str(cardnumber))-2, -1, -2):
        num = int(str(cardnumber)[i])
        num *= 2
        digit1 = num // 10
        digit2 = num % 10
        sum += digit1 + digit2
    for i in range(len(str(cardnumber))-1, -1, -2):
        sum += int(str(cardnumber)[i])
    return sum


if __name__ == "__main__":
    main()