function gui_directional_sound
% gui_directional_sound allows interpretation of sound from different 
% locations by pressing the speakers.

   %  Create and then hide the UI as it is being constructed.
   f = uifigure('Visible','off','WindowState', 'Maximize');
          
   %  Construct the components
   menu = uipanel('Title', 'Menu', 'FontSize', 12,...
       'backgroundColor', 'white', ...
       'Position', [0.1 0.1 0.4 0.8]);
   plot = uipanel('Title', 'Compass', 'FontSize', 12,...
       'backgroundColor', 'white', ...
       'Position', [0.5 0.1 0.4 0.8]);
   bg = uibuttongroup(plot,...
                  'Position',[0.1 0.1 0.8 0.8]);
              
   %  Create RGB map of speaker icon
   [speaker_g map]= imread('speaker.png');
   speaker_rgb = ind2rgb(speaker_g, map);
   %  Position of speakers in cartesian coordinates [x, y]
   speakerPositions = zeros(36,2);
   degrees = zeros(36,1);
   for i = 1:36
       degrees = (i-1)*10;
       rad = (i-1)*10*pi/180;
       ypos = sin(rad)/2 + 0.5;
       xpos = cos(rad)/2 + 0.5;
       speaker = uicontrol(bg,'Style', 'pushbutton');
       speaker.Position =[xpos ypos 0.1 0.1];  
%        speaker.cdata = speaker_RGB;
   end
   speaker = uicontrol(bg,'Style', 'pushbutton');
   speaker.CData = speaker_rgb;
   % Make the UI visible.
   f.Visible = 'on';

%%
% Initialize the UI.
% Change units to normalized so components resize automatically.
f.Units = 'normalized';
ha.Units = 'normalized';
hsurf.Units = 'normalized';
hmesh.Units = 'normalized';
hcontour.Units = 'normalized';
htext.Units = 'normalized';
hpopup.Units = 'normalized';

% Generate the data to plot.
peaks_data = peaks(35);
membrane_data = membrane;
[x,y] = meshgrid(-8:.5:8);
r = sqrt(x.^2+y.^2) + eps;
sinc_data = sin(r)./r;

% Create a plot in the axes.
current_data = peaks_data;
surf(current_data);

% Assign the a name to appear in the window title.
f.Name = 'Simple GUI';

% Move the window to the center of the screen.
movegui(f,'center')

% Make the window visible.
f.Visible = 'on';

%  Pop-up menu callback. Read the pop-up menu Value property to
%  determine which item is currently displayed and make it the
%  current data. This callback automatically has access to 
%  current_data because this function is nested at a lower level.
   function popup_menu_Callback(source,eventdata) 
      % Determine the selected data set.
      str = get(source, 'String');
      val = get(source,'Value');
      % Set current data to the selected data set.
      switch str{val};
      case 'Peaks' % User selects Peaks.
         current_data = peaks_data;
      case 'Membrane' % User selects Membrane.
         current_data = membrane_data;
      case 'Sinc' % User selects Sinc.
         current_data = sinc_data;
      end
   end

  % Push button callbacks. Each callback plots current_data in the
  % specified plot type.

  function surfbutton_Callback(source,eventdata) 
  % Display surf plot of the currently selected data.
       surf(current_data);
  end

  function meshbutton_Callback(source,eventdata) 
  % Display mesh plot of the currently selected data.
       mesh(current_data);
  end

  function contourbutton_Callback(source,eventdata) 
  % Display contour plot of the currently selected data.
       contour(current_data);
  end
end