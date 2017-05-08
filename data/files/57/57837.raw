using Base.Test

test_handler(r::Test.Success) = println("Test success: $(r.expr)")
test_handler(r::Test.Failure) = println("Test failure: $(r.expr)")
test_handler(r::Test.Error) = println("Test error: $(r.expr)")

f() = throw(DomainError())
g() = throw(BoundsError())
h() = error("An error happened")

Test.with_handler(test_handler) do
    @test_throws DomainError f()
    @test_throws BoundsError g()
    @test 1 != 1
    @test 1 == 1
    @test h()
    @test_throws BoundsError f()
    @test_throws DomainError g()
end
