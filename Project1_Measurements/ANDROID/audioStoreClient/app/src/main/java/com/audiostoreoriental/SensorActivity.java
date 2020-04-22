package com.audiostoreoriental;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

public class SensorActivity extends Activity implements SensorEventListener {

    Context callingContext;

    private SensorManager sensorManager;
    private Sensor mGravity;
    private Sensor mGeoMagnetic;
    private Sensor mRotationVector;

    public float[] gravity;
    public float[] geoMagnetic;
    public float[] rotationMatrix = new float[9];
    public float[] orientation = new float[3];

    TextView x_val_rotv;    //X-value obtained by rotation vector
    TextView y_val_rotv;
    TextView z_val_rotv;
    TextView x_val_acmg;    //X-value obtained by combination of accelerometer and magnetometer
    TextView y_val_acmg;
    TextView z_val_acmg;

    public int azimuth; //rotation around Z-axis
    public int pitch;   //rotation around X-axis
    public int roll;    //rotation around Y-axis1

    private boolean accelerometerUpdated = false;
    private boolean magnetometerUpdated = false;

    public SensorActivity(Context ogContext, SensorManager sensorManager, TextView textViewX, TextView textViewY, TextView textViewZ, TextView textViewX2, TextView textViewY2, TextView textViewZ2)
    {
        this.sensorManager = sensorManager;

        x_val_rotv = textViewX;
        y_val_rotv = textViewY;
        z_val_rotv = textViewZ;
        x_val_acmg = textViewX2;
        y_val_acmg = textViewY2;
        z_val_acmg = textViewZ2;

        callingContext = ogContext;

        initSensors();
    }

    /*
        Check sensor availability.
        Ideally the devices supports the RotationVector: Compass + Gyroscope.
        If not, this function checks for an Accelerometer + Compass combo.
        An error message is presented to the user if no necessary sensor is available.
     */
    private void initSensors()
    {
        if (sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR) != null)
        {
            mRotationVector = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
            sensorManager.registerListener(this, mRotationVector, SensorManager.SENSOR_DELAY_UI);
            Toast.makeText(callingContext, "Using Rotation Vector.", Toast.LENGTH_SHORT).show();
        }

        if ((sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) != null) && (sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD) != null))
        {
            mGravity = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            mGeoMagnetic = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
            sensorManager.registerListener(this, mGravity, SensorManager.SENSOR_DELAY_UI);
            sensorManager.registerListener(this, mGeoMagnetic, SensorManager.SENSOR_DELAY_UI);
            Toast.makeText(callingContext, "Using Accelerometer and Magnetometer.", Toast.LENGTH_SHORT).show();
        }

        if ((sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR) == null) && ((sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) == null) || (sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD) == null)))
        {
            noSensorsAlert();
        }
    }

    private void noSensorsAlert()
    {
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(callingContext);
        alertDialog.setMessage("Your device doesn't support the necessary sensors.")
                .setCancelable(true)
                .setNegativeButton("Close",new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        finish();
                    }
                });
        alertDialog.show();
    }

    @Override
    public final void onAccuracyChanged(Sensor sensor, int accuracy) {
        // Do something here if sensor accuracy changes.
        Toast.makeText(callingContext, "Accuracy Changed of Sensor "+sensor.getName(), Toast.LENGTH_SHORT).show();
    }

    @Override
    public final void onSensorChanged(SensorEvent event) {
        if( event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR)
        {
            SensorManager.getRotationMatrixFromVector(rotationMatrix, event.values);
            azimuth = (int) (Math.toDegrees(SensorManager.getOrientation(rotationMatrix, orientation)[0]) + 360) % 360;
            pitch = (int) (Math.toDegrees(SensorManager.getOrientation(rotationMatrix, orientation)[1]) + 360) % 360;
            roll = (int) (Math.toDegrees(SensorManager.getOrientation(rotationMatrix, orientation)[2]) + 360) % 360;

            x_val_rotv.setText(String.valueOf(pitch));
            y_val_rotv.setText(String.valueOf(roll));
            z_val_rotv.setText(String.valueOf(azimuth));
        }

        if( event.sensor.getType() == Sensor.TYPE_ACCELEROMETER )
        {
            gravity = event.values;
            accelerometerUpdated = true;
        }
        if( event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD )
        {
            geoMagnetic = event.values;
            magnetometerUpdated = true;
        }
        if( accelerometerUpdated == true && magnetometerUpdated == true )
        {
            accelerometerUpdated = false;
            magnetometerUpdated = false;
            boolean success = SensorManager.getRotationMatrix(rotationMatrix, null, gravity, geoMagnetic);
            if ( !success )
            {
                Log.d("SensorActivity", "Failed to extract sensor measurement data.");
                return;
            }

            azimuth = (int) (Math.toDegrees(SensorManager.getOrientation(rotationMatrix, orientation)[0]) + 360) % 360;
            pitch = (int) (Math.toDegrees(SensorManager.getOrientation(rotationMatrix, orientation)[1]) + 360) % 360;
            roll = (int) (Math.toDegrees(SensorManager.getOrientation(rotationMatrix, orientation)[2]) + 360) % 360;

            x_val_acmg.setText(String.valueOf(pitch));
            y_val_acmg.setText(String.valueOf(roll));
            z_val_acmg.setText(String.valueOf(azimuth));
        }
    }


    protected void deleteSensors() {
        sensorManager.unregisterListener(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        deleteSensors();
    }
}