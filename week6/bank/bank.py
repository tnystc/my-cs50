from sys import exit

greet = input('Greeting: ')

if 'hello' in greet.lower():
    print('$0')
    exit(0)


if 'h' in greet[0].lower():
    print('$20')
    exit(0)

print('$100')
