
 pcomp(c,np,p) =
  if(length(p) == 0)
   c
  else
   p[1](pcomp(c,np,p[2:end]))
 end

 casev(v,np,e1) = let
  extract(n::Symbol,v) = :($v.$n)
  extract(n::Int,v) = :($v[$n])
  spat(n, p) = let s = gensym() ; (m) ->
            :(let
               $s = $(extract(n, v))
               $(casev(s,np,:($p->$m)))
            end)
           end

  if(e1.head == :(->))
   (p,c) = e1.args
   if(isa(p,Symbol))
     :(let $p = $v ; $c end)
   elseif(!isa(p,Expr))
     :(if($p == $v) ; $c else $np end)
   elseif(p.head == :(call))
     t = eval(p.args[1])
     es = map(spat, t.names, p.args[2:end])
     :(if(isa($v,$t)) ; $(pcomp(c,np,es)) else $np end)
   elseif(p.head == :(tuple))
     es = map(spat, 1:length(p.args), p.args)
     :(if(isa($v,Tuple)) ; $(pcomp(c,np,es)) else $np end)
   elseif(p.head == :(::))
     (vn,t) = p.args
     :(if(isa($v,$t)) ; let $vn = $v ; $c end else ; $np end)
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
