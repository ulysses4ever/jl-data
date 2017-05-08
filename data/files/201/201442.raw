using Soundex

# Check basic examples
@assert soundex("Robert") == "R163"
@assert soundex("Rupert") == "R163"
@assert soundex("Rubin") == "R150"

# Verify double-coding gives single output when 's' and 'c' are separated by a 'h' or 'w'
@assert soundex("Ashcraft") == "A261"
@assert soundex("Ashcroft") == "A261"

# Verify double-coding gives double output when 'z' and 'k' are separated by a vowel
@assert soundex("Tymczak") == "T522"

# Verify double-coding for initial 'P' and 'f'
@assert soundex("Pfister") == "P236"

# Verify 0-padding is done correctly
@assert soundex("a") == "A000"
@assert soundex("ab") == "A100"
@assert soundex("abc") == "A120"
@assert soundex("abcd") == "A123"
