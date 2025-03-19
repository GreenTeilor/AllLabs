def sum_negative_elements(lst):
    return sum(x for x in lst if x < 0)


def sum_between_first_two_zeros(lst):
    try:
        first_zero_index = lst.index(0)
        second_zero_index = lst.index(0, first_zero_index + 1)
        return sum(lst[first_zero_index + 1:second_zero_index])
    except ValueError:
        return 0


numbers = [0, -11, 12, 42, 1, -13, 0, 4, -7]

negative_sum = sum_negative_elements(numbers)
sum_between_zeros = sum_between_first_two_zeros(numbers)

print("Negative elements sum: ", negative_sum)
print("Sum between 1-st 2 zeros: ", sum_between_zeros)
