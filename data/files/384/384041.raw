using LightXML

function main(xml_filename, desired_species_filename,output_file_name)
	
	data_dictionary = Dict();
	comparment_name_array = AbstractString[]; #for storing comparment names
	comparment_connection_name_array = AbstractString[]; #for storing comparment connection names
	symbol_array =AbstractString[]; #for storing species names
	complete_names_array = AbstractString[]; #for storing complete names
	compound_dict = Dict()
	to_plot = AbstractString[]; #for storing which species to make plots for


	xdoc = parse_file(xml_filename);
	xroot = root(xdoc);
	println(name(xroot));
	comparment_name_array= get_compartment_names(xroot)
	println("Found Comparments:")
	println(comparment_name_array)
	comparment_connection_name_array= get_compartment_connection_names(xroot)
	println("Found Connections:")
	println(comparment_connection_name_array)
	symbol_array = get_species_names(xroot)
	complete_names_array= construct_all_names(comparment_name_array, symbol_array)
	compound_dict = construct_all_names_dict(complete_names_array)
	to_plot = get_desired_species(desired_species_filename, complete_names_array)
	numSpecies = length(symbol_array)
	numCompartments = length(comparment_name_array)

	generate_plotting_code(to_plot, output_file_name, compound_dict,comparment_name_array,numSpecies,numCompartments, 0,10,.02)
	#for key in sort(collect(keys(compound_dict)))
        #   println("$key => $(compound_dict[key])")
       # end

end

function get_compartment_names(xroot)
	comparment_name_array = AbstractString[]; #for storing comparment names
	for c in child_nodes(xroot)  # c is an instance of XMLNode
	    #println(nodetype(c))
	    if is_elementnode(c)
		e = XMLElement(c)  # this makes an XMLElement instance
		if((name(e)=="listOfCompartments"))
			ces = collect(child_elements(e))
			for item in ces
				for a in attributes(item)  # a is an instance of XMLAttr
				    if(name(a)=="symbol")
				    	v = value(a)
					push!(comparment_name_array, v)
					end
				end
			end
		end
	    end
	end
	return comparment_name_array
end

function get_compartment_connection_names(xroot)
	comparment_connection_name_array = AbstractString[]; #for storing comparment names
	v =""
	w = ""
	for c in child_nodes(xroot)  # c is an instance of XMLNode
	    #println(nodetype(c))
	    if is_elementnode(c)
		e = XMLElement(c)  # this makes an XMLElement instance
		if((name(e)=="listOfCompartmentConnections"))
			ces = collect(child_elements(e))
			for item in ces
				for a in attributes(item)  # a is an instance of XMLAttr
				    if(name(a)=="start_symbol")
				    	v = value(a)
					
				    end
					if(name(a)=="end_symbol")
						w = value(a)
					end
					
				end
				namestr = string(v, "_to_", w)
				push!(comparment_connection_name_array, namestr)
			end
		end
	    end
	end
	return comparment_connection_name_array
end

function get_species_names(xroot)
	symbol_array =Any[];
	index_counter = 1;
	for c in child_nodes(xroot)  # c is an instance of XMLNode
	    #println(nodetype(c))
	    if is_elementnode(c)
		e = XMLElement(c)  # this makes an XMLElement instance
		if((name(e)=="listOfSpecies"))
			ces = collect(child_elements(e))
			for item in ces
				for a in attributes(item)  # a is an instance of XMLAttr
				    if(name(a)=="symbol")
				    	v = value(a)
					push!(symbol_array, v)
					index_counter= index_counter+1
					end
				end
			end
		end
	    end
	end
	return symbol_array
end

function construct_all_names(comparment_name_array,symbol_array)
	complete_names_array = AbstractString[];
	counter = 1;	
	#generate biochemical species names
	for comparment in comparment_name_array
		for symbol in symbol_array
			completeString = string(symbol,"_",comparment)
			push!(complete_names_array, completeString)
		end
	end
	
	#generate volume terms
	for comparment in comparment_name_array
		completeString= string("volume_", comparment)
		push!(complete_names_array, completeString)
	end
	return complete_names_array
end

function construct_all_names_dict(complete_names_array)
	compound_dict = Dict()
	for (n,f) in enumerate(complete_names_array)
		compound_dict[n] = f
	end
	return compound_dict
end

function get_desired_species(desired_species_filename, complete_names_array)
	to_plot = AbstractString[]
	f = open(desired_species_filename)
	for ln in eachline(f)
		stringln = (strip(ln));
		#println(stringln)
		if(stringln in complete_names_array)
			push!(to_plot, stringln)
		else
			println("$ln is not a valid species")
		end
	end
	close(f)
	return to_plot
end

function writeCopyright(openfile)
	write(openfile, "# ----------------------------------------------------------------------------------- #\n")
	write(openfile,"# Copyright (c) 2016 Varnerlab\n")
	write(openfile,"# School of Chemical Engineering Purdue University\n")
	write(openfile, "# W. Lafayette IN 46907 USA\n")
	write(openfile, "\n")
	write(openfile, "# Permission is hereby granted, free of charge, to any person obtaining a copy\n")
	write(openfile, "# of this software and associated documentation files (the \"Software\"), to deal\n")
	write(openfile, "# in the Software without restriction, including without limitation the rights \n")
	write(openfile, "# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n")
	write(openfile, "# copies of the Software, and to permit persons to whom the Software is \n")
	write(openfile, "# furnished to do so, subject to the following conditions:\n")
	write(openfile, "#\n")
	write(openfile, "# The above copyright notice and this permission notice shall be included in\n")
	write(openfile, "# all copies or substantial portions of the Software.\n")
	write(openfile, "#\n")
	write(openfile, "# THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n")
	write(openfile, "# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n")
	write(openfile, "# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n")
	write(openfile, "# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n")
	write(openfile, "# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n")
	write(openfile, "# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n")
	write(openfile, "# THE SOFTWARE.\n")
	write(openfile, "# ----------------------------------------------------------------------------------- #\n")

	return openfile	
