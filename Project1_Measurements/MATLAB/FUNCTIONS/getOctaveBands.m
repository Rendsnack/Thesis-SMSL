% this function gives the upper limits of each octave band, starting at the
% end frequency and calucalting down towards 0Hz
function octaveBand = getOctaveBands(Fend, numOfBands)
% INPUT:
% - Fend: highest frequency, typ. F_Nyq; this frequency will be continously
% halved
% - numOfbands: amount of times Fend is halved

% OUTPUT:
% -octaveBand: array of frequencies, these are the upper limits of the
% octave bands

octaveBand(numOfBands+1) = Fend;
    for i=numOfBands:-1:2
       octaveBand(i) =  octaveBand(i+1)/2;
    end
    octaveBand(1) = 0;
end