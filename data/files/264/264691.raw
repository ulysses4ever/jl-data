# Protein Data Bank (PDB) format
# ==============================

import Base: readline, start, done, next

type State
    io::IO
    record::Symbol
    linen::Int
    # the number of ATOM/HETATM records
    n_atom_records::Int
    max_atom_serial::Int
    line::ASCIIString
    State(io::IO) = new(io, :Init, 0, 0, 0)
end

macro pdb_assert(ex, msg)
    quote
        @assert ex error("$($msg) (line:$($s.linen))")
    end
end

function readline(s::State)
    s.line = readline(s.io)
    s.linen += 1
    s.record = (
        beginswith(s.line, "HEADER") ? :HEADER :
        beginswith(s.line, "OBSLTE") ? :OBSLTE :
        beginswith(s.line, "TITLE ") ? :TITLE  :
        beginswith(s.line, "SPLIT ") ? :SPLIT  :
        beginswith(s.line, "CAVEAT") ? :CAVEAT :
        beginswith(s.line, "COMPND") ? :COMPND :
        beginswith(s.line, "SOURCE") ? :SOURCE :
        beginswith(s.line, "KEYWDS") ? :KEYWDS :
        beginswith(s.line, "EXPDTA") ? :EXPDTA :
        beginswith(s.line, "NUMMDL") ? :NUMMDL :
        beginswith(s.line, "MDLTYP") ? :MDLTYP :
        beginswith(s.line, "AUTHOR") ? :AUTHOR :
        beginswith(s.line, "REVDAT") ? :REVDAT :
        beginswith(s.line, "SPRSDE") ? :SPRSDE :
        beginswith(s.line, "JRNL  ") ? :JRNL   :
        beginswith(s.line, "REMARK") ? :REMARK :
        beginswith(s.line, "DBREF ") ? :DBREF  :
        beginswith(s.line, "DBREF1") ? :DBREF1 :
        beginswith(s.line, "DBREF2") ? :DBREF2 :
        beginswith(s.line, "SEQADV") ? :SEQADV :
        beginswith(s.line, "SEQRES") ? :SEQRES :
        beginswith(s.line, "MODRES") ? :MODRES :
        beginswith(s.line, "HET   ") ? :HET    :
        beginswith(s.line, "HETNAM") ? :HETNAM :
        beginswith(s.line, "HETSYN") ? :HETSYN :
        beginswith(s.line, "FORMUL") ? :FORMUL :
        beginswith(s.line, "HELIX ") ? :HELIX  :
        beginswith(s.line, "SHEET ") ? :SHEET  :
        beginswith(s.line, "SSBOND") ? :SSBOND :
        beginswith(s.line, "LINK  ") ? :LINK   :
        beginswith(s.line, "CISPEP") ? :CISPEP :
        beginswith(s.line, "SITE  ") ? :SITE   :
        beginswith(s.line, "CRYST1") ? :CRYST1 :
        beginswith(s.line, "ORIGX1") ? :ORIGX1 :
        beginswith(s.line, "ORIGX2") ? :ORIGX2 :
        beginswith(s.line, "ORIGX3") ? :ORIGX3 :
        beginswith(s.line, "SCALE1") ? :SCALE1 :
        beginswith(s.line, "SCALE2") ? :SCALE2 :
        beginswith(s.line, "SCALE3") ? :SCALE3 :
        beginswith(s.line, "MTRIX1") ? :MTRIX1 :
        beginswith(s.line, "MTRIX2") ? :MTRIX2 :
        beginswith(s.line, "MTRIX3") ? :MTRIX3 :
        beginswith(s.line, "MODEL ") ? :MODEL  :
        beginswith(s.line, "ATOM  ") ? :ATOM   :
        beginswith(s.line, "ANISOU") ? :ANISOU :
        beginswith(s.line, "TER   ") ? :TER    :
        beginswith(s.line, "HETATM") ? :HETATM :
        beginswith(s.line, "ENDMDL") ? :ENDMDL :
        beginswith(s.line, "CONECT") ? :CONECT :
        beginswith(s.line, "MASTER") ? :MASTER :
        beginswith(s.line, "END   ") ? :END    : :Unknown
    )
    s.line
end

