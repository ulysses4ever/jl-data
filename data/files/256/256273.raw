module Barrett

using PyCall
@pyimport bisect as pybisect

global const init_sender = [1 1 1 1; 1 1 1 1; 1 1 1 1; 1 1 1 1]
global const init_receiver = [1 1 1 1; 1 1 1 1; 1 1 1 1; 1 1 1 1]
global const successful_act=[1 2 3 4]
num_trials=1000

#function weight: 
function weighted_rand_choice (weights)
    cumulative = Int[]
    running_cumulative = 0

    for w in weights
        running_cumulative =running_cumulative + w
        push!(cumulative, running_cumulative)
    end
    # println(cumulative)
    rnd = rand(1:cumulative[length(cumulative)])
     return pybisect.bisect_left(cumulative, rnd) + 1
end
    
#function game: hace una partida del juego
function round_of_game (maxinum, sender, receiver)
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
    return sender, receiver
end

#loop:
function game(num_trials)
    sender = copy(init_sender)
    receiver = copy (init_receiver)
        for i=1:num_trials
            sender, receiver = round_of_game(500, sender, receiver)
        end
    println ("sender: ", sender) 
    println ("receiver: ", receiver)
 end

end

