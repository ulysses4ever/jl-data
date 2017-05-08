module SDL
    libtest = dlopen(string(pwd(),"/libtest.so"))    
    function sdl_init()
        ccall( dlsym(libtest, :init), Void, ())
    end
    function getwindow()
        return ccall( dlsym(libtest, :getwindow), Ptr{Void}, ())
    end
    function getrenderer(window, width, height)
        return ccall( dlsym(libtest, :getrenderer), Ptr{Void}, (Ptr{Void}, Int32, Int32), window, width, height);
    end
    function getsurface(path)
        return ccall( dlsym(libtest, :getsurface), Ptr{Void}, (Ptr{Uint8},), path)
    end
    function gettexture(renderer::Ptr{Void}, path)
        return ccall( dlsym(libtest, :gettexture), Ptr{Void}, (Ptr{Void}, Ptr{Uint8}), renderer, path)
    end    
    function render(renderer, texture, x, y)
        ccall( dlsym(libtest, :render), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32), renderer, texture, x, y)
    end
    function renderagent(renderer, surface, texture, x, y, angle)
        ccall( dlsym(libtest, :renderagent), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32, Float64), renderer, texture, x, y, angle)        
    end    
    function sdl_getevents()
        return ccall( dlsym(libtest, :get_events), Ptr{Void}, ())
    end    
    function quit(window)
        ccall( dlsym(libtest, :quit), Void, (Ptr{Void},), window)
    end    
    function sdl_events(events::Ptr{Void})
        return ccall( dlsym(libtest, :sdl_events), Int32, (Ptr{Void},), events);
    end
    function setpixel(map::Ptr{Void}, x, y, r, g, b)
        ccall( dlsym(libtest, :setpixel), Int32, (Ptr{Void}, Int32, Int32, Uint8, Uint8, Uint8), map, x, y, r, g, b);
    end
    function update(src::Ptr{Void})
        ccall( dlsym(libtest, :update), Void, (Ptr{Void},), src);
    end
    export sdl_init, quit, getwindow, getrenderer, gettexture, getsurface, setpixel, update,
          sdl_events, sdl_getevents, render, renderagent, libtest
end

module Motion
    using SDL
    using constants
    using Images: imread, float32sc
        
    # creating a list of index to check in img_background for collision
    img_background = int8(float32sc(imread(world_name)).data');
    img_agent = int8(float32sc(imread(agent_name)).data');
    contour_index = find(i->i==0,img_agent)
    # info about the world and the agent
    height, width = size(img_background)
    width_agent, height_agent = size(img_agent)        
    # SDL initiation
    sdl_init();
    window = getwindow()
    renderer = getrenderer(window, width, height);
    background_surface = getsurface(world_name)
    background_texture = gettexture(renderer, world_name)
    agent = gettexture(renderer, agent_name)
    events = sdl_getevents();    
    
    function quit()
        quit(window)
    end

    function checkcollision(x,y)    
        if int8(0) in img_background[y:y+height_agent,x:x+width_agent][contour_index]
            return false
        else
            return true
        end
    end

    function move(x, y, vr, vl, length, theta)    
        if abs(vr-vl) > 1e-6        
            cste1 = (length*(vr+vl))/(2*(vr-vl))
            cste2 = theta+((vr-vl)*dt)/length
            return [x+cste1*(sin(cste2)-sin(theta)),y+cste1*(cos(cste2)-cos(theta)), cste2]
        elseif (vr>0.0) & (vl>0.0)
            return [x+dt*cos(theta)*vr, y-dt*sin(theta)*vl, theta]
        else
            return [x-dt*cos(theta)*vr, y+dt*sin(theta)*vl, theta]
        end
    end

    function drive(pos, vr, vl)
        new_pos = move(pos[1], pos[2], vr, vl, wheel_dist, pos[3])    
        if checkcollision(int(new_pos[1]-width_agent/2), int(new_pos[2]-height_agent/2))
            pos = new_pos
            render(renderer, background_texture, 0, 0)
            renderagent(renderer, background_surface, agent, int(pos[1]-width_agent/2), int(pos[2]-height_agent/2), -180.0*pos[3]/pi)
            update(renderer)
        end
        return pos
    end

    export drive, quit, init
end

tic();
using Motion

sigmoide(x,l=1) = 1.0/(1.0+exp(-x*l))

pos = [500.0, 200.0, 0]

vr = 0.9
vl = 1.1

while true
    # println(pos')
    pos = drive(pos, vr, vl)
end
quit()
toc();







