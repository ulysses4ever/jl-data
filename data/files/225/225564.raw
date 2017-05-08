module XCB

include("../deps/deps.jl")
include("include_h.jl")

#this should work at least

# #include <unistd.h>      /* pause() */

# #include <xcb/xcb.h>

# int
# main ()
# {
#   xcb_connection_t *c;
#   xcb_screen_t     *screen;
#   xcb_window_t      win;

#   /* Open the connection to the X server */
#   c = xcb_connect (NULL, NULL);

#   /* Get the first screen */
#   screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;

#   /* Ask for our window's Id */
#   win = xcb_generate_id(c);

#   /* Create the window */
#   xcb_create_window (c,                             /* Connection          */
#                      XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
#                      win,                           /* window Id           */
#                      screen->root,                  /* parent window       */
#                      0, 0,                          /* x, y                */
#                      150, 150,                      /* width, height       */
#                      10,                            /* border_width        */
#                      XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
#                      screen->root_visual,           /* visual              */
#                      0, NULL);                      /* masks, not used yet */

#   /* Map the window on the screen */
#   xcb_map_window (c, win);

#   /* Make sure commands are sent before we pause, so window is shown */
#   xcb_flush (c);

#   pause ();    /* hold client until Ctrl-C */

#   return 0;
# }

# ...so

function connect(displayname::String,screenp::Int32)
	c = ccall((:xcb_connect, _jl_libxcb), Ptr{Void},
                (Ptr{Uint8},Ptr{Int32}), bytestring(displayname), &screenp)
    xcb_connection_t(c)
end

function get_setup(c::xcb_connection_t)
	ccall((:xcb_get_setup, _jl_libxcb), xcb_setup_t,
                (xcb_connection_t,), c)
end

function setup_roots_iterator(s::xcb_setup_t)
	ccall((:xcb_setup_roots_iterator, _jl_libxcb), xcb_screen_iterator_t,
                (xcb_setup_t,), s)
end

function generate_id(c::xcb_connection_t)
	ccall((:xcb_generate_id, _jl_libxcb), Uint32,
                (xcb_connection_t,), c)
end

# xcb_void_cookie_t
# xcb_create_window (xcb_connection_t *c  /**< */,
#                    uint8_t           depth  /**< */,
#                    xcb_window_t      wid  /**< */,
#                    xcb_window_t      parent  /**< */,
#                    int16_t           x  /**< */,
#                    int16_t           y  /**< */,
#                    uint16_t          width  /**< */,
#                    uint16_t          height  /**< */,
#                    uint16_t          border_width  /**< */,
#                    uint16_t          _class  /**< */,
#                    xcb_visualid_t    visual  /**< */,
#                    uint32_t          value_mask  /**< */,
#                    const uint32_t   *value_list  /**< */);


function create_window (c::xcb_connection_t,
                   depth::uint8_t,      
                   wid::xcb_window_t,   
                   parent::xcb_window_t,   
                   x::int16_t,         
                   y::int16_t,         
                   width::uint16_t,    
                   height::uint16_t,    
                   border_width::uint16_t,  
                   _class::uint16_t,        
                   visual::xcb_visualid_t,  
                   value_mask::uint32_t,    
                   value_list::Ptr{Uint32})
	ccall((:xcb_create_window, _jl_libxcb), Void,
		(Uint8,xcb_window_t,xcb_window_t,Int16,Int16,Uint16,Uint16,Uint16,Uint16,
			xcb_visualid_t,Uint32,Ptr{Uint32}), c,depth,wid,parent,x,y,width,height,border_width,
		_class,visual,value_mask,value_list)
	nothing
	end

function test0()
	a = Int32(0)
	c = connect("0:0",a)
	s = setup_roots_iterator(get_setup(c))
	sc = s.data
	i = generate_id(c)
	create_window(c,0L,i,)
end






end # module

