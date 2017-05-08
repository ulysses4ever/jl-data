module OLS

using Distributions
export ols
export olstable

function ols(y,x)
	x   = hcat(ones(size(x, 1)), x)
	b   = (x'*x)\x'*y
	r   = y-x*b
	
	nobs = size(y, 1)         # number of observations
	ncoef = size(x, 2)        # number of coefficients
	df_e = nobs - ncoef       # degrees of freedom, error
	df_r = ncoef - 1          # degrees of freedom, regression
	
	tss = (y-mean(y))'*(y-mean(y))
	rss = r'*r
	ess = tss-rss
	
	R2  = ess./tss                      # R-squared
	R2adj = 1 - (1 - R2) * ((nobs - 1) / (nobs - ncoef)) # R2 adjusted
	F = (R2 / df_r) / ((1 - R2) / df_e) # model F-statistic
	
	s2  = rss/(nobs-ncoef)    # Residual variance
	s2  = s2[1,1] 						# convert to float
	cov = s2.*inv(x'*x)                 # OLS variance-covariance matri
	se  = sqrt(diag(cov))              # OLS standard errors
	t   = b./se 						# T-value
	p   = ccdf(TDist(df_e), abs(t))*2      # P-values
    return b, se, t, R2, R2adj, F, s2, p
end

# Print function
function olstable(title,lbly,lblx,b,se,t,R2,R2adj,F,s2,p)
# Print output in a table
println("")
println(title)
println(string("Dependent Variable: ", lbly))
println("========================================================")
println("Variable     Parm. Val.  Std. Err.  t-Value    Pr(>|t|)")
for (i, j, s, t, p) in zip(lblx, b, se ,t, p)
@printf("%-10s",i), @printf("%11.4f",j), @printf("%11.4f", s), @printf("%11.4f", t), @printf("%11.4f\n", p)
end
println("--------------------------------------------------------")
println(string("R-squared:           " , round(R2[1,1],2)))
println(string("Adjusted R-Squared:  " , round(R2adj[1,1],2)))
println(string("Sigma-squared:       " , round(s2[1,1],2)))
println(string("F-Statistic :        " , round(F[1,1],2)))
println("========================================================")
end

end # module
