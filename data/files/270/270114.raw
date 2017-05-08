
# loading simple intervals
intervals = collect(eachchromosomeinterval(open("test.bedGraph")))
@test intervals[1] == ChromosomeInterval("chr1", 101, 200)
@test intervals[end] == ChromosomeInterval("chr7", 101, 200)

intervals = collect(eachchromosomeinterval(open("test.bed"), format="bed"))
@test intervals[1] == ChromosomeInterval("chr1", 564450, 570371, 1000)
@test intervals[7] == ChromosomeInterval("chr1", 16839924, 16841396, 1000)

# filtering the intervals uisng the custom iterator
intervals = collect(filter(x->x.chromosome == "chr1", eachchromosomeinterval(open("test.bedGraph"))))
@test intervals[1] == ChromosomeInterval("chr1", 101, 200)
@test intervals[end] == ChromosomeInterval("chr1", 10001, 20000)

# the overlap tester
intervals = [ChromosomeInterval("chr1", 100, 200), ChromosomeInterval("chr2", 100, 200)]
@test Link.testoverlap(ChromosomeInterval("chr3", 100, 200), intervals) == false
@test Link.testoverlap(ChromosomeInterval("chr1", 100, 200), intervals) == true
@test Link.testoverlap(ChromosomeInterval("chr1", 10, 20), intervals) == false
@test Link.testoverlap(ChromosomeInterval("chr1", 10, 100), intervals) == true
@test Link.testoverlap(ChromosomeInterval("chr1", 200, 230), intervals) == true
@test Link.testoverlap(ChromosomeInterval("chr1", 201, 230), intervals) == false
@test Link.testoverlap(ChromosomeInterval("chr1", 230, 231), intervals) == false
@test Link.testoverlap(ChromosomeInterval("chr1", 200, 200), intervals) == true
@test Link.testoverlap(ChromosomeInterval("chr1", 90, 120), intervals) == true
@test Link.testoverlap(ChromosomeInterval("chr1", 150, 210), intervals) == true
@test Link.testoverlap(ChromosomeInterval("chr2", 150, 210), intervals) == true

intervals = [IntegerInterval(100, 200), IntegerInterval(90, 200)]
@test Link.testoverlap(IntegerInterval(100, 200), intervals) == true
@test Link.testoverlap(IntegerInterval(10, 20), intervals) == false
@test Link.testoverlap(IntegerInterval(10, 100), intervals) == true
@test Link.testoverlap(IntegerInterval(200, 230), intervals) == true
@test Link.testoverlap(IntegerInterval(201, 230), intervals) == false
@test Link.testoverlap(IntegerInterval(230, 231), intervals) == false
@test Link.testoverlap(IntegerInterval(200, 200), intervals) == true
@test Link.testoverlap(IntegerInterval(90, 120), intervals) == true
@test Link.testoverlap(IntegerInterval(150, 210), intervals) == true
@test Link.testoverlap(IntegerInterval(10, 90), intervals) == true

# loading intervals with values and NA values
intervals = collect(eachchromosomeinterval(open("testValues.bedGraph")))
@test intervals[1] == ChromosomeInterval("chr1", 101, 200, 0.0)
@test intervals[2] == ChromosomeInterval("chr1", 121, 200, 1.2)
@test intervals[6] == ChromosomeInterval("chr3", 101, 200, NA)
@test intervals[end] == ChromosomeInterval("chr7", 101, 200, NA)

# the bin function
bins = bin(10, 20, filter(x->x.chromosome == "chr1", intervals))
@test isna(bins[1])
@test_approx_eq bins[11] 0.0
@test_approx_eq bins[13] 0.6

bins = bin(300, 2, threshold=0.1, filter(x->x.chromosome == "chr1", intervals))
@test_approx_eq bins[1] 80/180 * 1.2
@test isna(bins[2])

# the zerobin function
bins = zerobin(10, 20, filter(x->x.chromosome == "chr1", intervals), "nonzero")
@test bins[1] == 0
@test bins[11] == 1
@test bins[13] == 1

# jointintervals
intervals = collect(eachchromosomeinterval(open("overlaps.bedGraph")))
jints = jointintervals(intervals)
@test jints[1].first == 1
@test jints[1].last == 5
@test length(jints[1].values) == 1
@test jints[1].values[1] == 0.0
@test length(jints[2].values) == 3
@test jints[2].last == 6

# minmaxdownsample
points1 = minmaxdownsample(intervals, 4)
@test length(points1) == 2
@test points1[1].position == 1
@test points1[1].value == 0.0
@test points1[2].position == 30
@test points1[2].value == 10.0

points2 = minmaxdownsample(intervals, 2)
@test points2[1].position == 1
@test points2[end].position == 30

points3 = minmaxdownsample([intervals[1]], 2)
@test length(points3) == 2
@test points3[1].position == 1
@test points3[2].position == 6

# chunkintervals
cints = chunkintervals(intervals, 4)
@test cints[1][1].first == 1
@test cints[1][1].last == 4
@test cints[2][1].first == 5
@test cints[2][1].last == 6
@test cints[7][1].first == 25
@test cints[7][1].last == 28
@test cints[8][1].first == 29
@test cints[8][1].last == 30

# parseintsimple
@test parseintsimple("123", 1, 3) == 123
@test parseintsimple("1", 1, 1) == 1

# parsefloatsimple
@test parsefloatsimple("123.0", 1, 5) == 123.0
@test parsefloatsimple("1.123", 1, 5) == 1.123
@test parsefloatsimple("0.99a", 1, 4) == 0.99

# parsebedgraphline
@test parsebedgraphline("chr1\t0\t5\t0.0\n").first == 1
@test parsebedgraphline("chr1\t0\t5\t0.0\n").last == 5
@test parsebedgraphline("chr1\t0\t5\t1.0\n").value == 1.0
@test parsebedgraphline("chr1\t0\t5\t0.2").value == 0.2

# parsebedgraphlineii
@test parsebedgraphlineii("chr1\t0\t5\t0.2").value == 0.2
