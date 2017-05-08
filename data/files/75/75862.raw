# protein type that keeps centered MD data for a protein
# 2014 - murozturk@ku.edu.tr

immutable protein
	R::Matrix{Float64}
	index::Vector{Int}
	means::Vector{Float64}
	stdPerRes::Vector{Float64}
	covariance::Matrix{Float64}

	function protein(R::Matrix{Float64}, index=1:size(R,2))
		m = mean(R,1)
		R .-= m
		
		println ("Calculating covariance matrix...")	
		gamma = cov(R, mean=0, corrected=false)
		
		println ("Calculating real fluctuations...")	
		rF = realFluc(R, centered=true) 

		new(R, index[:], m[:], std(rF,1)[:], gamma  )
	end
end

# Returns decentered coordinates
# recovers original md data

deCenter(p::protein) = p->p.R .+ p.means'

# Returns real fluctuations per residue

function realFluc(R::Matrix{Float64}; centered=false)
	!centered && (R .-= mean(R,1)) 
	sqrt(R[:,1:3:end].^2 + R[:,2:3:end].^2 + R[:,3:3:end].^2)
end
realFluc(p::protein) = realFluc(p.R, centered=true)

