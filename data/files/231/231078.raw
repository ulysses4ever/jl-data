module REIYFramework

export main
export cfg_t
export Individual_t

using DataFrames
using ArgParse
using PyPlot
using IniFile
import Base.show

@everywhere using RNN
@everywhere using Match
@everywhere using YARS
@everywhere global yars = None

type Individual_t
  rnn::Vector{RNN_t}
  fitness::Float64
  cost::Float64
  f::Float64
  age::Int64
end


type cfg_t
  lifetime::Int64
  generations::Int64
  population_size::Int64
  nr_of_parents::Int64
  pan::Float64
  pdn::Float64
  pcn::Float64
  pas::Float64
  pds::Float64
  pmn::Float64
  pms::Float64
  db::Float64
  dw::Float64
  mb::Float64
  mw::Float64
  mn::Int64
  cn::Float64
  cs::Float64
  file::String
  ni::Int64
  no::Int64
  working_directory::String
  xml::String
  logdir::String
  logprefix::String
  startcost::Int64
  repeats::Int64

  cfg_t() = new(1000, 1000, 100, 10, 0.1, 0.1, 0.1, 0.2, 0.2, 0.1, 0.3, 0.1,
                0.5, 5.0, 20.0, 4, 0.0, 0.0, "", 0, 0, "", "", "", "", 0, 1)
end

function create_cfg(filename)
  cfg       = cfg_t()
  cfg.file  = filename
  update!(cfg)
  cfg
end

function update!(cfg::cfg_t)
  ini = Inifile()
  read(ini, cfg.file)

  cfg.lifetime          = int(get(ini,   "general", "life time",                 cfg.lifetime))
  cfg.generations       = int(get(ini,   "general", "nr of generations",         cfg.generations))
  cfg.population_size   = int(get(ini,   "general", "population size",           cfg.population_size))
  cfg.nr_of_parents     = int(get(ini,   "general", "nr of parents",             cfg.nr_of_parents))
  cfg.working_directory = get(ini,       "general", "working directory",         cfg.working_directory)
  cfg.startcost         = int(get(ini,   "general", "costs starting generation", cfg.startcost))
  cfg.xml               = get(ini,       "general", "xml file",                  cfg.xml)
  cfg.logdir            = get(ini,       "general", "log directory",             cfg.logdir)
  cfg.logprefix         = get(ini,       "general", "log prefix",                cfg.logprefix)
  cfg.repeats           = int(get(ini,   "general", "repeats",                   cfg.repeats))

  cfg.pan               = float(get(ini, "neuron",  "p(add)",                    cfg.pan))
  cfg.pdn               = float(get(ini, "neuron",  "p(del)",                    cfg.pdn))
  cfg.pcn               = float(get(ini, "neuron",  "p(connect)",                cfg.pcn))
  cfg.pmn               = float(get(ini, "neuron",  "p(modify)",                 cfg.pmn))
  cfg.db                = float(get(ini, "neuron",  "delta bias",                cfg.db))
  cfg.mb                = float(get(ini, "neuron",  "max absolute bias",         cfg.mb))
  cfg.mn                = float(get(ini, "neuron",  "max hidden neuron",         cfg.mn))
  cfg.cn                = float(get(ini, "neuron",  "cost",                      cfg.cn))
  cfg.ni                = float(get(ini, "neuron",  "nr of input neurons",       cfg.ni))
  cfg.no                = float(get(ini, "neuron",  "nr of output neurons",      cfg.no))

  cfg.pas               = float(get(ini, "synapse", "p(add)",                    cfg.pas))
  cfg.pds               = float(get(ini, "synapse", "p(del)",                    cfg.pds))
  cfg.pms               = float(get(ini, "synapse", "p(modify)",                 cfg.pms))
  cfg.dw                = float(get(ini, "synapse", "delta weigth",              cfg.dw))
  cfg.mw                = float(get(ini, "synapse", "max absolute weight",       cfg.mw))
  cfg.cs                = float(get(ini, "synapse", "cost",                      cfg.cs))
end

