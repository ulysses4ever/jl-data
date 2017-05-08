function dump(title, policy::Dict)
  f = open(string(title, ".policy"),"w")
  sortedstates = sort(collect(keys(policy)), by=x -> (x[2], x[1]))
  for state in sortedstates
    write(f, policy[state], "\n")
  end
  close(f)
end
