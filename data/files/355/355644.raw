function printError (integral, f, g, spacing, intervals)

  for i=[1:size(intervals,1)]
    a = intervals [i,1]
    b = intervals [i,2]
    println ("\n between $a and $b :\n")
    for i=[1:length(spacing)]
      n = spacing[i]
      error = integral(a, b) - g(f, a, b, n)
      println (" Error (n = $n): $error")
    end
  end
end