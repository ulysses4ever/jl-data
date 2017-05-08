

function makeFiles(dx, dt, T, BWP, disc, a)
	ts = convert(Integer,datetime2unix(now()));
	filepath 	= "resultaten/$ts"
	filepathSVG = "resultaten/svg/$ts"
	i = 1
	while isfile("$filepath.txt")
		i += 1
		filepath	= "resultaten/$ts_$i"
		filepathSVG = "resultaten/svg/$ts_$i"
	end
	println("Bestandsnaam: $filepath.txt")
	
	f = open("$filepath.txt", "w")
	write(f, "Date:   $(now())\n\n");
	write(f, "dx:     $dx\n");
	write(f, "dt:     $dt\n");
	write(f, "T:      $T\n");
	write(f, "disc:   $(disc.toString)\n");
	write(f, "alpha:  $a\n");
	write(f, "chi:    $(BWP.chi)\n");
	write(f, "gamma:  $(BWP.gamma)\n");
	close(f);
	
	savefig("$filepath.png");
	savefig("$filepathSVG.svg");
end

function RS_save(result::ResultSet)
	ts = convert(Integer,datetime2unix(now()));
	filename = "$ts";
	RS_save(result, filename);
end

function RS_save(result::ResultSet, filename::String)
	filepath 	= "resultaten/$filename"
	filepathSVG = "resultaten/svg/$filename"
	i = 1
	while isfile("$filepath.txt")
		i += 1
		filepath	= "resultaten/$(filename)_$i"
		filepathSVG = "resultaten/svg/$(filename)_$i"
	end
	println("Bestandsnaam: $filepath.txt")
	
	f = open("$filepath.txt", "w")
	write(f, JSON.json(result));
	close(f);
	
	nothing
end

function RS_open(filename::String)
	filepath 	= "resultaten/$filename.txt"
	
	convert(ResultSet, JSON.parsefile(filepath));
end