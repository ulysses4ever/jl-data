
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

const NEWPOINT = 0
const MOVE = 1
const CLOSE = 2
const CENTER = 3
const REPAINT = 4

global poly_lastwhat = CLOSE

#-------------------------------------------------------------------------
# Desenha o poligono em rubber band.
#-------------------------------------------------------------------------
function polygon(handles::Handles, what::Integer, x::Integer, y::Integer)
	global poly_lastwhat

	line_seg = getappdata(handles.iup_canvas, "lineSeg")
	if (isnada(line_seg) || !line_seg.active) return end

	if (what == NEWPOINT)
		if (poly_lastwhat != CLOSE)
			cdCanvasLine(line_seg.x1, line_seg.y1, line_seg.x2, line_seg.y2);      # ...apaga a anterior e...
			cdCanvasLine(line_seg.x1, line_seg.y1, x, y);        # desenha a definitiva
		end
		line_seg.x1 = x;                        # novo segmento comeca no...
		line_seg.y1 = y;                        # fim do primeiro
	elseif (what == MOVE)
		if (poly_lastwhat == MOVE)
			cdCanvasLine(handles.cd_canvas, line_seg.x1, line_seg.y1, line_seg.x2, line_seg.y2);      # apaga o segmento velho
		end
		cdCanvasLine(handles.cd_canvas, line_seg.x1, line_seg.y1, x, y);     # desenha o novo
		line_seg.x2 = x;                        # e o novo se...
		line_seg.y2 = y;                        # torna velho
	elseif (what == REPAINT)
		cdCanvasLine(handles.cd_canvas, line_seg.x1, line_seg.y1, line_seg.x2, line_seg.y2);        # recupera o segmento perdido
		return                             # nao modifica lastwhat
	elseif (what == CLOSE)
		if (poly_lastwhat != CLOSE)
			cdLine(handles.cd_canvas, line_seg.x1, line_seg.y1, line_seg.x2, line_seg.y2);        # apaga o ultimo segmento
			# apaga o poligono temporario inteiro
			for i = 1:ctgc.num_points-1
				cdCanvasLine(handles.cd_canvas, ctgc.points[i].x, ctgc.points[i].y, ctgc.points[i+1].x, ctgc.points[i+1].y);
			end
		end
	end
	poly_lastwhat = what
	setappdata(handles.iup_canvas, "lineSeg", line_seg)
end

# ---------------------------------------------------------------------------------------------
function cmdDrawPoly(iup_canvas::Ptr{Ihandle})
	handles = guidata(iup_canvas)
	line_seg = LineSegPix(0, 0, 0, 0, true)

	setappdata(handles.iup_canvas, "lineSeg", line_seg)

	cdCanvasBackground(handles.cd_canvas, IUP_CD.CD_WHITE); 
	cdCanvasClear(handles.cd_canvas); 
	cdCanvasLineWidth(handles.cd_canvas, 3); 
	cdCanvasLineStyle(handles.cd_canvas, IUP_CD.CD_CONTINUOUS); 
	cdCanvasForeground(handles.cd_canvas, cdEncodeAlpha(IUP_CD.CD_DARK_MAGENTA, Char(128)))
	cdCanvasWriteMode(handles.cd_canvas, IUP_CD.CD_NOT_XOR)
	cdCanvasActivate(handles.cd_canvas)
	return IUP_DEFAULT
end

# ------------------------------------------------------------------------
function fMotionCB(hand::Ptr{Ihandle}, x::Int32, y::Int32, r::Ptr{UInt8})
	handles = guidata(hand)
	yp = convert(Ptr{Cint}, pointer([y]))
	cdCanvasUpdateYAxis(handles.cd_canvas, yp)
	y = unsafe_load(yp)
#@show(x,y)
	polygon(handles, MOVE, x, y)
	return IUP_DEFAULT
end

#-------------------------------------------------------------------------
# Function associated to the mouse buttons
#-------------------------------------------------------------------------
function fButtonCB(hand::Ptr{Ihandle}, b::Char, e::Integer, x::Integer, y::Integer, r::Ptr{UInt8})
	handles = guidata(hand)

	cdCanvasActivate(handles.cd_canvas)
	#cdCanvasWriteMode(handles.cd_canvas, IUP_CD.CD_NOT_XOR)
	cdCanvasForeground(handles.cd_canvas, convert(Clong, IUP_CD.CD_BLACK))
	cdCanvasLineStyle(handles.cd_canvas, IUP_CD.CD_CONTINUOUS)
	cdCanvasLineWidth(handles.cd_canvas, 1)
	cdCanvasClip(handles.cd_canvas, IUP_CD.CD_CLIPOFF)

	yp = convert(Ptr{Cint}, pointer([y]))
	cdCanvasUpdateYAxis(handles.cd_canvas, yp)
	y = unsafe_load(yp)
	x = Int32(x)

	set_current_point(handles.iup_canvas, [x,y])

	if (b == IUP_BUTTON1)		# Left button
		if (e != 0)				# button was pressed
			line_seg = getappdata(handles.iup_canvas, "lineSeg")
			if (isnada(line_seg)) return IUP_DEFAULT end
			line_seg.x1 = x
			line_seg.y1 = y
			line_seg.active = true
			setappdata(handles.iup_canvas, "lineSeg", line_seg)
		end
	end
	return IUP_DEFAULT
end
