using IteratedMaps
using Base.Test


# A logistic map with parameter 2 converges to 0.5
lm = LogisticMap(2)

for i in take(lm(0.5),100)
    @test i == 0.5
end

# Test the alternative syntax for map generation
for i in 1:100
    @test collect(take(lm(0.2),100))[i] == collect(take(LogisticMap(2,0.2),100))[i]
end

# Check the Henon map calculates correctly
@test collect(take(HenonMap([1.4,0.3],[0.2,0.3]),2)) == Any[[0.2,0.3],[1.244,0.06]]

# Same with the Duffing map
@test collect(take(DuffingMap([2.75,0.2],[1.0,0.0]),2)) == Any[[1.0,0.0],[0.0,-0.2]]

# And the Tent map

@test collect(take(TentMap(2,0.2),2)) == [0.2,0.4]