type Title
    # HEADER
    classification::ASCIIString
    dep_date::ASCIIString
    idcode::ASCIIString
    # TITLE
    title::ASCIIString
    # OBSLTE
    rep_date::ASCIIString
    r_idcodes::Vector{ASCIIString}
    function Title(classification, dep_date, idcode, titles)
        new(classification, dep_date, idcode, titles)
    end
    function Title(classification, dep_date, idcode, titles, rep_date, r_idcodes)
        new(classification, dep_date, idcode, titles, rep_date, r_idcodes)
    end
end

isobsolete(t::Title) = isdefined(t, :rep_date)

type Remark
    remarks::Dict{Int,Vector{ASCIIString}}
end

type DBReference
    idcode::ASCIIString
    chainID::Char
    seqrange::UnitRange{Int}
    ins::(Char,Char)
    database::ASCIIString
    dbaccession::ASCIIString
    dbidcode::ASCIIString
    dbseqrange::UnitRange{Int}
    dbins::(Char,Char)
end

type PrimaryStructure
    dbref::Nullable{DBReference}
    seqres::Dict{Char,Vector{ASCIIString}}
end

function show(io::IO, primstr::PrimaryStructure)
    chains = sort(collect(keys(primstr.seqres)))
    n_chains = length(chains)
    print(io, "Primary Structure ($n_chains chains)")
    for chain in chains
        println(io)
        residues = primstr.seqres[chain]
        n_residues = length(residues)
        if n_residues > 4
            seq = join(vcat(residues[1:2], "...", residues[end-1:end]), "-")
        else
            seq = join(residues, "-")
        end
        print(io, " * $chain ($n_residues residues): $seq")
    end
end

type Het
    hetID::ASCIIString
    chainID::Char
    seqnum::Int
    icode::Char
    numhetatoms::Int
    text::ASCIIString
end

type Hetnam
    hetID::ASCIIString
    text::ASCIIString
end

type Heterogen
    hets::Vector{Het}
    hetnams::Vector{Hetnam}
end

type Atom
    hetero::Bool
    serial::Int
    name::ASCIIString
    altloc::Char
    resname::ASCIIString
    chainID::Char
    resseq::Int
    icode::Char
    x::Float32
    y::Float32
    z::Float32
    occupancy::Float32
    tempfactor::Float32
    element::Element
    charge::Float32
    anisou::Matrix{Int}  # optional

    # constructors
    Atom(hetero, serial, name, altloc, resname, chainID, resseq, icode, x, y, z, occupancy, tempfactor, element, charge) =
        new(hetero, serial, name, altloc, resname, chainID, resseq, icode, x, y, z, occupancy, tempfactor, element, charge)
    Atom(hetero, serial, name, altloc, resname, chainID, resseq, icode, x, y, z, occupancy, tempfactor, element, charge, anisou) =
        new(hetero, serial, name, altloc, resname, chainID, resseq, icode, x, y, z, occupancy, tempfactor, element, charge, anisou)
end

ishetero(a::Atom) = a.hetero

type Molecule
    name::ASCIIString
    seq::Int
    range::UnitRange{Int}
end

typealias Residue Molecule

type Chain
    chainID::Char
    residues::Vector{Residue}
    range::UnitRange{Int}
end

# Model - the core object to store coordinate data
# if a PDB entry has only one model, all ATOMs and HETATMs are stored in this object;
# otherwise a Model object stores coordinates between MODEL and ENDMDL records
type Model
    # model serial found in the MODEL record
    # if an entry has only one model and there is no MODEL record, this serial is set to 0
    serial::Int

    # chains terminated by a TER record
    chains::Vector{Chain}

    # molecules which aren't a monomer within a chain (e.g. metal ions, ligand, water, etc.)
    molecules::Vector{Molecule}

    # atoms found in ATOM/HETATM records
    # if there are multiple conformations, only the first occurring locations are
    # stored in this field: alternative locations are stored in altloc field (see below)
    atoms::Vector{Atom}

    # alternatives locations (key: serial of atoms, value: atoms found in alternative locations)
    altlocs::Dict{Int,Vector{Atom}}
end

function Model(serial::Int, chains::Vector{(Char,Vector{Atom})}, molecules::Vector{Atom})
    chains′ = Chain[]
    atoms′ = Atom[]
    altlocs′ = Dict{Int,Vector{Atom}}()
    for (chainID, atoms) in chains
        chain_start = endof(atoms′) + 1
        residues = read_mols!(atoms′, altlocs′, atoms, Residue)
        chain_stop = endof(atoms′)
        push!(chains′, Chain(chainID, residues, chain_start:chain_stop))
    end
    molecules′ = read_mols!(atoms′, altlocs′, molecules, Molecule)
    Model(serial, chains′, molecules′, atoms′, altlocs′)
