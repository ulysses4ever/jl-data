#=
05. n-gram
与えられたシーケンス（文字列やリストなど）からn-gramを作る関数を作成せよ．
この関数を用い，"I am an NLPer"という文から単語bi-gram，文字bi-gramを得よ．
=#

function ngram(inputStr, mode)
  # inputStrをスペース区切りで単語に分けたものをsplitedInputStrに格納する。
  splitedInputStr = split(inputStr)
  wordCount = 1
  # modeがwなら単語bi-gramとする。
  if (mode == "w")
    for wordCount = 1:length(splitedInputStr)+1
      if (wordCount == 1)
        println(splitedInputStr[wordCount])
      elseif (wordCount == length(splitedInputStr)+1)
        println(splitedInputStr[wordCount-1])
      else
        println(splitedInputStr[wordCount-1], " ", splitedInputStr[wordCount])
      end
    end
  end
end

input = "I am an NLPer"
println("input:$input")
println("---Word bi-gram---")
ngram(input, "w")
