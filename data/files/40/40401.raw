type Feature
  name::String
  tests::LinkedList{Test}
  beforeEach::Function
  afterEach::Function
end

emptyFn = () -> {}
Feature(name::String, tests::LinkedList{Test}) = Feature(name, tests, emptyFn, emptyFn)

function addTest(f::Feature,t::Test)
  cons(t,f.tests)
end