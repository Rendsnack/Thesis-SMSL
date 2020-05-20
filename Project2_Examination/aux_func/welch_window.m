function [x_windowed_fft] = welch_window(x,segmentLength, noverlap, win)
%WELCH_WINDOW The input is segmented and windowed before applying the welch
% estimate


    L = length(x);
    nSegments = ceil((L-segmentLength)/(segmentLength-noverlap))+1;
    nZeros = ((nSegments+1)*noverlap) - L;
    x_zero_padded = [x; zeros(nZeros,1)];         % Signal is now zero padded, time to split and window
    x_windowed_fft = zeros(segmentLength,nSegments);
    for k = 1:nSegments
        index = max(1, ((k-1)*noverlap));
        segment = x_zero_padded(index:index+segmentLength-1);
        x_windowed_fft(:,k) = fft(segment.*win);
    end
    
    
end

