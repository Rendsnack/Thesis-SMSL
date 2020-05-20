% this function averages the frequency magnitude per octaveband
function amp = avgAmplitudesPerAngle(y,fs, octaveBand)
% INPUT:
% -y: signal to be averagef
% -fs: sampling frequency
% -octaveBand: array containg octave band upper limits, see function 'getOctaveBands'

% OUTPUT:
% - amp: average amplitude per frequency band(columns)

    numOfOctaveBands = length(octaveBand)-1;
    NFFT = length(y);                   %get fft length
    Y = fft(y,NFFT);                    %go to frequency domain
    Midpoint = (NFFT/2)+1;              %get middle of frequency signal
    YdB = mag2db(abs(Y(1:Midpoint)));   %magnitude of first halve of frequency signal
    F = fs*(0:(NFFT/2))/NFFT;           %frequency indexes
    startIndex = 1;                                                         %start index of lowest frequency of first octave band
    for j = 1:numOfOctaveBands                                                   %for each octave band
        endFrequency = octaveBand(j+1);                                     %upper limit frequency of current octave band
        [~, endIndex] = min(abs(F-endFrequency));                           %find index closest to endFrequency
        amp(1,j) = mean(YdB(startIndex:endIndex));                 %average over octave band smaples
        startIndex = endIndex + 1;                                          %index of end frequency of this octave band is start index of next octave band
    end
end