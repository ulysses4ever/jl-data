function basicTerrainAnalysis(elevation; shade=false, slope=false, aspect=false,
    hcurv=false, vcurv=false, convergence=false, sinks=false, carea=false,
    wetness=false, lsfactor=false, channels=false, basins=false, chnl_base=false,
    chnl_alti=false, vall_depth=false, rsp=false, threshold=5)

    # generate a temp file for the SAGA grid, then use the GDAL importer to
    # read the elevation data
    println("Importing raster $elevation...")
    grids=tempname()".sgrd"
    tic()
    tiff2sgrd(elevation, grids)
    @printf "\t"
    toc()

    println("Performing basic terrain analysis... (",
        shade ? " shade" : "",
        slope ? " slope" : "",
	aspect ? " aspect" : "",
	hcurv ? " hcurv" : "",
	vcurv ? " vcurv" : "",
	convergence ? " convergence" : "",
	sinks ? " sinks" : "",
	carea ? " carea" : "",
	wetness ? " wetness" : "",
	lsfactor ? " lsfactor" : "",
	channels ? " channels" : "",
	basins ? " basins" : "",
	chnl_base ? " chnl_base" : "",
	chnl_alti ? " chnl_alti" : "",
	vall_depth ? " vall_depth" : "",
	rsp ? " rsp" : "",
	" )")
    shade_name = shade ? tempname()".sgrd" : ""
    slope_name = slope ? tempname()".sgrd" : ""
    aspect_name = aspect ? tempname()".sgrd" : ""
    hcurv_name = hcurv ? tempname()".sgrd" : ""
    vcurv_name = vcurv ? tempname()".sgrd" : ""
    convergence_name = convergence ? tempname()".sgrd" : ""
    sinks_name = sinks ? tempname()".sgrd" : ""
    carea_name = carea ? tempname()".sgrd" : ""
    wetness_name = wetness ? tempname()".sgrd" : ""
    lsfactor_name = lsfactor ? tempname()".sgrd" : ""
    channels_name = channels ? tempname()".sgrd" : ""
    basins_name = basins ? tempname()".sgrd" : ""
    chnl_base_name = chnl_base ? tempname()".sgrd" : ""
    chnl_alti_name = chnl_alti ? tempname()".sgrd" : ""
    vall_depth_name = vall_depth ? tempname()".sgrd" : ""
    rsp_name = rsp ? tempname()".sgrd" : ""
    tic()
    run(`saga_cmd -f=s ta_compound 0 -ELEVATION $grids -SHADE $shade_name
	-SLOPE $slope_name -ASPECT $aspect_name -HCURV $hcurv_name
	-VCURV $vcurv_name -CONVERGENCE $convergence_name -SINKS $sinks_name
	-CAREA $carea_name -WETNESS $wetness_name -LSFACTOR $lsfactor_name
	-CHANNELS $channels_name -BASINS $basins_name
	-CHNL_BASE $chnl_base_name -CHNL_ALTI $chnl_alti_name
	-VALL_DEPTH $vall_depth_name -RSP $rsp_name -THRESHOLD $threshold`)
    @printf "\t"
    toc()

    # form the output file name based on the elevation basename and directory
    println("Exporting rasters...")
    prefix=splitext(elevation)[1]
    tic()
    @sync begin
	shade ? (@spawn sgrd2tiff(shade_name, "$prefix-shade.tif")) : nothing
	slope ? (@spawn sgrd2tiff(slope_name, "$prefix-slope.tif")) : nothing
	aspect ? (@spawn sgrd2tiff(aspect_name, "$prefix-aspect.tif")) : nothing
	hcurv ? (@spawn sgrd2tiff(hcurv_name, "$prefix-hcurv.tif")) : nothing
	vcurv ? (@spawn sgrd2tiff(vcurv_name, "$prefix-vcurv.tif")) : nothing
	convergence ? (@spawn sgrd2tiff(convergence_name, "$prefix-convergence.tif")) : nothing
	sinks ? (@spawn sgrd2tiff(sinks_name, "$prefix-sinks.tif")) : nothing
	carea ? (@spawn sgrd2tiff(carea_name, "$prefix-carea.tif")) : nothing
	wetness ? (@spawn sgrd2tiff(wetness_name, "$prefix-wetness.tif")) : nothing
	lsfactor ? (@spawn sgrd2tiff(lsfactor_name, "$prefix-lsfactor.tif")) : nothing
	channels ? (@spawn sgrd2tiff(channels_name, "$prefix-channels.tif")) : nothing
	basins ? (@spawn sgrd2tiff(basins_name, "$prefix-basins.tif")) : nothing
	chnl_base ? (@spawn sgrd2tiff(chnl_base_name, "$prefix-chnl_base.tif")) : nothing
	chnl_alti ? (@spawn sgrd2tiff(chnl_alti_name, "$prefix-chnl_alti.tif")) : nothing
	vall_depth ? (@spawn sgrd2tiff(vall_depth_name, "$prefix-vall_depth.tif")) : nothing
	rsp ? (@spawn sgrd2tiff(rsp_name, "$prefix-rsp.tif")) : nothing
    end
    @printf "\telapsed time: %f seconds\n" toq()

    # cleanup
    rmSgrd(grids)
end

