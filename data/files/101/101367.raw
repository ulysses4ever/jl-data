#Propose stellar parameters in the main algorithm, send them to each of the workers.

#Workers evaluate these, then return a lnprob. Master sums all of the lnprobs, and decides whether to keep the proposed jump. Sends back a KEEP or REVERT.

#Then, also, the program can go off and do it's own IND-ependent sampling, decoupled from the master.

#There will be two remote references on each process. One that is looping constantly, checking to see if the main reference is full (brain), and the other acting as a pipe to store messages.

#pipe is the remote ref that acts like the Python PIPE
@everywhere function brain(pipe)
    id = myid()
    println("Initialized brain $id")
    while true
        msg = take!(pipe)
        println("Process $id received msg $msg")
    end
end

pipe2 = RemoteRef(2)
r2 = remotecall(2, brain, pipe2)

pipe3 = RemoteRef(3)
r3 = remotecall(3, brain, pipe3)

put!(pipe2, "Hello")
put!(pipe3, "Potatoes")

#Instead of @everywhere, we may want to use the require function to build up the necessary code on each process.

#Also, it might be worthwhile to investigate the driver code mentioned in the manual. Seems like more of an MPI startup approach (everything is loaded everywhere, and we can check to see if we are master or not).
