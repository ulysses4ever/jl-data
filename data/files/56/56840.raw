module X
const regnames = ["ra", "rc", "rd", "rb", "sp", "bp", "si", "di",
                  "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"]
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
const F_NEEDS_MODRM = 0x1
const F_MODRM_EXT = 0x2
const F_GENERIC = 0x4
immutable OpDesc
    op
    sz
end
function needs_modrm(op::OpDesc)
    op.op in (OP_E, OP_G, OP_M)#, OP_R)
end
function needs_imm(op::OpDesc)
    op.op in (OP_I, OP_J)
end
OpDesc() = OpDesc(OP_NO, 0x0)
isvalid(op::OpDesc) = op.op != OP_NO
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

immutable InsnDesc3AC
    name :: ASCIIString
    dst :: OpDesc
    src1 :: OpDesc
    src2 :: OpDesc
    flags :: UInt
end
dest_ops(i :: InsnDesc3AC) = (i.dst,)
src_ops(i :: InsnDesc3AC) = (i.src1, i.src2)
immutable InsnDescGen
    name :: ASCIIString
    dsts :: Vector{OpDesc}
    srcs :: Vector{OpDesc}
    flags :: UInt
end
dest_ops(i :: InsnDescGen) = i.dsts
src_ops(i :: InsnDescGen) = i.srcs

immutable InsnTable
    insn_3ac :: Vector{InsnDesc3AC}
    insn_gen :: Dict{UInt8, InsnDescGen}
end
function InsnTable(sz :: Int)
    tab_3ac = Array(InsnDesc3AC, sz)
    InsnTable(tab_3ac, Dict{UInt8, InsnDescGen}())
end
function Base.getindex(t::InsnTable, i)
    i3ac = t.insn_3ac[i+1]
    if i3ac.flags & F_GENERIC != 0
        t.insn_gen[i]
    else
        i3ac
    end
end
function needs_modrm(d :: InsnDesc3AC)
    needs_modrm(d.dst) | needs_modrm(d.src1) | needs_modrm(d.src2) |
    ((d.flags&F_MODRM_EXT) != 0) | ((d.flags&F_NEEDS_MODRM) != 0)
end
function needs_imm(d :: InsnDesc3AC)
    needs_imm(d.dst) | needs_imm(d.src1) | needs_imm(d.src2)
end
function imm_sz(d :: OpDesc)
    if needs_imm(d)
        d.sz
    else
        0
    end
end
function needs_modrm(d :: InsnDescGen)
    reduce(|, map(needs_modrm, d.dsts)) | reduce(|, map(needs_modrm, d.srcs)) | 
    ((d.flags&F_MODRM_EXT) != 0) | ((d.flags&F_NEEDS_MODRM) != 0)
end
function needs_imm(d :: InsnDescGen)
    reduce(|, map(needs_imm, d.dsts)) |
    reduce(|, map(needs_imm, d.srcs))
end
imm_sz(d :: InsnDesc3AC) = max(imm_sz(d.src1), imm_sz(d.src2), imm_sz(d.dst))
imm_sz(d :: InsnDescGen) = max(maximum(map(imm_sz, d.dsts)),
                               maximum(map(imm_sz, d.srcs)))
const op1_tab = InsnTable(256)
const op2_tab = InsnTable(256)
const modrm_ext_tab = Dict{UInt8,InsnTable}()
# OP_DS_S
# OP_D_S_S
# OP_D
# OP_S
function op_2ac!(tab, opc, name, dst_src1, src2, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(dst_src1), OpDesc(dst_src1), OpDesc(src2), flags)
end
function op_d_s!(tab, opc, name, dst, src, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(dst), OpDesc(src), OpDesc(), flags)
end
function op_s!(tab, opc, name, src, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(), OpDesc(src), OpDesc(), flags)
end
function op_2s!(tab, opc, name, src1, src2, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(), OpDesc(src1), OpDesc(src2), flags)
end
function op_3ac!(tab, opc, name, dst, src1, src2, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(dst), OpDesc(src1), OpDesc(src2), flags)
end
function op_0!(tab, opc, name, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(), OpDesc(), OpDesc(), flags)
end
function op_gen!(tab, opc, name, dsts, srcs, flags = 0)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(), OpDesc(), OpDesc(), F_GENERIC)
    tab.insn_gen[opc] = InsnDescGen(name, collect(map(OpDesc, dsts)), collect(map(OpDesc, srcs)), flags)
end
function ext_group!(tab, ext_tab, sz, opc, name)
    tab.insn_3ac[opc+1] = InsnDesc3AC(name, OpDesc(), OpDesc(), OpDesc(), F_MODRM_EXT)
    ext_tab[opc] = InsnTable(8)
