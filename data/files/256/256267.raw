using PyCall
@pyimport bisect as pybisect

sender = [1 1 1 1; 1 1 1 1; 1 1 1 1; 1 1 1 1]
receiver = [1 1 1 1; 1 1 1 1; 1 1 1 1; 1 1 1 1]
successful_act=[1 2 3 4]
num_trials=100

#function weight: 
function weighted_rand_choice (weights)
    cumulative = Int[]
    running_cumulative = 0

    for w in weights
        running_cumulative =running_cumulative + w
        push!(cumulative, running_cumulative)
    end
    rnd= rand(1:cumulative[length(cumulative)])
     return pybisect.bisect_left(cumulative, rnd, lo=1)
end
    
#function game: hace una partida del juego
function game (maxinum)
    #println ("sender_i: ", sender)
    state= rand(1:4)
   #println ("state: ", state)
    sender_urn=sender[state, :]
    #println ("sender_urn: ", sender_urn)
     message=weighted_rand_choice(sender_urn)
    #println ("message: ", message)
    receiver_urn=receiver[message, :]
    #println("receiver_urn: ", receiver_urn)
    act=weighted_rand_choice(receiver_urn)
    #println("act: ", act)
    

    
    if successful_act[state]==act
       # println ("bien") 
        if sender[state, message]<maxinum
            sender[state,message]= sender[state,message]+1      
        end
    
        if receiver[message, act]<maxinum
            receiver[message, act]= receiver[message,act]+1      
        end
    else 
       # println ("mal")
        if sender[state,message]>1
            sender[state,message]= sender[state,message]-1
        end    
    
        if receiver[message,act]>1
            receiver[message,act]= receiver[message,act]-1
        end
    end
end

#loop:
for i=1:num_trials
    game(500)
    println ("i: ", i)
    println ("sender: ", sender) 
    println ("receiver: ", receiver)
end
    
