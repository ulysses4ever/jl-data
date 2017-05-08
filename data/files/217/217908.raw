using ArgParse

function parse_cmdline()
    settings = ArgParseSettings()
    @add_arg_table settings begin
        "--gc"
            arg_type = Bool
            default = true
            help = "collect garbage between iterations"
        "--ci"
            arg_type = FloatingPoint
            default = 0.95
            help = "bootstrap confidence interval"
        "--list"
            action = :store_true
            help = "print only a list of benchmark names"
        "--report"
            arg_type = String
            default = nothing
            help = "file to write report"
        "--quiet"
            action = :store_true
            help = "print less output"
        "--resamples"
            arg_type = Integer
            default = 100 * 1000
            help = "number of botstrap resamples to perform"
        "--results"
            arg_type = String
            default = nothing
            help = "file to write raw results to"
        "--samples"
            arg_type = Integer
            default = 100
            help = "number of samples to collect"
        "--summary"
            arg_type = String
            default = nothing
            help = "produce a summary csv file of all results"
        "--no-measurements"
            action = :store_true
            help = "don't do any measurements"
        "--junit"
            arg_type = String
            default = nothing
            help = "produce a junit report file of all results"
        end
    parse_args(settings)
end

function main()
    parsed_args = parse_cmdline()
    cfg = config(parsed_args)
end 
