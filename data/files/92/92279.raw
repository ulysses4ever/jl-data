Pkg.add("DataFrames")
Pkg.add("Gadfly")
Pkg.add("Cairo")
Pkg.add("Interact")

Pkg.update()

#Lancer les paquetages utilisés par le script
using DataFrames
using Gadfly
#using Cairo
#using Interact

#Boulot = 1 Maison = 2
#En local
#pc = 1

date = string(Dates.today())

separateur = "\\"

#Oblige à se placer dans le répertoire de base
cd()
pwd()

#Nom de l'emplacement des fichiers CSV
repertoireMesuresRhomboedres = string(pwd(),"\\Documents\\Julia\\Spirou-Rhomboedres")
repertoireResultats = string(repertoireMesuresRhomboedres, separateur, "Resultats")
#Indique l'endroit où chercher les modules
push!(LOAD_PATH, string(pwd(),"\\Documents\\Julia\\HVBiblioJulia"))

#Charge les bibliothèques nécessaires
using BibliothequeHV
using BibliothequeGraphHV

function getListeFichiersDeType(repertoire, extension)
  #liste les fichiers contenus dans le répertoire qui doit contenir des fichiers CSV
  listeDesFichiersDuRepertoire = readdir(repertoire)
  #Recherche les fichiers CSV dans ce répertoire
  #Création d'une fonction qui filtre les fichiers CSV
  function isFichierDuTypeExtension(fichier)
    endswith(fichier, extension)
  end

  #Liste de tous les fichiers CSV du répertoire
  listeDesFichiersDuType = filter(isFichierDuTypeExtension, listeDesFichiersDuRepertoire)
  return(listeDesFichiersDuType)
end

#Liste de tous les fichiers CSV du répertoire
listeDesFichiersMesuresRhomboedres = getListeFichiersDeType(repertoireMesuresRhomboedres, ".csv")

