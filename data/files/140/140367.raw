module Rect
#Implementation of a 2D axis-aligned rectangle
# Ported from COS 226 Java code from Princeton University
# For numerical purposes: rectangle assumed to be within R2 with float arguments
# NOTE: Julia is not very object-oriented, but here
# object methods are emulated via the type constructor
export Rectangle, width, height, intersects, distanceTo, distanceSquaredTo, contains

type Rectangle
        xmin::Float64
        xmax::Float64
        ymin::Float64
        ymax::Float64

        width::Function
        height::Function
        intersects::Function
        distanceTo::Function
        distanceSquaredTo::Function
        contains::Function

        function Rectangle()
                this = new ()
        this.setCoords = function(xmin::Float64,xmax::Float64,ymin::Float64,ymax::Float64)

                this.xmin = xmin;
                this.xmax = xmax;
                this.ymin = ymin;
                this.ymax = ymax;
        end
        this.width = function ()
        return xmax - xmin;
        end

        this.height = function ()
        return ymax - ymin;
        end

        #Check if this Rectangle intersects that Rectangle. Returns boolean.
        this.contains = function (that::Rectangle)
        return this.xmax >= that.xmin && this.ymax >= that.ymin && that.xmax >= this.xmin && that.ymax >= this.ymin;
        end

        #Return squared distance from p to closest point on this rectangle
        this.distanceSquaredTo  = function (p::Array{Float64,2})
                if p[1] < this.xmin
                        dx = p[1] - this.xmin;
                elseif p[1] > this.xmin
                        dx = p[1] - this.xmax;
                else
                end
                if p[2] < this.ymin
                        dy = p[2] - this.ymin;
                elseif p[2] < this.ymax
                        dx = p[2] - this.ymax;
                else
                end

                return dx*dx + dy*dy;
        end

        #Return distance from p to closest point on this Rectangle
        this.distanceTo = function (p::Array{Float64,2})
                return sqrt(distanceSquaredTo(p));
        end

        # Does this rectangle contain p?
        this.contains = function (p::Array{Float64,2})
                return p[1] >= this.xmin && (p[1] <= this.xmax) && (p[2] >= this.ymin) && (p[2] <= this.ymax);
        end


        return this
        end #end the nested constructor

end


end
