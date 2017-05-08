using Winston
# type_name:DividedDifferenceTable
# get a divide difference table
type DividedDifferenceTable
  x::Vector{Any} #data point(x-coordinate)
  d::Vector{Any} #coefficients in the table
  DividedDifferenceTable() = new(Array(Any,0),Array(Any,0));
end

#function_name:getNumPoints
#function_describe:get the Number of date points
#input:T::DividedDifferenceTable
#output:the length of table x-coordinate
function getNumPoints(T::DividedDifferenceTable)
  return length(T.x);
end

#function_name:addPoint!
#function_describe:add new points into table
#input:T::DividedDifferenceTable,new data point
#output:table which had added a new data point
function addPoint!(T::DividedDifferenceTable,x,y)
  n=getNumPoints(T);             #number of data points
  T.x=[T.x,x];                   #append the x-coordinate
  T.d=[T.d,y];                   #append the y-coordinate
  for i=1:n
    nom = T.d[end]-T.d[end-n];   #nominator of d-d recursion
    den = T.x[end]-T.x[end-i];   #de-nominator of d-d recursion
    T.d=[T.d,nom/den];           #append the computed quotient
  end
end

#function_name:getNewtonCoefficients
#function_describe:get Newton Coefficients
#input:T::DividedDifferenceTable
#output:Array c
function getNewtonCoefficients(T::DividedDifferenceTable)
  n=length(T.x);         #number of data points
  c=Array(Any,0);        #empty array
  k=0;                   #initiate run index
  for i=1:n
    k+=i;                #pick the coefficients
    c=[c,T.d[k]];        #the first row of the table
  end
  return c;
end

#function_name:getPloynomial
#function_describe:get Ploy nomial
#input:T::DividedDifferenceTable
#output:return function p(x) and return b
function getPloynomial(T::DividedDifferenceTable)
  n=length(T.x);                  #n
  c=getNewtonCoefficients(T);     #Newton coeff
  return function p(x)
    b=c[end];
    for i=1:n-1
      b=c[n-i]+b*(x-T.x[n-i]);    #Horner's recursion
    end
    return b;                     #result of the evaluation
  end
end

#function_name:interpolate
#function_describe:inter polate
#input:T::range and f
#output:return getPloynomial()
function interpolate(range,f)
    table = DividedDifferenceTable();
    for i=1:length(range)
        addPoint!(table,range[i],f(range[i]));
    end
  return getPloynomial(table);
end

#function_name:plot2
#function_describe:plot interpolate and
#input:T::r ,f1 and f2
#output:none
function plot2(r,f1,f2)
  N=200;
  x=linspace(r[1],r[2],N);
  ylim(-4,4);
  window=FramedPlot(
                    title="Compare Interpolation with Primitive",
                    xlabel="x",
                    ylabel="y",
                    xrange=(-8,8),
                    yrange=(-2,2)
                    );

  y1=Array(Any,N);
  y2=Array(Any,N);
  for i=1:N
    y1[i]=f1(x[i]);
    y2[i]=f2(x[i]);
  end
  Cur1=Curve(x,y1,color="red");
  Cur2=Curve(x,y2,color="blue");
  add(window,Cur2);
  add(window,Cur1);
end
