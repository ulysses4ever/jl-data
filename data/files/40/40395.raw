export describe,it,test,T

currentFeature = Feature("Nothing",list(Test))
suite = Suite(list(Feature))
green = "\e[0;32m"
red = "\e[0;31m"
reset = "\e[0m"

function describe(specs::Function, name::String)
  currentFeature = Feature(name,list(Test))
  addFeature(suite,currentFeature)
  write(reset)
  println()
  println(name)
  println(repeat("-",Base.length(name)))
  specs()
  write(reset)
end

function it(test::Function, name::String)
  pass = true;
  try
    test()
    write(STDOUT, green)
    print("+ ")
    println(name)
  catch e
    pass = false
    write(STDOUT, red)
    print("x ")
    println(name)
    Base.showerror(STDOUT, e, catch_backtrace())
    println()
  end
  addTest(currentFeature, Test(name,pass,false))  
end

function test(actual::Any, check::Function)
  check(actual)
end

T = test