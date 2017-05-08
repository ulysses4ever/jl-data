using Intervalos
using IntervalMatrices
using FactCheck

facts ("Prueba-IntervalMatrices") do
    a=Interval(0,1)
    b=Interval(-3,2)
    c=Interval(-5,-1)
    d=Interval(-7,7)

    vn=[3 5]
    un=[1;2]
    M=[1 2;3 4]

    A=[a b;c d]
    B=[d c;b a]
    v=[a;b]
    u=[c;d]


    @fact v+u==[Interval(-5,0);Interval(-10,9)]=>true
    @fact u-v==[Interval(-5,-2);Interval(-4,5)]=>true
    @fact 5*u==u*5=>true
    @fact v/5==(1/5)*v=>true
    @fact (vn*u)[1]==Interval(-50,32)=>true

    @fact A+B==B+A=>true
    @fact M+A==A+M=>true
    @fact A-B==-(B-A)=>true
    @fact M*A==[Interval(-10,-1) Interval(-17,16);Interval(-20,-1) Interval(-37,34)]=>true
    @fact A*10==10*A=>true
    @fact A*un==[Interval(-6,5);Interval(-19,13)]=>true
    @fact M*A==A*M=>false

    @fact Midpoint(v)==[0.5;-0.5]=>true
    @fact Midpoint(A)==[0.5 -0.5;-3 0]=>true

    @fact Intersection(v,[Interval(0.5,1);Interval(-1,1)])==[Interval(0.5,1);Interval(-1,1)]=>true
    @fact one(Interval(-3,7))==Interval(1)=>true




end