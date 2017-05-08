#=
        elseif x == 0xf2
        REPN
    elseif x == 0xf3
        REP
    elseif x == 0x2e
        CS
    elseif x == 0x36
        SS
    elseif x == 0x3e
        DS
    elseif x == 0x26
        ES
    elseif x == 0x64
        FS
    elseif x == 0x65
        GS
    elseif x == 0x66
        OP_SZO
    elseif x == 0x67
        AD_SZO
    else
        NO

const NO =     0x0000000000000000
const LOCK =   0x0000000000000001
const REPN  =  0x0000000000000010
const REP =    0x0000000000000100
const CS =     0x0000000000001000
const SS =     0x0000000000010000
const DS =     0x0000000000100000
const ES =     0x0000000001000000
const FS =     0x0000000010000000
const GS =     0x0000000100000000
const OP_SZO = 0x0000001000000000
const AD_SZO = 0x0000010000000000

const BR_NTAKEN = CS
const BR_TAKEN = DS
const BOUNDS = REPN
=#
module X
const regnames = ["ax", "cx", "dx", "bx", "sp", "bp", "si", "di",
                  "8", "9", "10", "11", "12", "13", "14", "15"]
reg_name(n) = regnames[n+1]
rex_w(rex) = (rex & 0x8) >> 3
rex_r(rex) = (rex & 0x4) >> 2
rex_x(rex) = (rex & 0x2) >> 1
rex_b(rex) = (rex & 0x1)
has_rex(rex) = rex != 0x0

const OP_NO = 0x0
const OP_E = 0x1
const OP_G = 0x2
const OP_INL = 0x3
const OP_I = 0x4
const OP_J = 0x5
const OP_CR0 = 0x6
const OP_CR1 = 0x7
const OP_CV1 = 0x8
const OP_M = 0x09
const S_v = 0x1
const S_b = 0x2
const S_z = 0x3
const S_p = 0x4
const S_w = 0x5
const F_NO_MODRM = 0x1
const F_MODRM_EXT = 0x2
immutable OpDesc
    op
    sz
end
OpDesc() = OpDesc(OP_NO, 0x0)
function OpDesc(spec::ASCIIString)
    op = 0x0
    if length(spec) == 0
        return OpDesc()
    end
    idx = findlast(c -> !isupper(c) && !isnumber(c), spec)
    d = if idx == 0
        spec
    else
        spec[1:idx-1]
    end
    op = if length(d) == 0
        OP_NO
    elseif d[1] == 'E'
        OP_E
    elseif d[1] == 'G'
        OP_G
    elseif d[1] == 'I'
        OP_I
    elseif d[1] == 'J'
        OP_J
    elseif d[1] == 'T'
        OP_INL
    elseif d[1] == 'G'
        OP_G
    elseif d[1] == 'M'
        OP_M
    elseif d[1] == 'C' && d[2] == 'R' # constant register
        if d[3] == '0'
            OP_CR0
        elseif d[3] == '1'
            OP_CR1
        else
            error()
        end
    elseif d[1] == 'C' && d[2] == 'V'
        if d[3] == '1'
            OP_CV1
        else
            error()
        end
    else
        error(d)
    end
    sz = if idx == 0
        0x0
    else
        d = spec[idx:end]
        if length(d) == 0
            0x0
        elseif d[1] == 'v'
            S_v
        elseif d[1] == 'b'
            S_b
        elseif d[1] == 'z'
            S_z
        elseif d[1] == 'p'
            S_p
        elseif d[1] == 'w'
            S_w
        else
            error(d)
        end
    end
    OpDesc(op, sz)
end
immutable InsnDesc
    name
    dst :: OpDesc
    src1 :: OpDesc
    src2 :: OpDesc
    flags :: UInt
