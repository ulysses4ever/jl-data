#オイラー法
function f(t,x)
  x * (1-x)
end

#ルンゲ・クッタ法
function g(t,y)
  y*(1-y)
end

#ファイルへの書き込みのおまじない(writecsvとはあるけどどこにかけば。。。)
outputFile = "/Users/shinnosukesaitou/Dropbox/julia/result1.txt"
io = open(outputFile,"w")

#何回計算するか任意の値
n = 20000

#初期値
x = 0.01
y = 0.01
#刻み幅
dt = 0.001
dt1 = 0.001

for i =1:n

  #オイラー
  t = i*dt
  x = (1+dt)*x

  #ルンゲ・クッタ
  t1 = i*dt1
	k1 = g(t,y)
	k2 = g(t1 + dt1*0.5, y + k1*dt1*0.5)
	k3 = g(t1 + dt1*0.5, y + k2*dt1*0.5)
	k4 = g(t1 + dt1, y + k3*dt1)
	y += (k1 + 2*k2 + 2*k3 + k4)*dt1/6

  #ターミナルに出力
  println("t = $(t),x = $(x),y = $(y)")
  #ファイルへ書き込みioのあとに変数を記述
  println(io,t,',',x,',',y,',')
end

#最後に閉じる
close(io)

