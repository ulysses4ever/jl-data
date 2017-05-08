# for all real numbers from 3 to 1000, if divisable by 3 or 5 sum.
ans1 = 0
for x in 1:999
  ans1 += x % 3 == 0 || x % 5 == 0 ? x : 0
end
assert(ans1 == 233168)

ans2 = [1:999] |> x -> filter(y -> y % 3 == 0 || y % 5 == 0,x) |> sum
assert(ans2 == 233168)
