function achaRaizes (f, df, a, b, ninter, tol)
  # Acha as raízes da função f, cuja derivada é df, procurando a cada ninter
  # intervalos entre a e b, com tolerância tol.
  dist = (b - a) / ninter;

  a1 = a;
  b1 = a1 + dist;

  while a1 < b
    if f(a1) == 0
      disp (a1)
    end
    
    if f(a1) * f(b1) < 0
      raiz = newton (f, df, (a1 + b1) / 2, tol);
      
      while isnan (raiz)
        x0 = bissec (f, a, b);
        raiz = newton (f, df, x0, tol);
      end

      disp (raiz)
    end
    a1 = b1;
    b1 += dist;
  end
end

function x0 = bissec (f, a, b)
  # Aplica o método da bissecção 3 vezes em f, e devolve uma aproximação da
  # raiz da função
  fa = f (a);

  for i = 1 : 3
    p = (a + b) / 2;
    fp = f (p);

    if fa * fp == 0
      x0 = p;
      break
    elseif fa * fp < 0
      b = p;
    else
      a = p;
      fa = fp;
    end
  end
  
  x0 = p;
end

function x = newton (f, df, x0, tol)
  # Aplica o método de Newton na função f, com derivada df, em x0, com
  # tolerância tol. 
  valdf = df (x0);

  while valdf == 0
    x += 0.1;
    valdf = df (x0);
  end
  
  x = x0 - f(x0) / valdf;

  while !(abs (x - x0) < tol * (1 + abs (x)) && f(x) < tol)
  if abs (f(x)) > abs (0.5 * f (x0))
      x = NaN;
      return
    end
      
    x0 = x;
    valdf = df (x0);

    while valdf == 0
      x += 0.1;
      valdf = df (x0);
    end

    x = x0 - f (x0) / valdf;
  end
end
