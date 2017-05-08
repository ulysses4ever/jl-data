module mirone_

export
	mirone

using IUP
using IUP_IM
using IUP_CD
using GMT

const NEWPOINT = 0
const MOVE = 1
const CLOSE = 2
const CENTER = 3
const REPAINT = 4

type LineSegPix
	x1::Cint
	x2::Cint
	y1::Cint
	y2::Cint
	active::Bool
end
#function LineSegPix(x1, x2, y1, y2, active)
#	x1 = 0; x2 = 0; y1 = 0; y2 = 0; active = false
#end 

include("draw_poly.jl")
include("mirone_uis.jl")
include("scaleto8.jl")

global poly_lastwhat = CLOSE

# ----------------------------------------------------------------------------------
function mirone()
	IupOpen()	#Initializes IUP

	imCreateButtonImages()

 	mainMenu = CreateMainMenu()

	# Associates handle "mainMenu" with mainMenu
	IupSetHandle("mainMenu", mainMenu)

	btNew = IupButton("", "imImgWinNew" )
	IupSetAttribute(btNew,"TIP","Creates a new image.");
	IupSetAttribute(btNew,"IMAGE","imImgWinNewButton");

	btOpen = IupButton("", "imImgWinOpen" )
	IupSetAttribute(btOpen,"TIP","Loads an image file from disk.")
	IupSetAttribute(btOpen,"IMAGE","imImgWinOpenButton")

	btLine = IupButton("", "imImgWinLine" )
	IupSetAttribute(btLine,"TIP","Draw line.")
	IupSetAttribute(btLine,"IMAGE","imImgWinLineButton")

	btCloseAll = IupButton("", "imImgWinCloseAll" );
	IupSetAttribute(btCloseAll,"TIP","Close all windows.");
	IupSetAttribute(btCloseAll,"IMAGE","imImgWinCloseAllButton");
	IupSetAttribute(btCloseAll, "ACTIVE", "NO");

	hbToolBar = IupHbox(
		IupSetAttributes(IupFill(),"SIZE=5, EXPAND=NO"),	# Blank space before first icon
		btNew,
		btOpen,
		btLine,
		IupSetAttributes(IupFill(),"SIZE=5, EXPAND=NO"),
		#IupSetAttributes(IupFill(),"EXPAND=YES"),
		IupSetAttributes(IupFill(),"SIZE=5, EXPAND=NO")
	)
	IupSetAttribute(hbToolBar, "btCloseAll", btCloseAll);
	IupSetAttribute(hbToolBar, "FLAT", "YES");

	cnvStatus = IupCanvas();
	IupSetAttribute(cnvStatus, "EXPAND", "HORIZONTAL");
	IupSetAttribute(cnvStatus, "RASTERSIZE", "1x25");
	IupSetAttribute(cnvStatus, "BORDER", "YES");

	iup_canvas = blabla()

	vbMainDesktop = IupVbox(
		IupSetAttributes(IupFill(),"SIZE=2, EXPAND=NO"),
		hbToolBar,
		IupSetAttributes(IupFill(),"SIZE=4, EXPAND=NO"),
		IupHbox(iup_canvas),
		IupSetAttributes(IupFill(),"SIZE=4, EXPAND=NO"),
		cnvStatus,
		IupSetAttributes(IupFill(),"SIZE=2, EXPAND=NO")
	)

	# Creates a dialog
	main_window = IupDialog(vbMainDesktop)

	handles = Handles(C_NULL, C_NULL, C_NULL)
	handles.figure1 = main_window
	handles.iup_canvas = iup_canvas
	guidata(main_window, handles)

	IupSetAttribute(main_window, "MENU","mainMenu")
	#IupSetAttribute(main_window, "CLOSE_CB","imImgWinMainExit");
	#IupSetAttribute(main_window, "DROPFILES_CB","imImgWinDropFile");
	#IupSetAttribute(main_window, "GETFOCUS_CB", "imImgWinGetFocus");

	IupSetAttribute(main_window,"MainToolBar", hbToolBar);

	#IupSetAttribute(main_window,"PLACEMENT", "MAXIMIZED");
	IupSetAttribute(main_window,"BRINGFRONT", "YES");
	IupSetAttribute(main_window, "K_cN","imImgWinWindowNext");
	IupSetAttribute(main_window, "K_cO","imImgWinOpen");

	# Sets title and size of the dialog and associates a menu to it
	IupSetAttributes(main_window, "TITLE=\"Mirone toy\", RASTERSIZE = 730x91, MENU = mainMenu");

	# associa os callbacks
	setcallbacks(handles)

	IupShowXY(main_window, IUP_CENTER, IUP_TOP) # Displays the dialog (at screen center)
	IupMainLoop()                               # Initializes IUP main loop
	IupClose()                                  # And close it when ready

