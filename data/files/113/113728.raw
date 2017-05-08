function catchmentArea(elevation; method=4)
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
    println("Computing catchment area...")
    carea_name = tempname()".sgrd"
    tic()
    run(`saga_cmd ta_hydrology 0 -ELEVATION $grids -CAREA $carea_name -Method $method`)
    @printf "\t"
    toc()

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(elevation)[1]
    tic()
    sgrd2tiff(carea_name, "$prefix-carea.tif")
    @printf "\telapsed time: %f seconds\n" toq()

    # cleanup
    rmSgrd(grids)
end

