# Lucas Seiki Oshiro                -  9298228
# Marcos Vinicius do Carmo Sousa    -  9298274

# Comprime a imagem originalImg, retirando k linhas e k colunas, gerando o
# arquivo compressed.png
function compress (originalImg, k)
  imagem = imread (originalImg);
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

  i = 1;
  for cont = 0:p - 1;
    if (mod (cont, k + 1) != 0);
      R(:, i) = [];
      R(i, :) = [];

      G(:, i) = [];
      G(i, :) = [];

      B(:, i) = [];
      B(i, :) = [];
    else
      i += 1;
    end;
  end;

  if size (imagem, 3) == 1
    imout = R;
  else
    imout (:,:,1) = R;
    imout (:,:,2) = G;
    imout (:,:,3) = B;
  end

  imwrite (imout, 'compressed.png');
end
