module JDB
#= Indicate that the process making this request should be traced.
All signals received by this process can be intercepted by its
parent, and its parent can use the other `ptrace' requests.  =#
const PTRACE_TRACEME = 0
#= Return the word in the process's text space at address ADDR.  =#
const PTRACE_PEEKTEXT = 1
#= Return the word in the process's data space at address ADDR.  =#
const PTRACE_PEEKDATA = 2
#= Return the word in the process's user area at offset ADDR.  =#
const PTRACE_PEEKUSER = 3
#= Write the word DATA into the process's text space at address ADDR.  =#
const PTRACE_POKETEXT = 4
#= Write the word DATA into the process's data space at address ADDR.  =#
const PTRACE_POKEDATA = 5
#= Write the word DATA into the process's user area at offset ADDR.  =#
const PTRACE_POKEUSER = 6
#= Continue the process.  =#
const PTRACE_CONT = 7
#= Kill the process.  =#
const PTRACE_KILL = 8
#= Single step the process.
This is not supported on all machines.  =#
const PTRACE_SINGLESTEP = 9
#= Get all general purpose registers used by a processes.
This is not supported on all machines.  =#
const PTRACE_GETREGS = 12
#= Set all general purpose registers used by a processes.
This is not supported on all machines.  =#
const PTRACE_SETREGS = 13
#= Get all floating point registers used by a processes.
This is not supported on all machines.  =#
const PTRACE_GETFPREGS = 14
#= Set all floating point registers used by a processes.
This is not supported on all machines.  =#
const PTRACE_SETFPREGS = 15
#= Attach to a process that is already running. =#
const PTRACE_ATTACH = 16
#= Detach from a process attached to with const PTRACE_ATTACH.  =#
const PTRACE_DETACH = 17
#= Get all extended floating point registers used by a processes.
This is not supported on all machines.  =#
const PTRACE_GETFPXREGS = 18
#= Set all extended floating point registers used by a processes.
This is not supported on all machines.  =#
const PTRACE_SETFPXREGS = 19
#= Continue and stop at the next (return from) syscall.  =#
const PTRACE_SYSCALL = 24
#= Set ptrace filter options.  =#
const PTRACE_SETOPTIONS = 0x4200
#= Get last ptrace message.  =#
const PTRACE_GETEVENTMSG = 0x4201
#= Get siginfo for process.  =#
const PTRACE_GETSIGINFO = 0x4202
#= Set new siginfo for process.  =#
const PTRACE_SETSIGINFO = 0x4203
#= Get register content.  =#
const PTRACE_GETREGSET = 0x4204
#= Set register content.  =#
const PTRACE_SETREGSET = 0x4205
#= Like const PTRACE_ATTACH, but do not force tracee to trap and do not affect
signal or group stop state.  =#
const PTRACE_SEIZE = 0x4206
#= Trap seized tracee.  =#
const PTRACE_INTERRUPT = 0x4207
#= Wait for next group event.  =#
const PTRACE_LISTEN = 0x4208
const PTRACE_PEEKSIGINFO = 0x4209
const PTRACE_SEIZE_DEVEL = 0x80000000
const PTRACE_O_TRACESYSGOOD	= 0x00000001
const PTRACE_O_TRACEFORK	= 0x00000002
const PTRACE_O_TRACEVFORK   = 0x00000004
const PTRACE_O_TRACECLONE	= 0x00000008
const PTRACE_O_TRACEEXEC	= 0x00000010
const PTRACE_O_TRACEVFORKDONE = 0x00000020
const PTRACE_O_TRACEEXIT	= 0x00000040
const PTRACE_O_TRACESECCOMP = 0x00000080
const PTRACE_O_EXITKILL	= 0x00100000
const PTRACE_O_MASK		= 0x001000ff
const PTRACE_EVENT_FORK	= 1
const PTRACE_EVENT_VFORK	= 2
const PTRACE_EVENT_CLONE	= 3
const PTRACE_EVENT_EXEC	= 4
const PTRACE_EVENT_VFORK_DONE = 5
const PTRACE_EVENT_EXIT	= 6
const PTRACE_EVENT_SECCOMP  = 7

immutable PeekSigInfo
    off :: UInt64
    flags :: UInt32
    nr :: Int32
end

const PTRACE_PEEKSIGINFO_SHARED = 1


const UNW_X86_64_RAX = 0
const UNW_X86_64_RDX = 1
const UNW_X86_64_RCX = 2
const UNW_X86_64_RBX = 3
const UNW_X86_64_RSI = 4
const UNW_X86_64_RDI = 5
const UNW_X86_64_RBP = 6
const UNW_X86_64_RSP = 7
const UNW_X86_64_R8 = 8
const UNW_X86_64_R9 = 9
const UNW_X86_64_R10 = 10
const UNW_X86_64_R11 = 11
const UNW_X86_64_R12 = 12
const UNW_X86_64_R13 = 13
const UNW_X86_64_R14 = 14
const UNW_X86_64_R15 = 15
const UNW_X86_64_RIP = 16
#=const UNW_X86_64_XMM0,
const UNW_X86_64_XMM1,
const UNW_X86_64_XMM2,
const UNW_X86_64_XMM3,
const UNW_X86_64_XMM4,
const UNW_X86_64_XMM5,
const UNW_X86_64_XMM6,
const UNW_X86_64_XMM7,
const UNW_X86_64_XMM8,
const UNW_X86_64_XMM9,
const UNW_X86_64_XMM10,
const UNW_X86_64_XMM11,
const UNW_X86_64_XMM12,
const UNW_X86_64_XMM13,
const UNW_X86_64_XMM14,
const UNW_X86_64_XMM15=#


const unw = Libdl.dlopen("libunwind-generic", Libdl.RTLD_GLOBAL)
const unw_pt = Libdl.dlopen("libunwind-ptrace", Libdl.RTLD_GLOBAL)
const unw_x = Libdl.dlopen("libunwind-x86_64", Libdl.RTLD_GLOBAL)
const _UPT_accessors = Libdl.dlsym(unw_pt, :_UPT_accessors)
const unw_create_addr_space = Libdl.dlsym(unw, :_Ux86_64_create_addr_space)
const unw_init_remote = Libdl.dlsym(unw, :_Ux86_64_init_remote)
const unw_get_reg = Libdl.dlsym(unw, :_Ux86_64_get_reg)
const unw_get_proc_name = Libdl.dlsym(unw, :_Ux86_64_get_proc_name)
const unw_step = Libdl.dlsym(unw, :_Ux86_64_step)
const _UPT_create = Libdl.dlsym(unw_pt, :_UPT_create)


function ptrace(req, pid, addr, data)
    Libc.errno(0)
    res = ccall(:ptrace, UInt, (Cint, Cint, Int, Int), req, pid, addr, data)
    if Libc.errno() != 0
        throw(Libc.strerror(Libc.errno()))
    end
    res
end

include("dw.jl")

macro check(x)
    :(val = $x; if val < 0; error("Failed while ", $(string(x)), " : ", val); end; val)
end

# laid out as in user.h
immutable X64Regs
    r15 :: UInt64
    r14 :: UInt64
    r13 :: UInt64
    r12 :: UInt64
    rbp :: UInt64
    rbx :: UInt64
    r11 :: UInt64
    r10 :: UInt64
    r9 :: UInt64
    r8 :: UInt64
    rax :: UInt64
    rcx :: UInt64
    rdx :: UInt64
    rsi :: UInt64
    rdi :: UInt64
    orig_rax :: UInt64
    rip :: UInt64
    cs :: UInt64
    eflags :: UInt64
    rsp :: UInt64
    ss :: UInt64
    fs_base :: UInt64
    gs_base :: UInt64
    ds :: UInt64
    es :: UInt64
    fs :: UInt64
    gs :: UInt64
end
immutable UserMem
    regs :: X64Regs
end

const DWARF_TO_REG = [11, 13, 12, 6, 14, 15, 5, 20, 10, 9, 8, 7, 4, 3, 2, 1]
function dwarf_reg(r :: X64Regs, regnum)
    r.(DWARF_TO_REG[regnum+1])
end
function regname(n)
    Base.fieldname(X64Regs, n)
end
function dwarf_regname(n)
    if n+1 <= length(DWARF_TO_REG)
        regname(DWARF_TO_REG[n+1])
    else
        "dr$n"
    end
end
function Base.show(io::IO, r :: X64Regs)
    for fn = 1:nfields(r)
        @printf(io, "%s = %#x \n", regname(fn), r.(fn))
    end
end
immutable SymTable
    addrs :: Vector{UInt}
    syms
end
type ObjInfo
    name
    handle
    # a few sections
    symtab
    strtab
    sym_table :: SymTable
    # where is loaded
    offset
    # debug infos, one per CU
    dies
end
type ProcInfo
    obj
    symbol
    addr
    size
    die
    fde
    cu_die
end

Base.show(io::IO, d :: ObjInfo) = @printf(io, "(elf %s @ %#x)", d.name, d.offset)

type Session
    pid :: Cint
    objects :: Vector{ObjInfo} # first item is always /proc/self/exe
end

function Base.show(io::IO, s::Session)
    println(io, "Process ", s.pid, ":")
    for o in s.objects; println(io, "\t", o); end
end

Session(pid) = Session(pid, Array(ObjInfo,0))
function attach(pid)
    global current_session
    pid = convert(Cint, pid)
    ptrace(PTRACE_ATTACH, pid, C_NULL, C_NULL)
    s = Session(pid)
    current_session = s
    load_elf!(s, "/proc/$pid/exe")
    find_loaded_dsos!(s)
    s
end
function detach(s :: Session)
    ptrace(PTRACE_DETACH, pid, C_NULL, C_NULL)
end
cont() = cont(current_session::Session)
function cont(s :: Session)
    ptrace(PTRACE_CONT, s.pid, C_NULL, C_NULL)
end
function kill(s :: Session, sig)
    sig = convert(Cint, sig)
    @check ccall(:kill, Cint, (Cint,Cint), s.pid, sig)
end
stop() = stop(current_session::Session)
stop(s :: Session) = kill(s, 23)

immutable UnwCursor
    data :: NTuple{140, UInt64}
end

const addrspace = ccall(unw_create_addr_space, Ptr{Void}, (Ptr{Void}, Ptr{Void}), _UPT_accessors, C_NULL)

bt() = bt(current_session::Session)

function is_stopped(s :: Session)
    stat = Ref{Cint}()
    res = 0
    while res == 0
        res = ccall(:waitpid, Cint, (Cint, Ref{Cint}, Cint), s.pid, stat, 1) # 1 == WNOHANG
        @show res
    end
    stat[] & 0xff == 0x7f
end

function peekmem(s::Session, addr::UInt, where)
    UInt(ptrace(where, s.pid, addr, C_NULL))
end

function bt(s::Session)
    was_stopped = is_stopped(s)
    if !was_stopped
        stop(s)
    end
    ui = ccall(_UPT_create, Ptr{Void}, (Cint,), s.pid)
    cur = Ref{UnwCursor}()

    @check ccall(unw_init_remote, Cint, (Ref{UnwCursor}, Ptr{Void}, Ptr{Void}), cur, addrspace, ui)
    ripval = Ref{Clong}()
    while true
        @check ccall(unw_get_reg, Cint, (Ref{UnwCursor}, Clong, Ref{Clong}), cur, UNW_X86_64_RIP, ripval)
        rip = UInt64(ripval[])
        
        offsetval = Ref{Clong}()
        maxsz = 512
        buff = fill(0x0, maxsz)
        if ccall(unw_get_proc_name, Cint, (Ref{UnwCursor}, Ptr{UInt8}, Csize_t, Ref{Clong}), cur, buff, maxsz, offsetval) >= 0
            func = ASCIIString(buff[1:findfirst(buff,0)-1])
            offset = UInt64(offsetval[])
        else
            func = "???"
            offset = UInt64(0)
        end
        @printf("0x%x - %s + 0x%x\n", rip, func, offset)
        res = ccall(unw_step, Cint, (Ref{UnwCursor},), cur)
        if res <= 0
            break
        end
    end
    if !was_stopped
        cont(s)
    end
end

using ELF, DWARF

function load_elf!(s, name, offset = UInt(0))
    elf = ELF.readmeta(open(name, "r"), ELF.ELFHandle)
    sects = ELF.Sections(elf)
    symtab = nothing
    text = nothing
    #strtab = ELF.load_strtab(elf)
    for sect in sects
        sname = ELF.sectionname(sect)
        if sname == ".symtab"
            symtab = sect
        elseif sname == ".text"
            text = sect
        end
    end
    if symtab === nothing
        warn("no symtab in $name")
        symstrtab = nothing
    else
        symstrtab = ELF.strtab(ELF.Sections(elf)[symtab.header.sh_link+1])
    end
    if text === nothing
        warn("no text in $name")
    end
#=  
    @show dynamic_addr=#
    #ds = ELF.debugsections(elf)
    #ds, DIETrees(ds)
    starts = UInt[]
    syms = ELF.SymbolRef[]
    if symtab !== nothing
        for sym in ELF.Symbols(symtab)
            push!(starts, ELF.deref(sym).st_value)
            push!(syms, sym)
            #=if s.st_value <= addr - d.offset < s.st_value + s.st_size
            return sym
            end=#
        end
        p = sortperm(starts)
        permute!(starts, p)
        permute!(syms, p)
    end
    push!(s.objects, ObjInfo(name, elf, symtab, symstrtab, SymTable(starts,syms), offset, nothing))
    elf
end

function dies(d :: ObjInfo)
    if d.dies === nothing
        ds = ELF.debugsections(d.handle)
        dies = Any[]
        if ds.debug_info !== nothing
            dies = collect(collect(DIETrees(ds)))
        end
        d.dies = dies
    end
    d.dies
end

function find_sym(d :: ObjInfo, name :: String)
    for sym in ELF.Symbols(d.symtab)
        if ELF.symname(sym, strtab=d.strtab) == name
            return sym
        end
    end
    nothing
end
function find_sym_addr(d :: ObjInfo, name)
    UInt(ELF.deref(find_sym(d, name)).st_value)
end
function find_sym(d :: ObjInfo, addr :: UInt)
    d.symtab === nothing && return nothing
    addr -= d.offset
    i = searchsortedfirst(d.sym_table.addrs, addr)
    n = length(d.sym_table.addrs)
    if i <= n && d.sym_table.addrs[i] > addr
        i = i-1
    end
    if 1<=i<=length(d.sym_table.addrs)
        sym = d.sym_table.syms[i]
        s = ELF.deref(sym)
        if s.st_value <= addr < s.st_value + s.st_size
            return sym
        end
    end
    nothing
end
function attribute_by_name(x, name; required = false)
    as = DWARF.attributes(x)
    for a in as
        if a.name == name
            return a
        end
    end
    required && error("not found $(get(DWARF.DW_AT, name, name)))")
    nothing
end

low_pc_attr(d) = attribute_by_name(d, DWARF.DW_AT_low_pc)
high_pc_attr(d) = attribute_by_name(d, DWARF.DW_AT_high_pc)
function is_inside(d, ip)
    # TODO ranges
    a_lpc = attribute_by_name(d, DWARF.DW_AT_low_pc)
    a_hpc = attribute_by_name(d, DWARF.DW_AT_high_pc)
    if a_lpc !== nothing && a_hpc !== nothing
        lpc = convert(Int, a_lpc.content)
        hpc = convert(Int, a_hpc.content) + lpc
        return lpc <= ip < hpc
    end
    false
end
function proc_info(s :: Session, ip)
    for obj in s.objects
        proc_sym = find_sym(obj, ip)
        if proc_sym !== nothing
            return proc_info(obj, proc_sym, ip)
        end
    end
    warn("no symbol found for procedure at $ip")
    nothing
end
function proc_info(obj, proc_sym, ip)
    # symbol
    proc_addr = ELF.deref(proc_sym).st_value
    proc_sz = ELF.deref(proc_sym).st_size
    # DIE
    proc_die = nothing
    cu_die = nothing
    for die in dies(obj)
        @assert DWARF.tag(die) == DWARF.DW_TAG_compile_unit
        if is_inside(die, ip - obj.offset)
            # good CU
            for child in DWARF.children(die)
                if DWARF.tag(child) == DWARF.DW_TAG_subprogram
                    if is_inside(child, ip - obj.offset)
                        # good subprogram
                        proc_die = child
                        #=if low_pc != proc_addr
                            warn("DWARF and symbol disagree on procedure address : $low_pc vs $proc_addr")
                        end
                        if sz != proc_sz
                            warn("DWARF and symbol disagree on procedure size : $sz vs $proc_sz")
                        end=#
                        cu_die = die
                        break
                    end
                end
            end
        end
    end
    # FDE
    fr = read(ELF.debugsections(obj.handle), CallFrameInfo.FrameRecord)
    proc_fde = nothing
    for fde in fr.fdes
        fde_addr = CallFrameInfo.absolute_initial_loc(fde)
        fde_addr === nothing && continue
        fde_sz = fde.range
        
        if fde_addr <= ip - obj.offset < fde_addr+fde_sz
            # good fde
            proc_fde = fde
            if fde_addr != proc_addr
                warn("FDE and symbol disagree on proc addr : $fde_addr vs $proc_addr")
            end
            if fde_sz != proc_sz
                warn("FDE and symbol disagree on proc sz : $fde_sz vs $fde_addr")
            end
        end
    end
    ProcInfo(obj, proc_sym, proc_addr + obj.offset, proc_sz, proc_die, proc_fde, cu_die)
end

type RemoteMem <: IO
    s :: Session
    addr :: UInt
    where :: Int
end
RemoteMem(s::Session, where = :data) = RemoteMem(s, 0, where == :data ? PTRACE_PEEKDATA : where == :user ? PTRACE_PEEKUSER : error())
function Base.read(m::RemoteMem, ::Type{UInt})
    data = peekmem(m.s, m.addr, m.where)
    m.addr += sizeof(UInt)
    data
end
function Base.read(m::RemoteMem, ::Type{UInt8})
    align = WORD_SIZE >> 3
    msk = (-align) % UInt
    aligned = m.addr & msk
    rest = m.addr & ~msk
    data = peekmem(m.s, aligned, m.where)
    m.addr += 1
    (data >> (rest << 3)) % UInt8
end
Base.seek(m::RemoteMem, off) = m.addr = off

function regs(s::Session)
    m = RemoteMem(s, :user)
    reinterpret(X64Regs, read(m, UInt8, sizeof(X64Regs)))[1]
end

function find_r_debug(s)
    _DYNAMIC = find_sym_addr(s.objects[1], "_DYNAMIC")
    m = RemoteMem(s)
    seek(m, _DYNAMIC)
    while true
        token = read(m, UInt)
        val = read(m, UInt)
        if token == 0
            return UInt(0)
        elseif token == 0x15
            return val
        end
    end
    error()
end


function find_loaded_dsos!(s)
    r_debug = find_r_debug(s)
    m = RemoteMem(s)
    seek(m, r_debug)
    version = read(m, UInt)
    @assert(version == 1)
    link_map = read(m, UInt)
    while link_map != 0
        seek(m, link_map)
        #@show link_map
        l_addr, l_name, l_ld, next = read(m, UInt, 4)
        #@show l_addr, l_name, l_ld, next
        seek(m, l_name)
        path = ASCIIString(CallFrameInfo.read_cstring(m))
        if isfile(path)
            load_elf!(s, path, l_addr)
        end
        link_map = next
    end
end

immutable VarInfo
    name :: ASCIIString
    typ
    loc
end

function compute_var_locs(pi :: ProcInfo)
    d = Array(VarInfo, 0)
    for die in DWARF.children(pi.die)
        vi = compute_var_locs(pi, die)
        if vi !== nothing
            push!(d, vi)
        end
    end
    d
end

function dwarf_to_julia_type(d)
    enc_attr = attribute_by_name(d, DWARF.DW_AT_encoding)
    sz_attr = attribute_by_name(d, DWARF.DW_AT_byte_size)
    if sz_attr === nothing
        return "unknown type $(DWARF.DW_TAG[d.tree.self.tag])"
    end
    sz = convert(Int, sz_attr)
    if enc_attr !== nothing
        enc = convert(Int,enc_attr)
        if enc == DWARF.DW_ATE_signed # TODO more cases
            if sz == 4
                return (Int32,)
            elseif sz == 8
                return (Int64,)
            end
        end
    end
    return (UInt8, sz)
end

function compute_var_locs(pi::ProcInfo, die :: DWARF.DIETreeRef)
    tag = DWARF.tag(die)
    if tag == DWARF.DW_TAG_variable
#        @show die
        name_attr = attribute_by_name(die, DWARF.DW_AT_name)
        if name_attr === nothing
            warn("no name for variable $die")
            return nothing
        end
        varname = bytestring(name_attr, die.strtab)
#        @show varname name_attr
        locexpr = attribute_by_name(die, DWARF.DW_AT_location)
        typeref = attribute_by_name(die, DWARF.DW_AT_type)
        if isa(typeref, DWARF.Attributes.Reference4)
            typ = DWARF.deref(die, typeref)
            VarInfo(varname, dwarf_to_julia_type(typ), locexpr)
        else
            warn("unknown type ref $typeref")
            nothing
        end
    elseif tag == DWARF.DW_TAG_lexical_block
        # TODO
        nothing
    end
end

function fetch_dwarf_loc(s, r, typ, val)
    if isa(val, DWARF.Expressions.RegisterLocation)
        dwarf_reg(r, val.i)
    elseif isa(val, DWARF.Expressions.MemoryLocation)
        m = RemoteMem(s)
        seek(m, val.i)
        read(m, typ...)
    else
        error("unsupported $val")
    end
end

function fetch_cfi_value(s, r, val :: CallFrameInfo.Offset, cfa_addr)
    if !val.is_val
        fetch_dwarf_loc(s, r, (UInt,), DWARF.Expressions.MemoryLocation(convert(Int, val.n) + cfa_addr))
    else
        error("unsupported $val")
    end
end

type Frame
    session
    pi
    ip
    locals
    ret_addr
    cfa_addr
    rs
end
Base.bytestring(x::DWARF.Attributes.StringAttribute, y) = x.content
function get_reg_func(r, frame_base, cfa)
    function (n)
        if n == DWARF.DW_OP_fbreg
            frame_base === nothing ? error("request frame base but not provided") : frame_base
        elseif n == DWARF.DW_OP_call_frame_cfa
            cfa === nothing ? error("request cfa but not provided") : cfa
        else
            dwarf_reg(r, n)
        end
    end
end
function get_addr_func(offset)
    n -> n+offset
end
function dwarf_eval_loc(s, expr, r, frame_base = nothing, cfa = nothing, offset = nothing)
    DWARF.Expressions.evaluate_simple_location(DWARF.Expressions.StateMachine(Int[]), expr, get_reg_func(r, frame_base, cfa), x -> error("get word $x"), get_addr_func(offset), :NativeEndian)
end
function dwarf_eval(s, expr, r, frame_base = nothing, cfa = nothing, offset = nothing)
    sm = DWARF.Expressions.StateMachine(Int[])
    DWARF.Expressions.evaluate_generic(sm, expr, get_reg_func(r, frame_base, cfa),x -> error("get word $x"), get_addr_func(offset), :NativeEndian)
    last(sm.stack)
end
#=
function find_object(s :: Session, ip)
    for obj in s.objects
        for cu_die in obj.dies
            low = low_pc_attr(cu_die)
            low === nothing && continue
            high = high_pc_attr(cu_die)
            high === nothing && continue
            low = low.content; high = high.content
            high += low
            if low <= ip - obj.offset < high
                return obj
            end
        end
    end
    nothing
end
=#

frame(s :: Session) = frame(s, regs(s))
function frame(s :: Session, r :: X64Regs)
    pi = proc_info(s, r.rip)
    pi === nothing && return nothing
    # compute CFA
    beg = CallFrameInfo.absolute_initial_loc(pi.fde) + pi.obj.offset
    target_delta = r.rip - beg
    rs = CallFrameInfo.interpret!(pi.fde, target_delta)
    #@show r.rip rs
    local cfa_addr
    if isa(rs.cfa, Tuple{Int,Int})
        cfa_addr = convert(Int, dwarf_reg(r, rs.cfa[1]) + rs.cfa[2])
    else
        error("DWARF expr for CFA not supported yet")
    end
    ret_addr = fetch_cfi_value(s, r, rs[pi.fde.cie.return_reg], cfa_addr)
    #@show proc_info(d, ret_addr)
    res = nothing
    if pi.die !== nothing
        vis = compute_var_locs(pi)
        m = RemoteMem(s)
        res = Dict{String,Any}()
        for vi in vis
            loc = nothing
            if !isa(vi.typ, Tuple) # TODO should be !== nothing
                res[vi.name] = vi.typ
                continue
            end
            if isa(vi.loc, DWARF.Attributes.ExprLocAttribute)
                loc = vi.loc.content
            elseif isa(vi.loc, DWARF.Attributes.SectionOffset) # location list
                seek(ELF.debugsections(pi.obj.handle).debug_loc)
                loclist = read(pi.obj.handle.io, DWARF.LocationList{Int})
                loc_pc = low_pc_attr(pi.cu_die).content
                base = loc_pc
                for loc_entry in loclist.entries
                    if loc_entry.first <= r.rip - loc_pc < loc_entry.last
                        loc = loc_entry.data
                        break
                    end
                end
                if loc === nothing
                    warn("no location in loclist for $(vi.name)")
                end
            elseif vi.loc === nothing
                warn("no location for $(vi.name)")
            else
                error("Unsupported loc $(typeof(vi.loc))")
            end
            if loc == nothing
                res[vi.name] = nothing
                continue
            end
            #@show val vi cfa_addr
            local frame_base
            frame_base_mode = attribute_by_name(pi.die, DWARF.DW_AT_frame_base)
            if isa(frame_base_mode, DWARF.Attributes.ExprLocAttribute)
                frame_base = dwarf_eval(s, frame_base_mode.content, r, nothing, cfa_addr, pi.obj.offset)
            else
                error("unsupported frame base $frame_base_mode")
            end
            #@show frame_base
            #DWARF.Expressions.print_expression(STDOUT, Int, loc, :NativeEndian)
            #println()
            val = dwarf_eval_loc(s, loc, r, frame_base, cfa_addr, pi.obj.offset)
            res[vi.name] = fetch_dwarf_loc(s, r, vi.typ, val)
        end
    end
    Frame(s, pi, r.rip, res, ret_addr, cfa_addr, rs)
end

function proc_name(pi)
    ELF.symname(pi.symbol, strtab = pi.obj.strtab)
end

function Base.show(io::IO, f::Frame)
    ret_pi = proc_info(f.session, f.ret_addr)
    @printf(io, "frame: %s [%#x]\n", proc_name(f.pi), f.pi.addr)
    filename = "unknown file"
    if f.pi.cu_die !== nothing
        filename = bytestring(attribute_by_name(f.pi.cu_die, DWARF.DW_AT_name), f.pi.cu_die.strtab)
    end
    @printf(io, "  in %s from %s\n", filename, f.pi.obj.name)
    @printf(io, "  at +%#x (%#x) return to ", f.ip - f.pi.addr, f.ip)
    if ret_pi !== nothing
        @printf(io, "%s + %#x (%#x)\n", proc_name(ret_pi), f.ret_addr - ret_pi.addr, f.ret_addr)
    else
        @printf(io, "%#x (no symbol)\n", f.ret_addr)
    end
    if f.locals === nothing
        @printf(io, "  no debug info\n")
    else
        @printf(io, "  locals:\n")
        for (name,val) in f.locals
            @printf(io, "   %s = %s\n", name, val)
        end
    end
    println(io, "  register state relative to previous frame:")
    @printf(io, "   cfa = %s + %#x\n", dwarf_regname(f.rs.cfa[1]), f.rs.cfa[2])
    rr = 
    for (k, v) in f.rs.values
        if k == f.pi.fde.cie.return_reg
            @printf(io, "   ret = %s\n", v)
        else
            @printf(io, "   %s = %s\n", dwarf_regname(k), v)
        end
    end
end

function unwind_step(s, regs :: X64Regs, f :: Frame)
    nf = nfields(X64Regs)
    values = UInt[regs.(i) for i=1:nf]
    n_rip = 17
    values[n_rip] = f.ret_addr
    n_rsp = 20
    values[n_rsp] = f.cfa_addr
    for (reg,val) in f.rs.values
        if 0 <= reg < length(DWARF_TO_REG)
            values[DWARF_TO_REG[reg+1]] = fetch_cfi_value(s, regs, val, f.cfa_addr)
        end
    end
    new_regs = X64Regs(values...)
    (new_regs, frame(s, new_regs))
end

function unwind_all(s)
    r = regs(s)
    f = frame(s, r)
    @show f
    while true
        r, f = unwind_step(s, r, f)
        if f === nothing
            break
        end
        @show f
    end
end

end
#pid = parse(Int, ARGS[1])
#s = attach(pid)
#aaa(s)
