#19.  Isaac Newton helps Samuel Pepys


function newtonDice(dice, rolls)
  results = falses(rolls)
  for i in 1:rolls
          results[i] = sum(rand(1:6,dice*6) .== 6) >= dice
  end
  return mean(results)
end


newtonDice(1,10000), newtonDice(2,100000), newtonDice(3,10000)

