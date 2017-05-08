# cairo interface (cairo_xcb_x)

import Cairo

# cairo_surface_t *
# cairo_xcb_surface_create (xcb_connection_t *connection,
#                           xcb_drawable_t drawable,
#                           xcb_visualtype_t *visual,
#                           int width,
#                           int height);

function cairo_xcb_surface_create(connection::xcb_connection_t, drawable::xcb_drawable_t,
	visual::xcb_visualtype_t,width::Int32,height::Int32)

    ptr = ccall((:cairo_xcb_surface_create,Cairo._jl_libcairo), Ptr{Void},
                (Ptr{xcb_connection_t}, xcb_drawable_t, Ptr{xcb_visualtype_t}, Int32, Int32),
                &connection, drawable, &visual, width, height)
    Cairo.CairoSurface(ptr, width, height)
end