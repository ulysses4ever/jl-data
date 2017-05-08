const re_format = Dict([('a', "[A-Z]"), ('c', "[A-Z0-9]"), ('n', "[0-9]")])

const iban_global_re = r"([A-Z]{2})([0-9]{2})([A-Z0-9]{10,34})"

const iban_country_length = Dict([
                            ("AL", 28),  # Albania
                            ("AD", 24),  # Andorra
                            ("AE", 23),  # United Arab Emirates
                            ("AT", 20),  # Austria
                            ("AZ", 28),  # Azerbaijan
                            ("BA", 20),  # Bosnia and Herzegovina
                            ("BE", 16),  # Belgium
                            ("BG", 22),  # Bulgaria
                            ("BH", 22),  # Bahrain
                            ("BR", 29),  # Brazil
                            ("CH", 21),  # Switzerland
                            ("CR", 21),  # Costa Rica
                            ("CY", 28),  # Cyprus
                            ("CZ", 24),  # Czech Republic
                            ("DE", 22),  # Germany
                            ("DK", 18),  # Denmark
                            ("DO", 28),  # Dominican Republic
                            ("EE", 20),  # Estonia
                            ("ES", 24),  # Spain
                            ("FI", 18),  # Finland
                            ("FO", 18),  # Faroe Islands
                            ("FR", 27),  # France 
                            ("GB", 22),  # United Kingdom
                            ("GE", 22),  # Georgia
                            ("GI", 23),  # Gibraltar
                            ("GL", 18),  # Greenland
                            ("GR", 27),  # Greece
                            ("GT", 28),  # Guatemala
                            ("HR", 21),  # Croatia
                            ("HU", 28),  # Hungary
                            ("IE", 22),  # Ireland
                            ("IL", 23),  # Israel
                            ("IS", 26),  # Iceland
                            ("IT", 27),  # Italy
                            ("JO", 30),  # Jordan
                            ("KZ", 20),  # Kazakhstan
                            ("KW", 30),  # Kuwait
                            ("LB", 28),  # Lebanon
                            ("LI", 21),  # Liechtenstein
                            ("LT", 20),  # Lithuania
                            ("LU", 20),  # Luxembourg
                            ("LV", 21),  # Latvia
                            ("MC", 27),  # Monaco
                            ("MD", 24),  # Moldova
                            ("ME", 22),  # Montenegro
                            ("MK", 19),  # Macedonia
                            ("MT", 31),  # Malta
                            ("MR", 27),  # Mauritania
                            ("MU", 30),  # Mauritius
                            ("NL", 18),  # Netherlands
                            ("NO", 15),  # Norway
                            ("PS", 29),  # Palestine
                            ("PK", 24),  # Pakistan
                            ("PL", 28),  # Poland
                            ("PT", 25),  # Portugal
                            ("QA", 29),  # Qatar
                            ("RO", 24),  # Romania
                            ("RS", 22),  # Serbia
                            ("SA", 24),  # Saudi Arabia
                            ("SE", 24),  # Sweden
                            ("SI", 19),  # Slovenia
                            ("SK", 24),  # Slovakia
                            ("SM", 27),  # San Marino
                            ("TN", 24),  # Tunisia
                            ("TR", 26),  # Turkey
                            ("VG", 24)  # British Virgin Islands
                             ])

const bban_format = Dict([
                          ("GB", ((4, 'a'), (14, 'n'))),
                          ("DE", ((18, 'n'), ))
                          ])
