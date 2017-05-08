using Lingua
using Base.Test

@test stem("благодаря",    "bg") == "благодар"  # remove -я
@test stem("това",         "bg") == "тов"       # remove -а
@test stem("добре",        "bg") == "добр"      # remove -е
@test stem("какво",        "bg") == "какв"      # remove -о
@test stem("сигурен",      "bg") == "сигурн"    # remove -е- from -ен
@test stem("веднъж",       "bg") == "веднж"     # remove -ъ- from -ъ�
@test stem("единственият", "bg") == "единствн"  # remove article: -ият
@test stem("история",      "bg") == "истор"     # remove article: -ия
@test stem("животът",      "bg") == "живот"     # remove article: -ът
@test stem("работата",     "bg") == "раб"       # remove article: -та
@test stem("когато",       "bg") == "ког"       # remove article: -то
@test stem("дяволите",     "bg") == "дявол"     # remove article: -те
@test stem("правят",       "bg") == "прав"      # remove article: -ят
@test stem("ключовете",    "bg") == "ключ"      # remove plural: -ове
@test stem("търговци",     "bg") == "търг"      # remove plural: remove -вци from -овци
@test stem("запази",       "bg") == "запаг"     # remove plural: replace -зи with -г
@test stem("приятели",     "bg") == "приятял"   # remove plural: replace -е�и with -я�
@test stem("седмици",      "bg") == "седмик"    # remove plural: replace -ци with -к
@test stem("момчетата",    "bg") == "момч"      # remove plural: -та
@test stem("сънищата",     "bg") == "сън"       # remove plural: -ища
@test stem("спаси",        "bg") == "спах"      # remove plural: replace -си with -х
@test stem("всички",       "bg") == "всичк"     # remove plural: -и
