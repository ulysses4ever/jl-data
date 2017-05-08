#reload ("DanaTypes.jl/test/DanaTypesTest.jl")
using DanaTypes
using Base.Test
import DanaTypes.set
# test DanaBoolean
db1=DanaBoolean(Dict{Symbol,Any}(:Brief=>"test",:Default=>true))
@test db1.value==true
@test db1.immute.brief=="test"
db2=DanaBoolean(Dict{Symbol,Any}(:Default=>false))
@test db2.value==false
@test db2.immute.brief=="Boolean Value" #default brief
db3=DanaBoolean(Dict{Symbol,Any}())
@test db3.value==false #defualt 
@test db3.immute.brief=="Boolean Value" #default brief
db4=DanaBoolean()
@test db4.value==false #defualt 
@test db4.immute.brief=="Boolean Value" #default brief
db5=DanaBoolean(Dict{Symbol,Any}(:Brief=>"test",:Default=>true,:finalBrief=>"finaltest",:finalDefault=>false))
@test db5.value==false #defualt 
@test db5.immute.brief=="finaltest" #default brief
# test DanaInteger
di1=DanaInteger(Dict{Symbol,Any}(:Brief=>"test",:Default=>1,:Lower=>-1))
@test di1.value==1
@test di1.immute.brief=="test"
set(di1,-1)
@test di1.value==-1
@test isa(set(di1,-2),DanaError)
@test di1.value==-1
di2=DanaInteger(Dict{Symbol,Any}(:Default=>2))
@test di2.value==2
@test di2.immute.brief=="Integer Number" #default brief
di3=DanaInteger(Dict{Symbol,Any}())
@test di3.value==0 #defualt 
@test di3.immute.brief=="Integer Number" #default brief
di4=DanaInteger()
@test di4.value==0 #defualt 
@test di4.immute.brief=="Integer Number" #default brief
di5=DanaInteger(Dict{Symbol,Any}(:Brief=>"test",:Default=>4,:finalBrief=>"finaltest",:finalDefault=>3))
@test di5.value==3 #defualt 
@test di5.immute.brief=="finaltest" #default brief
# test DanaSwitcher
ds1=DanaSwitcher(Dict{Symbol,Any}(:Brief=>"test",:Default=>1,:Valid=>Set(-1,1)))
@test isequal(ds1,-1)[1]==nothing
set(ds1,1)
@test get(ds1)==1
@test ds1.immute.brief=="test"
set(ds1,-1)
@test get(ds1)[1]==-1
ret= set(ds1,-2)
@test isa(ret,DanaError)
@test get(ds1)==-1
@test isequal(ds1,-1)==true
# test DanaReal
dr1=DanaReal(Dict{Symbol,Any}(:Brief=>"test",:Default=>1.0,:Lower=>-1.0))
set(dr1,1.0)
@test get(dr1)==1.0
@test dr1.immute.brief=="test"
set(dr1,-1.0)
@test get(dr1)==-1.0
@test isa(set(dr1,-2.0),DanaError)
@test get(dr1)==-1.0
dr2=DanaReal(Dict{Symbol,Any}(:Default=>2.0))
@test isunknown(get(dr2)) #isunknown til set
@test dr2.immute.brief=="Real Number" #default brief
dr3=DanaReal(Dict{Symbol,Any}())
@test dr3.value==0.0 #defualt 
@test dr3.immute.brief=="Real Number" #default brief
dr4=DanaReal()
@test dr4.value==0.0 #defualt 
@test dr4.immute.brief=="Real Number" #default brief
dr5=DanaReal(Dict{Symbol,Any}(:Brief=>"test",:Default=>4.0,:finalBrief=>"finaltest",:finalDefault=>1.0,:Upper=>1.0))
set(dr5,3.0) #3.0>upper
@test isunknown(get(dr5)[1]) #unset 
@test dr5.immute.brief=="finaltest" #default brief
