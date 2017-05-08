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


for p = 1:5, ref_shape = [ref_line, ref_triangle, ref_square, ref_tetrahedron, ref_cube]
    qr = make_quadrule(ref_shape, p)
    @test_approx_eq integrate(qr, x -> 1) volume(ref_shape)
end
