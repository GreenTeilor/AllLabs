def is_password_good(password):
    has_upper = any(char.isupper() for char in password)
    has_digit = any(char.isdigit() for char in password)

    return len(password) >= 8 and has_upper and has_digit


print(is_password_good("GoodPassword2"))
print(is_password_good("bad_password"))
