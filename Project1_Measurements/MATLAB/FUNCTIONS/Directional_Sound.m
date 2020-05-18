 speakerPositions = zeros(36,2);
 degrees = zeros(36,1);
   for i = 1:36
       degree = i*10;
       rad = (i-1)*10*pi/180;
       speakerPositions(i,2) = sin(rad)/2 + 0.5;
       speakerPositions(i,1) = cos(rad)/2 + 0.5;
   end
   
   polar = polarplot(degrees,0);
   ax = gca;
   ax.RAxisLocation = 90;