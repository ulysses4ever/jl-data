module DimensionalAnalysis

export PhysicalQuantity
export Mass, Length, Time, Temperature, Intensity, Current, Amount
export Dimensionless
export Area, Volume, Density, Speed, Acceleration, Force, Energy, Power, Stress, Pressure
export Diffusivity, DynamicViscosity, KinematicViscosity, SurfaceEnergy

export mass, length_, time_, temperature, intensity, current, amount
export dimensionless
export area, volume, density, speed, acceleration, force, energy, power, stress, pressure
export diffusivity, kinematicViscosity, dynamicViscosity, surfaceEnergy

export ReynoldsNumber, WeberNumber, ModifiedWeberNumber


export MeasuredQuantity
export Meter

type PhysicalQuantity{X<:Real,Mass,Length,Time,Temperature,Intensity,Current,Amount}
    value::X
end





value{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}(x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount} ) = x.value

+{X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}(x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount},
                                                             y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}) =
    PhysicalQuantity{typeof(x.value+y.value),Mass,Length,Time,Temperature,Intensity,Current,Amount}(x.value+y.value)

-{X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}(x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount},
                                                             y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current}) =
    PhysicalQuantity{typeof(x.value-y.value),Mass,Length,Time,Temperature,Intensity,Current,Amount}(x.value-y.value)

*{X,MassX,LengthX,TimeX,TemperatureX,IntensityX,CurrentX,AmountX,Y,MassY,LengthY,TimeY,TemperatureY,IntensityY,CurrentY,AmountY}(x::PhysicalQuantity{X,MassX,LengthX,TimeX,TemperatureX,IntensityX,CurrentX,AmountX},
                                                                                                                                 y::PhysicalQuantity{Y,MassY,LengthY,TimeY,TemperatureY,IntensityY,CurrentY,AmountY}) =
    PhysicalQuantity{typeof(x.value*y.value),MassX+MassY,LengthX+LengthY,TimeX+TimeY,TemperatureX+TemperatureY,IntensityX+IntensityY,CurrentX+CurrentY,AmountX+AmountY}(x.value*y.value)

/{X,MassX,LengthX,TimeX,TemperatureX,IntensityX,CurrentX,AmountX,Y,MassY,LengthY,TimeY,TemperatureY,IntensityY,CurrentY,AmountY}(x::PhysicalQuantity{X,MassX,LengthX,TimeX,TemperatureX,IntensityX,CurrentX,AmountX},
                                                                                                                                 y::PhysicalQuantity{Y,MassY,LengthY,TimeY,TemperatureY,IntensityY,CurrentY,AmountY}) =
    PhysicalQuantity{typeof(x.value/y.value),MassX-MassY,LengthX-LengthY,TimeX-TimeY,TemperatureX-TemperatureY,IntensityX-IntensityY,CurrentX-CurrentY,AmountX-AmountY}(x.value/y.value)


typealias Dimensionless{X} PhysicalQuantity{X, 0, 0, 0, 0, 0, 0, 0}

dimensionless{X}( x::X ) = Dimensionless{X}( x )
dimensionless() = dimensionless( 1 )

<{X<:Number,Y}(x::X, y::Dimensionless{Y})  = x < value( y )
<{X,Y<:Number}(x::Dimensionless{X}, y::Y)   = value( x ) < y

<={X<:Number,Y}(x::X, y::Dimensionless{Y}) = x <= value( y )
<={X,Y<:Number}(x::Dimensionless{X}, y::Y)  = value( x ) <= y

=={X<:Number,Y}(x::X, y::Dimensionless{Y}) = x == value( y )
=={X,Y<:Number}(x::Dimensionless{X}, y::Y)  = value( x ) == y

!={X<:Number,Y}(x::X, y::Dimensionless{Y}) = x != value( y )
!={X,Y<:Number}(x::Dimensionless{X}, y::Y) = value( x ) != y

>={X<:Number,Y}(x::X, y::Dimensionless{Y}) = x >= value( y )
>={X,Y<:Number}(x::Dimensionless{X}, y::Y)  = value( x ) >= y

>{X<:Number,Y}(x::X, y::Dimensionless{Y})  = x > value( y )
>{X,Y<:Number}(x::Dimensionless{X}, y::Y)   = value( x ) > y




*{X,Mass,Length,Time,Temperature,Intensity,Current,Amount,Y<:Number}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::Y ) = x*dimensionless( y )
*{X<:Number,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::X, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount} ) = dimensionless( x )*y

/{X,Mass,Length,Time,Temperature,Intensity,Current,Amount,Y}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::Y ) = x/dimensionless( y )
/{X, Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::X, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount} ) = dimensionless( x )/y


>{X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount} ) = value( x ) >  value( y )
>={X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}) = value( x ) >= value( y )
=={X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}) = value( x ) == value( y )
!={X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}) = value( x ) != value( y )
<={X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}) = value( x ) <= value( y )
<{X,Y,Mass,Length,Time,Temperature,Intensity,Current,Amount}( x::PhysicalQuantity{X,Mass,Length,Time,Temperature,Intensity,Current,Amount}, y::PhysicalQuantity{Y,Mass,Length,Time,Temperature,Intensity,Current,Amount} ) = value( x ) <  value( y )

typealias Mass{X} PhysicalQuantity{X, 1, 0, 0, 0, 0, 0, 0}
mass{X}( x::X ) = Mass{X}( x )
mass() = mass( 1 )

typealias Length{X} PhysicalQuantity{X, 0, 1, 0, 0, 0, 0, 0}
length_{X}( x::X ) = Length{X}( x )
length_() = length_( 1 )

typealias Time{X} PhysicalQuantity{X, 0, 0, 1, 0, 0, 0, 0}
time_{X}( x::X ) = Time{X}( x )
time_() = time_( 1 )

typealias Temperature{X} PhysicalQuantity{X, 0, 0, 0, 1, 0, 0, 0}
temperature{X}( x::X ) = Temperature{X}( x )
temperature() = temperature( 1 )


typealias Intensity{X} PhysicalQuantity{X, 0, 0, 0, 0, 1, 0, 0}
intensity{X}( x::X ) = Intensity{X}( x  )
intensity() = intensity( 1 )

typealias Current{X} PhysicalQuantity{X, 0, 0, 0, 0, 0, 1, 0}
current{X}( x::X ) = Current{X}( x )
current() = current( 1 )

typealias Amount{X} PhysicalQuantity{X, 0, 0, 0, 0, 0, 0, 1}
amount{X}( x::X ) = Amount{X}( x )
amount() = amount( 1 )

typealias Area{X} PhysicalQuantity{X, 0, 2, 0, 0, 0, 0, 0}
area{X}( x::X ) = Area{X}( x )
area() = area( 1 )

typealias Volume{X} PhysicalQuantity{X, 0, 3, 0, 0, 0, 0, 0}
volume{X}( x::X ) = Volume{X}( x )
volume() = volume( 1 )

typealias Density{X} PhysicalQuantity{X, 1,-3, 0, 0, 0, 0, 0}
density{X}( x::X ) = Density{X}( x )
density() = density( 1 )

typealias Speed{X} PhysicalQuantity{X, 0, 1,-1, 0, 0, 0, 0}
speed{X}( x::X ) = Speed{X}( x )
speed() = speed( 1 )

typealias Acceleration{X} PhysicalQuantity{X, 0, 1,-2, 0, 0, 0, 0}
acceleration{X}( x::X ) = Acceleration{X}( x )
acceleration() = acceleration( 1 )

typealias Force{X} PhysicalQuantity{X, 1, 1,-2, 0, 0, 0, 0}
force{X}( x::X ) = Force{X}( x )
force() = force( 1 )


typealias Momentum{X} PhysicalQuantity{X, 1, 1,-1, 0, 0, 0, 0}
momentum{X}( x::X ) = Momentum{X}( x )
momentum() = momentum( 1 )


typealias Energy{X} PhysicalQuantity{X, 1, 2,-2, 0, 0, 0, 0}
energy{X}( x::X ) = Energy{X}( x )
energy() = energy( 1 )

typealias Power{X} PhysicalQuantity{X, 1, 2,-3, 0, 0, 0, 0}
power{X}( x::X ) = Power{X}( x )
power() = power( 1 )

typealias Stress{X} PhysicalQuantity{X, 1,-1,-2, 0, 0, 0, 0}
stress{X}( x::X ) = Stress{X}( x )
stress() = stress( 1 )

typealias Pressure{X} PhysicalQuantity{X, 1,-1,-2, 0, 0, 0, 0}
pressure{X}( x::X ) = Pressure{X}( x )
pressure() = pressure( 1 )

typealias Diffusivity{X} PhysicalQuantity{X, 0, 2,-1, 0, 0, 0, 0}
diffusivity{X}( x::X ) = Diffusivity{X}( x )
diffusivity() = diffusivity( 1 )

typealias KinematicViscosity{X} PhysicalQuantity{X, 0, 2, -1, 0, 0, 0, 0}
kinematicViscosity{X}( x::X ) = KinematicViscosity{X}( x )
kinematicViscosity() = kinematicViscosity( 1 )

typealias DynamicViscosity{X} PhysicalQuantity{X, 1,-1,-1, 0, 0, 0, 0}
dynamicViscosity{X}( x::X ) = DynamicViscosity{X}( x )
dynamicViscosity() = dynamicViscosity( 1 )

typealias SurfaceEnergy{X} PhysicalQuantity{X, 1, 0,-2, 0, 0, 0, 0}
surfaceEnergy{X}( x::X ) = SurfaceEnergy{X}( x )
surfaceEnergy() = surfaceEnergy( 1 )





ReynoldsNumber{X1,X2,X3,X4}( ρ::Density{X1}, v::Speed{X2}, d::Length{X3}, μ::DynamicViscosity{X4} ) = ρ*v*d/μ
ReynoldsNumber{X1,X2,X3}( v::Speed{X1}, d::Length{X2}, ν::KinematicViscosity{X3 } ) = v*d/ν

WeberNumber{X1,X2,X3,X4}( ρ::Density{X1}, v::Speed{X2}, d::Length{X3}, σ::SurfaceEnergy{X4} ) = ρ*v^2*d/σ

ModifiedWeberNumber{X1,X2,X3,X4}( ρ::Density{X1}, v::Speed{X2}, d::Length{X3}, σ::SurfaceEnergy{X4} ) = WeberNumber( ρ, v, d, σ )/12






type MeasuredQuantity{T,Mass,Length,Time,Temperature,Intensity,Current,Amount,Offset,Scale}
    value::PhysicalQuantity{T,Mass,Length,Time,Temperature,Intensity,Current,Amount}
end

value{T,Mass,Length,Time,Temperature,Intensity,Current,Amount,Offset,Scale}( x::MeasuredQuantity{T,Mass,Length,Time,Temperature,Intensity,Current,Amount,Offset,Scale}) =
    value( x.value )


typealias Meter{T} MeasuredQuantity{T,0,1,0,0,0,0,0,0,1}

show{T}(   x::Meter{T}) = println( value( x ), "m" )
offset{T}( x::Meter{T}) = 0
scale{T}(  x::Meter{T}) = 1


# M,L,T,Θ,I,C,N


# SchmidtNumber{T1,T2,T3}( ρ::MechanicalDensity{T1}, μ::MechanicalDynamicViscosity{T2}, d::MechanicalMolecularDiffusivity{T}) = μ*d/ρ
# SchmidtNumber{T1,T2}( ν::MechanicalKinematicViscosity{T1}, d::MechanicalMolecularDiffusivity{T2} ) = ν/d

# # Weber number	We	\mathrm{We} = \frac{\rho v^2 l}{\sigma}	multiphase flow (strongly curved surfaces; ratio of inertia to surface tension)
# WeberNumber{T1,T2,T3,T4}( ρ::Mechanical





# Abbe number	V	V = \frac{ n_d - 1 }{ n_F - n_C }	optics (dispersion in optical materials)
# Activity coefficient	\gamma	 \gamma= \frac {{a}}{{x}} 	chemistry (Proportion of "active" molecules or atoms)
# Albedo	\alpha	\alpha= (1-D) \bar \alpha(\theta_i) + D \bar{ \bar \alpha}	climatology, astronomy (reflectivity of surfaces or bodies)
# Archimedes number	Ar	 \mathrm{Ar} = \frac{g L^3 \rho_\ell (\rho - \rho_\ell)}{\mu^2}	fluid mechanics (motion of fluids due to density differences)
# Arrhenius number	\alpha	\alpha = \frac{E_a}{RT} 	chemistry (ratio of activation energy to thermal energy)[5]
# Atomic weight	M		chemistry (mass of atom over one atomic mass unit, u, where carbon-12 is exactly 12 u)
# Atwood number	A	\mathrm{A} = \frac{\rho_1 - \rho_2} {\rho_1 + \rho_2} 	fluid mechanics (onset of instabilities in fluid mixtures due to density differences)
# Bagnold number	Ba	\mathrm{Ba} = \frac{\rho d^2 \lambda^{1/2} \gamma}{\mu}	fluid mechanics, geology (ratio of grain collision stresses to viscous fluid stresses in flow of a granular material such as grain and sand)[6]
# Bejan number


# (fluid mechanics)	Be	\mathrm{Be} = \frac{\Delta P L^2} {\mu \alpha}	fluid mechanics (dimensionless pressure drop along a channel)[7]
# Bejan number
# (thermodynamics)	Be	\mathrm{Be} = \frac{\dot S'_{\mathrm{gen},\, \Delta T}}{\dot S'_{\mathrm{gen},\, \Delta T}+ \dot S'_{\mathrm{gen},\, \Delta p}}	thermodynamics (ratio of heat transfer irreversibility to total irreversibility due to heat transfer and fluid friction)[8]
# Bingham number	Bm	\mathrm{Bm} = \frac{ \tau_y L }{ \mu V }	fluid mechanics, rheology (ratio of yield stress to viscous stress)[5]
# Biot number	Bi	\mathrm{Bi} = \frac{h L_C}{k_b}	heat transfer (surface vs. volume conductivity of solids)
# Blake number	Bl or B	\mathrm{B} = \frac{u \rho}{\mu (1 - \epsilon) D}	geology, fluid mechanics, porous media (inertial over viscous forces in fluid flow through porous media)
# Bodenstein number	Bo or Bd	\mathrm{Bo} = vL/\mathcal{D} = \mathrm{Re}\, \mathrm{Sc} 	chemistry (residence-time distribution; similar to the axial mass transfer Peclet number)[9]
# Bond number	Bo	\mathrm{Bo} = \frac{\rho a L^2}{\gamma}	geology, fluid mechanics, porous media (buoyant versus capilary forces, similar to the Eötvös number) [10]
# Brinkman number	Br	 \mathrm{Br} = \frac {\mu U^2}{\kappa (T_w - T_0)}	heat transfer, fluid mechanics (conduction from a wall to a viscous fluid)
# Brownell–Katz number	NBK	\mathrm{N}_\mathrm{BK} = \frac{u \mu}{k_\mathrm{rw}\sigma} 	fluid mechanics (combination of capillary number and Bond number) [11]
# Capillary number	Ca	\mathrm{Ca} = \frac{\mu V}{\gamma} 	porous media, fluid mechanics (viscous forces versus surface tension)
# Chandrasekhar number	Q	 \mathrm{Q} = \frac{{B_0}^2 d^2}{\mu_0 \rho \nu \lambda} 	magnetohydrodynamics (ratio of the Lorentz force to the viscosity in magnetic convection)
# Colburn J factors	JM, JH, JD		turbulence; heat, mass, and momentum transfer (dimensionless transfer coefficients)
# Coefficient of kinetic friction	\mu_k		mechanics (friction of solid bodies in translational motion)
# Coefficient of static friction	\mu_s		mechanics (friction of solid bodies at rest)
# Coefficient of determination	R^2		statistics (proportion of variance explained by a statistical model)
# Coefficient of variation	\frac{\sigma}{\mu}	\frac{\sigma}{\mu}	statistics (ratio of standard deviation to expectation)
# Correlation	ρ or r	\frac{{\mathbb E}[(X-\mu_X)(Y-\mu_Y)]}{\sigma_X \sigma_Y} or  \frac{\sum_{k=1}^n (x_k-\bar x)(y_k-\bar y)}{\sqrt{\sum_{k=1}^n (x_k-\bar x)^2 \sum_{k=1}^n (y_k-\bar y)^2}}  where \bar x = \sum_{k=1}^n x_k/n and similarly for \bar y	statistics (measure of linear dependence)
# Courant–Friedrich–Levy number	C or 𝜈	C = \frac {u\,\Delta t} {\Delta x}	mathematics (numerical solutions of hyperbolic PDEs)[12]
# Damkohler number	Da	 \mathrm{Da} = k \tau	chemistry (reaction time scales vs. residence time)
# Damping ratio	\zeta	 \zeta = \frac{c}{2 \sqrt{km}}	mechanics (the level of damping in a system)
# Darcy friction factor	Cf or fD		fluid mechanics (fraction of pressure losses due to friction in a pipe; four times the Fanning friction factor)
# Darcy number	Da	 \mathrm{Da} = \frac{K}{d^2}	porous media (ratio of permeability to cross-sectional area)
# Dean number	D	\mathrm{D} = \frac{\rho V d}{\mu} \left( \frac{d}{2 R} \right)^{1/2}	turbulent flow (vortices in curved ducts)
# Deborah number	De	 \mathrm{De} = \frac{t_\mathrm{c}}{t_\mathrm{p}}	rheology (viscoelastic fluids)
# Decibel	dB		acoustics, electronics, control theory (ratio of two intensities or powers of a wave)
# Drag coefficient	cd	c_\mathrm{d} = \dfrac{2 F_\mathrm{d}}{\rho v^2 A}\, ,	aeronautics, fluid dynamics (resistance to fluid motion)
# Dukhin number	Du	 \mathrm{Du} = \frac{\kappa^{\sigma}}{{\Kappa_m} a}	colloid science (ratio of electric surface conductivity to the electric bulk conductivity in heterogeneous systems)
# Eckert number	Ec	 \mathrm{Ec} = \frac{V^2}{c_p\Delta T}  	convective heat transfer (characterizes dissipation of energy; ratio of kinetic energy to enthalpy)
# Ekman number	Ek	\mathrm{Ek} = \frac{\nu}{2D^2\Omega\sin\varphi} 	geophysics (viscous versus Coriolis forces)
# Elasticity
# (economics)	E	E_{x,y} = \frac{\partial \ln(x)}{\partial \ln(y)} = \frac{\partial x}{\partial y}\frac{y}{x}	economics (response of demand or supply to price changes)
# Eötvös number	Eo	\mathrm{Eo}=\frac{\Delta\rho \,g \,L^2}{\sigma}	fluid mechanics (shape of bubbles or drops)
# Ericksen number	Er	\mathrm{Er}=\frac{\mu v L}{K}	fluid dynamics (liquid crystal flow behavior; viscous over elastic forces)
# Euler number	Eu	 \mathrm{Eu}=\frac{\Delta{}p}{\rho V^2} 	hydrodynamics (stream pressure versus inertia forces)
# Euler's number	e	e =  \displaystyle\sum\limits_{n = 0}^{ \infty} \dfrac{1}{n!} \approx 2.71828 	mathematics (base of the natural logarithm)
# Excess temperature coefficient	\Theta_r	\Theta_r = \frac{c_p (T-T_e)}{U_e^2/2}	heat transfer, fluid dynamics (change in internal energy versus kinetic energy)[13]
# Fanning friction factor	f		fluid mechanics (fraction of pressure losses due to friction in a pipe; 1/4th the Darcy friction factor)[14]
# Feigenbaum constants	\alpha, \delta	\alpha \approx 2.50290,
# \ \delta \approx 4.66920 	chaos theory (period doubling)[15]
# Fine structure constant	\alpha	\alpha = \frac{e^2}{2\varepsilon_0 hc}	quantum electrodynamics (QED) (coupling constant characterizing the strength of the electromagnetic interaction)
# f-number	f	 f = \frac {{\ell}}{{D}}	optics, photography (ratio of focal length to diameter of aperture)
# Föppl–von Kármán number	\gamma	\gamma = \frac{Y r^2}{\kappa}	virology, solid mechanics (thin-shell buckling)
# Fourier number	Fo	\mathrm{Fo} = \frac{\alpha t}{L^2}	heat transfer, mass transfer (ratio of diffusive rate versus storage rate)
# Fresnel number	F	\mathit{F} = \frac{a^{2}}{L \lambda}	optics (slit diffraction)[16]
# Froude number	Fr	\mathrm{Fr} = \frac{v}{\sqrt{g\ell}}	fluid mechanics (wave and surface behaviour; ratio of a body's inertia to gravitational forces)
# Gain	–		electronics (signal output to signal input)
# Gain ratio	–		bicycling (system of representing gearing; length traveled over length pedaled)[17]
# Galilei number	Ga	\mathrm{Ga} = \frac{g\, L^3}{\nu^2}	fluid mechanics (gravitational over viscous forces)
# Golden ratio	\varphi	\varphi = \frac{1+\sqrt{5}}{2} \approx 1.61803	mathematics, aesthetics (long side length of self-similar rectangle)
# Görtler number	G	\mathrm{G} = \frac{U_e \theta}{\nu} \left( \frac{\theta}{R} \right)^{1/2}	fluid dynamics (boundary layer flow along a concave wall)
# Graetz number	Gz	\mathrm{Gz} = {D_H \over L} \mathrm{Re}\, \mathrm{Pr}	heat transfer, fluid mechanics (laminar flow through a conduit; also used in mass transfer)
# Grashof number	Gr	 \mathrm{Gr}_L = \frac{g \beta (T_s - T_\infty ) L^3}{\nu ^2}	heat transfer, natural convection (ratio of the buoyancy to viscous force)
# Gravitational coupling constant	\alpha_G	\alpha_G=\frac{Gm_e^2}{\hbar c}	gravitation (attraction between two massy elementary particles; analogous to the Fine structure constant)
# Hatta number	Ha	\mathrm{Ha} = \frac{N_{\mathrm{A}0}}{N_{\mathrm{A}0}^{\mathrm{phys}}} 	chemical engineering (adsorption enhancement due to chemical reaction)
# Hagen number	Hg	 \mathrm{Hg} = -\frac{1}{\rho}\frac{\mathrm{d} p}{\mathrm{d} x}\frac{L^3}{\nu^2} 	heat transfer (ratio of the buoyancy to viscous force in forced convection)
# Hydraulic gradient	i	i = \frac{\mathrm{d}h}{\mathrm{d}l} = \frac{h_2 - h_1}{\mathrm{length}}	fluid mechanics, groundwater flow (pressure head over distance)
# Iribarren number	Ir	\mathrm{Ir} = \frac{\tan \alpha}{\sqrt{H/L_0}}	wave mechanics (breaking surface gravity waves on a slope)
# Jakob number	Ja	\mathrm{Ja} = \frac{c_p (T_\mathrm{s} - T_\mathrm{sat}) }{\Delta H_{\mathrm{f}} }	chemistry (ratio of sensible to latent energy absorbed during liquid-vapor phase change)[18]
# Karlovitz number	Ka	\mathrm{Ka} = k t_c	turbulent combustion (characteristic flow time times flame stretch rate)
# Keulegan–Carpenter number	KC	\mathrm{K_C} = \frac{V\,T}{L}	fluid dynamics (ratio of drag force to inertia for a bluff object in oscillatory fluid flow)
# Knudsen number	Kn	\mathrm{Kn} = \frac {\lambda}{L}	gas dynamics (ratio of the molecular mean free path length to a representative physical length scale)
# Kt/V	Kt/V		medicine (hemodialysis and peritoneal dialysis treatment; dimensionless time)
# Kutateladze number	Ku	\mathrm{Ku} = \frac{U_h \rho_g^{1/2}}{\left({\sigma g (\rho_l - \rho_g)}\right)^{1/4}}	fluid mechanics (counter-current two-phase flow)[19]
# Laplace number	La	\mathrm{La} = \frac{\sigma \rho L}{\mu^2}	fluid dynamics (free convection within immiscible fluids; ratio of surface tension to momentum-transport)
# Lewis number	Le	\mathrm{Le} = \frac{\alpha}{D} = \frac{\mathrm{Sc}}{\mathrm{Pr}}	heat and mass transfer (ratio of thermal to mass diffusivity)
# Lift coefficient	CL	C_\mathrm{L} = \frac{L}{q\,S}	aerodynamics (lift available from an airfoil at a given angle of attack)
# Lockhart–Martinelli parameter	\chi	\chi = \frac{m_\ell}{m_g} \sqrt{\frac{\rho_g}{\rho_\ell}}	two-phase flow (flow of wet gases; liquid fraction)[20]
# Love numbers	h, k, l		geophysics (solidity of earth and other planets)
# Lundquist number	S	S = \frac{\mu_0LV_A}{\eta}	plasma physics (ratio of a resistive time to an Alfvén wave crossing time in a plasma)
# Mach number	M or Ma	 \mathrm{M} = \frac{{v}}{{v_\mathrm{sound}}}	gas dynamics (compressible flow; dimensionless velocity)
# Magnetic Reynolds number	Rm	\mathrm{R}_\mathrm{m} = \frac{U L}{\eta}	magnetohydrodynamics (ratio of magnetic advection to magnetic diffusion)
# Manning roughness coefficient	n		open channel flow (flow driven by gravity)[21]
# Marangoni number	Mg	\mathrm{Mg} = - {\frac{\mathrm{d}\sigma}{\mathrm{d}T}}\frac{L \Delta T}{\eta \alpha} 	fluid mechanics (Marangoni flow; thermal surface tension forces over viscous forces)
# Morton number	Mo	\mathrm{Mo} = \frac{g \mu_c^4 \, \Delta \rho}{\rho_c^2 \sigma^3}  	fluid dynamics (determination of bubble/drop shape)
# Nusselt number	Nu	\mathrm{Nu} =\frac{hd}{k}	heat transfer (forced convection; ratio of convective to conductive heat transfer)
# Ohnesorge number	Oh	 \mathrm{Oh} = \frac{ \mu}{ \sqrt{\rho \sigma L }} = \frac{\sqrt{\mathrm{We}}}{\mathrm{Re}} 	fluid dynamics (atomization of liquids, Marangoni flow)
# Péclet number	Pe	\mathrm{Pe} =  \frac{du\rho c_p}{k} = \mathrm{Re}\, \mathrm{Pr}	heat transfer (advection–diffusion problems; total momentum transfer to molecular heat transfer)
# Peel number	NP	N_\mathrm{P} = \frac{\text{Restoring force}}{\text{Adhesive force}}	coating (adhesion of microstructures with substrate)[22]
# Perveance	K	{K} = \frac{{I}}{{I_0}}\,\frac{{2}}{{\beta}^3{\gamma}^3} (1-\gamma^2f_e)	charged particle transport (measure of the strength of space charge in a charged particle beam)
# pH	\mathrm{pH}	\mathrm{pH} = - \log_{10}(a_{\textrm{H}^+}) = \log_{10}\left(\frac{1}{a_{\textrm{H}^+}}\right)	chemistry (the measure of the acidity or basicity of an aqueous solution)
# Pi	\pi	\pi = \frac{C}{d} \approx 3.14159	mathematics (ratio of a circle's circumference to its diameter)
# Pixel	px		digital imaging (smallest addressable unit)
# Poisson's ratio	\nu	\nu = -\frac{\mathrm{d}\varepsilon_\mathrm{trans}}{\mathrm{d}\varepsilon_\mathrm{axial}} 	elasticity (load in transverse and longitudinal direction)
# Porosity	\phi	\phi = \frac{V_\mathrm{V}}{V_\mathrm{T}}	geology, porous media (void fraction of the medium)
# Power factor	P/S		electronics (real power to apparent power)
# Power number	Np	 N_p = {P\over \rho n^3 d^5} 	electronics (power consumption by agitators; resistance force versus inertia force)
# Prandtl number	Pr	\mathrm{Pr} = \frac{\nu}{\alpha}  = \frac{c_p \mu}{k}	heat transfer (ratio of viscous diffusion rate over thermal diffusion rate)
# Prater number	β	\beta = \frac{-\Delta H_r D_{TA}^e C_{AS}}{\lambda^e T_s}	reaction engineering (ratio of heat evolution to heat conduction within a catalyst pellet)[23]
# Pressure coefficient	CP	C_p = {p - p_\infty \over \frac{1}{2} \rho_\infty V_\infty^2}	aerodynamics, hydrodynamics (pressure experienced at a point on an airfoil; dimensionless pressure variable)
# Q factor	Q	Q = 2 \pi f_r \frac{\text{Energy Stored}}{\text{Power Loss}}	physics, engineering (damping of oscillator or resonator; energy stored versus energy lost)
# Radian measure	rad	\text{arc length}/\text{radius}	mathematics (measurement of planar angles, 1 radian = 180/π degrees)
# Rayleigh number	Ra	\mathrm{Ra}_{x} = \frac{g \beta} {\nu \alpha} (T_s - T_\infin) x^3 	heat transfer (buoyancy versus viscous forces in free convection)
# Refractive index	n	n=\frac{c}{v}	electromagnetism, optics (speed of light in a vacuum over speed of light in a material)
# Relative density	RD	RD = \frac{\rho_\mathrm{substance}}{\rho_\mathrm{reference}}	hydrometers, material comparisons (ratio of density of a material to a reference material—usually water)
# Relative permeability	\mu_r	\mu_r = \frac{\mu}{\mu_0}	magnetostatics (ratio of the permeability of a specific medium to free space)
# Relative permittivity	\varepsilon_r	\varepsilon_{r} = \frac{C_{x}} {C_{0}}	electrostatics (ratio of capacitance of test capacitor with dielectric material versus vacuum)
# Reynolds number	Re	\mathrm{Re} = \frac{vL\rho}{\mu}	fluid mechanics (ratio of fluid inertial and viscous forces)[5]
# Richardson number	Ri	 \mathrm{Ri} = \frac{gh}{u^2} = \frac{1}{\mathrm{Fr}^2} 	fluid dynamics (effect of buoyancy on flow stability; ratio of potential over kinetic energy)[24]
# Rockwell scale	–		mechanical hardness (indentation hardness of a material)
# Rolling resistance coefficient	Crr	C_{rr} = \frac{F}{N_f} 	vehicle dynamics (ratio of force needed for motion of a wheel over the normal force)
# Roshko number	Ro	 \mathrm{Ro} = {f L^{2}\over \nu} =\mathrm{St}\,\mathrm{Re} 	fluid dynamics (oscillating flow, vortex shedding)
# Rossby number	Ro	\mathrm{Ro}=\frac{U}{Lf}	geophysics (ratio of inertial to Coriolis force)
# Rouse number	P or Z	\mathrm{P} = \frac{w_s}{\kappa u_*}	sediment transport (ratio of the sediment fall velocity and the upwards velocity of grain)

# Shape factor	H	H = \frac {\delta^*}{\theta}	boundary layer flow (ratio of displacement thickness to momentum thickness)
# Sherwood number	Sh	\mathrm{Sh} = \frac{K L}{D} 	mass transfer (forced convection; ratio of convective to diffusive mass transport)
# Shields parameter	\tau_* or \theta	\tau_{\ast} = \frac{\tau}{(\rho_s - \rho) g D}	sediment transport (threshold of sediment movement due to fluid motion; dimensionless shear stress)
# Sommerfeld number	S	 \mathrm{S} = \left( \frac{r}{c} \right)^2 \frac {\mu N}{P}	hydrodynamic lubrication (boundary lubrication)[26]
# Specific gravity	SG		(same as Relative density)
# Stanton number	St	\mathrm{St} = \frac{h}{c_p \rho V} = \frac{\mathrm{Nu}}{\mathrm{Re}\,\mathrm{Pr}} 	heat transfer and fluid dynamics (forced convection)
# Stefan number	Ste	\mathrm{Ste} = \frac{c_p \Delta T}{L}	phase change, thermodynamics (ratio of sensible heat to latent heat)
# Stokes number	Stk or Sk	\mathrm{Stk} = \frac{\tau U_o}{d_c}	particles suspensions (ratio of characteristic time of particle to time of flow)
# Strain	\epsilon	\epsilon = \cfrac{\partial{F}}{\partial{X}} - 1	materials science, elasticity (displacement between particles in the body relative to a reference length)
# Strouhal number	St or Sr	\mathrm{St} = {\omega L\over v} 	fluid dynamics (continuous and pulsating flow; nondimensional frequency)[27]
# Stuart number	N	 \mathrm{N} = \frac {B^2 L_{c} \sigma}{\rho U} = \frac{\mathrm{Ha}^2}{\mathrm{Re}} 	magnetohydrodynamics (ratio of electromagnetic to inertial forces)
# Taylor number	Ta	 \mathrm{Ta} = \frac{4\Omega^2 R^4}{\nu^2}	fluid dynamics (rotating fluid flows; inertial forces due to rotation of a fluid versus viscous forces)
# Transmittance	T	 T =  \frac{I}{I_0}	optics, spectroscopy (the ratio of the intensities of radiation exiting through and incident on a sample)
# Ursell number	U	\mathrm{U} = \frac{H\, \lambda^2}{h^3}	wave mechanics (nonlinearity of surface gravity waves on a shallow fluid layer)
# Vadasz number	Va	\mathrm{Va} = \frac{\phi\, \mathrm{Pr}}{\mathrm{Da}}	porous media (governs the effects of porosity \phi, the Prandtl number and the Darcy number on flow in a porous medium) [28]
# van 't Hoff factor	i	 i = 1 + \alpha (n - 1)	quantitative analysis (Kf and Kb)
# Wallis parameter	j*	j^* = R \left( \frac{\omega \rho}{\mu} \right)^\frac{1}{2}	multiphase flows (nondimensional superficial velocity)[29]
# Weaver flame speed number	Wea	\mathrm{Wea} = \frac{w}{w_\mathrm{H}} 100	combustion (laminar burning velocity relative to hydrogen gas)[30]

# Weissenberg number	Wi	\mathrm{Wi} = \dot{\gamma} \lambda 	viscoelastic flows (shear rate times the relaxation time)[31]
# Womersley number	\alpha	\alpha = R \left( \frac{\omega \rho}{\mu} \right)^\frac{1}{2}	biofluid mechanics (continuous and pulsating flows; ratio of pulsatile flow frequency to viscous effects)[32]





end # module
