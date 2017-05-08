using ScatterMatrixPlots,DataFrames
using Base.Test

# write your own tests here
@test 1 == 1

#データセット作成
x=1:10
y1=2x
y2=2x-1
label1=["a","a","a","b","b","b","b","c","c","c"]
label2=["1","2","3","1","2","3","1","2","3","1"]
df1=DataFrame(x=x,y1=y1,y2=y2,label1=label1)
df2=DataFrame(x=x,y1=y1,y2=y2,label1=label1,label2=label2)

#ファイル表示まで一括
ScatterMatrixPlot(df1)
ScatterMatrixPlot(df1, colorido="label1")
ScatterMatrixPlot(df2)
ScatterMatrixPlot(df2, colorido="label1")


#個別指示
pl=ScatterMatrix(df1, colorido="label1")
image=draw(SVG("scattermatrixplot.svg", 10inch, 10inch), pl)
open_imagefile("scattermatrixplot.svg")