function show(io::IO, cfg::cfg_t)

  println("[General]")
  println("  life time:           ", cfg.lifetime)
  println("  nr of generations:   ", cfg.generations)
  println("  population size:     ", cfg.population_size)
  println("  nr of parents:       ", cfg.nr_of_parents)
  println("  working directory:   ", cfg.working_directory)
  println("  xml:                 ", cfg.xml)
  println("  file:                ", cfg.file)
  println("  log dir:             ", cfg.logdir)
  println("  repeats:             ", cfg.repeats)

  println("[Neurons]")
  println("  p(add):              ", cfg.pan)
  println("  p(del):              ", cfg.pdn)
  println("  p(connect):          ", cfg.pcn)
  println("  p(modify):           ", cfg.pmn)
  println("  delta bias:          ", cfg.db)
  println("  max absolute bias:   ", cfg.mb)
  println("  max hidden neuron:   ", cfg.mn)
  println("  cost:                ", cfg.cn)
  println("[Synapses]")
  println("  p(add):              ", cfg.pas)
  println("  p(del):              ", cfg.pds)
  println("  p(modify):           ", cfg.pms)
  println("  delta weigth:        ", cfg.dw)
  println("  max absolute weight: ", cfg.mw)
  println("  cost:                ", cfg.cs)
end

function parse_commandline()
  s = ArgParseSettings()

  @add_arg_table s begin

    "--nogui"
    help     = "don't use gui"
    action = :store_true

    "--1gui"
    help     = "only one window"
    action = :store_true

    "--init"
    help     = "initial population directory"
    arg_type = String

    "--ld"
    help     = "overwrite log directory"
    arg_type = String

    "--ports"
    help     = "give list of ports"
    arg_type = Int64
    nargs    = '*'

    "cfg"
    help = "configuration file"
    arg_type = String
    default  = nothing
    required = true

  end
  return parse_args(s)
end

function reproduce(parents::Vector{Individual_t},
                   probabilities::Vector{Float64},
                   cfg::cfg_t,
                   variate_individual, random_individual)

  r = [random_individual(cfg) for i=1:cfg.population_size]

  nr_of_parents = length(parents)
  offspring = ones(nr_of_parents)

  for i=1:nr_of_parents
    r[i] = parents[i]
    r[i].age = r[i].age + 1
  end

  for i=nr_of_parents+1:2*nr_of_parents
    r[i] = variate_individual(parents[i-nr_of_parents], cfg)
  end

  for i=2*nr_of_parents+1:cfg.population_size
    p = rand()
    s = 0
    #= println(p) =#
    for j=1:nr_of_parents
      s = s + probabilities[j]
      #= println("parent ", j, " ", s) =#
      if p <= s
        #= println("chose parent ", j) =#
        r[i] = variate_individual(parents[j], cfg)
        offspring[j] = offspring[j] + 1
        break
      end
    end
  end
  offspring = int(offspring)
  return r, offspring
end

function close_yars()
  global yars
  yars_send_quit(yars)
end

function open_yars(wd, xml, use_gui, use_single_gui, ports)
  global yars
  if length(ports) == 0
    options = [xml]
    if use_single_gui == true && myid() > 2
      options = [options, "--nogui"]
    elseif use_gui == false
      options = [options, "--nogui"]
    else
      options = @match myid() begin
        1 => options
        2 => [options, "--geometry", "320x240+0+0"]
        3 => [options, "--geometry", "320x240+0+310"]
        4 => [options, "--geometry", "320x240+0+580"]
        5 => [options, "--geometry", "320x240+0+850"]
        6 => [options, "--geometry", "320x240+350+0"]
        7 => [options, "--geometry", "320x240+350+310"]
        8 => [options, "--geometry", "320x240+350+580"]
        9 => [options, "--geometry", "320x240+350+850"]
      end
    end
    #println(options)
    yars = yars_start(wd, options)
  else
    if myid() == 1
      println("connecting to yars on port ", ports[1])
      yars = connect(ports[1])
    else
      println("connecting to yars on port ", ports[myid()-1])
      yars = connect(ports[myid()-1])
    end
  end
  return "yars instance opened"
end

function count_synapses(rnn::RNN_t)
  synapse_count = 0
  for i = 1:size(rnn.w)[1]
    for j = 1:size(rnn.w)[2]
      if rnn.w[i,j] != 0.0
        synapse_count = synapse_count + 1
      end
    end
  end
  return synapse_count
end

searchdir(path,key) = filter(x->contains(x,key), readdir(path))

