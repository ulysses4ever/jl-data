module VAR_module
	type VAR_estimate
		data::Array{Float64, 2}
        residuals::Array{Float64, 2}
		lags::Int
		A_coef::Array{Float64, 3}
	end

	function VAR(X::Array{Float64, 2}, lags::Int)
		(T, vars) = size(X)
		y = X[(lags+1):T,:]
		x = X[((lags+1):T) - 1,:]
		for i=2:lags
			x = [x X[((lags+1):T) - i,:]]
		end
		beta = x\y
		A_coef = zeros(Float64, (vars, vars, lags))
		for i=1:lags
			A_coef[:,:,i] = beta[(1:vars) + (i-1)*vars,:]'
		end
		estimate = VAR_estimate(X, y-x*beta, lags, A_coef)
		return estimate
	end

	function Phi(var::VAR_estimate, H::Int)
		Phi_est = zeros(Float64, (size(var.data)[2], size(var.data)[2], H))
		Phi_est[:,:,1] = eye(size(var.data)[2])
        for i=2:H
			if (i<=var.lags) 
				for j = (1:(i-1))
					Phi_est[:,:,i] = Phi_est[:,:,i] + Phi_est[:,:,i-j]*var.A_coef[:,:,j]
				end
			else
				for j = (1:(var.lags))
					Phi_est[:,:,i] = Phi_est[:,:,i] + Phi_est[:,:,i-j]*var.A_coef[:,:,j]
				end
			end
        end
        for i=1:H
			
		end
		return Phi_est
	end

	function Psi(var::VAR_estimate, H::Int)
		Psi_est = zeros(Float64, (size(var.data)[2], size(var.data)[2], H))
		Omega = (var.residuals'*var.residuals)/(size(var.data)[1])
		L = chol(Omega, :L)
		Phi_est = Phi(var, H)
		for i=1:H
			Psi_est[:,:,i] = Phi_est[:,:,i] * L
		end
		return Psi_est
	end

	function irf(var::VAR_estimate, H::Int)
		irf_est = Psi(var, H)
		return irf_est
	end
end