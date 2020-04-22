package com.audiostoreoriental;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

public class SineSweep {
    private final int sampleRate = 48000;
    double startFrequency;
    double endFrequency;
    int numSamples;
    private final double sample[];
    private final byte generatedSnd[];

    public SineSweep(double startFrequency, double endFrequency, int duration)
    {
        this.startFrequency = startFrequency;
        this.endFrequency = endFrequency;
        numSamples = duration * sampleRate;
        sample = new double[numSamples];
        generatedSnd = new byte[2 * numSamples];

        generateTone();
    }

    private void generateTone()
    {
        double currentFreq = 0, numerator;
        for (int i = 0; i < numSamples; ++i) {
            numerator = (double) i / (double) numSamples;
            currentFreq = startFrequency + (numerator * (endFrequency - startFrequency))*0.5;
            if ((i % 1000) == 0) {
                Log.e("Current Freq:", String.format("Freq is:  %f at loop %d of %d", currentFreq, i, numSamples));
            }
            sample[i] = Math.sin(2 * Math.PI * i / (sampleRate / currentFreq));
        }
        convertToPCM();
    }

    private void convertToPCM()
    {
        int idx = 0;
        for (final double dVal : sample) {
            // scale to maximum amplitude
            final short val = (short) ((dVal * 32767));
            // in 16 bit wav PCM, first byte is the low order byte
            generatedSnd[idx++] = (byte) (val & 0x00ff);
            generatedSnd[idx++] = (byte) ((val & 0xff00) >>> 8);
        }
    }

    protected void playSound(){
        final AudioTrack audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                sampleRate, AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT, generatedSnd.length,
                AudioTrack.MODE_STATIC);
        audioTrack.write(generatedSnd, 0, generatedSnd.length);
        audioTrack.play();
    }


}
