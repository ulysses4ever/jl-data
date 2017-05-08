module DataTypes

    type Problem
        reynolds    ::Int
        bc_left     ::Int
        bc_bottom   ::Int
        bc_right         ::Int
        bc_top           ::Int
        flow_magnitude   ::Real
        flow_angle       ::Real

        Problem() = new(0,0,0,0,0,0.0,0.0)
    end

    type Grid
        nx          ::Int
        ny          ::Int
        width       ::Real
        height      ::Real

        Grid() = new(0,0,0.0,0.0)
    end

    type Solver
        cg_eps      ::Real
        timestep    ::Real
        nt          ::Int

        Solver() = new(0.0,0.0,0)
    end

    type Parameters
        problem::Problem
        grid::Grid
        solver::Solver

        Parameters() = new(Problem(), Grid(), Solver())
    end


    # Data structure for instantaneous flow data
    type FlowSnapshot
        u::Vector{Float64}
        p::Vector{Float64}
        t::Float64

        FlowSnapshot() = new()
    end

end
