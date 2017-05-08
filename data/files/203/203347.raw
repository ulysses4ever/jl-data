
#6.  Chuckaluck

function chuckaluck(dollars)

history = zeros(dollars)

for i=1:dollars
bet = rand(1:6)
dice_roll = rand(1:6, 3)


winnings = sum( bet .== dice_roll)
    if winnings > 0
            history[i] = winnings +1
    else history[i] = 0
    end


end
return   (sum(history) - dollars)/dollars

end

chuckaluck(100000)
