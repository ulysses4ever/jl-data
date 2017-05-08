#This is a script to test if my operator J (from game theory CE -> NE)
#is nonexpansive

w=0
x=0
y=0
z=0
a=0
b=0
c=0
d=0


n=0
nhead = for n = 1:10^6
    w=rand()
    x=(1-w)*rand()
    y=(1-w-x)*rand()
    z=(1-w-x-y)

    a=rand()
    b=(1-a)*rand()
    c=(1-a-b)*rand()
    d=(1-a-b-c)

    X=[w,x,y,z]
    Y=[a,b,c,d]
    JX=[(w+x)*(w+y),(w+y)*(y+z),(w+x)*(x+z),(x+z)*(y+z)]
    JY=[(a+b)*(a+c),(a+c)*(c+d),(a+b)*(b+d),(b+d)*(c+d)]

    if norm(JX-JY)>norm(X-Y)
        f=open("output.txt","a")
        write(f, "2-norm violated! \n ")
	write(f, "X: " * string(X) * "  Y: " * string(Y) * "\n")
        close(f)
    end

    if norm(JX-JY,1)>norm(X-Y,1)
        f=open("output.txt","a")
        write(f, "1-norm violated! \n ")
	write(f, "X: " * string(X) * "  Y: " * string(Y) * "\n")
        close(f)
    end
end
    
