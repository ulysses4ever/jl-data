
# ####################################################
# データ読み込みに関するいくつかの方法。
# ####################################################


# working directory の変更(このフォルダのなかに読み込みたいデータがある)。
cd("C:\\Users\\tetsuhiro.honda\\JuliaLangJP\\DataSet")

# working directory のファイル一覧を取得。
readdir()



# 1.tsvファイルを読み込む1 (読み込んだ後は Array)

# 参考サイト
# http://randyzwitch.com/julia-import-data/

iris_array = readdlm("iris.tsv", '\t', has_header = true)

	# 注意
	# ファイル名は、ダブルクォテーションで囲む
	# 区切り文字は、シングルクォテーションで囲む
	# ※クォートの違いがあるのは、文字列と文字リテラルが区別されるため


	# 第1配列にデータの配列、第2配列にヘッダの配列が格納されている

	# データ配列
	iris_array[1]

	# データ配列の要素を指定
	iris_array[1][1,2]

	# ヘッダの配列
	iris_array[2]

	# ヘッダの配列の要素を指定
	iris_array[2][3]



# 2.tsvファイルを読み込む2 (読み込んだ後は DataFrame)

# 参考サイト
# http://randyzwitch.com/julia-import-data/
# http://juliastats.github.io/DataFrames.jl/io.html

Pkg.add("DataFrames") 
using DataFrames

iris_df = readtable("iris.tsv", separator = '\t', header = true)

	# 数行表示
	head(iris_df)

	# 行数と列数
	size(iris_df)

	# Rでいうclass関数みたいなやつ。
	typeof(iris_df)



# 3.tsvファイルを一行ずつ読み込む


# 4.データベースにあるテーブルを読み込む


