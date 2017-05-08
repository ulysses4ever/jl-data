#=
	Módulo com a implementação de listas duplamente encadeadas genéricas

	@author Bernardo Pinto de Alkmim
=#

# Começo do módulo
module Name

	using Main

# Símbolos exportados
	export nulled,
		   ListElement, List,
		   createList # adicionar as funções aqui

# Define um valor nulo
	nulled = Nullable{Union()}()

# Tipos
	# Elemento de uma lista genérica
	type ListElement{T}
		value::T
		next::ListElement{T}
		previous::ListElement{T}

		# Construtor do elemento da lista
		ListElement{T}(v::T) = new(v, nulled, nulled)
	end

	# Cabeça de uma lista genérica
	type List{T}
		size::Int64
		current::ListElement{T}
		first::ListElement{T}
		last::ListElement{T}

		# Construtor da cabeça da lista
		List{T}() = new(0, nulled, nulled, nulled)
	end

# Funções

	#=
		Inserir no começo
			Insere um nó no começo de uma lista, tornando-o novo corrente.
		
		@param l Cabeça da lista na qual o nó será inserido.
		@param v Valor do nó a ser inserido.
		@return Booleano dizendo se a operação foi realizada com sucesso ou não.
	=#
	function insertFirst(l::List{T}, v::T)
		if l == nulled || v == nulled
			return false
		end

		newElem = ListElement{T}(v)
		newElem.next = l.first

		l.first.previous = newElem
		l.first = newElem
		l.current = newElem
		l.size = l.size + 1
		return true
	end

	#=
		Inserir
			Insere um nó após o corrente de uma lista, tornando-o novo corrente.

		@param l Cabeça da lista na qual o nó será inserido.
		@param v Valor do nó a ser inserido.
		@return Booleano dizendo se a operação foi realizada com sucesso ou não.
	=#
	function insert(l::List{T}, v::T)
		if l == nulled || v == nulled
			return false
		end

		newElem = ListElement{T}(v)
		newElem.previous = l.current
		newElem.next = l.current.next

		l.current.next.previous = newElem
		l.current.next = newElem
		l.current = newElem
		l.size = l.size + 1
		return true
	end

	#=
		Inserir no fim
			Insere um nó no fim de uma lista, tornando-o novo corrente.

		@param l Cabeça da lista na qual o nó será inserido.
		@param v Valor do nó a ser inserido.
		@return Booleano dizendo se a operação foi realizada com sucesso ou não.
	=#
	function insertLast(l::List{T}, v::T)
		if l == nulled || v == nulled
			return false
		end

		newElem = ListElement{T}(v)
		newElem.previous = l.last.previous

		l.last.next = newElem
		l.last = newElem
		l.current = newElem
		l.size = l.size + 1
		return true
	end

	#=
		Funções:
		buscar elemento
		obter valor do corrente
		alterar elemento corrente
		remover elemento corrente
		mudar corrente:
			mover para o próximo
			mover apra o anterior
			mover para o início
			mover para o final
		destruir lista
	=#

	#=
		Esvaziar lista
			Remove todos os elementos da cabeça da lista.

		@param l Lista a ser esvaziada.
		@return Booleano dizendo se a operação foi realizada com sucesso.
	=#
	function emptyList(l)
		if l == nulled
			return false
		end

		# TODO
		return true
	end

end
# Fim do módulo