end
#InsnDesc(name, dst::Tuple, src1::Tuple, src2::Tuple, rest...) = InsnDesc(name, OpDesc(dst...), OpDesc(src1...), OpDesc(src2...), rest...)
InsnDesc(name, d, s1, s2) = InsnDesc(name, d, s1, s2, 0)
InsnDesc(name, d :: ASCIIString, s1 :: ASCIIString, s2 :: ASCIIString, flags) = InsnDesc(name, OpDesc(d), OpDesc(s1), OpDesc(s2), flags)
const op1_table = Dict{UInt8,InsnDesc}()
const op2_table = Dict{UInt8,InsnDesc}()
const modrm_ext_table = Dict{UInt8,Vector{InsnDesc}}()
# "standard" instructions
for (bop, name) in [(0x00, "add"), (0x10, "adc"), (0x20, "and"), (0x30, "xor"),
                    (0x08, "or"),  (0x18, "sbb"), (0x28, "sub"), (0x38, "cmp")]
    op1_table[bop] = InsnDesc(name, "Eb", "Eb", "Gb")
    op1_table[bop+1] = InsnDesc(name, "Ev", "Ev", "Gv")
    op1_table[bop+2] = InsnDesc(name, "Gb", "Gb", "Eb")
    op1_table[bop+3] = InsnDesc(name, "Gv", "Gv", "Ev")
    op1_table[bop+4] = InsnDesc(name, "CR0b", "CR0b", "Ib", F_NO_MODRM)
    op1_table[bop+5] = InsnDesc(name, "CR0v", "CR0v", "Iz", F_NO_MODRM)
end
op1_table[0x88] = InsnDesc("mov", "Eb", "", "Gb")
op1_table[0x89] = InsnDesc("mov", "Ev", "", "Gv")
op1_table[0x8a] = InsnDesc("mov", "Gb", "", "Eb")
op1_table[0x8b] = InsnDesc("mov", "Gv", "", "Ev")
#TODO mov 0x8c
op1_table[0x8d] = InsnDesc("lea", "Gv", "Gv", "M")
# jumps
for (i, name) in enumerate(["jo", "jno", "jb", "jnb", "jz", "jnz", "jbe", "jnbe",
                            "js", "jns", "jp", "jnp", "jl", "jnl", "jle", "jnle"])
    op1_table[0x70 + i - 1] = InsnDesc(name, "", "", "Jb", F_NO_MODRM)
end
# instruction with inline reg
for (opc,name,args) in [(0x50, "push", ("", "Tv", "")),
                        (0x58, "pop", ("Tv", "", "")),
                        (0x90, "xchg", ("", "Tv", "CR0v")),
                        (0xb0, "mov", ("Tb", "", "Ib")),
                        (0xb8, "mov", ("Tv", "", "Iv"))]
    for act_opc = opc:opc+7
        op1_table[act_opc] = InsnDesc(name, args..., F_NO_MODRM)
    end
end
op1_table[0xe8] = InsnDesc("call", "", "", "Jz", F_NO_MODRM)
op1_table[0xe9] = InsnDesc("jmp", "", "", "Jz", F_NO_MODRM)
#op1_table[0xea] = InsnDesc("jmp", "", "", "Ap", F_NO_MODRM)
op1_table[0xeb] = InsnDesc("jmp", "", "", "Jb", F_NO_MODRM)
op1_table[0xf4] = InsnDesc("hlt", "", "", "", F_NO_MODRM)
op1_table[0xc2] = InsnDesc("ret", "", "", "Iw", F_NO_MODRM)
op1_table[0xc3] = InsnDesc("ret", "", "", "", F_NO_MODRM)
for (opc, name) in [(0x84, "test"), (0x86, "xchg")] # TODO support multiple output for xchg
    op1_table[opc] = InsnDesc(name, "", "Eb", "Gb")
    op1_table[opc+1] = InsnDesc(name, "", "Ev", "Gv")
end

# group 1
for i = 0:3
    opc = 0x80 + i
    modrm_ext_table[opc] = Array(InsnDesc, 8)
    op1_table[opc] = InsnDesc("group1", "", "", "", F_MODRM_EXT)
