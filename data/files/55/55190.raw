tic()

libtest = dlopen("/home/guillaume/fast-sim-julia/libtest.so")

# module SDL
#     import GetC.@getCFun
#     include("deps.jl")

#     @getCFun libSDL SDL_Init SDL_Init(flags::Uint32)::Int32
#     @getCFun libSDL SDL_SetVideoMode SDL_SetVideoMode(width::Int32,height::Int32,
#                                                     bpp::Int32,
#                                                     flags::Uint32)::Ptr{Void}
#     @getCFun libSDL SDL_CreateRGBSurface SDL_CreateRGBSurface(flags::Uint32,
#                                                               width::Int32,
#                                                               height::Int32,
#                                                               depth::Int32,
#                                                               Rmask::Uint32,
#                                                               Gmask::Uint32,
#                                                               Bmask::Uint32,
#                                                               Amask::Uint32)::Ptr{Void}
#     @getCFun libSDL SDL_MapRGB SDL_MapRGB(format::Ptr{Void},
#                                           r::Uint8,
#                                           g::Uint8,
#                                           b::Uint8)::Uint32
#     @getCFun libSDL SDL_BlitSurface SDL_BlitSurface(src::Ptr{Void},
#                                                     srcrect::Int32,
#                                                     dst::Ptr{Void},
#                                                     dstrect::Ptr{Void})::Int32
#     @getCFun libSDL SDL_UpdateRect SDL_UpdateRect(screen::Ptr{Void},
#                                                   x::Uint32,
#                                                   y::Uint32,
#                                                   w::Uint32,
#                                                   h::Uint32)::Ptr{Void}

#     export SDL_Init
#     export SDL_SetVideoMode
#     export SDL_CreateRGBSurface
#     export SDL_MapRGB    
#     export SDL_BlitSurface
#     export SDL_UpdateRect

#     const SDL_INIT_VIDEO = 0x00000020
#     export SDL_INIT_VIDEO
#     const SDL_SWSURFACE = 0x00000000
#     export SDL_SWSURFACE
#     const rmask = 0xff000000;
#     export rmask    
#     const gmask = 0x00ff0000;
#     export gmask
#     const bmask = 0x0000ff00;
#     export bmask
#     const amask = 0x000000ff;
#     export amask
# end

# using StrPack

# type sdl_color
#   r::Uint8;
#   g::Uint8;
#   b::Uint8;
#   unused::Uint8;
# end

# type sdl_palette
#   ncolors::Int32
#   colors::Ptr{sdl_color}
# end

# type sdl_pixelformat
#   palette::Ptr{sdl_palette};
#   BitsPerPixel::Uint8; BytesPerPixel::Uint8; 
#   Rloss::Uint8; Gloss::Uint8; Bloss::Uint8; Aloss::Uint8;
#   Rshift::Uint8; Gshift::Uint8; Bshift::Uint8; Ashift::Uint8;
#   Rmask::Uint32; Gmask::Uint32; Bmask::Uint32; Amask::Uint32;
#   colorkey::Uint32;
#   alpha::Uint8;
# end

# type sdl_rect
#   x::Int16;
#   y::Int16;
#   w::Uint16;
#   h::Uint16;
# end

# type sdl_surface
#     flags::Uint32;
#     format::Ptr{sdl_pixelformat};
#     w::Int32;
#     h::Int32;
#     pitch::Uint16;
#     pixels::Ptr{Void};
#     clip_rect::sdl_rect;
#     refcount::Int32;
# end


function sdl_init(flags::Uint32)
  ccall( dlsym(libtest, :init), Int32, (Uint32,), 0x00000020)
end

function sdl_setvideomode(w, h)
  return ccall( dlsym(libtest, :setvideomode), Ptr{Void}, (Int32, Int32, Int32, Uint32,), w, h, 32, 0x00000000);
end

function sdl_creatergbsurface(w, h)
  return ccall( dlsym(libtest, :creatergbsurface), Ptr{Void}, (Int32, Int32,), w, h);
end

function putpixel(map::Ptr{Void}, x, y, r, g, b)
  ccall( dlsym(libtest, :putpixel), Int32, (Ptr{Void}, Int32, Int32, Uint8, Uint8, Uint8), map, x, y, r, g, b);
end

function update(src::Ptr{Void}, dst::Ptr{Void}, w, h)
  ccall( dlsym(libtest, :update), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32), src, dst, w, h);
end

function blitmap(map, screen, w, h)
  for i = 0:w
    for j = 0:h
      putpixel(map, i, j, 0, 0, 200)            
    end
  end  
  update(map, screen, w, h)  
end




width = 640
height = 480



sdl_init(0x00000020)
screen = sdl_setvideomode(width, height)
map = sdl_creatergbsurface(width, height)

blitmap(map, screen, width, height)

  
toc()