function curvatureClassification(elevation)
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
    println("Computing curvature classification...")
    class_name = tempname()".sgrd"
    tic()
    run(`saga_cmd ta_morphometry 4 -DEM $grids -CLASS $class_name`)
    @printf "\t"
    toc()

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(elevation)[1]
    tic()
    sgrd2tiff(class_name, "$prefix-class.tif")
    @printf "\telapsed time: %f seconds\n" toq()

    # cleanup
    rmSgrd(grids)
end

# saga Slope, Aspect, Curvature
function slopeAspectCurvature(elevation; slope=false, aspect=false,
    curvature=false, c_gene=false, c_prof=false, c_plan=false, c_tang=false,
    c_long=false, c_cros=false, c_mini=false, c_maxi=false, c_tota=false,
    c_roto=false, method=6, unit_slope=1, unit_aspect=1)

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
    println("Computing primitives... (",
        slope ? " slope" : "",
	aspect ? " aspect" : "",
	c_gene ? " c_gene" : "",
	c_prof ? " c_prof" : "",
	c_plan ? " c_plan" : "",
	c_tang ? " c_tang" : "",
	c_long ? " c_long" : "",
	c_cros ? " c_cros" : "",
	c_mini ? " c_mini" : "",
	c_maxi ? " c_maxi" : "",
	c_tota ? " c_tota" : "",
	c_roto ? " c_roto" : "",
	" )")
    slope_name = slope ? tempname()".sgrd" : ""
    aspect_name = aspect ? tempname()".sgrd" : ""
    c_gene_name = c_gene ? tempname()".sgrd" : ""
    c_prof_name = c_prof ? tempname()".sgrd" : ""
    c_plan_name = c_plan ? tempname()".sgrd" : ""
    c_tang_name = c_tang ? tempname()".sgrd" : ""
    c_long_name = c_long ? tempname()".sgrd" : ""
    c_cros_name = c_cros ? tempname()".sgrd" : ""
    c_mini_name = c_mini ? tempname()".sgrd" : ""
    c_maxi_name = c_maxi ? tempname()".sgrd" : ""
    c_tota_name = c_tota ? tempname()".sgrd" : ""
    c_roto_name = c_roto ? tempname()".sgrd" : ""
    tic()
    run(`saga_cmd -f=s ta_morphometry 0 -ELEVATION $grids -SLOPE $slope_name
        -ASPECT $aspect_name -C_GENE $c_gene_name -C_PROF $c_prof_name
	-C_PLAN $c_plan_name -C_TANG $c_tang_name -C_LONG $c_long_name
	-C_CROS $c_cros_name -C_MINI $c_mini_name -C_MAXI $c_maxi_name
	-C_TOTA $c_tota_name -C_ROTO $c_roto_name -METHOD $method
	-UNIT_SLOPE $unit_slope -UNIT_ASPECT $unit_aspect`)
    @printf "\t"
    toc()

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(elevation)[1]
    tic()
    @sync begin
	slope ? (@spawn sgrd2tiff(slope_name, "$prefix-slope.tif")) : nothing
	aspect ? (@spawn sgrd2tiff(aspect_name, "$prefix-aspect.tif")) : nothing
	c_gene ? (@spawn sgrd2tiff(c_gene_name, "$prefix-c_gene.tif")) : nothing
	c_prof ? (@spawn sgrd2tiff(c_prof_name, "$prefix-c_prof.tif")) : nothing
	c_plan ? (@spawn sgrd2tiff(c_plan_name, "$prefix-c_plan.tif")) : nothing
	c_tang ? (@spawn sgrd2tiff(c_tang_name, "$prefix-c_tang.tif")) : nothing
	c_long ? (@spawn sgrd2tiff(c_long_name, "$prefix-c_long.tif")) : nothing
	c_cros ? (@spawn sgrd2tiff(c_cros_name, "$prefix-c_cros.tif")) : nothing
	c_mini ? (@spawn sgrd2tiff(c_mini_name, "$prefix-c_mini.tif")) : nothing
	c_maxi ? (@spawn sgrd2tiff(c_maxi_name, "$prefix-c_maxi.tif")) : nothing
	c_tota ? (@spawn sgrd2tiff(c_tota_name, "$prefix-c_tota.tif")) : nothing
	c_roto ? (@spawn sgrd2tiff(c_roto_name, "$prefix-c_roto.tif")) : nothing
    end
    @printf "\telapsed time: %f seconds\n" toq()

    # cleanup
    rmSgrd(grids)
end

