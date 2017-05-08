# Use the Datetime library for date and time manipulations (use Pkg.add("Datetime") first time)
using Datetime

# Read in the file 
d2=readlines(open("mfs.csv"));
# Create a dictionary to hold all of the incidents
type Incident
 idnum::Int
 idate::DateTime
 istation::ASCIIString
 icalltype::ASCIIString
end
calllog=Dict{DateTime,Incident}()
# Iterate through the file loading each elem
for thiselem in d2[2:end]
 eachelem=split(chomp(thiselem),',',4)
 # should check for collisions
 calllog[datetime(int(eachelem[2][1:4]),int(eachelem[2][6:7]),int(eachelem[2][9:10]),int(eachelem[2][12:13]),int(eachelem[2][15:16]),int(eachelem[2][18:19]),0,"Adelaide/Australia")]=Incident(int(eachelem[1]),datetime(int(eachelem[2][1:4]),int(eachelem[2][6:7]),int(eachelem[2][9:10]),int(eachelem[2][12:13]),int(eachelem[2][15:16]),int(eachelem[2][18:19]),0,"Adelaide/Australia"),eachelem[3],eachelem[4])
 end
outfil=open("comb.csv","w")
# print a header
println(outfil,"Fire,Incdate,dayofweek,hour,month");
 # Iterate through each time loading a fire or not
thisdate=datetime(2009,5,1,0,0,0,0,"Adelaide/Australia")
zeroskipped=0
linesprinted=0
while thisdate < datetime(2013,5,1,0,0,0,0,"Adelaide/Australia")
  zeroskipped=zeroskipped+1
  if (haskey(calllog,thisdate))
    if linesprinted < 1
      print(outfil,"1")
      println(outfil,",\"",thisdate,"\",",dayofweek(thisdate),',',hour(thisdate),',',month(thisdate))
      linesprinted=linesprinted+1
    end
   end
  if zeroskipped >=60
    if linesprinted < 1
        print(outfil,"0")
        println(outfil,",\"",thisdate,"\",",dayofweek(thisdate),',',hour(thisdate),',',month(thisdate))
      end
      zeroskipped=0
      linesprinted=0
    end
 thisdate=thisdate+minute(1)
end
close(outfil)
