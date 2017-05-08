function rmSgrd(sgrd)
    # after converting from sgrd to tiff, we assume we are done with the sgrd
    # file, this could be made optional
    prefix=splitext(sgrd)[1]
    run(`rm $prefix.mgrd`)
    run(`rm $prefix.prj`)
    run(`rm $prefix.sdat`)
    run(`rm $prefix.sgrd`)
end


