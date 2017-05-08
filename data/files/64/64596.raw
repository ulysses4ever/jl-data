using ZipFile

using AVRDUDE

ver = AVRDUDE.version

install_path = Pkg.dir("AVRDUDE", "deps", "avrdude", "v"*ver)

!isdir(install_path) && mkpath(install_path)

zip_loc = joinpath(install_path, ver*".zip")

# Grab the repo with all the flash tools
if !isfile(zip_loc)
    download("https://github.com/sjkelly/arduino-flash-tools/archive/v$(ver).zip",
             zip_loc)
end

# Determine the AVRDUDE version we need to use
@windows_only (avr_version = "tools_windows")
@osx_only (avr_version = "tools_darwin")

@linux_only begin
    if contains(Sys.MACHINE, "arm")
        avr_version = "tools_linux_arm"
    elseif WORD_SIZE == 32
        avr_version = "tools_linux_32"
    else
        avr_version = "tools_linux_64"
    end
end

avrdude_ziploc = "arduino-flash-tools-"*ver*"/"*avr_version*"/avrdude/"

r = ZipFile.Reader(zip_loc)
for f in r.files
    if startswith(f.name, avrdude_ziploc)
        zipf = replace(f.name, avrdude_ziploc, "")
        isempty(zipf) && continue
        if endswith(zipf, "/") || endswith(zipf, "\\")
            mkpath(joinpath(install_path, zipf))
        else
            open(joinpath(install_path, zipf), "w") do unzipped
                write(unzipped, readall(f))
            end
        end
    end
end

close(r)
