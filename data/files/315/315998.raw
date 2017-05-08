function Base.show(io::IO, i::InfoNode)
  println(typeof(i),":")
  f()=@printf(io,"flags = 0x%08x \n",i.flags);f()
  f()=@printf(io,"devicetype = 0x%08x \n",i.devicetype);f()
  f()=@printf(io,"id = 0x%08x \n",i.id);f()
  f()=@printf(io,"locid = 0x%08x \n",i.locid);f()
  println(io,"serialnumber = ",i.serialnumber)
  println(io,"description = ",i.description)
  f()=@printf(io,"handle = 0x%08x \n",i.handle);f()
end

function Base.show(io::IO, a::Array{InfoNode,1})
  println(length(a),"-element ",typeof(a),":")
  for i in a
    println("sn=",rpad(i.serialnumber,17,' ')," description=",rpad(i.description,40,' '))
    @printf(io,"f=0x%08x, dt=0x%08x, id=0x%08x, lid=0x%08x, h=0x%08x \n",
      i.flags, i.devicetype, i.id, i.locid, i.handle)
    println()
  end
end
 