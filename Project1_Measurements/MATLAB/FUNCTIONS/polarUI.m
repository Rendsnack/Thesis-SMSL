function polarUI
% polarplot plots the pickup patterns and Frequency-Angle plot using
% the input samples from 36 recordings.     

addpath(genpath(fullfile('../')));
%  Create and then hide the UI as it is being constructed.
width = 0;
height = 0;
f = figure('Name', 'ui_part3a', 'Visible','off','WindowState', 'maximized', 'SizeChangedFcn', @adjust);
figMain= get(groot, 'CurrentFigure');
width = figMain.Position(3);
height = figMain.Position(4);
    

%Check out the folder Data/... for available orientations
dataDir = dir('Data/');
dataDir = dataDir(3:end);
N_angle = size(dataDir,1);
freqDirs = strings(N_angle, 1);
for i = 1:N_angle
    freqDirs(i) = sprintf("Directory selected: %s", dataDir(i).name);
end

testDir = dir('Signals/');
testDir = testDir(3:end);
N_testSig = size(testDir,1);
testSine = strings(N_testSig,1);
for i = 1:N_testSig
    testSine(i) = sprintf("Test signal selected: %s", testDir(i).name);
end

%Text + Popupmenu: Select sinesweep delay of interest
htextSine = uicontrol('Tag', 'htextSine', 'Style','text','String','Select Test signal',...
    'Position',[width*0.1 , height*0.9,width*0.15, height*0.1]);
selectSine = uicontrol('Style','popupmenu', 'Tag', 'selectSine',...
    'String',testSine,...
    'Callback', {@selectSine_callback, f}, ...
    'Position',[width*0.3,height*0.9,width*0.2,height*0.1]);
%Text + Popupmenu: Select directory of interest
htextdir = uicontrol('Tag', 'htextdir', 'Style','text','String','Select directory',...
    'Position',[width*0.1 , height*0.8,width*0.15, height*0.1]);
selectDir = uicontrol('Style','popupmenu', 'Tag', 'selectDir',...
    'String',freqDirs,...
    'Callback', {@selectDir_callback, f}, ...
    'Position',[width*0.3,height*0.8,width*0.2,height*0.1]);

% Check selected dataFolder for signals
sigDir = dir(strcat('Data/', dataDir(1).name));
sigDir = sigDir(3:end);
N_sigs = size(sigDir,1);
if N_sigs == 0
    sigWaves = "No recordings found";
else
    sigWaves = strings(N_sigs, 1);
    for i = 1:N_angle
        sigWaves(i) = sprintf("Directory selected: %s", sigDir(i).name);
    end
end
%Text + Popupmenu: Select Signal to Inspect
htextsig = uicontrol('Tag', 'htextsig', 'Style','text','String','Select a signal to inspect',...
    'Position',[width*0.1 , height*0.7,width*0.15, height*0.1]);
selectsig = uicontrol('Style','popupmenu', 'Tag', 'selectSignal',...
    'String',sigWaves,...
    'Callback', @selectSig_callback, ...
    'Position',[width*0.3,height*0.7,width*0.2,height*0.1]);

% Button: Plot polar pattern
runPolar  =   uicontrol('Tag', 'run', 'Style', 'pushbutton', 'String', 'polar pattern', ...
    'Callback',{ @runButton_callback, f}, ...
    'Position', [width*0.7, height*0.8, width*0.2, height*0.1]);

% Button: Plot selected signal
runInspect  =   uicontrol('Tag', 'InspectSignal', 'Style', 'pushbutton', 'String', 'plot data', ...
    'Callback',{ @inspectSignal_callback, f}, ...
    'Position', [width*0.7, height*0.65, width*0.2, height*0.1]);

% Plot: Inspect Magnitude and Phase of particular signal
Magnitude = axes('Tag', 'MagnitudeY', 'Units', 'Pixels', 'Position',[width*0.1,height*0.55,width*0.3,height*0.3]); 
Phase = axes('Tag', 'PhaseY', 'Units', 'Pixels', 'Position',[width*0.1,height*0.1,width*0.3,height*0.3]); 

