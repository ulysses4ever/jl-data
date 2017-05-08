module MovingMesh

using FiniteDifferenceDerivatives
using ArrayViews
using DASSL
using Iterators

export Equation, solve

abstract Equation

function epsilon_eval(eps::Function,r,u,ur)
    return eps(r,u,ur)
end

function epsilon_eval(eps::Real,r,u,ur)
    return eps
end

function extracty(y,dy,npts,npde)
    t   =  y[1]
    dt  = dy[1]
    # r   = view( y,2:npts+1)
    # dr  = view(dy,2:npts+1)
    # u   = reshape_view( view( y,npts+2:length(y)), (npts, npde))
    # du  = reshape_view( view(dy,npts+2:length(y)), (npts, npde))
    r   =  y[2:npts+1]
    dr  = dy[2:npts+1]
    u   = reshape(  y[npts+2:length(y)], npts, npde)
    du  = reshape( dy[npts+2:length(y)], npts, npde)
    return t, dt, r, dr, u, du
end

function computederivatives(r,dr,u,du,derivative)
    dudr = zero(u)          # du/dr
    dudt = zero(u)
    tmp = Array(eltype(u),size(u,1))
    for j = 1:size(u,2)
        derivative(tmp,view(u,:,j),r)
        dudr[:,j] = tmp
        for i = 1:size(u,1)
            dudt[i,j] = du[i,j]-dr[i]*dudr[i,j]
        end
    end
    return dudr, dudt
end

# simple in-place gaussian filter to smoothen the monitor function
function smoothen!(M; passes = 4, args...)
    if passes == 0
        return
    else
        # forward pass
        for i = 1:length(M)-1
            M[i]=(M[i+1]+M[i])/2
        end
        M[end] = M[end-1]
        # backward pass
        for i = length(M):-1:2
            M[i]=(M[i]+M[i-1])/2
        end
        smoothen!(M, passes=passes-1)
    end
end

function movingmeshres(r,dr,M,gamma,gval,epsilon)
    npts = length(dr)
    dxi  = 1/(npts-1)
    resr = zero(dr)          # residua of moving mesh
    for i = 2:npts-1
        resr[i]   = (dr[i]-gamma*(dr[i-1]+dr[i+1]-2*dr[i])/dxi^2)-gval/epsilon*( (M[i+1]+M[i])*(r[i+1]-r[i])/dxi-(M[i]+M[i-1])*(r[i]-r[i-1])/dxi )/dxi
    end
    resr[ 1 ] =  r[ 1 ]   # mesh boundary conditions
    resr[end] = dr[end]
    return resr
end

function physicalres!(resu,rhsval,r,u,dudt,gval)
    npts, npde = size(u)
    for j = 1:npde
        resu[1,j] = u[1,j]          # enforce boundary conditions u(0,t)=0
        for i = 1:npts
            resu[i,j] = gval*rhsval[i,j]-dudt[i,j]
        end
    end
end


function meshinit(eqn,
                  uinit,
                  nx;
                  T = Float64,
                  epsilon = 1e-5,
                  gamma = 2,
                  derivative = (du,u,r)->fdd!(du,u,r,1,3),
                  args...)

    info("Mesh initialization: Start")
    r0   = linspace(eqn.rspan...,nx)
    dxi  = 1/(convert(T,nx)-1)

    dudr = zero(uinit(r0))      # du/dr

    function F(t,r,dr)
        u    = uinit(r)::Matrix{T}
        for j = 1:size(u,2)
            derivative(view(dudr,:,j),view(u,:,j),r)
        end
        M = eqn.monitor(r,u,dudr)::Array{T}
        smoothen!(M; args...)
        ϵ   = epsilon_eval(epsilon,r,u,dudr)
        res  = zero(dr)
        res[  1] = dr[  1]
        res[end] = dr[end]
        for i = 2:nx-1
            res[i]=ϵ*(dr[i]*dxi^2-gamma*(dr[i-1]+dr[i+1]-2*dr[i]))-( (M[i+1]+M[i])*(r[i+1]-r[i])-(M[i]+M[i-1])*(r[i]-r[i-1]) )
        end
        return res
    end

    u0    = uinit(r0)
    for j = 1:size(u0,2)
        derivative(view(dudr,:,j),view(u0,:,j),r0)
    end

    ϵ   = epsilon_eval(epsilon,r0,u0,dudr)
    tol = min(1,ϵ*1e7)
    err = Inf
    for (t,r,dr) in dasslIterator(F, r0, zero(T); reltol = dxi*tol, abstol = 1e-2*dxi*tol)
        err = norm(dr)*dxi
        if err < eps(T)^(4/5)
            info("Mesh initialization: Done! Total error = $err")
            return r
        end
    end

    warn("Mesh initialization: Failed! Total error = $err")
    return r0
end

function solve(eqn   :: Equation,
               uinit :: Function;
               npts :: Int = 100,
               T     = Float64,
               epsilon = 1e-5,
               gamma = 2,
               derivative = (du,u,r)->fdd!(du,u,r,1,3),
               args...)

    # generate initial data
    r0 = meshinit(eqn, uinit, npts; epsilon=epsilon, derivative=derivative, gamma=gamma, T=T, args...)
    u0 = uinit(r0)
    resu = zero(u0)
    y0 = vcat(eqn.t0,r0,vec(u0))

    # dae to solve
    function dae(tau,y,dy)
        t, dt, r, dr, u, du = extracty(y,dy,npts,eqn.npde)::(T,T,Vector{T},Vector{T},Matrix{T},Matrix{T})
        dudr, dudt = computederivatives(r,dr,u,du,derivative)

        M    = eqn.monitor(r,u,dudr)::Array{T}
        smoothen!(M; args...)
        gval = eqn.sundman(r,u,dudr)::T
        eps  = epsilon_eval(epsilon,r,u,dudr)::T
        rhs  = eqn.rhs(r,u)

        res  = Array(T,npts*eqn.npde+npts+1)
        res[1]          = dt-gval # Sundman transform equations
        res[2:npts+1]   = movingmeshres(r,dr,M,gamma,gval,eps) # moving mesh equations
        physicalres!(resu,rhs,r,u,dudt,gval) # physical equations
        res[npts+2:end] = vec(resu)

        return res
    end

    function extract_results(t,y,yt)
        t = y[1];
        x = y[2:npts+1]
        u = reshape(y[npts+2:end],npts,eqn.npde)
        dt = yt[1];
        dx = yt[2:npts+1]/dt
        du = reshape(yt[npts+2:end],npts,eqn.npde)/dt
        return t, x, u, dt, dx, du
    end

    sol = dasslIterator(dae, y0, zero(T); args...)

    return imap(z->extract_results(z...),sol)

end

end # module
