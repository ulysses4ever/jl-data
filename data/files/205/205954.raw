module BlinkEditor

using Blink, DevTools

function editor()

w = Window()
id,cb = Blink.callback!()
# Wait for blink.js to load
while haskey(Blink.callbacks,id)
    js_(w,JSString("try {Blink.cb($id);} catch(err) {}"))
    sleep(0.5)
end
tools(w)
for f in ["codemirror.min.js" "codemirror.min.css"]
    load!(w, "https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.3.0/$f")
end
load!(w,Pkg.dir("DevTools","res","julia.js"))
body!(w,"", fade = false)
opt = Dict("mode"=>"julia2","lineNumbers"=>true)
script = """
var cm = CodeMirror(document.body, {"mode": "julia2", "lineNumbers": true});
CodeMirror.keyMap.default["Shift-Enter"] = function(cm) {Blink.msg("eval",{"code": cm.getSelection()});};
"""
js_(w,Blink.JSString(script))

handle(w, "eval") do data
    try
        result = eval(Main, parse(data["code"]))
        @js_ w console.log($(sprint(show, result)))
    catch(e)
        @js_ w console.log($(sprint(showerror, e, catch_backtrace)))
    end
end

end

editor()

end
