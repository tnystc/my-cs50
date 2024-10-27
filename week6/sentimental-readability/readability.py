from cs50 import get_string
import re


text = get_string("Text: ")
letterCount = 0
sentenceCount = 0

n = text.strip()

for i in range(0, len(text.strip())):
    if text[i].strip().isalpha():
        letterCount += 1

for i in range(0, len(text.strip())):
    if text[i].strip() == '!' or text[i].strip() == '.' or text[i].strip() == '?':
        sentenceCount += 1

L = letterCount / len(text.split()) * 100
S = sentenceCount / len(text.split()) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")

print("Letter ", letterCount)
print("Sentece ", sentenceCount)
print("Word ", len(text.split()))
