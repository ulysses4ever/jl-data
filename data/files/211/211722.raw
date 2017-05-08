#Brian Pomerantz
function testVar(y::Array)
	println(var3d(y));
	println(var(y));

	thsh = 0.01;
	@test_approx_eq_eps(var3d(y), var(y), thsh);
end
