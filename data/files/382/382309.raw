#!/usr/bin/env julia

include("resume.jl")
include("InputStuff.jl")

function main()
    if length(ARGS) > 1
        input_yml = ARGS[1]
        output_path = ARGS[2]
        generate_resume(input_yml, output_path, "tex/template.tex")
        try
            run(`xelatex --interaction=nonstopmode $output_path`)
            print("Resume generation complete.")
        catch
            println("Error compiling latex. Do you have xetex installed?")
        end
    else
        generate_resume(InputStuff.input("Resume yaml path: "), InputStuff.input("Output path: "), "tex/template.tex")
    end
end

main()
