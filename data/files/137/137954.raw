
import Base: done, next, start
import Distributions: Normal, rand

immutable Mutagenize
    itr::Homocount
    alph::Array

    Mutagenize(itr::Homocount, alph) = new(itr, collect(alph))
end

mutagenize(seq, alph) = join(Mutagenize(homocount(seq), alph))
mutagenize(seq) = mutagenize(seq, Set(seq...))

start(p::Mutagenize) = start(p.itr)

function next(p::Mutagenize, state)
    # taken from:
    # "Characteristics of 454 pyrosequencing data—enabling realistic
    # simulation with flowsim". Susanne Balzer, Ketil Malde, Anders Lanzén,
    # Animesh Sharma, and Inge Jonassen. Bioinformatics Vol. 26 ECCB 2010,
    # pages i420–i425. doi:10.1093/bioinformatics/btq365
    const errors = [ 
        Normal(0.1230, 0.0737),
        Normal(1.0193, 0.1227),
        Normal(2.0006, 0.1585),
        Normal(2.9934, 0.2188),
        Normal(3.9962, 0.3168),
        Normal(4.9550, 0.3863)
        ]
    # insertion
    c = p.alph[rand(1:length(p.alph))]
    n = int(round(rand(errors[1])))
    prefix = repeat(c, n)
    # body
    (c, n), s = next(p.itr, state)
    if n < length(errors)
        n = int(round(rand(errors[n + 1])))
    else
        n = int(round(rand(Normal(n, 0.03494 + n * 0.06856))))
    end
    body = repeat(c, n)
    # if we're at the end, then include potential terminal insertion
    if done(p.itr, s)
        c = p.alph[rand(1:length(p.alph))]
        n = int(round(rand(errors[1])))
        suffix = repeat(c, n)
        (prefix * body * suffix, s)
    else
        (prefix * body, s)
    end
end
   
done(p::Mutagenize, s) = done(p.itr, s)
