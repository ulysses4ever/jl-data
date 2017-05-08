module gel

# package code goes here






function trunc!(g::Array(64,2), lag::Int64)
    T,m = size(g)
    j = 1
    t = T-1
    for k=1:lag
        g[1,j] += g[k+1,]
    end
    while t>1
        g[t, j]=g[t+1,j]+g[t,j]
        t -= 1
    end
    end
end
            
    
	int t, j, k, low, high, idxi, T, m;
	int bw = INTEGER(Kt)[0];
	double *pmf = REAL(mf), *rsg;
	SEXP sg, dim;
	/* double den = (2.0*bw+1.0)/2; */
	double den = (2.0*bw+1.0)/2.0;
	PROTECT(dim = allocVector(INTSXP, 2)); 
	dim = getAttrib(mf, R_DimSymbol);
	T = INTEGER(dim)[0];
	m = INTEGER(dim)[1];
 
	PROTECT(sg = allocVector(REALSXP, (T*m)));
	rsg = REAL(sg);
	for(t = 0; t < T; t++)
		{ 
			low = imax2((t-T+1), -bw);
			high = imin2(t, bw);
			for(j = 0; j < m; j++)
				{
					idxi = j*T+t;
					rsg[idxi] = 0.0;
					for(k = low; k <= high; k++)
						{
	      rsg[idxi] += pmf[(idxi-k)];
						}
					rsg[idxi] /= den;
				}
		}
	setAttrib(sg, R_DimSymbol, dim); 
	UNPROTECT(2);
	return(sg);
}




end # module
