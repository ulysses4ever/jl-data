module SDL
    libtest = dlopen(string(pwd(),"/libtest.so"))    
    function sdl_init(flags::Uint32)
        ccall( dlsym(libtest, :init), Int32, (Uint32,), 0x00000020)
    end
    function getwindow(width, height)
        return ccall( dlsym(libtest, :getwindow), Ptr{Void}, (Int32, Int32), width, height)
    end
    function getrenderer(window::Ptr{Void})
        return ccall( dlsym(libtest, :getrenderer), Ptr{Void}, (Ptr{Void},), window);
    end
    function getsurface(window::Ptr{Void})
        return ccall( dlsym(libtest, :getsurface), Ptr{Void}, (Ptr{Void},), window)
    end
    function gettexture(renderer::Ptr{Void}, window::Ptr{Void}, path)
        return ccall( dlsym(libtest, :gettexture), Ptr{Void}, (Ptr{Void}, Ptr{Void}, Ptr{Uint8}), renderer, window, path)
    end
    function getbackground(screen, path)
        return ccall( dlsym(libtest, :getbackground), Ptr{Void}, (Ptr{Void}, Ptr{Uint8}), screen, path)
    end 
    function render(renderer, texture)
        ccall( dlsym(libtest, :render), Void, (Ptr{Void}, Ptr{Void}), renderer, texture)
    end
    function sdl_getevents()
        return ccall( dlsym(libtest, :get_events), Ptr{Void}, ())
    end
    function quit()
        ccall( dlsym(libtest, :quit), Void, (Uint32,), 0x00000020)
    end
    function sdl_setvideomode(w, h)
        return ccall( dlsym(libtest, :setvideomode), Ptr{Void}, (Int32, Int32, Int32, Uint32,), w, h, 32, 0x00000000);
    end
    function sdl_creatergbsurface(w, h)
        return ccall( dlsym(libtest, :creatergbsurface), Ptr{Void}, (Int32, Int32,), w, h);
    end
    function sdl_events(events::Ptr{Void}, window::Ptr{Void})
        return ccall( dlsym(libtest, :sdl_events), Int32, (Ptr{Void}, Ptr{Void}), events, window);
    end
    function circle(screen, map, x, y, r)
        ccall( dlsym(libtest, :circle), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32, Int32, Uint8, Uint8, Uint8), screen, map, x, y, r, 255, 0, 0)
    end
    function setpixel(map::Ptr{Void}, x, y, r, g, b)
        ccall( dlsym(libtest, :setpixel), Int32, (Ptr{Void}, Int32, Int32, Uint8, Uint8, Uint8), map, x, y, r, g, b);
    end
    function update(src::Ptr{Void}, dst::Ptr{Void}, win::Ptr{Void})
        ccall( dlsym(libtest, :update), Void, (Ptr{Void}, Ptr{Void}, Ptr{Void}), src, dst, win);
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



sdl_init(0x00000020);
window = getwindow(width, height);
screen = getsurface(window);
renderer = getrenderer(window);
texture = gettexture(renderer, screen, "starmaze.bmp")
render(renderer, texture)
# screen = getsurface(window);
# map = background(screen, "starmaze.bmp");
# update(map, screen, window);
# # circle(screen, map, width/2, height/2, 100);
# events = sdl_getevents();
# # while sdl_events(events, window) == 1    
while true
    # update(map, screen, window)        
    render(renderer, texture)
end
# # quit()
toc();