# incFichiers=1
#incFichiers = 2
##Pour tous les fichiers CSV
for incFichiers in 1:length(listeDesFichiersMesuresRhomboedres)

  ##Ouvre le fichier CSV et récupère les noms etc.
  nomDuFichierMesuresRhomboedres = listeDesFichiersMesuresRhomboedres[incFichiers]
  #nomDuFichierSansExtension = split(nomDuFichierMesuresRhomboedres,".csv")[1]
	nomCompletDuFichierMesuresRhomboedres = string(repertoireMesuresRhomboedres, separateur, nomDuFichierMesuresRhomboedres)

  dfManipRhomboedres = readtable(nomCompletDuFichierMesuresRhomboedres, separator = ';', header = true)
  dfManipRhomboedres

  Lambda = dfManipRhomboedres[:Lambda]
  Tour = dfManipRhomboedres[:Tour]
  P1 = dfManipRhomboedres[:P1]
  Rhomb = dfManipRhomboedres[:Rhomb]
  Cell1 = dfManipRhomboedres[:Cell1]
  IncertCell1 = dfManipRhomboedres[:IncertCell1]
  Cell2 = dfManipRhomboedres[:Cell2]
  IncertCell2 = dfManipRhomboedres[:IncertCell2]
  DarkCell1 = dfManipRhomboedres[:DarkCell1]
  DarkIncertCell1 = dfManipRhomboedres[:DarkIncertCell1]
  DarkCell2 = dfManipRhomboedres[:DarkCell2]
  DarkIncertCell2 = dfManipRhomboedres[:DarkIncertCell2]
  PmMoy = dfManipRhomboedres[:PmMoy]
  PmIncert = dfManipRhomboedres[:PmIncert]
  Temps = dfManipRhomboedres[:Temps]
  ErreurP1 = dfManipRhomboedres[:ErreurP1]
  PosDensite = dfManipRhomboedres[:PosDensite]
  NumDensite = dfManipRhomboedres[:NumDensite]

  maxErreurP1 = maximum(ErreurP1)
  moyPmMoy = mean(PmMoy)
  #Calcul du facteur de correction pour tenir compte de la fluctuation de la variation de la lampe
  facteurDeCorrection = moyPmMoy / PmMoy
  #Corrige PmMoy
  PmMoyCorrige = PmMoy .* facteurDeCorrection
  #Tracé des erreurs
  plotErreurP1 = plot(dfManipRhomboedres, x = P1, y = ErreurP1, Geom.point, Guide.XLabel("P1"), Guide.YLabel("ErreurP1"), Guide.title("Tracé des erreurs de positionnement de P1 en fonction de P1"), color = Tour)
  #Tracé du Flux de la Lampe
  Ymin = PmMoy - (PmIncert/2)
  Ymax = PmMoy + (PmIncert/2)
  plotPmMoy = plot(dfManipRhomboedres, x = Temps, y = PmMoy, ymin = Ymin, ymax = Ymax, Geom.point, Geom.errorbar,
                   Guide.XLabel("Temps"), Guide.YLabel("PmMoy Brute"), Guide.title("Tracé de PmMoy"), Theme(default_color=color("purple")))
  #Tracé du Flux de la lampe Corrigé
  Ymin = PmMoyCorrige - (PmIncert/2)
  Ymax = PmMoyCorrige + (PmIncert/2)
  plotPmMoyFinal = plot(dfManipRhomboedres, x = Temps, y = PmMoyCorrige, ymin = Ymin, ymax = Ymax, Geom.point, Geom.errorbar,
                        Guide.title("plotPmMoyCorrigé"), Guide.xlabel("Temps"), Guide.ylabel("Pm Corrigé"), Scale.color_discrete_manual("purple"))

  nomDuFichierMesuresRhomboedresCorrigees = string(repertoireResultats, separateur, nomDuFichierMesuresRhomboedres)
  nomDuFichierSansExtension = split(nomDuFichierMesuresRhomboedresCorrigees,".csv")[1]
  nomDuFichierGraphiquePDF1 = string(nomDuFichierSansExtension,"-ErreursEtLampe.PDF")

  draw(PDF(nomDuFichierGraphiquePDF1, 297mm, 210mm), vstack(plotPmMoy,plotPmMoyFinal,plotErreurP1))

  #Applique la correction sur Cell1 et Cell2 (Pas de correction au Dark)
  Cell1Corrige = ((Cell1 .* facteurDeCorrection)-DarkCell1)
  Cell2Corrige = ((Cell2 .* facteurDeCorrection)-DarkCell2)

  #Calcule de l'incertitude car on soustraie le Dark à Cell1
  IncertCell1Corrige = sqrt(IncertCell1.^2 + DarkIncertCell1.^2)
  IncertCell2Corrige = sqrt(IncertCell2.^2 + DarkIncertCell2.^2)

  #Fabrique le fichier comparaison des bruits qui sera utilisé pour le script graphique de R
  dfMesuresRhomboedresCorriges = DataFrame(Lambda = Float64[], Tour = Int64[], P1 = Float64[],
                                           Cell1Corrige = Float64[], IncertCell1Corrige = Float64[],
                                           Cell2Corrige = Float64[], IncertCell2Corrige = Float64[],
                                           NumDensite = Int64[])
  dfMesuresRhomboedresCorriges

  for incNbLignes in 1:length(Lambda)
    push!(dfMesuresRhomboedresCorriges, [Lambda[incNbLignes] Tour[incNbLignes] P1[incNbLignes] Cell1Corrige[incNbLignes] IncertCell1Corrige[incNbLignes] Cell2Corrige[incNbLignes] IncertCell2Corrige[incNbLignes] NumDensite[incNbLignes]])
  end

  writetable(nomDuFichierMesuresRhomboedresCorrigees, dfMesuresRhomboedresCorriges, quotemark = '\"', separator = ';', header = true)

  #Permet de connaître le nombre de Lambda Différents dans la liste
  listeDesDifferentsLambdas = Float64[]
  #nbDeLambdasDifferents = Int64
  lambdaCourant = 0.0
  for incNbValeurs in 1:length(dfMesuresRhomboedresCorriges[:Lambda])
    if(lambdaCourant != dfMesuresRhomboedresCorriges[:Lambda][incNbValeurs])
      lambdaCourant = dfMesuresRhomboedresCorriges[:Lambda][incNbValeurs]
      push!(listeDesDifferentsLambdas, lambdaCourant)
    end
  end
  listeDesDifferentsLambdas

  listePlotCell1CorrigeParLambda = Gadfly.Plot[]
  listePlotCell2CorrigeParLambda = Gadfly.Plot[]
  listeTitresPrincipaux = ASCIIString[]
  listeDesNomsDeFichiersPDF2 = ASCIIString[]

  #m=2
  for incNbDeLambda in 1:length(listeDesDifferentsLambdas)
    println("lambda = ",listeDesDifferentsLambdas[incNbDeLambda])
    #
    listeLambdaParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :Lambda]
    listeTourParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :Tour]
    listeP1ParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :P1]
    listeCell1CorrigeParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :Cell1Corrige]
    listeIncertCell1CorrigeParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :IncertCell1Corrige]
    listeCell2CorrigeParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :Cell2Corrige]
    listeIncertCell2CorrigeParLambda = dfMesuresRhomboedresCorriges[dfMesuresRhomboedresCorriges[:Lambda] .== listeDesDifferentsLambdas[incNbDeLambda], :IncertCell2Corrige]

    Ymin = listeCell1CorrigeParLambda - (listeIncertCell1CorrigeParLambda/2)
    Ymax = listeCell1CorrigeParLambda + (listeIncertCell1CorrigeParLambda/2)
    plotCell1Corrige = plot(dfMesuresRhomboedresCorriges, x = listeP1ParLambda, y = listeCell1CorrigeParLambda, ymin = Ymin, ymax = Ymax, Geom.point, Geom.errorbar, Guide.XLabel("P1"), Guide.YLabel("Cell1Corrige"), Guide.title("Tracé de Cell1 Corrigé"), Theme(default_color=color("green")))
    push!(listePlotCell1CorrigeParLambda,plotCell1Corrige)

    Ymin = listeCell2CorrigeParLambda - (listeIncertCell2CorrigeParLambda/2)
    Ymax = listeCell2CorrigeParLambda + (listeIncertCell2CorrigeParLambda/2)
    plotCell2Corrige = plot(dfMesuresRhomboedresCorriges, x = listeP1ParLambda, y = listeCell2CorrigeParLambda, ymin = Ymin, ymax = Ymax, Geom.point, Geom.errorbar, Guide.XLabel("P1"), Guide.YLabel("Cell2Corrige"), Guide.title("Tracé de Cell2 Corrigé"), Theme(default_color=color("orange")))
    push!(listePlotCell2CorrigeParLambda,plotCell2Corrige)

      #Titre principal
    titrePrincipal = string(nomDuFichierMesuresRhomboedres,"@",listeDesDifferentsLambdas[incNbDeLambda])
    push!(listeTitresPrincipaux,titrePrincipal)
    nomDuFichierGraphiquePDF2 = string(nomDuFichierSansExtension,"@",listeDesDifferentsLambdas[incNbDeLambda],".PDF")
    push!(listeDesNomsDeFichiersPDF2,nomDuFichierGraphiquePDF2)
    #Dessine un fichier PDF
    draw(PDF(listeDesNomsDeFichiersPDF2[incNbDeLambda], 297mm, 210mm), vstack(listePlotCell1CorrigeParLambda[incNbDeLambda],listePlotCell2CorrigeParLambda[incNbDeLambda]))
  end
end
