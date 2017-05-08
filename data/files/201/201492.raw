using Lucas, Base.Test

# strcut

@test strcut("ello", 1) == "…"
@test strcut("ello", 2) == "e…"
@test strcut("ello", 3) == "el…"
@test strcut("ello", 4) == "ello"

@test strcut("elo", 1, dots=false) == "e"
@test strcut("elo", 2, dots=false) == "el"
@test strcut("elo", 3, dots=false) == "elo"

@test strcut("ที่รัก", 1) == "…"
@test strcut("ที่รัก", 2) == "ที่…"
@test strcut("ที่รัก", 3) == "ที่รัก"
@test strcut("ที่รักa",3) == "ที่รั…"

@test strcut("ที่รัก", 1, dots=false) == "ที่"
@test strcut("ที่รัก", 2, dots=false) == "ที่รั"
@test strcut("ที่รัก", 3, dots=false) == "ที่รัก"
@test strcut("ที่รักa",3, dots=false) == "ที่รัก"

