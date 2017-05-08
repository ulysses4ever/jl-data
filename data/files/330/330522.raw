using LightGraphs

function sharedModel(data,compgraphs,compsummary,iters::Integer = 50000, numChains::Integer = 4)
  prots = levels(data[:Protein])
  #println(prots)
  verts = [compgraphs[compsummary[1,:ID]][3][v] for v in vertices(compgraphs[compsummary[1,:ID]][1])]
  #println(verts)
  p = intersect(verts,prots)
  #println(p)
  dat = data[[data[i,:Protein] in p for i in 1:size(data)[1]].==true,:]

  peptides = levels(dat[:Peptide])
  proteins = levels(dat[:Protein])

  protToPep = Array{UInt8,2}(length(peptides),length(proteins))
  for j in 1:size(protToPep)[2]
    for i in 1:size(protToPep)[1]
      protToPep[i,j] = 0
    end
  end

  for i in 1:size(dat)[1]
    row = findfirst((s)->s==dat[i,:Peptide],peptides)
    col = findfirst((s)->s==dat[i,:Protein],proteins)
    protToPep[row,col] = 1
  end

  cols = filter(
    (s) -> !contains(string(s),"Protein"),
    names(dat)
  )

  #dat = unique(dat[:,[:Feature,:Peptide,:Condition,:Sample,:Population,:Count]])
  dat = unique(dat[:,cols])

  tmp = unique(dat[:,[:Peptide,:Feature]])
  nFeatures = Array{Int64,1}(length(peptides))
  for i in 1:length(peptides)
    nFeatures[i]  = size(levels(tmp[tmp[:Peptide].==peptides[i],:][:Feature]))[1]
  end

  maxNFeatures = maximum(nFeatures)


  features = levels(dat[:Feature])
  conditions = levels(dat[:Condition])
  #digestions = levels(dat[:Digestion])

  samples = levels(dat[:Sample])
  nSamples = Integer(length(samples)/length(conditions))


  peptideFeatureMap = zeros(length(features),length(peptides))
  for f in 1:length(features)
    p = findfirst(peptides,dat[dat[:Feature].==features[f],:][1,:Peptide])
    peptideFeatureMap[f,p] = 1
  end

  N = size(dat)[1]
  nPeptides = length(peptides)
  nProteins = length(proteins)
  totalNFeatures = length(features)
  nConditions = length(conditions)
  #nDigestions = length(digestions)

  proteinConditionMatrix = kron(eye(nProteins),[zeros(1,nConditions-1);eye(nConditions-1)])

  referenceAbundanceMatrix = kron(eye(nProteins),ones(nConditions,1))

  proteinSampleMatrix = kron(eye(nProteins*nConditions),ones(nSamples,1))

  peptideSampleToFeatureSampleMap = kron(peptideFeatureMap,eye(nConditions*nSamples))

  ionisationCoeffToFeatureMap = zeros(totalNFeatures,totalNFeatures+nPeptides)
  for p in 1:nPeptides
    for f in 1:nFeatures[p]
      a = cumsum(nFeatures)[p] - nFeatures[p]
      b = a + p
      ionisationCoeffToFeatureMap[a+f,b+f]=1.0
    end
  end

  ionisationMap = kron(ionisationCoeffToFeatureMap,ones(nSamples*nConditions,1))

  dirichletPrior = Array{Float64,1}(totalNFeatures + nPeptides)
  for p in 1:nPeptides
    a = cumsum(nFeatures)[p] - nFeatures[p] + p-1
    dirichletPrior[a+1] = 0.1
    for f in 2:nFeatures[p]+1
      dirichletPrior[a+f] = 1.0
    end
  end

  println(dirichletPrior)

  peptideMapMatrix = kron(eye(nPeptides),ones(nConditions,1))

  protToPep = kron(protToPep,eye(nConditions*nSamples))

  peptideConditionMatrix = Array{UInt8,2}(N,nPeptides*nConditions)
  for j in 1:nPeptides
    for k in 1:nConditions
      for i in 1:N
        peptideConditionMatrix[i,(j-1)*nConditions + k] = (
          dat[i,:Peptide] == peptides[j]
          && dat[i,:Condition] == conditions[k]
          ? 1 : 0
        )
      end
    end
  end

  peptideMatrix = Array{UInt8,2}(N,nPeptides)
  for j in 1:nPeptides
    for i in 1:N
      peptideMatrix[i,j] = (
        dat[i,:Peptide] == peptides[j] ? 1 : 0
      )
    end
  end



  #=digestMatrix = Array{UInt8,2}(N,nDigestions*nPeptides)
  for k in 1:nPeptides
    for j in 1:nDigestions
      for i in 1:N
        digestMatrix[i,(nPeptides)*(j-1) + k] = (dat[i,:Peptide] == peptides[k] && dat[i,:Digestion] == digestions[j] ? 1 : 0)
      end
    end
  end=#

  samples = levels(dat[:Sample])
  populations = levels(dat[:Population])

  dat[:SamplePopulation] = [string(dat[i,:Sample]) * ":" * string(dat[i,:Population]) for i in 1:size(dat)[1]]

  samplePopulations = levels(dat[:SamplePopulation])

  #nSamples = length(samples)
  nPopulations = length(populations)
  nSamplePopulations = length(samplePopulations)

  samplePopulationMap = zeros(nSamples*nConditions,nPopulations)
  tmp = unique(dat[:,[:Sample,:Population]])
  println(populations)
  for s in 1:length(samples)
    println("pop: " * string(tmp[tmp[:Sample].==samples[s],:][1,:Population]))
    a = findfirst(populations,tmp[tmp[:Sample].==samples[s],:][1,:Population])
    println(string(s)*","*string(a))
    samplePopulationMap[s,a] = 1.0
  end
  println(samplePopulationMap)
  proteinPopulationMatrix = kron(eye(nProteins),samplePopulationMap)


  samplePopMatrix = Array{UInt8,2}(N,nSamplePopulations)
  for j in 1:nSamplePopulations
    for i in 1:N
      samplePopMatrix[i,j] = (dat[i,:SamplePopulation] == samplePopulations[j] ? 1 : 0)
    end
  end

  samplePopToPopMatrix = Array{UInt8,2}(nSamplePopulations,nPopulations)
  for j in 1:nPopulations
    for i in 1:nSamplePopulations
      samplePopToPopMatrix[i,j] = (split(samplePopulations[i],":")[2] == string(populations[j]) ? 1 : 0)
    end
  end


  #intensity = [dat[i,:LogIntensity] for i in 1:size(dat)[1]]
  intensity = [dat[i,:Count] for i in 1:size(dat)[1]]

  standata = [Dict{String,Any}(
    "N" => N,
    "y" => intensity,
    "nProteins" => nProteins,
    "nPeptides" => nPeptides,
    "nConditions" => nConditions,

    "nFeatures"=> nFeatures,
    "maxNFeatures"=>maxNFeatures,
    "totalNFeatures"=>totalNFeatures,

    #"nDigestions" => nDigestions,

    "nSamples" => nSamples,
    "nPopulations" => nPopulations,
    "nSamplePopulations" => nSamplePopulations,
    "protToPep" => protToPep,
    "peptideMatrix" => peptideMatrix,
    "peptideConditionMatrix" => peptideConditionMatrix,
    "proteinConditionMatrix" => proteinConditionMatrix,
    "referenceAbundanceMatrix" => referenceAbundanceMatrix,
    "proteinSampleMatrix" => proteinSampleMatrix,

    "peptideSampleToFeatureSampleMap" => peptideSampleToFeatureSampleMap,
    "ionisationMap" => ionisationMap,
    "dirichletPrior" => dirichletPrior,

    "proteinPopulationMatrix" => proteinPopulationMatrix,

    "peptideMapMatrix" => peptideMapMatrix,
    #"digestMatrix" => digestMatrix,
    "samplePopMatrix" => samplePopMatrix,
    "samplePopToPopMatrix" => samplePopToPopMatrix
  )]

  #println(proteinPopulationMatrix)

  model = """
  functions{
    vector lse(matrix X, vector a){
      vector[rows(X)] out;
      for (i in 1:rows(X))
      {
        out[i] <- log_sum_exp(log_sum_exp(row(X,i)' .* a) ,-cols(X) + sum(row(X,i)));
      }
      return out;
    }

    int[] cumulative_sum(int[] a)
    {
      int out[size(a)];
      out[1] = a[1];

      for (i in 2:size(a))
      {
        out[i] = a[i] + out[i-1];
      }

      return out;
    }
  }

  data{
    int N; //Number of data points;
    int<lower=0> y[N]; //Response

    int<lower=1>nProteins; //Num proteins
    int<lower=1>nPeptides; //Num peptides
    int<lower=1>nConditions; //Num Conditions

    int<lower=1>nSamples; //NUm samples per condition
    int <lower=0> nFeatures[nPeptides]; //Number of LC-MS features corresponding to each peptide
    int<lower=1>totalNFeatures;//Total number of LC-MS features
    int<lower=1> maxNFeatures; //Most features in a single peptide

    vector[totalNFeatures+nPeptides] dirichletPrior;

    //int<lower=1>nDigestions; //Num Digestions
    //int<lower=1>nSamplePopulations; //Num Samples
    int<lower=1> nPopulations; //Num populations

    matrix<lower=0,upper=1>[nProteins*nConditions,nProteins*(nConditions-1)] proteinConditionMatrix;
    matrix<lower=0,upper=1>[nProteins*nConditions,nProteins] referenceAbundanceMatrix;

    matrix<lower=0,upper=1>[nProteins*nSamples*nConditions,nProteins*nConditions] proteinSampleMatrix;
    matrix<lower=0,upper=1>[totalNFeatures*nSamples*nConditions,nPeptides*nSamples*nConditions] peptideSampleToFeatureSampleMap;
    matrix<lower=0,upper=1>[totalNFeatures*nSamples*nConditions,totalNFeatures+nPeptides] ionisationMap;

    matrix<lower=0,upper=1>[nPeptides*nConditions,nPeptides] peptideMapMatrix;
    matrix<lower=0,upper=1>[nPeptides*nConditions*nSamples,nProteins*nConditions*nSamples] protToPep;
    matrix<lower=0,upper=1>[N,nPeptides*nConditions] peptideConditionMatrix;
    matrix<lower=0,upper=1>[N,nPeptides] peptideMatrix;

    matrix<lower=0,upper=1>[nProteins*nSamples*nConditions,nProteins*nPopulations] proteinPopulationMatrix;

    //matrix<lower=0,upper=1>[N,nDigestions*nPeptides] digestMatrix;
    //matrix<lower=0,upper=1>[N,nSamplePopulations] samplePopMatrix;
    //matrix<lower=0,upper=1>[nSamplePopulations,nPopulations] samplePopToPopMatrix;


    }

    transformed data{

      int posArray[nPeptides];

      for (p in 1:nPeptides)
      {
        posArray[p] = cumulative_sum(nFeatures)[p] - nFeatures[p] + p;
      }

    }

    parameters{
      vector[nProteins] logProteinReferenceAbundance;
      vector[nProteins*(nConditions-1)] logProteinFoldChange;
      //vector[nProteins*nConditions*nSamples] logProteinSampleAbundance;
      vector[nProteins*nConditions*nSamples] raw_logProteinSampleAbundance;
      vector<lower=0> [totalNFeatures+nPeptides] raw_ionisationCoeff;
      vector<lower=0>[nProteins*nPopulations] sigma_population;
      real<lower=0> sigma_res;
      vector[N] res;

    }

    transformed parameters{
      vector[nProteins*nConditions] logProteinAbundance;

      vector[nPeptides*nConditions*nSamples] logPeptideSampleAbundance;
      vector[nProteins*nConditions*nSamples] logProteinSampleAbundance;

      vector[N] logFeatureSampleIntensity;

      vector<lower=0> [totalNFeatures+nPeptides] ionisationCoeff;

      logProteinAbundance <- referenceAbundanceMatrix*logProteinReferenceAbundance + proteinConditionMatrix*logProteinFoldChange;

      logProteinSampleAbundance <- proteinSampleMatrix*logProteinAbundance + raw_logProteinSampleAbundance;

      logPeptideSampleAbundance <- lse(protToPep, logProteinSampleAbundance);

      for (p in 1:nPeptides){
        int pos;
        vector[nFeatures[p]+1] lambda;

        pos = posArray[p];

        lambda = segment(raw_ionisationCoeff, pos, nFeatures[p] + 1);
        lambda = lambda / sum(lambda);

        for (f in 1:nFeatures[p]+1)
        {
          ionisationCoeff[pos-1 + f] <- lambda[f];
        }
      }


      logFeatureSampleIntensity <- ionisationMap*log(ionisationCoeff) + peptideSampleToFeatureSampleMap*logPeptideSampleAbundance;
    }

    model{


      logProteinReferenceAbundance ~ normal(0,10);
      logProteinFoldChange ~ normal(0,10);
      raw_ionisationCoeff ~ gamma(dirichletPrior,1.0);

      sigma_population ~ student_t(3,0,5);
      sigma_res ~ student_t(3,0,5);

      //logProteinSampleAbundance ~ normal(proteinSampleMatrix*logProteinAbundance,proteinPopulationMatrix*sigma_population);
      raw_logProteinSampleAbundance ~ normal(0,proteinPopulationMatrix*sigma_population);
      
      res ~ student_t(3,0,sigma_res);
      y ~ poisson(exp(logFeatureSampleIntensity + res));
    }
    generated quantities{
      vector[(nProteins-1)*nConditions] logRelativeProteinAbundance;

      for (c in 1:nConditions){
        for (p in 1:nProteins-1){
          logRelativeProteinAbundance[(p-1)*nConditions+c] <- logProteinAbundance[p*nConditions + c] - logProteinAbundance[c];
        }
      }

    }
    """

  #numChains = 4
  initialIters = iters
  warmup = 0.5
  thinning =  1

  stanmodel = Stan.Stanmodel(Stan.Sample(save_warmup = false),
                    name="model",
                    nchains=numChains,
                    model=model,
                    adapt = round(Int, warmup*initialIters),
                    update = round(Int, initialIters*(1-warmup)),
                    thin = thinning)
  #tic()
  sim = Stan.stan(stanmodel, standata, pwd(), CmdStanDir=Stan.CMDSTAN_HOME)

  Mamba.gelmandiag(sim[:,filter(s->!contains(s,"__"),sim.names),:])

  sim

end