end

function writeAlias(openfile, compound_dict)
	for k in keys(compound_dict)
		write(openfile, string("\t", compound_dict[k], " = x[:, ", k, "]\n"))
	end

	return openfile
end

function writePlotting(openfile, to_plot,numSpecies,numCompartments)
	numPlots = length(to_plot)
	#if numPlots > 5, make multiple rows
	#else, just plot in one rows
	counter = 1
	if(numPlots > 5)
		maxDim = ceil(sqrt(numPlots))
		while(counter<=numPlots)
			write(openfile, string("\t plt[:subplot](", numCompartments,",",numSpecies,",",counter,")\n" ))
			write(openfile, "\t plt[:tick_params](axis=\"both\", which=\"major\", labelsize=7)\n")
			write(openfile, "\t plt[:tick_params](axis=\"both\", which=\"minor\", labelsize=7)\n")
			write(openfile, "\t plt[:ticklabel_format](axis=\"y\", useOffset=false)\n")
			write(openfile, string("\t plot(t, ", to_plot[counter], " ,linewidth=2.0,\"k\")\n"))
			write(openfile, string("\t title(\"", to_plot[counter], "\" ,fontsize = 10)\n"))
			counter = counter+1;
		end
	else
		while(counter <= numPlots)
			write(openfile, string("\t plt[:subplot](1,",numPlots,",",counter,")\n" ))
			write(openfile, "\t plt[:tick_params](axis=\"both\", which=\"major\", labelsize=7)\n")
			write(openfile, "\t plt[:tick_params](axis=\"both\", which=\"minor\", labelsize=7)\n")
			write(openfile, "\t plt[:ticklabel_format](axis=\"y\", useOffset=false)\n")
			write(openfile, string("\t plot(t, ", to_plot[counter], " ,linewidth=2.0, \"k\")\n"))
			write(openfile, string("\t title(\"", to_plot[counter], "\" ,fontsize = 10)\n"))
			counter = counter+1;
		end
	end
	return openfile

end

function writePlotVolumes(openfile, comparment_name_array)
	numPlots = length(comparment_name_array)
	#if numPlots > 5, make multiple rows
	#else, just plot in one rows
	counter = 1
	if(numPlots > 5)
		maxDim = ceil(sqrt(numPlots))
		while(counter<=numPlots)
			plottingstr = string("volume_", comparment_name_array[counter])
			write(openfile, string("\t plt[:subplot](", maxDim,",",maxDim,",",counter,")\n" ))
			write(openfile,string("\t plot(t, ", plottingstr, ")\n"))
			write(openfile, string("\t title(\"", plottingstr, "\")\n"))
			counter = counter+1;		
		end
	else
		while(counter<=numPlots)
			plottingstr = string("volume_", comparment_name_array[counter])
			write(openfile, string("\t plt[:subplot](1,",numPlots,",",counter,")\n" ))
			write(openfile,string("\t plot(t, ", plottingstr, ")\n"))
			write(openfile, string("\t title(\"", plottingstr, "\")\n"))
			counter = counter+1;
		end
	end	

	return openfile
end

function generate_plotting_code(to_plot, output_file_name, compound_dict,comparment_name_array, numSpecies, numCompartments,tstart, tend, step)
	f = open(output_file_name, "w")
	f = writeCopyright(f)
	#write includes
	write(f,"include(\"SolveBalances.jl\")\n")
	write(f,"include(\"DataFile.jl\")\n")

	#we use PyPlot, so add that
	write(f, "using PyPlot\n")
	
	write(f, "function runModel()\n")
	write(f, "\t close(\"all\") #close already open windows\n")
	write(f, "\t#set start time, stop time and step sizes\n")
	write(f, string("\t tstart=", tstart, "\n"))
	write(f, string("\t tend=", tend, "\n"))
	write(f, string("\t step=", step, "\n"))
	
	write(f, "\t data_dict = DataFile(tstart, tend, step)\n")
	write(f,"\t t, x = SolveBalances(tstart, tend, step, data_dict)\n")
	write(f, "\t #Alias the species vector\n")
	f = writeAlias(f, compound_dict)
	write(f, "\n")
	write(f, "\t #code to plot, using subplots\n")
	write(f, "\t figure(figsize=(20,20))\n")
	write(f, "\t PyPlot.hold(true)\n")
	write(f, "\t plt[:tight_layout]() \t #to prevent plots from overlapping\n")
	f = writePlotting(f, to_plot,numSpecies,numCompartments)

	write(f, "\n")
	write(f, "\t #code to plot compartment volumes, using subplots\n")
	write(f, "\t figure(figsize=(20,20))\n")
	write(f, "\t PyPlot.hold(true)\n")
	write(f, "\t plt[:tight_layout]() \t #to prevent plots from overlapping\n")
	f = writePlotVolumes(f, comparment_name_array)

	write(f, "\t end\n")
	write(f, "runModel()\n")
	close(f)

end


main("debug/PBPK_AST.xml", "desiredspecies.txt", "src/runModel.jl")
