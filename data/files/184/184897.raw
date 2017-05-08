module JulTest

export case, runtests

immutable type TestCase
  description::String
  expr::Expr
end

immutable type Result
  passing::Bool
  case::TestCase
  error #todo figure out how to specify as Exception type
end

tests = TestCase[]

macro case(expr)
  description = expr.args[2]
  newtest = TestCase(description, expr)
  push!(tests, newtest)
end

function runtests()
  shuffled = shuffle(tests)
  results = Result[]
  
  for test in shuffled
    result = run(test)
    push!(results, result)

    if result.passing
      print(".")
    else
      print("-")
    end
  end

  report(results)
end

#where does function doc go?
function run(test::TestCase) # Can I specify this must return type Result?
  try
    eval(test.expr)
    return Result(true, test, None) # should this be none - is there a better way?
  catch error
    return Result(false, test, error)
  end
end

function report(results)
  failing = filter(x -> x.passing == false, results)

  total  = length(results)
  num_failing = length(failing)
  println()
  println("$num_failing failed out of $total")
  println()

  map(report_failure, failing)
end

function report_failure(result::Result)
    println("Failure: ", result.case.description)
    println(result.error)
    println()
end

end
