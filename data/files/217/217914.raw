abstract MatchType 
type Prefix <: MatchType end
type Glob <: MatchType end

abstract Verbosity
type Quiet   <: Verbosity end
type Normal  <: Verbosity end
type Verbose <: Verbosity end

abstract PrintExit
type Nothing <: PrintExit end
type List    <: PrintExit end
type Version <: PrintExit end


function default_config()
   {:ci => 0.95,
    :gc => true,
    :resamples  => 1000,
    :results => nothing,
    :report => nothing,
    :samples => 100,
    :summary => nothing,
    :template => "report.tpl",
    :quiet => false,
    :no_measurements => false,
    :junit => false}
end


function config(options)
   merge(default_config(), options)
end
