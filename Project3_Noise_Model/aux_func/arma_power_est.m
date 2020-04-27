function [pow, f] = arma_power_est(x,order,fs)
%ARMA_POWER_EST estimate ARMA coefficients using Yule-Walker
%   Detailed explanation goes here


n = length(x);

% Create frequency vector
df = fs/(2*((order/2)+1));     
f = 0:df:(fs-df)/2;

% Compute Autoregressive coefficients using Yule-Walker method with
% Levinson-Durbin algorithm
[d1, p1] = aryule(x,order);

% Compute autocorrelation matrix and take only correlations of order size
r = xcorr(x);

% Solve for coefficients of Moving Average filter
covar_ma = [1; zeros(order,1)];
for k = 1:order
    covar = 0;
    for l = 1:pAR
        for p = 1:pAR
            index = abs(k+p-l);
            if index > 0
                covar = covar + (d1(l)*conj(d1(p))*r(index));
            end
        end
    end
    covar_ma(k) = covar;
end

AR = d1;
MA = covar_ma;

for i = 1:pAR
    A = 1;
    w_index = f(i);
    for w=2:13
        A = A + exp(-j*w_index*w);
    end
    B = 0;
    for u = 1:length(MA)
        B = B + (MA(u)*exp(-j*w_index*u));
    end
    psd_est_arma(i) = B/(abs(A)^2);
end

end

