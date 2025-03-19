even = 0
odd = 0
text = input("Input string: ")
for char in text:
    if char.isdigit():
        if int(char) % 2 == 0:
            even += 1
        else:
            odd += 1

print("Even values count: ", even)
print("Odd values count: ", odd)

