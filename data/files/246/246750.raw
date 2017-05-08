using ReverseDiffSource
# Defining Hock-Schittkowksi problems 6-9

# Prob 6, dimension = 2, x* = [1,1]
f6(x) = (1 - x[1])^2
c6(x) = 10*(x[2] - x[1]^2)
x6_0 = [-1.2, 1]

# Prob 7, dimension = 2, x* = [0,sqrt(3)]
f7(x) = log(1 + x[1]^2) - x[2]
c7(x) = (1 + x[1]^2)^2 + x[2]^2 - 4
x7_0 = [2, 2]

# Prob 8, dimension = 2, x* = [a,9/a], [-a,-9/a], a = sqrt( ( 25 +- sqrt(301) )/2 )
f8(x) = -1
c81(x) = x[1]^2 + x[2]^2 - 25
c82(x) = x[1]*x[2] - 9
x8_0 = [2,1]
a = sqrt( ( 25 - sqrt(301) )/2 );
x8star1 = [a,9/a]
x8star2 = [-a,-9/a]
a = sqrt( ( 25 + sqrt(301) )/2 );
x8star3 = [a,9/a]
x8star4 = [-a,-9/a]

# Prob 9, dimension = 2, x* = [12k - 3, 16k - 4] for integer k
f9(x) = sin(pi*x[1]/12)*cos(pi*x[2]/16)
c9(x) = 4*x[1] - 3*x[2]
x9_0 = [0,0]



# L(x,y,rho) = f(x) - y'*c(x) + (rho/2)*c(x)'*c(x)
L6(x,y,ρ) = (1 - x[1])^2 - y*10*(x[2] - x[1]^2) + (ρ/2)*(10*(x[2] - x[1]^2))^2
L7(x,y,ρ) = log(1 + x[1]^2) - x[2] - y*((1 + x[1]^2)^2 + x[2]^2 - 4) + (ρ/2)*((1 + x[1]^2)^2 + x[2]^2 - 4)^2
L8(x,y,ρ) = -1 - y[1]*(x[1]^2 + x[2]^2 - 25) - y[2]*(x[1]*x[2] - 9) + (ρ/2)*((x[1]^2 + x[2]^2 - 25)^2 + (x[1]*x[2] - 9)^2)
L9(x,y,ρ) = sin(pi*x[1]/12)*cos(π*x[2]/16) - y[1]*(4*x[1] - 3*x[2]) + (ρ/2)*(4*x[1] - 3*x[2])^2

# the gross versions: x comes first, then y, then \rho
L6(x) = (1 - x[1])^2 - x[3]*10*(x[2] - x[1]^2) + (x[4]/2)*(10*(x[2] - x[1]^2))^2
L7(x) = log(1 + x[1]^2) - x[2] - x[3]*((1 + x[1]^2)^2 + x[2]^2 - 4) + (x[4]/2)*((1 + x[1]^2)^2 + x[2]^2 - 4)^2
L8(x) = -1 - x[3]*(x[1]^2 + x[2]^2 - 25) - x[4]*(x[1]*x[2] - 9) + (x[5]/2)*((x[1]^2 + x[2]^2 - 25)^2 + (x[1]*x[2] - 9)^2)
L9(x) = sin(pi*x[1]/12)*cos(π*x[2]/16) - x[3]*(4*x[1] - 3*x[2]) + (x[4]/2)*(4*x[1] - 3*x[2])^2


diff_f6 = rdiff( f6, (ones(2),), order = 2)
diff_f7 = rdiff( f7, (ones(2),), order = 2)
diff_f8(x) = (-1, 0, [0 0; 0 0])
diff_f9 = rdiff( f9, (ones(2),), order = 2)

diff_c6 = rdiff( c6, (ones(2),), order = 1)
diff_c7 = rdiff( c7, (ones(2),), order = 1)
diff_c81 = rdiff( c81, (ones(2),), order = 1)
diff_c82 = rdiff( c82, (ones(2),), order = 1)
diff_c82([1,1])
function diff_c8(x)
  t1 = diff_c81(x)
  t2 = diff_c82(x)
  return ([t1[1], t2[1]], [[t1[2]] [t2[2]]])
end
diff_c8([1,1])[2]
diff_c9 = rdiff( c9, (ones(2),), order = 2)

diff_L6 = rdiff( L6, (ones(4),), order = 2)
diff_L7 = rdiff( L7, (ones(4),), order = 2)
diff_L8 = rdiff( L8, (ones(5),), order = 2)
diff_L9 = rdiff( L9, (ones(4),), order = 2)

# Get around the fact that rdiff is a bit kludgy
function diff_L6abb(x,y,ρ)
  tmp=diff_L6([x,y,ρ])
  return (tmp[1], tmp[2][1:2],tmp[3][1:2,1:2])
end
function diff_L7abb(x,y,ρ)
  tmp=diff_L7([x,y,ρ])
  return (tmp[1], tmp[2][1:2],tmp[3][1:2,1:2])
end
diff_L8([1,1,1,1,1])
function diff_L8abb(x,y,ρ)
  tmp=diff_L8([x,y,ρ])
  return (tmp[1], tmp[2][1:2],tmp[3][1:2,1:2])
end
diff_L8abb([1,1],[1,1],1)
function diff_L9abb(x,y,ρ)
  tmp=diff_L9([x,y,ρ])
  return (tmp[1], tmp[2][1:2],tmp[3][1:2,1:2])
end