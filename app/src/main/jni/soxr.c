#include <jni.h>
#include <soxr.h>
#include "examples-common.h"
#include <android/log.h>
#define LOG_TAG  "C_TAG"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
JNIEXPORT void JNICALL
Java_soxr_dyc_com_soxr_Testutil_excute(JNIEnv *env, jobject instance) {
    const float in[] = {  /* Input: 12 cycles of a sine wave with freq. = irate/4 */
            0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1,
            0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1, 0,1,0,-1};
    double irate =  1;      /* Default to interpolation */
    double orate =  2;             /* by a factor of 2. */

    size_t olen = (size_t)(AL(in) * orate / irate + .5);   /* Assay output len. */
    float * out = malloc(sizeof(*out) * olen);       /* Allocate output buffer. */
    size_t odone;

    soxr_error_t error = soxr_oneshot(irate, orate, 1, /* Rates and # of chans. */
                                      in, AL(in), NULL,                              /* Input. */
                                      out, olen, &odone,                             /* Output. */
                                      NULL, NULL, NULL);                             /* Default configuration.*/

    unsigned i = 0;                            /* Print out the resampled data, */
    while (i++ < odone){
        printf("%5.2f%c", out[i-1], " \n"[!(i&7) || i == odone]);
        LOGD("5.2f%f", out[i-1]);
       // LOGD("\n%c"[!(i&7) || i == odone]);
    }
    //LOGD("%-26c %c\n", 1, soxr_strerror(error));
  //  printf("%-26s %s\n", 1, soxr_strerror(error)); /* and reported result. */

                                       /* Library version check: */
       // printf("runtime=%s API="SOXR_THIS_VERSION_STR"\n", soxr_version());
    LOGD("runtime=%s API="SOXR_THIS_VERSION_STR"\n", soxr_version());
    free(out);                                                      /* Tidy up. */

}

JNIEXPORT jint JNICALL
Java_soxr_dyc_com_soxr_Testutil_resample(JNIEnv *env, jobject instance, jbyteArray b_,
                                         jbyteArray ob_, jint src_size, jint dst_sample_value,
                                         jint dest_channel) {
//    jbyte *b = (*env)->GetByteArrayElements(env, b_, NULL);
//    jbyte *ob = (*env)->GetByteArrayElements(env, ob_, NULL);

    jbyte * b = malloc(96000/8*2*16);
    jbyte *ob = malloc(44100*16*2+.5);
    LOGD("获取到数据");
    soxr_error_t error;
    /* Create a stream resampler: */
    LOGD("创建实例前");
    soxr_t soxr = soxr_create(
            src_size, dst_sample_value, dest_channel,             /* Input rate, output rate, # of channels. */
            &error,                         /* To report any error during creation. */
            NULL, NULL, NULL);
    LOGD("创建实例");
    size_t odone;/* Use configuration defaults.*/
    if (!error) {                         /* If all is well, run the resampler: */
        LOGD("准备处理实例");
        error = soxr_process(soxr, b, src_size, NULL, ob, sizeof(ob), &odone);
    }
    LOGD("释放资源");
    (*env)->ReleaseByteArrayElements(env, b_, b, 0);
    (*env)->ReleaseByteArrayElements(env, ob_, ob, 0);
    soxr_delete(soxr);
    return odone;
}

JNIEXPORT void JNICALL
Java_soxr_dyc_com_soxr_Testutil_test(JNIEnv *env, jobject instance) {
    double const irate = 96000.;
    double const orate =  44100.;

    /* Allocate resampling input and output buffers in proportion to the input
     * and output rates: */
#define buf_total_len 15000  /* In samples. */
    size_t const olen = (size_t)(orate * buf_total_len / (irate + orate) + .5);
    size_t const ilen = buf_total_len - olen;
    size_t const osize = sizeof(float), isize = osize;
    jbyte * obuf = malloc(osize * olen);
    jbyte * ibuf = malloc(isize * ilen);

    size_t odone, written, need_input = 1;
    soxr_error_t error;
    LOGD("创建实例前aaaaa");
    /* Create a stream resampler: */
    soxr_t soxr = soxr_create(
            irate, orate, 1,             /* Input rate, output rate, # of channels. */
            &error,                         /* To report any error during creation. */
            NULL, NULL, NULL);                        /* Use configuration defaults.*/

    if (!error) {                         /* If all is well, run the resampler: */
//        USE_STD_STDIO;
        /* Resample in blocks: */
//        do {
//            size_t ilen1 = 0;
//
//            if (need_input) {
//                /* Read one block into the buffer, ready to be resampled: */
////                ilen1 = fread(ibuf, isize, ilen, stdin);
//
//                if (!ilen1) {     /* If the is no (more) input data available, */
//                    free(ibuf);     /* set ibuf to NULL, to indicate end-of-input */
//                    ibuf = NULL;    /* to the resampler. */
//                }
//            }
            /* Copy data from the input buffer into the resampler, and resample
             * to produce as much output as is possible to the given output buffer: */
        LOGD("开始处理");
        error = soxr_process(soxr, ibuf, sizeof(ibuf) , NULL, obuf, olen, &odone);
        LOGD("释放资源前%i",odone);
//            written = fwrite(obuf, osize, odone, stdout); /* Consume output.*/
            /* If the actual amount of data output is less than that requested, and
             * we have not already reached the end of the input data, then supply some
             * more input next time round the loop: */
//            need_input = odone < olen && ibuf;

//        } while (!error && (need_input || written));
    }
    LOGD("释放资源前");
    /* Tidy up: */
    soxr_delete(soxr);
    free(obuf), free(ibuf);
    /* Diagnostics: */
    LOGD("释放资源");


}