function read_population_from_directory(dir::String, prefix::String, n::Int64)
  files       = searchdir(dir, prefix)
  files       = filter(r"^((?!gen))", files)
  nr_of_files = int(length(files) / n)
  r           = []
  for i=1:nr_of_files
    rnns = []
    println("reading rnns for individual $i")
    for j=1:n
      println("reading $dir/$prefix\_$i\_rnn_$j.rnn")
      rnns = [rnns, rnn_read("$dir/$prefix\_$i\_rnn_$j.rnn")]
    end
    individual = Individual_t(rnns, 0.0, 0.0, 0.0, 0)
    r = [r, individual]
  end
  return r
end

function get_last_generation_index(dir::String)
  files = searchdir(dir, "gen_")
  ids = []
  for f in files
    m = match(r"gen_(\d+)", f)
    ids = [ids, int(m.captures[1])]
  end
  ids = sort(ids,rev=true)
  id = int(ids[1])
  return id
end


function log_individual(individuals::Vector{Individual_t}, index::Int64,
  logdir::String, prefix::String)
  i_index = 1
  for i in individuals
    for j in 1:length(i.rnn)
      rnn_write(i.rnn[j],  "$logdir/$prefix\_$i_index\_rnn_$j.rnn")
    end
    i_index = i_index + 1
  end
  for j in 1:length(individuals[1].rnn)
    rnn_write(individuals[1].rnn[j], "$logdir/gen_$index\_$prefix\_rnn_$j.rnn")
  end
end

