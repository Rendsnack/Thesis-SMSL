function [sample_index] = onset_estimation(IR, nfft, fs)
%ONSET_ESTIMATION Determine the initial onset of the IR and use the IR from that instant
% Onset time is determined using a spectrally based method (Hermes, 1990)


%Mean over spectra (Ds): 

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % STFT parameters
    rfft = nfft/2;                              % Shift = 50% overlap
    win = sqrt(hann(nfft,'periodic'));         % Analysis windows
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % STFT output will be an array with the columns being time frames and the
    % rows being frequency bins.
    [IR_f, f] = calc_STFT(IR, fs, win, nfft, nfft/rfft, 'onesided' );  % STFT output

    Energy_spectral = sum(abs(IR_f));       % Sum of spectral energy for each time frame

    [E, frame_index] = max(Energy_spectral);
    sample_index = max(1,(frame_index -1) *(nfft-rfft));
  
    
end

