package com.audiostoreoriental;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Message;
import android.view.ViewParent;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.logging.Handler;

public class ClientThread implements Runnable {

    private Socket socket;
    private BufferedReader input;
    public static final String SERVER_IP = "192.168.137.1"; //your computer IP address
    public static final int SERVER_PORT = 4242;
    public static final int KEY_MESSAGE = 1;
    public static final int KEY_CONTROL = 2;
    public static final int KEY_DATA = 3;
    android.os.Handler _Nethandler;

    public ClientThread(android.os.Handler handler) {
        this._Nethandler = handler;
    }

    @Override
    public void run() {
        try{
            InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
            socket = new Socket(serverAddr, SERVER_PORT);
            sendMessage("I am connected to you");
            while (!Thread.currentThread().isInterrupted()) {

                this.input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String message = input.readLine();
                if (null == message || "Disconnect".contentEquals(message)) {
                    Thread.interrupted();
                    message = "Server Disconnected.";
                    break;
                }
                Message m = Message.obtain();
                Bundle b = new Bundle();
                b.putString("net", message);
                m.setData(b);
                _Nethandler.sendMessage(m);
            }

        }
        catch (UnknownHostException e1) {
            e1.printStackTrace();
        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }

    void sendControl(final int control){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (null != socket) {
                        PrintWriter out = new PrintWriter(new BufferedWriter(
                                new OutputStreamWriter(socket.getOutputStream())),
                                true);
                        out.println(KEY_CONTROL + "\n" + control);
                        out.flush();

                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
    void sendMessage(final String message) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (null != socket) {
                        PrintWriter out = new PrintWriter(new BufferedWriter(
                                new OutputStreamWriter(socket.getOutputStream())),
                                true);
                        out.println(KEY_MESSAGE + "\n" + message);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    void sendFile(final String pathsave, final long totalAudioLen){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (null != socket) {
                        try {

                            PrintWriter out = new PrintWriter(new BufferedWriter(
                                    new OutputStreamWriter(socket.getOutputStream())),
                                    true);
                            out.println(KEY_DATA + "\n " +totalAudioLen);
                            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                            BufferedInputStream in = new BufferedInputStream(new FileInputStream(pathsave));
                            int read;
                            byte[] header = new byte[44];
                            read = in.read(header, 0, 44);
                            long audioLen = header[40] | header[41] << 8 | header[42] << 16 | header[43] << 24 ;
                            byte[] buff = new byte[1024];
                            while ((read = in.read(buff)) > 0) {
                                 byteArrayOutputStream.write(buff, 0, read);
                            }
                            byteArrayOutputStream.flush();
                            byte[] audioBytes = byteArrayOutputStream.toByteArray();

                            for(int i = 0; i < audioBytes.length; i++){
                                if(i == audioBytes.length-1)
                                    out.println(audioBytes);
                                else
                                     out.print(audioBytes[i] + ",");
                            }
                            out.flush();
                        }
                        catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

}
