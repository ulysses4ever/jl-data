function slopeStability(slope)
    # generate a temp file for the SAGA grid, then use the GDAL importer to
    # read the elevation data
    println("Importing raster $slope...")
    grids=tempname()".sgrd"
    tic()
    tiff2sgrd(slope, grids)
    @printf "\t"
    toc()

    # generate temp files for all requested products, then use Slope, Aspect,
    # Curvature module to process
    println("Computing slope stability...")
    values_name = tempname()".sgrd"
    classes_name = tempname()".sgrd"
    tic()
    run(`saga_cmd ta_slope_stability 0 -A $grids -G $values_name -H $classes_name`)
    @printf "\t"
    toc()

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(slope)[1]
    tic()
    sgrd2tiff(values_name, "$prefix-values.tif")
    sgrd2tiff(classes_name, "$prefix-classes.tif")
    @printf "\telapsed time: %f seconds\n" toq()

    # cleanup
    #rmSgrd(grids)
end

