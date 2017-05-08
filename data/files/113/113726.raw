tiff2sgrd(tiff, sgrd) = run(`saga_cmd -f=s io_gdal 0 -FILES $tiff -GRIDS $sgrd`)

function sgrd2tiff(sgrd, tiff)
    run(`saga_cmd -f=s io_gdal 1 -GRIDS $sgrd -FORMAT 1 -TYPE 0 -FILE $tiff
        -NODATA -99999`)

    # cleanup
    rmSgrd(sgrd)
end

