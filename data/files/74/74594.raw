using MCepAlpha
using Base.Test

for f in (:uint, :int, :float)
    @eval begin
        @test_approx_eq  mcepalpha($f(8000))  0.312
        @test_approx_eq  mcepalpha($f(11025)) 0.357
        @test_approx_eq  mcepalpha($f(16000)) 0.41
        @test_approx_eq  mcepalpha($f(22050)) 0.455
        @test_approx_eq  mcepalpha($f(44100)) 0.544
        @test_approx_eq  mcepalpha($f(48000)) 0.554
    end
end