end

function read_mols!{T<:Union(Molecule,Residue)}(dst, altlocs, src, ::Type{T})
    first_altloc_i = findfirst(a -> a.altloc != ' ', src)
    first_altloc = first_altloc_i > 0 ? src[first_altloc_i].altloc : '\0'
    mol_start = endof(dst) + 1
    mol_stop = endof(dst)
    mols = T[]
    for (i, atom) in enumerate(src)
        if atom.altloc == ' ' || atom.altloc == first_altloc
            if i > 1 && atom.resseq != src[i-1].resseq
                mol_stop = endof(dst)
                push!(mols, T(src[i-1].resname, src[i-1].resseq, mol_start:mol_stop))
                mol_start = mol_stop + 1
            end
            push!(dst, atom)
        else
            # this atom is in an alternative location
            if !haskey(altlocs, atom.serial)
                altlocs[atom.serial] = Atom[]
            end
            push!(altlocs[atom.serial], atom)
        end
    end
    if mol_stop < endof(dst)
        mol_stop = endof(dst)
        push!(mols, T(src[end].resname, src[end].resseq, mol_start:mol_stop))
    end
    mols
end

name(a::Atom) = a.name
name(r::Residue) = r.name
name(c::Chain) = c.chainID

type Coordinate
    models::Vector{Model}
end

type Connectivity
    connection::SparseMatrixCSC{Bool,Int}
end

isconnected(a::Atom, b::Atom) = connection[a.serial,b.serial] || connection[b.serial,a.serial]

type Entry
    title::Title
    remark::Remark
    primarystructure::PrimaryStructure
    coordinate::Coordinate
    connectivity::Connectivity
end

function show(io::IO, ent::Entry)
    println(io, "Protein: $(ent.title.classification) [$(ent.title.idcode)]")
    models = ent.coordinate.models
    print(io, "  $(length(models)) models")
    if length(models) == 1
        println(io)
        model = first(models)
        n_chains = length(model.chains)
        print(io, "  $n_chains chains - ")
        println(join(map(c -> c.chainID, model.chains), " "))
        print(io, "  $(length(model.atoms)) atoms")
    end
end


# Iterators
# ---------

type AtomIterator{T}
    model::Model
    view::T
end

start(::AtomIterator) = 1

eachatom(model::Model, atom::Atom) = AtomIterator(model, atom)
done(iter::AtomIterator{Atom}, i) = i > 1
next(iter::AtomIterator{Atom}, i) = iter.view, i + 1

eachatom{T<:Union(Molecule,Chain)}(model::Model, view::T) = AtomIterator(model, view)
done{T<:Union(Molecule,Chain)}(iter::AtomIterator{T}, i) = i > endof(iter.view.range)
next{T<:Union(Molecule,Chain)}(iter::AtomIterator{T}, i) = iter.model.atoms[iter.view.range[i]], i + 1

eachatom(model::Model) = AtomIterator(model, model)
done(iter::AtomIterator{Model}, i) = i > endof(iter.model.atoms)
next(iter::AtomIterator{Model}, i) = iter.model.atoms[i], i + 1

type MoleculeIterator{T}
    model::Model
    view::T
end

eachmol(model::Model, mol::Molecule) = MoleculeIterator(model, mol)
start(::MoleculeIterator{Molecule}) = 1
done(iter::MoleculeIterator{Molecule}, i) = i > 1
next(iter::MoleculeIterator{Molecule}, i) = iter.view, i + 1

eachmol(model::Model, chain::Chain) = MoleculeIterator(model, chain)
start(::MoleculeIterator{Chain}) = 1
done(iter::MoleculeIterator{Chain}, i) = i > endof(iter.view.residues)
next(iter::MoleculeIterator{Chain}, i) = iter.view.residue[i], i + 1

eachmol(model::Model) = MoleculeIterator(model, model)
start(::MoleculeIterator{Model}) = (1, 1)
done(iter::MoleculeIterator{Model}, ij) = ij[1] > endof(iter.view.chains) && ij[2] > endof(iter.view.molecules)
function next(iter::MoleculeIterator{Model}, ij)
    i, j = ij
    if i <= endof(iter.view.chains)
        # first, iterate through molecules (residues) within chains
        chain = iter.view.chains[i]
        mol = chain.residues[j]
        j += 1
        if j > endof(chain.residues)
            i += 1
            j = 1
        end
    else
        # second, iterate through molecules out of chains
        mol = iter.view.molecules[j]
        j += 1
    end
    return mol, (i, j)
