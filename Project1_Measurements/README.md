# Project 1: Polar Pattern Measurement
This project consists of four key programs. Note that both the Android and Arduino device must be connected to the PC using a WiFi hotspot.

## Server side tutorial
The first program, **SERVER**, runs a Transmission Control Protocol (TCP) server, written in C which controls the flow of the measurement.
The executable is found under *AudioStorOrientalServer/Release/AudioStorOrientalServer.exe*. When you run this program, the main window will open. Once a device (Android or Arduino) is connected, the message log on the bottom left will show this.
For example if the Android smartphone connects to the PC using its Android application (discussed below), the following message is seen:
![](images/mainwindow.PNG)

You still have to select the correct IP address of the Android and Arduino device. Failing to do so correctly will cause the program to shut down.
The next step is to select the correct output channel and the corresponding signal. All signal types should be stored in the folder *SERVER/AudioStorOrientalServer/Signals* and have .wav extension. 
Once the signal is select you can test the audio with the *Test audio* button.
The last step is to set the step size of the motor. Each step is 1.8°. Therefore to replicate the measurement, set the step size to 9 degrees. The arduino will send a confirmation command back if the step size is received correctly. 

* Note that you have to align the stepper motor of the Arduino manually with the speaker.*

Once everything works, press the *Run Automatic* button. This will start a synchronized process of recordings.
The process is as follows:
<ol>
  <li> The server sends a command to the Android to start recording and waits for a confirmation of the Android.</li>
  <li> The server receives confirmation of the Android and plays the selected signal. </li>
  <li> Once the selected signal is finished playing, the server sends a command to the Android to stop recording and send the recording back to the server. </li>
  <li> Once the recording is received and stored at the server-side, the server sends a command to the Arduino to rotate the stepper motor with the specified step size. The step count is incremented. </li>
  <li> One iteration of the process is finished. Return to 1. </li>
</ol>
The number of iterations depends on the specified step size. For a step size of 9° the process will have 40 iterations.
  
## Android side tutorial
The application on the Android is a multi-threaded program which runs a TCP client in one thread and a mediarecorder in the second thread. The main thread handles synchronization of the threads and also calculates the rotation of the smartphone.
The UI is kept simple as seen here.

![](images/android.png)

Before the server can actually run, you have to press the *connect* button on the Android application to connect with the server program.
Afterwards the Android application is completely controlled by the server.

## Arduino side considerations
