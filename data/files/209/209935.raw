# Encoding of the Disciplined Convex Programming Ruleset
# (c) Philipp Moritz, 2014
#
# see Chapter in Global Optimization: From Theory to Implementation,
# L. Liberti and N. Maculan (eds.), in the book series Nonconvex
# Optimization and its Applications, Springer, 2006, pages
# 155-210. (http://stanford.edu/~boyd/papers/pdf/disc_cvx_prog.pdf)

using Match

# THE CURVATURE RULES

# Add two curvatures
function plus(first, second)
    @match (first, second) begin
        (:affine, second) => second
        (first, :affine) => first
        (:convex, :convex) => :convex
        (:concave, :concave) => :concave
        (_, _) => :unknown
    end
end

# Negate a curvature
function negative(curvature)
    @match curvature begin
        :convex => :concave
        :concave => :convex
        :affine => :affine
        :unknown => :unknown
    end
end

# Multiply curvature and scalar
function multiply(scalar, curvature)
        if scalar < 0.0
            return negative(curvature)
        else
            return curvature
        end
end
