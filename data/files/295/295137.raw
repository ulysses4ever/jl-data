export simpsons_rule_adapted

function simpsons_rule_adapted(f, a, b; tol = 1e-10, N = 128)
  Va = fill(1.0, N); Vb = fill(1.0, N);
  Vfa = fill(1.0, N); Vfb = fill(1.0, N); Vfc = fill(1.0, N); Vfm1 = fill(1.0, N); Vfm2 = fill(1.0, N);
  i = 1; approx = 0; Va[i] = a; Vb[i] = b; m = 0;
  Vfa[i] = f(a);   Vfb[i] = f(b);   Vfc[i] = f((a + b)/2); Vfm1[i] = f(a + (b - a)/4); Vfm2[i] = f(b - (b - a)/4);

  while i > 0
    atemp = Va[i]; btemp = Vb[i]; htemp = (btemp - atemp)/2;
    fatemp = Vfa[i]; fbtemp = Vfb[i]; fctemp = Vfc[i]; fm1temp = Vfm1[i]; fm2temp = Vfm2[i];
    S1 = (fatemp + 4fctemp + fbtemp)*htemp/3; 
    S2 = (fatemp + 4(fm1temp + fm2temp) + 2fctemp + fbtemp)*htemp/6;
    toltemp = 15tol/((b - a)/(btemp - atemp))
    i -= 1

    if abs(S1 - S2) < toltemp
      approx += S2
    else
      if ((b - a)/(btemp - atemp) > N)
        approx += S2
        m = 1;
      else
        i += 1
        Va[i] = btemp - htemp; Vb[i] = btemp; Vfa[i] = fctemp; Vfb[i] = fbtemp; 
        Vfc[i] = fm2temp; Vfm1[i] = f(Va[i] + (Vb[i] - Va[i])/4); Vfm2[i] = f(Vb[i] - (Vb[i] - Va[i])/4);
        i += 1
        Va[i] = atemp; Vb[i] = btemp - htemp; Vfa[i] = fatemp; Vfb[i] = fctemp;
        Vfc[i] = fm1temp; Vfm1[i] = f(Va[i] + (Vb[i] - Va[i])/4); Vfm2[i] = f(Vb[i] - (Vb[i] - Va[i])/4);
      end
    end
  end
  return approx
end
