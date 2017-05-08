# ------------------------ #
# Solving for Coefficients #
# ------------------------ #

L"""
How to solve for coefficients using the least squares method.


Given $n+1$ basis functions $\{\phi_j\}_{j=0}^n$, do the following:

1. Choose m>n+1 interpolation nodes $\{x_i \}_{i=0}^m$
2. Evaluate the function you wish to approximate at each of the nodes.
   Call the output $\{y_i \}_{i=0}^m$
3. Form the $n+1 \times m$ matrix $\Phi$ by evaluating each basis
   function at each node. The (i,j) element should be $\phi_j(x_i)$
4. Minimize the squared errors $(\Phi \omega - y)'(\Phi \omega - y)$,
   which leads to $\omega = (\Phi'\Phi)^{-1}\Phi' y$

NOTE: the special case when there are $n+1$ node is known as collocation

"""
coefs_ls(b::BasisFunctions, nodes::AbstractVector, y::AbstractVector) =
    evaluate(b, nodes) \ y


coefs_ls(spc::FunctionalSpace, y::AbstractVector) =
    spc._basis_at_nodes \ y

function coefs_ls!(ii::Interpoland, y::AbstractVector)
    ii.coefs = ii.spc._basis_at_nodes \ y
end

L"""
How to solve for coefficients using the Galerkin method.

Given $n+1$ basis functions $\{\phi_j\}_{j=0}^n$, do the following:

1. Choose n+1 interpolation nodes $\{x_i \}_{i=0}^n$
2. Evaluate the function you wish to approximate at each of the nodes.
   Call the output $\{y_i \}_{i=0}^n$
3. At each $x$, define the residuals
   $r(x_i) = y_i - \sum_{j=0}^{n} \omega_j \phi(j)(x_i)$
4. Solve the following $n+1$ equations for the $n+1$ unknown $\omega$:

   $$ \int_a^b r(x) \phi_j(x) dx =0 \; \for j = 0, 1, \dots, n,$$

   where $a$ and $b$ are the lower and upper bounds on the interpolation
   interval, respectively.

*NOTE*: using this method for a generic set of basis functions can be
quite inefficient. However, if an orthogonal family of polynomials is
used, this routine can be as efficient as others.

Consider the case for Chebyshev polynomials. We want to solve for the
coefficients that set

$$\int_a^b \phi_j(x) r(x) / sqrt(1 - itrans(x)^2) dx = 0.$$

Note that we have included the weighting function that makes the
Chebyshev polynomials orthongonal here. In this case, if our nodes x
are a transformed version of the zeros of the Chebyshev polynomials, the
integral equaion above can be represented as

$$T R = 0$$,


where the (i,j) element of $T$ is $\phi_i(itrans(x_j))$ and the $j$
element of $R$ is $r(x_j)$.

This system can then be solved using either linear algebra techniques or
a non-linear solver.

"""
function coefs_galerkin(b::BasisFunctions, nodes::AbstractVector,
                            y::AbstractVector)
    error("Galerkin method not implemented for this type")
end
