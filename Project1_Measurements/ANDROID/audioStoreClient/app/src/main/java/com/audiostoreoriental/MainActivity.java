package com.audiostoreoriental;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.hardware.SensorManager;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.io.File;
import java.io.IOException;

public class MainActivity extends Activity {
    public static final String TAG = "MainActivity";

    private TextView mTextView;
    public String logMessage = "Click" ;

    // Initialization for Audio Record and Store ***************************************************
    RecordThread recordThread;

    final int REQUEST_PERMISSION_CODE = 1000;
    // Initialization of Rotation Vector ***********************************************************
    TextView ThetaXROTV;
    TextView ThetaYROTV;
    TextView ThetaZROTV;
    // Initialization of Accelerometer and Magnetometer
    TextView ThetaXACMG;
    TextView ThetaYACMG;
    TextView ThetaZACMG;
    SensorActivity sensors;
    private final float[] deltaRotationVector = new float[5];
    private float timestamp;

    // Initialize TCP connections******************************************************************
    Button connectTcp;
    ClientThread clientThread;
    Thread threadNet;
    Thread threadRec;
    TcpClient mTcpClient;
    public Handler _handler;
    private Bundle bb = new Bundle();

    // For sinesweep*******************************************************************************
    SineSweep sweeper;
    double startFrequency = 20;
    double endFrequency = 20000;
    int duration = 10;  // in seconds

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.v(TAG, "onCreate");
        setContentView(R.layout.activity_main);

        connectTcp = findViewById(R.id.connectTCP);
        connectTcp.setText("Connect");
        connectTcp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(connectTcp.getText() == "Connect") {
                        _handler = new Handler(Looper.getMainLooper()){
                            @Override
                            public void handleMessage(Message msg) {
                                bb = msg.getData();
                                String strNet = bb.getString("net");
                                String strRec = bb.getString("rec");
                                if(strNet != null) processMessage(strNet, "net");
                                if(strRec != null) processMessage(strRec, "rec");
;
                            }
                        };
                        clientThread = new ClientThread(_handler);
                        threadNet = new Thread(clientThread);
                        threadNet.start();
                        connectTcp.setText("Disconnect");
                }
                else
                {
                    threadNet = null;
                    connectTcp.setText("Connect");
                }
            }
        });

        if(checkPermissionFromDevice()){
            if(clientThread != null)
                clientThread.sendMessage("Permissions granted! \n");
        }
        else requestPermission();

        // Get rotation vector
        ThetaXROTV = findViewById(R.id.tv_X_rotv);
        ThetaYROTV = findViewById(R.id.tv_Y_rotv);
        ThetaZROTV = findViewById(R.id.tv_Z_rotv);
        ThetaXACMG = findViewById(R.id.tv_X_acmg);
        ThetaYACMG = findViewById(R.id.tv_Y_acmg);
        ThetaZACMG = findViewById(R.id.tv_Z_acmg);

        SensorManager sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        sensors = new SensorActivity(this, sensorManager, ThetaXROTV, ThetaYROTV, ThetaZROTV, ThetaXACMG, ThetaYACMG, ThetaZACMG);

        sweeper = new SineSweep(startFrequency, endFrequency, duration);
        Button sineSweepButton = findViewById(R.id.bt_sineSweep);
        sineSweepButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sweeper.playSound();
            }
        });
}

    private String processMessage(String str, String key) {
        if( key == "net") {
            if (str.contains("1")) { //Start Record command

                if (threadRec == null) {
                    recordThread = new RecordThread(_handler);
                    threadRec = new Thread(recordThread);
                    threadRec.start();
                }
                else
                    clientThread.sendControl(1);
                return "k";
            } else if (str.contains("2")) {
                if(recordThread != null) {
                    if (recordThread.getIsRecording()) {
                        recordThread.stopRecording();
                        threadRec = null;
                    }
                }
                else
                    clientThread.sendControl(2);
                return "k";
            } else if (str.contains("3")){
                clientThread.sendFile(recordThread.getFilePath(), recordThread.getTotalAudioLen());
                recordThread.incrementRecordIndex();
            }
            else
                return "invalid command";
        }
        else if(key == "rec"){
            if(str.contains("1"))
                clientThread.sendControl(1);
            else if(str.contains("2"))
                clientThread.sendControl(2);
            else
                clientThread.sendMessage(str);

                return "k";
        }

        return "invalid command";

    }

    protected void onResume() {
        super.onResume();
        Log.v(TAG, "onResume");
    }

    protected void onPause() {
        super.onPause();
        Log.v(TAG, "onPause");
    }
    protected void onStop(){
        super.onStop();
        Log.v(TAG, "onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (null != threadNet) {
            threadNet = null;
        }
        if(null != threadRec){
            threadRec = null;
        }
    }

    /** Show Dialog when method mDialog used. */
    public void mDialog(String mMessage){
        AlertDialog.Builder builder =new AlertDialog.Builder(MainActivity.this);
        builder.setMessage(mMessage)
                .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                }).create().show();
    }

    private void requestPermission() {
        ActivityCompat.requestPermissions(this, new String[]{
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.RECORD_AUDIO
        }, REQUEST_PERMISSION_CODE);

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch(requestCode){
            case REQUEST_PERMISSION_CODE: {
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                    mDialog("Permission Granted");
                else
                    mDialog("Permission Denied");
            }
        }
    }

    private boolean checkPermissionFromDevice() {
        int write_external_storage_result = ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        int record_audio_result = ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO);
        return write_external_storage_result == PackageManager.PERMISSION_GRANTED && record_audio_result == PackageManager.PERMISSION_GRANTED;
    }
}