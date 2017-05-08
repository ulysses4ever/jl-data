const RequireFile = ARGS[1]

required_packages = split(readall(RequireFile), r"\n")

for rp in required_packages
  if length(rp) >= 18 && rp[1:18] == "https://github.com"
    println("Cloning package: ", rp)
    Pkg.clone(rp)
  else    
    println("Adding package: ", rp)
    Pkg.add(rp)
  end
end

println("Running Pkg.update()")
Pkg.update()