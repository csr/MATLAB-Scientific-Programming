% ----------------------------------------------
% WP : orthogonal and periodical basis functions
% file : chebyshev_plots.m
% ----------------------------------------------

clf;
hold on;

x = linspace(-1,1,1000);
y = chebyshev(x,5);

title( 'the first few chebyshev polynomials' );

p0=plot( x, y(:,1), 'Color', [1,141/256,0]);
l = legend( 'T_0' );
axis([-1 1 -1 1]);
pause;

plot( x, y(:,2), 'g');
l = legend([ l.String(1:end-1), 'T_1' ]);
pause;

plot( x, y(:,3), 'c');
l = legend([ l.String(1:end-1), 'T_2' ]);
pause;

plot( x, y(:,4), 'r');
l = legend([ l.String(1:end-1), 'T_3' ]);
pause;

plot( x, y(:,5), 'b');
l = legend([ l.String(1:end-1), 'T_4' ]);
pause;

plot( x, y(:,6), 'm');
l = legend([ l.String(1:end-1), 'T_5' ]);