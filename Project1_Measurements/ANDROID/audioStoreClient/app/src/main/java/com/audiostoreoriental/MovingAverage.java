package com.audiostoreoriental;

public class MovingAverage {

    private final double[] window;
    private float sum = 0f;
    private int fill;
    private int position;   //keeps track of oldest value
    private int min;

    public MovingAverage(int size, int range)   {
        this.window = new double[size];
        this.min = range;

    }

    public void add(float number) {
        double angle = Math.toDegrees(number);
        if(angle < 0){
            angle += min;
        }
        if( fill == window.length ){
            sum -= window[position];    //subtract oldest value
        }else{
            fill++;
        }

        sum += angle;
        window[position++] = angle;    //overwrite oldest value

        if( position == window.length ){
            position = 0;
        }

    }

    public double getAverage() {

        return sum/fill;
    }
}
