#Brian Pomerantz
function testValues(arr::Array)
	writer2b("2b", arr);
	writer2d("2d", arr);
	writer2e("2e", arr);

	arrB = reader2b("2b");
	arrD = reader2d("2d");
	
	thsh = 0.001;

	for i in 1:length(arr)
		temp = arr[i];
		@test_approx_eq_eps(temp, arrB[i], thsh);
		@test_approx_eq_eps(temp, arrD[i], thsh);
		#@test_approx_eq_eps(temp, reader2bf("2b", i), thsh);
		#@test_approx_eq_eps(temp, reader2df("2d", i), thsh);
	end
end

