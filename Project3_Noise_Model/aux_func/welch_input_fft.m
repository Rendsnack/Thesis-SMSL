function [Welch_psd] = welch_input_fft(X, win, fs)
%WELCH_INPUT_FFT The original Welch Method function requires a time-domain
%signal, however the averaged fft requires a new function to perform Welch
%method directly on the frequency-domain signal. windowing is already
%performed on the time domain signal

% INPUTS:
%   - X:            Frequency-domain input signal (nfft x segments);
%   - win:          The window used on the segments is needed for its
%                   signal power

nfft = size(X,1);
k = size(X,2);

% First calculate the periodogram of each segment (taking only the positive
% frequencies
periodo = zeros((nfft/2)+1, k);
P = sum(abs(win).^2)/length(win);       % Power of window
for i = 1:k
    Pxx = (1/(nfft*P))* abs(X(:,i).*conj(X(:,i)));
    Pxx = Pxx/fs;
    periodo(:,i) = Pxx(1:1+ (nfft/2));
end

% The Welch Estimate is the average of the periodograms of the segments
Welch_psd = sum(periodo,2)/k;

end

