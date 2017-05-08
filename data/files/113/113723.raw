function strahlerOrder(elevation)
    # generate a temp file for the SAGA grid, then use the GDAL importer to
    # read the elevation data
    println("Importing raster $elevation...")
    grids=tempname()".sgrd"
    @time tiff2sgrd(elevation, grids)

    # generate temp files for all requested products, then use Slope, Aspect,
    # Curvature module to process
    println("Computing Strahler order...")
    strahler_name = tempname()".sgrd"
    @time run(`saga_cmd ta_channels 6 -DEM $grids -STRAHLER $strahler_name`)

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(elevation)[1]
    @time sgrd2tiff(strahler_name, "$prefix-strahler.tif")

    # cleanup
    rmSgrd(grids)
end


