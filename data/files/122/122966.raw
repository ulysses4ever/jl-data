"""Balance a list of chemical equations.

  The program takes as input from STDIN a list of strings representing chemical
  equations in standard form and returns strings of the balanced equations or
  explaining that the equation couldn't be solved by this program. 
  
  Usage:

  julia chem.jl < equations.txt

"""

module BalanceChemEquation
    using DataStructures
    using Iterators

    const ATOM_RE         = r"[A-Z][a-z]*"    # Match individual atom
    const INSIDE_RE       = r"\((.*)\)"       # Match interior of parenthesis
    const SINGLE_MOL_RE   = r"[A-z][a-z]*\d*" # Match a single molecule
    const NESTED_MOL_RE   = r"\((.*)\)\d*"    # Match a nested molecule
    const TRAILING_NUM_RE = r"\d+$"           # Match trailing coefficients

    """Extract trailing coefficient from a molecule string as integer."""
    function get_trailing_coef(atom::AbstractString)
        coef = match(TRAILING_NUM_RE, atom)
        coef != nothing ? parse(Int, coef.match) : 1
    end

    """Count each atom in a molecule and return it as a counter object."""
    function count_atoms(mols::Array)
        counts = counter(AbstractString)
        for mol in mols
            atom = match(ATOM_RE, mol)
            if atom != nothing
                atom = atom.match
                push!(counts, atom, get_trailing_coef(mol))
            end
        end
        counts
    end

    """Parse an individual molecule into counts of individual atoms. """
    function parsemol(mol::AbstractString)
        # Parse molecule into atom counts
        all_count = matchall(SINGLE_MOL_RE, mol) |> count_atoms

        leading_coef = match(r"^\d+", mol)
        scale = (leading_coef != nothing) ? parse(Int, leading_coef.match) : 1
        
        # Compute count for nested molecules (e.g. HO(SO)4 -> HO + 4SO)
        for token in matchall(NESTED_MOL_RE, mol)
            inside = match(INSIDE_RE, token).captures[1]

            coef = get_trailing_coef(token)

            # Remove double counts and add to nested total
            for (k, v) in parsemol(inside)
                push!(all_count, k, v * coef - all_count[k])
            end
        end

        # Return scaled molecule counts
        if scale != 1
            map(all_count) do x
                k, v = x
                k, v * scale
            end
        else
            all_count
        end
    end

    """Parse a section of a molecular equation. into a list of molecules,
    atoms, and counts.
    """
    function parsesection(section::AbstractString, separator="+")
        molecules = []
        atoms     = []
        counts    = []

        # Split section into molecules separated with an addition sign.
        for mol in imap(strip, split(section, separator))
            count = parsemol(mol)

            push!(molecules, mol)
            push!(counts, count)
            append!(atoms, map(first, count))
        end

        molecules, atoms, counts
    end

    function parse_equation(equation::AbstractString, separator="->")
        map(parsesection, split(equation, separator))
    end
    
    """Test wehther each value in basis is within epsilon of an integer."""
    function valid_integer_scale(s::Float64, basis::Array{Float64}, eps=eps())
        err = 0.0
        @simd for i in 1:endof(basis)
            v = s * basis[i]
            err += (v - round(v))^2
        end
        err < eps
    end

    """Brute-force search for integer solutions for a given basis."""
    function find_integer_solution(basis::Array{Float64}, max_iter::Int)
        for i in 1:max_iter
            for j in 1:endof(basis)
                t = i / basis[j]
                if valid_integer_scale(t, basis)
                    return t * basis
                end
            end
        end
        nothing
    end

    """Convert molecules and atom counts into a matrix.
    
    The chemical equation matrix is an M×N matrix where M is the number of
    molecules and N is the number of atoms. Each cell represents the total
    count of each atom in a molecule. 
    """
    function build_matrix(mols, atoms)
        mat = zeros(length(mols), length(atoms))
        @itr for (i, mol) in enumerate(map(Dict, mols))
            @itr for (j, atom) in enumerate(atoms)
                mat[i, j] = get(mol, atom, 0)
            end
        end
        mat
    end

    function balance_equation(equation::AbstractString)
        # Extract necessary data
        left, right = parse_equation(equation)
        lmolecules, latoms, lcounts = left
        rmolecules, ratoms, rcounts = right

        all_molecules = lmolecules ∪ rmolecules
        all_atoms = latoms ∪ ratoms

        # Convert system to homogeneous linear system
        system = [build_matrix(lcounts, all_atoms); 
                  -build_matrix(rcounts, all_atoms)]'

        # Solve system
        basis = nullspace(system)

        if 0 in size(basis)
            return "Cannot Solve."
        end

        solution = find_integer_solution(basis, 100000)

        if solution == nothing
            return "Cannot Solve."
        end

        # Add solution coefficients to final molecules
        molecule_counts = zip(solution, all_molecules)
        molecule_strings = map(molecule_counts) do x
            quantity, symbol = x
            quantity = round(Int, quantity)
            "$(quantity == 1 ? "" : quantity)$symbol"
        end

        N = length(lmolecules)
        left_result = join(molecule_strings[1:N], " + ")
        right_result = join(molecule_strings[N+1:end], " + ")

        "$left_result -> $right_result"
    end

    export balance_equation
end 

using BalanceChemEquation

for line in eachline(STDIN)
    sol = balance_equation(chomp(line))
    println(sol)
end
