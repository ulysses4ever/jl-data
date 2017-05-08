# c.f. Learn julia in Y Minutes ( http://learnxinyminutes.com/docs/julia/ )
#
# * 関数やマクロは、小文字・アンダースコアなしで命名する
#
# * 入力を変異させる関数には、名前の最後に「!」をつける e.g. increment!(x)



function add(x, y)
    x + y # 最後の文が評価されて戻り値となる
end

add(5, 6) # => 11

# 上の関数は、以下のように書くこともできる
add(x, y) = x + y

# 複数の戻り値を返すことも出来る
function foo(x, y)
    x+y, x-y
end



# 任意の数の引数をとる関数
function varargs(args...)
    return args # 「return」キーワードで、関数内のどこからでも戻り値を返すことが出来る
end

varargs("A","B","C") # => ("A","B","C")



# オプション引数の定義
function defaults(a,b,x=5,y=6)
    return "$a $b and $x $y"
end

defaults('h','g') # => "h g and 5 6"
defaults('h','g','j') # => "h g and j 6"
defaults('h','g','j','k') # => "h g and j k"
try
    defaults('h') # => ERROR: no method defaults(Char,)
    defaults() # => ERROR: no methods defaults()
catch e
    println(e)
end



# キーワード引数の定義
function keyword_args(;k1=4,name2="hello") # 「;」に注意
    return ["k1"=>k1,"name2"=>name2]
end

keyword_args(name2="ness") # => ["name2"=>"ness","k1"=>4]
keyword_args(k1="mine") # => ["k1"=>"mine","name2"=>"hello"]
keyword_args() # => ["name2"=>"hello","k1"=>4]



# 関数は第1級オブジェクト
# map, filterといった組み込みの高階関数がある
# リスト内包表記（List Comprehension）もある



# 多重ディスパッチ（Multiple Dispatch）
# 与えられた全ての引数の型に応じて関数が適用される
# c.f. The Design Impact of Multiple Dispatch
# http://nbviewer.ipython.org/gist/StefanKarpinski/b8fe9dbb36c1427b9f22

