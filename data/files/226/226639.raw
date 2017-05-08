# installation script for local ubitrack version (with homebrew dependencies)

import Base: show
import Base: Pkg.Git

import Homebrew

@unix_only begin
    mkpath("src")
    cd("src")
    if !isdir("ubitrack")
        Git.run(`clone -b master git@git.magicvisionlab.com:mirrors/buildenvironment.git ubitrack`)
        cd("ubitrack")
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utcore.git modules/utcore`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utcomponents.git modules/utcomponents`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utvision.git modules/utvision`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utvisioncomponents.git modules/utvisioncomponents`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utfacade.git modules/utfacade`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utdataflow.git modules/utdataflow`)
        # Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/uthaptics.git modules/uthaptics`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/utvisualization.git modules/utvisualization`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/natnet.git modules/natnet`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/artdriver.git modules/artdriver`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/flycapture.git modules/flycapture`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/video4linux.git modules/video4linux`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/firewirecamera.git modules/firewirecamera`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:mirrors/multimarkertracker.git modules/multimarkertracker`)
        Git.run(`submodule add -b master git@git.magicvisionlab.com:ubitrack/utzmq.git modules/utzmq`)
        cd("..")
    end
    cd("..")

    map(mkpath, ("builds/ubitrack", "usr$WORD_SIZE"))
	try
		info("Building Ubitrack library from source")
		cd("builds/ubitrack") do
			options = map(x -> "-D$(x[1])=$(x[2])", Dict(
				"BUILD_SHARED_LIBS"     => "ON",
				"CMAKE_INSTALL_PREFIX"  => "../../usr$WORD_SIZE",
                "Boost_DIR" => Homebrew.prefix(),
                "OPENCV_ROOT_DIR" => Homebrew.prefix(),
			))
			run(`cmake $options ../../src/ubitrack`)
			run(`make install`)
		end
	catch e
		warn(e)
	end

end