end
ext_op_3ac!(tab, opc1, opc2, args...) = op_3ac!(tab[opc1], opc2, args...)
ext_op_2ac!(tab, opc1, opc2, args...) = op_2ac!(tab[opc1], opc2, args...)
ext_op_d_s!(tab, opc1, opc2, args...) = op_d_s!(tab[opc1], opc2, args...)
ext_op_s!(tab, opc1, opc2, args...) = op_s!(tab[opc1], opc2, args...)
# "standard" instructions
for (bop, name) in [(0x00, "add"), (0x10, "adc"), (0x20, "and"), (0x30, "xor"),
                    (0x08, "or"),  (0x18, "sbb"), (0x28, "sub"), (0x38, "cmp")]
    op_2ac!(op1_tab, bop+0, name, "Eb", "Gb")
    op_2ac!(op1_tab, bop+1, name, "Ev", "Gv")
    op_2ac!(op1_tab, bop+2, name, "Gb", "Eb")
    op_2ac!(op1_tab, bop+3, name, "Gv", "Ev")
    op_2ac!(op1_tab, bop+4, name, "CR0b", "Ib")
    op_2ac!(op1_tab, bop+5, name, "CR0v", "Iz")
end
op_d_s!(op1_tab, 0x88, "mov", "Eb", "Gb")
op_d_s!(op1_tab, 0x89, "mov", "Ev", "Gv")
op_d_s!(op1_tab, 0x8a, "mov", "Gb", "Eb")
op_d_s!(op1_tab, 0x8b, "mov", "Gv", "Ev")
# TODO 8c
op_2ac!(op1_tab, 0x8d, "lea", "Gv", "M")

# jumps
for (i, name) in enumerate(["jo", "jno", "jb", "jnb", "jz", "jnz", "jbe", "jnbe",
                            "js", "jns", "jp", "jnp", "jl", "jnl", "jle", "jnle"])
    op_s!(op1_tab, 0x70+i-1, name, "Jb")
    op_s!(op2_tab, 0x80+i-1, name, "Jz")
end
# instruction with inline reg
for (opc,name,args) in [(0x50, "push", ("", "Tv", "")),
                        (0x58, "pop", ("Tv", "", "")),
                        (0xb0, "mov", ("Tb", "", "Ib")),
                        (0xb8, "mov", ("Tv", "", "Iv"))]
    for act_opc = opc:opc+7
        op_3ac!(op1_tab, act_opc, name, args...)
    end
end
for act_opc = 0x90:0x90+7
    op_gen!(op1_tab, act_opc, "xchg", ("Tv", "CR0v"), ("Tv", "CR0v"))
end
op_s!(op1_tab, 0xe8, "call", "Jz")
op_s!(op1_tab, 0xe9, "jmp", "Jz")
#op_s!(op1_tab, 0xea, "jmp", "Ap")
op_s!(op1_tab, 0xeb, "jmp", "Jb")
op_0!(op1_tab, 0xf4, "hlt")
op_s!(op1_tab, 0xc2, "ret", "Iw")
op_0!(op1_tab, 0xc3, "ret")

for (opc, name) in [(0x84, "test"),]
    op_2s!(op1_tab, opc+0, name, "Eb", "Gb")
    op_2s!(op1_tab, opc+1, name, "Ev", "Gv")
end
op_gen!(op1_tab, 0x86, "xchg", ("Eb", "Gb"), ("Eb", "Gb"))
op_gen!(op1_tab, 0x86, "xchg", ("Ev", "Gv"), ("Ev", "Gv"))

# group 1
for i = 0:3
    opc = 0x80 + i
    ext_group!(op1_tab, modrm_ext_tab, 8, opc, "group1")
end
for (j, name) in enumerate(["add", "or", "adc", "sbb", "and", "sub", "xor", "cmp"])
    o1 = name == "cmp" ? "" : "Eb"
    o2 = name == "cmp" ? "" : "Ev"
    j = j-1
    ext_op_3ac!(modrm_ext_tab, 0x80, j, name, o1, "Eb", "Ib")
    ext_op_3ac!(modrm_ext_tab, 0x81, j, name, o2, "Ev", "Iz")
    #ext_op_3ac!(modrm_ext_tab, 0x82, j, name, o1, "Eb", "Ib") # TODO invalid
    ext_op_3ac!(modrm_ext_tab, 0x83, j, name, o2, "Ev", "Ib")
end
# group 2
for i in (0xc0, 0xc1, 0xd0, 0xd1, 0xd2, 0xd3)
    ext_group!(op1_tab, modrm_ext_tab, 8, i, "group2")
end
for (j, name) in enumerate(["rol", "ror", "rcl", "rcr", "shl", "shr", "shl", "sar"])
    j = j-1
    ext_op_2ac!(modrm_ext_tab,0xc0,j,name, "Eb", "Ib")
    ext_op_2ac!(modrm_ext_tab,0xc1,j,name, "Ev", "Ib")
    ext_op_2ac!(modrm_ext_tab,0xd0,j,name, "Eb", "CV1b")
    ext_op_2ac!(modrm_ext_tab,0xd1,j,name, "Ev", "CV1b")
    ext_op_2ac!(modrm_ext_tab,0xd2,j,name, "Eb", "CR1b")
    ext_op_2ac!(modrm_ext_tab,0xd3,j,name, "Ev", "CR1b")
