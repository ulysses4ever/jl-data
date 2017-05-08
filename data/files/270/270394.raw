#=
Este código é referente ao exercício 2 da lista 2 da disciplina Tópicos Especiais em Banco de Dados VI.

Implementar o IR-SVD
=#

using MLBase

const y = 0.005
const lambda = 0.02
const k = 5
const qtd_treinamentos = 10

# Mudando a pasta atual do Julia para a pasta deste arquivo
cd(dirname(Base.source_path()))

# Lendo as notas do arquivo
avaliacoes = readdlm("ml-100k/u.data")

# Calcula a quantidade de notas
qtd_avaliacoes = size(avaliacoes,1)

# Separa o conjunto em 80% para treinamento e 20% para teste
ind_treinamento = collect(RandomSub(qtd_avaliacoes,qtd_avaliacoes*0.8,1))[1]
ind_teste = setdiff([1:qtd_avaliacoes],ind_treinamento)

# Parâmetros do IR-SVD
b_i = rand(1,convert(Int64,maximum(avaliacoes[:,2])))
b_u = rand(1,convert(Int64,maximum(avaliacoes[:,1])))
q_i = rand(k,convert(Int64,maximum(avaliacoes[:,2])))
p_u = rand(k,convert(Int64,maximum(avaliacoes[:,1])))
media = mean(avaliacoes[ind_treinamento,3])

# Realiza o treinamento
for it = 1:qtd_treinamentos
  for i = ind_treinamento
    usuario = avaliacoes[i,1]
    item = avaliacoes[i,2]
    nota = avaliacoes[i,3]
    nota_prevista = media + b_i[item] + b_u[usuario] + q_i[:,item]'*p_u[:,usuario]
    b_i[item] = b_i[item] + y*((nota - nota_prevista[1]) - lambda*b_i[item])
    b_u[usuario] = b_u[usuario] + y*((nota - nota_prevista[1]) - lambda*b_u[usuario])
    q_i[:,item] = q_i[:,item] + y*((nota - nota_prevista[1])*p_u[:,usuario] - lambda*q_i[:,item])
    p_u[:,usuario] = p_u[usuario] + y*((nota - nota_prevista[1])*q_i[:,item] - lambda*p_u[:,usuario])
  end
end

# Realizando os testes
erro = 0
for i = ind_teste
  usuario = avaliacoes[i,1]
  item = avaliacoes[i,2]
  nota = avaliacoes[i,3]
  nota_prevista = media + b_i[item] + b_u[usuario] + q_i[:,item]'*p_u[:,usuario]
  erro += abs(nota - nota_prevista)
end

mae = erro / length(ind_teste)
