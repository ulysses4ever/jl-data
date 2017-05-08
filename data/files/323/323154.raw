module Problem09

pythagoreantriple(m,n) = (m^2 - n^2,
                          2m*n,
                          m^2 + n^2)

makemns(m,n) = [2 -1;
							  1  0] * [m, n],
               [2  1;
							  1  0] * [m, n],
               [1  2;
								0  1] * [m, n]

function f(m,n)
	mns = makemns(m,n)
	pts = (pythagoreantriple(mns[1][1],mns[1][2]),
         pythagoreantriple(mns[2][1],mns[2][2]),
         pythagoreantriple(mns[3][1],mns[3][2]))

  a,b,c = 0,0,0
	s=0

	for i in 1:3
		for k in 2:100
			a=k*pts[i][1]
			b=k*pts[i][2]
			c=k*pts[i][3]

			(a>1_000 || b>1_000 || c>1_000) && break

			s=a+b+c

			s≡1_000 && break
		end

		s≡1_000 && break
	end

	(a,b,c)
end

m=2
n=1

r=f(m,n)

problem09 = prod(r)

end
