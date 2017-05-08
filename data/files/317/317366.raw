function middleware(message)
  println("before $message")
  produce()
  println("after $message")
end



p = Task(() -> middleware("hello"))

println("1")
println(consume(p))
println("2")
println(consume(p))
println("3")
println(consume(p))
println("4")

