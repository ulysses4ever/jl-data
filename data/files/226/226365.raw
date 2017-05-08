ref_line = ReferenceLine()
@test dim(ref_line) == 1

ref_triangle = ReferenceTriangle()
@test dim(ref_triangle) == 2

ref_square = ReferenceSquare()
@test dim(ref_square) == 2

ref_tetrahedron = ReferenceTetrahedron()
@test dim(ref_tetrahedron) == 3

ref_cube = ReferenceCube()
@test dim(ref_cube) == 3


for p = 2:5
    qr = make_quadrule(ref_line, p)
    for n = [2*p - 1, 2*p - 2]
        analytic = 1 / (n+1) * (1. + (-1.)^n)
        @test_approx_eq integrate(qr, x -> x[1]^n) analytic
    end

    # http://www.m-hikari.com/ijma/ijma-2011/ijma-1-4-2011/venkateshIJMA1-4-2011.pdf
end


