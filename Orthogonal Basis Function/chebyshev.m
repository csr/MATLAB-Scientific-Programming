function A = chebyshev(x, n)
%CHEBYSHEV Compute chebyshev polynomials.
%   CHEBYSHEV( X, N ) computes the first N+1 Chebyshev polynomials
%   for the given value X. 

if (size(x, 1) < size(x, 2))
  x = x';
end

A = zeros(length(x), n+1);
for i=0:n
  A(:, i+1) = chebyshevml(i, x);
end

function res = chebyshevml(m, x)

  if m==0, pn = ones(size(x));
  elseif m==1, pn = x;
  else
    pnm2 = ones(size(x));
    pnm1 = x;
    for n = 2:m
      pn = (2.*x.*pnm1-pnm2);
      pnm2 = pnm1;
      pnm1 = pn;
    end
  end
  res = pn;
  return