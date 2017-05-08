# ####################################################
# ファイル出力
# ####################################################


# working directory の変更(このフォルダのなかに出力したい)。
# path separatorは'\\'か、'/'
cd("C:\\Users\\daisuke.oda\\julia_test")

# working directory の確認
pwd()

# working directory のファイル一覧を取得。
readdir()


# 1.StandardLibraryを利用したファイル出力（用途小）

# 参考サイト
# http://julia.readthedocs.org/en/latest/stdlib/base/#i-o



# IOstreamをオープン
f = open("hello_julia.txt", "w")

# 出力
write(f, "Hello, Jilia!!")

# IOstreamをクローズ
close(f)


# 2.DataFrameを利用した出力

# ・DataFramesパッケージ
# https://github.com/JuliaStats/DataFrames.jl
# 
# 以下が可能になる
# ・NA型の利用
# ・欠損値を含む配列の利用（DataArray型）
# ・DataFrame型の利用
# 
# ・DataFrames I/Oの参考サイト
# http://juliastats.github.io/DataFrames.jl/io.html


# DataFramesパッケージのインストールとロード
Pkg.add("DataFrames") 
using DataFrames

# DataFrameの生成
df = DataFrame(A = 1:5, B = 101:105, C = ["a", "b", "c", "d", "abced"])

# tsv形式でファイル出力
writetable("df.tsv", df, quotemark = '\'', separator = '\t', header = true )