end
for (j, name) in enumerate(["add", "or", "adc", "sbb", "and", "sub", "xor", "cmp"])
    o1 = name == "cmp" ? "" : "Eb"
    o2 = name == "cmp" ? "" : "Ev"
    modrm_ext_table[0x80][j] = InsnDesc(name, o1, "Eb", "Ib")
    modrm_ext_table[0x81][j] = InsnDesc(name, o2, "Ev", "Iz")
    modrm_ext_table[0x82][j] = InsnDesc(name, o1, "Eb", "Ib")
    modrm_ext_table[0x83][j] = InsnDesc(name, o2, "Ev", "Ib")
end
# group 2
for i in (0xc0, 0xc1, 0xd0, 0xd1, 0xd2, 0xd3)
    modrm_ext_table[i] = Array(InsnDesc, 8)
    op1_table[i] = InsnDesc("group2", "", "", "", F_MODRM_EXT)
end
for (j, name) in enumerate(["rol", "ror", "rcl", "rcr", "shl", "shr", "shl", "sar"])
    modrm_ext_table[0xc0][j] = InsnDesc(name, "Eb", "Eb", "Ib")
    modrm_ext_table[0xc1][j] = InsnDesc(name, "Ev", "Ev", "Ib")
    modrm_ext_table[0xd0][j] = InsnDesc(name, "Eb", "Eb", "CV1b")
    modrm_ext_table[0xd1][j] = InsnDesc(name, "Ev", "Ev", "CV1b")
    modrm_ext_table[0xd2][j] = InsnDesc(name, "Eb", "Eb", "CR1b")
    modrm_ext_table[0xd3][j] = InsnDesc(name, "Ev", "Ev", "CR1b")
end
# group 5
op1_table[0xff] = InsnDesc("group5", "", "", "", F_MODRM_EXT)
modrm_ext_table[0xff] = Array(InsnDesc, 7)
for (opc, name, dst) in [(0,"inc", "Ev"), (1, "dec", "Ev"), (6, "push", "")]
    modrm_ext_table[0xff][opc+1] = InsnDesc(name, dst, "Ev", "")
end
for (opc, name) in [(2,"call"), (4, "jmp")]
    modrm_ext_table[0xff][opc+1] = InsnDesc(name, "", "Ev", "")
    modrm_ext_table[0xff][opc+2] = InsnDesc(name, "", "Ep", "")
end
# group 11
op1_table[0xc6] = InsnDesc("mov", "Eb", "", "Ib")
op1_table[0xc7] = InsnDesc("mov", "Ev", "", "Iz")

# 2-byte opcodes
    
op2_table[0x1f] = InsnDesc("nop", "", "", "") # TODO prefetch is also in there in group 16

immutable Reg
    n :: Int
end
immutable Imm
    v
end
immutable IpRel
    v
end
Base.show(io::IO, r::Reg) = print(io, reg_name(r.n))
function S_to_typ(s, op_typ)
    if s == S_b
        UInt8
    elseif s == S_z
        if op_typ == UInt16
            UInt16
        else
            @assert op_typ == UInt32 || op_typ == UInt64
            UInt32
        end
    elseif s == S_v
        op_typ
    else
        error(s)
    end
