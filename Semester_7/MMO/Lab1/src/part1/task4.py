def scrabble_score(word):
    scores = {
        1: "AEIOULNSTR",
        2: "DG",
        3: "BCMP",
        4: "FHVWY",
        5: "K",
        8: "JX",
        10: "QZ"
    }

    score_dict = {}
    for score, letters in scores.items():
        for letter in letters:
            score_dict[letter] = score

    total_score = 0
    for letter in word.upper():
        total_score += score_dict.get(letter, 0)

    return total_score


input_word = input("Input word: ")
result = scrabble_score(input_word)

print("Word costs: ", result)
