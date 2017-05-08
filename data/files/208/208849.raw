
export tripletPowder,
        SOPolarizedOcupation,
        SOPolarizedAmplitude,
        thermalPolarization

inv2sqrt2 = float32(1.0/(2*sqrt(2.)))

function zeroFieldVectors(x::Real, y::Real, z::Real)
    invsqrt2 = 1.0/sqrt(2.0)
    zerofieldvectors = [  invsqrt2 0.0 -invsqrt2;
                          invsqrt2 0.0  invsqrt2;
                            0.0    1.0    0.0     ]
                               
    scale = 1.0/sqrt(x*x + y*y + z*z)
    # initial state based on the initial coefficients 
    i = [x,y,z]
    iv = i'*zerofieldvectors
    return iv*scale
end

function thermalPolarization(theta, phi)
  # levels are -1, 0, 1
  return [2.0, 1.0, 0.0]
end

function SOPolarizedAmplitude(Ax::Real, Ay::Real, Az::Real)
    iv = zeroFieldVectors(Ax, Ay, Az)
    function rotatedPolarization(theta::Real, phi::Real)
        rot = qRotation(theta, phi)
        rvec = abs(iv*rot)
        return rvec.*rvec
    end
        
    return rotatedPolarization
end

SOPolarizedOcupation(px::Real, py::Real, pz::Real) = SOPolarizedAmplitude(sqrt(abs(px)), sqrt(abs(py)), sqrt(abs(pz)))
  

function gauss!(spect::Vector{Float64}, field::Vector{Float64}, scale::Real, eng::Real, width::Real = 0.002)
    center = field-eng
    for i = 1:length(field)
      center = field[i]-eng
      spect[i] += scale*exp(-center*center*width)
    end
end

function qRotation(theta::Real, phi::Real)
    ctheta = cos(theta)
    hcthetam1 = 0.5*(ctheta-1.0)
    mephi = exp(-1.0im*phi)
    pephi = conj(mephi)
    xfactor = 1.0im*sin(theta)/sqrt(2.0)    # factor that is present on all terms in Sx elements
    
    rotmatrix = [ (hcthetam1+1.0)*pephi  xfactor*pephi       pephi*hcthetam1;
                         xfactor            ctheta               xfactor    ;
                     mephi*hcthetam1     xfactor*mephi  (hcthetam1+1.0)*mephi ]
                 
    return rotmatrix
end

function rotationMatrix(theta::Real, phi::Real)
    cp = cos(phi)
    sp = sin(phi)
    ct = cos(theta)
    st = sin(theta)
    # Rotation about z
    zrot = [cp -sp  0.0; 
            sp  cp  0.0; 
            0.0 0.0 1.0]
    # Rotation about x
    prot = [  1.0 0.0 0.0; 
              0.0 ct  -st;
              0.0 st   ct  ]
    
    return prot*zrot
end

function D(d::Real, e::Real)
    #if (d > 0.0 and e < 0.0) or (d < 0.0 and e > 0.0): 
    #    raise ValueError('D and E must have same signs: D: {}, E: {}'.format(d,e))
    dz = 2.0/3.0*d
    dx = e - 0.5*dz
    dy = -2.0*e + dx
    return diagm([dx, dy, dz])
end

function scaledFieldHamiltonian(d::Real, e::Real, theta::Real, phi::Real)
    d = -float32(d)  # Reverse the contribution of the d terms to shift the field instead of the energy
    e = -float32(e)
    theta = float32(theta)    
    phi = float32(phi)
    
    c2t = cos(2.*theta)
    s2t = sin(2*theta)
    
    c2p = cos(2.0*phi)
    s2p = sin(2.0*phi)
    
    st = sin(theta)
    
    chalftheta = cos(0.5*theta)
    shalftheta = sin(0.5*theta)
    
    exp2jphi = exp(2.0im*phi)
    
    H11 = 1.0/12.0*(d*(1.0+3.0*c2t) - 6.0*e*c2p*st*st)
    H21 = (-1.0im*(d + e*c2p)*s2t + 2.0*e*st*s2p)*inv2sqrt2
    H31 = e*(exp2jphi*chalftheta*chalftheta*chalftheta*chalftheta + 
            shalftheta*shalftheta*shalftheta*shalftheta*conj(exp2jphi)) - 0.5*d*st*st
    
    H = [   H11+1.0   conj(H21)   conj(H31);
              H21     -2.0*H11   -conj(H21);
              H31       -H21       H11-1.0   ]
    
    return H
end

function twoPowder(d::Float64, 
                            e::Float64, 
                            field::Vector{Float64}, 
                            B0::Float64, 
                            polarization::Function;
                            steps::Int = 75, 
                            width::Float64 = 0.001)
    T01 = zeros(Float64,length(field))
    T_10 = zeros(Float64,length(field))
    
    d = d/B0    # scale our D and E params so the forming the Hamiltonian is easy
    e = e/B0
    
    for theta in linspace(0, pi, steps)
        for phi in linspace(0, pi*2.0, steps)
            h = scaledFieldHamiltonian(d, e, theta, phi)  # Should the sign of RD should depend on if the units are in energy or Gauss?
            en = eigvals(h)            # Right now I'm assuming Gauss
            
            # Transition energies
            e1 = B0*(en[2] - en[1])  # -1 -> 0
            e2 = B0*(en[3] - en[2])  #  0 -> 1
            
            assert (e1 > 0 && e2 > 0)
            
            p = polarization(theta, phi) 
            
            st = sin(theta)
            gauss!(T_10, field, st*(p[1]-p[2]), e1, width)
            gauss!(T01, field, st*(p[2]-p[3]), e2, width)
        end
    end
    return T01, T_10
end

function tripletPowder{T <: Real}(B0::Real, 
                          field::Vector{T}, 
                          d::Real, 
                          e::Real, 
                          polarization::Function; 
                          steps::Int = 75, 
                          width::Real = 0.001)

    spect1, spect2 = twoPowder(float64(d), 
                               float64(e), 
                               convert(Vector{Float64},field), 
                               float64(B0), 
                               polarization, 
                               steps = steps, 
                               width = width)
                               
    result = spect1 + spect2
    # Normalize
    result = result/maximum(abs(result))   
    return result
end
    
function getThetaPhi(x::Real, y::Real, z::Real)
    scale = sqrt(x*x + y*y + z*z)
    theta = acos(z*scale)
    phi = atan2(x*scale, y*scale)
    return [theta, phi]
end
    
function getXYZ(theta::Real, phi::Real)
    x = sin(theta)*cos(phi)
    y = sin(theta)*sin(phi)
    z = cos(theta)
    return abs([x, y, z])
end
