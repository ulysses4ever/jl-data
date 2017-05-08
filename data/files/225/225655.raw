module ODESolver

  export RKF45,RK4,RKF45S

  #=
  Step function for a Runge-Kutta-Fehlberg Method
  of order 4 with a 5th order correcting term
  Input:
    f  : System of first order ODEs
    t  : The time at which the system is at the moment
    y  : Value of the system at the last time interval
    h  : The step size
  Output:
    O₄ : Fourth order accurate method
    O₅ : Fifth order accurate method
  =#
  function RKF45S(f,t,y,h)
    k₁ = h*f(t,y)
    k₂ = h*f(t +        h/4.0  , y +          k₁/4.0)
    k₃ = h*f(t + 3.0  * h/8.0  , y + 3.0    * k₁/32.0   + 9.0    * k₂/32.0)
    k₄ = h*f(t + 12.0 * h/13.0 , y + 1932.0 * k₁/2197.0 - 7200.0 * k₂/2197.0
                                   + 7296.0 * k₃/2197.0)
    k₅ = h*f(t +        h      , y + 439.0  * k₁/216.0  - 8.0    * k₂
                                   + 3680.0 * k₃/513.0  - 845.0  * k₄/4104.0)
    k₆ = h*f(t +        h/2.0  , y - 8.0    * k₁/27.0   + 2.0    * k₂
                                   - 3544.0 * k₃/2565.0 + 1859.0 * k₄/4104.0
                                   - 11.0   * k₅/40.0)
    O₄ = y + 25.0 * k₁/216.0 + 1408.0 * k₃/2565.0 + 2197.0 * k₄/4101.0
           -        k₅/5.0
    O₅ = y + 16.0 * k₁/135.0 + 6656.0 * k₃/12825.0 + 28561.0 * k₄/56430.0
           - 9.0  * k₅/50.0  + 2.0    * k₆/55.0
    return O₄, O₅
  end

  #=
  Runge-Kutta-Fehlberg Method of order 4 with a 5th order correcting term
  Input:
    f      : System of first order ODEs
    IC     : Initial conditions for the system
    a      : Starting value for time
    b      : End value for time
    h      : Initial time step
    ϵ_min  : Error control tolerance minimum
    ϵ_max  : Error control tolerance maximum
  Output:
    ys     : Array of solutions from a to b of the system f
  =#
  function RKF45(f,IC,a,b,h,ϵ_min,ϵ_max)
    h_min = 0.005 #Choosen fairly by the politburo
    h_max = 0.1 #Choosen by fair dice roll
    y♮ = IC
    t = a
    n = iceil((b-a)/h_min)+1024 #upper bound
    ts = zeros(Float64, 1, n)
    ys = zeros(Float64, size(IC,1), n)
    ys_num = 1 #actual
    ys[:,1] = y♮
    ts[1,1] = t
    while t < b
      y♭, z = RKF45S(f,t,y♮,h)
      ϵ = norm(y♭ - z)
      s = 0.8408964152537146 * ((ϵ_max * h)/ϵ)^(0.25)
      h = min(max(s*h, h_min), h_max)
      y♮, Ø = RKF45S(f,t,y♮,h)
      #=if ϵ < ϵ_min  #Double h or set to h_max, whichever is lower
        h = min(2.0*h,h_max)
        y♮ = y♭
      elseif ϵ > ϵ_max
        #s = ((ϵ * h)/(2.0*norm(z-y♭)))^(0.25)
        s = 0.8408964152537146 * ((ϵ_max * h)/ϵ)^(0.25)
        h = min(max(s*h, h_min), h_max)
        y♮, Ø = RKF45S(f,t,y♮,h)
      else
        y♮ = y♭
      end=#
      ys_num += 1
      ys[:,ys_num] = y♮
      if t + h > b
        t = b
        h = b-t
      else
        t += h
      end
      ts[1,ys_num] = t
    end
    ys = ys[:,1:ys_num] #truncate
    ts = ts[1,1:ys_num]
    return [ts ; ys]
  end

  function RK4S(f,t,y,h)
    k₁ = f(t        , y)
    k₂ = f(t + h/2, y + h * k₁/2)
    k₃ = f(t + h/2, y + h * k₂/2)
    k₄ = f(t + h    , y + h * k₃)
    y + h/6 * (k₁ + 2 * k₂ + 2 * k₃ + k₄)
  end

  function RK4(f,IC,a,b,h,ϵ_min=0,ϵ_max=0)
    n = iceil((b-a)/abs(h))+20
    ys = zeros(typeof(h), size(IC,1),n)
    ts = zeros(typeof(h), 1,n)
    ys[:,1] = IC
    i = 1
    tset = h > 0 ? (a:h:(b-h)) : (b:h:(a-h))
    for t = tset
      IC = RK4S(f,t,IC,h)
      i += 1
      @inbounds ys[:,i] = IC
      @inbounds ts[1,i-1] = t
    end
    ts[1,i] = b
    ts = ts[1,1:i]
    ys = ys[:,1:i]
    return [ts ; ys]
  end


end
