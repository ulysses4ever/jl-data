#=
02. 「パトカー」＋「タクシー」＝「パタトクカシーー」
「パトカー」＋「タクシー」の文字を先頭から交互に連結して文字列「パタトクカシーー」を得よ．
=#

inputStrPatrolCar = "パトカー"
inputStrTaxi = "タクシー"
shiftInputStrPatrolCar = []
shiftInputStrTaxi = []

#=
  FunctionName:strSuffixFix
  Argument:inputStr_String
  return:shiftInputStr_char[]
  Detail:Julia has UTF-8 String suffix bug. This function is patch to the bug.
=#
function strSuffixFix(inputStr)
  i = 1
  shiftInputStr = []
  for c = 1:length(inputStr)
    readPoint = 1
    readbuf = inputStr.data[i]
    if (readbuf >= 0x60)
      readPoint = 3
    end
    shiftInputStr = union(shiftInputStr,inputStr[i])
    i += readPoint
  end
  return shiftInputStr
end

shiftInputStrTaxi = strSuffixFix(inputStrTaxi)
shiftInputStrPatrolCar = strSuffixFix(inputStrPatrolCar)
ansStr = ""
minStrLength = min(length(inputStrPatrolCar),length(inputStrTaxi))
for c = 1:minStrLength
  ansStr = string(ansStr, shiftInputStrPatrolCar[c])
  ansStr = string(ansStr, shiftInputStrTaxi[c])
end

println(ansStr)
