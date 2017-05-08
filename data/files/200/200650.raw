# This is the "example of simple learning" from Lecture 1

import MNIST

const SEED = 42

# Playing around with these...
const INITIAL_SPREAD = 1
const UPDATE_AMOUNT = .6

srand(SEED)

network = INITIAL_SPREAD*(rand(Float32, (MNIST.NROWS, MNIST.NCOLS, 10)) .- (INITIAL_SPREAD/2))

function guess(image)
    scores = zeros(10)
	for i = 1:10
	    scores[i] = sum(image .* network[:,:,i])
	end
    return indmax(scores) 
end

# This trains the network on the new image
function showexample(image, label)
    best_guess = guess(image)
    label_index = label + 1
    for (r,c) in zip(findn(image)...)
        network[r, c, best_guess] -= UPDATE_AMOUNT
        network[r, c, label_index] += UPDATE_AMOUNT
    end
end

function test_error(the_range)
    correct = 0.0
    total = 0.0
    for i = the_range
        if guess(MNIST.testimage(i)) == (MNIST.testlabel(i) + 1)
	    correct += 1
	end
	total += 1
    end
    println("ERROR: $(1 - correct / total)")
end

function train_many(the_range)
    for i = the_range
        showexample(MNIST.trainimage(i), MNIST.trainlabel(i))
    end
end

test_error(1:1000)
train_many(1:1000)

test_error(1:1000)
train_many(1000:5000)

test_error(1:1000)
train_many(5000:10000)

test_error(1:1000)
train_many(10000:20000)

test_error(1:1000)
