function scaleto8(G)
	# Read a grid with GMT and return an image object of it scaled to [1 255]
	add_off = 1;
	range = 254. / (G.hdr[6] - G.hdr[5])
	img = zeros(UInt8,  G.n_rows, G.n_columns)
	GMT_grid_flip_vertical(convert(Ptr{Void}, pointer(G.z)), G.n_columns, G.n_rows, 0, sizeof(G.z[1]))
	for (k = 1:G.n_columns * G.n_rows)
		img[k] = round(UInt8, (((G.z[k] - G.hdr[5]) * range) + add_off))
	end

	P = gmt("makecpt -T0/255/1")
	nColors = size(P.colormap,1)
	cm = zeros(UInt32, nColors, 3)
	for (k = 1:nColors*3)
		cm[k] = round(UInt32, P.colormap[k]*255)
	end
	pal = zeros(UInt32, nColors)
	for (k = 1:nColors)
		pal[k] =  (UInt32(0) << 24) | (UInt32(cm[k]) << 16) | (UInt32(cm[k+nColors]) << 8) | UInt32(cm[k+2*nColors])
	end
	pPalette = pointer(pal)

	n = G.n_columns * G.n_rows
	data = pointer([pointer(img)])
	im = imImage(G.n_columns, G.n_rows, IM_MAP, 0, 0, 1, G.n_columns, n,
	             n, n, data, pPalette, nColors, C_NULL)
	image = pointer([im])

	return image
end