end
# group 5
ext_group!(op1_tab, modrm_ext_tab, 7, 0xff, "group5")
for (opc, name, dst) in [(0,"inc", "Ev"), (1, "dec", "Ev"), (6, "push", "")]
    ext_op_d_s!(modrm_ext_tab,0xff,opc,name,dst, "Ev")
end
for (opc, name) in [(2,"call"), (4, "jmp")]
    ext_op_s!(modrm_ext_tab,0xff,opc,name,"Ev")
    ext_op_s!(modrm_ext_tab,0xff,opc+1,name,"Ep")
end

# group 11
op_d_s!(op1_tab, 0xc6, "mov", "Eb", "Ib")
op_d_s!(op1_tab, 0xc7, "mov", "Ev", "Iz")

# 2-byte opcodes

op_0!(op2_tab, 0x1f, "nop", F_NEEDS_MODRM) # TODO prefetch is also in there in group 16

immutable Reg
    n :: Int
end
immutable Imm
    v
end
immutable IpRel
    v
end
immutable Load
    base
    index
    scale
    disp
end
Base.show(io::IO, r::Reg) = print(io, reg_name(r.n))
Base.show(io::IO, r::Imm) = @printf(io, "imm(%#x)", r.v)
Base.show(io::IO, r::IpRel) = @printf(io, "*(ip + %#x)", r.v)
function Base.show(io::IO, r::Load)
    if r.scale == 0
        if r.disp == 0
            @printf(io, "*(%s)", r.base)
        else
            @printf(io, "*(%s + %#x)", r.base, r.disp)
        end
    else
        if r.disp == 0
            @printf(io, "*(%s + %d*%s)", r.base, r.scale, r.index)
        else
            @printf(io, "*(%s + %d*%s + %#x)", r.base, r.scale, r.index, r.disp)
        end
    end
end
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
    # read prefixes
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
        elseif (x & 0xf0) == 0x40 # TODO only in long mode
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

    # adjust operand & addr size
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
        op2_tab[opcode2]
    else
        op1_tab[opcode1]
    end

    # read mod/rm & sib
    reg = nothing
    rm = nothing
    if needs_modrm(desc)
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


        if modrm_mod != 0x3
            if modrm_rm == 0x4 # SIB
                modrm_sib = read(io, UInt8)
            end
            if modrm_mod == 0x0
                if modrm_rm == 0x5
                    modrm_disp = read(io, UInt32) # RIP relative addressing
                    rm = IpRel(disp)
                end
            elseif modrm_mod == 0x1
                modrm_disp = UInt32(read(io, UInt8))
            elseif modrm_mod == 0x2
                modrm_disp = read(io, UInt32)
            end
            if modrm_rm == 0x4 # SIB
                @show modrm_sib
                sib_scale = (modrm_sib & 0xc0) >> 6
                sib_index = (modrm_sib & 0x38) >> 3
                sib_base = modrm_sib & 0x7
                @show sib_scale sib_index sib_base
                # b i s d
                if has_rex(pfx_rex)
                    sib_base = sib_base | (rex_b(pfx_rex) << 3) # TODO sib_base == 5 special case
                    sib_index = sib_index | (rex_x(pfx_rex) << 3)
                end
                load_scale = 1 << sib_scale
                if sib_index == 0x4 # sp special case
                    load_scale = 0
                end
                @show sib_scale sib_index sib_base
                rm = Load(Reg(sib_base),Reg(sib_index),load_scale,modrm_disp)
            else
                rm = Load(Reg(modrm_rm_adj),0,0,modrm_disp)
            end
        else
            rm = Reg(modrm_rm_adj)
        end
    end

    if (desc.flags & F_MODRM_EXT) != 0
        desc = modrm_ext_tab[opcode1][modrm_reg]
    end


    imm = nothing
    imm_typ = Void
    if needs_imm(desc)
        imm = read(io, S_to_typ(imm_sz(desc), op_typ))
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
    
    d = map(read_operand, collect(filter(isvalid, dest_ops(desc))))
    s = map(read_operand, collect(filter(isvalid, src_ops(desc))))
    #=dst = read_operand(desc.dst)
    src1 = read_operand(desc.src1)
    src2 = read_operand(desc.src2)=#
    dest_s = isempty(d) ? "" : string(join(d, ", "), " <- ")
    src_s = join(s, ", ")
    name = desc.name
    print_with_color(:green, dest_s, name, " ", src_s, "\n")
end

function go(s::AbstractString, n = 5)
    io = open(s, "r")
    for i=1:n
        go2(io)
    end
end
end
