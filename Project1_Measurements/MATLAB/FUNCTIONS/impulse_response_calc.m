%% Calculate Impulse Response %%
% based on section 4 of: 
% IMPULSE RESPONSE MEASUREMENT TECHNIQUES AND THEIR APPLICABILITY IN THE REAL WORLD
% - Holters et al.

function [h ,C, n0] = impulse_response_calc(x, f1, f2, fs, y)
% INPUTS:
% - x: original measurement signal
% - f1: start frequency of x
% - f2: end frequency of x
% - fs: sampling frequency
% - y: recored signal

% OUTPUTS:
% - h: impulse response
% - C: scaling factor
% - n0: timeshift

L = length(x);      %length of measurement signal x

%% calculate inverse of x
x_inv = inverse(x, f1, f2, fs);

%% calculate scaling factor
C = (pi*L*(f1/f2 - 1))/(2*2*pi*(f2-f1)*log(f1/f2));   % scaling factor
x_inv = x_inv/max(x)^2/C;
%% calculate impulse response
n0 = L-1;   %timeshift
h = conv(y,x_inv);

end
