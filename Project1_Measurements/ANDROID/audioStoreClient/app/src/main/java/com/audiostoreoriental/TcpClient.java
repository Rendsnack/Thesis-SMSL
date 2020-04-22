package com.audiostoreoriental;

import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class TcpClient{

    public static final String SERVER_IP = "192.168.137.1"; //your computer IP address
    public static final int SERVER_PORT = 4242;
    // message to send to the server
    private String mServerMessage;
    // sends message received notifications
    private OnMessageReceived mMessageListener = null;
    // while this is true, the server will continue running
    private boolean mRun = false;
    // used to send messages
    private PrintWriter mBufferOut;
    // used to read messages from the server
    private BufferedReader mBufferIn;

    /**
     * Constructor of the class. OnMessagedReceived listens for the messages received from server
     */
    public TcpClient(OnMessageReceived listener) {
        mMessageListener = listener;
    }

    /**
     * Sends the message entered by client to the server
     * @param message text entered by client
     */
    public void sendMessage(String message) {
        if (mBufferOut != null && !mBufferOut.checkError()) {
            mBufferOut.println(message);
            mBufferOut.flush();
        }
    }

    /**
     * Sends the filename to tcp server
     *
     * @param filename filename constructed by rotation vector
     */
    public void sendFilename(String filename){
        //int filenameSize = filename.length(); // Reads number of bytes (1 char = 8 bits)
        if (mBufferOut != null && !mBufferOut.checkError()) {
            // mBufferOut.println(filenameSize);
            mBufferOut.println("FILENAME \n");
            mBufferOut.println(filename + "\n");
            mBufferOut.flush();
        }
    }

    /**
     * Sends the filename to tcp server
     *
     * @param file recorded file
     */
    public void sendFile(File file){
        if(file.exists()) {
            FileInputStream stream;
            try {
                stream = new FileInputStream(file);
                while(stream.available() > 4){
                    byte[] data = null;
                    stream.read(data,0, 4);
                    mBufferOut.println(data);
                    mBufferOut.flush();
                }
            }
            catch (Exception e) {
            }
        }
    }

    /**
     * Close the connection and release the members
     */
    public void stopClient() {

        // send mesage that we are closing the connection

        mRun = false;
        sendMessage("Client stopped connection \n");

        if (mBufferOut != null) {
            mBufferOut.flush();
            mBufferOut.close();
        }

        mMessageListener.messageReceived("Closing socket client side \n");
        mMessageListener = null;
        mBufferIn = null;
        mBufferOut = null;
        mServerMessage = null;
    }

    public void run() {

        mRun = true;

        try {
            //here you must put your computer's IP address.
            InetAddress serverAddr = InetAddress.getByName(SERVER_IP);

            Log.e("TCP Client", "C: Connecting...");

            //create a socket to make the connection with the server
            Socket socket = new Socket(serverAddr, SERVER_PORT);

            try{
                //sends the message to the server
                mBufferOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

                //in this while the client listens for the messages sent by the server
                while (mRun) {

                    if(socket.isClosed()){
                        mMessageListener.messageReceived("Socket server side closed");
                        mRun = false;
                    }
                    //receives the message which the server sends back
                    mBufferIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                    mServerMessage = mBufferIn.readLine();
                    while(mServerMessage != null){
                        mMessageListener.messageReceived(mServerMessage);
                        mServerMessage = mBufferIn.readLine();
                    }


                }

                Log.e("RESPONSE FROM SERVER", "S: Received Message: '" + mServerMessage + "'");

            } catch (Exception e) {

                Log.e("TCP", "S: Error", e);

            }
        } catch (Exception e) {

            Log.e("TCP", "C: Error", e);
            mMessageListener.messageReceived("connection failed");

        }

    }

    //Declare the interface. The method messageReceived(String message) will must be implemented in the MyActivity
    //class at on asynckTask doInBackground
    public interface OnMessageReceived {
        public void messageReceived(String message);
    }
}
