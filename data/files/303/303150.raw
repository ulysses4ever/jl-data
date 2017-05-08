using PedModule
using DataFrames

type NumSSBayes
  num_ped::Int64  #individulals in pedigree
  num_g1::Int64   #non-genotyped individuals in pedigree
  num_g2::Int64   #genotyped individuals in pedigree
  num_y::Int64    #individuals with phenotypes
  num_y1::Int64   #non-genotyped individuals with phenotypes
  num_y2::Int64   #genotyped individuals with phenotypes
  num_markers::Int64 #number of markers
end

type ZMats
  Z    # Z= | Z1 0 |
  Z1   #    | 0  Z2|
  Z2   # Z_1 = |Z1|
  Z_1  #       |0 |
end

type AMats
  Ai
  Ai11
  Ai12
end

type YVecs
  y
  y1
  y2  #order of ids is same to order of y
  ids #order of ids is nongeno then geno
end

type MMats
  M
  M1
  M2
end

type JVecs
  J
  J1
  J2
end

type XMats
  X
  X1
  X2
end

type WMats
  W
  W1
  W2
end

function calc_Ai(pedfile,genoID;calculateInbreeding=true)
    #ped         = PedModule.mkPed(pedfile,inbreeding=calculateInbreeding)
    ped         = PedModule.mkPed(pedfile)
    num_nongeno = PedModule.genoSet!(genoID,ped)
    Ai          = PedModule.AInverse(ped)
    num_ped     = size(Ai,2)   #num_ped=num_geno+num_nongeno
    num_geno    = num_ped-num_nongeno
    Ai11        = Ai[1:num_nongeno,1:num_nongeno]
    Ai12        = Ai[1:num_nongeno,(num_nongeno+1):num_ped]
    return ped,AMats(Ai,Ai11,Ai12),NumSSBayes(num_ped,num_nongeno,num_geno,0,0,0,0)
end

function read_genotypes(file,all_num,header=false,rowID=true)

    #get number of markers
    f=open(file)
    if rowID == true
      len_ebv = length(split(readline(f)))
      num_markers  = len_ebv - 1
    end
    close(f)

    all_num.num_markers = num_markers
    #set types for each column
    etv= Array(DataType,len_ebv)
    fill!(etv,Int64)
    etv[1]=UTF8String

    #read genotypes
    df = readtable(file, eltypes=etv, separator = ' ',header=false)
    return df
end

function make_MMats(df,all_A,ped)
    num_obs, num_cols = size(df)
    num_markers  = num_cols - 1
    M2 = Array(Float64,num_obs,num_markers)
    num_nongeno=size(all_A.Ai11,1)

    for i in 1:num_obs
      id = df[i,1]
      row = ped.idMap[id].seqID - num_nongeno
      M2[row,:] = convert(Array,df[i,2:num_cols])
    end
    M1 = all_A.Ai11\(-all_A.Ai12*M2)
    M  = [M1;M2];
    return MMats(M,M1,M2)
end

function make_yVecs(file,all_num)
    df = readtable(file, eltypes=[UTF8String, Float64], separator = ' ',header=false)
    num_y = size(df,1)

    num_g2     = all_num.num_g2
    num_g1     = all_num.num_g1
    num_ped    = all_num.num_ped

    y   = fill(-9999.0,num_ped)
    ids = fill(".",num_ped)

    for i=1:num_y
      j = ped.idMap[df[i,1]].seqID
      y[j]   = df[i,2]
      ids[j] = df[i,1]
    end

    y1 = y[1:num_g1]
    y2 = y[(num_g1+1):num_ped]
    y1 = y1[y1.!=-9999]
    y2 = y2[y2.!=-9999]
    ids = ids[ids.!="."] #order of ids is nongeno then geno
    y = [y1;y2]          #order of ids is same to order of y

    all_num.num_y = num_y
    all_num.num_y1= length(y1)
    all_num.num_y2= length(y2)

    return YVecs(y,y1,y2,ids)
end

function make_JVecs(all_num,all_A)
    J2 = -ones(all_num.num_g2,1)
    J1 = all_A.Ai11\(-all_A.Ai12*J2)
    J  = [J1;
          J2]
    return JVecs(J,J1,J2)
end

function make_ZMats(ped,all_y,all_num)
    Z = spzeros(all_num.num_y,all_num.num_ped)
    num_row=1
    for i in all_y.ids #go through y
      j=ped.idMap[i].seqID #get the position of this id in reordered A
      Z[num_row,j]=1
      num_row += 1
    end

    # Z= | Z1 0 |
    #    | 0  Z2|

    Z_1= Z[:,1:all_num.num_g1]
    Z1 = Z[1:all_num.num_y1,1:all_num.num_g1]
    Z2 = Z[(all_num.num_y1+1):all_num.num_y,(all_num.num_g1+1):all_num.num_ped]
    return ZMats(Z,Z1,Z2,Z_1)
end

function make_XWMats(all_J,all_Z,all_M,all_num)#now fixed effects: μ
    X1  = hcat(ones(all_num.num_y1), all_Z.Z1*all_J.J1)
    X2  = hcat(ones(all_num.num_y2), all_Z.Z2*all_J.J2)
    X   =[X1;
          X2]

    W1 = all_Z.Z1*all_M.M1
    W2 = all_Z.Z2*all_M.M2
    W  = [W1;W2];
    return XMats(X,X1,X2),WMats(W,W1,W2)
end

function test123()
    a=3
end