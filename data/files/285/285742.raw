###########################################################################
module OptimalTax

  using Dataframes, JuMP, NLopt, NLsolve

  # We first describe the data

  function data()
    # the grid of wages
    w=Float64[0;2000;4000;6000;8000;10000;12500;15000;17500;20000;25000;30000;50000;100000]
    # the weights of income within the population
    h=Float64[14.2;3.3;2.7;2.8;3.0;4.8;5.2;6.5;4.7;8.2;9.8;16.4;14.5;3.9]
    # the intensive response of labor supply (from a occupation to another)
    eps=Float64[0;0.25;0.5]
    # the extensive reponse of labor supply (from an occuption to unemployement)
    eta=Float64[0;0.5;1]
    # the redistributive tastes of the government (the higher, the stronger)
    v=Float64[0.25;1;4]
    # The benchmark levels of consumption as used in Saez paper : a guaranteed income of 6000 dollars, and a proportional tax rate of 40% above.
    czero=Float64[6000;6001;6001;6001;6001;6001;7500;9000;10500;12000;15000;18000;30000;60000]
    # primitive weights for the optimization. The reflect
    prim=Float64[11250/6000;11250/6001;11250/6001;11250/6001;11250/6001;11250/6001;11250/7500;11250/9000;11250/10500;11250/12000;11250/15000;11250/18000;11250/30000;11250/60000]
    Dict("w"=>w,"h"=>h,"eps"=>eps,"eta"=>eta,"v"=>v,"czero"=>czero,"prim"=>prim)
  end

  d=data()

  ##################################### SOLVING NON LINEAR SYSTEM #################################################

  # We first try to find the optimal tax levels by using the package NLsolve. For some reasons, it does not work.
  # There is no convergence and we don't find any tax vector/


  function f!(T,g,vect,newh,MT)

    p=0.0
    vect=MT=newh=g=T=zeros(length(d["w"]))
    one=ones(length(d["w"]))

      # This is the first constraint as exposed in the pdf file
      if dot(newh,g)==100.0
          # This is the second constraint.
          if   dot(newh,T)==5000.0
            for i=1:14
              # This is the formula of social weights for the first bin defined in the pdf.
              g[1]=1/(p*(float(d["w"][1])-float(T[1])^d["v"][2]))
              # a part of the right hand side of the optimal marginal tax rates formula
              vect[1]=one[1]-g[1]
              # the updated income function in unemployement. According to the formula, should be equal to zero.
              newh[1]=d["h"][1]
              # a part of the RHS of the OMT rate formula
              vect[i]=one[i]-g[i]-d["eta"][2]*(T[i]-T[1])/(d["w"][i]-T[i]-d["w"][1]+T[1])
              # the LHS of the OMT rate formula
              MT[i]= T[i]-T[i-1]
              # The total RHS of the OMT rate formula, with vector vect.
              MT[i]=(d["w"][i]-T[i]-d["w"][i-1]+T[i-1])*((d["w"][i]-d["w"][i-1])/(d["w"][i]*(d["eps"][2]*newh[i])))*dot(newh[i:end],vect[i:end])
              # the social weights function as defined in Saez.
              g[i]=1/(p*(float(d["w"][i])-float(T[i])^d["v"][2]))
              # The update income function.
              newh[i]=d["h"][i]*((d["w"][i]-T[i]-d["w"][1]+T[1])/(d["c0"][i]-d["c0"][1]))^(d["eta"][2])
            end
          end
        end

  end

  nlsolve(f!, [-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;0.1;0.1;0.1;0.1])


  ##############################################################################

  # We now write a type function because we may need it to ease the use of our vectors to determine.

  type Endo
    # the vector of social weights
    g::Vector
    # the vector of updated income bins
    newh::Vector
    # the vector of "composite" social values in the optimal tax scheme
    vect::Vector
    # the real number describing the shadow value of public fund. It tells how binding the government consumption constraint is.
    p::Real
    # the vector of marginal tax rates for the optimal function
    MT::Vector
  end

  # we compute functions for each equation of the non linear system, so we can maybe get something from the nlsolve package.

  function optimtax!(T, MT,g,newh)

    newh=zeros(length(d["w"]))
    g=zeros(length(d["w"]))
    one=float(ones(d["w"]))

    for i=1:14
      MT[1]=0
      MT[i]=(d["w"][i]-T[i]-d["w"][i-1]+T[i-1])*((d["w"][i]-d["w"][i-1])/(d["w"][i]*(d["eps"][2]*newh[i])))*dot(newh[i:end],vec(one[i]-g[i]-d["eta"][2]*(T[i]-T[1])/(d["w"][i]-T[i]-d["w"][1]+T[1]))[i:end])

    end
    return T
  end

  # we relaxe this constraint and don't add it the optimization problem. We may test for it later.
  function constraint1!(endo::Endo)

    newh=float(endo.newh)
    g=float(endo.g)

    for i=1:14
      dot(newh,g)=100.0
    end
  end

  function constraint2!(T, cons1)

    cons1=5000.0
    cons1=dot(newh,T)

  end

  function socialvalue!(T, g)

    g=zeros(length(d["w"]))

    for i=1:14
      g[i]=1/(p*(float(d["w"][i])-float(T[i])^d["v"][2]))
    end
  end

  function incomeupdate!(T, newh)

    newh=zeros(length(d["w"]))

    for i=1:14
    newh[i]=d["h"][i]*((d["w"][i]-T[i]-d["w"][1]+T[1])/(d["c0"][i]-d["c0"][1]))^(d["eta"][2])
    end

  end

  nlsolve(optimtax!, socialvalue!,[-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;-0.1;0.1;0.1;0.1;0.1;0.1;0.1;0.1])

  # This does not work either.

  ########################################### MAXIMIZATION PROBLEM ###############################

  # We try now to transform the maximization problem into something feasible.
  w1=collect(linspace(0,200000,14))

  function obj(T::Vector,welfare::Vector,grad::Vector,d::Dict)
  # We compute welfare function as a cumulative sum. Only the last value is to be maximized.
    welfare[1]=d["prim"][1]*log(w1[1]-T[1])
    for i=2:14
      welfare[i]+=welfare[i-1]+d["prim"][i]*log(w1[i]-T[i])
    end
    # This value must be optimized
    bigwelfare = welfare[14]
    grad[1]=-d["prim"][1]/(w1[1]-T[1])

    for i=2:14
      grad[i]+=grad[i-1] -d["prim"][i]/(w1[i]-T[i])
    end
  end

  function constr(T::Vector,constraint::Vector,d::Dict)

    constraint[1]=0
    for i=2:14
      constraint[i]+=constraint[i-1]+T[i]*d["h"][i]*((w1[i]-T[i]-w1[1]+T[1])/(d["c0"][i]-d["c0"][1]))^0.5
      contraint[14]=5000.0
    end
    # This only value corresponds to the full government consumption constraint.
    bigconstraint = constraint[14]
  end

  JuMP.register(:obj, 14, obj, autodiff=true)
  JuMP.register(:constr, 14, constr, autodiff=true)

  # We try the JuMP maximization.

  function max_JuMP()
    d=data()
    m=Model()
    @variable(m, T[i=1:14])
    @NLobjective(m, Max, obj.bigwelfare)
    @NLconstraint(m, constr.bigconstraint==5000.0)
    print(m)
    solve(m)
    return Dict("T"=>T)
  end

  # We then try the NLopt maximization.

  function max_NLopt()
  d=data()
  optim=NLopt.Opt(:LD_MMA,14)
  max_objective!(optim, (T,bigwelfare,grad)-> obj(T,bigwelfare,grad,d))
  equality_constraint!(optim, (T,bigconstraint) -> constr(T,bigconstraint,d)==5000.0 ,1e-7)
  ftol_rel!(optim,1e-9)
  (optf, optx, ret)=optimize(optim, rand())
  println("I got $optx after $count iterations")
  end

############################ GRAPHS ###############################
end
