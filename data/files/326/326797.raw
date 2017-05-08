# https://en.wikibooks.org/wiki/Introducing_Julia/Metaprogramming
s = "TOP LEVEL"

macro f1(x)
       quote
           s = "in quote"
           (s, $(esc(s)))
       end
end

macro f2(x)
       quote
           (s, $(esc(s)))
       end
end

macro f3(x)
    s = "in macro"
       quote
           (s, $(esc(s)))
       end
end

@f1 10
@f2 10
@f3 10

macro p(n)
    if typeof(n) == Expr 
       println(n.args)
    end
    eval(n)
end

macroexpand(quote @p 3 + 4 - 5 * 6 / 7 % 8 end)

macro dotimes(n, body)
    quote
        for i in 1:$(esc(n))
            $(esc(body))
        end
    end
end

@dotimes 3 println("hi there")

macroexpand( quote  @dotimes 3 begin
           for i in 4:6
               println("i is $i")
           end
       end
end )


name = :holle
def = :($name(x,y) = x)
eval(def)
holle(10, 9)

macro test(name, el)
    :($(esc(name))(x,y) = x)
end

@test BBB 0
BBB(1, 2)
