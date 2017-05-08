#2


function compare(sims)

        beat_dad = rand(2:99)   #Define p(beating dad).
        beat_champ = rand(1:beat_dad)  #Define p(beating champ).  Ints are used since one probability is based on the other.

        beat_dad = beat_dad/100     #Convert to probabilities
        beat_champ = beat_champ/100
        dcd = 0     #Initialize counters for keeping track of dad-champ-dad (DCD) and CDC
        cdc = 0

     #Dad-Champ-Dad
     for i in 1:sims
          if rand() < beat_dad      #If I beat dad
                  if rand() < beat_champ    #And then champ
                          dcd += 1          #Then I win
                  end
          elseif rand() < beat_champ    #Or if I lose to dad and beat champ
                  if rand() < beat_dad  #And then  beat dad
                        dcd += 1        #I also win
                  end
          end
     end

     #Champ-Dad-Champ
     for i in 1: sims           #Copy-paste of above with dad and champ inverted
          if rand() < beat_champ
                  if rand() < beat_dad
                          cdc += 1
                  end
          elseif rand() < beat_dad
                  if rand() < beat_champ
                        cdc += 1
                  end
          end
     end
        return dcd > cdc    #In the simulation, did dcd result in more victories?
end


function sim(sims)  #Run the above many times to be sure of our answer.
        results = zeros(sims)
        for i in 1:sims
                results[i] = compare(100)
        end
        print(sum(results)/sims*100)
        print("% of the simulations showed dad-champ-dad combo better than champ-dad-champ")
        println()
end

sim(1000)
