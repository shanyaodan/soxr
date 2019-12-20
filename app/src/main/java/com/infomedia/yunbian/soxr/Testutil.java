package com.infomedia.yunbian.soxr;

public class Testutil {

    public native void excute();
    public native int resample(byte[] b,byte[]ob,int src_size,int dest_size,int src_sample_size,int dst_sample_value,int dest_channel);
    public native int resample3(float[] b,float[]ob,int src_size,int dest_size,int src_sample_size,int dst_sample_value,int dest_channel);
    public native int resample2(byte[] b,byte[]ob,int src_sample_size,int dst_sample_value,int dest_channel);
    public native void test();


    static {
        System.loadLibrary("soxr-test");
    }
}
