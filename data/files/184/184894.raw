module JulTest

export jt, runtests

immutable type MyTest
  description::String
  ex::Expr
end

tests = MyTest[]

macro jt(ex)
  description = ex.args[2]
  newtest = MyTest(description, ex)
  push!(tests, newtest)
end

function runtests()
  passing = 0
  shuffled = shuffle(tests)
  for test in shuffled
    result = run(test)
    if result
      passing += 1
    end
  end
  println("$passing out of $(length(tests)) passed")
end

#where does function doc go?
function run(test::MyTest) # Can I specify this must return boolean?
  try
    eval(test.ex)
    println("Success: ", test.description)
    println()
    return true # returns true if test succeeeds
  catch error
    println("Failure: ", test.description)
    println(error)
    println()
    return false #returns false if failure
  end
end

end
