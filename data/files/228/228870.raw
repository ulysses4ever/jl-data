module travelling_salesman

  export simulated_annealing, cost

    #tuple de dictionnaires
  villes =  (["name" => "Paris", "lat" => 48.8575, "lon" => 2.3458],
               ["name" => "Lyon", "lat" => 45.7564, "lon" => 4.8333],
               ["name" => "Marseille", "lat" => 43.2815, "lon" => 5.3751],
               ["name" => "Toulouse", "lat" => 43.6013, "lon" => 1.4375],
               ["name" => "Clermont-Ferrand", "lat" => 45.7824, "lon" => 3.0987],
               ["name" => "Montpellier", "lat" => 43.6067, "lon" => 3.8763],
               ["name" => "Bordeaux", "lat" =>  44.8521, "lon" => -0.5852],
               ["name" => "Poitiers", "lat" => 44.8521, "lon" => -0.585],
               ["name" => "Nantes", "lat" => 47.2238, "lon" => -1.5557],
               ["name" => "Rennes", "lat" => 48.1138, "lon" => -1.6806],
               ["name" => "Caen", "lat" => 49.1832, "lon" => -0.3710],
               ["name" => "Rouen", "lat" => 49.4440, "lon" => 1.0894],
               ["name" => "Lille", "lat" => 50.6310, "lon" => 3.0561],
               ["name" => "Amiens", "lat" => 49.8968, "lon" => 2.2931],
               ["name" => "Reims", "lat" => 49.2542, "lon" => 4.0452],
               ["name" => "Nancy", "lat" => 48.67301, "lon" => 6.17070],
               ["name" => "Strasbourg", "lat" => 48.59759, "lon" => 7.76836],
               ["name" => "Dijon", "lat" => 47.3265, "lon" => 5.0398],
               ["name" => "Besançon", "lat" => 47.2419, "lon" => 6.0221],
               ["name" => "Ajaccio", "lat" => 41.9254, "lon" => 8.7311],
               ["name" => "Limoges", "lat" => 45.8390, "lon" => 1.2539],
               ["name" => "Orléans", "lat" => 47.8886, "lon" => 1.9140])

  global radius = 6378

  function degreesToRad(angle)
    return angle*pi/180.0
  end

  function dist(ville1,ville2)
    #formulae from http://en.wikipedia.org/wiki/Great-circle_distance
    lat1 = degreesToRad(ville1["lat"])
    lat2 = degreesToRad(ville2["lat"])
    lon1 = degreesToRad(ville1["lon"])
    lon2 = degreesToRad(ville2["lon"])

    dx = cos(lon2)*cos(lat2) -cos(lon1)*cos(lat1)
    dy = cos(lon2)*sin(lat2) - cos(lon1)*sin(lat1)
    dz = sin(lat2) - sin(lat1)
    C  = sqrt(dx^2+dy^2+dz^2)
    dsigma = 2*asin(C/2.0)

    return radius*dsigma
  end

  function permute_cities(villes)
    # c'est plus joli en clojure
    len = length(villes)
    pos1 = rand(2:len-1)
    pos2 = rand(2:len-1)
    ville1 = villes[pos1]
    ville2 = villes[pos2]
    if pos1<pos2
      result = villes[1:pos1-1]
      push!(result,ville2)
      append!(result,villes[pos1+1:pos2-1])
      push!(result,ville1)
      append!(result,villes[pos2+1:end])
      return result
    else
      result = villes[1:pos2-1]
      push!(result,ville2)
      append!(result,villes[pos2+1:pos1-1])
      push!(result,ville1)
      append!(result,villes[pos1+1:end])
      return result
    end
  end

  function permute_neighbour_cities(villes)
    len = length(villes)
    pos1 = rand(2:len-1)
    pos2 = rand(2:len-1)
    if pos1 < pos2 && pos1 > 2
      #permute avec la ville de gauche de pos1
      result = villes[1:pos1-2]
      push!(result,villes[pos1])
      push!(result,villes[pos1-1])
      append!(result,villes[pos1+1:end])
      return result
    elseif pos1 > pos2 && pos1<(len-1)
      #permute avec la ville de droite de pos1
      result = villes[1:pos1-1]
      push!(result,villes[pos1+1])
      push!(result,villes[pos1])
      append!(result,villes[pos1+2:end])
      return result
    else
      permute_neighbour_cities(villes)
    end
  end

  function perturb_cities(cities,iteration)
    if iteration%2!=0
      return permute_neighbour_cities(cities)
    else
      return permute_cities(cities)
    end
  end


  function nameToVille(nom,cities=villes)
    if cities[1]["name"]==nom
      return cities[1]
    else
      return nameToVille(nom,cities[2:end])
    end
  end

  function cost(listVilles)
    total = 0.0
    for i=2:length(listVilles)
      depart = nameToVille(listVilles[i-1])
      arrivée = nameToVille(listVilles[i])
      total += dist(depart,arrivée)
    end
    return total
  end

  function accept(nouveau,ancien,temperature)
    oldcost = cost(ancien)
    newcost = cost(nouveau)
    test = reverse(nouveau[2:end-1]) == ancien[2:end-1]
    if !test
      if newcost < oldcost || rand() < exp((oldcost-newcost)/temperature)
        return true
      else
        return false
      end
    else
      return false
    end
  end

  function set_temperature(iteration,init_temp,max_iter,speed)
    return init_temp*exp(-iteration/(max_iter*(1-speed)))
  end

  function simulated_annealing(cities, init_temp, cooling_speed,max_iteration)
    println(init_temp," ",cooling_speed," ",max_iteration)
    #(spit "optimization-results.csv" "iteration;temperature;cost;result\n")
    x = 0
    ancien = cities
    nouveau = cities
    temperature = init_temp
    cout = Float64[]
    while (x <= max_iteration && temperature >= 1)
      push!(cout,cost(ancien))
      x += 1
      nouveau = perturb_cities(ancien, x)
      if accept(nouveau,ancien,temperature)
        ancien = nouveau
        x += 1
        temperature = set_temperature(x,init_temp,max_iteration,cooling_speed)
      else
        x += 1
        temperature = set_temperature(x,init_temp,max_iteration,cooling_speed)
      end
    end
    return ancien, cout
  end

end #module
