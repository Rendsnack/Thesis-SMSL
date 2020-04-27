function [powspecdens, frequencies, bandwidths, magnitudes, p] = resonance_feature_extraction(y,P, Fs, nfft)
%NOTCH_FEATURE_EXTRACTION The augmented signal (speech) contains NOTCHES
%which indicate the direction. Frequencies are estimated using linear
%prediction

% Peaks are ignored as these indicate formants
%   INPUT:
%       - y:            time-domain signal
%       - P:            all-pole filter order
%   OUTPUT:
%       - powspecdens:
%       - Frequencies:  
%       - Bandwidths:   
%       - Magnitudes:
%       - p:    

    % LP coefficients: cartesian form
    [a,g] = lpc(y,P);
    
    % Convert to poles:
    [z, p, k] = tf2zp(1,a);
    
    angles = angle(p);      % pole angles
    radii = sqrt(real(p).^2+imag(p).^2);    % pole radii
    
    frequencies = Fs*angles/(2*pi);   % resonance frequencies
    % Only keep valid frequencies
    indexes = find(frequencies>0 & frequencies<22050);
    frequencies = frequencies(indexes);
    [frequencies, new_indexes] = sort(frequencies);
    indexes = indexes(new_indexes);
    bandwidths = -log10(radii(indexes))*(Fs/pi);   % resonance bandwidths
    
    % Get notch magnitudes from Power Spectral Density (smooth magnitude)
    powspecdens = periodogram(y,hamming(length(y)), nfft);

    df = Fs/(2*length(powspecdens));
    f = 0:df:(Fs-df)/2;

    L = length(frequencies);
    magnitudes = ones(L,1);

    for i = 1:L
        magnitudes(i) = powspecdens(find(min(abs(f-frequencies(i)))== abs(f-frequencies(i))));
    end
  

end

