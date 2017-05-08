#Another simulation function. I should work on naming these better.
function simulate (sims)

p = rand() #Define probability of correct decision for all jurors.
j_one = p
j_two = p
j_three = .5

difference = zeros(sims)# Initialize.  Will be the difference of jury's correct rate and lone juror's rate
    for i in 1:sims

    correct_jury = falses(1000) #Initialize jury array.  1000 is arbitrary number of trials.
        for j in 1:1000
            correct_jury[j] = sum( [rand() < j_one, rand() < j_two, j_three < rand()] ) > 1  #If two out of three jurors vote correctly, a true is returned to indicate the jury was correct
        end
    difference[i] = sum(correct_jury)/1000 - p  #Calculate difference of correct rate for jury and single juror

    end

print("95% Credible Interval for (Jury - Single) = ")
print(quantile(difference, .025) )
print(" to ")
print(quantile(difference,.975) )

end


simulate(1000)
#Since zero is in credible region, they are not different

