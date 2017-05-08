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

## example fake, valid IBANs
valid_ibans = [
              "AL90 2081 1008 0000 0010 3953 1801",
              "AT13 1490 0220 1001 0999",
              "BE68 8440 1037 0034",
              "CZ42 0100 0000 1955 0503 0267",
              "EE34 2200 2210 3412 6658",
              "FI98 1428 3500 1711 41",
              "FR76 3006 6100 4100 0105 7380 116",
              "DE12 5001 0517 0648 4898 90",
              "HU29 1170 8001 2054 7794 0000 0000",
              "IE92 BOFI 9000 1710 0279 52",
              "IT68 D030 0203 2800 0040 0162 854",
              "LI10 0880 0000 0201 7630 6",
              "LU76 1111 0008 7296 0000",
              "MT98 MMEB 4409 3000 0000 0902 7293 051",
              "NL18 ABNA 0484 8698 68",
              "PT50 0035 0683 0000 0007 8431 1",
              "SE64 1200 0000 0121 7014 5230",
              "CH39 0870 4016 0754 7300 7",
              "SK93 1111 0000 0010 5736 1004",
              "SI56 0310 0100 1300 933",
              "ES10 2090 3200 5000 4104 5040",
              "GB96 MIDL 4027 1522 8598 82",
              "AD12 0001 2030 2003 5910 0100",
              "AT61 1904 3002 3457 3201",
              "BE68 5390 0754 7034",
              "CY17 0020 0128 0000 0012 0052 7600",
              "CZ65 0800 0000 1920 0014 5399",
              "DK50 0040 0440 1162 43",
              "EE38 2200 2210 2014 5685",
              "FI21 1234 5600 0007 85",
              "FR14 2004 1010 0505 0001 3M02 606",
              "DE89 3704 0044 0532 0130 00",
              "GI75 NWBK 0000 0000 7099 453",
              "GR16 0110 1250 0000 0001 2300 695",
              "HU42 1177 3016 1111 1018 0000 0000",
              "IS14 0159 2600 7654 5510 7303 39",
              "IE29 AIBK 9311 5212 3456 78",
              "IT60 X054 2811 1010 0000 0123 456",
              "LV80 BANK 0000 4351 9500 1",
              "LT12 1000 0111 0100 1000",
              "LU28 0019 4006 4475 0000",
              "NL91 ABNA 0417 1643 00",
              "NO93 8601 1117 947",
              "PL27 1140 2004 0000 3002 0135 5387",
              "PT50 0002 0123 1234 5678 9015 4",
              "SK31 1200 0000 1987 4263 7541",
              "SI56 1910 0000 0123 438",
              "ES80 2310 0001 1800 0001 2345",
              "SE35 5000 0000 0549 1000 0003",
              "CH39 0070 0115 2018 4917 3",
              "GB29 NWBK 6016 1331 9268 19"]

for iban in valid_ibans
    @test is_valid_iban(iban)
end

## REXPs
bban_GB_re = r"[A-Z]{4}[0-9]{14}"
@test ismatch(bban_GB_re, "WEST12345698765432")

bban_gb_rexp = IBAN.construct_bban_re(IBAN.bban_format["GB"])
@test bban_GB_re.pattern == bban_gb_rexp.pattern

@test IBAN.bban_length(IBAN.bban_format["GB"]) == 18
@test IBAN.iban_length(IBAN.bban_format["GB"]) == 22

## split IBAN
country, checksum, bban = split_iban(test_iban1)
@test country == "GB"
@test checksum == "82"
