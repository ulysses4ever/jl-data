#Brian Pomerantz
function var3g(arr::Array)
	n = length(arr);
	sum1 = zero(arr[1]);
	sum2 = zero(arr[1]);

	if arr[1] > 10.0^4.0 || arr[length(arr)] > 10.0^4.0
		for i in 1:n
			#if !isfinite(arr[i])
			#	return -1
			#end

			sum1 = sum1 + arr[i];
		end

		mean = sum1/n;

		for i in 1:n
			sum2 = sum2 + (arr[i] - mean)^2.0;
		end

		return sum2/(n-1);
	end

	for i in 1:n
		#if !isfinite(arr[i])
		#	return -1;
		#end

		sum1 = sum1 + arr[i];
		sum2 = sum2 + arr[i]*arr[i];
	end

	return (sum2 - ((sum1*sum1)/n))/(n-1);
end
