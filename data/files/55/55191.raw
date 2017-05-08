module SDL
    libtest = dlopen(string(pwd(),"/libtest.so"))    
    function sdl_init(flags::Uint32)
      ccall( dlsym(libtest, :init), Int32, (Uint32,), 0x00000020)
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
    function sdl_events()
        return ccall( dlsym(libtest, :sdl_events), Void, ());
    end
    function setpixel(map::Ptr{Void}, x, y, r, g, b)
      ccall( dlsym(libtest, :setpixel), Int32, (Ptr{Void}, Int32, Int32, Uint8, Uint8, Uint8), map, x, y, r, g, b);
    end
    function update(src::Ptr{Void}, dst::Ptr{Void}, w, h)
      ccall( dlsym(libtest, :update), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32), src, dst, w, h);
    end
    function setColor(src::Ptr{Void}, r, g, b)
        ccall( dlsym(libtest, :setfullcolor), Void, (Ptr{Void}, Uint8, Uint8, Uint8), src, r, g, b)
    end
    function background(screen, path)
        ccall( dlsym(libtest, :background), Void, (Ptr{Void}, Ptr{Uint8}), screen, path)
    end
    function blitmap(map, screen, w, h)
      for i = 40:w-1
        for j = 30:50
          setpixel(map, i, j, 200, 220, 0)            
        end
      end  
      update(map, screen, w, h)
    end    
    export sdl_init, quit, sdl_setvideomode, sdl_creatergbsurface, setpixel, update, setColor, blitmap, 
            background, sdl_events
end

tic();
using SDL


width = 1000
height = 1000



sdl_init(0x00000020)
screen = sdl_setvideomode(width, height)
background(screen, "starmaze.pbm")

# map = sdl_creatergbsurface(width, height)
# blitmap(map, screen, width, height)
# while sdl_events() == 1
#     println("h")
# end
# quit()
toc();