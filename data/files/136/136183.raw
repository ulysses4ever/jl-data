using ThighDemo
using Base.Test

function test_readPhantom()
    @test size(ThighDemo.readPhantom(1)) == (48, 51);
    @test size(ThighDemo.readPhantom(2)) == (99, 104);
    @test size(ThighDemo.readPhantom(3)) == (200, 211);
    @test size(ThighDemo.readPhantom(4)) == (403, 424);
    @test_throws ErrorException ThighDemo.readPhantom(5);
end

function runtests()
    test_readPhantom();
end
