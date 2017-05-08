const SEED = 42
srand(SEED)

# simple binary classification using perceptron

const DIMENSIONS = 100
const NUM_TRAINING = 10000
const NUM_TEST = 300
const LEARNING_RATE = .1
const NUM_PASSES = 200

fake_hyperplane = rand(Float32, (DIMENSIONS,)) .- .5

weights = rand(Float32, (DIMENSIONS,)) - .5
println("WEIGHTS")
println(weights)

fake_data = 10 * rand(Float32, (NUM_TRAINING, DIMENSIONS)) .- 5
fake_test = 10 * rand(Float32, (NUM_TEST, DIMENSIONS)) .- 5

train_labels = ((fake_data * fake_hyperplane) .> 0)
test_labels = ((fake_test * fake_hyperplane) .> 0)

function test_error()
    global weights
    dotty = (fake_test * weights)
    test_predictions = (dotty .> 0)
    num_correct = sum(test_predictions .== test_labels)
    println("TEST ERROR: $((1 - num_correct / NUM_TEST))")
end

function train_pass()
    global weights
    for i = 1:NUM_TRAINING
        score = 0.0
        for j = 1:DIMENSIONS
            score += weights[j]*fake_data[i,j]
        end
        if score > 0 && !train_labels[i]
            for j = 1:DIMENSIONS
                weights[j] = weights[j] - LEARNING_RATE * fake_data[i,j]
            end
        elseif score < 0 && train_labels[i]
            for j = 1:DIMENSIONS
                weights[j] = weights[j] + LEARNING_RATE * fake_data[i,j]
            end
        end
    end
end

test_error()

println("TRAINING")

for i = 1:NUM_PASSES
    train_pass()
    test_error()
end
