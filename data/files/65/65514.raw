#=
	Módulo com a implementação de uma lista duplamente encadeada genérica

	Funções:
	criar lista
	inserir no começo
	inserir no fim
	inserir no corrente (após ele)
	alterar elemento corrente
	remover elemento corrente
	mudar corrente:
		mover para o próximo
		mover apra o anterior
		mover para o início
		mover para o final
	esvaziar lista
	destruir lista

	@author Bernardo Pinto de Alkmim
=#

# Elemento de uma lista genérica
type ListElement{T}
	value::T
	next::Nullable{ListElement{T}}
	previous::Nullable{ListElement{T}}
end

# Cabeça de uma lista genérica
type List{T}
	size::Int64
	current::Nullable{ListElement{T}}
	first::Nullable{ListElement{T}}
	last::Nullable{ListElement{T}}
end

