module GridTypes
using DataTypes

#abstract Grid
    type StaggeredGrid2D# <: Grid
        nx::Int
        ny::Int
        nu::Int
        np::Int

        x::Vector{Real}
        y::Vector{Real}

        config::Function
        setup::Function
        createGrid::Function
        getSizes::Function

        function StaggeredGrid2D()
            this = new()

            this.config = function(options::DataTypes.Grid)
                this.nx = options.nx
                this.ny = options.ny
                this.x = linspace(0,options.width,options.nx+1)
                this.y = linspace(0,options.height,options.ny+1)
            end

            this.setup = function()
            end

            return this
        end
    end #StaggeredGrid2D

end #module
