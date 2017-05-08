# # から改行まではコメント

# 平均値を計算する関数の定義
function mean(xs)
  sum = 0
  num = 0

  # いわゆる foreach 型のfor 文
  # x には xs の要素がひとつずつ順番にはいる
  for x in xs
    sum += x
    num += 1
  end
  # 最後に実行した式の値が関数の返り値になる
  sum/num
end
# すべてのブロックは end で終了

# 分散を計算する関数
function var(xs)
  sum  = 0
  sum2 = 0
  num  = 0
  for x in xs
    sum += x
    sum2 += x*x
    num += 1
  end
  # return を用いることで関数を抜け出せる
  # もちろん、今回は不要
  return (sum2/num - (sum/num)^2)*(num/(num-1))
end

# function mean_and_var(xs)
#   (mean(xs), var(xs))
# end
# と同義（糖衣構文）
# また、返り値を () で囲んで , で分ける（タプルにする）ことで
# 複数の返り値を同時に返すことが出来る（多値関数）
mean_and_var(xs) = (mean(xs),var(xs))

# 配列の初期化
# 型名 (Float64) そのものもオブジェクトであり、関数に渡せる
# なお、中身は初期化されない
N = 1000
xs = Array(Float64,N)

# 1:N は 1,2,3,...,N を表す Range 型の値を作る
# for 文に食わせると順番にi に入れられる
# また、配列のインデックスは 1 から始まる
for i in 1:N
  xs[i] = 0.0
end

T = 1000
for t in 0:T

  # 多値関数の受け取り
  m,v = mean_and_var(xs)

  # print は文字列を出力する関数
  # println は最後に改行をつける
  # 文字列の中では $var という形で、変数var の値を参照できる
  # 改行(\n) などのエスケープシーケンスももちろん使える
  print("$t $m $v\n")

  for i in 1:N

    # 条件分岐
    # rand() は 0 以上1 未満の一様乱数を64bit 浮動小数点数で返す
    if rand() < 0.5
      xs[i] += 1.0
    else
      xs[i] -= 1.0
    end
  end # end of for i
end # end of for t

