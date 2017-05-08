export describe,it

currentFeature = Feature("Nothing",list(Test))
suite = Suite(list(Feature))
green = "\e[0;32m"
red = "\e[0;31m"
reset = "\e[0m"

function describe(specs::Function, name::String)
  currentFeature = Feature(name,list(Test))
  addFeature(suite,currentFeature)
  write(reset)
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
  catch e
    pass = false
    write(STDOUT, red)
  end
  println(name)
  addTest(currentFeature, Test(name,pass,false))  
end