end

type ChainIterator{T}
    model::Model
    view::T
end

start(::ChainIterator) = 1

eachchain(model::Model, chain::Chain) = ChainIterator(model, chain)
done(iter::ChainIterator{Chain}, i) = i > 1
next(iter::ChainIterator{Chain}, i) = iter.view, i + 1

eachchain(model::Model) = ChainIterator(model, model)
done(iter::ChainIterator{Model}, i) = i > endof(iter.model.chains)
next(iter::ChainIterator{Model}, i) = iter.model.chains[i], i + 1


# Parsers
# -------
#
# Every parser takes a current state and returns parsed object.
# Since a PDB entry is divided into several sections in its format specs, an entry parser
# is also separated into sub-parsers corresponding to each section:
#   * parse_title_section
#   * parse_remark_section
#   * parse_primary_structure_section
#   * parse_coodinate_section
# And each section parser calls record parsers contained in its section.
# The specs of the PDB file format can be found in:
#     "Atomic Coordinate Entry Format Description"  Version 3.3: July, 2011
#     http://www.wwpdb.org/documentation/file-format-content/format33/v3.3.html
# And other official documents about annotations:
#     "wwPDB Processing Procedures and Policies Document"
#     Section A: http://www.wwpdb.org/documentation/procedure  January 2014 Version 2.7
#     Section B: http://www.wwpdb.org/documentation/policy  April 2015 version 3.6
#
# PDB-101 would also help you understand the format:
#     http://www.rcsb.org/pdb/101/structural_view_of_biology.do

function parse_entry(io::IO)
    s = State(io)
    readline(s)
    title = parse_title_section(s)
    # TODO
    while s.record !== :REMARK; readline(s); end
    remark = parse_remark_section(s)
    primarystructure = parse_primary_structure_section(s)
    while s.record !== :ATOM && s.record !== :MODEL; readline(s); end
    coordinate = parse_coodinate_section(s)
    connectivity = parse_connectivity_section(s)
    parse_bookkeeping_section(s)
    @assert eof(s.io)
    Entry(title, remark, primarystructure, coordinate, connectivity)
end

# Title Section
# -------------

function parse_title_section(s)
    @assert s.record === :HEADER "the first record should be HEADER"
    classification, dep_date, idcode = parse_header(s)
    readline(s)
    obsolete = false
    if s.record === :OBSLTE
        rep_date, idcode′, r_idcodes = parse_obslte(s)
        @assert idcode′ == idcode "obsoleted idCode should match the header idCode (header: $idcode, obsoleted: $idcode′)"
        obsolete = true
    end
    titles = parse_title(s)
    obsolete ? Title(classification, dep_date, idcode, titles, rep_date, r_idcodes) :
               Title(classification, dep_date, idcode, titles)
end

function parse_header(s)
    # classification, depDate, idCode
    strip(s.line[11:50]), s.line[51:59], s.line[63:66]
end

function parse_obslte(s)
    rep_date = s.line[12:20]
    id_code = s.line[22:25]
    r_id_codes = ASCIIString[]
    while s.record === :OBSLTE
        for i in 32:5:72
            r_id_codes = s.line[i:i+3]
            r_id_codes == "    " && break
            push(r_id_codes, r_id_codes)
        end
        readline(s)
    end
    rep_date, id_code, r_id_codes
end

function parse_title(s)
    titles = ASCIIString[]
    while s.record === :TITLE
        push!(titles, rstrip(s.line[11:80]))
        readline(s)
    end
    join(titles)
end

# Remark Section
# --------------

parse_remark_section(s) = parse_remark(s)

function parse_remark(s)
    remarks = Dict{Int,Vector{ASCIIString}}()
    while s.record === :REMARK
        remarknum = int(s.line[8:10])
        if !haskey(remarks, remarknum)
            remarks[remarknum] = ASCIIString[]
        end
        push!(remarks[remarknum], s.line[12:79])
        readline(s)
    end
    Remark(remarks)
end

# Primary Structure Section
# -------------------------

