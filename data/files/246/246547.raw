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
    r   = view( y,2:npts+1)
    dr  = view(dy,2:npts+1)
    u   = reshape_view( view( y,npts+2:length(y)), (npts, npde))
    du  = reshape_view( view(dy,npts+2:length(y)), (npts, npde))
    return t, dt, r, dr, u, du
end

function computederivatives(r,dr,u,du,derivative)
    dudr = zero(u)          # du/dr
    dudt = zero(u)
    for j = 1:size(u,2)
        derivative(view(dudr,:,j),view(u,:,j),r)
        for i = 1:size(u,1)
            dudt[i,j] = du[i,j]-dr[i]*dudr[i,j]
        end
    end
    return dudr, dudt
end

# simple gaussian filter to smoothen the monitor function
function smoothen(M; passes = 4, args...)
    if passes == 0
        return M
    else
        Msmooth = zero(M)
        @simd for i = 2:length(M)-1
            @inbounds Msmooth[i]=(M[i-1]+2M[i]+M[i+1])/4
        end
        Msmooth[1]=(M[1]+M[2])/2
        Msmooth[end]=(M[end-1]+M[end])/2
        return smoothen(Msmooth, passes=passes-1)
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

function physicalres(rhs,r,u,dudt,gval)
    rhsval = rhs(r,u)
    npts, npde = size(dudt)
    resu = -dudt+gval*rhsval
    for j = 1:size(u,2)
        resu[1,j] = u[1,j]          # enforce boundary conditions u(0,t)=0
    end
    return reshape(resu,npts*npde)
end

function newF(eqn::Equation;
              epsilon=1e-5,
              gamma=2,
              derivative=(du,u,r)->fdd!(du,u,r,1,3),
              args...)

    function F(tau,y,dy)
        npde = eqn.npde

        npts = int((length(y)-1)/(npde+1))

        t, dt, r, dr, u, du = extracty(y,dy,npts,npde)
        dudr, dudt = computederivatives(r,dr,u,du,derivative)

        M    = smoothen(eqn.monitor(r,u,dudr); args...)
        gval = eqn.sundman(r,u,dudr)
        eps  = epsilon_eval(epsilon,r,u,dudr)

        res  = zero(y)
        res[1]          = dt-gval                                  # Sundman transform equations
        res[2:npts+1]   = movingmeshres(r,dr,M,gamma,gval,eps) # moving mesh equations
        res[npts+2:end] = physicalres(eqn.rhs,r,u,dudt,gval)       # physical equations

        return res
    end

    return F

end

function meshinit(eqn,
                  r0,
                  uinit;
                  epsilon = 1e-5,
                  gamma = 2,
                  derivative = (du,u,r)->fdd!(du,u,r,1,3),
                  args...)

    info("Mesh initialization: Start")
    T    = eltype(r0)
    npts = length(r0)
    dxi  = convert(T,1/(npts-1))

    dudr = zero(uinit(r0))          # du/dr

    function F(t,r,dr)
        u    = uinit(r)
        for j = 1:size(u,2)
            derivative(view(dudr,:,j),view(u,:,j),r)
        end
        M   = smoothen(eqn.monitor(r,u,dudr); args...)
        ϵ   = epsilon_eval(epsilon,r,u,dudr)
        res  = copy(dr)
        for i = 2:npts-1
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
               npts  = 100,
               rspan = [0,pi],
               T     = Float64,
               args...)

    npde = eqn.npde

    # TODO remove the generation of initial data to another function

    # generate initial data
    t0 = zero(T)
    tau0 = zero(T)
    dr = convert(T,(rspan[2]-rspan[1])/(npts-1))
    r0 = [rspan[1]:dr:rspan[2]]
    r0 = meshinit(eqn, r0, uinit; args...)
    u0 = uinit(r0)

    # generate y0
    ny=npts*(npde+1)+1
    y0=zeros(T,ny)
    y0[1]=t0
    y0[2:npts+1]=r0
    u0view=reshape_view(view(y0,npts+2:ny),(npts,npde))
    for j=1:npde, i=1:npts
        u0view[i,j]=u0[i,j]
    end

    F=newF(eqn; args...)
    sol = dasslIterator(F, y0, tau0; args...)

    function extract_results(t,y,yt)
        t = y[1]
        x = y[2:npts+1]
        u = reshape(y[npts+2:end],npts,npde)
        return t, x, u
    end

    return imap(z->extract_results(z...),sol)

end

end # module