% Polar pattern plot
polar = axes('Tag', 'pickUpPattern', 'Units', 'Pixels', 'Position',[width*0.5,height*0.55,width*0.3,height*0.3]); 
% Frequency-Angle plot 
FreqAngle = axes('Tag', 'FreqAngle', 'Units', 'Pixels', 'Position',[width*0.5,height*0.1,width*0.3,height*0.3]);

% Make the UI visible.
   f.Visible = 'on';
% --- Executes on button press in pushbutton1.
function runButton_callback(source, eventdata, f)
% hObject    handle to Run button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

addpath(genpath(fullfile('..')));

% Get selected Sine
    selectedSine = findobj(f,'Tag', 'selectSine');
    indexSine = selectedSine.Value;
    sineDir = dir("Signals");
    sineDir = sineDir(3:end);
    [sine fs] = audioread(sineDir(indexSine).name);
    
% Process the data in directory
selectedDirs = findobj(f, 'Tag', 'selectDir');
index = selectedDirs.Value;
datadir = dir("Data");
datadir = datadir(3:end);
StringDir = "Data/" + datadir(index).name;
dirAngle = dir(StringDir);
dirAngle = dirAngle(3:end)
dirLength = size(dirAngle,1);
% Averages: 0-325, 325-750, 750-1500, 1500-3000, 3000-6000,
    % 6000-12000

avgAmplitude = zeros(dirLength, 6);
for i = 1:dirLength
    wav_file = StringDir +'/' + dirAngle(i).name;
    [y fs] = audioread(wav_file);
    NFFT = length(y);
    Y = fft(y,NFFT);
    YdB = mag2db(abs(Y));
    Midpoint = (NFFT/2)+1;
    YdB = YdB(1:Midpoint);
    F = fs*(0:(NFFT/2))/NFFT;
    steps = zeros(7,1);
    steps(1) = 1;
    currentVal = 325;
    for j = 1:6
        steps(j+1) = floor(currentVal/ (fs/(2*Midpoint)));
        currentVal = currentVal*2;
        avgAmplitude(i,j) = mean(YdB(steps(j):steps(j+1)+1));
    end
    
    
    % Octave bands: 0-325, 325-750, 750-1500, 1500-3000, 3000-6000,
    % 6000-12000
    % Position F = 0:Fs/2 --> 325/(fs/(2*NFFT))   
end
avgAmplitude = [avgAmplitude; avgAmplitude(1,:)];
polarObj = findobj(f,'Tag', 'pickUpPattern');
axes(polarObj);
theta = 0:360/dirLength:360-(360/dirLength);
p = 0;
figure
for i = 1:6
    p = polarplot(avgAmplitude(:,i));
    hold on;
end
freqstep = ["0-325", "325-750", "750-1500", "1500-3000", "3000-6000", "6000-12000"];
legend(freqstep+ "Hz");

end

function inspectSignal_callback(src, callbackdata, f)
    % hObject    handle to Run button (see GCBO)
    % eventdata  reserved - to be defined in a future version of MATLAB
    % handles    structure with handles and user data (see GUIDATA)
    
    addpath(genpath(fullfile('..')));
    
    % Get directory
    selectedDirs = findobj(f, 'Tag', 'selectDir');
    indexDir = selectedDirs.Value;
    datadir = dir("Data");
    datadir = datadir(3:end);
    
    StringDir = "Data/" + datadir(indexDir).name;
    dirAngle = dir(StringDir);
    dirAngle = dirAngle(3:end);
    
    % Get selected signal 
    selectedSignal = findobj(f, 'Tag', 'selectDir');
    indexSig = selectedSignal.Value;
    selectedSignalString = dirAngle(indexSig).name;
    wav_file = StringDir + '/' + selectedSignalString;
    [y fs] = audioread(wav_file);
    NFFT = length(y);
    Y = fft(y,NFFT);
    Midpoint = (NFFT/2)+1;
    Y = Y(1:Midpoint);
    F = fs*(0:(NFFT/2))/NFFT;
    
    magY = abs(Y);      %% Magnitude of FFT
    magPlot = findobj(f, 'Tag', 'MagnitudeY');
    axes(magPlot);
    plot(F,magY); title(strcat('Magnitude response: ' , selectedSignalString));
    
    phaseY = unwrap(angle(Y)); %% Phase of FFT  
    phasePlot = findobj(f,'Tag', 'PhaseY');
    axes(phasePlot);
    plot(phaseY); title(strcat('Phase response: ' ,selectedSignalString));
