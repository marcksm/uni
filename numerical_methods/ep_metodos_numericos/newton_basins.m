function newton_basins (f, n)
  # A função recebe um vetor de coeficientes de uma função polinomial e recebe
  # um inteiro n e gera um arquivo de saída com os campos x, y e r, em que x e
  # são pontos do gráfico e r um número que representa a raiz para a qual essa
  # função converge nesse ponto.
  arquivo = fopen ("output.txt", "w");
  df = derivada (f);

  raizes = [];
  min = -n / 2;
  max = n / 2 - 1;
  
  for x = min : max
    for y = min : max
      x0 = ((x + n / 2) * 4) / n - 2 + (((y + n / 2) * 4) / n - 2) * i;

      raiz = newton (f, derivada (f), x0);

      indice = -1;
      for a = 1 : size (raizes, 2)
        if raizes(a) == raiz || (isnan (raiz) && isnan (raizes(a)))
          indice = a;
          break
        end
      end

      if indice == -1
        indice = size (raizes, 2) + 1;
        raizes = [raizes, raiz];
      end

      fprintf (arquivo, "%d %d %d\n", x, y, indice);
    end
  end

  fclose (arquivo);
end

function y = val_func (f, x)
  # Calcula em x o valor da função polinomial representada por f.
  y = 0;
  sz = size (f, 2);
  for j = 1 : sz
    y += f(j) * x ^ (sz - j);
  end
end

function df = derivada (f)
  # Devolve a derivada da função polinomial f
  df = [];
  sz = size (f, 2);
  for j = 1 : sz - 1
    df = [df, f(j) * (sz - j)];
  end
end

function x = newton (f, df, x0)
  # Aplica o método de Newton na função f, partindo de x0. Devolve a raiz, em
  # caso o método de newton convirja em menos de 100 iterações, ou devolve NaN,
  # caso contrário.
  atol = 1.e-15;
  valdf = val_func (df, x0);
  iteracoes = 1;

  if valdf == 0
    x = NaN;
    return
  else
    x = x0 - val_func (f, x0) / valdf;
  end

  while abs (val_func (f, x0)) > atol
    x0 = x;
    valdf = val_func (df, x0);
    
    if valdf == 0 || iteracoes >= 500
      x = NaN;
      return
    else
      x = x0 - val_func (f, x0) / valdf;
    end

    iteracoes += 1;
  end

  x = round (x * 1.e15) / 1.e15;
end
