#!/usr/bin/env octave-cli

function y = f(x)
  y = x ^ 5 + x ^ 2 - 0.2;
end

function y = df(x)
  y = 5 * x ^ 4 + 2 * x;
end


achaRaizes (@(x) f(x), @(x) df (x), -10, 10, 100, 1.e-8)
