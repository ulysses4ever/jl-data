#=
Write a guessing game where the user
has to guess a secret number.
After each guess it should write if the
number was too large or too small.
At the end write number of tries.
=#

☃ = rand(1:10000)
tries = 1
while true
  print("Guess a number: ")
  guess = int(readline(STDIN))
  if guess == ☃
      println("Yes! It is correct.")
      break
  elseif guess < ☃
      println("The number is larger. Try again...")
  else
      println("The number is smaller. Try again...")
  end
  tries += 1
end

println("Number of tries: $tries")
