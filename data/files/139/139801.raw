function input(prompt::String="")
	print(prompt, ": ")
	int(chomp(readline()))
end

function output(value, indication::String="")
	println(indication, ": ")
	println()
	println(value)
	println()
end

function writeValue(value, label::String="")
	print("$label:  ")
	print_with_color(:green, string(round(value, 3)))
	println("\n")
end

function writeString(cont::String, label::String="")
	print("$cont")
	print_with_color(:green, cont)
	println("\n")
end

function goOn(prompt::String="per proseguire")
	println("Premi INVIO ", prompt)
	readline(STDIN)
end

function writeMat(mat, label::String="")
	rn, cn = size(mat)
	print("\n$label\n\n")
	for r = 1:rn
		for c = 1:cn
			print_with_color(:green, string(round(mat[r,c], 3)))
			print("\t")
		end
		println()
	end
	println()
end

function writeVect(vec, label::String="")
	en = size(vec)
	print("\n$label\n\n")
	for e = 1:en[1]
		print_with_color(:green, string(round(vec[e], 3)))
		println()
	end
	println()
end

function warning(message::String)
	print_with_color(:red, "\nATTENZIONE!\n")
	println(message,"\n")
end

function softwareInfo()
	corniceUp("Algebra Lineare - Gianluca Mondini - 2015")
	info("Versione 0.3")
	warn("Questo software è ancora in fase sperimentale e viene distribuito senza alcuna garanzia")

	@osx? warn("Questo software non è ancora stato testato su OSX\n") : null
	@windows? warn("Questo software non è ancora stato testato su Windows\n") : null
end

function blueBar(n)
	for i = 1:n
		print_with_color(:blue, "-")
	end
end

function getMat()
	dim = input("Dimensione della matrice")
	if dim < 1
		error("La dimensione della matrice deve essere maggiore di 0")
	end
	min = input("Valore minimo degli elem. della matrice")
	max = input("Valore massimo degli elem. della matrice")
	if (max - min) <= 0
		error("Il range di valori degli elementi della matrice deve essere positivo")
	end
	return dim, min, max
end

function getVet()
	dim = input("Dimensione del vettore")
	if dim < 1
		error("La dimensione del vettore deve essere maggiore di 0")
	end
	min = input("Valore minimo degli elem. del vettore")
	max = input("Valore massimo degli elem. del vettore")
	if (max - min) <= 0
		error("Il range di valori degli elementi del vettore deve essere positivo")
	end
	return dim, min, max
end

function corniceUp(prompt::String)
	prompt = uppercase(prompt)
	local w = strwidth(prompt)
	#
	blueBar(2*w)
	println()
	#
	blueBar(w/2)
	print_with_color(:blue, prompt)
	blueBar(w/2)
	println()
	#
	blueBar(2*w)
	println()
end
