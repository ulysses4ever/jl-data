function printTime (f, g, spacing, intervals)

  for i=1:1:size(intervals,1)
    a = intervals [i,1]
    b = intervals [i,2]
    println ("\n between $a and $b :\n")
    for i=[1:length(spacing)]
      n = spacing[i]
      println (" Time (n = $n): ")
      @timeit g(f, a, b, n)
    end
  end
end