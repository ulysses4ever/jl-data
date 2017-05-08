using JSTypes

# Simple example
typename = :Foo
spec = [(:axistype, String, "x", false)]

typedecl = JSTypes.maketype(typename, spec)
eval(typedecl)

@assert isa(Foo, Type)
@assert length(methods(Foo)) == 1

func = JSTypes.makekwfunc(typename, spec)
eval(func)

@assert length(methods(Foo)) == 2

x = Foo()

@assert isa(x, Foo)
@assert isa(x.axistype, String)
@assert x.axistype == "x"

copydef = JSTypes.makecopy(typename, spec)
eval(copydef)

@assert copy(x) != mybar

# Extended example
typename = :Bar
spec = [
        (:axistype, String, "x", false),
        (:ticks, Int, nothing, true)
       ]

typedecl = JSTypes.maketype(typename, spec)
eval(typedecl)

@assert isa(Bar, Type)
@assert length(methods(Bar)) == 1

func = JSTypes.makekwfunc(typename, spec)
eval(func)

@assert length(methods(Bar)) == 2

jsdef = JSTypes.maketojs(typename, spec)
eval(jsdef)

mybar = Bar("x", 1)
tojs(mybar)

mybar = Bar()
tojs(mybar)

mybar = Bar(axistype = "x")
tojs(mybar)

mybar = Bar(ticks = 3)
tojs(mybar)

copydef = JSTypes.makecopy(typename, spec)
eval(copydef)

@assert copy(mybar) != mybar
