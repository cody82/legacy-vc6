#ifndef DECODER_H
#define DECODER_H

#include "common.h"
#include "args.h"
#include "player.h"
                
#define VERSION_O

extern int equalizer_cnt;
extern real equalizer[2][32];
extern real equalizer_sum[2][32];
extern bool Decoder_Initialized;

extern unsigned char *pcm_sample;
extern int pcm_point;

extern __inline void AudioFlush(); 
extern bool Done_MPEGDecoder();
extern bool Init_MPEGDecoder(int down_samp);
extern void make_decode_tables(long scaleval);    
extern void make_conv16to8_table();    
   
extern void init_layer3(int);

extern int do_layer3();
extern int do_layer2();
extern int do_layer1();
extern float GetSubbandValues(int Band);

extern void InitMoreTables(void);
extern void III_get_side_info_1(struct III_sideinfo *si,int stereo,int ms_stereo,long sfreq,int single);
extern void III_get_side_info_2(struct III_sideinfo *si,int stereo,int ms_stereo,long sfreq,int single);
extern int  III_get_scale_factors_1(int *scf,struct gr_info_s *gr_info);
extern int  III_get_scale_factors_2(int *scf,struct gr_info_s *gr_info,int i_stereo);
extern int  III_dequantize_sample(real xr[SBLIMIT][SSLIMIT],int *scf,struct gr_info_s *gr_info,int sfreq,int part2bits);
extern int  III_dequantize_sample_ms(real xr[2][SBLIMIT][SSLIMIT],int *scf,struct gr_info_s *gr_info,int sfreq,int part2bits);
extern void III_i_stereo(real xr_buf[2][SBLIMIT][SSLIMIT],int *scalefac,struct gr_info_s *gr_info,int sfreq,int ms_stereo,int lsf);
extern void III_antialias(real xr[SBLIMIT][SSLIMIT],struct gr_info_s *gr_info);
extern void III_hybrid(real fsIn[SBLIMIT][SSLIMIT],real tsOut[SSLIMIT][SBLIMIT],int ch,struct gr_info_s *gr_info);
extern void dct64(real *,real *,real *);
extern void dct36(real *inbuf,real *o1,real *o2,real *wintab,real *tsbuf);
extern void dct12(real *in,real *rawout1,real *rawout2,register real *wi,register real *ts);
extern void I_step_one(unsigned int balloc[], unsigned int scale_index[2][SBLIMIT]);
extern void I_step_two(real fraction[2][SBLIMIT],unsigned int balloc[2*SBLIMIT],unsigned int scale_index[2][SBLIMIT]);
extern void II_step_one(unsigned int *bit_alloc,int *scale);
extern void II_step_two(unsigned int *bit_alloc,real fraction[2][4][SBLIMIT],int *scale,int x1);

extern int synth_1to1(real *, int, unsigned char *,int *);
extern int synth_1to1_8bit(real *,int,unsigned char *,int *);
extern int synth_1to1_mono(real *,unsigned char *,int *);
extern int synth_1to1_mono2stereo(real *,unsigned char *,int *);
extern int synth_1to1_8bit_mono(real *,unsigned char *,int *);
extern int synth_1to1_8bit_mono2stereo(real *,unsigned char *,int *);

extern int synth_2to1_mono(real *,unsigned char *,int *);
extern int synth_2to1_mono2stereo(real *,unsigned char *,int *);
extern int synth_2to1_8bit_mono(real *,unsigned char *,int *);
extern int synth_2to1_8bit_mono2stereo(real *,unsigned char *,int *);
extern int synth_2to1(real *,int,unsigned char *,int *);
extern int synth_2to1_8bit(real *,int,unsigned char *,int *);

extern int synth_4to1_mono(real *,unsigned char *, int *);
extern int synth_4to1_mono2stereo(real *,unsigned char *, int *);
extern int synth_4to1_8bit_mono(real *,unsigned char *, int *);
extern int synth_4to1_8bit_mono2stereo(real *,unsigned char *, int *);
extern int synth_4to1(real *,int,unsigned char *,int *);
extern int synth_4to1_8bit(real *,int,unsigned char *,int *);

extern void synth_ntom_set_step(long, long);

extern int synth_ntom (real *,int,unsigned char *,int *);
extern int synth_ntom_8bit (real *,int,unsigned char *,int *);
extern int synth_ntom_mono (real *,unsigned char *,int *);
extern int synth_ntom_mono2stereo (real *,unsigned char *,int *);
extern int synth_ntom_8bit_mono (real *,unsigned char *,int *);
extern int synth_ntom_8bit_mono2stereo (real *,unsigned char *,int *);


