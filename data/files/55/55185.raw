
module SDL
    import GetC.@getCFun
    include("deps.jl")

    @getCFun libSDL SDL_Init SDL_Init(flags::Uint32)::Int32
    export SDL_Init

    @getCFun libSDL SDL_SetVideoMode SDL_SetVideoMode(width::Int32,height::Int32,
                                                    bpp::Int32,
                                                    flags::Uint32)::Ptr{Void}
    export SDL_SetVideoMode

    @getCFun libSDL SDL_CreateRGBSurface SDL_CreateRGBSurface(flags::Uint32,
                                                              width::Int32,
                                                              height::Int32,
                                                              depth::Int32,
                                                              Rmask::Uint32,
                                                              Gmask::Uint32,
                                                              Bmask::Uint32,
                                                              Amask::Uint32)::Ptr{Void}
    export SDL_CreateRGBSurface

    const SDL_INIT_VIDEO              = 0x00000020
    export SDL_INIT_VIDEO
    const SDL_SWSURFACE               = 0x00000000
    export SDL_SWSURFACE
    const rmask = 0xff000000;
    export rmask    
    const gmask = 0x00ff0000;
    export gmask
    const bmask = 0x0000ff00;
    export bmask
    const amask = 0x000000ff;
    export amask
end


using SDL

width              = 640
height             = 480

SDL_Init(SDL_INIT_VIDEO)
screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
map = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);