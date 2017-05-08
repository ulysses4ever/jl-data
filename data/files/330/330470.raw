#Collection of some useful functions

function intToHexavigesimal(i::Integer)
  s = ""
  while i > 26
    rem = i % 26
    if rem == 0
      i -= 26
      s = string('Z') * s
    else
      s = string(Char(64+rem)) * s
    end
    i = floor(i/26)
  end
  s = string(Char(64+i)) * s
end

function unfold(sim,variable)
  a = Array{Float64,1}(size(sim.value)[1] * size(sim.value)[3])

  for k in 1:size(sim.value)[3]
    a[1+(k-1)*size(sim.value)[1]:k*size(sim.value)[1]] = sim[:,variable,k].value
  end

  return a
end

function unfold(sim)
  a = Array{Float64,1}(size(sim.value)[1] * size(sim.value)[3])

  for k in 1:size(sim.value)[3]
    a[1+(k-1)*size(sim.value)[1]:k*size(sim.value)[1]] = sim[:,sim.names[1],k].value
  end

  return a
end

function HPDinterval(a, p=0.025)
  uq = quantile(a,1-p)
  lq = quantile(a,p)

  keep = [a[i] < uq && a[i] > lq for i in 1:size(a)[1]]

  return_a = Array{typeof(a[1]),1}()

  for i in 1:size(a)[1]
    if keep[i]
      push!(return_a,a[i])
    end
  end
  return_a
end

function calculateFDR(samples,fc=0.05)
  up = 0
  down = 0
  for i in 1:size(samples)[1]
      samples[i]<log(1-fc) ? down = down +1 : down = down
      samples[i]>log(1+fc) ? up = up + 1 : up = up
  end

  upfdr = 1 - up/(size(samples)[1])
  downfdr = 1 - down/(size(samples)[1])

  upfdr,downfdr
end

function iswanted(s)
  !(contains(s, "fake") || contains(s,"__") || contains(s,"raw") || contains(s,"lambda"))
end

function isplotfile(s)
  contains(s, "plot")
end

function combinePDFs(dir,filename)
  pdffiles = filter(s->contains(s,filename*"-")&&contains(s,".pdf"),readdir(dir))
  outputfile = filename*".pdf"
  cd(
    ()->begin
      run(`pdfunite $pdffiles $outputfile`)
      for p in pdffiles
        rm(p)
      end
    end,
    dir
   )

end
