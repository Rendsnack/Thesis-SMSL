% this function time reverses and amplitude scales a signal
% based on section 4 of: 
% IMPULSE RESPONSE MEASUREMENT TECHNIQUES AND THEIR APPLICABILITY IN THE REAL WORLD
% - Holters et al.
function x_inv = inverse(x,f1,f2,fs)
% INPUTS:
% - x: signal to be inverted
% - f1: start frequency
% - f2: end frequency
% - fs: sampling frequency

% OUTPUTS:
% - x_inv: inverted signal

%% time reverse signal
x_inv = flip(x);

%% scale amplitude
T = length(x)/fs;
t = 0:1/fs:(T*fs-1)/fs;
G = (f2/f1).^(-t./T);
for i = 1:size(x_inv)
    x_inv(i) = x_inv(i)*G(i);
end
% x_inv = x_inv.*G;

end