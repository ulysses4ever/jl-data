module senstools
export OSM!, SCM!
#######################################################################
#   Function for performing different types of sensitivity analysis   #
#######################################################################

type SCMdata
  nopars            :: Int
  parameters        :: Array{Float64, 1}
  names             :: Array{String, 1}
  time              :: Array{Float64, 1}
  sensitivities     :: Array{Float64, 2}
  twonorms          :: Array{Float64, 1}
  ordering          :: Array{Int, 1}
  subset            :: Array{Int, 1}
  nochosen          :: Array{Int, 1}
  twonormfactor     :: Array{Float64, 1}
  normval           :: Array{Float64, 1}
  precision         :: Array{Float64, 1}
  correlation_limit :: Array{Float64, 1}
end

type OSMdata
  parameters    :: Array{Float64, 1}
  names         :: Array{String, 1}
  time          :: Array{Float64, 1}
  sensitivities :: Array{Float64, 2}
  E             :: Array{Float64,1}
  subset        :: Array{Int, 1}
  available     :: Array{Int, 1}
  angles        :: Array{Float64, 1}
  I             :: Array{Float64, 1}
  tolerance     :: Float64
end

type Morrisdata
  level         :: Int
  points        :: Int
  no_parameters :: Int
  f             :: Function
  print         :: Bool
  names         :: Array{String, 1}
  mu
  s2
end

type Soboldata
  points        :: Int              # Number of points to use (M)
  no_parameters :: Int              # Number of parameters
  f             :: Function         # Function to be investigated. Must take array of parameters as only input.
  print         :: Bool             # Print results?
  names         :: Array{String, 1} # Names of parameters
  Si                                # Resulting Si values
  STi                               # Resulting STi values
end

function SCM!(
  Data :: SCMdata)

  """ Strucural Correlation Matrix Method from Olufsen et. al REF"""

  run(`figlet -w 800 Structural Correlations`)
  @printf("\n\nSTATUS: Started Structural Correlation investigation.\n")

  SCM_twonorm_order!(
    Data :: SCMdata);

  SCM_select_from_twonorm!(
    Data :: SCMdata);

  
  flag = 1
  while flag > 0
    flag = SCM_max_correlation_reduction!(
      Data :: SCMdata)
  end

  SCM_print_results(
    Data :: SCMdata)

  return int32(0);
end

function SCM_twonorm_order!(
  Data :: SCMdata)

  @printf("STATUS: Calculating norms for sensitivities...\n")
  Data.twonorms[1:Data.nopars]   = float64([norm(Data.sensitivities[:,j],Data.normval[1]) for j in 1:Data.nopars]) :: Array{Float64,1};
  Data.twonorms[1:Data.nopars]  /= maximum(Data.twonorms);
  Data.ordering[1:Data.nopars]   = sortperm(Data.twonorms)[end:-1:1]                                               :: Array{Int,1};

  return int32(0);
end

function SCM_select_from_twonorm!(
  Data :: SCMdata)

  #Data.nochosen[1] = length(Data.subset[Data.twonorms[Data.subset].>(1.0/Data.twonormfactor[1])])
  Data.subset = Data.subset[Data.twonorms[Data.subset].>(1.0/Data.twonormfactor[1])]
  Data.nochosen[1] = length(Data.subset)
  
  return int32(0)
end

