using Base.Test
using Debug

# Simples implementação de um algoritmo de chave simétrica baseado em permutação

function extrai_ordem(cifra)
	cifra = split(cifra, "")
	cifra_ordenada = sort(cifra)
	ordem = Integer[]
	
	for c in cifra
		push!(ordem, findfirst(cifra_ordenada, c))
	end
	return ordem
end

@test extrai_ordem("hack") == [3,1,2,4]

function encrypt(text, key)
	retorno = String[]
	texto_quebrado = split(text, "")
	l_texto_quebrado = length(texto_quebrado)
	l_bloco = length(key)
	qtd_blocos = div(l_texto_quebrado, l_bloco) + (l_texto_quebrado%l_bloco>1?1:0)
	bloco_atual = 0
	while bloco_atual < qtd_blocos
		bloco = texto_quebrado[(bloco_atual*l_bloco+1):min((bloco_atual+1)*l_bloco, length(text))]
		while length(bloco) < l_bloco
			push!(bloco, "")
		end
		for (index, b) in enumerate(bloco)
			push!(retorno, bloco[key[index]])
		end
		bloco_atual += 1
	end
	return join(retorno, "")
end

@test encrypt("text", extrai_ordem("abcd")) == "text"
@test encrypt("text", extrai_ordem("acbd")) == "txet"
@test encrypt("Hello World", extrai_ordem("abcd")) == "Hello World"
@test encrypt("Hello World", extrai_ordem("hack")) == "lHelWo odrl"

@debug function decrypt(text, key)
	retorno = Array(String, length(text))
	texto_quebrado = split(text, "")
	l_texto_quebrado = length(texto_quebrado)
	l_bloco = length(key)
	qtd_blocos = div(l_texto_quebrado, l_bloco) + (l_texto_quebrado%l_bloco>1?1:0)
	bloco_atual = 0
	while bloco_atual < qtd_blocos
		bloco = texto_quebrado[(bloco_atual*l_bloco+1):min((bloco_atual+1)*l_bloco, length(text))]
		while length(bloco) < l_bloco
			push!(bloco, "")
		end
		for (index, b) in enumerate(bloco)
			offset = bloco_atual*l_bloco
			posicao_troca = offset + key[index]
			if (posicao_troca <= l_texto_quebrado)
				retorno[posicao_troca] = b
			end
		end
		bloco_atual += 1
	end
	return join(retorno, "")
end

ordem = extrai_ordem("hack")

@test decrypt(encrypt("Hello World", ordem), ordem) == "Hello World"