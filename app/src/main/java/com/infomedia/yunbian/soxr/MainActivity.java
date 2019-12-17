package com.infomedia.yunbian.soxr;

import android.app.Activity;
import android.os.Bundle;

import com.infomedia.soxr.R;


public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        new Testutil().excute();
//        new Testutil().test();
        byte[] input=new byte[]{  /* Input: 12 cycles of a sine wave with freq. = irate/4 */
                0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1,
                0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1};
        byte[] output=new byte[24*2*2];
       int lenth= new Testutil().resample2(input,output,1,2,1);
        System.out.println("lenthlenthlenthlenth"+lenth);
//        System.out.println("output.lengthoutput.length"+output.length);
        for(int i=0;i<19;i++){
            System.out.println("lenthlenthlenthlenth"+output[i]);
        }
    }

}
