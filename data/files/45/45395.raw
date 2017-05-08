
 pcomp(c,np,p) =
  if(length(p) == 0)
   c
  else
   (r,d) = p[1]
   n1 = pcomp(c,np,p[2:end])
   if(r == :(=))
    :(let $d ; $n1 ; end)
   elseif(r == :(==))
    :(if $(d) ; $n1 else $np end)
   elseif(r == :(m))
    d(n1)
   end
 end

 casev(v,np,e1) = let
  spat(n::Symbol, p::Symbol) = (:(=), :($p = $v.$n))
  spat(n::Symbol, p::Expr) = (:(m), let s = gensym() ; (m) ->
            :(let
               $s = $v.$n
               $(casev(s,np,:($p->$m)))
            end)
           end)
  spat(n::Symbol, p::Any) = (:(==), :($p == $v.$n))

  if(e1.head == :(->))
   (p,c) = e1.args
   if(p.head == :(call))
     t = eval(p.args[1])
     es = map(spat, t.names, p.args[2:end])
     :(if(isa($v,$t)) ; $(pcomp(c,np,es)) else $np end)
   end
  end
 end

 casen(v,el) = if(length(el) == 0)
   :()
  else
   casev(v,casen(v,el[2:end]),el[1])
  end

 macro case(v,e1...)
  if(isa(v,Symbol))
   casen(v,e1)
  else
   let s = gensym()
    :(let $(s) = $(v) ; $(casen(s,e1)) end)
   end
  end

 end
