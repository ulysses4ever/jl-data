{\rtf1\ansi\ansicpg1252\cocoartf1187\cocoasubrtf400
{\fonttbl\f0\fswiss\fcharset0 Helvetica;\f1\fmodern\fcharset0 Courier;}
{\colortbl;\red255\green255\blue255;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural

\f0\fs24 \cf0 #Astro 585 Homework 3\
\
# 2a. Creating an array:\
srand(10)\
N=1024\
A=randn(N)\
\
# Time to print that:\
@elapsed x=A\
\pard\pardeftab720

\f1\fs28 \cf0 2.331e-6\
\

\f0 #2b. \
function write_to_file()\
    fin=open("writefile.txt","w+");\
    A=randn(1000);\
    writecsv(fin,A);\
    close(fin);\
    return A #Just to print the values of A to check later with the read in values.\
end\
\
\
#2b. \
function read_from_file()\
fr=open("writefile.txt","r");\
C=readcsv(fr,Float64);\
    close(fr);\
    return C\
end\
\
#2c.\
@elapsed x=write_to_file()\
#
\f1 0.006761774
\f0 \
@elapsed x=read_from_file()\
#
\f1 0.001323264\
#0.00121477\
#reduces slightly.\
\
#2d.\
function write_binary()\
    fin=open("writebinary.bin","w+");\
    B=randn(1000);\
    write(fin,B);\
    close(fin);\
    return B; #Just to print the values of A to check later with the read in values.\
end\
\
function read_binary()\
    fr=open("writebinary.bin");\
D=read(fr,Float64);\
    close(fr);\
    #return D;\
end\
\
#For a large matrix\
function write_binary()\
    fin=open("writebinary.bin","w+");\
    B=randn(1000,1000,100);\
    write(fin,B);\
    close(fin);\
    return B #Just to print the values of A to check later with the read in values.\
end\
@elapsed x=write_binary()\
\
function read_binary()\
    fr=open("writebinary.bin");\
D=read(fr,Float64);\
    close(fr);\
    #return D;\
end\
@elapsed x=read_binary()\
}


#2f.
function write_element()
    fin=open("write_element.txt","w+");
    A=randn(1000);
    writecsv(fin,A);
    close(fin);
    return A #Just to print the values of A to check later with the read in values.
end

function read_element(i::Int)
    fr=open("write_element.txt","r");
C=readcsv(fr,Float64);
    close(fr);
    return C[i]
end

function write_binary_element()
    fin=open("writebinaryelement.bin","w+");
    B=randn(1000);
    write(fin,B);
    close(fin);
    #return B; #Just to print the values of A to check later with the read in values.
end

function read_binary_element(i::Int)
    fr=open("writebinaryelement.bin","r+");
D=read(fr,Float64);
    close(fr);
    #return D[i];
end

@elapsed x=read_element(500)
@elapsed x=read_binary_element(500)
