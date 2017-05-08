module TestBlackbox
    using BasicSpace

    data = [
        1.0 2.0 3.0 4.0;
        2.0 3.0 4.0 5.0;
        3.0 4.0 5.0 7.0;
    ]

    res = BasicSpace.blackbox(data, verbose = true)

    @printf("Stimuli:              %s\n", repr(res.stimuli))
    @printf("Individuals:          %s\n", repr(res.individuals))
    @printf("Fits:                 %s\n", repr(res.fits))
    @printf("# of Rows:            %d\n", res.nrow)
    @printf("# of Columns:         %d\n", res.ncol)
    @printf("# of Data Points:     %d\n", res.ndata)
    @printf("# of Missing Points:  %d\n", res.nmiss)
    @printf("Sum of squared error: %f\n", res.ss_mean)
    @printf("# of Dimensions:      %d\n", res.dims)
end