function parse_primary_structure_section(s)
    if s.record === :DBREF
        while s.record === :DBREF
            dbref = Nullable(parse_dbref(s))
            readline(s)
        end
    else
        dbref = Nullable{DBReference}()
    end
    while s.record === :DBREF1 || s.record === :DBREF2
        # TODO
        readline(s)
    end
    while s.record === :SEQADV
        parse_seqadv(s)
        readline(s)
    end
    seqres = parse_seqres(s)
    while s.record === :MODRES
        parse_modres(s)
        readline(s)
    end
    PrimaryStructure(dbref, seqres)
end

function parse_dbref(s)
    idcode = s.line[8:11]
    chainID = s.line[13]
    seqbegin = int(s.line[15:18])
    insertbegin = s.line[19]
    seqend = int(s.line[21:24])
    insertend = s.line[25]
    database = strip(s.line[27:32])
    dbaccession = strip(s.line[34:41])
    dbidcode = strip(s.line[43:54])
    dbseqbegin = int(s.line[56:60])
    idbnsbeg = s.line[61]
    dbseqend = int(s.line[63:67])
    dbinsend = s.line[68]
    DBReference(
        idcode, chainID, seqbegin:seqend, (insertbegin,insertend),
        database, dbaccession, dbidcode, dbseqbegin:dbseqend, (idbnsbeg,dbinsend)
    )
end

function parse_seqadv(s)
    idcode = s.line[8:11]
    resname = strip(s.line[13:15])
    chainID = s.line[17]
    seqnum = int(s.line[19:22])
    icode = s.line[23]
    database = strip(s.line[25:28])
    dbaccession = strip(s.line[30:38])
    dbres = strip(s.line[40:42])
    dbseq = int(s.line[44:48])
    conflict = strip(s.line[50:70])
end

function parse_seqres(s)
    seqres = Dict{Char,Vector{ASCIIString}}()
    while s.record === :SEQRES
        current_chain = s.line[12]
        chain = s.line[12]
        numres = int(s.line[14:17])
        residues = ASCIIString[]
        while chain == current_chain
            sernum = int(s.line[8:10])
            for i in 20:4:68
                residue = s.line[i:i+2]
                residue == "   " && break
                push!(residues, residue)
            end
            readline(s)
            chain = s.line[12]
        end
        @assert length(residues) == numres
        seqres[current_chain] = residues
    end
    seqres
end

function parse_modres(s)
    idcode = s.line[8:11]
    resname = strip(s.line[13:15])
    chainID = s.line[17]
    seqnum = int(s.line[19:22])
    icode = s.line[23]
    stdres = strip(s.line[25:27])
    comment = strip(s.line[30:70])
end

# Heterogen Section
# -----------------

function parse_heterogen_section(s)
    hets = Het[]
    while s.record === :HET
        parse_het(s)
        readline(s)
    end
    while s.record === :HETNAM
        parse_hetnam(s)
        readline(s)
    end
end

function parse_het(s)
    hetID = strip(s.line[8:10])
    chainID = s.line[13]
    seqnum = int(s.line[14:17])
    icode = s.line[18]
    numhetatoms = int(s.line[21:25])
    text = strip(s.line[31:70])
    Het(hetID, chainID, seqnum, icode, numhetatoms, text)
end

function parse_hetnam(s)
    # TODO: continuation
    hetID = strip(s.line[12:14])
    text = rstrip(s.line[16:70])
    Hetnam(hetID, text)
end

# Coordinate Section
# ------------------

