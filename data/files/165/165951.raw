# Install and update a repository that contains all existing Julia packages.
function install()
	if !ispath(Pkg.dir())
		Pkg.init()
	end
	# TODO: Change this to only fetch metadata entries
	Pkg.update()
	packages = Pkg.available()
	for package in packages
		Pkg.add(package)
	end
end
