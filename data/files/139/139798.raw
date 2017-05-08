function determinanteEinversa()
	info("I valori dell'inversa ed il determinante sono approssimati")
	dim, min, max = getMat()
	run(`clear`)
	while true
		corniceUp("DETERMINANTE E INVERSA")
		M = rand(min:max, dim, dim)
		writeMat(M, "Matrice")
		detM = det(M)
		if detM != 0 invM = inv(M) end
		tic()
		goOn("per visualizzare il determinante")
		toc()
		writeValue(detM, "Determinante")
		if detM != 0
			goOn("per visualizzare l'inversa")
			#output(invM, "Inversa")
			writeMat(invM, "Inversa")
		else
			println("Non esiste l'inversa")
		end
		goOn("per una nuova matrice")
		run(`clear`)
	end
end

function sistemaLineare()
	info("I valori della soluzione sono approssimati")
	info("Se la matrice non ha vettori linearmente indipendenti la soluzione non viene calcolata")
	dim, min, max = getMat()
	while true
		run(`clear`)
		corniceUp("sistema lineare")
		M = rand(min:max, dim, dim)
		writeMat(M, "Matrice")
		b = rand(min:max, dim, 1)
		writeVect(b, "Coefficienti")
		detM = det(M)
		if detM != 0 sol = \(M, b) end
		tic()
		goOn("per la soluzione")
		toc()
		if detM != 0
			writeVect(sol, "Soluzione")
		else
			println("I vettori non sono linearmente indipendenti")
		end
		goOn("per un nuovo sistema")

	end
end

function prodottoTraMatrici()
	dim, min, max = getMat()
	while true
		run(`clear`)
		corniceUp("prodotto tra matrici")
		A = rand(min:max, rand(1:dim), dim)
		B = rand(min:max, dim, rand(1:dim))
		writeMat(A, "Matrice A")
		writeMat(B, "Matrice B")
		prod = *(A, B)
		tic()
		goOn("per visualizzare il prodotto")
		toc()
		writeMat(prod, "Prodotto")
		goOn("per un nuovo prodotto")
	end
end

function rangoMatrice()
	dim, min, max = getMat()
	while true
		run(`clear`)
		corniceUp("rango della matrice")
		M = rand(min:max, rand(1:dim), rand(1:dim))
		writeMat(M, "Matrice")
		rango = rank(M)
		tic()
		goOn("per visualizzare il rango")
		toc()
		writeValue(rango, "Rango")
		goOn("per una nuova matrice")
	end
end

function sommaSottospazi()
	dim, min, max = getMat()
	while true
		run(`clear`)
		corniceUp("somma tra sottospazi")
		X = rand(min:max, rand(1:dim), dim)
		Y = rand(min:max, rand(1:dim), dim)
		writeMat(X, "Sottospazio X")
		writeMat(Y, "Sottospazio Y")
		dimX = rank(X)
		dimY = rank(Y)
		dimXY = rank([X, Y])
		dimX∩Y = -dimXY + dimX + dimY
		tic()
		goOn("per visualizzare le dimensioni dei due sottospazi")
		toc()
		writeValue(dimX, "Dimensione di X")
		writeValue(dimY, "Dimensione di Y")
		tic()
		goOn("per visualizzare le dimensioni dello spazio somma")
		toc()
		writeValue(dimXY, "Dimensione di X+Y")
		#println("Per la formula di Grassman, la dimensione dell'intersezione è ", -rankXY + rankX + rankY )
		writeValue(dimX∩Y, "Dimensione di X∩Y (formula di Grassmann)")
		if dimX∩Y == 0
			print_with_color(:green, "La somma è diretta")
		else
			print_with_color(:red, "La somma non è diretta")
		end
		print("\n\n")
		goOn("per un nuovo esercizio")
	end
end