function SCM_max_correlation_reduction!(
  Data :: SCMdata;
  condlimit = 1e10)

  @printf("STATUS: Calculating correlations...\n")
  @printf("----------------------------------------------\n")

  subset = Data.subset[1:Data.nochosen[1]]
  STS = Data.sensitivities[:,subset]'*Data.sensitivities[:,subset]

  ###########################################
  #  Check if we can calculate the inverse  #
  ###########################################
  
  c = try inv(STS)
    catch error("STS can not be inverted. Perhaps too many parameters have been chosen,
    or the ones chosen have linearly dependent sensitivities.")
    end

  # The (STS)^-1 * STS shoulde be I. Consdire the difference from the identity matrix.
  I = c*STS-eye(c)

  # If the largest error is larger than the precision we want, return an error.
  if maximum(abs(I)) > Data.precision[1]
    error("Too large imprecission in covariance matrix. Perhaps too many parameters have been chosen,
    or the ones chosen have linearly dependent sensitivities.\n")
  end

  C = zeros(c);

  #C = [c[i,j]/sqrt(c[i,i]*c[j,j]) for i in 1:Data.nochosen[1], j in 1:Data.nochosen[1]]-eye(c)
  for i in 1:Data.nochosen[1]
    for j in 1:Data.nochosen[1]
      C[i,j] = c[i,j]/sqrt(c[i,i]*c[j,j]);
    end
  end
  C -= eye(C);

  if maximum(C) > Data.correlation_limit[1]
    (i,j) = max_index(abs(C))

    @printf("CORRELATION FOUND:\t %2.2f\n", C[i,j])
    @printf("%s (%2.2f) and %s (%2.2f)\n", 
      Data.names[Data.subset[i]], 
      Data.twonorms[Data.subset[i]], 
      Data.names[Data.subset[j]], 
      Data.twonorms[Data.subset[j]])

    if Data.twonorms[Data.subset[i]] > Data.twonorms[Data.subset[j]] 
      removed = j
    else 
      removed = i
    end
    @printf("Removed parameter:\t %s\n", Data.names[Data.subset[removed]])
    @printf("----------------------------------------------\n")
    splice!(Data.subset,removed)
    Data.nochosen[1] -= 1

    return int32(1)

  else
    @printf("----------------------------------------------\n")
    @printf("No correlation larger than %2.2f have been identified.\n",Data.correlation_limit[1])
    @printf("----------------------------------------------\n")
    (i,j) = max_index(abs(C))
    return int32(0)
  end
end

function SCM_print_results(
  Data :: SCMdata)

  @printf("\n\nSTATUS: Structural Correlations analysis finished.\n")
  @printf("Found parameters are:\n")
  @printf("----------------------------------------------\n")
  @printf("2-norm\t Name\n")
  @printf("----------------------------------------------\n")
  #for i in 1:Data.nochosen[1]
  for i in sortperm(Data.twonorms[Data.subset])[end:-1:1]
    @printf("%2.4f\t %s\n", Data.twonorms[Data.subset[i]], Data.names[Data.subset[i]])
  end
  @printf("----------------------------------------------\n")
end

function max_index(
  Ain :: Array{Float64,2})

  A = copy(Ain)
  B = zeros(Int,size(A))

  # Order each column
  for i in 1:size(A,1)
    B[:,i] = sortperm(A[:,i])
    A[:,i] = A[B[:,i],i]
  end
  # Save index for largest row in each column
  maxrows = copy(B[end,:])

  # Transpose, and repeat
  A = A'
  B = zeros(Int,size(A))
  for i in 1:size(A,1)
    B[:,i] = sortperm(A[:,i])
    A[:,i] = A[B[:,i],i]
  end

  # Last component of the last column of B is the column number we are looking for
  j = copy(B[end,end])
  i = maxrows[j]

  return (i,j) :: (Int, Int);
end

function OSM_calcE!(
  Data :: OSMdata)

  """ Function to be called by OSM! to calculate the E-rank
  of the parameters. """

    #p = numpy.size(basis,1)
    #STS =  numpy.dot(numpy.transpose(basis),basis)
    #[l, Q] = numpy.linalg.eig(STS);

  STS = Data.sensitivities'*Data.sensitivities
  (l, Q) = eig(STS)

    #E = abs(Q)
    #E = numpy.array(numpy.dot(numpy.abs(Q),numpy.abs(l)))/numpy.sum(numpy.abs(l))
    #E = E[0]

  Data.E = abs(Q)*abs(l)/sum(abs(l))

  return int(0)
end

function OSM_select_par!(
  index :: Int,
  Data :: OSMdata;
  I = NaN :: Float64,
  angle = NaN :: Float64)
  """ Function to be called by OSM! to select a parameter for the subset. """

  push!(Data.subset, Data.available[index])
  push!(Data.I,I)
  push!(Data.angles,angle)
  splice!(Data.available,index)

  return int(0)
end

function OSM_calculate_I_and_select!(
  Data :: OSMdata)

  d = zeros(Float64,size(Data.available))
  for (i,j) in enumerate(Data.available)
    a = Data.sensitivities[:,Data.subset]\Data.sensitivities[:,j]
    s = Data.sensitivities[:,Data.subset]*a

    ########################################################
    #  Calculate the I-index for the remaining parameters  #
    ########################################################
    
    # Consinder the easy options first

    if norm(Data.sensitivities[:,j]) < Data.tolerance
      # If the column has near 0 2-norm, set d[j] = 0
      d[i] = 0.0

    elseif norm(a) < Data.tolerance
      # If the closests fit has all zero components, set d[j] = 1
      d[i] = 1.0

    else
      # Calculate the projection length and denominator 
      proj_length = dot(s,Data.sensitivities[:,j])
      denom = norm(s)*norm(Data.sensitivities[:,j])

      if abs(proj_length/denom) > 1.0
        # This could happen with numerical error, but would only be slightly larger
        d[i] = 0
      else
        d[i] = sin(acos(proj_length/denom))
      end

    end
  end

  I = Data.E[Data.available].*d


  #####################################
  #  Now for selecting the parameter  #
  #####################################
  
  if norm(I) == 0.0
    # If all I-values are 0
    println("All I-values are 0")
    
    if norm(Data.E[Data.available]) == 0
      # If E-value of remaining parameters are 0, select first from the list
      selected_element = sortperm(Data.available)[1]

    else
      # Select available parameter with largest E-value
      selected_element = sortperm(E[Data.available])[end]

    end

  else
    # Otherwise, select parameter with largest I-value
    selected_element = sortperm(I)[end]

  end

  OSM_select_par!(
    selected_element :: Int,
    Data :: OSMdata;
    I=I[selected_element],
    angle=d[selected_element])

  return int(0)
end

function OSM_print_results(
  Data :: OSMdata)

  @printf("Results for OSM analysis:\n")
  @printf("---------------------------------------------------------------------------------------------------\n")
  @printf("Rank\t\t I\t\t E\t\t d\t\t Name\n")
  @printf("---------------------------------------------------------------------------------------------------\n")
  for (i,j) in enumerate(Data.subset)
    @printf("%i\t\t %1.0e \t\t %1.0e \t\t %1.0e \t\t %s\n", i, Data.I[i], Data.E[j], Data.angles[i], Data.names[j])
  end
  @printf("---------------------------------------------------------------------------------------------------\n")
end

function OSM!(
  Data :: OSMdata)


  ###############
  #  Load data  #
  ###############


  run(`figlet -w 800 Orthogonal Sensitivities`)

  #@printf("    ____       _   _                                   _    _____                _ _   _       _ _   _           
   #/ __ \\     | | | |                                 | |  / ____|              (_) | (_)     (_) | (_)          
  #| |  | |_ __| |_| |__   ___   __ _  ___  _ __   __ _| | | (___   ___ _ __  ___ _| |_ ___   ___| |_ _  ___  ___ 
  #| |  | | '__| __| '_ \\ / _ \\ / _` |/ _ \\| '_ \\ / _` | |  \\___ \\ / _ \\ '_ \\/ __| | __| \\ \\ / / | __| |/ _ \\/ __|
  #| |__| | |  | |_| | | | (_) | (_| | (_) | | | | (_| | |  ____) |  __/ | | \\__ \\ | |_| |\\ V /| | |_| |  __/\\__ \\
   #\\____/|_|   \\__|_| |_|\\___/ \\__, |\\___/|_| |_|\\__,_|_| |_____/ \\___|_| |_|___/_|\\__|_| \\_/ |_|\\__|_|\\___||___/
                               #__/ |                                                                            
                              #|___/                                                                             \n") 
  # Calculate E values
  OSM_calcE!(
    Data :: OSMdata)

  # If subset is empty, select the parameter with largest E-value
  if length(Data.subset) == 0
    first = sortperm(Data.E)[end]
    OSM_select_par!(
      first :: Int,
      Data :: OSMdata)
    end

  while length(Data.available)>0
    # As long as there are still parameters to add to the subset
    OSM_calculate_I_and_select!(
      Data :: OSMdata)
  end

  # Print results
  OSM_print_results(
    Data :: OSMdata)

  return int(0)
end

function Morris!(
  Data :: Morrisdata)
  
  """ 
  [Mus, S2] = morris_series_parallel(l,r,p,response) 
  
  Calculates elementary effects using Morris method.
  
  Parameters
  ----------
  l : The number of points per dimension on the parameter grid.
  r : The number of evaluations of elementary effects for each parameter.
  p : The number of parameters.
  response : a function that takes a numpy.array of length p with parameter-values uniformly distributed between 0 and 1.

  Returns
  -------
  Mus : Sampling mean (the mean of the ABSOLUTE value of the elementary effects).
  S2 : Sampling variance.
  
  References
  ----------
  The code is presented on the algorithm presented by Smith in the book "Uncertainty Quantification: Theory, Implementation, and Applications" page 331-334.

  Comments
  --------
  The code could probably be improved by implementing methods for selecting good initial points on the parameter grid.

  Author
  ------
  Christian Haargaard Olsen <chaarga@ncsu.edu>

  """

  l = Data.level
  r = Data.points
  p = Data.no_parameters
  response = Data.f 

  run(`figlet -w 800 Morris`)
                             
  @printf("\n\nCalculating Morris measures mean and variance for l=%i, r=%i.\n",l,r)


  # For l even, this delta prevent Type2 errors
  delta = l/(2.0*(l-1))

  #Sample base parameter values 
  q = Morris_qvalue(l,p)

  ###############################################################################
  #                       Do steps and calculate indices                        #
  ###############################################################################
    
  #Determine size of output
  resp = response(vec(q))
  n_t = length(resp)

  #Containers for responses and d values
  d   = zeros(r,p,n_t)
  uis = zeros(p,n_t)
  ui  = zeros(p,n_t)
  s2i = zeros(p,n_t)

  for i in 1:r
    # generate initial parameter configuration - the point to start in the grid
    q = Morris_qvalue(l,p)

    results = zeros(p+1,n_t)

    # Generate the permutation matrix - See Smith. 2013
    A = zeros(p+1,p)
    J = ones(p+1,p)
    for j in 1:size(A,1)
      for k in 1:size(A,2)
        if j>k
          A[j,k] = 1
        end
      end
    end

    D = diagm(floor(2*rand(p)-1)*2+1)
    P = eye(p)
    P = P[shuffle([1:p]),:]

    B = (J.*q' + delta/2*((2*A-J)*D + J))*P

    # In case the permutation takes any values to be larger than 1, find the indexes that overshoots, and subtract 2*delta instead
    over = -floor(-mod(B,1).*floor(B/1))
    B = B-2*delta*over

    # Find the order of steps, so the elementary effects can be assigned to the correct parameter
    shift = diff(B)
    shiftindex = [indmax(abs(shift[i,:])) for i in 1:p]
    deltas = sum(shift,1)

    #parallel code
    y0 = zeros(p+1,n_t)
    for j in 1:p+1
      y0[j,:] = response(vec(B[j,:]))
    end

    # Calculate the elementary effects, and assign them to the correct parameter
    for j in 1:p
      d[i,shiftindex[j],:] = (y0[j+1,:]-y0[j,:])/deltas[j]
    end
  end

  for i in 1:p
    for j in 1:n_t
      uis[i,j] = sum(abs(d[:,i,j]))/r
      ui[i,j] = sum(d[:,i,j])/r
      s2i[i,j] = sum((d[:,i,j]-ui[i,j]).^2)/(r-1)
    end
  end

  Data.mu = uis
  Data.s2 = sqrt(s2i)

  if Data.print
    Morris_print(Data)
  end

  return int32(0)
end

function Morris_print(
  Data :: Morrisdata)

  if Data.print
    munorm = [norm(Data.mu[i,:]) for i in 1:Data.no_parameters]
    s2norm = [norm(Data.s2[i,:]) for i in 1:Data.no_parameters]
    @printf("\n\nResults for Morris elementary effects analysis\n")
    @printf("---------------------------------------------------------------------------------------------------\n")
    @printf("Name \t \t μ \t \t σ2\n")
    @printf("---------------------------------------------------------------------------------------------------\n")
    for i in 1:Data.no_parameters
      @printf("%s\t\t %1.0e\t\t %1.0e.\n", Data.names[i], munorm[i], s2norm[i])
    end
    @printf("---------------------------------------------------------------------------------------------------\n")
  end
  @printf("See data structure fields .mu and .s2 for results.\n\n\n")
end

function Morris_qvalue(
  l :: Int, 
  n=1 :: Int)
  # Draw parameter values from the proper grid points
  return floor(rand(n)*(l))/(l-1)
end

function Sobol!(
  Data :: Soboldata)

  """ 
  [Si, STi] = sobol_weirs(M,no_p,response) 
  
  Calculates first order and total Sobol Indices of a function returning an array, using the method produced by Weirs et al., 2010.
  
  Parameters
  ----------
  M : The number of points in parameter space used.
  no_p: Number of parameters.
  response : A function accepting as input a numpy.array of parameter values.

  Returns
  -------
  Si : First order indices
  STi : Total indices
  
  References
  ----------
  The code is based on the method presented in the paper "Sensitivity analysis techniques applied to a system of hyperbolic conservation laws" by V. Gregory Weirs, James R. Kamm, Laura P. Swiler, Stefano Tarantola, Marco Ratto, Brian M. Adams, William J. Rider, Michael S. Eldred in Reliability Engineering and System Safety, vol. 107, 2012, pages 157-170.
  """

  M = Data.points
  run(`figlet -w 800 Sobol`)
                           
  @printf("\n\nCalculating first order Sobol Indices Si and STi using M=%i points.\n", M)

  no_p     = Data.no_parameters
  response = Data.f

  # Draw random parameter values ~ U(0,1)
  A = rand(M,no_p)
  B = rand(M,no_p)

  # Asses the size of the output.
  A0   = copy(A)
  resp = response(vec(A0[1,:]))
  n_t  = length(resp)

  # Container for model output
  yA  = zeros(M,n_t)
  yB  = zeros(M,n_t)
  yAB = zeros(M,n_t)
  yBA = zeros(M,n_t)

  # Some parallel magic
  # from http://stackoverflow.com/questions/9742739/how-do-i-make-processes-able-to-write-in-an-array-of-the-main-program/9849971
  # pool = Pool(processes=cpu_count())

  # Populate rows of yA and yB with responses corresponding to parameters from rows of 
  # A and B
  for i in 1:M
    yA[i,:] = response(vec(A[i,:]))
    yB[i,:] = response(vec(B[i,:]))
  end

  yC          = [yA,yB]
  yC2         = mean(yC,1).^2
  denominator = sum(yC.*yC,1)-2*M*yC2

  Data.Si     = zeros(no_p,n_t)
  Data.STi    = zeros(no_p,n_t)

  # For each parameter
  for i in 1:no_p
    Bi = copy(B)
    Bi[:,i] = copy(A[:,i])
    Ai = copy(A)
    Ai[:,i] = copy(B[:,i])

    # For parameter set
    for j=1:M
      yAB[j,:] = response(vec(Ai[j,:]))
      yBA[j,:] = response(vec(Bi[j,:]))
    end

    Data.Si[i,:]  = 2*sum(yA.*(yBA -yB),1)./denominator
    Data.STi[i,:] = sum((yA-yAB).*(yA-yAB),1)./denominator

    @printf("Done for parameter: %i/%i.\n", i, no_p)
  end

  Sobol_print(Data)
  return 0
end

function Sobol_print(
  Data :: Soboldata)

  if Data.print
    Sinorm = [norm(Data.Si[i,:]) for i in 1:Data.no_parameters]
    STinorm = [norm(Data.STi[i,:]) for i in 1:Data.no_parameters]
    @printf("\n\nResults for Sobol indices analysis\n")

    @printf("---------------------------------------------------------------------------------------------------\n")
    @printf("Name \t \t Si \t \t STi\n")
    @printf("---------------------------------------------------------------------------------------------------\n")
    for i in 1:Data.no_parameters
      @printf("%s\t\t %1.0e\t\t %1.0e.\n", Data.names[i], Sinorm[i], STinorm[i])
    end
    @printf("---------------------------------------------------------------------------------------------------\n")
  end
  @printf("See data structure fields .Si and .STi for results.\n\n\n")
end

function ishigami_function(
  x :: Array{Float64,1};
  a = 7.0 :: Float64,
  b = 0.05 :: Float64)
  """
  y = ishigami_function(x; a=7.0, b=0.05)

  The Ishigami function of Ishigami & Homma (1990) is used as an example for uncertainty 
  and sensitivity analysis methods, because it exhibits strong nonlinearity and nonmonotonicity. 
  It also has a peculiar dependence on x3, as described by Sobol' & Levitan (1999). 
  (Description from http://www.sfu.ca/~ssurjano/ishigami.html)

  Parameters
  ----------
  x is a vector with three components with numbers between 0 and 1. They are scaled to -pi:pi before 
  they are used in the function expression.
  a = 7.0 as suggested by Sobol & Levitan (1999)
  b = 0.05 as suggested by Sobol & Levitan (1999)

  Returns
  -------
  Returns function output for the function
      f(x) = sin(x[1]) + a*sin(x[2])^2 + b*x[3]^4*sin(x[1]).
  
  Comments
  --------
  Analytical values for a=7, b=0.05 for Si should be [0.222, 0.697, 0.000] (Smith, 2014.)

  References
  ----------
  The code is presented on the algorithm presented by Smith in the book "Uncertainty Quantification: 
  Theory, Implementation, and Applications" page 331-334.
  
  Author
  ------
  Christian Haargaard Olsen <christianhaargaard@gmail.com>
  """

  # scale parameters to interval -pi:pi
  x = x*2.0*pi-pi
  y = (
    + sin(x[1]) 
    + a*(sin(x[2]))^2 
    + b*x[3]^4*sin(x[1]) 
    )
  #return [y,y] # To test the tools for function returning more than one output eg. time-dependent
  return y
end

function sobols_function(
  x :: Array{Float64,1};
  a1 = 78.0:: Float64,
  a2 = 12.0 :: Float64,
  a3 = 0.50 :: Float64,
  a4 = 2.00 :: Float64,
  a5 = 97.0 :: Float64,
  a6 = 33.0 :: Float64,
  p = 6 :: Int,
  )
  """
  y = sobols_function(x; a=7.0, b=0.05)


  Parameters
  ----------
  x is a vector with three components with numbers between 0 and 1. They are scaled to -pi:pi before 
  they are used in the function expression.
  a = 7.0 as suggested by Sobol & Levitan (1999)
  b = 0.05 as suggested by Sobol & Levitan (1999)

  Returns
  -------
  Returns function output for the function
      f(x) = sin(x[1]) + a*sin(x[2])^2 + b*x[3]^4*sin(x[1]).
  
  Comments
  --------
  Numerical values from Smith (2014) are
      |   x1    |   x2    |    x3   |    x4   |   x5    |   x6   
    -------------------------------------------------------------
    μ | 5.60e-2 | 2.77e-1 |  1.76e0 |  1.19e0 | 3.50e-2 | 9.90e-2
    σ | 3.84e-2 | 1.90e-1 |  1.68e0 |  1.13e0 | 3.74e-2 | 2.38e-2
    -------------------------------------------------------------

  References
  ----------
  The code is presented on the algorithm presented by Smith in the book "Uncertainty Quantification: 
  Theory, Implementation, and Applications" page 331-334.
  
  Author
  ------
  Christian Haargaard Olsen <christianhaargaard@gmail.com>
  """

  # scale parameters to interval -pi:pi
  y = (
    (abs(4*x[1]-2.0)+a1)/(1.0+a1)*
    (abs(4*x[2]-2.0)+a2)/(1.0+a2)*
    (abs(4*x[3]-2.0)+a3)/(1.0+a3)*
    (abs(4*x[4]-2.0)+a4)/(1.0+a4)*
    (abs(4*x[5]-2.0)+a5)/(1.0+a5)*
    (abs(4*x[6]-2.0)+a6)/(1.0+a6)
    )
  #return [y,y] # To test the tools for function returning more than one output eg. time-dependent
  return y
end
end