static long intwinbase[] = {
     0,    -1,    -1,    -1,    -1,    -1,    -1,    -2,    -2,    -2,
    -2,    -3,    -3,    -4,    -4,    -5,    -5,    -6,    -7,    -7,
    -8,    -9,   -10,   -11,   -13,   -14,   -16,   -17,   -19,   -21,
   -24,   -26,   -29,   -31,   -35,   -38,   -41,   -45,   -49,   -53,
   -58,   -63,   -68,   -73,   -79,   -85,   -91,   -97,  -104,  -111,
  -117,  -125,  -132,  -139,  -147,  -154,  -161,  -169,  -176,  -183,
  -190,  -196,  -202,  -208,  -213,  -218,  -222,  -225,  -227,  -228,
  -228,  -227,  -224,  -221,  -215,  -208,  -200,  -189,  -177,  -163,
  -146,  -127,  -106,   -83,   -57,   -29,     2,    36,    72,   111,
   153,   197,   244,   294,   347,   401,   459,   519,   581,   645,
   711,   779,   848,   919,   991,  1064,  1137,  1210,  1283,  1356,
  1428,  1498,  1567,  1634,  1698,  1759,  1817,  1870,  1919,  1962,
  2001,  2032,  2057,  2075,  2085,  2087,  2080,  2063,  2037,  2000,
  1952,  1893,  1822,  1739,  1644,  1535,  1414,  1280,  1131,   970,
   794,   605,   402,   185,   -45,  -288,  -545,  -814, -1095, -1388,
 -1692, -2006, -2330, -2663, -3004, -3351, -3705, -4063, -4425, -4788,
 -5153, -5517, -5879, -6237, -6589, -6935, -7271, -7597, -7910, -8209,
 -8491, -8755, -8998, -9219, -9416, -9585, -9727, -9838, -9916, -9959,
 -9966, -9935, -9863, -9750, -9592, -9389, -9139, -8840, -8492, -8092,
 -7640, -7134, -6574, -5959, -5288, -4561, -3776, -2935, -2037, -1082,
   -70,   998,  2122,  3300,  4533,  5818,  7154,  8540,  9975, 11455,
 12980, 14548, 16155, 17799, 19478, 21189, 22929, 24694, 26482, 28289,
 30112, 31947, 33791, 35640, 37489, 39336, 41176, 43006, 44821, 46617,
 48390, 50137, 51853, 53534, 55178, 56778, 58333, 59838, 61289, 62684,
 64019, 65290, 66494, 67629, 68692, 69679, 70590, 71420, 72169, 72835,
 73415, 73908, 74313, 74630, 74856, 74992, 75038 };

#ifdef VERSION_O

static struct bandInfoStruct bandInfo[9] = { 
     { {0,4,8,12,16,20,24,30,36,44,52,62,74, 90,110,134,162,196,238,288,342,418,576},
       {4,4,4,4,4,4,6,6,8, 8,10,12,16,20,24,28,34,42,50,54, 76,158},
       {0,4*3,8*3,12*3,16*3,22*3,30*3,40*3,52*3,66*3, 84*3,106*3,136*3,192*3},
       {4,4,4,4,6,8,10,12,14,18,22,30,56} } ,
     { {0,4,8,12,16,20,24,30,36,42,50,60,72, 88,106,128,156,190,230,276,330,384,576},
       {4,4,4,4,4,4,6,6,6, 8,10,12,16,18,22,28,34,40,46,54, 54,192},
       {0,4*3,8*3,12*3,16*3,22*3,28*3,38*3,50*3,64*3, 80*3,100*3,126*3,192*3},
       {4,4,4,4,6,6,10,12,14,16,20,26,66} } ,
     { {0,4,8,12,16,20,24,30,36,44,54,66,82,102,126,156,194,240,296,364,448,550,576} ,
       {4,4,4,4,4,4,6,6,8,10,12,16,20,24,30,38,46,56,68,84,102, 26} ,
       {0,4*3,8*3,12*3,16*3,22*3,30*3,42*3,58*3,78*3,104*3,138*3,180*3,192*3} ,
       {4,4,4,4,6,8,12,16,20,26,34,42,12} }  ,
     { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576},
       {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54 } ,
       {0,4*3,8*3,12*3,18*3,24*3,32*3,42*3,56*3,74*3,100*3,132*3,174*3,192*3} ,
       {4,4,4,6,6,8,10,14,18,26,32,42,18 } } ,
     { {0,6,12,18,24,30,36,44,54,66,80,96,114,136,162,194,232,278,330,394,464,540,576},
       {6,6,6,6,6,6,8,10,12,14,16,18,22,26,32,38,46,52,64,70,76,36 } ,
       {0,4*3,8*3,12*3,18*3,26*3,36*3,48*3,62*3,80*3,104*3,136*3,180*3,192*3} ,
       {4,4,4,6,8,10,12,14,18,24,32,44,12 } } ,
     { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576},
       {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54 },
       {0,4*3,8*3,12*3,18*3,26*3,36*3,48*3,62*3,80*3,104*3,134*3,174*3,192*3},
       {4,4,4,6,8,10,12,14,18,24,30,40,18 } } ,
     { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576} ,
       {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54},
       {0,12,24,36,54,78,108,144,186,240,312,402,522,576},
       {4,4,4,6,8,10,12,14,18,24,30,40,18} },
     { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576} ,
       {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54},
       {0,12,24,36,54,78,108,144,186,240,312,402,522,576},
       {4,4,4,6,8,10,12,14,18,24,30,40,18} },
     { {0,12,24,36,48,60,72,88,108,132,160,192,232,280,336,400,476,566,568,570,572,574,576},
       {12,12,12,12,12,12,16,20,24,28,32,40,48,56,64,76,90,2,2,2,2,2},
       {0, 24, 48, 72,108,156,216,288,372,480,486,492,498,576},
       {8,8,8,12,16,20,24,28,36,2,2,2,26} } ,
    };

#endif // VERSION_O

#endif