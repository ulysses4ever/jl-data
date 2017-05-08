#07.  Curing the compulsive gambler


function roulette(bet_amount,number)
        wheel = rand(1:38)
        if wheel !== number
           return 0
        else
            return bet_amount*35 + bet_amount
        end
end

function mrFriend()
        games = zeros(36)
        for i in 1:36
                games[i] = roulette(1,13)
        end
        if sum(games) > 36
                return sum(games) + 20
        else
                return sum(games) -20
        end
end

function simMrFriend(num_sims)
        results = zeros(num_sims)
        for i in 1:num_sims
                results[i] = mrFriend()
        end
        return results
end

#Does he come out ahead?
sum(simMrFriend(10000))

