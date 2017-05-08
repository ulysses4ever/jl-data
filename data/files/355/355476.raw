#=
01. 「パタトクカシーー」
「パタトクカシーー」という文字列の1,3,5,7文字目を取り出して連結した文字列を得よ．
=#

inputStr = "パタトクカシーー"
#文字が入っているのは1,4,7,10,13,...の形
combinedStr = ""

#Juliaのバグで複数バイトを利用する文字はバイト数がそのまま適用されてしまうため
#ひらがなであれば1文字3バイト利用することになる。
#2015/06/13現在、string.jl内にコメントで解決策は提示されている。
i = 1
strCount = 1
shiftInputStr = []
for c = 1:length(inputStr)
  readPoint = 1
  readbuf = inputStr.data[i]
  if (readbuf >= 0x60)
    readPoint = 3
  end
  shiftInputStr = union(shiftInputStr,inputStr[i])
  i += readPoint
  strCount += 1
end

for c in [1,3,5,7]
 print(shiftInputStr[c])
end
