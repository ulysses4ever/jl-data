function warmup(warmUp, obj, x, its, fvals, gNormVals)
    for i = 1:warmUp
        (f,g,H) = obj(x);
        (sigma, V) = eig(H)
        L = maximum(sigma)
        x = x - (1/L)*g

        its = its + 1;
        fvals = [fvals; f];
        gNormVals = [gNormVals; norm(g,2)];
    end
    return (x,its,fvals,gNormVals)
end

function newtstep1(obj,x,its,fvals,gNormVals)
    (f,g,H) = obj(x);

    #modify H if not pos def
    E = eigfact(H);
    V = E[:vectors];
    lambda = diagm(max(abs(E[:values]),1e-2));
    d = -V*inv(lambda)*transpose(V)*g;

    #backtracking linesearch
    alpha = 1;
    mu = 10^-2.0;
    (newf,newg,newH) = obj(x+alpha*d);
    while newf > f + (alpha*mu)*(dot(g,d))
        (newf, newg, newH) = obj(x + alpha*d);
        alpha = alpha/2;
    end

    x = x+alpha*d;

    its = its + 1;
    fvals = [fvals; f];
    gNormVals= [gNormVals; norm(g,2)];
    return(x,g,its,fvals,gNormVals);
end

function newtstep2(obj,x,its,fvals,gNormVals)
    (f,g,H) = obj(x);

    #modify H if not pos def
    E = eigfact(H);
    V = E[:vectors];
    lambda = diagm(max(E[:values],1e-2));
    d = -V*inv(lambda)*transpose(V)*g;

    #backtracking linesearch
    alpha = 1;
    mu = 10^-2.0;
    (newf,newg,newH) = obj(x+alpha*d);
    while newf > f + (alpha*mu)*(dot(g,d))
        (newf, newg, newH) = obj(x + alpha*d);
        alpha = alpha/2;
    end

    x = x+alpha*d;

    its = its + 1;
    fvals = [fvals; f];
    gNormVals= [gNormVals; norm(g,2)];
    return(x,g,its,fvals,gNormVals);
end

function BFGSstep(obj,x,B,its,fvals,gNormVals)
    (f,g,H) = obj(x);
    d = -B\g;


    #backtracking linesearch with Wolfe condition
    alpha = 1;
    mu = 10^-2.0;
    nu = 0.8;
    oldx = x;
    (oldf,oldg,oldH) = obj(x);
    (newf,newg,newH) = obj(x+alpha*d);
    alphaDir = 0;
    while newf > f + (alpha*mu)*(dot(g,d))
        (newf, newg, newH) = obj(x + alpha*d);
        alpha = alpha/2;
    end

    x = x+alpha*d;
    (f,g,H) = obj(x);
    q = alpha*B*d;
    y = g - oldg;
    s = x - oldx;

    B = B - (1/(transpose(q)*s)[1])*(q*transpose(q)) + (1/(transpose(y)*s)[1])*(y*transpose(y));

    its = its + 1;
    fvals = [fvals; f];
    gNormVals= [gNormVals; norm(g,2)];
    return(x,B,g,its,fvals,gNormVals);
end
function Or(boolArray)
    for i=1:size(boolArray,1)
        if boolArray[i] == true
            return (true, i)
        end
    end
    return (false,size(boolArray,1))
end

function newtmin(obj, x0, maxIts, optTol, warmUp, whileSwitch, randPerts, newtVers)
    fvals = [];
    gNormVals=[];
    (f0,g0,H0) = obj(x0);
    x = x0;
    (f,g,H) = obj(x);
    its = 0;
    B = eye(size(x0,1));


    if warmUp > 0
        (x,its,fvals,gNormVals) = warmup(warmUp,obj,x,its,fvals,gNormVals);
    end

    while (norm(g,2) > optTol*whileSwitch*norm(g0,2) && norm(g,2) > 1e-8 && its < maxIts)
        if newtVers == 1
            (x,g,its,fvals,gNormVals) = newtstep1(obj,x,its,fvals,gNormVals);
        end
        if newtVers == 2
            (x,g,its,fvals,gNormVals) = newtstep2(obj,x,its,fvals,gNormVals);
        end
        if newtVers == 3
            (x,B,g,its,fvals,gNormVals) = BFGSstep(obj,x,B,its,fvals,gNormVals)
        end
    end

    if norm(g,2) < optTol*whileSwitch*norm(g0,2) || norm(g,2) < 1e-8
#        println("Method computed optimal x: ", x)
#        println("\nIterations: ", its)
#        println("\nObjective: ", f)
#        println("\nInitial gradient norm: ", norm(g0,2))
#        println("\nGradient norm: ", norm(g,2))
        return (x, its, fvals, gNormVals)
    else
        perts = 0;
        while perts < randPerts
            E = eigfact(H);
            lambda = E[:values];
            V = E[:vectors];
            if Or(lambda.<0)[1]
                perts = perts + 1
                x = x + optTol*V[Or(lambda.<0)[2]];         #use small perturbation in decreasing eigenvector direction
                while (norm(g,2) > optTol*whileSwitch*norm(g0,2) && norm(g,2) > 1e-8 && its < (perts + 1)*maxIts)
                    (x,g,its,fvals,gNormVals) = newtstep1(x,its,fvals,gNormVals);
                end
            end
            if norm(g,2) < optTol*whileSwitch*norm(g0,2) || norm(g,2) < 1e-8
#                println("Method computed optimal x: ", x)
#                println("\nIterations: ", its)
#                println("\nObjective: ", f)
#                println("\nInitial gradient norm: ", norm(g0,2))
#                println("\nGradient norm: ", norm(g,2))
                return (x, its, fvals, gNormVals)
            end
        end
#        println("Method timed out on maxIts: ", its)
#        println("\nx: ", x)
#        println("\nObjective: ", f)
#        println("\nInitial gradient norm: ", norm(g0,2))
#        println("\nGradient norm: ", norm(g,2))
    end
    return (x, its, fvals, gNormVals);
end