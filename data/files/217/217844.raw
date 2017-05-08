using Transformator
  const e1 = 200 # [V] SEM - siły elektromotoryczne
  const e2 = 100 # [V]
  const R2 = 200 # [ohm]
  const X2 = 300 # [ohm]
  const i1 = 5 	 # [A]
  const i2 = 10  # [A]
  const rfe = 50 # [ohm]
  # przekladnia(200,100)
  x = przekladnia(e1, e2)
  R2_prim = rez_2_prim(x, R2)
  X2_prim = reak_2_prim(x, X2)
  straty = straty_uzwojen(i1,i2, R2, R2_prim)
  c = 1 / rfe
  straty_w_rfe = straty_w_rdzeniu(e1, c)
  sumaryczne_straty = straty + straty_w_rfe
  sprawnosc = moc_pierwotna(i1, e1) / moc_wtorna(i2, e2)

  # # R1, R2_prim - rezystancja uzwojenia pierwotnego i przeliczona na stronę pierwotną, rezystancja uzwojenia wtórnego
  # # X1, X2_prim - reaktancje rozproszeń uzwojenia pierwotnego i przeliczona na stronę pierwotną reaktancji rozproszeń uzwojenia wtórnego

  println("Przekładnia transformatora: ", x)
  println("Rezystancja uzwojenia pierwotnego: ", R2)
  println("Reaktancja rozproszeń uzwojenia pierwotnego: ", X2)
  println("Straty całkowite w uzwojeniu: ", straty)
  println("Sprawnosc transformatora: ", sprawnosc)
  println("Straty w rdzeniu: ", straty_w_rfe)
  println("Straty sumaryczne: ", sumaryczne_straty)

