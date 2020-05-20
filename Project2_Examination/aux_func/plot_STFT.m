function [X] = plot_STFT(x,fs, name)
%PLOT_STFT Plot stft domain of signal
%   x:  time-domain signal
%   fs: sampling frequency of signal

% Original Speech sample STFT domain: Weighted Overlap Add method
%%%%%%% WOLA parameters %%%%%%%
L = length(x);
N_fft = 512;                        % 512 points
R_fft = N_fft/2;                    % shifting (50% overlap)
win = sqrt(hann(N_fft,'periodic')); % analysis window
N_half = floor(N_fft/2)+1;          % number of bins in onsided FFT 
freqs = 0:fs/N_fft:fs/2;            % one-sided set of actual frequencies

X = calc_STFT(x, fs, win, N_fft, N_fft/R_fft, 'onesided');
[N_freqs, N_frames] = size(X); 
times = [0:(N_half-1)/fs:(L-1)/fs];
times = times(2:end-1);

freqs = [fs/(N_freqs*2):fs/(N_freqs*2):fs/2];

magnitude = abs(X);
phase = rad2deg(angle(X));
phase_max = max(phase, [], 'all');
phase_min = min(phase, [], 'all');
titl = sprintf("%s: Magnitude", name); 
imagesc(times,freqs,mag2db(magnitude), [-65, 10]); axis xy; set(gcf,'color','w');set(gca,'Fontsize',14); xlabel('Time (s)'), ylabel('Frequency (Hz)'), ...
    title(titl); 
c = colorbar;
c.Label.String = 'Amplitude (dB)';
% 
% titl = sprintf("%s: Phase", name); 
% subplot(2,1,2);imagesc(times,freqs,phase, [phase_min, phase_max]); axis xy; set(gcf,'color','w');set(gca,'Fontsize',14); xlabel('Time (s)'), ylabel('Frequency (Hz)'), ...
%    title(titl); 
% c = colorbar;
% c.Label.String = 'Phase (°)';


end

