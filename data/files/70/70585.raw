plaintext=uppercase(replace("",(' '), ""))
key = [7,1,20,5,14,8,2,11,12,13,3,19,15,6,17,9,4,18,10,16]
ciphertext=uppercase(replace("sebt yuwi ytrr ortl rbon aluo konf ihye cyog rowh prhj feom ihos perp twnb tpak heoc yaui usoa irtd tnlu ntke onds goym hmpq",(' '),""))
function encrypt(plaintext::String,key)
        numOfRows = length(plaintext)/length(key)
        println("This should be a round number: ",numOfRows)
        CBlock=""
        CText=""
        i=0
        j=1
        while(j<=length(key))
                while(i<numOfRows)
                    offset=length(key)*i
                    CChar=plaintext[key[j]+offset]
                    CBlock=string(CBlock,CChar)
                    i=i+1
                end
                CText=string(CText," ",CBlock)
                CBlock=""
                i=0
                j=j+1
        end
        println(CText)
        return CText
end

function decrypt(ciphertext::String,key)
        PWork=Array(Char,length(ciphertext))
        i=1
        while(i<=length(ciphertext))
                PWork[i]='z'
                i=i+1
        end

        numOfRows = length(ciphertext)/length(key)
        println(numOfRows)
        PBlock=""
        PText=""
        i=0
        j=1
        keypos=1
        while(j<=length(ciphertext))

                while(i<numOfRows)
                    offset=length(key)*i
                    PWork[key[keypos]+offset]=ciphertext[j+i]
                    i=i+1
                end
                j=j+i
                i=0
                keypos=keypos+1
        end
        print(replace(string(PWork),("\n"),""))
        return PWork
end

function keyGen(input::String)
        phrase = uppercase(replace(input,(' '),""))
        key = Array(Int64, length(phrase))
        println(phrase)
        search='A'
        count=1
        i=1
        while(search!='Z')
            i=1
            while(i<=length(phrase))
                    if (phrase[i] == search)
                        key[i] = count
                        count=count+1
                    end
                    i=i+1
            end
            search=search+1
        end
        println(replace(string(key),("\n"),","))
        return key
 end
