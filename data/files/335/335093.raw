using AutoDiff
using Base.Test

<<<<<<< HEAD

let underlier = 1.0, derivative = 2.0, x = Dual( underlier, derivative )
    @test typeof( u( x )) == typeof( underlier )
    @test typeof( d( x )) == typeof( derivative )
    @test u( x ) == underlier
    @test d( x ) == derivative
end

let underlier1 = 1.0, derivative1 = 2.0, x = Dual( underlier1, derivative1 ),
    underlier2 = 3.0, derivative2 = 4.0, y = Dual( underlier2, derivative2 )
    let z = x+y
        @test u( z ) == underlier1+underlier2
        @test d( z ) == derivative1+derivative2
    end
    let z = x-y
        @test u( z ) == underlier1-underlier2
        @test d( z ) == derivative1-derivative2
    end
    let z = x*y
        @test u( z ) == underlier1*underlier2
        @test d( z ) == derivative1*underlier2+derivative2*underlier1
    end
    
    let z = x/y
        @test u( z ) == underlier1/underlier2
        @test d( z ) == (derivative1*underlier2-derivative2*underlier1)/underlier2^2
    end
end

let underlier = 1.0, derivative = 2.0, x = Dual( underlier, derivative )
    let y = sin( x )
        @test u( y ) == sin( underlier )
        @test d( y ) == derivative*cos( underlier )
    end
    let y = cos( x )
        @test u( y ) == cos( underlier )
        @test d( y ) == -derivative*sin( underlier )
    end
    let y = tan( x )
        @test u( y ) == tan( underlier )
        @test d( y ) == derivative*( tan( underlier )^2+1 )
    end
    let y = asin( x )
        @test u( y ) == asin( underlier )
        @test d( y ) == derivative/sqrt( 1-underlier^2 )
    end
    let y = acos( x )
        @test u( y ) == acos( underlier )
        @test d( y ) == -derivative/sqrt( 1-underlier^2 )
    end
    let y = atan( x )
        @test u( y ) == atan( underlier )
        @test d( y ) == derivative/( underlier^2+1 )
    end

    let y = sinh( x )
        @test u( y ) == sinh( underlier )
        @test d( y ) == derivative*cosh( underlier )
    end
    
    let y = cosh( x )
        @test u( y ) == cosh( underlier )
        @test d( y ) == derivative*sinh( underlier )
    end

    let y = tanh( x )
        @test u( y ) == tanh( underlier )
        @test d( y ) == derivative*( 1-tanh( underlier )^2 )
    end

    let y = asinh( x )
        @test u( y ) == asinh( underlier )
        @test d( y ) == derivative/sqrt( underlier^2+1 )
    end
    
    let y = acosh( x )
        @test u( y ) == acosh( underlier )
        @test d( y ) == derivative/sqrt( underlier^2-1 )
    end

    let y = atanh( x )
        @test u( y ) == atanh( underlier )
        @test d( y ) == derivative/( 1-underlier^2 )
    end

    let y = sqrt( x )
        @test u( y ) == sqrt( underlier )
        @test d( y ) == derivative/( 2sqrt( underlier ))
    end

    let y = exp( x )
        @test u( y ) == exp( underlier )
        @test d( y ) == derivative*exp( underlier )
    end

    let y = log( x )
        @test u( y ) == log( underlier )
        @test d( y ) == derivative/underlier
    end


    

    
    
end


=======
# write your own tests here
@test 1 == 1
>>>>>>> 5b7dcf86f5a0a3054a83233fb194c0a97db9c3c5