end



end

function adjust(src, callbackdata, f)
        width = src.Position(3);
        height = src.Position(4);
        % get objects that need resizing
        htextSine = findobj(src,'Tag', 'htextSine');
        selectSine = findobj(src, 'Tag', 'selectSine');
        htextdir = findobj(src, 'Tag', 'htextdir');
        selectDir = findobj(src, 'Tag', 'selectDir');
        htextsig = findobj(src, 'Tag', 'htextsig');
        selectSig = findobj(src, 'Tag', 'selectSignal');
        
        polar = findobj(src, 'Tag', 'pickUpPattern');
        FreqAngle = findobj(src, 'Tag', 'FreqAngle');
        MagY = findobj(src, 'Tag', 'MagnitudeY');
        PhaseY = findobj(src, 'Tag', 'PhaseY');
        runPolar = findobj(src, 'Tag', 'run');
        runSignal = findobj(src, 'Tag', 'InspectSignal');
        
        % Adjust positions
        
        htextSine.Position = [width*0.1, height*0.9,width*0.15, height*0.05];
        selectSine.Position = [width*0.3, height*0.9,width*0.15, height*0.05];
        htextdir.Position = [width*0.1, height*0.85,width*0.15, height*0.05];
        selectDir.Position = [width*0.3,height*0.85,width*0.2,height*0.05];
        htextsig.Position = [width*0.1, height*0.8,width*0.15, height*0.05];
        selectSig.Position = [width*0.3,height*0.8,width*0.2,height*0.05];
        
        runPolar.Position = [width*0.8, height*0.8, width*0.2, height*0.1];
        runSignal.Position = [width*0.8, height*0.65, width*0.2, height*0.1];
        
        polar.Position = [width*0.5,height*0.5,width*0.25,height*0.25];
        FreqAngle.Position = [width*0.5,height*0.1,width*0.25,height*0.25];
        MagY.Position = [width*0.1,height*0.5,width*0.25,height*0.25];
        PhaseY.Position = [width*0.1,height*0.1,width*0.25,height*0.25];
        
        
        
end

function selectDir_callback(hObject, source, eventdata, f)
        if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
            set(hObject,'BackgroundColor','white');
        end
        indexDir = hObject.Value;
        
        % Check selected dataFolder for signals
        dataDir = dir('Data/');
        dataDir = dataDir(3:end);
        sigDir = dir(strcat('Data/', dataDir(indexDir).name));
        sigDir = sigDir(3:end);
        N_sigs = size(sigDir,1);
        if N_sigs == 0
            sigWaves = "No recordings found";
        else
            sigWaves = strings(N_sigs, 1);
            for i = 1:N_sigs
                sigWaves(i) = sprintf("Directory selected: %s", sigDir(i).name);
            end
        end
        selectSigObj = findobj(eventdata, 'Tag', 'selectSignal');
        selectSigObj.String = sigWaves;
        
end

function selectSig_callback(hObject, source, eventdata)
        if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
            set(hObject,'BackgroundColor','white');
        end
        
        
        
end

function selectSine_callback(hObject, source, eventdata)
        if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
            set(hObject,'BackgroundColor','white');
        end
        
        
        
end