end

# ---------------------------------------------------------------------------------------------
function blabla()
	iup_canvas = IupCanvas()
	IupSetAttribute(iup_canvas, "BORDER", "NO");
	IupSetCallback(iup_canvas, "ACTION", cfunction(cbCanvasRepaint, Int, (Ptr{Ihandle},)))
	IupSetCallback(iup_canvas, "MAP_CB", cfunction(cbCanvasMap, Int, (Ptr{Ihandle},)))
	return iup_canvas
end

# --------------------------------------------------------------------------------
function cbCanvasMap(iup_canvas::Ptr{Ihandle})
	handles = guidata(iup_canvas)
	cd_canvas = cdCreateCanvas(cdContextIup(), iup_canvas)
	#cd_canvas = cdCreateCanvas(cdContextDBuffer(), iup_canvas)
	IupSetAttribute(IupGetDialog(iup_canvas), "cdCanvas", cd_canvas)
	IupSetAttribute(iup_canvas, "cdCanvas", cd_canvas)			# Redundant with handles
	handles.cd_canvas = cd_canvas
	guidata(handles.figure1, handles)
	return IUP_DEFAULT
end

# ---------------------------------------------------------------------------------------------
function setcallbacks(handles::Handles)
	IupSetFunction("imImgWinOpen",  cfunction(cmOpen, Int, (Ptr{Ihandle},)))
	IupSetFunction("imImgWinLine",  cfunction(cmdDrawPoly, Int, (Ptr{Ihandle},)))

	#IupSetFunction("cmdRepaint", (Icallback) fRepaint);
	WindowButtonDownFcn(handles.iup_canvas, fButtonCB)
	WindowButtonMotionFcn(handles.iup_canvas, fMotionCB)
	#IupSetFunction("cmdResizeCB", (Icallback) fResizeCB);
end

# ---------------------------------------------------------------------------------------------
function cmOpen(iup_canvas::Ptr{Ihandle})
	# Retrieve a file name
	FileName = "*.*" * repeat(" ",253)	# File name will be returned in this variable, hence its size.
	if (IupGetFile(FileName) != 0)
		return IUP_DEFAULT
	end

	ShowImage(FileName, IupGetDialog(iup_canvas))
	return IUP_DEFAULT
end

# --------------------------------------------------------------------------------
function ShowGrid(FileName::String, iup_dialog::Ptr{Ihandle})
	# ...
	imgGrd = IupGetAttribute(iup_dialog, "imImage")		# typeof(imImage) => Ptr{Uint8}
	imgGrd = convert(Ptr{imImage}, imgGrd)		# If I use Ptr{imImage} it Booms???
	if (imgGrd != C_NULL)
		imImageDestroy(imgGrd)
	end
	IupSetAttribute(iup_dialog, "imImage")

	G   = load_grd_with_gmt(FileName)
	img = scaleto8(G)

	handles = guidata(iup_dialog)
	IupSetAttribute(handles.figure1, "CLIENTSIZE", @sprintf("%dx%d", max(G.n_columns,730), G.n_rows+72))
	IupRefresh(handles.figure1)

	IupSetAttribute(iup_dialog, "imImage", imgGrd);
	cbCanvasRepaint(iup_dialog)   # we can do this because canvas inherit attributes from the dialog */
	IupShow(iup_dialog)
