using LaTeX
import LaTeX: processdecl, processitem, isdecl, AbstractDecl

type Name <: AbstractDecl
    first::UTF8String
    surname::UTF8String
end
processdecl(n::Name) = """
\\firstname{$(n.first)}
\\familyname{$(n.surname)}"""

type ModernCVStyle <: AbstractDecl
    style::UTF8String
    colour::UTF8String
end
processdecl(s::ModernCVStyle) = """
\\moderncvstyle{$(s.style)}
\\moderncvcolor{$(s.colour)}"""

type Email <: AbstractDecl
    address::UTF8String
end
processdecl(e::Email) = """\\email{$(e.address)}"""

type Phone <: AbstractDecl
    number::UTF8String
end
processdecl(p::Phone) = """\\mobile{$(p.number)}"""

type CVEntry
    time::UTF8String
    place::UTF8String
    role::UTF8String
end
processitem(p, cv::CVEntry, indent) = ["""
\\cventry{$(replace(cv.time, r"–", "--"))}{$(cv.role)}{$(cv.place)}{}{}{}"""]

type CVItem
    desc::UTF8String
end
processitem(p, cv::CVItem, indent) = ["""
\\cvitem{}{$(cv.desc)}"""]

function texify(e::Experience)
    l = Any[CVEntry(e.time, e.at.name, e.role)]
    for desc in e.descs
        push!(l, CVItem(replace(replace(desc, "\$", "\\\$"), r"é", "\\'e")))
    end
    l
end

function texify(r::Résumé)
    docobjects = [
        DocumentClass("moderncv", ["12pt", "letterpaper", "sans"]),
        Name(split(r.name)[1], split(r.name)[2]),
        Email(r.email),
        Phone(r.phone),
        ModernCVStyle("casual", "burgundy"),
        Section("Objective", "Position as a."),
        Section("Skills", join(r.skills, ", "))]
    for (k, vs) in r.experience
        push!(docobjects, Section(k, map(texify, vs)))
    end
    document(docobjects)
end
