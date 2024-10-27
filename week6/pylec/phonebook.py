import csv

file = open('phonebook.csv', 'a')

name = input('name: ')
number = input('number: ')

#writer = csv.writer(file)
writer = csv.DictWriter(file, fieldnames = ['name', 'number'])

#writer.writerow([name, number])
writer.writerow({'name': name, 'number': number})

file.close() #normally!!!! with open(...) as file: