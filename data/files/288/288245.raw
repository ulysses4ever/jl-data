using DimensionalAnalysis
using Base.Test

@test typeof( dimensionless()) == PhysicalQuantity{Int,0,0,0,0,0,0,0}
@test typeof( dimensionless())   <: Dimensionless
@test typeof( 3*dimensionless()) <: Dimensionless
@test typeof( dimensionless()/4 ) <: Dimensionless

@test dimensionless( 2 ) > dimensionless( 1 )
@test !( dimensionless( 1 ) > dimensionless( 2 ))
@test !( dimensionless( 2 ) > dimensionless( 2 ))

@test dimensionless( 2 ) >= dimensionless( 1 )
@test dimensionless( 2 ) >= dimensionless( 2 )
@test !( dimensionless( 1 ) >= dimensionless( 2 ))

@test dimensionless( 2 ) == dimensionless( 2 )
@test !( dimensionless( 1 ) == dimensionless( 2 ))
@test !( dimensionless( 2 ) == dimensionless( 1 ))

@test dimensionless( 1 ) <= dimensionless( 2 )
@test dimensionless( 1 ) <= dimensionless( 1 )
@test !( dimensionless( 2 ) <= dimensionless( 1 ))

@test dimensionless( 1 ) < dimensionless( 2 )
@test !( dimensionless( 1 ) < dimensionless( 1 ))
@test !( dimensionless( 2 ) < dimensionless( 1 ))


@test dimensionless( 2 ) > 1
@test 2 > dimensionless( 1 )
@test !( dimensionless( 1 ) > 2)
@test !( 1 > dimensionless( 2 ))
@test !( dimensionless( 1 ) > 1 )
@test !( 1 > dimensionless( 1 ))

@test dimensionless( 2 ) >= 1
@test !( 1 >= dimensionless( 2 ))

@test typeof( mass()) == PhysicalQuantity{Int,1,0,0,0,0,0,0}
@test typeof( mass()) <: Mass


@test typeof( length_()) == PhysicalQuantity{Int,0,1,0,0,0,0,0}
@test typeof( length_()) <: Length

@test typeof( time_()) == PhysicalQuantity{Int,0,0,1,0,0,0,0}
@test typeof( time_()) <: Time

@test typeof( temperature()) == PhysicalQuantity{Int,0,0,0,1,0,0,0}
@test typeof( temperature()) <: Temperature

@test typeof( intensity()) == PhysicalQuantity{Int,0,0,0,0,1,0,0}
@test typeof( intensity()) <: Intensity

@test typeof( current()) == PhysicalQuantity{Int,0,0,0,0,0,1,0}
@test typeof( current()) <: Current

@test typeof( amount()) == PhysicalQuantity{Int,0,0,0,0,0,0,1}
@test typeof( amount()) <: Amount

@test typeof( length_()*length_() ) <: Area
@test typeof( length_()*length_()*length_()) <: Volume
@test typeof( length_()*area()) <: Volume

@test typeof( density()) <: Density
@test typeof( mass()/volume() ) <: Density

@test typeof( speed()) <: Speed
@test typeof( length_()/time_()) <: Speed

@test typeof( acceleration())  <: Acceleration
@test typeof( speed()/time_()) <: Acceleration

@test typeof( force()) <: Force
@test typeof( mass()*acceleration()) <: Force

@test typeof( energy()) <: Energy
@test typeof( force()*length_()) <: Energy

@test typeof( power()) <: Power
@test typeof( energy()/time_()) <: Power

@test typeof( stress()) <: Stress
@test typeof( force()/area()) <: Stress

@test typeof( pressure()) <: Pressure
@test typeof( force()/area()) <: Pressure

@test typeof( diffusivity()) <: Diffusivity
@test typeof( area()/time_()) <: Diffusivity

@test typeof( kinematicViscosity()) <: KinematicViscosity
@test typeof( kinematicViscosity()) <: Diffusivity

@test typeof( dynamicViscosity()) <: DynamicViscosity
@test typeof( density()*diffusivity()) <: DynamicViscosity

@test typeof( energy()/area()) <: SurfaceEnergy
@test typeof( surfaceEnergy()) <: SurfaceEnergy

@test typeof( density()*speed()*length_()/dynamicViscosity()) <: Dimensionless
@test typeof( speed()*length_()/kinematicViscosity()) <: Dimensionless

let ρ = density(), v = speed(), d = length_(), μ = dynamicViscosity()
    Re = ReynoldsNumber( ρ, v, d, μ )
    @test typeof( Re ) <: Dimensionless
end

let v = speed(), d = length_(), ν = kinematicViscosity()
    Re = ReynoldsNumber( v, d, ν )
    @test typeof( Re ) <: Dimensionless
end

let ρ = density(), v = speed(), d = length_(), σ = surfaceEnergy()
    We = WeberNumber( ρ, v, d, σ )
    @test typeof( We ) <: Dimensionless
end

let ρ = density(),
    v = speed(),
    d = length_(),
    σ = surfaceEnergy(),
    We = WeberNumber( ρ, v, d, σ )
    We_m = ModifiedWeberNumber( ρ, v, d, σ )
    @test typeof( ρ )    <: Density
    @test typeof( d )    <: Length
    @test typeof( σ )    <: SurfaceEnergy
    @test typeof( We_m ) <: Dimensionless
    @test We/We_m == dimensionless( 12 )
end
    

