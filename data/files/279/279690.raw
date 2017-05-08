function initialize_package_array(package_list)
	println("\nOpening, parsing, sorting, and making package list array.\n")
	Unsorted_Package_List = ASCIIString[]
	Intermediary_Package_List = ASCIIString[]
	file = open(package_list);
	Intermediary_Package_List = readdlm(file, ASCIIString)

	for i in Intermediary_Package_List
		push!(Unsorted_Package_List, i)
	end

	global Sorted_Package_List=sort(Unsorted_Package_List)
end

function install(Package_Array)
	println("\nUpdating package database, and installed packages.\n")
	Pkg.update()
	check_installed=0
	println("\nBeginning installation of designated packages.\n")
	for i in Package_Array
		if check_installed == 0
			y=string(Pkg.installed())
		end
		if contains(y, i)
			println("Already got ", i, " installed dude!")
			check_installed=1	
		else
			println("Installing ", i, " now.")
			Pkg.add(i)
			check_installed=0
		end
	end
	println("All done here!")
end

Package_List1 = "pkg_list.txt"
initialize_package_array(Package_List1)
install(Sorted_Package_List)