function parse_coodinate_section(s)
    models = Model[]
    @assert s.n_atom_records == 0
    while s.record === :MODEL || s.record === :ATOM
        multimodel = s.record === :MODEL
        if multimodel
            mserial = parse_model(s)
            readline(s)
        else
            mserial = 0
        end
        atoms = Atom[]
        chains = (Char,Vector{Atom})[]
        local atom::Atom
        while (multimodel && s.record !== :ENDMDL) || (!multimodel && !(s.record === :CONECT || s.record === :MASTER))
            if s.record === :ATOM || s.record === :HETATM
                atom = parse_atom(s)
                s.n_atom_records += 1
                s.max_atom_serial = max(atom.serial, s.max_atom_serial)
                push!(atoms, atom)
            elseif s.record === :ANISOU
                serial, name, altloc, resname, chainID, resseq, icode, mtx, element, charge = parse_anisou(s)
                # assuming an ATOM record is immediately followed by an associated ANISOU record
                @assert serial == atom.serial
                @assert name == atom.name
                @assert altloc == atom.altloc
                @assert resname == atom.resname
                @assert chainID == atom.chainID
                @assert resseq == atom.resseq
                @assert icode == atom.icode
                @assert element == atom.element
                @assert charge === atom.charge
                atom.anisou = mtx
            elseif s.record === :TER
                # end of a chain
                serial, resname, chainID, resseq, icode = parse_ter(s)
                @assert !isempty(atoms) "found TER record with no ATOM/HETATM records"
                @assert serial == atom.serial + 1
                @assert resname == atom.resname
                @assert chainID == atom.chainID
                @assert resseq == atom.resseq
                @assert icode == atom.icode
                push!(chains, (chainID, atoms))
                atoms = Atom[]
            else
                if multimodel
                    error("invalid record MODEL and ENDMDL: $(string(s.record))")
                else
                    error("invalid record before CONECT: $(string(s.record))")
                end
            end
            readline(s)
        end
        push!(models, Model(mserial, chains, atoms))
        if multimodel
            @assert s.record === :ENDMDL
            readline(s)
        end
    end
    Coordinate(models)
end

function parse_model(s)
    # model serial number
    int(s.line[11:14])
end

function parse_atom(s)
    hetero = s.record === :HETATM
    serial = int(s.line[7:11])
    name = strip(s.line[13:16])
    altloc = s.line[17]
    resname = strip(s.line[18:20])
    chainID = s.line[22]
    resseq = int(s.line[23:26])
    icode = s.line[27]
    x = float32(s.line[31:38])
    y = float32(s.line[39:46])
    z = float32(s.line[47:54])
    occupancy = float32(s.line[55:60])
    tempfactor = float32(s.line[61:66])
    element = parse_element(s.line[77:78])
    # e.g. 2+, 1-
    charge = s.line[79:80] == "  " ? NaN32 : float32(s.line[80:-1:79])
    Atom(hetero, serial, name, altloc, resname, chainID, resseq, icode,
         x, y, z, occupancy, tempfactor, element, charge)
end

parse_hetatm(s) = parse_atom(s)

function parse_anisou(s)
    serial = int(s.line[7:11])
    name = strip(s.line[13:16])
    altloc = s.line[17]
    resname = strip(s.line[18:20])
    chainID = s.line[22]
    resseq = int(s.line[23:26])
    icode = s.line[27]
    u00 = int(s.line[29:35])
    u11 = int(s.line[36:42])
    u22 = int(s.line[43:49])
    u01 = int(s.line[50:56])
    u02 = int(s.line[57:63])
    u12 = int(s.line[64:70])
    mtx = [u00 u01 u02;
           u01 u11 u12;
           u02 u12 u22]
    element = parse_element(s.line[77:78])
    charge = s.line[79:80] == "  " ? NaN32 : float32(s.line[80:-1:79])
    return serial, name, altloc, resname, chainID, resseq, icode, mtx, element, charge
end

function parse_ter(s)
    # serial, resName, chainID, resSeq, iCode
    int(s.line[7:11]), s.line[18:20], s.line[22], int(s.line[23:26]), s.line[27]
end

# Connectivity Section
# --------------------

function parse_connectivity_section(s)
    Connectivity(parse_conect(s))
end

function parse_conect(s)
    connection = spzeros(Bool, s.max_atom_serial, s.max_atom_serial)
    while s.record === :CONECT
        a = int(s.line[7:11])
        for i in 12:5:27
            num = s.line[i:i+4]
            num == "     " && break
            b = int(num)
            connection[a,b] = true
        end
        readline(s)
    end
    connection
end

# Bookkeeping Section
# -------------------

function parse_bookkeeping_section(s)
    parse_master(s)
    readline(s)
    parse_end(s)
end

function parse_master(s)
    # TODO: check
    n_remark = int(s.line[11:15])
    n_het = int(s.line[21:25])
    n_helix = int(s.line[26:30])
    n_sheet = int(s.line[31:35])
    # deprecated: n_turn = int(s.line[36:40])
    n_site = int(s.line[41:45])
    n_xform = int(s.line[46:50])
    n_coord = int(s.line[51:55])
    n_ter = int(s.line[56:60])
    n_conect = int(s.line[61:65])
    n_seq = int(s.line[66:70])
    # 148L doesn't match???
    #@assert s.n_atoms == n_coord
end

function parse_end(s)
    @assert s.record === :END
end
