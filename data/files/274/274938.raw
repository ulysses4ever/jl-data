unary_diff = Dict(
    (cos) => x -> -sin(x),
    (sin) => x -> cos(x),
    (tan) => x -> tan(x)^2 + 1,
    (acos) => x -> -1/sqrt(-x^2 + 1),
    (asin) => x -> 1/sqrt(-x^2 + 1),
    (atan) => x -> 1/(x^2 + 1),
    (+) => x -> 1,
    (-) => x -> -1)

binary1_diff = Dict(
    (+) => ( x, y ) -> 1,
    (-) => ( x, y ) -> 1,
    (*) => ( x, y ) -> y,
    (/) => ( x, y ) -> 1/y,
    (^) => ( x, y ) -> x^y*y/x)

binary2_diff = Dict(
    (+) => ( x, y ) -> 1,
    (-) => ( x, y ) -> -1,
    (*) => ( x, y ) -> x,
    (/) => ( x, y ) -> -x/y^2,
    (^) => ( x, y ) -> x^y*log(x))

