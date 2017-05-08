using IBAN
using Base.Test

## valid IBANs
test_iban1 = "GB82 WEST 1234 5698 7654 32"

@test is_valid_iban(test_iban1)
@test is_valid_iban(replace(test_iban1, " ", ""))
@test is_valid_iban(replace(test_iban1, " ", ","))

## invalid IBANs
test_wban1 = "GB82 WEST 2134 5698 7654 32"
@test_throws ErrorException is_valid_iban(test_wban1)
test_wban2 = "GX82 WEST 1234 5698 7654 32"
@test_throws ErrorException is_valid_iban(test_wban2)
test_wban3 = "GB82 WEST 1234 5698 7654 3200"
@test_throws ErrorException is_valid_iban(test_wban3)

## REXPs
bban_GB_re = r"[A-Z]{4}[0-9]{14}"
@test ismatch(bban_GB_re, "WEST12345698765432")

bban_gb_rexp = construct_bban_re(bban_format["GB"])
@test bban_GB_re == bban_gb_rexp

@test bban_length(bban_format["GB"]) == 18
@test iban_length(bban_format["GB"]) == 22

## split IBAN
country, checksum, bban = split_iban(test_iban1)
@test country == "GB"
@test checksum == "82"
