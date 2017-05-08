module XCB

include("../deps/deps.jl")
include("include_h.jl")
include("include_manual.jl")

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

function connect()
  c = ccall((:xcb_connect, _jl_libxcb), Ptr{Void},
                (Ptr{Uint8},Ptr{Int32}), C_NULL, C_NULL)
    xcb_connection_t(c)
end

function get_setup(c::xcb_connection_t)
	ccall((:xcb_get_setup, _jl_libxcb), Ptr{xcb_setup_t},
                (xcb_connection_t,), c)
end

function setup_roots_iterator(s::Ptr{xcb_setup_t})
	s1 = ccall((:xcb_setup_roots_iterator, _jl_libxcb), xcb_screen_iterator_t,
                (Ptr{xcb_setup_t},), s)
  xcb_screen_iterator_t(s1)
end

function generate_id(c::xcb_connection_t)
	ccall((:xcb_generate_id, _jl_libxcb), xcb_window_t,
                (xcb_connection_t,), c)
end

function map_window(c::xcb_connection_t,w::xcb_window_t)
  ccall((:xcb_map_window, _jl_libxcb), Void,
                (xcb_connection_t, xcb_window_t), c, w)
  nothing
end

function flush(c::xcb_connection_t)
  ccall((:xcb_flush, _jl_libxcb), Void,
                (xcb_connection_t,), c)
  nothing
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
                   _class::uint32_t,        
                   visual::xcb_visualid_t,  
                   value_mask::uint32_t,    
                   value_list::Ptr{Void})
	ccall((:xcb_create_window, _jl_libxcb), Void,
		(xcb_connection_t, Uint8, xcb_window_t, xcb_window_t, Int16, Int16,
      Uint16, Uint16, Uint16, Uint32,
			xcb_visualid_t, Uint32, Ptr{Void}), c,depth,wid,parent,x,y,width,height,border_width,
		_class,visual,value_mask,value_list)
	nothing
	end



function test0()
	
	c = connect()
  
    s0 = get_setup(c)
  
	s = setup_roots_iterator(s0)
  
	screen = unsafe_load(s.data)
  
	win = generate_id(c)
  
    a = Uint32(0)
    create_window(c,
        XCB_COPY_FROM_PARENT,win,screen.root,
        Int16(0),Int16(0),UInt16(150),UInt16(150),UInt16(10),
        XCB_WINDOW_CLASS_INPUT_OUTPUT,screen.root_visual,Uint32(0),pointer_from_objref(a))
  
  
    map_window(c,win)

    flush(c)
    c,screen,win
end

function screen_allowed_depths_iterator(screen::xcb_screen_t)
    ccall((:xcb_screen_allowed_depths_iterator, _jl_libxcb), xcb_depth_iterator_t,
                (xcb_screen_t,), screen)
end

function depth_next(d::xcb_depth_iterator_t)
    ccall((:xcb_depth_next, _jl_libxcb), Void,
                (Ptr{xcb_depth_iterator_t},), &d)
end


function get_visual(c::xcb_connection_t,screen::xcb_screen_t)

    depth_iter = screen_allowed_depths_iterator(screen)
    
end
#  To get the xcb_visualtype_t structure, it's a bit less easy. You have to get the xcb_screen_t structure that you want, get its root_visual member, then iterate over the xcb_depth_ts and the xcb_visualtype_ts, and compare the xcb_visualid_t of these xcb_visualtype_ts: with root_visual:

# xcb_connection_t *c;
# xcb_screen_t     *screen;
# int               screen_nbr;
# xcb_visualid_t    root_visual = { 0 };
# xcb_visualtype_t  *visual_type = NULL;    /* the returned visual type */

# /* you init the connection and screen_nbr */

# screen = screen_of_display (c, screen_nbr);
# if (screen) {
#   xcb_depth_iterator_t depth_iter;

#   depth_iter = xcb_screen_allowed_depths_iterator (screen);
#   for (; depth_iter.rem; xcb_depth_next (&depth_iter)) {
#     xcb_visualtype_iterator_t visual_iter;

#     visual_iter = xcb_depth_visuals_iterator (depth_iter.data);
#     for (; visual_iter.rem; xcb_visualtype_next (&visual_iter)) {
#       if (screen->root_visual == visual_iter.data->visual_id) {
#         visual_type = visual_iter.data;
#         break;
#       }
#     }
#   }
# }

# /* visual_type contains now the visual structure, or a NULL visual structure if no screen is found */





end # module