end
function go2(io :: IO)
    pfx1 = 0x0
    pfx2 = 0x0
    pfx3 = 0x0
    pfx4 = 0x0
    pfx_rex = 0x0
    while true
        x = read(io, UInt8)
        if x in (0xf0, 0xf2, 0xf3)
            pfx1 = x
        elseif x in (0x2e, 0x36, 0x3e, 0x26, 0x64, 0x65)
            pfx2 = x
        elseif x == 0x66
            pfx3 = x
        elseif x == 0x67
            pfx4 = x
        elseif (x & 0xf0) == 0x40 # only in long mode
            pfx_rex = x
            break
        else
            skip(io, -1)
            break
        end
    end
    @printf("legacy prefix = %#x %#x %#x %#x\n", pfx1, pfx2, pfx3, pfx4)
    if has_rex(pfx_rex)
        @printf("rex prefix = W:%d R:%d X:%d B:%d\n", rex_w(pfx_rex), rex_r(pfx_rex), rex_x(pfx_rex), rex_b(pfx_rex))
    end
    opcode1 = read(io, UInt8)
    @printf("opcode1 = %#x\n", opcode1)

    op_typ = UInt32
    if has_rex(pfx_rex)
        if rex_w(pfx_rex) != 0
            op_typ = UInt64
        elseif pfx3 == 0x66
            op_typ = UInt16
        end
    end
    addr_typ = UInt64
    if pfx4 == 0x67
        addr_typ = UInt32
    end

    opcode2 = 0x0
    desc = if opcode1 == 0x0f
        opcode2 = read(io, UInt8)
        @printf("opcode2 = %#x\n", opcode2)
        op2_table[opcode2]
    else
        op1_table[opcode1]
    end

    # read mod/rm & sib
    reg = nothing
    rm = nothing
    if (desc.flags & F_NO_MODRM) == 0
        modrm = read(io, UInt8)
        modrm_mod = (0xc0 & modrm) >> 6
        modrm_reg = (0x38 & modrm) >> 3
        modrm_rm = 0x7 & modrm
        modrm_disp = zero(UInt32)
        modrm_sib = zero(UInt8)
        
        modrm_reg_adj = modrm_reg
        modrm_rm_adj = modrm_rm
        if has_rex(pfx_rex)
            modrm_reg_adj = modrm_reg | (rex_r(pfx_rex) << 3)
            modrm_rm_adj = modrm_rm | (rex_b(pfx_rex) << 3)
        end

        reg = Reg(modrm_reg_adj)
        rm = nothing

        if modrm_rm == 0x4 && modrm_mod != 0x3
            modrm_sib = read(io, UInt8)
        end
        if modrm_mod == 0x0
            if modrm_rm == 0x5
                disp = read(io, UInt32) # RIP relative addressing
                rm = IpRel(disp)
            else
                rm = (:deref, Reg(modrm_rm_adj))
            end
        elseif modrm_mod == 0x1
            modrm_disp = UInt32(read(io, UInt8))
            rm = (:disp, modrm_rm)
        elseif modrm_mod == 0x2
            modrm_disp = read(io, UInt32)
            rm = (:disp, modrm_rm)
        elseif modrm_mod == 0x3
            rm = Reg(modrm_rm_adj)
        end
    end

    if (desc.flags & F_MODRM_EXT) != 0
        desc = modrm_ext_table[opcode1][modrm_reg + 1]
    end


    imm = nothing
    imm_typ = Void
    if desc.src2.op in (OP_I, OP_J)
        imm = read(io, S_to_typ(desc.src2.sz, op_typ))
    end 
    function read_operand(op)
        if op.op == OP_NO
            nothing
        elseif op.op == OP_E
            rm
        elseif op.op == OP_M
            @assert !isa(rm, Reg)
            rm
        elseif op.op == OP_G
            reg
        elseif op.op == OP_INL
            Reg((opcode1 & 0x07) | (rex_b(pfx_rex) << 3))
        elseif op.op == OP_I
            Imm(imm)
        elseif op.op == OP_J
            IpRel(imm)
        elseif op.op == OP_CR0
            Reg(0)
        elseif op.op == OP_CR1
            Reg(1)
        elseif op.op == OP_CV1
            Imm(0x1)
        else
            error("unknown op $op")
        end
    end
    dst = read_operand(desc.dst)
    src1 = read_operand(desc.src1)
    src2 = read_operand(desc.src2)

    name = desc.name
    print_with_color(:green, @sprintf("%s <- %s %s %s\n", dst, name, src1, src2))
end

function go(s::AbstractString, n = 5)
    io = open(s, "r")
    for i=1:n
        go2(io)
    end
end
end