function main(random_individual, evaluate, variate_individual)
  parsed_args = parse_commandline()

  cfg_file       = parsed_args["cfg"]
  use_no_gui     = parsed_args["nogui"]
  use_single_gui = parsed_args["1gui"]
  init           = parsed_args["init"]
  ld             = parsed_args["ld"]
  ports          = parsed_args["ports"]
  use_gui        = use_no_gui == false

  cfg         = create_cfg(cfg_file)

  if use_gui
    subplots(2,2)
  end

  pointers = []
  use_gui = use_no_gui == false
  for i=1:length(workers())
    p = @spawn open_yars(cfg.working_directory, cfg.xml, use_gui, use_single_gui, ports)
    pointers = [p, pointers]
  end

  for i=1:length(pointers)
    println(fetch(pointers[i]))
  end


  for r=1:cfg.repeats
    update!(cfg)

    if ld == nothing
      logdir = cfg.logdir
    else
      logdir = ld
    end
    if cfg.repeats > 1
      logdir = "$logdir-$r"
    end

    println("log dir is $logdir")
    logprefix   = cfg.logprefix
    println(cfg)

    if isdir(logdir) == false
      mkdir(logdir)
    end

    if isfile("$logdir/log.txt")
      log_data_frame    = readtable("$logdir/log.txt")
      log_avg_fitness   = log_data_frame[:AVG]
      log_best_fitness  = log_data_frame[:BEST]
      log_std_fitness   = log_data_frame[:STD]
      log_neurons       = log_data_frame[:NEURONS]
      log_synapses      = log_data_frame[:SYNAPSES]
      log_age           = log_data_frame[:AGE]

      if use_gui
        clf()
        subplot(221)
        plot(log_best_fitness)
        plot(log_avg_fitness)
        plot(log_avg_fitness - log_std_fitness)
        plot(log_avg_fitness + log_std_fitness)
        title("fitness")
        subplot(223)
        plot(log_age)
        title("age")
        subplot(222)
        plot(log_neurons)
        title("nr. of neurons")
        subplot(224)
        plot(log_synapses)
        title("nr. of synapses")
      end


    else
      log_data_frame    = DataFrame()
      log_avg_fitness   = [0.0]
      log_best_fitness  = [0.0]
      log_std_fitness   = [0.0]
      log_neurons       = [0]
      log_synapses      = [0]
      log_age           = [0]
    end
    generation_offset = 0


    if init == nothing
      init_population = [random_individual(cfg) for i=1:cfg.nr_of_parents]

      log_data_frame    = DataFrame()
      log_avg_fitness   = [0.0]
      log_best_fitness  = [0.0]
      log_std_fitness   = [0.0]
      log_neurons       = [0]
      log_synapses      = [0]
      log_age           = [0]

    else
      i = random_individual(cfg)
      n = length(i.rnn)
      init_population = read_population_from_directory(init, logprefix, n)
      generation_offset = get_last_generation_index(init)
    end

    init_population = convert(Vector{Individual_t}, init_population)

    population, c = reproduce(init_population,
                          [1.0/(cfg.nr_of_parents)
                          for i=1:cfg.nr_of_parents], cfg,
                          variate_individual, random_individual)
    for g=1:cfg.generations
      tic()
      update!(cfg)

      evaluated = []
      index = 1
      while length(population) > 0
        pointers = []
        for i=1:length(workers())
          if length(population) > 0
            individual = pop!(population)
            p = @spawn evaluate(individual, cfg, generation_offset + g, index)
            index = index + 1
            pointers = [p, pointers]
          end
        end

        for p in pointers
          individual = fetch(p)
          evaluated  = [individual, evaluated]
        end
      end

      data    = DataFrame()

      fitness = [0.0 for i=1:length(evaluated)]
      cost    = [0.0 for i=1:length(evaluated)]
      f       = [0.0 for i=1:length(evaluated)]
      ages    = [0   for i=1:length(evaluated)]

      for i=1:length(evaluated)
        fitness[i] = evaluated[i].fitness
        cost[i]    = evaluated[i].cost
        f[i]       = evaluated[i].f
        ages[i]    = evaluated[i].age
      end
      data[:FITNESS]     = fitness
      data[:COST]        = cost
      data[:F]           = f
      data[:AGES]        = ages
      data[:INDIVIDUALS] = evaluated

      sort!(data, cols = (:F), rev=true)
      selected              = data[1:cfg.nr_of_parents, :]
      fitness_values        = selected[:F]
      individuals = convert(Vector{Individual_t}, selected[:INDIVIDUALS])

      best = individuals[1]
      nr_of_neurons  = 0
      nr_of_synapses = 0
      for rnn in best.rnn
        nr_of_neurons  += rnn.nh
        nr_of_synapses += count_synapses(rnn)
      end
      log_neurons           = [log_neurons,      nr_of_neurons]
      log_synapses          = [log_synapses,     nr_of_synapses]
      log_avg_fitness       = [log_avg_fitness,  mean(fitness_values)]
      log_best_fitness      = [log_best_fitness, maximum(fitness_values)]
      log_std_fitness       = [log_std_fitness,  std(fitness_values)]
      log_age               = [log_age,          best.age]

      result_data           = DataFrame()
      result_data[:FITNESS] = selected[:FITNESS]
      result_data[:COST]    = selected[:COST]
      result_data[:F]       = fitness_values
      result_data[:AGE]     = selected[:AGES]
      m                     = minimum(fitness_values)
      fitness_values        = fitness_values .- m
      s                     = sum(fitness_values)
      if s == 0
        for i=1:length(fitness_values)
          fitness_values[i] = 1.0/length(fitness_values)
        end
      else
        fitness_values = fitness_values ./ s
      end

      fitness_values = convert(Vector{Float64}, fitness_values)
      result_data[:PROBABILITIES] = fitness_values

      if use_gui
        clf()
        subplot(221)
        plot(log_best_fitness)
        plot(log_avg_fitness)
        plot(log_avg_fitness - log_std_fitness)
        plot(log_avg_fitness + log_std_fitness)
        title("fitness")
        subplot(223)
        plot(log_age)
        title("age")
        subplot(222)
        plot(log_neurons)
        title("nr. of neurons")
        subplot(224)
        plot(log_synapses)
        title("nr. of synapses")
      end


      log_individual(individuals, generation_offset + g, logdir, logprefix)

      fitness_values = convert(Vector{Float64}, fitness_values)
      population, c = reproduce(individuals, fitness_values, cfg,
      variate_individual, random_individual)
      result_data[:COUNTS] = c
      println("Generation ", generation_offset + g)
      println(cfg)
      println(result_data)

      log_data_frame = DataFrame()
      log_data_frame[:AVG]      = log_avg_fitness
      log_data_frame[:BEST]     = log_best_fitness
      log_data_frame[:STD]      = log_std_fitness
      log_data_frame[:NEURONS]  = log_neurons
      log_data_frame[:SYNAPSES] = log_synapses
      log_data_frame[:AGE]      = log_age

      writetable("$logdir/log.txt", log_data_frame)
      toc()

    end
  end

  for i=1:length(workers())
  p = @spawn close_yars()
  end

end


end # module
