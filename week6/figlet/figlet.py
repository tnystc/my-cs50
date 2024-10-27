from sys import argv
from sys import exit
from pyfiglet import Figlet
from random import randint

figlet = Figlet()
list = figlet.getFonts()

if len(argv) == 1:
    s = input('Input: ')
    figlet.setFont(font=list[randint(0, len(list) - 1)])
    print(figlet.renderText(s))
    exit(0)

if len(argv) == 3:
    if argv[1].lower() == '-f' or argv[1].lower() == '--font':
        f = argv[2]
        if f in list:
            s = input('Input: ')
            figlet.setFont(font=f)
            print(figlet.renderText(s))
            exit(0)


print('Invalid usage')
exit(1)