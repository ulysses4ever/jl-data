module Problem09

pythagoreantriple(m,n) = (m^2 - n^2,
                          2m*n,
                          m^2 + n^2)

makemns(m,n) = ([m n] * [2 -1;
                         1  0],
                [m n] * [2  1;
                         1  0],
                [m n] * [1  2;
                         0  1])

function g(i,pts)
#  a,b,c = 0,0,0

  p(xs) = (xs[1]>1_000 || xs[2]>1_000 || xs[3]>1_000 || xs[1]+xs[2]+xs[3]≡1_000)
  filter(p, map(k->(k*pts[i][1], k*pts[i][2], k*pts[i][3]), 2:100))
#   for k in 2:100
#     a=k*pts[i][1]
#     b=k*pts[i][2]
#     c=k*pts[i][3]

#     (a>1_000 || b>1_000 || c>1_000) && break

#     a+b+c≡1_000 && break
#   end

  #a,b,c
end

function h(pts)
  a,b,c = 0,0,0
  for i in 1:3
    a,b,c = g(i,pts)
    a+b+c≡1_000 && break
  end
  a,b,c
end

function f(m,n)
	mns = makemns(m,n)
	pts = (pythagoreantriple(mns[1][1],mns[1][2]),
         pythagoreantriple(mns[2][1],mns[2][2]),
         pythagoreantriple(mns[3][1],mns[3][2]))

  a,b,c = 0,0,0
	s=0

  a,b,c = h(pts)
#	for i in 1:3
# 		for k in 2:100
# 			a=k*pts[i][1]
# 			b=k*pts[i][2]
# 			c=k*pts[i][3]

# 			(a>1_000 || b>1_000 || c>1_000) && break

# 			s=a+b+c

# 			s≡1_000 && break
# 		end

#     a,b,c = g(i,pts)

# 		a+b+c≡1_000 && break
# 	end

	(a,b,c)
end

m=2
n=1

r=f(m,n)

problem09 = prod(r)

end