end

# --------------------------------------------------------------------------------
function ShowImage(FileName::String, iup_dialog::Ptr{Ihandle})
	image = IupGetAttribute(iup_dialog, "imImage")		# typeof(image) => Ptr{Uint8}
	image = convert(Ptr{imImage}, image)		# If I use Ptr{imImage} it Booms???
	if (image != C_NULL)
		imImageDestroy(image)
	end
	IupSetAttribute(iup_dialog, "imImage")

#=
	error = pointer([0])
	image = imFileImageLoadBitmap(FileName, 0, error)
	error = unsafe_load(error)
	if (error != 0)	PrintError(error)	end
	if (image == C_NULL) return end
=#
	image = load_grd_with_gmt(FileName)
	img   = unsafe_load(image)		# Need to get access to the composite type, not to its pointer

	handles = guidata(iup_dialog)
	IupSetAttribute(handles.figure1, "CLIENTSIZE", @sprintf("%dx%d", max(img.width,730), img.height+72))
	IupRefresh(handles.figure1)
#@show(bytestring(IupGetAttribute(handles.figure1, "RASTERSIZE")))

	IupSetAttribute(iup_dialog, "imImage", image);
	cbCanvasRepaint(iup_dialog)   # we can do this because canvas inherit attributes from the dialog */
	IupShow(iup_dialog)
end

# --------------------------------------------------------------------------------
function load_img_with_gmt(FileName::String)
	# Load an image with GDAL but via GMT
	I = gmt("read -Ti " * FileName)
	n = I.n_columns * I.n_rows
	if (I.LayerCount >= 3)
		data = pointer([pointer(I.image[:,:,1]), pointer(I.image[:,:,2]), pointer(I.image[:,:,3])])
		pPalette = C_NULL
	else
		data = pointer([pointer(I.image)])
	end
	color_space = IM_RGB
	if (I.nColors > 1)
		color_space = IM_MAP
		cm = I.colormap
		pal = zeros(UInt32, I.nColors)
		for (k = 1:I.nColors)
			pal[k] =  (UInt32(cm[k*4]) << 24) | (UInt32(cm[k*4-3]) << 16) | (UInt32(cm[k*4-2]) << 8) | UInt32(cm[k*4-1])
		end
		pPalette = pointer(pal)
	end

	im = imImage(I.n_columns, I.n_rows, color_space, 0, 0, I.LayerCount, I.n_columns, n,
	             n*I.LayerCount, n, data, pPalette, I.nColors, C_NULL)
	image = pointer([im])
	return gc_ref(image)
end

# --------------------------------------------------------------------------------
function load_grd_with_gmt(FileName::String)
	# Load a grid with GMT (it may use GDAL)
	G = gmt("read -Tg " * FileName)
	pImg = scaleto8(G)
	return pImg
end


# --------------------------------------------------------------------------------
function cbCanvasRepaint(iup_canvas::Ptr{Ihandle})
	cd_canvas = convert(Ptr{cdCanvas}, IupGetAttribute(iup_canvas, "cdCanvas"))
	if (cd_canvas == C_NULL)
		return IUP_DEFAULT
	end

	cdCanvasActivate(cd_canvas);
	cdCanvasClear(cd_canvas);

	image = convert(Ptr{imImage}, IupGetAttribute(iup_canvas, "imImage"))
	if (image == C_NULL)
		return IUP_DEFAULT
	end

	#handles = guidata(iup_canvas)
	img = unsafe_load(image)		# Need to get access to the composite type, not to its pointer
	x_off = div(730 - img.width, 2)
	imcdCanvasPutImage(cd_canvas, img, x_off, 0, img.width, img.height, 0, 0, 0, 0)

	IupRefresh(iup_canvas)
	cdCanvasFlush(cd_canvas)
	return IUP_DEFAULT
end


end 	# module
