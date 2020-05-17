function [Pxx, ma_params, ar_params] = arma_power_est(x,p,q, nfft,fs)
%ARMA_POWER_EST estimates the power spectral density based on the ARMA
%model using the least-squares modified yule-walker equations and a long AR
%approximate (Durbin's method with least squares criterion)
%   INPUT:
%       - x:    time-domain signal
%       - p:    order AR
%       - q:    order MA
%       - nfft: Number of FFT-points 
%       - fs:   Sampling frequency
%   OUTPUT:
%       - Pxx:  Power Spectral Density Estimate of signal x


    % 1. Least Squares Modified Yule-Walker Equation (LSMYWE)
    M = (p+q)*2; % Define overdetermined number of equations
    
    % 1.a. Autocorrelation sequence of input with max lag of M
    l = length(x);
    rxx = xcorr(x,x,M);
   
    % 1.b. Construct overdetermined set of linear equations with autocorrelation matrix
    % Matrix should be of size (M-q x p): Note middle starts from (M+1)
    Rxx = toeplitz(rxx);
    Rxx = Rxx(M+q+1:(2*M),1:p);
    
    % 1.c. Least Square solution ( min || r- Ra||^2) (can also use weights
    % to minimize effect of covariance)
    ar_params = [1;-(inv(Rxx'*Rxx))*Rxx'*rxx(M+q+2:end)]; 
    % Get parameters of autoregressive filter
    %[ar_params, e] = aryule(x,p); % Get parameters of Autoregressive part

    % Filter original time-series (using Â(z))
    v_n = filter(ar_params,1,x);
    v_n = v_n(p:end);
    
    % 2. Durbin's method to solve b
    O = q*2;
    % 1: Approximate MA using long AR 
    long_a = aryule(v_n,O);  % Note that we can now easily use the aryule function since we do not need a modified autocorrelation sequence.
    ma_params = aryule(long_a,q);


    H = freqz(ma_params,ar_params,nfft,"whole", fs);
    H_oneside = H(1:nfft/2 +1);
    Sxx = (abs(H_oneside).^2);
    Pxx = Sxx./fs;

end

