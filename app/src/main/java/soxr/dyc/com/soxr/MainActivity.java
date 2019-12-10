package soxr.dyc.com.soxr;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new Testutil().excute();
//        new Testutil().test();
        byte[] input=new byte[96000*16*2/8];
        byte[] output=new byte[44100*16*2/8];
       int lenth= new Testutil().resample(input,output,input.length,44100,2);
        System.out.println("lenthlenthlenthlenth"+lenth);
        for(int i=0;i<output.length;i++){
            System.out.println("lenthlenthlenthlenth"+output[i]);
        }
    }

}
