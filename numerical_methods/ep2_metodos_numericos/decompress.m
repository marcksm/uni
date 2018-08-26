# Lucas Seiki Oshiro                -  9298228
# Marcos Vinicius do Carmo Sousa    -  9298274

# Descomprime a imagem compressImg, com o método indicado por method (1 =
# bilinear, 2 = bicubica), adicionando k linhas e k colunas, e interpolando com
# quadrados de lado h, gerando o arquivo decompressed.png
function decompress (compressImg, method, k, h);
  imagem = imread (compressImg);
  global R
  global G
  global B
  global p

  if size (imagem, 3) == 1
    R = imagem;
    G = imagem;
    B = imagem;
  else
    R = imagem(:,:,1);
    G = imagem(:,:,2);
    B = imagem(:,:,3);
  endif

  p = size (R, 1);
  n = p + (p - 1) * k;

  R2 = uint8 (zeros (p, p));
  G2 = uint8 (zeros (p, p));
  B2 = uint8 (zeros (p, p));

  if method == 1
  # bilinear
    M = [1, 0, 0, 0;
         1, 0, h, 0;
         1, h, 0, 0;
         1, h, h, h ^ 2];

    Mi = M ^ -1;

    xb = 0;
    yb = 0;

    for a = 1:n
      for b = 1:n
        i = p * (a - 1) / n + 1;
        j = p * (b - 1) / n + 1;

        x = xb + i * h;
        y = yb + j * h;

        xi = piso (x, h);
        xi1 = xi + h;
        yj = piso (y, h);
        yj1 = yj + h;

        if (int16 ((xi - xb) / h) > p || int16 ((xi1 - xb) / h) > p)
          xi -= h;
          xi1 -= h;
        end

        if (int16 ((yj - yb) / h) > p || int16 ((yj1 - yb) / h) > p)
          yj -= h;
          yj1 -= h;
        end

        N = [1, (x - xi), (y - yj), (x - xi) * (y - yj)];

        TR = [R(int16 ((xi - xb) / h), int16 ((yj - yb) / h));
              R(int16 ((xi - xb) / h), int16 ((yj1 - yb) / h));
              R(int16 ((xi1 - xb) / h), int16 ((yj - yb) / h));
              R(int16 ((xi1 - xb) / h), int16 ((yj1 - yb) / h))];

        TG = [G(int16 ((xi - xb) / h), int16 ((yj - yb) / h));
              G(int16 ((xi - xb) / h), int16 ((yj1 - yb) / h));
              G(int16 ((xi1 - xb) / h), int16 ((yj - yb) / h));
              G(int16 ((xi1 - xb) / h), int16 ((yj1 - yb) / h))];

        TB = [B(int16 ((xi - xb) / h), int16 ((yj - yb) / h));
              B(int16 ((xi - xb) / h), int16 ((yj1 - yb) / h));
              B(int16 ((xi1 - xb) / h), int16 ((yj - yb) / h));
              B(int16 ((xi1 - xb) / h), int16 ((yj1 - yb) / h))];

        R2(a, b) = N * Mi * double (TR);
        G2(a, b) = N * Mi * double (TG);
        B2(a, b) = N * Mi * double (TB);
      end
    end
  else
    # bicubica
    Bb = [1, 0, 0, 0;
          0, 0, 1, 0;
          -3/h^2, 3/h^2, -2/h, -1/h;
          2/h^3, -2/h^3, 1/h^2, 1/h^2];

    Bi = Bb';

    xb = 0;
    yb = 0;

    count1 = k + 1;
    for a = 1:n
      count2 = k+1;
      for b = 1:n
        i = p * (a - 1) / n + 1;
        j = p * (b - 1) / n + 1;
        if (mod (count1, k+1) != 0 || mod (count2, k+1) != 0)
          x = xb + i * h;
          y = yb + j * h;

          xi = piso(x, h);
          xi1 = xi + h;
          xi_1 = xi - h;
          yj = piso(y, h);
          yj1 = yj + h;
          yj_1 = yj - h;

          N1B = [1, (x - xi), (x - xi)^2, (x - xi)^3] * Bb;
          BiN2 = Bi * [1; (y - yj); (y - yj)^2; (y - yj)^3];

          m1=f(xi, yj, h, xb, yb);
          m2=f(xi, yj1, h, xb, yb);
          m3=dfdy(xi, yj, h, xb, yb);
          m4=dfdy(xi, yj1, h, xb, yb);
          m5=f(xi1, yj, h, xb, yb);
          m6=f(xi1, yj1, h, xb, yb);
          m7=dfdy(xi1, yj, h, xb, yb);
          m8=dfdy(xi1, yj1, h, xb, yb);
          m9=dfdx(xi, yj, h, xb, yb);
          m10=dfdx(xi, yj1, h, xb, yb);
          m11=dfdxdy(xi, yj, h, xb, yb);
          m12=dfdxdy(xi, yj1, h, xb, yb);
          m13=dfdx(xi1, yj, h, xb, yb);
          m14=dfdx(xi1, yj1, h, xb, yb);
          m15=dfdxdy(xi1, yj, h, xb, yb);
          m16=dfdxdy(xi1, yj1, h, xb, yb);

          FR = [m1(1), m2(1), m3(1), m4(1);
                m5(1), m6(1), m7(1), m8(1);
                m9(1), m10(1), m11(1), m12(1);
                m13(1), m14(1), m15(1), m16(1)];

          FG = [m1(2), m2(2), m3(2), m4(2);
                m5(2), m6(2), m7(2), m8(2);
                m9(2), m10(2), m11(2), m12(2);
                m13(2), m14(2), m15(2), m16(2)];

          FB = [m1(3), m2(3), m3(3), m4(3);
                m5(3), m6(3), m7(3), m8(3);
                m9(3), m10(3), m11(3), m12(3);
                m13(3), m14(3), m15(3), m16(3)];

          R2(a, b) = N1B * double (FR) * BiN2;
          G2(a, b) = N1B * double (FG) * BiN2;
          B2(a, b) = N1B * double (FB) * BiN2;

        else
          R2(a, b) = R(int16(floor(i)), int16(floor(j)));
          G2(a, b) = G(int16(floor(i)), int16(floor(j)));
          B2(a, b) = B(int16(floor(i)), int16(floor(j)));
        end
        count2 += 1;
      end
      count1 += 1;
    end
  end

  if size (imagem, 3) == 1
    imout = R2;
  else
    imout (:,:,1) = R2;
    imout (:,:,2) = G2;
    imout (:,:,3) = B2;
  end

  imwrite (imout, 'decompressed.png');
