using ThighDemo
using Base.Test

function test_readPhantom()
    @test size(ThighDemo.readPhantom(1)) == (48, 51);
    @test size(ThighDemo.readPhantom(2)) == (99, 104);
    @test size(ThighDemo.readPhantom(3)) == (200, 211);
    @test size(ThighDemo.readPhantom(4)) == (403, 424);
    @test_throws ErrorException ThighDemo.readPhantom(5);
end

function test_id2_slowness()
    M = [0 3 4;5 6 7;8 9 11];
    V = id2slowness(M);
    # id2slowness should not alter M
    @test M != V;
    # id2slowness! should
    id2slowness!(M);
    @test M == V;
end

function runtests()
    test_readPhantom();
    test_id2_slowness();
end
