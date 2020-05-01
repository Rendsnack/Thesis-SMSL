function [Pxx] = arma_power_est(x,p,q, nfft,fs)
%ARMA_POWER_EST estimates the power spectral density based on the ARMA
%model using the yule-walker methos
%   INPUT:
%       - x:    time-domain signal
%       - p:    order AR
%       - q:    order MA
%       - nfft: Number of FFT-points 
%       - fs:   Sampling frequency
%   OUTPUT:
%       - Pxx:  Power Spectral Density Estimate of signal x


 % Get parameters of autoregressive filter
    [ar_params, e] = aryule(x,p); % Get parameters of Autoregressive part

    % Filter original time-series
    v_n = filter(1,ar_params,x);
    v_n = v_n(p:end);

    % Get parameters of moving average filter
    co_a = aryule(v_n,q*2);     % Approximate MA model using a Long-AR model (recommended to take order 2*Q)
    ma_params = aryule(co_a,q);

    H = freqz(ma_params,ar_params,nfft,"whole", fs);
    H_oneside = H(1:nfft/2 +1);
    Sxx = e.*(abs(H_oneside).^2);
    Pxx = Sxx./fs;

end

