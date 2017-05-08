function writeASCII(x::ASCIIString,file_name)
        s = open(file_name,"w+");   # create the file
        write(s,x);         # write the ASCIIString to file
        #writecsv(s,x);
        close(s);
end

function readASCII(file_name)
        s = open(file_name,"r");
        readline(s);
        close(s);
end

