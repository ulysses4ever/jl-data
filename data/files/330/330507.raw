function sharedModel(data,compgraphs,compsummary,iters::Integer = 50000)
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

  dat = unique(dat[:,[:Peptide,:Condition,:Sample,:Digestion,:Population,:LogIntensity]])
  conditions = levels(dat[:Condition])
  digestions = levels(dat[:Digestion])

  N = size(dat)[1]
  nPeptides = length(peptides)
  nProteins = length(proteins)
  nConditions = length(conditions)
  nDigestions = length(digestions)

  #=proteinConditionMatrix = Array{UInt8,2}(N,nProteins*(nConditions-1))
  for j in 1:nProteins
    for c in 1:nConditions-1
      for i in 1:N
        print("column: $((j-1)*(nConditions-1) + c)\n")
        proteinConditionMatrix[i,(j-1)*(nConditions-1) + c] = (
          dat[i,:Condition] == conditions[c+1]
          && protToPep[findfirst((s)->s==dat[i,:Peptide],peptides),j] == 1 ?
          1 : 0
        )

      end
    end
  end=#

  proteinConditionMatrix = kron(eye(nProteins),[zeros(1,nConditions-1);eye(nConditions-1)])

  referenceAbundanceMatrix = kron(eye(nProteins),ones(nConditions,1))

  peptideMapMatrix = kron(eye(nPeptides),ones(nConditions,1))

  protToPep = kron(protToPep,eye(nConditions))

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



  digestMatrix = Array{UInt8,2}(N,nDigestions*nPeptides)
  for k in 1:nPeptides
    for j in 1:nDigestions
      for i in 1:N
        digestMatrix[i,(nPeptides)*(j-1) + k] = (dat[i,:Peptide] == peptides[k] && dat[i,:Digestion] == digestions[j] ? 1 : 0)
      end
    end
  end

  samples = levels(dat[:Sample])
  populations = levels(dat[:Population])

  dat[:SamplePopulation] = [string(dat[i,:Sample]) * ":" * string(dat[i,:Population]) for i in 1:size(dat)[1]]

  samplePopulations = levels(dat[:SamplePopulation])

  nSamples = length(samples)
  nPopulations = length(populations)
  nSamplePopulations = length(samplePopulations)

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


  intensity = [dat[i,:LogIntensity] for i in 1:size(dat)[1]]

  standata = [Dict{String,Any}(
    "N" => N,
    "y" => intensity,
    "nProteins" => nProteins,
    "nPeptides" => nPeptides,
    "nConditions" => nConditions,
    "nDigestions" => nDigestions,
    "nSamples" => nSamples,
    "nPopulations" => nPopulations,
    "nSamplePopulations" => nSamplePopulations,
    "protToPep" => protToPep,
    "peptideMatrix" => peptideMatrix,
    "peptideConditionMatrix" => peptideConditionMatrix,
    "proteinConditionMatrix" => proteinConditionMatrix,
    "referenceAbundanceMatrix" => referenceAbundanceMatrix,
    "peptideMapMatrix" => peptideMapMatrix,
    "digestMatrix" => digestMatrix,
    "samplePopMatrix" => samplePopMatrix,
    "samplePopToPopMatrix" => samplePopToPopMatrix
  )]

  #println(standata)

  model = """
  functions{
    vector lse(matrix X, vector a){
      vector[rows(X)] out;
      for (i in 1:rows(X))
        out[i] = log_sum_exp(log_sum_exp(row(X,i)' .* a) ,-cols(X) + sum(row(X,i)));
      return out;
    }
  }

  data{
    int N; //Number of data points;
    vector[N] y; //Response
    int<lower=1>nProteins; //Num proteins
    int<lower=1>nPeptides; //Num peptides
    int<lower=1>nConditions; //Num Conditions
    //int<lower=1>nDigestions; //Num Digestions
    //int<lower=1>nSamplePopulations; //Num Samples
    //int<lower=1> nPopulations; //Num populations
    //matrix<lower=0,upper=1>[N,nProteins*(nConditions-1)] proteinConditionMatrix;
    matrix<lower=0,upper=1>[nProteins*nConditions,nProteins*(nConditions-1)] proteinConditionMatrix;
    matrix<lower=0,upper=1>[nProteins*nConditions,nProteins] referenceAbundanceMatrix;
    matrix<lower=0,upper=1>[nPeptides*nConditions,nPeptides] peptideMapMatrix;
    matrix<lower=0,upper=1>[nPeptides*nConditions,nProteins*nConditions] protToPep;
    matrix<lower=0,upper=1>[N,nPeptides*nConditions] peptideConditionMatrix;
    matrix<lower=0,upper=1>[N,nPeptides] peptideMatrix;
    //matrix<lower=0,upper=1>[N,nDigestions*nPeptides] digestMatrix;

    //matrix<lower=0,upper=1>[N,nSamplePopulations] samplePopMatrix;
    //matrix<lower=0,upper=1>[nSamplePopulations,nPopulations] samplePopToPopMatrix;
    }

    transformed data{
    }

    parameters{
      vector[nProteins] logProteinReferenceAbundance;
      vector[nProteins*(nConditions-1)] logProteinFoldChange;
      //vector[(nProteins-1)*nConditions] logRelativeProteinAbundance;
      vector<lower=0,upper=1>[nPeptides] ionisationCoeff;
      //real<lower=0> sigmaRes;
    }

    transformed parameters{
      vector[nProteins*nConditions] logProteinAbundance;
      vector[nPeptides*nConditions] logPeptideAbundance;
      vector[nPeptides*nConditions] logPeptideIntensity;

      logProteinAbundance <- referenceAbundanceMatrix*logProteinReferenceAbundance + proteinConditionMatrix*logProteinFoldChange;
      logPeptideAbundance <- lse(protToPep, logProteinAbundance);// + ionisationCoeff;// digestMatrix*epsilonDigest + sampleMatrix*epsilonSample;

      logPeptideIntensity <- peptideMapMatrix*log(ionisationCoeff) + logPeptideAbundance;
      //for (j in 1:nPeptides*nConditions) {
      //  vector[nProteins] b;
      //  //
      //  for i in 1:nProtein
      //    b[i] <- protToPep
      //
      //  logPeptideAbundance <- log_sum_exp(b);
      //}
    }

    model{
      logProteinReferenceAbundance ~ normal(0,10);
      logProteinFoldChange ~ normal(0,10);
      ionisationCoeff ~ beta(5,1);
      //y ~ normal(peptideConditionMatrix*logPeptideAbundance + peptideMatrix*ionisationCoeff,sigmaRes);
      //sigmaRes ~ student_t(3,0,5);
      y ~ student_t(3,peptideConditionMatrix*logPeptideIntensity,0.1);
      //logRelativeProteinIntensity ~ normal()
    }
    generated quantities{
      //vector[nProteins*(nConditions-1)] logProteinFoldChange;
      vector[(nProteins-1)*nConditions] logRelativeProteinAbundance;

      /*for (p in 1:nProteins){
        for (c in 1:nConditions-1){
          logProteinFoldChange[(p-1)*(nConditions-1) + c] <- logProteinIntensity[(p-1)*nConditions + 1 + c] - logProteinIntensity[(p-1)*nConditions + 1];
        }
      }*/

      for (c in 1:nConditions){
        for (p in 1:nProteins-1){
          logRelativeProteinAbundance[(p-1)*nConditions+c] <- logProteinAbundance[p*nConditions + c] - logProteinAbundance[c];
        }
      }

    }
    """

  numChains = 4
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