function prodottoScalare()
	dim, min, max = getVet()
	while true
		run(`clear`)
		corniceUp("prodotto scalare")
		V = rand(min:max, dim)
		U = rand(min:max, dim)
		writeVect(V, "Vettore V")
		writeVect(U, "Vettore U")
		dotVU = dot(V, U)
		tic()
		goOn("per visualizzare il prodotto scalare")
		toc()
		writeValue(dotVU, "Prodotto scalare")
		goOn("per due nuovi vettori")
	end
end

function prodottoVettore()
	info("Metodo di calcolo del prodotto vettore in R³: http://alan.dma.unipi.it/miei/dispense2/PRODOTTOVETTORE.pdf")
	dim, min, max = getVet()
	while true
		run (`clear`)
		corniceUp("prodotto vettore")
		V = rand(min:max, dim)
		U = rand(min:max, dim)
		writeVect(V, "Vettore V")
		writeVect(U, "Vettore U")
		crossVU = cross(V,U)
		tic()
		goOn("per visualizzare il prodotto vettore")
		toc()
		#output(crossVU, "Prodotto vettore")
		writeVect(crossVU, "Prodotto vettore")
		goOn("per due nuovi vettori")
	end
end

function autovalori()
	warn("Modalità non ancora testata.")
	info("Gli autovalori sono approssimati")
	dim, min, max = getMat()
	while true
		run(`clear`)
		corniceUp("calcolo autovalori")
		M = rand(min:max, dim, dim)
		writeMat(M, "Matrice")
		eigvalsM = eigvals(M)
		tic()
		goOn("per visualizzare gli autovalori")
		toc()
		writeVect(eigvalsM, "Autovalori")
		goOn("per una nuova matrice")
	end
end

### Non funziona
function nucleo()
	warn("Questa funzione non è ancora stata testata")
	info("Le soluzioni sono approssimate")
	dim, min, max = getMat()
	while true
		run(`clear`)
		corniceUp("calcolo nucleo")
		M = rand(min:max, dim, dim)
		writeMat(M, "Matrice")
		kerM = \(M, zeros(dim))
		goOn("per visualizzare il nucleo dell'applicazione")
		output(kerM, "Nucleo")
		goOn("per una nuova matrice")
	end
end

function areaParallelogramma()
	info("Funzione testata solamente in R³")
	dim, min, max = getVet()
	while true
		run(`clear`)
		corniceUp("area di un parallelogramma")
		v1 = rand(min:max, dim)
		v2 = rand(min:max, dim)
		writeVect(v1, "v1")
		writeVect(v2, "v2")
		area = vecnorm(cross(v1, v2))
		tic()
		goOn("per visualizzare l'area del parallelogramma")
		toc()
		writeValue(area, "Area del parallelogramma ")
		goOn("per un nuovo esercizio")
	end
end

function proiezioneSuSottospazio()
	info("Funzione non ancora testata")
	info("Funziona solamente in R³")
	dim, min, max = getVet()
	if dim != 3
		info("Dimensione impostata a 3")
		dim = 3
	end
	while true
		run(`clear`)
		corniceUp("proiezione su di un sottospazio")
		v0 = rand(min:max, dim)
		x0 = rand(min:max, dim)
		X0 = rand(min:max, dim-1, dim)
		#v0 = [1,1,3]
		#x0 = [1,1,2]
		#X0 = [[0 1 1]
		#[1 1 1]]
		writeVect(v0, "Vettore da proiettare")
		writeVect(x0, "x0 del sottospazio affine")
		writeMat(X0, "Sottospazio affine")
		bufferA = squeeze(X0[1,:], 1)
		bufferB = squeeze(X0[2,:], 1)
		pv = cross(bufferA, bufferB)
		trasl = v0 - x0
		pro = ((dot(trasl, pv))/(norm(pv)^2))*pv
		fin = v0 - pro
		tic()
		goOn("per visualizzare la proiezione")
		toc()
		writeVect(pv, "Prodotto vettore")
		writeVect(trasl, "Punto traslato")
		writeVect(pro, "Proiezione sulla traslazione")
		writeVect(fin, "Risultato finale")
		goOn("per un nuovo esercizio")
	end
end
