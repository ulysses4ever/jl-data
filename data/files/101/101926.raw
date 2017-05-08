function initializeBAMReader( filename::String )
    stream = GZip.open(filename)
    seek(stream, 0)
    if !checkBAMMagicString( stream )
        error("BAM magic string was not found!")
    end
    headerText = readBAMHeaderText( stream )
    references = readBAMHeaderReferences( stream )
    return( BAMReader( filename, stream, headerText, references ) )
end

function resetBAMReader( br::BAMReader )
    seek(br.stream, 0)
    if !checkBAMMagicString( br.stream )
        error("BAM magic string was not found!")
    end
    headerText = readBAMHeaderText( br.stream )
    references = readBAMHeaderReferences( br.stream )
    assert(headerText == br.headerText)
    assert(references == br.references)
end

function Base.string(x::Alignment)
    return "Alignment(" * string(x.readName) * ")"
end
Base.print(io::IO, x::Alignment) = print(io, string(x))
Base.show(io::IO, x::Alignment) = print(io, string(x))

function Base.string(x::BAMReader)
    return "BAMReader(" * string(x.stream) * ")"
end
Base.print(io::IO, x::BAMReader) = print(io, string(x))
Base.show(io::IO, x::BAMReader) = print(io, string(x))

function Base.string(x::CigarOperation)
    return "CigarOperation(" * string(x.opcode) * string(x.size) * " at " * string(x.interval) * ")"
end
Base.print(io::IO, x::CigarOperation) = print(io, string(x))
Base.show(io::IO, x::CigarOperation) = print(io, string(x))

function checkBAMMagicString( br )
    ret = Array(Uint8, 4)
    read(br, ret)
    return( char(ret) == ['B','A','M','\x01'] )
end

function readBAMHeaderText( br )
    headerLength = Array(Int32,1)
    read( br, headerLength )
    headerText = Array(Uint8, headerLength[1])
    read( br, headerText )
    return( UTF8String(headerText) )
end

function readBAMHeaderReferences( br )
    n_ref = read(br, Int32)
    ret = Array( BAMReference, n_ref )
    for i in 1:n_ref
        l_name = read(br, Int32)
        name = Array(Uint8,l_name)
        read(br, name)
        l_ref = read(br, Int32)
        ret[i] = BAMReference(UTF8String(name[1:(l_name-1)]), l_ref)
    end
    return(ret)
end

function getBAMheader( br )
    seek( br, 0 )
    if checkBAMMagicString( br )
        headerText = readBAMHeaderText( br )
        readBAMHeaderReferences( br )
    end
end

function processCigar( cigar, refID, pos )
    ret = Array(CigarOperation, length(cigar))
    for i in 1:length(cigar)
        size = (cigar[i] >>> 4)
        opcode = "MIDNSHP=X"[convert(Uint8, cigar[i]) & 15 + 1]
        if opcode in "MDN=X"
            ret[i] = CigarOperation( opcode, size, GenomicInterval( refID, pos, pos + size ) )
            pos += size
        else
            ret[i] = CigarOperation( opcode, size, GenomicInterval( refID, pos, pos ) )
        end
    end
    ret
end

function convertValueType( vt::Uint8, br::GZip.GZipStream )
    valueType = nothing
    if vt == 65 #Plain Char - 'A'
        return(Uint8, read(br, Uint8), sizeof(Uint8))
    elseif vt == 99 #int8 - 'c'
        return(Int8, read(br, Int8), sizeof(Int8))
    elseif vt == 67 #uint8 - 'C'
        return(Uint8, read(br, Uint8), sizeof(Uint8))
    elseif vt == 115 #int16 - 's'
        return(Int16, read(br, Int16), sizeof(Int16))
    elseif vt == 83 # uint16 - 'S'
        return(Uint16, read(br, Uint16), sizeof(Uint16))
    elseif vt == 105 # int32 - 'i'
        return(Int32, read(br, Int32), sizeof(Int32))
    elseif vt == 73 #uint32 - 'I'
        return(Uint32, read(br, Uint23), sizeof(Uint32))
    elseif vt == 102 #single precision float - 'f'
        return(Float32, read(br, Float32), sizeof(Float32))
    elseif vt == 90 #Printable String - 'Z'
        data = []
        byte = read(br, Uint8)
        while byte != 0
            data = vcat( data, byte )
            byte = read(br, Uint8)
        end
        return( Uint8, CharString(data), sizeof(Uint8)*length(data))
    elseif vt == 72 #Byte Array in Hex format - 'H'
        print("H")
    elseif vt == 66 #Integer or numeric array - 'B'
        print("B")
    else
        error("Typecode not found: " * string(vt))
    end
end

function readBlock( br::BAMReader )
    blockSize = read(br.stream, Int32)
    refID = read(br.stream, Int32)
    pos = read(br.stream, Int32)
    bin_mq_nl = read(br.stream, Uint32)
    bin = convert(Uint16,bin_mq_nl >>> 16)
    mapq = convert(Uint8,bin_mq_nl >>> 8)
    l_read_name = convert(Uint8,bin_mq_nl)
    flag_nc = read(br.stream, Uint32)
    flag = flag_nc >>> 16
    nCigar = convert(Uint16,flag_nc)
    l_seq = read(br.stream, Int32)
    next_refID = read(br.stream, Int32)
    next_pos = read(br.stream, Int32)
    tlen = read(br.stream, Int32)
    readName = Array(Uint8,l_read_name)
    read(br.stream, readName)
    cigar = Array(Uint32,nCigar)
    read(br.stream, cigar)
    cigar = processCigar( cigar, br.references[refID+1].name, pos )
    seq = Array( Uint8, convert( Uint32, ceil((l_seq+1) / 2) ) )
    read(br.stream, seq)
    seqmap = "=ACMGRSVTWYHKDBN"
    readseq = CharString([mapreduce( byte->[ seqmap[byte >>> 4 + 1], seqmap[byte & 15 + 1]], vcat, seq )])[1:l_seq]
    qual = Array(Uint8,l_seq)
    read(br.stream,qual)
    bytesLeft = blockSize - 9*4 - l_read_name - nCigar*4 - convert( Uint32, ceil((l_seq+1) / 2) ) - l_seq
    optionalFields = Dict()
    while bytesLeft >= 0
        tagvt = Array(Uint8, 3)
        read(br.stream, tagvt)
        tag = UTF8String(tagvt[1:2])
        vt, value, size = convertValueType(tagvt[3], br.stream)
        optionalFields[tag] = value
        bytesLeft -= 3 + size
    end
    return(Alignment(UTF8String(readName), flag, br.references[refID+1].name, pos, mapq, cigar, next_refID, next_pos, tlen, readseq, qual, optionalFields))
end
