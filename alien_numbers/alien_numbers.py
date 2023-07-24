def source_to_decimal(alien_number, source_language):
    N_base = len(source_language)
    result = 0
    for an in alien_number:
        result = N_base*result + source_language.find(an)
    return result

def decimal_to_target(decimal, target_language):
    N_base = len(target_language)
    translation = ""
    while decimal != 0:
        remainder = decimal % N_base
        decimal //= N_base
        translation = target_language[remainder] + translation
    return translation

N = int(input())
for i in range(N):
    alien_number, source_language, target_language = input().split()
    decimal_repr = source_to_decimal(alien_number, source_language)
    translation = decimal_to_target(decimal_repr, target_language)
    print(f"Case #{i + 1}: {translation}")