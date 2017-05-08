type DividedDifferenceTable
  x::Vector{Any} #data point(x-coordinate)
  d::Vector{Any} #coefficients in the table
  DividedDifferenceTable() = new(Array(Any,0),Array(Any,0));
end

function getNumPoints(T::DividedDifferenceTable)
  return length(T.x);
end

function addPoint!(T::DividedDifferenceTable,x,y)
  n=getNumPoints(T); #number of data points
  T.x=[T.x,x];#append the x-coordinate
  T.d=[T.d,y];#append the y-coordinate
  for i=1:n
    nom = T.d[end]-T.d[end-n];#nominator of d-d recursion
    den = T.x[end]-T.x[end-i];#de-nominator of d-d recursion
    T.d=[T.d,nom/den];#append the computed quotient
  end

end
table=DividedDifferenceTable();
addPoint!(table,0.,1.);
addPoint!(table,1.,2.);
table;

