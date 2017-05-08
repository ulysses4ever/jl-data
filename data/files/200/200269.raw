module DataTypes

    type Problem
        reynolds    ::Int
        bc_left     ::Int
        bc_bottom   ::Int
        bc_right         ::Int
        bc_top           ::Int
        flow_magnitude   ::Float64
        flow_angle       ::Float64

        Problem() = new()
    end

    type Grid
        nx          ::Int
        ny          ::Int
        height      ::Real
        width       ::Real

        Grid() = new()
    end

    type Solver
        cg_eps      ::Float64
        timestep    ::Float64
        nt          ::Int

        Solver() = new()
    end

    type Parameters
        problem::Problem
        grid::Grid
        solver::Solver

        Parameters() = new()
    end


    # Data structure for instantaneous flow data
    type FlowSnapshot
        u::Vector{Float64}
        p::Vector{Float64}
        t::Float64

        FlowSnapshot() = new()
    end

end
