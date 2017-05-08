using ScatterMatrixPlots,DataFrames
using Base.Test

# write your own tests here
@test 1 == 1

#データセット作成
x=1:10
y1=2x
y2=2x-1
label=["a","a","a","b","b","b","b","c","c","c"]
df=DataFrame(x=x,y1=y1,y2=y2,label=label)

#ファイル表示まで一括
ScatterMatrixPlot(df, "label")

#個別指示
pl=ScatterMatrix(df, "label")
image=draw(SVG("scattermatrixplot.svg", 10inch, 10inch), pl)
open_imagefile("scattermatrixplot.svg")

