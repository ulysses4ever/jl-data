type BlackBox
    stimuli
    individuals
    fits::Vector{Float64}
    nrow::Int
    ncol::Int
    ndata::Int
    nmiss::Int
    ss_mean::Float64
    dims::Int
end

# function DataFrames.describe(x::BlackBox)
#     print("\n\nSUMMARY OF BLACKBOX OBJECT")
#     print("\n----------------------------------")
#     for i in 1:x.dims
#         cat("\n")
#         print(x.stimuli[i])
#     end

#     @printf("\n\tDimensions Estimated: %d", x.dims)
#     @printf("\n\tNumber of Rows: %d", x.nrow)
#     @printf("\n\tNumber of Columns: %d", x.ncol)
#     @printf("\n\tTotal Number of Data Entries: %d", x.ndata)
#     @printf("\n\tNumber of Missing Entries: %d", x.nmiss)
#     @printf(
#         "\n\tPercent Missing Data: %f%%",
#         round(100 * x.nmiss / (x.ndata + x.nmiss), 2)
#     )
#     @printf("\n\tSum of Squares (Grand Mean): %f", x.ss_mean)
#     @printf("\n\n")
# end

function blackbox(
    data::Matrix{Float64};
    missing::Array{Int32} = Int32[], # May be NULL
    verbose::Bool = false,
    dims::Int32 = int32(1),
    minscale::Int32 = int32(1),
    stimnames::Vector{UTF8String} = UTF8String[]
)
    # Error check each argument
    if minscale < 1
        error("Argument 'minscale' must be positive.")
    end
    if dims < 1
        error("Argument 'dims' must be positive.")
    end

    # Format the data input
    n = int32(size(data, 1))
    nq = int32(size(data, 2))

    # TODO: Decide what to do here
    # This is a stupid way of doing things
    # if isa(missing, Vector)
    #   data[data %in% missing] <- NA
    # end
    # if isa(missing, Matrix)
    #   for(i in 1:ncol(data))  data[data[,i] %in% missing[,i],i] <- NA
    # end
    missval = maximum(data) + 1 # code for missing data
    rawdata = data'
    # TODO: Decide what to do here
    # rawdata[isna(rawdata)] = missval

    # Longer output
    if isempty(stimnames)
        stimnames = UTF8String[@sprintf("stim%d", i) for i in 1:n]
    end
    if verbose
        # deleted = sum(isna([sum(data[i, :]) for i in 1:n]))
        print("\n\n\tBeginning Blackbox Scaling...")
        @printf("%d stimuli have been provided.", nq)
    end

    fits = Array(Float64, 7 * dims)
    psimatrix = Array(Float64, n * int((dims * (dims + 1)) / 2) + 2 * n * dims)
    wmatrix = Array(Float64, nq * int((dims * (dims + 1)) / 2) + 2 * nq * dims)
    lresp = Array(Int32, n + nq)
    lmark = Array(Int32, n)
    fits2 = Array(Float64, 6)
    status = Array(Int32, 1)

    res = ccall(
        (:blackbox_, libpath),
        Void,
        (
            Ptr{Int32},   # NRESPONDENTS
            Ptr{Int32},   # NISSUES
            Ptr{Int32},   # NDIMENSIONS
            Ptr{Int32},   # NMISSING
            Ptr{Float64}, # KMISS
            Ptr{Int32},   # MINSCALE
            Ptr{Int32},   # MID
            Ptr{Float64}, # KISSUE
            Ptr{Uint8},   # CAND
            Ptr{Float64}, # FITS
            Ptr{Float64}, # PSIMATRIX
            Ptr{Float64}, # WMATRIX
            Ptr{Int32},   # LRESPONDENTS
            Ptr{Int32},   # LMARK
            Ptr{Float64}, # FITS2
            Ptr{Int32}    # EXITSTATUS
        ),
        &n,                             # NRESPONDENTS
        &nq,                            # NISSUES
        &dims,                          # NDIMENSIONS
        &1,                             # NMISSING
        Float64[missval for i in 1:nq], # KMISS
        &minscale,                      # MINSCALE
        Int32[1 for i in 1:n],          # MID
        rawdata,                        # KISSUE
        [uint8('a')],                   # CAND, not used
        fits,                           # FITS
        psimatrix,                      # PSIMATRIX
        wmatrix,                        # WMATRIX
        lresp,                          # LRESPONDENTS
        lmark,                          # LMARK
        fits2,                          # FITS2
        status                          # EXITSTATUS
    )

    if status[1] != 1
        error("\n\n\t====== Blackbox did not execute properly ======\n\n")
    end

    stimuli = Array(Any, dims)
    # start = 1
    # myend = 3 * nq
    # for i in 1:dims
    #     stimuli[i] = DataFrame(
    #         matrix(
    #             round(wmatrix[start:myend], 3),
    #             nrow = nq,
    #             ncol = i + 2,
    #             byrow = T)
    #     )
    #     colnames(stimuli[[i]]) <- c("c",paste("w",1:i,sep=""),"R2")
    #     rownames(stimuli[[i]]) <- stimnames
    #     stimuli[[i]] <- cbind(N=res$lresp[1:NQ],stimuli[[i]])
    #     start = myend + 1
    #     myend = start + (i + 3) * nq - 1
    # end

    individuals = Array(Any, dims)
    # start = 1
    # myend = n
    # for i in 1:dims
    #     individuals[i] = DataFrame(
    #         matrix(
    #             round(psimatrix[start:myend], 3),
    #             nrow = n,
    #             ncol = i,
    #             byrow = T)
    #     )
    #     dumpthese = (rowSums(individuals[[i]]==0)==i)
    #     individuals[[i]][dumpthese,] <- NA
    #     colnames(individuals[[i]]) <- c(paste("c",1:i,sep=""))
    #     rownames(individuals[[i]]) <- rownames(data)
    #     start = myend + 1
    #     myend = start + (i + 1) * n - 1
    # end

    # fits = reshape(fits, dims, 7, byrow = T)
    #   fits <- as.data.frame(fits[,c(1:3,6:7),drop=FALSE])
    #   colnames(fits) <- c("SSE","SSE.explained","percent","SE","singular")
    #   rownames(fits) <- paste("Dimension",1:dims)

    result = BlackBox(
        stimuli,
        individuals,
        fits,
        fits2[1],
        fits2[2],
        fits2[3],
        fits2[4],
        fits2[6],
        dims
    )

    if verbose
        print("\n\n\tBlackbox estimation completed successfully.\n\n")
    end

    return result
end
