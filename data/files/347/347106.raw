module Publish

export publish, publish_tex, setup, showit

import PGFPlots: Plots, Axis, save, TEX, PDF, SVG, Plottable, plot
export Plots, Axis, save

# Global variables
#  _output_buffer	Contains tex string
#  _num_plots		Number of plots in this document
#  _plot_list		List of the plot names
#  _publish_file	Name of file being pulished
#  _folder_name		Name of directory in which file to publish is housed
_output_buffer = nothing
_num_plots = 0
_plot_list = nothing
_publish_file = nothing
_folder_name = nothing


# Creates the tex file
# Called by publish
# filename includes the foldername...
function publish_tex(filename::String; runcode::Bool=true)
	global _output_buffer = IOBuffer()
	global _publish_file = filename
	global _plot_list = String[]

	# TODO: Here I should check for larger names (test.rar.jl)
	filename_arr = split(filename, ".")
	if filename_arr[end] == "jl"
		filename_short = filename_arr[1]
	end

	tex = open("$(filename_short).tex", "w")
	println(tex, "\\documentclass{article}")
	println(tex, "\\usepackage{caption}")

	# For quotation marks in lstlisting
	println(tex, "\\newcommand{\\dbllq}{``}")
	println(tex, "\\newcommand{\\dblrq}{''}")

	# Standalone stuff for figures
	println(tex, "\\usepackage{standalone}")
	println(tex, "\\usepackage[usenames,dvipsnames]{xcolor}")
	println(tex, "\\usepackage{pgfplots}")
	println(tex, "\\pgfplotsset{compat=newest}")

	# Change the Margins
	println(tex, "\\usepackage[margin=1.0in]{geometry}")

	# Headers, footers
	println(tex, "\\usepackage{fancyhdr}")
	println(tex, "\\pagestyle{fancy}")
	filename_sanitized = replace(filename, "_", "\\_")
	println(tex, "\\lhead{$filename_sanitized}")
	println(tex, "\\rhead{}")
	println(tex, "\\renewcommand{\\headrulewidth}{0.4pt}")
	println(tex, "\\renewcommand{\\footrulewidth}{0.4pt}")

	# listings stuff
	lst = readall(joinpath(Pkg.dir("Publish"), "src", "julia_listings.tex"))
	println(tex, lst)

	println(tex, "\\begin{document}")

	# Begin the code section
	println(tex, "\\begin{lstlisting}[style=JuliaStyle,numbers=left]")
	source_file = open(filename, "r")
	while (currentline = readline(source_file)) != ""
		print(tex, currentline)
	end
	close(source_file)
	println(tex, "\\end{lstlisting}")

	# Run the test file and print the output
	if runcode
		include(filename)
		output_string = takebuf_string(_output_buffer)
		if length(output_string) > 0
			println(tex, "\\begin{lstlisting}[style=Output]")
			println(tex, output_string)
			println(tex, "\\end{lstlisting}")
		end

		# We also have a bunch of tex plots
		global _num_plots
		global _plot_list
		for i = 1:_num_plots
			println(tex, "\\begin{figure}[!ht]")
			println(tex, "\\centering")
			println(tex, "\\input{$(_plot_list[i])}")
			println(tex, "\\end{figure}")
		end
		_num_plots = 0
	end
	_publish_file = nothing

	# End the document and close
	println(tex, "\\end{document}")
	close(tex)
end


# Does the same thing as normal println function, 
#  but also prints to a buffer if it exists.
function Base.println(xs...)
	global _output_buffer
	if _output_buffer != nothing
		println(_output_buffer, xs...)
	end
	println(STDOUT, xs...)
end


# Does the same thing as normal print function, 
#  but also prints to a buffer if it exists.
function Base.print(xs...)
	global _output_buffer
	if _output_buffer != nothing
		print(_output_buffer, xs...)
	end
	print(STDOUT, xs...)
end


function publish(filename::String; runcode::Bool=true)

	if !isfile(filename)
		error(filename, " does not exist.")
	end

	# Generate the .tex file and make pass along any possible errors
	IX = rsearch(filename,'/')              # Find the last slash
	foldername = filename[1:IX-1]           # Everything before that is the folder name
	foldername = (IX == 0 ? "." : foldername) # If there was no slash, folder is "."
	global _folder_name = foldername
	#save(TEX(f.filename * ".tex"), tp)        # Save the tex file in the directory that was given

	# This also sets the global _output_buffer to a value (as in, not nothing)
	# When it is done, set the global _output_buffer back to nothing
	publish_tex(filename; runcode=runcode)
	global _output_buffer = nothing

	# TODO: Here I should check for larger names (test.rar.jl)
	filename_arr = split(filename, ".")
	if filename_arr[end] == "jl"
		filename_short = filename_arr[1]
	end

	# From the .tex file, generate a pdf within the specified folder
	latexCommand = ``
	# TODO: I'm not sure what enableWrite18 does. I asssume it is some latex feature
	#if tp.enableWrite18
	#	latexCommand = `lualatex --enable-write18 --output-directory=$(foldername) $(f.filename)`
	#else
	#	latexCommand = `lualatex --output-directory=$(foldername) $(f.filename)`
	#end
	# Change to the folder...
	home = pwd()
	cd(foldername)
	latexCommand = `lualatex $(split(filename_short,"/")[end])`
	isPdfThere = success(latexCommand)
	cd(home)

	if !isPdfThere
		line1 = "ERROR: The pdf generation failed.\n"
		line2 = "   Be sure your latex libraries are fully up to date!\n"
		line3 = "   You tried: $(latexCommand)"
		error(line1 * line2 * line3)  # Throw an error
	end

	try
		# Shouldn't need to be try-catched anymore, but best to be safe
		# This failing is NOT critical either, so just make it a warning
		# Before, it checked for tikzDeleteIntermediate
		#if tikzDeleteIntermediate()
		#rm("$(filename).tex")
		rm("$(filename_short).aux")
		rm("$(filename_short).log")
	catch
		println("WARNING! Your intermediate files are not being deleted.")
	end
end


# Mostly a copy from the PGFPlots version
# However, here we also deal with some gobal stuff
function save(filename::String, o::Plottable)

	# Make sure you are referring to the global variables
	global _output_buffer
	global _num_plots
	global _plot_list
	global _publish_file
	global _folder_name

	# Determine the base and extension
    base_name, ext = splitext(filename)
    ext = lowercase(ext)

	# Additional functionality for Publish.jl
	# If this name matches the name they gave, do not accept
	# Check before the dot...
	# TODO: Ensure a clean break on error out
	if _publish_file != nothing
		file_base = splitext(_publish_file)[1]
		filename = "$(_folder_name)/$filename"
		if file_base == base_name
			_publish_file = nothing
			error("Plot name cannot equal filename")
		end
	end

	# Continue to the original save functionality
    if ext == ".pdf"
        save(PDF(filename), plot(o))
    elseif ext == ".svg"
        save(SVG(filename), plot(o))
    elseif ext == ".tex"
        save(TEX(filename), plot(o))
    elseif ext == "." || ext == ""
        error("You must specify a file extension.")
    else
        error("Unsupported file extensions: $ext")
    end

	# Additional functionality for Publish.jl
	# Save name and tex file so we can plot this later
	if _output_buffer != nothing
		_num_plots += 1
		temp_name = "$(base_name).tex"
		push!(_plot_list, temp_name)
		save(TEX("$(_folder_name)/$temp_name"), plot(o))
	end
end

end # module
