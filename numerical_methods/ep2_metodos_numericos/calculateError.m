# Lucas Seiki Oshiro                -  9298228
# Marcos Vinicius do Carmo Sousa    -  9298274

# Calcula o erro da imagem decompressedImg em relação à imagem originalImg
function calculateError(originalImg, decompressedImg)
  orig = imread(originalImg);
  decomp = imread(decompressedImg);

  if size(orig, 3) == 1
    origR = double(orig);
    origG = double(orig);
    origB = double(orig);

  else
    origR = double(orig(:,:,1));
    origG = double(orig(:,:,2));
    origB = double(orig(:,:,3));
  end

  if size(decomp, 3) == 1
    decR = double(decomp);
    decG = double(decomp);
    decB = double(decomp);

  else
    decR = double(decomp(:,:,1));
    decG = double(decomp(:,:,2));
    decB = double(decomp(:,:,3));
  end

  (norm(origR - decR) / norm(origR) + norm(origG - decG) / norm(origG) + norm(origB - decB) / norm(origB)) / 3
end
