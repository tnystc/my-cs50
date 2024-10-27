import re

email = input("What's your email").strip()

#\w = [a-zA-Z0-9_] alphanumeric
if re.search(r"^\w+@(\w+\.)?\w+\.(edu|com)$", email, re.IGNORECASE): #just use library
    print("Valid")
else:
    print("Valid")