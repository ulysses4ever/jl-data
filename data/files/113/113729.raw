function analyticalHillshading(elevation; method=0)
    # generate a temp file for the SAGA grid, then use the GDAL importer to
    # read the elevation data
    println("Importing raster $elevation...")
    grids=tempname()".sgrd"
    tic()
    tiff2sgrd(elevation, grids)
    @printf "\t"
    toc()

    # generate temp files for all requested products, then use Slope, Aspect,
    # Curvature module to process
    println("Computing hillshade...")
    hillshade_name = tempname()".sgrd"
    tic()
    run(`saga_cmd ta_lighting 0 -ELEVATION $grids -SHADE $hillshade_name -METHOD $method`)
    @printf "\t"
    toc()

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(elevation)[1]
    tic()
    sgrd2tiff(hillshade_name, "$prefix-hillshade.tif")
    @printf "\telapsed time: %f seconds\n" toq()

    # cleanup
    rmSgrd(grids)
end


