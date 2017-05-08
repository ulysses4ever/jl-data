#19.  Isaac Newton helps Samuel Pepys

#A) At least 1 6 with 6 dice

function oneD(rolls)
  results = falses(rolls)
  for i in 1:rolls
     results[i] = sum(rand(1:6,6) .== 6) >= 1
  end
  return mean(results)
end

#B) 2 sixes with 12 dice
function twoD(rolls)
  results = falses(rolls)
  for i in 1:rolls
    results[i] = sum(rand(1:6,12) .== 6) >= 2
  end
  return mean(results)
end

#C) 3 sixes with 18 dice
function threeD(rolls)
  results = falses(rolls)
  for i in 1:rolls
          results[i] = sum(rand(1:6,18) .== 6) >= 3
  end
  return mean(results)
end


oneD(10000), twoD(10000), threeD(10000)

