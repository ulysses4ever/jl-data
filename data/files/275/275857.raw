module TerrainMap

export Terrain_Map, terrain_contour
type Terrain_Map
    north
    north_abs
    east
    east_abs
    down

    min_N
    max_N 
    min_E
    max_E

    sig

function Terrain_Map()
    down = -10.0*ones(20,20);
    setO = Set();

    for e = 1:1:20
        for n = 1:1:20
            if(n == 15 && e == 8)
                down[n,e] = down[n,e] + 4;
            elseif(ceil(sqrt((n-15)^2+(e-8)^2)) == 1)
                down[n,e] = down[n,e] + 3;
            elseif(ceil(sqrt((n-15)^2+(e-8)^2)) == 2)
                down[n,e] = down[n,e] + 2;
            elseif(ceil(sqrt((n-15)^2+(e-8)^2)) == 3)
                down[n,e] = down[n,e] + 1;
            end

            if(floor(sqrt((n-8)^2+(e-15)^2))<= 1)
                down[n,e] = down[n,e] + 4;
            elseif(floor(sqrt((n-8)^2+(e-15)^2)) <= 2)
                down[n,e] = down[n,e] + 2;
            end

        end
    end
    this = new();
    this.down = down;
    this.north = [1.0:20.0];
    this.north_abs = this.north;
    this.east = [1.0:20.0];
    this.east_abs = this.east;
    this.min_N = 1.0;
    this.max_N = 20.0;
    this.min_E = 1.0;
    this.max_E = 20.0;
    this.sig = 0.1;
    return this
end

function Terrain_Map(filename)
    down = readdlm(filename,skipstart=2);
    down[down.==0]=NaN;
    (num_north,num_east) = size(down);
    temp = readdlm(filename);
    north = squeeze(float(temp[1,1:num_north]),1);
    east = squeeze(float(temp[2,1:num_east]),1);
    this = new();
    this.down = down;
    this.north = north-minimum(north)+1;
    this.north_abs = north;
    this.east = east-minimum(east)+1;
    this.east_abs = east;
    this.min_N = minimum(north);
    this.min_E = minimum(east);
    this.max_E = maximum(east)
    this.max_N = maximum(north)
    this.sig = 0.1;
    return this;
end
end

function terrain_countour(map)
    min_down = minimum(map.down)-1;
    max_down = maximum(map.down)+1;
    c = contour(map.east,map.north,map.down,25,cmap="ocean",vmin=min_down,vmax=max_down);
    axis("equal")
    return c
end

end # module
