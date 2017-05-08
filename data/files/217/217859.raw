module Transformator
  export przekladnia, rez_2_prim, reak_2_prim, straty_uzwojen, moc_pierwotna, moc_wtorna, straty_w_rdzeniu

  # wylicza przekładnię transformatora
  function przekladnia(e1, e2)
      e1 /  e2
  end

  # wylicza przeliczoną na stronę pierwotną rezystancję uzwojenia wtórnego
  function rez_2_prim(przek, R2)
      przek^2 * R2
  end

  #wylicza  przeliczoną na stronę pierwotną reaktancję rozproszeń uzwojenia wtórnego
  function reak_2_prim(przek, X2)
      przek^2 * X2
  end

  # straty całkowite w uzwojeniu
  function straty_uzwojen(i1, i2, r1, r2)
      i1^2 * r1 + i2^2 * r2
  end

  # moc
  function moc_pierwotna(i1, e1)
      i1*e1
  end

  function moc_wtorna(i2, e2)
      i2 * e2
  end

  function straty_w_rdzeniu(e1, c)
	    e1^2 * c
  end
end
