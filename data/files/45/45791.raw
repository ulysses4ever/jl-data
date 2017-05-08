# ----------------------------------------------------------------------------------------------
function imCreateButtonImages()
	new_bits = Uint8[
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
		,3,2,2,1,3,2,2,1,2,2,2,2,2,2,2,2
		,1,3,2,1,4,2,1,3,2,2,2,2,2,2,2,2
		,2,1,3,1,3,1,3,0,0,0,0,0,0,0,0,2
		,2,3,1,3,4,1,1,1,1,4,4,4,4,4,0,2
		,1,1,1,4,3,3,4,4,4,4,4,4,4,4,0,2
		,2,2,4,1,4,4,1,4,4,4,4,4,4,4,0,2
		,1,2,2,1,3,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,1,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,4,4,4,4,4,4,4,4,4,4,0,2
		,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2
	]

	new_colors = [                                      
		"0 0 0",
		"132 132 132",
		"BGCOLOR",
		"255 255 0",
		"255 255 255",
		""
	]

	open_bits = Uint8[
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,
		1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
		1,0,1,3,1,0,0,0,0,0,0,0,1,1,1,1,
		1,0,3,1,3,1,3,1,3,1,3,0,1,1,1,1,
		1,0,1,3,1,3,1,3,1,3,1,0,1,1,1,1,
		1,0,3,1,3,1,0,0,0,0,0,0,0,0,0,0,
		1,0,1,3,1,0,2,2,2,2,2,2,2,2,2,0,
		1,0,3,1,0,2,2,2,2,2,2,2,2,2,0,1,
		1,0,1,0,2,2,2,2,2,2,2,2,2,0,1,1,
		1,0,0,2,2,2,2,2,2,2,2,2,0,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	]

	open_colors = [
		"0 0 0",
		"BGCOLOR",
		"128 128 0",
		"255 255 0",
		""
	]

	line_bits = Uint8[
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,
		1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,
		1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,
		1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,
		1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,
		1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,
		1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,
		1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	]

	CreateButtonImage(16,16, new_bits, new_colors, "imImgWinNewButton");
	CreateButtonImage(16,16, open_bits, open_colors, "imImgWinOpenButton");
	CreateButtonImage(16,16, line_bits, open_colors, "imImgWinLineButton");
end

# ----------------------------------------------------------------------------------------------
function CreateButtonImage(w::Int, h::Int, bits, colors, name::String)
	global total_images, images

	color_str = ["0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"]
	i = 1

	iup_image = IupImage(w, h, bits)
	IupSetHandle(name, iup_image)

	while (colors[i] != "")
		if (i > 16)
			aux_color_str = @sprintf("%d", i)
			IupStoreAttribute(iup_image, aux_color_str, colors[i]); 
		else
			IupStoreAttribute(iup_image, color_str[i], colors[i]); 
		end
		i += 1
	end

end

# ---------------------------------------------------------------------------------------------
function CreateMainMenu()

	# Creates items of menu File
	item_new   = IupItem ("New","");
	item_open  = IupItem ("Open Grid/Image", "");
	item_close = IupItem ("Close", "");
	item_exit  = IupItem ("Exit", "item_exit_act");

	# Creates items of menu Image
	item_copy  = IupItem ("Copy", "");
	item_paste = IupItem ("Paste", "")

	# Creates items for menu triangle
	item_scalenus = IupItem ("Scalenus","")
	item_isoceles = IupItem ("Isoceles", "")
	item_equilateral = IupItem ("Equilateral", "")

	# Create menu triangle
	menu_triangle = IupMenu(item_equilateral, item_isoceles, item_scalenus)

	# Creates submenu triangle
	submenu_triangle = IupSubmenu("Triangle", menu_triangle)

	# Creates items for menu create
	item_line = IupItem ("Line", "")
	item_circle = IupItem ("Circle", "")

	# Creates menu create
	menu_create = IupMenu(item_line, item_circle, submenu_triangle)

	# Creates submenu create
	submenu_create = IupSubmenu ("Create", menu_create)

	# Creates items of menu help
	item_help = IupItem ("Help", "item_help_act")
  
	# Creates menus
	menu_file  = IupMenu (item_new, item_open, item_close, IupSeparator(), item_exit)
	menu_image = IupMenu (item_copy, item_paste, IupSeparator(), submenu_create)
	menu_tools = IupMenu (IupItem("Tools",""))
	menu_help  = IupMenu (item_help);

	# Creates submenus
	submenu_file  = IupSubmenu ("File", menu_file)
	submenu_image = IupSubmenu ("Image", menu_image)
	submenu_tools = IupSubmenu ("Tools", menu_tools)
	submenu_help  = IupSubmenu ("Help", menu_help)

	# The menu Draw and its descendents
	menu_draw = IupMenu(IupItem("Draw",""))
	submenu_draw = IupSubmenu ("Draw", menu_draw)

	# The menu Geography and its descendents
	menu_geog = IupMenu(IupItem("Plot-coastline",""))
	submenu_geog = IupSubmenu ("Geography", menu_geog)

	# The menu Plates and its descendents
	menu_plates = IupMenu(IupItem("Plate calculator",""))
	submenu_plates = IupSubmenu ("Plates", menu_plates)

	# The menu Mag/Grav and its descendents
	menu_mag = IupMenu(IupItem("IGRF calculator",""))
	submenu_mag = IupSubmenu ("Mag/Grav", menu_mag)

	# The menu Seismology and its descendents
	menu_seismic = IupMenu(IupItem("Seismicity",""))
	submenu_seismic = IupSubmenu ("Seismology", menu_seismic)

	# The menu Tsunamis and its descendents
	menu_tsu = IupMenu(IupItem("Tsunami Travel Time",""))
	submenu_tsu = IupSubmenu("Tsunamis", menu_tsu)

	# The menu GMT and its descendents
	menu_gmt = IupMenu(IupItem("grdfilter",""))
	submenu_gmt = IupSubmenu("GMT", menu_gmt)

	# The menu Grid Tools and its descendents
	menu_grdtool = IupMenu(IupItem("grid calculator",""))
	submenu_grdtool = IupSubmenu("Grid Tools", menu_grdtool)

	# The menu Projections and its descendents
	menu_proj = IupMenu(IupItem("None",""))
	submenu_proj = IupSubmenu("Projections", menu_proj)

	# Creates main menu with file menu
	mainMenu = IupMenu(submenu_file, submenu_image, submenu_tools, submenu_draw, submenu_geog, submenu_plates,
	                   submenu_mag, submenu_seismic, submenu_tsu, submenu_gmt, submenu_grdtool, submenu_proj,
	                   submenu_help)

	return mainMenu
end
