package soxr.dyc.com.soxr;

public class Testutil {

    public native void excute();
    public native int resample(byte[] b,byte[]ob,int src_size,int dst_sample_value,int dest_channel);
    public native void test();


    static {
        System.loadLibrary("soxr-test");
    }
}
