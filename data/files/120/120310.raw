using JSTypes
import JSTypes.tojs

typename = :Foo
spec = [
        (:_type, String, "x", false),
        (:ticks, Int, nothing, true)
       ]

eval(maketype(typename, spec))
eval(makekwfunc(typename, spec))
eval(maketojs(typename, spec))
eval(makecopy(typename, spec))

tojs(Foo(_type = "y", ticks = 30)) == {"ticks" => 30, "type" => "y"}
