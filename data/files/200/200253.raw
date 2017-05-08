# Simulation

type Simulation
    YAML_filename::String
    grid::Grids.Grid
    flow_data :: Array

    configure::Function
    setup::Function

    function Simulation(YAML_filename="IBFS_config_def.yml")
        this = new()
        this.YAML_filename = YAML_filename

        # ------------------- Configuration ------------------- #
        this.configure = function()
            println("------ Configure ...")
            # Configuration file
            println("Configuration file: ", this.YAML_filename)
            config_options = YAML.load(open(this.YAML_filename))
            config_options["solver"]["cg_eps"] = float(config_options["solver"]["cg_eps"])
            println(config_options)

            # Grid instance and configuration
            if config_options["grid"]["implementation"] == "StaggeredGrid2D"
                this.grid = Grids.StaggeredGrid2D()
            else
                println("Not implemented option.")
            end
            this.grid.configure(config_options["grid"])

            # Flow data instances of length nt
            this.flow_data = Array(DataTypes.FlowSnapshot,config_options["solver"]["nt"])
        end #fun config

        # ------------------- Initialization ------------------- #
        this.setup = function()
            println("------ Setup grid and initialize variables ...")
        end #fun init

        return this
    end

end #type
