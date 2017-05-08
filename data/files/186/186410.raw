#Astro 585 Homework 3

# 2a. Creating an array:
srand(10)
N=1024
A=randn(N)

# Time to print that:
@elapsed x=A
2.331e-6

#2b. 
#Write an array to files in asciii format
function write_to_file()
    fin=open("writefile.txt","w+");
    A=randn(1000);
    writecsv(fin,A);
    close(fin);
    return A #Just to print the values of A to check later with the read in values.
end


#2b. 
# read in ascii format
function read_from_file()
fr=open("writefile.txt","r");
C=readcsv(fr,Float64);
    close(fr);
    return C
end

#2c.
@elapsed x=write_to_file()
#0.006761774
@elapsed x=read_from_file()
#0.001323264
#0.00121477
#reduces slightly.

#2d.
#Write an array to files in binary format
function write_binary()
    fin=open("writebinary.bin","w+");
    B=randn(1000);
    write(fin,B);
    close(fin);
    return B; #Just to print the values of A to check later with the read in values.
end

#Write an array to files in binary format
function read_binary()
    fr=open("writebinary.bin");
D=read(fr,Float64,1000);
    close(fr);
    #return D;
end

#For a large matrix
function write_binary()      # writing a binary
    fin=open("writebinary.bin","w+");
    B=randn(1000,1000,100);
    write(fin,B);
    close(fin);
    return B #Just to print the values of A to check later with the read in values.
end
@elapsed x=write_binary()

function read_binary() # reading a binary
    fr=open("writebinary.bin");
D=read(fr,Float64,1000,1000,100);
    close(fr);
    #return D;
end
@elapsed x=read_binary()





#3a.
#Testing
using Base.Test
@test_approx_eq(1.0,1.001)
@test 7>5

#Testing if the elements of the written array are same as the array it reads.

#Ascii files

Aw=write_to_file()
Ar=read_from_file()
using Base.Test
for i in 1:1000
    @test Aw[i]==Ar[i]   # testing the equivalence of the array elements.
end
print("Test successful")


#Binary files

Abw=write_binary()
Abr=read_binary()
using Base.Test
for i in 1:1000
    @test Abw[i]==Abr[i]
end
print("Test successful")

3b. Testing a pre condition, test if the file exist,
function read_from_file()
    fr=open("writefile.txt","r");
    C=readcsv(fr,Float64);
    close(fr);
    return fr
    end
f=read_from_file()
using Base.Test
@test f!=0   # Does the file exist? If it does, it passes test.

#Assert statements
function read_from_file()
    fr=open("writefile.txt","r");
    @assert fr!=0
    C=readcsv(fr,Float64);
    close(fr);
    return fr
    end


#3d.

#Testing whether the variance should use one pass or two pass algorithm.

function v_one(y::Array) # This function calculates variance of a given array by one pass method.
n = length(y);
sum=zero(y[1]);
ssqr= zero(y[1]);
for i in 1:n
ssqr=ssqr+y[i]*y[i];
sum=sum+y[i];
end;
var=(1/(n-1))*(ssqr-sum*sum/n);
return var; #output of this function.
end
    
    function v_two(y::Array) #this function gives the variance of an array calculated by two pass method.
n = length(y);
sum=zero(y[1]);
for j in 1:n
sum=sum+y[j];
end;
m1=sum/n;
v2= zero(y[1]);
for i in 1:n
v2=v2+(y[i]-m1)^2;
end;
var2=(1/(n-1))*v2;
return var2; #output
end

function cal_variance(N::Int) # main function deciding and calling which funtion to use for variance calculating. N is the size of the array which would be an input.
   srand(42);
true_mean = 10000.;
y = true_mean+randn(N);  # Creates an array of dimension N.
    if N>10^6             #If array size is bigger than 10^8 then it takes too much time. The program quits.
        println("Array size too big to compute it in a reasonable amount of time")
        elseif N>10^4              #If array size is bigger than 10^6, one pass takes smaller time and it's better to use this.
            variance=v_one(y)
        println("Used one pass")
        else                                # If array size is smaller than 10^6, two pass is better as it gives more accuracy.
            variance=v_two(y)
        println("Used two pass")
        end
 return variance; # output. Gives an error whenarray size is greater tha 10^8
end
 
