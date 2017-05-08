function store_posterior!(P,F,G,Rps,B,i)
  P["Lambda"][:,:,i] = F["Lambda"];
  P["U"][:,:,i] = G["U"];
  P["delta"][:,i] = F["delta"];
  P["h2"][:,i] = F["h2"];
  P["Gps"][:,i] = G["ps"];
  P["Rps"][:,i] = Rps;
  P["B"][:,:,i] = B;
end