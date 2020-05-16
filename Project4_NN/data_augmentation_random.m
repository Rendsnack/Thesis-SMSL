%% convolve randoly selected audio with different IR
% audio is randomly selected from different sub-folders of a given folder
%% prepare workspace
clc; clear; close all;

%% ADMIN
% set input and output folders
readAudioFrom = 'D:\Users\MC\Documents\UNI\MASTER\thesis\LibriSpeech\train-clean-360\*\*\*.flac';
readIRFrom = 'D:\Users\MC\Documents\UNI\MASTER\thesis\Learning_Model\aux_data\IR_Z_fixed\2s\';
writeTo = 'D:\Users\MC\Documents\UNI\MASTER\thesis\AUGMENTED_DATA\data5_unseen\';
% how many files to read
numOfFilesToRead = 1500;

%% get all files into struct 'directory'
directory = dir(readAudioFrom);
numOfFiles = length(directory);
load('used_speakers')
% if numOfFiles == 0
%     folderPath = [readAudioFrom '*.flac'];
%     directory = dir(readAudioFrom);
%     numOfFiles = length(directory);
% end
% randomly generate list of unique indexes
if numOfFilesToRead > numOfFiles
    indexes = randperm(numOfFiles, numOfFiles)';
else
    indexes = randperm(numOfFiles, numOfFilesToRead)';
end
clear readAudioFrom numOfFiles numOfFilesToRead;
%% get all impulse responses (IR)
folderPath = [readIRFrom '\*.mat'];
directoryIR = dir(folderPath);
for j=1:length(directoryIR)
    filePath = [directoryIR(j).folder '\' directoryIR(j).name];
    load(filePath);
end
clear readIRFrom folderPath filePath directoryIR j;

%% prepare upsampler (designed to upsample from 16k->44.1kHz)
originalFrequency = 16e3;
upsampledFrequency = 44.1e3;
[L,M] = rat(upsampledFrequency/originalFrequency);
f = (originalFrequency/2)*min(1/L,1/M);
d = designfilt('lowpassfir', ...
    'PassbandFrequency',0.9*f,'StopbandFrequency',1.1*f, ...
    'PassbandRipple',5,'StopbandAttenuation',40, ...
    'DesignMethod','kaiserwin','SampleRate',16000);
h_upsampler = L*tf(d);
clear f;

%% create log file
writeToLog([writeTo 'LOG.txt'],'log file created');

%% get each audio file and upsample to 44.1kHz
for index = 1:length(indexes)    
    %% read in audio
    i = indexes(index);
    
    % get random audiofile
    filePath = [directory(i).folder '\' directory(i).name];
    writeToLog([writeTo 'LOG.txt'],filePath);
    % extract audio filename
    audioFileName = split(directory(i).name, '.');
    audioFileName = audioFileName{1};
    audioFileNameSplit = split(audioFileName, '-');
    readerID = audioFileNameSplit{1};
%     readerID = strrep(audioFileName, 'speech-','')
    if any(strcmp(CELL,readerID))
        disp('song already exists')
        continue
    end
    
    % extract audio
    try
        [x,fs] = audioread(filePath, [1,originalFrequency*10]);
    catch exception
        disp('EXCEPTION:')
        disp(exception.message)
        % if exception is due to trying to read more than is in the file
        if (strcmp(exception.identifier,'MATLAB:audiovideo:audioread:endoffile'))
            [x,fs] = audioread(filePath);   %read entire audiofile isntead of short version
        end
        writeToLog([writeTo 'LOG.txt'],exception.message);
    end
    if size(x,2) > 1
       x = x(:,1); 
    end
    if fs~= originalFrequency && fs ~= upsampledFrequency
        disp('ERROR:')
        disp('unsuported sampling rate: adjust upsampling filter');
        writeToLog([writeTo 'LOG.txt'],'unsuported sampling rate: adjust upsampling filter');
        continue
    end
    
    if fs == originalFrequency
        % upsample
        x_u = upfirdn(x,h_upsampler,L,M);
        delay = floor(((filtord(d)-1)/2-(L-1))/L);
        x_u = x_u(delay+1:end);
    else
        x_u = x;
    end
    clear x fs delay;
    
    filePath = [writeTo 'random_selection_of_speakers.txt']
    try 
        fid = fopen(filePath, 'a+');
        fprintf(fid, '%s\n', readerID);
        fclose(fid);
    catch exception
        disp('EXCEPTION:')
        disp(exception.message)   
        writeToLog([writeTo 'LOG.txt'],exception.message);
    end
    clear fid readerID audioFileNameSplit;

    %% iterate over directions
    for k=0:39
        %% get the current direction
        direction = k*9;

        %% make sub-folder for this direction to which files will be written
        writeAudioTo = [writeTo num2str(direction) '\']
        [status, msg] = mkdir(writeAudioTo);
        if status == 0
            %failed to make directory
            disp(msg)
            quit
        end
        clear status msg

        %% extract all IRs at a certain index and store in struct 'H'
        % an index corresponds to an angle, e.g.: 0 =0 °; 1 = 9°; 2 = 18°
        irIndex = k+1; % +1 to adhere to matlabs indexing rules
        h_10 = IR44K_2s_10ms{irIndex,2};      H(1).h=h_10;    H(1).name = 'h_10';
        h_50 = IR44K_2s_50ms{irIndex,2};      H(2).h=h_50;    H(2).name = 'h_50';
        h_100 = IR44K_2s_100ms{irIndex,2};    H(3).h=h_100;   H(3).name = 'h_100';
        h_500 = IR44K_2s_500ms{irIndex,2};    H(4).h=h_500;   H(4).name = 'h_500';
        h_1000 = IR44K_2s_1000ms{irIndex,2};  H(5).h=h_1000;  H(5).name = 'h_1000';
        clear h_10 h_50 h_100 h_500 h_1000

        % convolve with each IR
        for j=1:length(H)
            y = conv(x_u,H(j).h);
            % normalize
            y  = y/max(abs(y));
            % shorten
            if length(y) > 220500
                y = y(1:220500);
            end
            %save
            filePath = [num2str(direction) '_' H(j).name '_' audioFileName '.wav'];
            filePath = [writeAudioTo filePath];
            disp(filePath);
            try
                audiowrite(filePath, y, upsampledFrequency);
            catch exception
                disp('EXCEPTION:')
                disp(exception.message)   
                writeToLog([writeTo 'LOG.txt'],exception.message);
            end
        end
        clear i filePath y j readerID;
    end
    clear c folderPath;
end

function writeToLog(filePath, msg)
    try 
        fid = fopen(filePath, 'a+');
        fprintf(fid, '%s\n', msg);
        fclose(fid);
    catch exception
        disp('EXCEPTION:')
        disp(exception.message)   
    end
    clear fid ;
end