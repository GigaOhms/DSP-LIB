fs = 50;
Ts = 1e-4;
t = 0:Ts:0.1;
x = sin(2*pi*t*fs);
y = RMS(x, 200, 1);
plot(t, x, t, y);