end;

global R
global G
global B
global p

# Calcula o maior produto de h por um natural que seja menor que menor ou igual
# a x.
function t = piso (x, h)
  t = x - rem (x, h);
end

## Lembrete: Nas proximas 3 funções, precisa tambem do yb, que ta se confundindo com xb.
## Porem, não faz diferença, ja que aqui eles são 0.

# Calcula a derivada parcial da função interpoladora, em relação a x, no ponto
# (xi, yj)

function a = dfdx (xi, yj, h, xb, yb)
  global R
  global G
  global B
  global p

  xi_1 = xi - h;
  xi1 = xi + h;

  while (int16((xi-xb)/h) > p)
    xi -= h;
  end

  while (int16((yj-yb)/h) > p)
    yj -= h;
  end

  p1 = int16((xi1-xb)/h);
  p2 = int16((yj-yb)/h);
  p3 = int16((xi-xb)/h);
  p4 = int16((xi_1-xb)/h);

  if (p3 == 1)
    a = [(R(p1, p2) - R(p3, p2))/h,
         (G(p1, p2) - G(p3, p2))/h,
         (B(p1, p2) - B(p3, p2))/h];

  elseif (p3 == p)
    a = [(R(p3, p2) - R(p4, p2))/h,
         (G(p3, p2) - G(p4, p2))/h,
         (B(p3, p2) - B(p4, p2))/h];

  else
    a = [(R(p1, p2) - R(p4, p2))/2*h,
         (G(p1, p2) - G(p4, p2))/2*h,
         (B(p1, p2) - B(p4, p2))/2*h];
  end
end

# Calcula a derivada parcial da função interpoladora, em relação a y, no ponto
# (xi, yj).
function b = dfdy (xi, yj, h, xb, yb)
  global R
  global G
  global B
  global p

  while (int16 ((xi - xb) / h) > p)
    xi -= h;
  end

  while (int16 ((yj - yb) / h) > p)
    yj -= h;
  end

  yj_1 = yj - h;
  yj1 = yj + h;

  p1 = int16((xi-xb)/h);
  p2 = int16((yj1-yb)/h);
  p3 = int16((yj-yb)/h);
  p4 = int16((yj_1-xb)/h);

  if (int16 ((yj - yb) / h) == 1)
    b = [(R(p1, p2) - R(p1, p3))/h,
         (G(p1, p2) - G(p1, p3))/h,
         (B(p1, p2) - B(p1, p3))/h];

  elseif (int16 ((yj - yb) / h) >= p)
    b = [(R(p1, p3) - R(p1, p4))/h,
         (G(p1, p3) - G(p1, p4))/h,
         (B(p1, p3) - B(p1, p4))/h];

  else
    b = [(R(p1, p2) - R(p1, p4))/2*h,
         (G(p1, p2) - G(p1, p4))/2*h,
         (B(p1, p2) - B(p1, p4))/2*h];
  end
end

# Calcula a derivada mista da função interpoladora no ponto (xi, yj).
function c = dfdxdy (xi, yj, h, xb, yb)
  global R
  global G
  global B
  global p

  xi1 = xi + h;
  xi_1 = xi - h;

  if (int16 ((xi - xb) / h) == 1)
    b1 = dfdy (xi1, yj, h, xb);
    b2 = dfdy (xi, yj, h, xb);
    c = (b1-b2)/h;

  elseif (int16 ((xi - xb) / h) == p)
    b1 = dfdy (xi, yj, h, xb);
    b2 = dfdy (xi_1, yj, h, xb);
    c = (b1-b2)/2*h;

  else
    b1 = dfdy (xi1, yj, h, xb);
    b2 = dfdy (xi_1, yj, h, xb);
    c = (b1-b2)/2*h;
  end
end

# Calcula a função interpoladora no ponto (xi, yj).
function f1 = f (xi, yj, h, xb, yb)
  global R
  global G
  global B
  global p

  if (int16 ((xi - xb) / h) > p)
    xi -= h;
  end

  if (int16 ((yj - yb) / h) > p)
    yj -= h;
  end

  if (int16 ((xi - xb) / h) <= 0)
    xi += h;
  end

  if (int16 ((yj - yb) / h) <= 0)
    yj += h;
  end
  p1 = int16((xi-xb)/h);
  p2 = int16((yj-yb)/h);
  f1 = [R(p1, p2),
        G(p1, p2),
        B(p1, p2)];
end
