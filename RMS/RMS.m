function y = RMS(x, sampleRateHz, rmsHorizonS)
	N = length(x);
	L = round(sampleRateHz * rmsHorizonS);
	ySq = zeros(1, N);
	ySq(1) = (1/L) * x(1) * x(1);

	for n = 2 : N
		if (n > L)
			ySq(n) = ySq(n-1) + (1/L) * (x(n) * x(n) - x(n-L) * x(n-L));
		else
			ySq(n) = ySq(n-1) + (1/L) * (x(n) * x(n));
        end
    end
	y = sqrt(ySq);
end