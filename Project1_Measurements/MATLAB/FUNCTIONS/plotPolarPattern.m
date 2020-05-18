% This funnction takes the audio files in a directory and turns them into a
% polar pattern plot.
function [avgAmplitude, avgAmplitudeScaled, avgHAmplitude] = plotPolarPattern(folderPath, numOfOctaveBands, plotAll)
% INPUT:
% -folderPath: string containing path to folder containing audio files.
% -numOfOctaveBands: in how many octave bands the frequency signal will be
% divided
% -plotAll: boolean which cotnrolls whether to plot everything or solely
% return the arrays

% OUTPUT:
% - avgAmplitude: average amplitude per frequency band(columns) per
% recording(rows)
% a polar plot

%% get directory
directory = dir([folderPath '\*.wav']);

%% check directory
if isempty(directory)
    disp('Error: no audio files found!');
    avgAmplitude = 0;
   return; 
end

%% retrieve all audiorecrodings, read them into arrays and store these arrays in a struct called 'audio'
for i=1:length(directory)
    fileName = directory(i).name; fprintf(fileName,'%s'); fprintf('\n');
    filePath = [folderPath '\' fileName];
    [audio(i).data, audio(i).fs] = audioread(filePath);
end; clear i;
clear fileName;

%% convert recordings to frequency domain, split in frequency bands and take average
octaveBand = getOctaveBands(audio(1).fs/2 ,numOfOctaveBands);
% numOfOctaveBands = length(octaveBand)-1;
x = sweeptone(1.5,0.5,audio(1).fs,'SweepFrequencyRange',[1 22050]);
avgAmplitude = zeros(length(audio), numOfOctaveBands);  %columns: octavebands, rows: recordings
avgHAmplitude = zeros(length(audio), numOfOctaveBands);  %columns: octavebands, rows: recordings
for i = 1:length(audio) %for each audio file
    y = audio(i).data;                  %get audio samples
    fs = audio(i).fs;                   %get sampling frequency
    [h,C,n0] = impulse_response_calc(x, 1, 2205, fs, y);
    h = shortenImpulseResponse(h, 20, 441);
    avgAmplitude(i,:) = avgAmplitudesPerAngle(y,fs,octaveBand);
    avgHAmplitude(i,:) = avgAmplitudesPerAngle(h,fs,octaveBand);
end; clear i;
clear startIndex; clear endIndex; clear endFrequency;

%% feature scale between 0 and 1
avgAmplitudeScaled = normalize(avgAmplitude, 'range');

%% plot polar pattern
if plotAll
    % prepare data:
    avgAmplitudeCircular = [avgAmplitude; avgAmplitude(1,:)];   %to go full circle when calling polarplot
    % plot:
    figure
    polarplot(avgAmplitudeCircular);
    % create title using pathname:
    pathArray = split(directory(1).folder,'\');
    newTitle = ['polar pattern: ', pathArray(end-1), '/', pathArray(end)];
    title(join(newTitle), 'Interpreter', 'none');
    % create legend:
    legendCell = cellstr(num2str(octaveBand(2:end)','fend=%4.2f Hz'));
    legend(legendCell);
    clear legendCell;

    % prepare data:
    avgHAmplitudeCircular = [avgHAmplitude; avgHAmplitude(1,:)];   %to go full circle when calling polarplot
    % plot:
    figure
    polarplot(avgHAmplitudeCircular);
    % create title using pathname:
    pathArray = split(directory(1).folder,'\');
    newTitle = ['polar pattern: ', pathArray(end-1), '/', pathArray(end)];
    title(join(newTitle), 'Interpreter', 'none');
    % create legend:
    legendCell = cellstr(num2str(octaveBand(2:end)','fend=%4.2f Hz'));
    legend(legendCell);
    clear legendCell;
end
end