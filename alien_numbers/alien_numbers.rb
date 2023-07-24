def source_to_decimal(alien_number, source_language)
    n_base = source_language.length
    result = 0
    for an in alien_number.each_char do
        result = n_base*result + source_language.index(an)
    end
    return result
end

def decimal_to_target(decimal, target_language)
    n_base = target_language.length
    translation = ""
    while decimal != 0 do
        remainder = decimal % n_base
        decimal /= n_base
        translation = target_language[remainder] + translation
    end
    return translation
end

n = gets.to_i
for i in 1..n
    alien_number, source_language, target_language = gets.split()
    decimal_repr = source_to_decimal(alien_number, source_language)
    puts decimal_repr
    translation = decimal_to_target(decimal_repr, target_language)
    print("Case \##{i}: #{translation}\n")
end
