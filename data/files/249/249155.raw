using OLS
using Base.Test

# write your own tests here

data = readcsv("/home/rudfaden/Dropbox/Archive/Advanced microeconometrics/Class/Week2/wagepan.txt")

# CREATE VARIABLES
nr   = data[:,1]                                                           # Individual identifier                    
y    = data[:,9]          
x    = [data[:,3] data[:,5] data[:,7] data[:,4] data[:,10] data[:,6] data[:,8]]

lbly = "LWAGE"
lblx = ["CONSTANT", "BLACK", "HISP", "EDUC", "EXPER", "EXPERSQ", "MARRIED", "UNION"]


b, se, t, R2, R2adj, F, s2, p=ols(y,x)

olstable("Wage Estimation",lbly,lblx,b,se,t,R2,R2adj,F,s2,p)
