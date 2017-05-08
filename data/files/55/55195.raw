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
    function getsurface(window::Ptr{Void})
        return ccall( dlsym(libtest, :getsurface), Ptr{Void}, (Ptr{Void},), window)
    end
    function gettexture(renderer::Ptr{Void}, path)
        return ccall( dlsym(libtest, :gettexture), Ptr{Void}, (Ptr{Void}, Ptr{Uint8}), renderer, path)
    end
    function getbackground(screen, path)
        return ccall( dlsym(libtest, :getbackground), Ptr{Void}, (Ptr{Void}, Ptr{Uint8}), screen, path)
    end 
    function render(renderer, texture, x, y)
        ccall( dlsym(libtest, :render), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32), renderer, texture, x, y)
    end
    function sdl_getevents()
        return ccall( dlsym(libtest, :get_events), Ptr{Void}, ())
    end    
    function quit(window)
        ccall( dlsym(libtest, :quit), Void, (Ptr{Void},), window)
    end
    function sdl_setvideomode(w, h)
        return ccall( dlsym(libtest, :setvideomode), Ptr{Void}, (Int32, Int32, Int32, Uint32,), w, h, 32, 0x00000000);
    end
    function sdl_creatergbsurface(w, h)
        return ccall( dlsym(libtest, :creatergbsurface), Ptr{Void}, (Int32, Int32,), w, h);
    end
    function sdl_events(events::Ptr{Void})
        return ccall( dlsym(libtest, :sdl_events), Int32, (Ptr{Void},), events);
    end
    function circle(screen, map, x, y, r)
        ccall( dlsym(libtest, :circle), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32, Int32, Uint8, Uint8, Uint8), screen, map, x, y, r, 255, 0, 0)
    end
    function setpixel(map::Ptr{Void}, x, y, r, g, b)
        ccall( dlsym(libtest, :setpixel), Int32, (Ptr{Void}, Int32, Int32, Uint8, Uint8, Uint8), map, x, y, r, g, b);
    end
    function update(src::Ptr{Void})
        ccall( dlsym(libtest, :update), Void, (Ptr{Void},), src);
    end
    function setColor(src::Ptr{Void}, r, g, b)
        ccall( dlsym(libtest, :setfullcolor), Void, (Ptr{Void}, Uint8, Uint8, Uint8), src, r, g, b)
    end
    function blitmap(map, screen, w, h)
        for i = 40:w-1
            for j = 30:50
                setpixel(map, i, j, 200, 220, 0)            
            end
        end  
        update(map, screen, w, h)
    end    

    export sdl_init, quit, getwindow, getrenderer, gettexture, getsurface, sdl_creatergbsurface, setpixel, update, setColor, blitmap, 
            getbackground, sdl_events, sdl_getevents, circle, render
end

tic();
using SDL


width = 1000
height = 1000
radius = 50

sdl_init();
window = getwindow()
renderer = getrenderer(window, width, height);
background = gettexture(renderer, "starmaze.bmp")
agent = gettexture(renderer, "agent.bmp")
events = sdl_getevents();


# while sdl_events(events) == 1 

for i = 0.0:0.001:20*pi

    x = int32(450+250*cos(i))
    y = int32(450+250*sin(i))
    render(renderer, background, 0, 0)
    render(renderer, agent, x, y)
    update(renderer)
end
# println("hello")
quit(window)
toc();