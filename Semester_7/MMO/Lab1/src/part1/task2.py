def count_pairs(word):
    upper_pairs = 0
    lower_pairs = 0
    total_letters = 0

    for i in range(len(word) - 1):
        if word[i].isalpha():
            total_letters += 1
            if word[i].isupper() and word[i + 1].isupper():
                upper_pairs += 1
            elif word[i].islower() and word[i + 1].islower():
                lower_pairs += 1

    if word[-1].isalpha():
        total_letters += 1

    return upper_pairs, lower_pairs, total_letters


input_word = input("Input string: ")
upper, lower, letters = count_pairs(input_word)

print("Upper pairs: ", upper)
print("Lower pairs: ", lower)
print("Letters: ", letters)
