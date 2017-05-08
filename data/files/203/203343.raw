#09.  Craps

function craps()

        crap_roll = sum(rand(1:6,2))
            if crap_roll in (7,11)
                return true
            elseif crap_roll in (2,3,12)
                return false
            else
                new_roll = 0
                while new_roll != 7
                        new_roll = sum(rand(1:6,2))
                        if new_roll==crap_roll
                                return true
                        end
                end
                return false
            end

end

crapAttempts = 1000000
crapVector = falses(crapAttempts)
for i in 1:crapAttempts
        crapVector[i] = craps()
end

sum(crapVector)/crapAttempts
