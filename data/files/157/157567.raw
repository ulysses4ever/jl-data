using PyPlot
function dbimage(z; x=nothing, y=nothing, dbrange=50, cmap="inferno",
  interpolation="None", aspect="auto")

  dbz = 20*log10(abs(z))
   if dbrange ≠ nothing
       vmin = maximum(dbz)-dbrange
       vmax = maximum(dbz)
   else
       vmin = nothing
       vmax = nothing
   end
   if (x ≠ nothing) && (y ≠ nothing)
      imshow(dbz, aspect=aspect, cmap=cmap,
                 extent=(x[0], x[-1], y[0],y[-1]),
                 vmin=vmin, vmax=vmax,
                 interpolation=interpolation)
   else
      imshow(dbz, aspect=aspect, cmap=cmap, interpolation=interpolation,
                 vmin=vmin, vmax=vmax)
   end
 end
