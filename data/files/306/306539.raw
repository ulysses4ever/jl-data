# Importando Julia Mathematical Progamming
Pkg.add("JuMP")
using JuMP

# Solver para mixed-integer
Pkg.add("Cbc")
using Cbc

# SimpleModel contém os dados para o problema de maximização
# de corte unidimensional de estoque com reaproveitamentos
# dos resíduos
type SimpleModel
  fracoes::Array{Int64,1}
  demanda::Array{Int64,1}
  result::Array{Int64,2}

  objectValue::Int64
  tam_barra::Int64
  num_barras::Int64

  SimpleModel() = new(zeros(1),zeros(1),zeros(1,1),0,0,0)
end

# Acha  solução otima, dado uma instancia de  SimpleModel como argumento
function simpleSolve(s::SimpleModel)
  # Primeiramente vamos definir o model
  # Utilizando o CbcSolver para resolver como inteiro
  m = Model(solver=CbcSolver())


  tam_pos = s.num_barras*size(s.fracoes)[1]
  num_var = size(s.fracoes)[1]

  # Criando as variaveis para a restrição
  @defVar(m, x[i=1:tam_pos], Int)
  @defVar(m, R , Int)

  # Adicionamos as restrição a primeira barra
  @defExpr(first, sum{s.fracoes[i]*x[i], i=1:num_var})
  addConstraint(m, first + R == s.tam_barra)

  # Adicionamos as restrições as demais barras
  for i = 1:(s.num_barras - 1)
    @defExpr(other, sum{s.fracoes[j]*x[j+ i*num_var], j=1:num_var})
    addConstraint(m, other <= s.tam_barra)
  end

  # Adicionamos as restrições por demanda
  for i = 1:num_var
    @defExpr(other, sum{x[i + j*num_var], j=0:(s.num_barras - 1)})

    addConstraint(m, other == s.demanda[i])
  end

  # Colocando todos maiores que zero
  for i = 1:tam_pos
    addConstraint(m, x[i] >= 0)
  end

  # Setamos R como nossa função objetiva
  @setObjective(m, :Max, R)

  # Checamos se o sistema pode ser resolvido
  status = solve(m)

  println(getObjectiveValue(m))
  println(getValue(x))
end


