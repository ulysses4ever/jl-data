

rate = readdlm("rate_constant.dat")
rate = [rate[1:163];ones(25,1);rate[164:end];0.02*ones(25,1)] # Set all new reactions to 1 and all new degradations to 0.02
writedlm("rate_constant.dat",rate)


