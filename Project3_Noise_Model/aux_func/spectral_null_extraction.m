function [IR_cut, IR_psd,f, notch_frequencies, notch_bandwidths, ...
    notch_magnitudes, p] = spectral_null_extraction(IR, Fs, P, nfft)
%SPECTRAL_NULL_EXTRACTION This function follows the algorithm described in
% Raykas, 2005 to extract notches from the magnitude spectrum of 
% an Impulse Response.

% https://pdfs.semanticscholar.org/5062/87f8e6ea82e88c2e053f763036158649a52f.pdf
% https://pdfs.semanticscholar.org/1410/53380eb9a7cffd94a609815d0217e29222d3.pdf
% https://pure.tue.nl/ws/files/1793824/622654.pdf
% INPUT:
%   - IR:       Time-domain signal Impulse Response
%   - Fs:       Sampling frequency of Impulse Response measurement
%   - P:        Order of LP residual (all-pole model)

% OUTPUT:
%   - IR_cut:   Impulse Response cut from Onset time
%   - IR_psd:   Power Spectral Density from IR_cut
%   - notch_:  Respectively the frequencies, bandwidths and magnitudes of the notches
%   - p:        The poles of the AR (AutoRegressive) filter
%   - k:        Gain of the filter (useless)

% 1: Determine the initial onset of the IR and use the IR from that instant
% Onset time is determined using a spectrally based method (Hermes, 1990)
%   Mean over spectra (Ds): 
    IR_cut = cell(1);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % STFT parameters
    rfft = nfft/2;                              % Shift = 50% overlap
    win = sqrt(hann(nfft,'periodic'));         % Analysis windows
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % STFT output will be an array with the columns being time frames and the
    % rows being frequency bins.
    [IR_f, f] = calc_STFT(IR, Fs, win, nfft, nfft/rfft, 'onesided' );  % STFT output

    Energy_spectral = sum(abs(IR_f));       % Sum of spectral energy for each time frame

    % Find max energy frame
    max_E = Energy_spectral(2) / Energy_spectral(1);
    max_E_frame = 0;
    for i = 2:length(Energy_spectral)-1
        E_i = Energy_spectral(i+1)/Energy_spectral(i);
        if E_i > max_E
            max_E = E_i;
            max_E_frame = i;
        end
    end
    % Time step between two windows is rfft; index begins at 1
    onset_frame = max([1, rfft * max_E_frame]);   % Onset time (in frames)
    
    IR_cut = {IR(onset_frame:end)};

    IR_cut = cell2mat(IR_cut);

% 2: Derive the Pth order LP residual from the given IR (10 to 12)
% Make use of the lpc function (Signal Processing Toolbox)
% a: linear predictor coefficients
% g: Prediction error variance
[a, g] = lpc(IR_cut, P);
residual_e = zeros(length(IR_cut),1);
for i = 1: length(IR_cut)
    if i < length(a)
        residual_e(i) = -a(1:i)*IR_cut(1:i);
    else
        residual_e(i) = (-a)*IR_cut(i-P:i);
    end
end

% 3: Window the LP residual using a half Hann window around 1.0ms
window = hann(Fs/1000, 'periodic');
half_window = window(ceil(length(window)/2):end);
residual_e_windowed = residual_e(1:length(half_window)) .* half_window;

% 4: Compute the squared magnitude spectrum of the windowed LP residual
magnitude = mag2db(abs(fft(residual_e_windowed, nfft)));
magnitude_squared = magnitude.^2;

% 5: Invert the windowed LP residual spectrum
magnitude_squared_inv = -magnitude_squared;

% 6: Take the IDFT of the inverted spectrum to get the corresponding
%       autocorrelation function
autocorr = ifft(magnitude_squared_inv);

% 7: Using Levinson-Durbin recursion fit a Pth order all-pole model to the
% inverted spectrum using the first P+1 coefficients of the autocorrelation
% function
coeffs_a = rmmissing(levinson(autocorr(1:P+1),P));
% 8: The null frequencies can be obtained from the all-pole model by
% factorizing the model polynomial
% Use function tf2pz
[z, p, k] = tf2zp(1,coeffs_a);

pole_angles = angle(p);
pole_radii = sqrt(real(p).^2+imag(p).^2);

notches = Fs* pole_angles/(2*pi);

% Only keep positive frequencies (two-sided spectrum)
indexes = find(notches>0 & notches<22050);
notch_frequencies = notches(indexes);
[notch_frequencies, new_indexes] = sort(notch_frequencies);
indexes = indexes(new_indexes);
notch_bandwidths = -log10(pole_radii(indexes))*(Fs/pi);

% Get Power Spectral Density
IR_psd = fft(IR_cut, nfft);
IR_psd = IR_psd(1:(length(IR_psd)-1)/2);
IR_psd = (1/(Fs*length(IR_psd)))* (abs(IR_psd).^2); %
IR_psd = mag2db(IR_psd);

df = Fs/(2*length(IR_psd));
f = 0:df:(Fs-df)/2;

L = length(notch_frequencies);
notch_magnitudes = ones(L,1);

for i = 1:L
    notch_magnitudes(i) = IR_psd(find(min(abs(f-notch_frequencies(i)))== abs(f-notch_frequencies(i))));
end

end

