#module LoggingMacro

import Logging

export @debug, @info, @warn, @err, @critical

for (fn,lvl,clr) in ((:debug,    Logging.DEBUG,    :cyan),
                     (:info,     Logging.INFO,     :blue),
                     (:warn,     Logging.WARNING,  :magenta),
                     (:err,      Logging.ERROR,    :red),
                     (:critical, Logging.CRITICAL, :red))
    if lvl >= Logging._root.level
        eval(quote 
            macro $fn(msg::String)
                Base.print_with_color($(Expr(:quote, clr)), 
                                      Logging._root.output, 
                                      string($lvl), ":", Logging._root.name, ":", msg, "\n")
            end
             end)
    else
        eval(quote
            macro $fn(msg::String) end
             end)
    end
end
#end
