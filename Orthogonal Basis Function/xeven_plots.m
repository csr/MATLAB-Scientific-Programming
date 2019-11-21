% ----------------------------------------------
% WP : orthogonal and periodical basis functions
% file : xeven_plots.m
% ----------------------------------------------

clf;
hold on;

x = linspace(-2,2,100);
y1 = x;
y2 = x.^2;
y3 = x.^3;
y4 = x.^4;
y5 = x.^5;
y6 = x.^6;
y7 = x.^7;
y8 = x.^8;
y9 = x.^9;


title( 'the even powers of x' )

plot( x, y2, 'Color', [1,141/256,0] );
l = legend( 'x^2' );
axis([-2 2 -1 40]);
pause;

plot( x, y4, 'g' );
l = legend([ l.String(1:end-1), 'x^4' ]);
pause;

plot( x, y6, 'c' );
l = legend([ l.String(1:end-1), 'x^6' ]);
pause;

plot( x, y8, 'r' );
l = legend([ l.String(1:end-1), 'x^8' ]);

