#include <signal.h>
#include <math.h>
#include "decoder.h"
#include "common.h"
#include "player.h"
#include "stream.h"
#include <winbase.h>    
#include "huffman.h"
#include "audio.h"

#define AUSHIFT (3)

int mapbuf0[9][152],
    mapbuf1[9][156],
    mapbuf2[9][44],
    *map[9][3],
    *mapend[9][3];

unsigned int 
    n_slen2[512],
    i_slen2[256];

real tan1_1[16],tan2_1[16],tan1_2[16],tan2_2[16];
real pow1_1[2][16],pow2_1[2][16],pow1_2[2][16],pow2_2[2][16];

static real gainpow2[256+118+4];
static real ispow[8207];
static real aa_ca[8], aa_cs[8];   
static real COS1[12][6];         
static real win[4][36];          
static real win1[4][36];         
static real COS9[9];             
static real COS6_1,COS6_2;       
static real tfcos36[9];          
static real tfcos12[3];          
int longLimit[9][23];
int shortLimit[9][14];
static int grp_3tab[32 * 3] = { 0, };
static int grp_5tab[128 * 3] = { 0, };
static int grp_9tab[1024 * 3] = { 0, };

#define NTOM_MUL (32768)
static unsigned long ntom_val[2] = { NTOM_MUL>>1,NTOM_MUL>>1 };
static unsigned long ntom_step = NTOM_MUL;

real muls[27][64];

real decwin[512+32];
static real cos64[16],cos32[8],cos16[4],cos8[2],cos4[1];
real *pnts[] = { cos64,cos32,cos16,cos8,cos4 };

static unsigned char conv16to8_buf[4096];
unsigned char *conv16to8;

static const int pretab1[22] = {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3,3,2,0};
static const int pretab2[22] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

#ifdef NEW_DCT9
static real cos9[3],cos18[3];
#endif

unsigned char *pcm_sample = NULL;
static real SubbandAnalyser[SSLIMIT];

real equalizer[2][32];
real equalizer_sum[2][32];
int equalizer_cnt;
int pcm_point;
bool Decoder_Initialized = false;

#define WRITE_SAMPLE(samples,sum,clip) \
    if( (sum) > 32767.0) { *(samples) = 0x7fff; (clip)++; } \
    else if( (sum) < -32768.0) { *(samples) = -0x8000; (clip)++; } \
else { *(samples) = sum; }

void do_equalizer( real *bandPtr, int channel){
    int i;
    if(Args->UseEqualizer) {
        for(i=0; i<32; i++) bandPtr[i]*=equalizer[channel][i];
    }
}

__inline void AudioFlush() {
    if(pcm_point) 
    {
        PlaySamples(pcm_sample, pcm_point);
        pcm_point=0;
    }
}

void dct36(real *inbuf,real *o1,real *o2,real *wintab,real *tsbuf)
{
#ifdef NEW_DCT9
    real tmp[18];
#endif
    
    {
        register real *in = inbuf;
        
        in[17]+=in[16]; in[16]+=in[15]; in[15]+=in[14];
        in[14]+=in[13]; in[13]+=in[12]; in[12]+=in[11];
        in[11]+=in[10]; in[10]+=in[9];  in[9] +=in[8];
        in[8] +=in[7];  in[7] +=in[6];  in[6] +=in[5];
        in[5] +=in[4];  in[4] +=in[3];  in[3] +=in[2];
        in[2] +=in[1];  in[1] +=in[0];
        
        in[17]+=in[15]; in[15]+=in[13]; in[13]+=in[11]; in[11]+=in[9];
        in[9] +=in[7];  in[7] +=in[5];  in[5] +=in[3];  in[3] +=in[1];
        
        
#ifdef NEW_DCT9
        {
            real t0, t1, t2, t3, t4, t5, t6, t7;
            
            t1 = COS6_2 * in[12];
            t2 = COS6_2 * (in[8] + in[16] - in[4]);
            
            t3 = in[0] + t1;
            t4 = in[0] - t1 - t1;
            t5 = t4 - t2;
            
            t0 = cos9[0] * (in[4] + in[8]);
            t1 = cos9[1] * (in[8] - in[16]);
            
            tmp[4] = t4 + t2 + t2;
            t2 = cos9[2] * (in[4] + in[16]);
            
            t6 = t3 - t0 - t2;
            t0 += t3 + t1;
            t3 += t2 - t1;
            
            t2 = cos18[0] * (in[2]  + in[10]);
            t4 = cos18[1] * (in[10] - in[14]);
            t7 = COS6_1 * in[6];
            
            t1 = t2 + t4 + t7;
            tmp[0] = t0 + t1;
            tmp[8] = t0 - t1;
            t1 = cos18[2] * (in[2] + in[14]);
            t2 += t1 - t7;
            
            tmp[3] = t3 + t2;
            t0 = COS6_1 * (in[10] + in[14] - in[2]);
            tmp[5] = t3 - t2;
            
            t4 -= t1 + t7;
            
            tmp[1] = t5 - t0;
            tmp[7] = t5 + t0;
            tmp[2] = t6 + t4;
            tmp[6] = t6 - t4;
        }
        
        {
            real t0, t1, t2, t3, t4, t5, t6, t7;
            
            t1 = COS6_2 * in[13];
            t2 = COS6_2 * (in[9] + in[17] - in[5]);
            
            t3 = in[1] + t1;
            t4 = in[1] - t1 - t1;
            t5 = t4 - t2;
            
            t0 = cos9[0] * (in[5] + in[9]);
            t1 = cos9[1] * (in[9] - in[17]);
            
            tmp[13] = (t4 + t2 + t2) * tfcos36[17-13];
            t2 = cos9[2] * (in[5] + in[17]);
            
            t6 = t3 - t0 - t2;
            t0 += t3 + t1;
            t3 += t2 - t1;
            
            t2 = cos18[0] * (in[3]  + in[11]);
            t4 = cos18[1] * (in[11] - in[15]);
            t7 = COS6_1 * in[7];
            
            t1 = t2 + t4 + t7;
            tmp[17] = (t0 + t1) * tfcos36[17-17];
            tmp[9]  = (t0 - t1) * tfcos36[17-9];
            t1 = cos18[2] * (in[3] + in[15]);
            t2 += t1 - t7;
            
            tmp[14] = (t3 + t2) * tfcos36[17-14];
            t0 = COS6_1 * (in[11] + in[15] - in[3]);
            tmp[12] = (t3 - t2) * tfcos36[17-12];
            
            t4 -= t1 + t7;
            
            tmp[16] = (t5 - t0) * tfcos36[17-16];
            tmp[10] = (t5 + t0) * tfcos36[17-10];
            tmp[15] = (t6 + t4) * tfcos36[17-15];
            tmp[11] = (t6 - t4) * tfcos36[17-11];
        }
        
#define MACRO(v) { \
    real tmpval; \
    real sum0 = tmp[(v)]; \
    real sum1 = tmp[17-(v)]; \
    out2[9+(v)] = (tmpval = sum0 + sum1) * w[27+(v)]; \
    out2[8-(v)] = tmpval * w[26-(v)]; \
    sum0 -= sum1; \
    ts[SBLIMIT*(8-(v))] = out1[8-(v)] + sum0 * w[8-(v)]; \
        ts[SBLIMIT*(9+(v))] = out1[9+(v)] + sum0 * w[9+(v)]; }
        
        {
            register real *out2 = o2;
            register real *w = wintab;
            register real *out1 = o1;
            register real *ts = tsbuf;
            
            MACRO(0);
            MACRO(1);
            MACRO(2);
            MACRO(3);
            MACRO(4);
            MACRO(5);
            MACRO(6);
            MACRO(7);
            MACRO(8);
        }
        
#else
        
        {
            
#define MACRO0(v) { \
    real tmp; \
    out2[9+(v)] = (tmp = sum0 + sum1) * w[27+(v)]; \
    out2[8-(v)] = tmp * w[26-(v)];  } \
    sum0 -= sum1; \
    ts[SBLIMIT*(8-(v))] = out1[8-(v)] + sum0 * w[8-(v)]; \
            ts[SBLIMIT*(9+(v))] = out1[9+(v)] + sum0 * w[9+(v)]; 
#define MACRO1(v) { \
    real sum0,sum1; \
    sum0 = tmp1a + tmp2a; \
    sum1 = (tmp1b + tmp2b) * tfcos36[(v)]; \
            MACRO0(v); }
#define MACRO2(v) { \
    real sum0,sum1; \
    sum0 = tmp2a - tmp1a; \
    sum1 = (tmp2b - tmp1b) * tfcos36[(v)]; \
            MACRO0(v); }
            
            register const real *c = COS9;
            register real *out2 = o2;
            register real *w = wintab;
            register real *out1 = o1;
            register real *ts = tsbuf;
            
            real ta33,ta66,tb33,tb66;
            
            ta33 = in[2*3+0] * c[3];
            ta66 = in[2*6+0] * c[6];
            tb33 = in[2*3+1] * c[3];
            tb66 = in[2*6+1] * c[6];
            
            { 
                real tmp1a,tmp2a,tmp1b,tmp2b;
                tmp1a =             in[2*1+0] * c[1] + ta33 + in[2*5+0] * c[5] + in[2*7+0] * c[7];
                tmp1b =             in[2*1+1] * c[1] + tb33 + in[2*5+1] * c[5] + in[2*7+1] * c[7];
                tmp2a = in[2*0+0] + in[2*2+0] * c[2] + in[2*4+0] * c[4] + ta66 + in[2*8+0] * c[8];
                tmp2b = in[2*0+1] + in[2*2+1] * c[2] + in[2*4+1] * c[4] + tb66 + in[2*8+1] * c[8];
                
                MACRO1(0);
                MACRO2(8);
            }
            
            {
                real tmp1a,tmp2a,tmp1b,tmp2b;
                tmp1a = ( in[2*1+0] - in[2*5+0] - in[2*7+0] ) * c[3];
                tmp1b = ( in[2*1+1] - in[2*5+1] - in[2*7+1] ) * c[3];
                tmp2a = ( in[2*2+0] - in[2*4+0] - in[2*8+0] ) * c[6] - in[2*6+0] + in[2*0+0];
                tmp2b = ( in[2*2+1] - in[2*4+1] - in[2*8+1] ) * c[6] - in[2*6+1] + in[2*0+1];
                
                MACRO1(1);
                MACRO2(7);
            }
            
            {
                real tmp1a,tmp2a,tmp1b,tmp2b;
                tmp1a =             in[2*1+0] * c[5] - ta33 - in[2*5+0] * c[7] + in[2*7+0] * c[1];
                tmp1b =             in[2*1+1] * c[5] - tb33 - in[2*5+1] * c[7] + in[2*7+1] * c[1];
                tmp2a = in[2*0+0] - in[2*2+0] * c[8] - in[2*4+0] * c[2] + ta66 + in[2*8+0] * c[4];
                tmp2b = in[2*0+1] - in[2*2+1] * c[8] - in[2*4+1] * c[2] + tb66 + in[2*8+1] * c[4];
                
                MACRO1(2);
                MACRO2(6);
            }
            
            {
                real tmp1a,tmp2a,tmp1b,tmp2b;
                tmp1a =             in[2*1+0] * c[7] - ta33 + in[2*5+0] * c[1] - in[2*7+0] * c[5];
                tmp1b =             in[2*1+1] * c[7] - tb33 + in[2*5+1] * c[1] - in[2*7+1] * c[5];
                tmp2a = in[2*0+0] - in[2*2+0] * c[4] + in[2*4+0] * c[8] + ta66 - in[2*8+0] * c[2];
                tmp2b = in[2*0+1] - in[2*2+1] * c[4] + in[2*4+1] * c[8] + tb66 - in[2*8+1] * c[2];
                
                MACRO1(3);
                MACRO2(5);
            }
            
            {
                real sum0,sum1;
                sum0 =  in[2*0+0] - in[2*2+0] + in[2*4+0] - in[2*6+0] + in[2*8+0];
                sum1 = (in[2*0+1] - in[2*2+1] + in[2*4+1] - in[2*6+1] + in[2*8+1] ) * tfcos36[4];
                MACRO0(4);
            }
        }
#endif
        
  }
}

void dct12(real *in,real *rawout1,real *rawout2,register real *wi,register real *ts)
{
#define DCT12_PART1 \
    in5 = in[5*3];  \
    in5 += (in4 = in[4*3]); \
    in4 += (in3 = in[3*3]); \
    in3 += (in2 = in[2*3]); \
    in2 += (in1 = in[1*3]); \
    in1 += (in0 = in[0*3]); \
    \
    in5 += in3; in3 += in1; \
    \
    in2 *= COS6_1; \
    in3 *= COS6_1; \
    
#define DCT12_PART2 \
    in0 += in4 * COS6_2; \
    \
    in4 = in0 + in2;     \
    in0 -= in2;          \
    \
    in1 += in5 * COS6_2; \
    \
    in5 = (in1 + in3) * tfcos12[0]; \
    in1 = (in1 - in3) * tfcos12[2]; \
    \
    in3 = in4 + in5;    \
    in4 -= in5;         \
    \
    in2 = in0 + in1;    \
    in0 -= in1;
    
    
    {
        real in0,in1,in2,in3,in4,in5;
        register real *out1 = rawout1;
        ts[SBLIMIT*0] = out1[0]; ts[SBLIMIT*1] = out1[1]; ts[SBLIMIT*2] = out1[2];
        ts[SBLIMIT*3] = out1[3]; ts[SBLIMIT*4] = out1[4]; ts[SBLIMIT*5] = out1[5];
        
        DCT12_PART1
            
        {
            real tmp0,tmp1;
            tmp1 = (in0 - in4);
            {
                real tmp2 = (in1 - in5) * tfcos12[1];
                tmp0 = tmp1 + tmp2;
                tmp1 -= tmp2;
            }
            ts[(17-1)*SBLIMIT] = out1[17-1] + tmp0 * wi[11-1];
            ts[(12+1)*SBLIMIT] = out1[12+1] + tmp0 * wi[6+1];
            ts[(6 +1)*SBLIMIT] = out1[6 +1] + tmp1 * wi[1];
            ts[(11-1)*SBLIMIT] = out1[11-1] + tmp1 * wi[5-1];
        }
        
        DCT12_PART2
            
            ts[(17-0)*SBLIMIT] = out1[17-0] + in2 * wi[11-0];
        ts[(12+0)*SBLIMIT] = out1[12+0] + in2 * wi[6+0];
        ts[(12+2)*SBLIMIT] = out1[12+2] + in3 * wi[6+2];
        ts[(17-2)*SBLIMIT] = out1[17-2] + in3 * wi[11-2];
        
        ts[(6+0)*SBLIMIT]  = out1[6+0] + in0 * wi[0];
        ts[(11-0)*SBLIMIT] = out1[11-0] + in0 * wi[5-0];
        ts[(6+2)*SBLIMIT]  = out1[6+2] + in4 * wi[2];
        ts[(11-2)*SBLIMIT] = out1[11-2] + in4 * wi[5-2];
    }
    
    in++;
    
    {
        real in0,in1,in2,in3,in4,in5;
        register real *out2 = rawout2;
        
        DCT12_PART1
            
        {
            real tmp0;
            real tmp1 = (in0 - in4);
            {
                real tmp2 = (in1 - in5) * tfcos12[1];
                tmp0 = tmp1 + tmp2;
                tmp1 -= tmp2;
            }
            out2[5-1] = tmp0 * wi[11-1];
            out2[0+1] = tmp0 * wi[6+1];
            ts[(12+1)*SBLIMIT] += tmp1 * wi[1];
            ts[(17-1)*SBLIMIT] += tmp1 * wi[5-1];
        }
        
        DCT12_PART2
            
            out2[5-0] = in2 * wi[11-0];
        out2[0+0] = in2 * wi[6+0];
        out2[0+2] = in3 * wi[6+2];
        out2[5-2] = in3 * wi[11-2];
        
        ts[(12+0)*SBLIMIT] += in0 * wi[0];
        ts[(17-0)*SBLIMIT] += in0 * wi[5-0];
        ts[(12+2)*SBLIMIT] += in4 * wi[2];
        ts[(17-2)*SBLIMIT] += in4 * wi[5-2];
    }
    
    in++; 
    
    {
        real in0,in1,in2,in3,in4,in5;
        register real *out2 = rawout2;
        out2[12]=out2[13]=out2[14]=out2[15]=out2[16]=out2[17]=0.0;
        
        DCT12_PART1
            
        {
            real tmp0;
            real tmp1 = (in0 - in4);
            {
                real tmp2 = (in1 - in5) * tfcos12[1];
                tmp0 = tmp1 + tmp2;
                tmp1 -= tmp2;
            }
            out2[11-1] = tmp0 * wi[11-1];
            out2[6 +1] = tmp0 * wi[6+1];
            out2[0+1] += tmp1 * wi[1];
            out2[5-1] += tmp1 * wi[5-1];
        }
        
        DCT12_PART2
            
            out2[11-0] = in2 * wi[11-0];
        out2[6 +0] = in2 * wi[6+0];
        out2[6 +2] = in3 * wi[6+2];
        out2[11-2] = in3 * wi[11-2];
        
        out2[0+0] += in0 * wi[0];
        out2[5-0] += in0 * wi[5-0];
        out2[0+2] += in4 * wi[2];
        out2[5-2] += in4 * wi[5-2];
    }
}

void I_step_one(unsigned int balloc[], unsigned int scale_index[2][SBLIMIT])
{
    unsigned int *ba=balloc;
    unsigned int *sca = (unsigned int *) scale_index;
    
    if(fr.stereo) {
        int i;
        int jsbound = fr.jsbound;
        for (i=0;i<jsbound;i++) { 
            *ba++ = GetBits(4);
            *ba++ = GetBits(4);
        }
        for (i=jsbound;i<SBLIMIT;i++)
            *ba++ = GetBits(4);
        
        ba = balloc;
        
        for (i=0;i<jsbound;i++) {
            if ((*ba++))
                *sca++ = GetBits(6);
            if ((*ba++))
                *sca++ = GetBits(6);
        }
        for (i=jsbound;i<SBLIMIT;i++)
            if ((*ba++)) {
                *sca++ =  GetBits(6);
                *sca++ =  GetBits(6);
            }
    }
    else {
        int i;
        for (i=0;i<SBLIMIT;i++)
            *ba++ = GetBits(4);
        ba = balloc;
        for (i=0;i<SBLIMIT;i++)
            if ((*ba++))
                *sca++ = GetBits(6);
    }
}

void I_step_two(real fraction[2][SBLIMIT],unsigned int balloc[2*SBLIMIT],unsigned int scale_index[2][SBLIMIT])
{
    int i,n;
    int smpb[2*SBLIMIT]; /* values: 0-65535 */
    int *sample;
    register unsigned int *ba;
    register unsigned int *sca = (unsigned int *) scale_index;
    
    if(fr.stereo) {
        int jsbound = fr.jsbound;
        register real *f0 = fraction[0];
        register real *f1 = fraction[1];
        ba = balloc;
        for (sample=smpb,i=0;i<jsbound;i++)  {
            if ((n = *ba++))
                *sample++ = GetBits(n+1);
            if ((n = *ba++))
                *sample++ = GetBits(n+1);
        }
        for (i=jsbound;i<SBLIMIT;i++) 
            if ((n = *ba++))
                *sample++ = GetBits(n+1);
            
            ba = balloc;
            for (sample=smpb,i=0;i<jsbound;i++) {
                if((n=*ba++))
                    *f0++ = (real) ( ((-1)<<n) + (*sample++) + 1) * muls[n+1][*sca++];
                else
                    *f0++ = 0.0;
                if((n=*ba++))
                    *f1++ = (real) ( ((-1)<<n) + (*sample++) + 1) * muls[n+1][*sca++];
                else
                    *f1++ = 0.0;
            }
            for (i=jsbound;i<SBLIMIT;i++) {
                if ((n=*ba++)) {
                    real samp = ( ((-1)<<n) + (*sample++) + 1);
                    *f0++ = samp * muls[n+1][*sca++];
                    *f1++ = samp * muls[n+1][*sca++];
                }
                else
                    *f0++ = *f1++ = 0.0;
            }
            for(i=SBLIMIT>>fr.down_sample;i<32;i++)
                fraction[0][i] = fraction[1][i] = 0.0;
    }
    else {
        register real *f0 = fraction[0];
        ba = balloc;
        for (sample=smpb,i=0;i<SBLIMIT;i++)
            if ((n = *ba++))
                *sample++ = GetBits(n+1);
            ba = balloc;
            for (sample=smpb,i=0;i<SBLIMIT;i++) {
                if((n=*ba++))
                    *f0++ = (real) ( ((-1)<<n) + (*sample++) + 1) * muls[n+1][*sca++];
                else
                    *f0++ = 0.0;
            }
            for(i=SBLIMIT>>fr.down_sample;i<32;i++)
                fraction[0][i] = 0.0;
    }
}

void II_step_one(unsigned int *bit_alloc,int *scale){
    int stereo = fr.stereo-1;
    int sblimit = fr.II_sblimit;
    int jsbound = fr.jsbound;
    int sblimit2 = fr.II_sblimit<<stereo;
    const struct al_table *alloc1 = fr.alloc;
    int i;
    static unsigned int scfsi_buf[64];
    unsigned int *scfsi,*bita;
    int sc,step;
    
    bita = bit_alloc;
    if(stereo) {
        for (i=jsbound;i;i--,alloc1+=(1<<step)) {
            *bita++ = (char) GetBits(step=alloc1->bits);
            *bita++ = (char) GetBits(step);
        }
        for (i=sblimit-jsbound;i;i--,alloc1+=(1<<step)) {
            bita[0] = (char) GetBits(step=alloc1->bits);
            bita[1] = bita[0];
            bita+=2;
        }
        bita = bit_alloc;
        scfsi=scfsi_buf;
        for (i=sblimit2;i;i--)
            if (*bita++)
                *scfsi++ = (char) GetBitsFast(2);
    }
    else /* mono */ {
        for (i=sblimit;i;i--,alloc1+=(1<<step))
            *bita++ = (char) GetBits(step=alloc1->bits);
        bita = bit_alloc;
        scfsi=scfsi_buf;
        for (i=sblimit;i;i--)
            if (*bita++)
                *scfsi++ = (char) GetBitsFast(2);
    }
    
    bita = bit_alloc;
    scfsi=scfsi_buf;
    for (i=sblimit2;i;i--) 
        if (*bita++) 
            switch (*scfsi++)  {
    case 0: 
        *scale++ = GetBitsFast(6);
        *scale++ = GetBitsFast(6);
        *scale++ = GetBitsFast(6);
        break;
    case 1 : 
        *scale++ = sc = GetBitsFast(6);
        *scale++ = sc;
        *scale++ = GetBitsFast(6);
        break;
    case 2: 
        *scale++ = sc = GetBitsFast(6);
        *scale++ = sc;
        *scale++ = sc;
        break;
    default:              /* case 3 */
        *scale++ = GetBitsFast(6);
        *scale++ = sc = GetBitsFast(6);
        *scale++ = sc;
        break;
        }
}

void II_step_two(unsigned int *bit_alloc,real fraction[2][4][SBLIMIT],int *scale,int x1)
{
    int i,j,k,ba;
    int stereo = fr.stereo;
    int sblimit = fr.II_sblimit;
    int jsbound = fr.jsbound;
    const struct al_table *alloc2,*alloc1 = fr.alloc;
    unsigned int *bita=bit_alloc;
    int d1,step;
    
    for (i=0;i<jsbound;i++,alloc1+=(1<<step)){
        step = alloc1->bits;
        for (j=0;j<stereo;j++){
            if ( (ba=*bita++) ) {
                k=(alloc2 = alloc1+ba)->bits;
                if( (d1=alloc2->d) < 0) {
                    real cm=muls[k][scale[x1]];
                    fraction[j][0][i] = ((real) ((int)GetBits(k) + d1)) * cm;
                    fraction[j][1][i] = ((real) ((int)GetBits(k) + d1)) * cm;
                    fraction[j][2][i] = ((real) ((int)GetBits(k) + d1)) * cm;
                } else {
                    static int *table[] = { 0,0,0,grp_3tab,0,grp_5tab,0,0,0,grp_9tab };
                    unsigned int idx,*tab,m=scale[x1];
                    idx = (unsigned int) GetBits(k);
                    tab = (unsigned int *) (table[d1] + idx + idx + idx);
                    fraction[j][0][i] = muls[*tab++][m];
                    fraction[j][1][i] = muls[*tab++][m];
                    fraction[j][2][i] = muls[*tab][m];  
                }
                scale+=3;
            }
            else
                fraction[j][0][i] = fraction[j][1][i] = fraction[j][2][i] = 0.0;
        }
    }
    
    for (i=jsbound;i<sblimit;i++,alloc1+=(1<<step)) {
        step = alloc1->bits;
        bita++;   /* channel 1 and channel 2 bitalloc are the same */
        if ( (ba=*bita++) ) {
            k=(alloc2 = alloc1+ba)->bits;
            if( (d1=alloc2->d) < 0) {
                real cm;
                cm=muls[k][scale[x1+3]];
                fraction[1][0][i] = (fraction[0][0][i] = (real) ((int)GetBits(k) + d1) ) * cm;
                fraction[1][1][i] = (fraction[0][1][i] = (real) ((int)GetBits(k) + d1) ) * cm;
                fraction[1][2][i] = (fraction[0][2][i] = (real) ((int)GetBits(k) + d1) ) * cm;
                cm=muls[k][scale[x1]];
                fraction[0][0][i] *= cm; fraction[0][1][i] *= cm; fraction[0][2][i] *= cm;
            } else
            {
                static int *table[] = { 0,0,0,grp_3tab,0,grp_5tab,0,0,0,grp_9tab };
                unsigned int idx,*tab,m1,m2;
                m1 = scale[x1]; m2 = scale[x1+3];
                idx = (unsigned int) GetBits(k);
                tab = (unsigned int *) (table[d1] + idx + idx + idx);
                fraction[0][0][i] = muls[*tab][m1]; fraction[1][0][i] = muls[*tab++][m2];
                fraction[0][1][i] = muls[*tab][m1]; fraction[1][1][i] = muls[*tab++][m2];
                fraction[0][2][i] = muls[*tab][m1]; fraction[1][2][i] = muls[*tab][m2];
            }
            scale+=6;
        }
        else {
            fraction[0][0][i] = fraction[0][1][i] = fraction[0][2][i] =
                fraction[1][0][i] = fraction[1][1][i] = fraction[1][2][i] = 0.0;
        }
    }
    
    if(sblimit > (SBLIMIT>>fr.down_sample) )
        sblimit = SBLIMIT>>fr.down_sample;
    
    for(i=sblimit;i<SBLIMIT;i++)
        for (j=0;j<stereo;j++)
            fraction[j][0][i] = fraction[j][1][i] = fraction[j][2][i] = 0.0;
        
}

void make_conv16to8_table(){
    int i;
    for(i=-2048;i<2048;i++) conv16to8[i]=(i>>4)+128;
}

void make_decode_tables(long scaleval)
{
    int i,j,k,kr,divv;
    real *table,*costab;
    
    for(i=0;i<5;i++) {
        kr=0x10>>i; divv=0x40>>i;
        costab = pnts[i];
        for(k=0;k<kr;k++)
            costab[k] = 1.0 / (2.0 * cos(M_PI * ((double) k * 2.0 + 1.0) / (double) divv));
    }
    
    table = decwin;
    scaleval = -scaleval;
    for(i=0,j=0;i<256;i++,j++,table+=32) {
        if(table < decwin+512+16)
            table[16] = table[0] = (double) intwinbase[j] / 65536.0 * (double) scaleval;
        if(i % 32 == 31)
            table -= 1023;
        if(i % 64 == 63)
            scaleval = - scaleval;
    }
    
    for( /* i=256 */ ;i<512;i++,j--,table+=32){
        if(table < decwin+512+16)
            table[16] = table[0] = (double) intwinbase[j] / 65536.0 * (double) scaleval;
        if(i % 32 == 31)
            table -= 1023;
        if(i % 64 == 63)
            scaleval = - scaleval;
    }
}

void III_get_side_info_1(struct III_sideinfo *si,int stereo,int ms_stereo,long sfreq,int single)
{
    int ch, gr;
    int powdiff = (single == 3) ? 4 : 0;
    si->main_data_begin = GetBits(9);
    if(stereo==1) si->private_bits = GetBitsFast(5);
    else si->private_bits = GetBitsFast(3);
    for(ch=0;ch<stereo;ch++)  {
        si->ch[ch].gr[0].scfsi = -1;
        si->ch[ch].gr[1].scfsi = GetBitsFast(4);
    }
    for (gr=0; gr<2; gr++)  {
        for (ch=0; ch<stereo; ch++) {
            register struct gr_info_s *gr_info = &(si->ch[ch].gr[gr]);
            gr_info->part2_3_length = GetBits(12);
            gr_info->big_values = GetBitsFast(9);
            if(gr_info->big_values>288) gr_info->big_values = 288;
            gr_info->pow2gain = gainpow2+256 - GetBitsFast(8) + powdiff;
            if(ms_stereo) gr_info->pow2gain += 2;
            gr_info->scalefac_compress = GetBitsFast(4);
            if(Get1Bit()) {
                int i;
                gr_info->block_type = GetBitsFast(2);
                gr_info->mixed_block_flag = Get1Bit();
                gr_info->table_select[0] = GetBitsFast(5);
                gr_info->table_select[1] = GetBitsFast(5);
                gr_info->table_select[2] = 0;
                for(i=0;i<3;i++) gr_info->full_gain[i] = gr_info->pow2gain + (GetBitsFast(3)<<3);
                if(gr_info->block_type==0) {
                    // Throw a engine error
                    throw 1;
                }
                gr_info->region1start = 36>>1;
                gr_info->region2start = 576>>1;
            } else {
                int i,r0c,r1c;
                for(i=0;i<3;i++) gr_info->table_select[i]=GetBitsFast(5);
                r0c = GetBitsFast(4);
                r1c = GetBitsFast(3);
                gr_info->region1start = bandInfo[sfreq].longIdx[r0c+1] >> 1 ;
                gr_info->region2start = bandInfo[sfreq].longIdx[r0c+1+r1c+1] >> 1;
                gr_info->block_type = 0;
                gr_info->mixed_block_flag = 0;
            }
            gr_info->preflag = Get1Bit();
            gr_info->scalefac_scale = Get1Bit();
            gr_info->count1table_select = Get1Bit();
        }
    }
}

void III_get_side_info_2(struct III_sideinfo *si,int stereo,int ms_stereo,long sfreq,int single)
{
    int ch;
    int powdiff = (single == 3) ? 4 : 0;
    si->main_data_begin = GetBits(8);
    if(stereo==1) si->private_bits = Get1Bit();
    else si->private_bits = GetBitsFast(2);
    for (ch=0; ch<stereo; ch++) {
        register struct gr_info_s *gr_info = &(si->ch[ch].gr[0]);
        gr_info->part2_3_length = GetBits(12);
        gr_info->big_values = GetBitsFast(9);
        if(gr_info->big_values>288) gr_info->big_values=288;
        gr_info->pow2gain = gainpow2 + 256 - GetBitsFast(8) + powdiff;
        if(ms_stereo) gr_info->pow2gain += 2;
        gr_info->scalefac_compress = GetBits(9);
        if(Get1Bit()) {
            int i;
            gr_info->block_type = GetBitsFast(2);
            gr_info->mixed_block_flag = Get1Bit();
            gr_info->table_select[0] = GetBitsFast(5);
            gr_info->table_select[1] = GetBitsFast(5);
            gr_info->table_select[2] = 0;
            for(i=0;i<3;i++) gr_info->full_gain[i]=gr_info->pow2gain+(GetBitsFast(3)<<3);
            if(gr_info->block_type==0) 
            {
                // Throw engine error
                throw 1;
            }
            if(gr_info->block_type==2) gr_info->region1start = 36>>1;
            else gr_info->region1start = 54>>1;
            gr_info->region2start = 576>>1;
        } else {
            int i,r0c,r1c;
            for (i=0;i<3;i++) gr_info->table_select[i]=GetBitsFast(5);
            r0c = GetBitsFast(4);
            r1c = GetBitsFast(3);
            gr_info->region1start = bandInfo[sfreq].longIdx[r0c+1] >> 1 ;
            gr_info->region2start = bandInfo[sfreq].longIdx[r0c+1+r1c+1] >> 1;
            gr_info->block_type = 0;
            gr_info->mixed_block_flag = 0;
        }
        gr_info->scalefac_scale = Get1Bit();
        gr_info->count1table_select = Get1Bit();
    }
}

int III_dequantize_sample(real xr[SBLIMIT][SSLIMIT],int *scf,struct gr_info_s *gr_info,int sfreq,int part2bits)
{
    int shift = 1 + gr_info->scalefac_scale;
    real *xrpnt = (real *) xr;
    int l[3],l3;
    int part2remain = gr_info->part2_3_length - part2bits;
    int *me;
    {
        int bv       = gr_info->big_values;
        int region1  = gr_info->region1start;
        int region2  = gr_info->region2start;
        l3 = ((576>>1)-bv)>>1;   
        if(bv <= region1) {
            l[0] = bv; l[1] = 0; l[2] = 0;
        } else {
            l[0] = region1;
            if(bv <= region2) {
                l[1] = bv - l[0];  l[2] = 0;
            } else {
                l[1] = region2 - l[0]; l[2] = bv - region2;
            }
        }
    }
    if(gr_info->block_type==2) 
    {
        int i,max[4];
        int step=0,lwin=0,cb=0;
        register real v = 0.0;
        register int *m,mc;
        if(gr_info->mixed_block_flag) 
        {
            max[3] = -1;
            max[0] = max[1] = max[2] = 2;
            m = map[sfreq][0];
            me = mapend[sfreq][0];
        } else 
        {
            max[0] = max[1] = max[2] = max[3] = -1;
            m = map[sfreq][1];
            me = mapend[sfreq][1];
        }
        mc = 0;
        for(i=0;i<2;i++) 
        {
            int lp=l[i];
            struct newhuff *h = ht+gr_info->table_select[i];
            for(;lp;lp--,mc--) 
            {
                register int x,y;
                if((!mc)) 
                {
                    mc = *m++;
                    xrpnt = ((real *) xr) + (*m++);
                    lwin = *m++;
                    cb = *m++;
                    if(lwin==3) 
                    {
                        v = gr_info->pow2gain[(*scf++) << shift];
                        step = 1;
                    } else 
                    {
                        v = gr_info->full_gain[lwin][(*scf++) << shift];
                        step = 3;
                    }
                }
                {
                    register short *val = h->table;
                    while((y=*val++)<0) 
                    {
                        if(Get1Bit()) val -= y;
                        part2remain--;
                    }
                    x = y >> 4;
                    y &= 0xf;
                }
                if(x==15) 
                {
                    max[lwin]=cb;
                    part2remain -= h->linbits+1;
                    x += GetBits(h->linbits);
                    if(Get1Bit()) *xrpnt = -ispow[x] * v;
                    else *xrpnt=ispow[x] * v;
                } else if(x) 
                {
                    max[lwin] = cb;
                    if(Get1Bit()) *xrpnt=-ispow[x] * v;
                    else *xrpnt=ispow[x] * v;
                    part2remain--;
                } else *xrpnt=0.0;
                xrpnt += step;
                if(y==15) 
                {
                    max[lwin] = cb;
                    part2remain -= h->linbits+1;
                    y += GetBits(h->linbits);
                    if(Get1Bit())
                        *xrpnt = -ispow[y] * v;
                    else
                        *xrpnt =  ispow[y] * v;
                }
                else if(y) {
                    max[lwin] = cb;
                    if(Get1Bit())
                        *xrpnt = -ispow[y] * v;
                    else
                        *xrpnt =  ispow[y] * v;
                    part2remain--;
                }
                else
                    *xrpnt = 0.0;
                xrpnt += step;
            }
        }
        for(;l3 && (part2remain > 0);l3--) {
            struct newhuff *h = htc+gr_info->count1table_select;
            register short *val = h->table,a;
            
            while((a=*val++)<0) {
                part2remain--;
                if(part2remain < 0) {
                    part2remain++;
                    a = 0;
                    break;
                }
                if (Get1Bit())
                    val -= a;
            }
            
            for(i=0;i<4;i++) {
                if(!(i & 1)) {
                    if(!mc) {
                        mc = *m++;
                        xrpnt = ((real *) xr) + (*m++);
                        lwin = *m++;
                        cb = *m++;
                        if(lwin == 3) {
                            v = gr_info->pow2gain[(*scf++) << shift];
                            step = 1;
                        }
                        else {
                            v = gr_info->full_gain[lwin][(*scf++) << shift];
                            step = 3;
                        }
                    }
                    mc--;
                }
                if( (a & (0x8>>i)) ) {
                    max[lwin] = cb;
                    part2remain--;
                    if(part2remain < 0) {
                        part2remain++;
                        break;
                    }
                    if(Get1Bit()) 
                        *xrpnt = -v;
                    else
                        *xrpnt = v;
                }
                else
                    *xrpnt = 0.0;
                xrpnt += step;
            }
        }
        
        while( m < me ) {
            if(!mc) {
                mc = *m++;
                xrpnt = ((real *) xr) + *m++;
                if( (*m++) == 3)
                    step = 1;
                else
                    step = 3;
                m++; /* cb */
            }
            mc--;
            *xrpnt = 0.0;
            xrpnt += step;
            *xrpnt = 0.0;
            xrpnt += step;
        }
        
        gr_info->maxband[0] = max[0]+1;
        gr_info->maxband[1] = max[1]+1;
        gr_info->maxband[2] = max[2]+1;
        gr_info->maxbandl = max[3]+1;
        
        {
            int rmax = max[0] > max[1] ? max[0] : max[1];
            rmax = (rmax > max[2] ? rmax : max[2]) + 1;
            gr_info->maxb = rmax ? shortLimit[sfreq][rmax] : longLimit[sfreq][max[3]+1];
        }
        
  }
  else {
      const int *pretab = gr_info->preflag ? pretab1 : pretab2;
      int i,max = -1;
      int cb = 0;
      register int *m = map[sfreq][2];
      register real v = 0.0;
      register int mc = 0;
      for(i=0;i<3;i++) {
          int lp = l[i];
          struct newhuff *h = ht+gr_info->table_select[i];
          
          for(;lp;lp--,mc--) {
              int x,y;
              
              if(!mc) {
                  mc = *m++;
                  v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
                  cb = *m++;
              }
              {
                  register short *val = h->table;
                  while((y=*val++)<0) {
                      if (Get1Bit())
                          val -= y;
                      part2remain--;
                  }
                  x = y >> 4;
                  y &= 0xf;
              }
              if (x == 15) {
                  max = cb;
                  part2remain -= h->linbits+1;
                  x += GetBits(h->linbits);
                  if(Get1Bit())
                      *xrpnt++ = -ispow[x] * v;
                  else
                      *xrpnt++ =  ispow[x] * v;
              }
              else if(x) {
                  max = cb;
                  if(Get1Bit())
                      *xrpnt++ = -ispow[x] * v;
                  else
                      *xrpnt++ =  ispow[x] * v;
                  part2remain--;
              }
              else
                  *xrpnt++ = 0.0;
              
              if (y == 15) {
                  max = cb;
                  part2remain -= h->linbits+1;
                  y += GetBits(h->linbits);
                  if(Get1Bit())
                      *xrpnt++ = -ispow[y] * v;
                  else
                      *xrpnt++ =  ispow[y] * v;
              }
              else if(y) {
                  max = cb;
                  if(Get1Bit())
                      *xrpnt++ = -ispow[y] * v;
                  else
                      *xrpnt++ =  ispow[y] * v;
                  part2remain--;
              }
              else
                  *xrpnt++ = 0.0;
          }
      }
      
      /*
      * short (count1table) values
      */
      for(;l3 && (part2remain > 0);l3--) {
          struct newhuff *h = htc+gr_info->count1table_select;
          register short *val = h->table,a;
          
          while((a=*val++)<0) {
              part2remain--;
              if(part2remain < 0) {
                  part2remain++;
                  a = 0;
                  break;
              }
              if (Get1Bit())
                  val -= a;
          }
          
          for(i=0;i<4;i++) {
              if(!(i & 1)) {
                  if(!mc) {
                      mc = *m++;
                      cb = *m++;
                      v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
                  }
                  mc--;
              }
              if ( (a & (0x8>>i)) ) {
                  max = cb;
                  part2remain--;
                  if(part2remain < 0) {
                      part2remain++;
                      break;
                  }
                  if(Get1Bit())
                      *xrpnt++ = -v;
                  else
                      *xrpnt++ = v;
              }
              else
                  *xrpnt++ = 0.0;
          }
      }
      for(i=(&xr[SBLIMIT][0]-xrpnt)>>1;i;i--) {
          *xrpnt++ = 0.0;
          *xrpnt++ = 0.0;
      }
      
      gr_info->maxbandl = max+1;
      gr_info->maxb = longLimit[sfreq][gr_info->maxbandl];
  }
  
  while( part2remain > 16 ) {
      GetBits(16);
      part2remain -= 16;
  }
  if(part2remain > 0)
      GetBits(part2remain);
  else if(part2remain < 0) {
      return 1; /* -> error */
  }
  return 0;
}

int III_dequantize_sample_ms(real xr[2][SBLIMIT][SSLIMIT],int *scf,struct gr_info_s *gr_info,int sfreq,int part2bits)
{
    int shift = 1 + gr_info->scalefac_scale;
    real *xrpnt = (real *) xr[1];
    real *xr0pnt = (real *) xr[0];
    int l[3],l3;
    int part2remain = gr_info->part2_3_length - part2bits;
    int *me;
    
    {
        int bv       = gr_info->big_values;
        int region1  = gr_info->region1start;
        int region2  = gr_info->region2start;
        
        l3 = ((576>>1)-bv)>>1;   
        if(bv <= region1) {
            l[0] = bv; l[1] = 0; l[2] = 0;
        }
        else {
            l[0] = region1;
            if(bv <= region2) {
                l[1] = bv - l[0];  l[2] = 0;
            }
            else {
                l[1] = region2 - l[0]; l[2] = bv - region2;
            }
        }
    }
    
    if(gr_info->block_type == 2) {
        int i,max[4];
        int step=0,lwin=0,cb=0;
        register real v = 0.0;
        register int *m,mc = 0;
        
        if(gr_info->mixed_block_flag) {
            max[3] = -1;
            max[0] = max[1] = max[2] = 2;
            m = map[sfreq][0];
            me = mapend[sfreq][0];
        }
        else {
            max[0] = max[1] = max[2] = max[3] = -1;
            m = map[sfreq][1];
            me = mapend[sfreq][1];
        }
        
        for(i=0;i<2;i++) {
            int lp = l[i];
            struct newhuff *h = ht+gr_info->table_select[i];
            for(;lp;lp--,mc--) {
                int x,y;
                
                if(!mc) {
                    mc = *m++;
                    xrpnt = ((real *) xr[1]) + *m;
                    xr0pnt = ((real *) xr[0]) + *m++;
                    lwin = *m++;
                    cb = *m++;
                    if(lwin == 3) {
                        v = gr_info->pow2gain[(*scf++) << shift];
                        step = 1;
                    }
                    else {
                        v = gr_info->full_gain[lwin][(*scf++) << shift];
                        step = 3;
                    }
                }
                {
                    register short *val = h->table;
                    while((y=*val++)<0) {
                        if (Get1Bit())
                            val -= y;
                        part2remain--;
                    }
                    x = y >> 4;
                    y &= 0xf;
                }
                if(x == 15) {
                    max[lwin] = cb;
                    part2remain -= h->linbits+1;
                    x += GetBits(h->linbits);
                    if(Get1Bit()) {
                        real a = ispow[x] * v;
                        *xrpnt = *xr0pnt + a;
                        *xr0pnt -= a;
                    }
                    else {
                        real a = ispow[x] * v;
                        *xrpnt = *xr0pnt - a;
                        *xr0pnt += a;
                    }
                }
                else if(x) {
                    max[lwin] = cb;
                    if(Get1Bit()) {
                        real a = ispow[x] * v;
                        *xrpnt = *xr0pnt + a;
                        *xr0pnt -= a;
                    }
                    else {
                        real a = ispow[x] * v;
                        *xrpnt = *xr0pnt - a;
                        *xr0pnt += a;
                    }
                    part2remain--;
                }
                else
                    *xrpnt = *xr0pnt;
                xrpnt += step;
                xr0pnt += step;
                
                if(y == 15) {
                    max[lwin] = cb;
                    part2remain -= h->linbits+1;
                    y += GetBits(h->linbits);
                    if(Get1Bit()) {
                        real a = ispow[y] * v;
                        *xrpnt = *xr0pnt + a;
                        *xr0pnt -= a;
                    }
                    else {
                        real a = ispow[y] * v;
                        *xrpnt = *xr0pnt - a;
                        *xr0pnt += a;
                    }
                }
                else if(y) {
                    max[lwin] = cb;
                    if(Get1Bit()) {
                        real a = ispow[y] * v;
                        *xrpnt = *xr0pnt + a;
                        *xr0pnt -= a;
                    }
                    else {
                        real a = ispow[y] * v;
                        *xrpnt = *xr0pnt - a;
                        *xr0pnt += a;
                    }
                    part2remain--;
                }
                else
                    *xrpnt = *xr0pnt;
                xrpnt += step;
                xr0pnt += step;
            }
        }
        
        for(;l3 && (part2remain > 0);l3--) {
            struct newhuff *h = htc+gr_info->count1table_select;
            register short *val = h->table,a;
            
            while((a=*val++)<0) {
                part2remain--;
                if(part2remain < 0) {
                    part2remain++;
                    a = 0;
                    break;
                }
                if (Get1Bit())
                    val -= a;
            }
            
            for(i=0;i<4;i++) {
                if(!(i & 1)) {
                    if(!mc) {
                        mc = *m++;
                        xrpnt = ((real *) xr[1]) + *m;
                        xr0pnt = ((real *) xr[0]) + *m++;
                        lwin = *m++;
                        cb = *m++;
                        if(lwin == 3) {
                            v = gr_info->pow2gain[(*scf++) << shift];
                            step = 1;
                        }
                        else {
                            v = gr_info->full_gain[lwin][(*scf++) << shift];
                            step = 3;
                        }
                    }
                    mc--;
                }
                if( (a & (0x8>>i)) ) {
                    max[lwin] = cb;
                    part2remain--;
                    if(part2remain < 0) {
                        part2remain++;
                        break;
                    }
                    if(Get1Bit()) {
                        *xrpnt = *xr0pnt + v;
                        *xr0pnt -= v;
                    }
                    else {
                        *xrpnt = *xr0pnt - v;
                        *xr0pnt += v;
                    }
                }
                else
                    *xrpnt = *xr0pnt;
                xrpnt += step;
                xr0pnt += step;
            }
        }
        
        while( m < me ) {
            if(!mc) {
                mc = *m++;
                xrpnt = ((real *) xr[1]) + *m;
                xr0pnt = ((real *) xr[0]) + *m++;
                if(*m++ == 3)
                    step = 1;
                else
                    step = 3;
                m++; /* cb */
            }
            mc--;
            *xrpnt = *xr0pnt;
            xrpnt += step;
            xr0pnt += step;
            *xrpnt = *xr0pnt;
            xrpnt += step;
            xr0pnt += step;
        }
        
        gr_info->maxband[0] = max[0]+1;
        gr_info->maxband[1] = max[1]+1;
        gr_info->maxband[2] = max[2]+1;
        gr_info->maxbandl = max[3]+1;
        
        {
            int rmax = max[0] > max[1] ? max[0] : max[1];
            rmax = (rmax > max[2] ? rmax : max[2]) + 1;
            gr_info->maxb = rmax ? shortLimit[sfreq][rmax] : longLimit[sfreq][max[3]+1];
        }
  }
  else {
      const int *pretab = gr_info->preflag ? pretab1 : pretab2;
      int i,max = -1;
      int cb = 0;
      register int mc=0,*m = map[sfreq][2];
      register real v = 0.0;
      for(i=0;i<3;i++) {
          int lp = l[i];
          struct newhuff *h = ht+gr_info->table_select[i];
          
          for(;lp;lp--,mc--) {
              int x,y;
              if(!mc) {
                  mc = *m++;
                  cb = *m++;
                  v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
              }
              {
                  register short *val = h->table;
                  while((y=*val++)<0) {
                      if (Get1Bit())
                          val -= y;
                      part2remain--;
                  }
                  x = y >> 4;
                  y &= 0xf;
              }
              if (x == 15) {
                  max = cb;
                  part2remain -= h->linbits+1;
                  x += GetBits(h->linbits);
                  if(Get1Bit()) {
                      real a = ispow[x] * v;
                      *xrpnt++ = *xr0pnt + a;
                      *xr0pnt++ -= a;
                  }
                  else {
                      real a = ispow[x] * v;
                      *xrpnt++ = *xr0pnt - a;
                      *xr0pnt++ += a;
                  }
              }
              else if(x) {
                  max = cb;
                  if(Get1Bit()) {
                      real a = ispow[x] * v;
                      *xrpnt++ = *xr0pnt + a;
                      *xr0pnt++ -= a;
                  }
                  else {
                      real a = ispow[x] * v;
                      *xrpnt++ = *xr0pnt - a;
                      *xr0pnt++ += a;
                  }
                  part2remain--;
              }
              else
                  *xrpnt++ = *xr0pnt++;
              
              if (y == 15) {
                  max = cb;
                  part2remain -= h->linbits+1;
                  y += GetBits(h->linbits);
                  if(Get1Bit()) {
                      real a = ispow[y] * v;
                      *xrpnt++ = *xr0pnt + a;
                      *xr0pnt++ -= a;
                  }
                  else {
                      real a = ispow[y] * v;
                      *xrpnt++ = *xr0pnt - a;
                      *xr0pnt++ += a;
                  }
              }
              else if(y) {
                  max = cb;
                  if(Get1Bit()) {
                      real a = ispow[y] * v;
                      *xrpnt++ = *xr0pnt + a;
                      *xr0pnt++ -= a;
                  }
                  else {
                      real a = ispow[y] * v;
                      *xrpnt++ = *xr0pnt - a;
                      *xr0pnt++ += a;
                  }
                  part2remain--;
              }
              else
                  *xrpnt++ = *xr0pnt++;
          }
      }
      
      for(;l3 && (part2remain > 0);l3--) {
          struct newhuff *h = htc+gr_info->count1table_select;
          register short *val = h->table,a;
          
          while((a=*val++)<0) {
              part2remain--;
              if(part2remain < 0) {
                  part2remain++;
                  a = 0;
                  break;
              }
              if (Get1Bit())
                  val -= a;
          }
          
          for(i=0;i<4;i++) {
              if(!(i & 1)) {
                  if(!mc) {
                      mc = *m++;
                      cb = *m++;
                      v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
                  }
                  mc--;
              }
              if ( (a & (0x8>>i)) ) {
                  max = cb;
                  part2remain--;
                  if(part2remain <= 0) {
                      part2remain++;
                      break;
                  }
                  if(Get1Bit()) {
                      *xrpnt++ = *xr0pnt + v;
                      *xr0pnt++ -= v;
                  }
                  else {
                      *xrpnt++ = *xr0pnt - v;
                      *xr0pnt++ += v;
                  }
              }
              else
                  *xrpnt++ = *xr0pnt++;
          }
      }
      for(i=(&xr[1][SBLIMIT][0]-xrpnt)>>1;i;i--) {
          *xrpnt++ = *xr0pnt++;
          *xrpnt++ = *xr0pnt++;
      }
      
      gr_info->maxbandl = max+1;
      gr_info->maxb = longLimit[sfreq][gr_info->maxbandl];
  }
  
  while ( part2remain > 16 ) {
      GetBits(16);
      part2remain -= 16;
  }
  if(part2remain > 0 )
      GetBits(part2remain);
  else if(part2remain < 0) {
      return 1; /* -> error */
  }
  return 0;
}

void III_i_stereo(real xr_buf[2][SBLIMIT][SSLIMIT],int *scalefac,struct gr_info_s *gr_info,int sfreq,int ms_stereo,int lsf){
    real (*xr)[SBLIMIT*SSLIMIT] = (real (*)[SBLIMIT*SSLIMIT]) xr_buf;
    struct bandInfoStruct *bi = (struct bandInfoStruct *) &bandInfo[sfreq];
    real *tab1,*tab2;
    
    if(lsf) {
        int p = gr_info->scalefac_compress & 0x1;
        if(ms_stereo) {
            tab1 = pow1_2[p]; tab2 = pow2_2[p];
        }
        else {
            tab1 = pow1_1[p]; tab2 = pow2_1[p];
        }
    }
    else {
        if(ms_stereo) {
            tab1 = tan1_2; tab2 = tan2_2;
        }
        else {
            tab1 = tan1_1; tab2 = tan2_1;
        }
    }
    
    if (gr_info->block_type == 2)
    {
        int lwin,do_l = 0;
        if( gr_info->mixed_block_flag )
            do_l = 1;
        
        for (lwin=0;lwin<3;lwin++) /* process each window */
        {
            /* get first band with zero values */
            int is_p,sb,idx,sfb = gr_info->maxband[lwin];  /* sfb is minimal 3 for mixed mode */
            if(sfb > 3)
                do_l = 0;
            
            for(;sfb<12;sfb++)
            {
                is_p = scalefac[sfb*3+lwin-gr_info->mixed_block_flag]; /* scale: 0-15 */ 
                if(is_p != 7) {
                    real t1,t2;
                    sb = bi->shortDiff[sfb];
                    idx = bi->shortIdx[sfb] + lwin;
                    t1 = tab1[is_p]; t2 = tab2[is_p];
                    for (; sb > 0; sb--,idx+=3)
                    {
                        real v = xr[0][idx];
                        xr[0][idx] = v * t1;
                        xr[1][idx] = v * t2;
                    }
                }
            }
            
#if 1
            /* in the original: copy 10 to 11 , here: copy 11 to 12 
            maybe still wrong??? (copy 12 to 13?) */
            is_p = scalefac[11*3+lwin-gr_info->mixed_block_flag]; /* scale: 0-15 */
            sb = bi->shortDiff[12];
            idx = bi->shortIdx[12] + lwin;
#else
            is_p = scalefac[10*3+lwin-gr_info->mixed_block_flag]; /* scale: 0-15 */
            sb = bi->shortDiff[11];
            idx = bi->shortIdx[11] + lwin;
#endif
            if(is_p != 7)
            {
                real t1,t2;
                t1 = tab1[is_p]; t2 = tab2[is_p];
                for ( ; sb > 0; sb--,idx+=3 )
                {  
                    real v = xr[0][idx];
                    xr[0][idx] = v * t1;
                    xr[1][idx] = v * t2;
                }
            }
        } /* end for(lwin; .. ; . ) */
        
        if (do_l)
        {
        /* also check l-part, if ALL bands in the three windows are 'empty'
        * and mode = mixed_mode 
            */
            int sfb = gr_info->maxbandl;
            int idx = bi->longIdx[sfb];
            
            for ( ; sfb<8; sfb++ )
            {
                int sb = bi->longDiff[sfb];
                int is_p = scalefac[sfb]; /* scale: 0-15 */
                if(is_p != 7) {
                    real t1,t2;
                    t1 = tab1[is_p]; t2 = tab2[is_p];
                    for ( ; sb > 0; sb--,idx++)
                    {
                        real v = xr[0][idx];
                        xr[0][idx] = v * t1;
                        xr[1][idx] = v * t2;
                    }
                }
                else 
                    idx += sb;
            }
        }     
    } 
    else /* ((gr_info->block_type != 2)) */
    {
        int sfb = gr_info->maxbandl;
        int is_p,idx = bi->longIdx[sfb];
        for ( ; sfb<21; sfb++)
        {
            int sb = bi->longDiff[sfb];
            is_p = scalefac[sfb]; /* scale: 0-15 */
            if(is_p != 7) {
                real t1,t2;
                t1 = tab1[is_p]; t2 = tab2[is_p];
                for ( ; sb > 0; sb--,idx++)
                {
                    real v = xr[0][idx];
                    xr[0][idx] = v * t1;
                    xr[1][idx] = v * t2;
                }
            }
            else
                idx += sb;
        }
        
        is_p = scalefac[20]; /* copy l-band 20 to l-band 21 */
        if(is_p != 7)
        {
            int sb;
            real t1 = tab1[is_p],t2 = tab2[is_p]; 
            
            for ( sb = bi->longDiff[21]; sb > 0; sb--,idx++ )
            {
                real v = xr[0][idx];
                xr[0][idx] = v * t1;
                xr[1][idx] = v * t2;
            }
        }
    } /* ... */
}

void III_antialias(real xr[SBLIMIT][SSLIMIT],struct gr_info_s *gr_info)
{
    int sblim;
    if(gr_info->block_type==2)
    {
        if(!gr_info->mixed_block_flag) return;
        sblim = 1; 
    } else 
    {
        sblim = gr_info->maxb-1;
    }
    {
        int sb;
        real *xr1=(real *) xr[1];
        for(sb=sblim;sb;sb--,xr1+=10)
        {
            int ss;
            real *cs=aa_cs,*ca=aa_ca;
            real *xr2 = xr1;
            for(ss=7;ss>=0;ss--)
            {
                register real bu = *--xr2,bd = *xr1;
                *xr2   = (bu * (*cs)   ) - (bd * (*ca)   );
                *xr1++ = (bd * (*cs++) ) + (bu * (*ca++) );
            }
        }
    }
}

void III_hybrid(real fsIn[SBLIMIT][SSLIMIT],real tsOut[SSLIMIT][SBLIMIT],int ch,struct gr_info_s *gr_info)
{
    real *tspnt = (real *) tsOut;
    static real block[2][2][SBLIMIT*SSLIMIT] = { { { 0, } } };
    static int blc[2]={0,0};
    real *rawout1,*rawout2;
    int bt;
    int sb = 0;
    {
        int b = blc[ch];
        rawout1=block[b][ch];
        b=-b+1;
        rawout2=block[b][ch];
        blc[ch] = b;
    }
    
    
    if(gr_info->mixed_block_flag) {
        sb = 2;
        dct36(fsIn[0],rawout1,rawout2,win[0],tspnt);
        dct36(fsIn[1],rawout1+18,rawout2+18,win1[0],tspnt+1);
        rawout1 += 36; rawout2 += 36; tspnt += 2;
    }
    
    bt = gr_info->block_type;
    if(bt == 2) {
        for (; sb<gr_info->maxb; sb+=2,tspnt+=2,rawout1+=36,rawout2+=36) {
            dct12(fsIn[sb],rawout1,rawout2,win[2],tspnt);
            dct12(fsIn[sb+1],rawout1+18,rawout2+18,win1[2],tspnt+1);
        }
    }
    else {
        for (; sb<gr_info->maxb; sb+=2,tspnt+=2,rawout1+=36,rawout2+=36) {
            dct36(fsIn[sb],rawout1,rawout2,win[bt],tspnt);
            dct36(fsIn[sb+1],rawout1+18,rawout2+18,win1[bt],tspnt+1);
        }
    }
    
    for(;sb<SBLIMIT;sb++,tspnt++) {
        int i;
        for(i=0;i<SSLIMIT;i++) {
            tspnt[i*SBLIMIT] = *rawout1++;
            *rawout2++ = 0.0;
        }
    }
}

void synth_ntom_set_step(long m, long n)
{
        if (n >= 96000 || m >= 96000 || m == 0 || n == 0) 
        {
                throw 1;
        }

        n *= NTOM_MUL;
        ntom_step = n / m;

        if (ntom_step > 8*NTOM_MUL) 
        {
                throw 1;
        }
        ntom_val[0] = ntom_val[1] = NTOM_MUL>>1;
}

int synth_ntom_8bit(real *bandPtr,int channel,unsigned char *samples,int *pnt)
{
  short samples_tmp[8*64];
  short *tmp1 = samples_tmp + channel;
  int i,ret;
  int pnt1 = 0;

  ret = synth_ntom(bandPtr,channel,(unsigned char *) samples_tmp,&pnt1);
  samples += channel + *pnt;

  for(i=0;i<(pnt1>>2);i++) {
    *samples = conv16to8[*tmp1>>AUSHIFT];
    samples += 2;
    tmp1 += 2;
  }
  *pnt += pnt1>>1;

  return ret;
}

int synth_ntom_8bit_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[8*64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_ntom(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<(pnt1>>2);i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += pnt1 >> 2;
  
  return ret;
}

int synth_ntom_8bit_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[8*64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_ntom(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<(pnt1>>2);i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += pnt1 >> 1;

  return ret;
}

int synth_ntom_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[8*64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_ntom(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<(pnt1>>2);i++) {
    *( (short *)samples) = *tmp1;
    samples += 2;
    tmp1 += 2;
  }
  *pnt += pnt1 >> 1;

  return ret;
}


int synth_ntom_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  int i,ret;
  int pnt1 = *pnt;

  ret = synth_ntom(bandPtr,0,samples,pnt);
  samples += pnt1;
  
  for(i=0;i<((*pnt-pnt1)>>2);i++) {
    ((short *)samples)[1] = ((short *)samples)[0];
    samples+=4;
  }

  return ret;
}


int synth_ntom(real *bandPtr,int channel,unsigned char *out,int *pnt)
{
  static real buffs[2][2][0x110];
  static const int step = 2;
  static int bo = 1;
  short *samples = (short *) (out + *pnt);

  real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;
  int ntom;

  if(Args->UseEqualizer)
        do_equalizer(bandPtr, channel);

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = buffs[0];
    ntom = ntom_val[1] = ntom_val[0];
  }
  else {
    samples++;
    out += 2; /* to compute the right *pnt value */
    buf = buffs[1];
    ntom = ntom_val[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }


  {
    register int j;
    real *window = decwin + 16 - bo1;
 
    for (j=16;j;j--,window+=0x10)
    {
      real sum;

      ntom += ntom_step;
      if(ntom < NTOM_MUL) {
        window += 16;
        b0 += 16;
        continue;
      }

      sum  = *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;

      while(ntom >= NTOM_MUL) {
        WRITE_SAMPLE(samples,sum,clip);
        samples += step;
        ntom -= NTOM_MUL;
      }
    }

    ntom += ntom_step;
    if(ntom >= NTOM_MUL)
    {
      real sum;
      sum  = window[0x0] * b0[0x0];
      sum += window[0x2] * b0[0x2];
      sum += window[0x4] * b0[0x4];
      sum += window[0x6] * b0[0x6];
      sum += window[0x8] * b0[0x8];
      sum += window[0xA] * b0[0xA];
      sum += window[0xC] * b0[0xC];
      sum += window[0xE] * b0[0xE];

      while(ntom >= NTOM_MUL) {
        WRITE_SAMPLE(samples,sum,clip);
        samples += step;
        ntom -= NTOM_MUL;
      }
    }

    b0-=0x10,window-=0x20;
    window += bo1<<1;

    for (j=15;j;j--,b0-=0x20,window-=0x10)
    {
      real sum;

      ntom += ntom_step;
      if(ntom < NTOM_MUL) {
        window -= 16;
        b0 += 16;
        continue;
      }

      sum = -*(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;

      while(ntom >= NTOM_MUL) {
        WRITE_SAMPLE(samples,sum,clip);
        samples += step;
        ntom -= NTOM_MUL;
      }
    }
  }

  ntom_val[channel] = ntom;
  *pnt = ((unsigned char *) samples - out);

  return clip;
}

int synth_1to1_8bit(real *bandPtr,int channel,unsigned char *samples,int *pnt)
{
  short samples_tmp[64];
  short *tmp1 = samples_tmp + channel;
  int i,ret;
  int pnt1=0;

  ret = synth_1to1(bandPtr,channel,(unsigned char *) samples_tmp,&pnt1);
  samples += channel + *pnt;

  for(i=0;i<32;i++) {
    *samples = conv16to8[*tmp1>>AUSHIFT];
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 64;

  return ret;
}

int synth_1to1_8bit_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_1to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<32;i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += 32;
  
  return ret;
}

int synth_1to1_8bit_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_1to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<32;i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += 64;

  return ret;
}

int synth_1to1_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_1to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<32;i++) {
    *( (short *)samples) = *tmp1;
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 64;

  return ret;
}


int synth_1to1_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  int i,ret;

  ret = synth_1to1(bandPtr,0,samples,pnt);
  samples = samples + *pnt - 128;

  for(i=0;i<32;i++) {
    ((short *)samples)[1] = ((short *)samples)[0];
    samples+=4;
  }

  return ret;
}


int synth_1to1(real *bandPtr,int channel,unsigned char *out,int *pnt)
{
  static real buffs[2][2][0x110];
  static const int step = 2;
  static int bo = 1;
  short *samples = (short *) (out+*pnt);

  real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;

  if(Args->UseEqualizer)
        do_equalizer(bandPtr,channel);

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = buffs[0];
  }
  else {
    samples++;
    buf = buffs[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }


  {
    register int j;
    real *window = decwin + 16 - bo1;
 
    for (j=16;j;j--,window+=0x10,samples+=step)
    {
      real sum;
      sum  = *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;

      WRITE_SAMPLE(samples,sum,clip);
    }

    {
      real sum;
      sum  = window[0x0] * b0[0x0];
      sum += window[0x2] * b0[0x2];
      sum += window[0x4] * b0[0x4];
      sum += window[0x6] * b0[0x6];
      sum += window[0x8] * b0[0x8];
      sum += window[0xA] * b0[0xA];
      sum += window[0xC] * b0[0xC];
      sum += window[0xE] * b0[0xE];
      WRITE_SAMPLE(samples,sum,clip);
      b0-=0x10,window-=0x20,samples+=step;
    }
    window += bo1<<1;

    for (j=15;j;j--,b0-=0x20,window-=0x10,samples+=step)
    {
      real sum;
      sum = -*(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;

      WRITE_SAMPLE(samples,sum,clip);
    }
  }

  *pnt += 128;

  return clip;
}

int synth_2to1_8bit(real *bandPtr,int channel,unsigned char *samples,int *pnt)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp + channel;
  int i,ret;
  int pnt1 = 0;

  ret = synth_2to1(bandPtr,channel,(unsigned char *) samples_tmp,&pnt1);
  samples += channel + *pnt;

  for(i=0;i<16;i++) {
    *samples = conv16to8[*tmp1>>AUSHIFT];
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 32;

  return ret;
}

int synth_2to1_8bit_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_2to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<16;i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += 16;

  return ret;
}


int synth_2to1_8bit_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_2to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<16;i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += 32;

  return ret;
}

int synth_2to1_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1=0;

  ret = synth_2to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<16;i++) {
    *( (short *) samples) = *tmp1;
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 32;

  return ret;
}

int synth_2to1_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  int i,ret;

  ret = synth_2to1(bandPtr,0,samples,pnt);
  samples = samples + *pnt - 64;

  for(i=0;i<16;i++) {
    ((short *)samples)[1] = ((short *)samples)[0];
    samples+=4;
  }
  
  return ret;
}

int synth_2to1(real *bandPtr,int channel,unsigned char *out,int *pnt)
{
  static real buffs[2][2][0x110];
  static const int step = 2;
  static int bo = 1;
  short *samples = (short *) (out + *pnt);

  real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;

  if(Args->UseEqualizer)
    do_equalizer(bandPtr,channel);

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = buffs[0];
  }
  else {
    samples++;
    buf = buffs[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }

  {
    register int j;
    real *window = decwin + 16 - bo1;

    for (j=8;j;j--,b0+=0x10,window+=0x30)
    {
      real sum;
      sum  = *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;

      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
    }

    {
      real sum;
      sum  = window[0x0] * b0[0x0];
      sum += window[0x2] * b0[0x2];
      sum += window[0x4] * b0[0x4];
      sum += window[0x6] * b0[0x6];
      sum += window[0x8] * b0[0x8];
      sum += window[0xA] * b0[0xA];
      sum += window[0xC] * b0[0xC];
      sum += window[0xE] * b0[0xE];
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
      b0-=0x20,window-=0x40;
    }
    window += bo1<<1;

    for (j=7;j;j--,b0-=0x30,window-=0x30)
    {
      real sum;
      sum = -*(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;

      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
    }
  }

  *pnt += 64;

  return clip;
}

int synth_4to1_8bit(real *bandPtr,int channel,unsigned char *samples,int *pnt)
{
  short samples_tmp[16];
  short *tmp1 = samples_tmp + channel;
  int i,ret;
  int pnt1 = 0;

  ret = synth_4to1(bandPtr,channel,(unsigned char *) samples_tmp,&pnt1);
  samples += channel + *pnt;

  for(i=0;i<8;i++) {
    *samples = conv16to8[*tmp1>>AUSHIFT];
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 16;

  return ret;
}

int synth_4to1_8bit_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[16];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_4to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<8;i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += 8;

  return ret;
}


int synth_4to1_8bit_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[16];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_4to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<8;i++) {
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    *samples++ = conv16to8[*tmp1>>AUSHIFT];
    tmp1 += 2;
  }
  *pnt += 16;

  return ret;
}

int synth_4to1_mono(real *bandPtr,unsigned char *samples,int *pnt)
{
  short samples_tmp[16];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_4to1(bandPtr,0,(unsigned char *) samples_tmp,&pnt1);
  samples += *pnt;

  for(i=0;i<8;i++) {
    *( (short *)samples) = *tmp1;
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 16;

  return ret;
}

int synth_4to1_mono2stereo(real *bandPtr,unsigned char *samples,int *pnt)
{
  int i,ret;

  ret = synth_4to1(bandPtr,0,samples,pnt);
  samples = samples + *pnt - 32;

  for(i=0;i<8;i++) {
    ((short *)samples)[1] = ((short *)samples)[0];
    samples+=4;
  }

  return ret;
}

int synth_4to1(real *bandPtr,int channel,unsigned char *out,int *pnt)
{
  static real buffs[2][2][0x110];
  static const int step = 2;
  static int bo = 1;
  short *samples = (short *) (out + *pnt);

  real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;

  if(Args->UseEqualizer)
    do_equalizer(bandPtr,channel);

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = buffs[0];
  }
  else {
    samples++;
    buf = buffs[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }

  {
    register int j;
    real *window = decwin + 16 - bo1;

    for (j=4;j;j--,b0+=0x30,window+=0x70)
    {
      real sum;
      sum  = *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;

      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
      WRITE_SAMPLE(samples,sum,clip); samples += step;
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
    }

    {
      real sum;
      sum  = window[0x0] * b0[0x0];
      sum += window[0x2] * b0[0x2];
      sum += window[0x4] * b0[0x4];
      sum += window[0x6] * b0[0x6];
      sum += window[0x8] * b0[0x8];
      sum += window[0xA] * b0[0xA];
      sum += window[0xC] * b0[0xC];
      sum += window[0xE] * b0[0xE];
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
      WRITE_SAMPLE(samples,sum,clip); samples += step;
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
      b0-=0x40,window-=0x80;
    }
    window += bo1<<1;

    for (j=3;j;j--,b0-=0x50,window-=0x70)
    {
      real sum;
      sum = -*(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;

      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
      WRITE_SAMPLE(samples,sum,clip); samples += step;
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
    }
  }
  
  *pnt += 32;

  return clip;
}

static void dct64_1(real *out0,real *out1,real *b1,real *b2,real *samples)
{
    {
        register real *costab = pnts[0];
        b1[0x00] = samples[0x00] + samples[0x1F];
        b1[0x1F] = (samples[0x00] - samples[0x1F]) * costab[0x0];
        b1[0x01] = samples[0x01] + samples[0x1E];
        b1[0x1E] = (samples[0x01] - samples[0x1E]) * costab[0x1];
        b1[0x02] = samples[0x02] + samples[0x1D];
        b1[0x1D] = (samples[0x02] - samples[0x1D]) * costab[0x2];
        b1[0x03] = samples[0x03] + samples[0x1C];
        b1[0x1C] = (samples[0x03] - samples[0x1C]) * costab[0x3];
        b1[0x04] = samples[0x04] + samples[0x1B];
        b1[0x1B] = (samples[0x04] - samples[0x1B]) * costab[0x4];
        b1[0x05] = samples[0x05] + samples[0x1A];
        b1[0x1A] = (samples[0x05] - samples[0x1A]) * costab[0x5];
        b1[0x06] = samples[0x06] + samples[0x19];
        b1[0x19] = (samples[0x06] - samples[0x19]) * costab[0x6];
        b1[0x07] = samples[0x07] + samples[0x18];
        b1[0x18] = (samples[0x07] - samples[0x18]) * costab[0x7];
        b1[0x08] = samples[0x08] + samples[0x17];
        b1[0x17] = (samples[0x08] - samples[0x17]) * costab[0x8];
        b1[0x09] = samples[0x09] + samples[0x16];
        b1[0x16] = (samples[0x09] - samples[0x16]) * costab[0x9];
        b1[0x0A] = samples[0x0A] + samples[0x15];
        b1[0x15] = (samples[0x0A] - samples[0x15]) * costab[0xA];
        b1[0x0B] = samples[0x0B] + samples[0x14];
        b1[0x14] = (samples[0x0B] - samples[0x14]) * costab[0xB];
        b1[0x0C] = samples[0x0C] + samples[0x13];
        b1[0x13] = (samples[0x0C] - samples[0x13]) * costab[0xC];
        b1[0x0D] = samples[0x0D] + samples[0x12];
        b1[0x12] = (samples[0x0D] - samples[0x12]) * costab[0xD];
        b1[0x0E] = samples[0x0E] + samples[0x11];
        b1[0x11] = (samples[0x0E] - samples[0x11]) * costab[0xE];
        b1[0x0F] = samples[0x0F] + samples[0x10];
        b1[0x10] = (samples[0x0F] - samples[0x10]) * costab[0xF];
    }
    {
        register real *costab = pnts[1];
        b2[0x00] = b1[0x00] + b1[0x0F]; 
        b2[0x0F] = (b1[0x00] - b1[0x0F]) * costab[0];
        b2[0x01] = b1[0x01] + b1[0x0E]; 
        b2[0x0E] = (b1[0x01] - b1[0x0E]) * costab[1];
        b2[0x02] = b1[0x02] + b1[0x0D]; 
        b2[0x0D] = (b1[0x02] - b1[0x0D]) * costab[2];
        b2[0x03] = b1[0x03] + b1[0x0C]; 
        b2[0x0C] = (b1[0x03] - b1[0x0C]) * costab[3];
        b2[0x04] = b1[0x04] + b1[0x0B]; 
        b2[0x0B] = (b1[0x04] - b1[0x0B]) * costab[4];
        b2[0x05] = b1[0x05] + b1[0x0A]; 
        b2[0x0A] = (b1[0x05] - b1[0x0A]) * costab[5];
        b2[0x06] = b1[0x06] + b1[0x09]; 
        b2[0x09] = (b1[0x06] - b1[0x09]) * costab[6];
        b2[0x07] = b1[0x07] + b1[0x08]; 
        b2[0x08] = (b1[0x07] - b1[0x08]) * costab[7];
        b2[0x10] = b1[0x10] + b1[0x1F];
        b2[0x1F] = (b1[0x1F] - b1[0x10]) * costab[0];
        b2[0x11] = b1[0x11] + b1[0x1E];
        b2[0x1E] = (b1[0x1E] - b1[0x11]) * costab[1];
        b2[0x12] = b1[0x12] + b1[0x1D];
        b2[0x1D] = (b1[0x1D] - b1[0x12]) * costab[2];
        b2[0x13] = b1[0x13] + b1[0x1C];
        b2[0x1C] = (b1[0x1C] - b1[0x13]) * costab[3];
        b2[0x14] = b1[0x14] + b1[0x1B];
        b2[0x1B] = (b1[0x1B] - b1[0x14]) * costab[4];
        b2[0x15] = b1[0x15] + b1[0x1A];
        b2[0x1A] = (b1[0x1A] - b1[0x15]) * costab[5];
        b2[0x16] = b1[0x16] + b1[0x19];
        b2[0x19] = (b1[0x19] - b1[0x16]) * costab[6];
        b2[0x17] = b1[0x17] + b1[0x18];
        b2[0x18] = (b1[0x18] - b1[0x17]) * costab[7];
    }
    {
        register real *costab = pnts[2];
        b1[0x00] = b2[0x00] + b2[0x07];
        b1[0x07] = (b2[0x00] - b2[0x07]) * costab[0];
        b1[0x01] = b2[0x01] + b2[0x06];
        b1[0x06] = (b2[0x01] - b2[0x06]) * costab[1];
        b1[0x02] = b2[0x02] + b2[0x05];
        b1[0x05] = (b2[0x02] - b2[0x05]) * costab[2];
        b1[0x03] = b2[0x03] + b2[0x04];
        b1[0x04] = (b2[0x03] - b2[0x04]) * costab[3];
        b1[0x08] = b2[0x08] + b2[0x0F];
        b1[0x0F] = (b2[0x0F] - b2[0x08]) * costab[0];
        b1[0x09] = b2[0x09] + b2[0x0E];
        b1[0x0E] = (b2[0x0E] - b2[0x09]) * costab[1];
        b1[0x0A] = b2[0x0A] + b2[0x0D];
        b1[0x0D] = (b2[0x0D] - b2[0x0A]) * costab[2];
        b1[0x0B] = b2[0x0B] + b2[0x0C];
        b1[0x0C] = (b2[0x0C] - b2[0x0B]) * costab[3];
        b1[0x10] = b2[0x10] + b2[0x17];
        b1[0x17] = (b2[0x10] - b2[0x17]) * costab[0];
        b1[0x11] = b2[0x11] + b2[0x16];
        b1[0x16] = (b2[0x11] - b2[0x16]) * costab[1];
        b1[0x12] = b2[0x12] + b2[0x15];
        b1[0x15] = (b2[0x12] - b2[0x15]) * costab[2];
        b1[0x13] = b2[0x13] + b2[0x14];
        b1[0x14] = (b2[0x13] - b2[0x14]) * costab[3];
        b1[0x18] = b2[0x18] + b2[0x1F];
        b1[0x1F] = (b2[0x1F] - b2[0x18]) * costab[0];
        b1[0x19] = b2[0x19] + b2[0x1E];
        b1[0x1E] = (b2[0x1E] - b2[0x19]) * costab[1];
        b1[0x1A] = b2[0x1A] + b2[0x1D];
        b1[0x1D] = (b2[0x1D] - b2[0x1A]) * costab[2];
        b1[0x1B] = b2[0x1B] + b2[0x1C];
        b1[0x1C] = (b2[0x1C] - b2[0x1B]) * costab[3];
    }
    {
        register real const cos0 = pnts[3][0];
        register real const cos1 = pnts[3][1];
        b2[0x00] = b1[0x00] + b1[0x03];
        b2[0x03] = (b1[0x00] - b1[0x03]) * cos0;
        b2[0x01] = b1[0x01] + b1[0x02];
        b2[0x02] = (b1[0x01] - b1[0x02]) * cos1;
        b2[0x04] = b1[0x04] + b1[0x07];
        b2[0x07] = (b1[0x07] - b1[0x04]) * cos0;
        b2[0x05] = b1[0x05] + b1[0x06];
        b2[0x06] = (b1[0x06] - b1[0x05]) * cos1;
        b2[0x08] = b1[0x08] + b1[0x0B];
        b2[0x0B] = (b1[0x08] - b1[0x0B]) * cos0;
        b2[0x09] = b1[0x09] + b1[0x0A];
        b2[0x0A] = (b1[0x09] - b1[0x0A]) * cos1;
        b2[0x0C] = b1[0x0C] + b1[0x0F];
        b2[0x0F] = (b1[0x0F] - b1[0x0C]) * cos0;
        b2[0x0D] = b1[0x0D] + b1[0x0E];
        b2[0x0E] = (b1[0x0E] - b1[0x0D]) * cos1;
        b2[0x10] = b1[0x10] + b1[0x13];
        b2[0x13] = (b1[0x10] - b1[0x13]) * cos0;
        b2[0x11] = b1[0x11] + b1[0x12];
        b2[0x12] = (b1[0x11] - b1[0x12]) * cos1;
        b2[0x14] = b1[0x14] + b1[0x17];
        b2[0x17] = (b1[0x17] - b1[0x14]) * cos0;
        b2[0x15] = b1[0x15] + b1[0x16];
        b2[0x16] = (b1[0x16] - b1[0x15]) * cos1;
        b2[0x18] = b1[0x18] + b1[0x1B];
        b2[0x1B] = (b1[0x18] - b1[0x1B]) * cos0;
        b2[0x19] = b1[0x19] + b1[0x1A];
        b2[0x1A] = (b1[0x19] - b1[0x1A]) * cos1;
        b2[0x1C] = b1[0x1C] + b1[0x1F];
        b2[0x1F] = (b1[0x1F] - b1[0x1C]) * cos0;
        b2[0x1D] = b1[0x1D] + b1[0x1E];
        b2[0x1E] = (b1[0x1E] - b1[0x1D]) * cos1;
    }
    {
        register real const cos0 = pnts[4][0];
        b1[0x00] = b2[0x00] + b2[0x01];
        b1[0x01] = (b2[0x00] - b2[0x01]) * cos0;
        b1[0x02] = b2[0x02] + b2[0x03];
        b1[0x03] = (b2[0x03] - b2[0x02]) * cos0;
        b1[0x02] += b1[0x03];
        b1[0x04] = b2[0x04] + b2[0x05];
        b1[0x05] = (b2[0x04] - b2[0x05]) * cos0;
        b1[0x06] = b2[0x06] + b2[0x07];
        b1[0x07] = (b2[0x07] - b2[0x06]) * cos0;
        b1[0x06] += b1[0x07];
        b1[0x04] += b1[0x06];
        b1[0x06] += b1[0x05];
        b1[0x05] += b1[0x07];
        b1[0x08] = b2[0x08] + b2[0x09];
        b1[0x09] = (b2[0x08] - b2[0x09]) * cos0;
        b1[0x0A] = b2[0x0A] + b2[0x0B];
        b1[0x0B] = (b2[0x0B] - b2[0x0A]) * cos0;
        b1[0x0A] += b1[0x0B];
        b1[0x0C] = b2[0x0C] + b2[0x0D];
        b1[0x0D] = (b2[0x0C] - b2[0x0D]) * cos0;
        b1[0x0E] = b2[0x0E] + b2[0x0F];
        b1[0x0F] = (b2[0x0F] - b2[0x0E]) * cos0;
        b1[0x0E] += b1[0x0F];
        b1[0x0C] += b1[0x0E];
        b1[0x0E] += b1[0x0D];
        b1[0x0D] += b1[0x0F];
        b1[0x10] = b2[0x10] + b2[0x11];
        b1[0x11] = (b2[0x10] - b2[0x11]) * cos0;
        b1[0x12] = b2[0x12] + b2[0x13];
        b1[0x13] = (b2[0x13] - b2[0x12]) * cos0;
        b1[0x12] += b1[0x13];
        b1[0x14] = b2[0x14] + b2[0x15];
        b1[0x15] = (b2[0x14] - b2[0x15]) * cos0;
        b1[0x16] = b2[0x16] + b2[0x17];
        b1[0x17] = (b2[0x17] - b2[0x16]) * cos0;
        b1[0x16] += b1[0x17];
        b1[0x14] += b1[0x16];
        b1[0x16] += b1[0x15];
        b1[0x15] += b1[0x17];
        b1[0x18] = b2[0x18] + b2[0x19];
        b1[0x19] = (b2[0x18] - b2[0x19]) * cos0;
        b1[0x1A] = b2[0x1A] + b2[0x1B];
        b1[0x1B] = (b2[0x1B] - b2[0x1A]) * cos0;
        b1[0x1A] += b1[0x1B];
        b1[0x1C] = b2[0x1C] + b2[0x1D];
        b1[0x1D] = (b2[0x1C] - b2[0x1D]) * cos0;
        b1[0x1E] = b2[0x1E] + b2[0x1F];
        b1[0x1F] = (b2[0x1F] - b2[0x1E]) * cos0;
        b1[0x1E] += b1[0x1F];
        b1[0x1C] += b1[0x1E];
        b1[0x1E] += b1[0x1D];
        b1[0x1D] += b1[0x1F];
    }
    out0[0x10*16] = b1[0x00];
    out0[0x10*12] = b1[0x04];
    out0[0x10* 8] = b1[0x02];
    out0[0x10* 4] = b1[0x06];
    out0[0x10* 0] = b1[0x01];
    out1[0x10* 0] = b1[0x01];
    out1[0x10* 4] = b1[0x05];
    out1[0x10* 8] = b1[0x03];
    out1[0x10*12] = b1[0x07];
    b1[0x08] += b1[0x0C];
    out0[0x10*14] = b1[0x08];
    b1[0x0C] += b1[0x0a];
    out0[0x10*10] = b1[0x0C];
    b1[0x0A] += b1[0x0E];
    out0[0x10* 6] = b1[0x0A];
    b1[0x0E] += b1[0x09];
    out0[0x10* 2] = b1[0x0E];
    b1[0x09] += b1[0x0D];
    out1[0x10* 2] = b1[0x09];
    b1[0x0D] += b1[0x0B];
    out1[0x10* 6] = b1[0x0D];
    b1[0x0B] += b1[0x0F];
    out1[0x10*10] = b1[0x0B];
    out1[0x10*14] = b1[0x0F];
    b1[0x18] += b1[0x1C];
    out0[0x10*15] = b1[0x10] + b1[0x18];
    out0[0x10*13] = b1[0x18] + b1[0x14];
    b1[0x1C] += b1[0x1a];
    out0[0x10*11] = b1[0x14] + b1[0x1C];
    out0[0x10* 9] = b1[0x1C] + b1[0x12];
    b1[0x1A] += b1[0x1E];
    out0[0x10* 7] = b1[0x12] + b1[0x1A];
    out0[0x10* 5] = b1[0x1A] + b1[0x16];
    b1[0x1E] += b1[0x19];
    out0[0x10* 3] = b1[0x16] + b1[0x1E];
    out0[0x10* 1] = b1[0x1E] + b1[0x11];
    b1[0x19] += b1[0x1D];
    out1[0x10* 1] = b1[0x11] + b1[0x19];
    out1[0x10* 3] = b1[0x19] + b1[0x15];
    b1[0x1D] += b1[0x1B];
    out1[0x10* 5] = b1[0x15] + b1[0x1D];
    out1[0x10* 7] = b1[0x1D] + b1[0x13];
    b1[0x1B] += b1[0x1F];
    out1[0x10* 9] = b1[0x13] + b1[0x1B];
    out1[0x10*11] = b1[0x1B] + b1[0x17];
    out1[0x10*13] = b1[0x17] + b1[0x1F];
    out1[0x10*15] = b1[0x1F];
}

void dct64(real *a,real *b,real *c)
{
    real bufs[0x40];
    dct64_1(a,b,bufs,bufs+0x20,c);
}

bool Done_MPEGDecoder() {
    if (pcm_sample) 
    {
        GlobalFree(pcm_sample);
        pcm_sample = NULL;
    }
    Decoder_Initialized = false;
    return true;
}

bool Init_MPEGDecoder(int down_samp)
{
    if (pcm_sample) GlobalFree(pcm_sample);
    pcm_sample = (unsigned char *) GlobalAlloc(GMEM_FIXED, Args->BufferSize + 1000);
    if (!pcm_sample) throw 1;
    ZeroMemory(pcm_sample,  Args->BufferSize + 1000);
    pcm_point = 0;
    conv16to8 = conv16to8_buf + 2048;
    
    int i;

    ntom_val[0] = NTOM_MUL>>1;
    ntom_val[1] = NTOM_MUL>>1;
    ntom_step = NTOM_MUL;

    memset(grp_3tab, 0, 32*3);
    memset(grp_5tab, 0, 128*3);
    memset(grp_9tab, 0, 1024*3);
    
    pnts[0] = cos64;
    pnts[1] = cos32;
    pnts[2] = cos16;
    pnts[3] = cos8;
    pnts[4] = cos4;


    init_layer3(down_samp);
    
    InitMoreTables();
    Decoder_Initialized = true;
    return true;
}

void InitMoreTables(void){
    static double mulmul[27] = {
        0.0 , -2.0/3.0 , 2.0/3.0 ,
            2.0/7.0 , 2.0/15.0 , 2.0/31.0, 2.0/63.0 , 2.0/127.0 , 2.0/255.0 ,
            2.0/511.0 , 2.0/1023.0 , 2.0/2047.0 , 2.0/4095.0 , 2.0/8191.0 ,
            2.0/16383.0 , 2.0/32767.0 , 2.0/65535.0 ,
            -4.0/5.0 , -2.0/5.0 , 2.0/5.0, 4.0/5.0 ,
            -8.0/9.0 , -4.0/9.0 , -2.0/9.0 , 2.0/9.0 , 4.0/9.0 , 8.0/9.0 };
        static int base[3][9] = {
            { 1 , 0, 2 , } ,
            { 17, 18, 0 , 19, 20 , } ,
            { 21, 1, 22, 23, 0, 24, 25, 2, 26 } };
            int i,j,k,l,len;
            real *table;
            static int tablen[3] = { 3 , 5 , 9 };
            static int *itable;
            
            static int *tables[3] = { grp_3tab , grp_5tab , grp_9tab };
            
            for(i=0;i<3;i++){
                itable = tables[i];
                len = tablen[i];
                for(j=0;j<len;j++)
                    for(k=0;k<len;k++)
                        for(l=0;l<len;l++){
                            *itable++ = base[i][l];
                            *itable++ = base[i][k];
                            *itable++ = base[i][j];
                        }
            }
            
            for(k=0;k<27;k++){
                double m=mulmul[k];
                table = muls[k];
                for(j=3,i=0;i<63;i++,j--)
                    *table++ = m * pow(2.0,(double) j / 3.0);
                *table++ = 0.0;
            }
}

int do_layer1()
{
    int clip=0;
    int i,stereo = fr.stereo;
    unsigned int balloc[2*SBLIMIT];
    unsigned int scale_index[2][SBLIMIT];
    real fraction[2][SBLIMIT];
    int single = fr.single;
    
    if(stereo==1||single==3) single = 0;
    I_step_one(balloc,scale_index);
    for (i=0;i<SCALE_BLOCK;i++)
    {
        I_step_two(fraction,balloc,scale_index);
        
        if(single >= 0) {
            clip += (fr.synth_mono)((real *)fraction[single],pcm_sample, &pcm_point);
        }
        else {
            int p1 = pcm_point;
            clip += (fr.synth)((real *)fraction[0],0,pcm_sample, &p1);
            clip += (fr.synth)((real *)fraction[1],1,pcm_sample, &pcm_point);
        }
        //pcm_point += fr.block_size;
        
        if(pcm_point >= Args->BufferSize) AudioFlush();
    }
    return clip;
}

int do_layer2(){
    int clip=0;
    int i,j;
    int stereo = fr.stereo;
    real fraction[2][4][SBLIMIT]; /* pick_table clears unused subbands */
    unsigned int bit_alloc[64];
    int scale[192];
    int single = fr.single;
    
    if(stereo == 1 || single == 3) single = 0;
    
    II_step_one(bit_alloc, scale);
    
    for (i=0;i<SCALE_BLOCK;i++) {
        II_step_two(bit_alloc,fraction,scale,i>>2);
        for (j=0;j<3;j++) {
            if(single >= 0){
                clip += (fr.synth_mono)(fraction[single][j],pcm_sample, &pcm_point);
            }
            else {
                int p1 = pcm_point;
                clip += (fr.synth)( fraction[0][j],0,pcm_sample, &p1);
                clip += (fr.synth)( fraction[1][j],1,pcm_sample, &pcm_point);
            }
            //pcm_point += fr.block_size;
            if(pcm_point >= Args->BufferSize) AudioFlush();
        }
    }
    return clip;
}

int do_layer3() 
{
    int gr, ch, ss,clip=0;
    int scalefacs[2][39]; /* max 39 for short[13][3] mode, mixed: 38, long: 22 */
    struct III_sideinfo sideinfo;
    int stereo = fr.stereo;
    int single = fr.single;
    int ms_stereo,i_stereo;
    int sfreq = fr.sampling_frequency;
    int stereo1,granules;
    
    if(stereo == 1) {
        stereo1 = 1;
        single = 0;
    }
    else if (single >= 0)
        stereo1 = 1;
    else
        stereo1 = 2;
    
    if(fr.mode == MPG_MD_JOINT_STEREO) {
        ms_stereo = fr.mode_ext & 0x2;
        i_stereo  = fr.mode_ext & 0x1;
    }
    else
        ms_stereo = i_stereo = 0;
    
    
    if(fr.lsf) {
        granules = 1;
        III_get_side_info_2(&sideinfo,stereo,ms_stereo,sfreq,single);
    }
    else {
        granules = 2;
        III_get_side_info_1(&sideinfo,stereo,ms_stereo,sfreq,single);
    }
    
    SetPointer(sideinfo.main_data_begin);
    
    for (gr=0;gr<granules;gr++)  {
        static real hybridIn[2][SBLIMIT][SSLIMIT];
        static real hybridOut[2][SSLIMIT][SBLIMIT];
        
        {
            struct gr_info_s *gr_info = &(sideinfo.ch[0].gr[gr]);
            long part2bits;
            if(fr.lsf)
                part2bits = III_get_scale_factors_2(scalefacs[0],gr_info,0);
            else
                part2bits = III_get_scale_factors_1(scalefacs[0],gr_info);
            if(III_dequantize_sample(hybridIn[0], scalefacs[0],gr_info,sfreq,part2bits))
                return clip;
        }
        if(stereo == 2) 
        {
            struct gr_info_s *gr_info = &(sideinfo.ch[1].gr[gr]);
            long part2bits;
            if(fr.lsf) 
                part2bits = III_get_scale_factors_2(scalefacs[1],gr_info,i_stereo);
            else
                part2bits = III_get_scale_factors_1(scalefacs[1],gr_info);
            if(ms_stereo) {
                if(III_dequantize_sample_ms(hybridIn,scalefacs[1],gr_info,sfreq,part2bits))
                    return clip;
            }
            else {
                if(III_dequantize_sample(hybridIn[1],scalefacs[1],gr_info,sfreq,part2bits))
                    return clip;
            }
            
            if(i_stereo)
                III_i_stereo(hybridIn,scalefacs[1],gr_info,sfreq,ms_stereo,fr.lsf);
            
            
            if(ms_stereo || i_stereo || (single == 3) ) {
                if(gr_info->maxb > sideinfo.ch[0].gr[gr].maxb) 
                    sideinfo.ch[0].gr[gr].maxb = gr_info->maxb;
                else
                    gr_info->maxb = sideinfo.ch[0].gr[gr].maxb;
            }
            
            switch(single) {
            case 3:
                {
                    register unsigned long i;
                    register real *in0 = (real *) hybridIn[0],*in1 = (real *) hybridIn[1];
                    for(i=0;i<SSLIMIT*gr_info->maxb;i++,in0++)
                        *in0 = (*in0 + *in1++); /* *0.5 done by pow-scale */ 
                }
                break;
            case 1:
                {
                    register unsigned long i;
                    register real *in0 = (real *) hybridIn[0],*in1 = (real *) hybridIn[1];
                    for(i=0;i<SSLIMIT*gr_info->maxb;i++)
                        *in0++ = *in1++;
                }
                break;
            }
        }
        
        for(ch=0;ch<stereo1;ch++) {
            struct gr_info_s *gr_info = &(sideinfo.ch[ch].gr[gr]);
            III_antialias(hybridIn[ch],gr_info);
            III_hybrid(hybridIn[ch], hybridOut[ch], ch,gr_info);
        }
        
        for(ss=0;ss<SSLIMIT;ss++) {
            if(single >= 0) {
                clip += (fr.synth_mono)( hybridOut[0][ss], pcm_sample, &pcm_point);
                SubbandAnalyser[ss] = *hybridOut[0][ss];
            }
            else {
                int p1 = pcm_point;
                clip += (fr.synth)(hybridOut[0][ss],0, pcm_sample, &p1);
                clip += (fr.synth)(hybridOut[1][ss],1, pcm_sample, &pcm_point);
                SubbandAnalyser[ss] = *hybridOut[0][ss];
            }
            //pcm_point += fr.block_size;
            if (pcm_point >= Args->BufferSize) AudioFlush();
        }
    }
    return clip;
}

static int III_get_scale_factors_1(int *scf,struct gr_info_s *gr_info)
{
    static unsigned char slen[2][16] = {
        {0, 0, 0, 0, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4},
        {0, 1, 2, 3, 0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 2, 3}
    };
    int numbits;
    int num0 = slen[0][gr_info->scalefac_compress];
    int num1 = slen[1][gr_info->scalefac_compress];
    
    if (gr_info->block_type == 2) {
        int i=18;
        numbits = (num0 + num1) * 18;
        
        if (gr_info->mixed_block_flag) {
            for (i=8;i;i--)
                *scf++ = GetBitsFast(num0);
            i = 9;
            numbits -= num0; /* num0 * 17 + num1 * 18 */
        }
        
        for (;i;i--)
            *scf++ = GetBitsFast(num0);
        for (i = 18; i; i--)
            *scf++ = GetBitsFast(num1);
        *scf++ = 0; *scf++ = 0; *scf++ = 0; /* short[13][0..2] = 0 */
    }
    else {
        int i;
        int scfsi = gr_info->scfsi;
        
        if(scfsi < 0) { /* scfsi < 0 => granule == 0 */
            for(i=11;i;i--)
                *scf++ = GetBitsFast(num0);
            for(i=10;i;i--)
                *scf++ = GetBitsFast(num1);
            numbits = (num0 + num1) * 10 + num0;
            *scf++ = 0;
        }
        else {
            numbits = 0;
            if(!(scfsi & 0x8)) {
                for (i=0;i<6;i++)
                    *scf++ = GetBitsFast(num0);
                numbits += num0 * 6;
            }
            else {
                scf += 6; 
            }
            
            if(!(scfsi & 0x4)) {
                for (i=0;i<5;i++)
                    *scf++ = GetBitsFast(num0);
                numbits += num0 * 5;
            }
            else {
                scf += 5;
            }
            
            if(!(scfsi & 0x2)) {
                for(i=0;i<5;i++)
                    *scf++ = GetBitsFast(num1);
                numbits += num1 * 5;
            }
            else {
                scf += 5; 
            }
            
            if(!(scfsi & 0x1)) {
                for (i=0;i<5;i++)
                    *scf++ = GetBitsFast(num1);
                numbits += num1 * 5;
            }
            else {
                scf += 5;
            }
            *scf++ = 0;  /* no l[21] in original sources */
        }
    }
    return numbits;
}

static int III_get_scale_factors_2(int *scf,struct gr_info_s *gr_info,int i_stereo)
{
    unsigned char *pnt;
    int i,j,n=0,numbits=0;
    unsigned int slen;
    
    static unsigned char stab[3][6][4] = {
        { { 6, 5, 5,5 } , { 6, 5, 7,3 } , { 11,10,0,0} ,
        { 7, 7, 7,0 } , { 6, 6, 6,3 } , {  8, 8,5,0} } ,
        { { 9, 9, 9,9 } , { 9, 9,12,6 } , { 18,18,0,0} ,
        {12,12,12,0 } , {12, 9, 9,6 } , { 15,12,9,0} } ,
        { { 6, 9, 9,9 } , { 6, 9,12,6 } , { 15,18,0,0} ,
        { 6,15,12,0 } , { 6,12, 9,6 } , {  6,18,9,0} } }; 
        
        if(i_stereo) /* i_stereo AND second channel -> do_layer3() checks this */
            slen = i_slen2[gr_info->scalefac_compress>>1];
        else
            slen = n_slen2[gr_info->scalefac_compress];
        
        gr_info->preflag = (slen>>15) & 0x1;
        
        n = 0;  
        if( gr_info->block_type == 2 ) {
            n++;
            if(gr_info->mixed_block_flag)
                n++;
        }
        
        pnt = stab[n][(slen>>12)&0x7];
        
        for(i=0;i<4;i++) {
            int num = slen & 0x7;
            slen >>= 3;
            if(num) {
                for(j=0;j<(int)(pnt[i]);j++)
                    *scf++ = GetBitsFast(num);
                numbits += pnt[i] * num;
            }
            else {
                for(j=0;j<(int)(pnt[i]);j++)
                    *scf++ = 0;
            }
        }
        
        n = (n << 1) + 1;
        for(i=0;i<n;i++)
            *scf++ = 0;
        
        return numbits;
}

void init_layer3(int down_samp)
{
    int i,j,k,l;
    
    for(i=-256;i<118+4;i++) gainpow2[i+256] = pow((double)2.0,-0.25 * (double) (i+210) );
    
    for(i=0;i<8207;i++) ispow[i] = pow((double)i,(double)4.0/3.0);

    for (i=0;i<8;i++) {
        static double Ci[8]={-0.6,-0.535,-0.33,-0.185,-0.095,-0.041,-0.0142,-0.0037};
        double sq=sqrt(1.0+Ci[i]*Ci[i]);
        aa_cs[i] = 1.0/sq;
        aa_ca[i] = Ci[i]/sq;
    }
    for(i=0;i<18;i++) 
    {
        win[0][i]    = win[1][i]    = 0.5 * sin( M_PI / 72.0 * (double) (2*(i+0) +1) ) / cos ( M_PI * (double) (2*(i+0) +19) / 72.0 );
        win[0][i+18] = win[3][i+18] = 0.5 * sin( M_PI / 72.0 * (double) (2*(i+18)+1) ) / cos ( M_PI * (double) (2*(i+18)+19) / 72.0 );
    }
    for(i=0;i<6;i++) 
    {
        win[1][i+18] = 0.5 / cos ( M_PI * (double) (2*(i+18)+19) / 72.0 );
        win[3][i+12] = 0.5 / cos ( M_PI * (double) (2*(i+12)+19) / 72.0 );
        win[1][i+24] = 0.5 * sin( M_PI / 24.0 * (double) (2*i+13) ) / cos ( M_PI * (double) (2*(i+24)+19) / 72.0 );
        win[1][i+30] = win[3][i] = 0.0;
        win[3][i+6 ] = 0.5 * sin( M_PI / 24.0 * (double) (2*i+1) )  / cos ( M_PI * (double) (2*(i+6 )+19) / 72.0 );
    }
    for(i=0;i<9;i++) COS9[i] = cos( M_PI / 18.0 * (double) i);
    for(i=0;i<9;i++) tfcos36[i] = 0.5 / cos ( M_PI * (double) (i*2+1) / 36.0 );
    for(i=0;i<3;i++) tfcos12[i] = 0.5 / cos ( M_PI * (double) (i*2+1) / 12.0 );
    COS6_1 = cos( M_PI / 6.0 * (double) 1);
    COS6_2 = cos( M_PI / 6.0 * (double) 2);
#ifdef NEW_DCT9
    cos9[0] = cos(1.0*M_PI/9.0);
    cos9[1] = cos(5.0*M_PI/9.0);
    cos9[2] = cos(7.0*M_PI/9.0);
    cos18[0] = cos(1.0*M_PI/18.0);
    cos18[1] = cos(11.0*M_PI/18.0);
    cos18[2] = cos(13.0*M_PI/18.0);
#endif
    for(i=0;i<12;i++) {
        win[2][i]  = 0.5 * sin( M_PI / 24.0 * (double) (2*i+1) ) / cos ( M_PI * (double) (2*i+7) / 24.0 );
        for(j=0;j<6;j++) COS1[i][j] = cos( M_PI / 24.0 * (double) ((2*i+7)*(2*j+1)) );
    }
    for(j=0;j<4;j++) {
        static int len[4] = { 36,36,12,36 };
        for(i=0;i<len[j];i+=2) win1[j][i] = + win[j][i];
        for(i=1;i<len[j];i+=2) win1[j][i] = - win[j][i];
    }
    for(i=0;i<16;i++) {
        double t = tan( (double) i * M_PI / 12.0 );
        tan1_1[i] = t / (1.0+t);
        tan2_1[i] = 1.0 / (1.0 + t);
        tan1_2[i] = M_SQRT2 * t / (1.0+t);
        tan2_2[i] = M_SQRT2 / (1.0 + t);
        for(j=0;j<2;j++) {
            double base = pow(2.0,-0.25*(j+1.0));
            double p1=1.0,p2=1.0;
            if(i > 0) {
                if(i&1) p1 = pow(base,(i+1.0)*0.5);
                else p2 = pow(base,i*0.5);
            }
            pow1_1[j][i] = p1;
            pow2_1[j][i] = p2;
            pow1_2[j][i] = M_SQRT2 * p1;
            pow2_2[j][i] = M_SQRT2 * p2;
        }
    }
    for(j=0;j<9;j++) {
        struct bandInfoStruct *bi = (struct bandInfoStruct *) &bandInfo[j];
        int *mp;
        int cb,lwin;
        int* bdf;
        mp = map[j][0] = mapbuf0[j];
        bdf = bi->longDiff;
        for(i=0, cb = 0; cb < 8 ; cb++, i+= *bdf++){
            *mp++ = (*bdf) >> 1;
            *mp++ = i;
            *mp++ = 3;
            *mp++ = cb;
        }
        bdf = bi->shortDiff+3;
        for(cb=3;cb<13;cb++) {
            int l = (*bdf++) >> 1;
            for(lwin=0;lwin<3;lwin++) {
                *mp++ = l;
                *mp++ = i + lwin;
                *mp++ = lwin;
                *mp++ = cb;
            }
            i += 6*l;
        }
        mapend[j][0] = mp;
        mp = map[j][1] = mapbuf1[j];
        bdf = bi->shortDiff+0;
        for(i=0,cb=0;cb<13;cb++) {
            int l = (*bdf++) >> 1;
            for(lwin=0;lwin<3;lwin++) {
                *mp++ = l;
                *mp++ = i + lwin;
                *mp++ = lwin;
                *mp++ = cb;
            }
            i += 6*l;
        }
        mapend[j][1] = mp;
        mp = map[j][2] = mapbuf2[j];
        bdf = bi->longDiff;
        for(cb = 0; cb < 22 ; cb++) {
            *mp++ = (*bdf++) >> 1;
            *mp++ = cb;
        }
        mapend[j][2] = mp;
    }
    for(j=0;j<9;j++) {
        for(i=0;i<23;i++) {
            longLimit[j][i]=(bandInfo[j].longIdx[i]-1+8)/18+1;
            if(longLimit[j][i]>(SBLIMIT>>down_samp)) longLimit[j][i]=SBLIMIT>>down_samp;
        }
        for(i=0;i<14;i++) {
            shortLimit[j][i]=(bandInfo[j].shortIdx[i]-1)/18+1;
            if(shortLimit[j][i]>(SBLIMIT>>down_samp)) shortLimit[j][i]=SBLIMIT>>down_samp;
        }
    }
    for(i=0;i<5;i++) {
        for(j=0;j<6;j++) {
            for(k=0;k<6;k++) {
                int n = k + j * 6 + i * 36;
                i_slen2[n] = i|(j<<3)|(k<<6)|(3<<12);
            }
        }
    }
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            for(k=0;k<4;k++) {
                int n = k + j * 4 + i * 16;
                i_slen2[n+180] = i|(j<<3)|(k<<6)|(4<<12);
            }
        }
    }
    for(i=0;i<4;i++) {
        for(j=0;j<3;j++) {
            int n = j + i * 3;
            i_slen2[n+244] = i|(j<<3) | (5<<12);
            n_slen2[n+500] = i|(j<<3) | (2<<12) | (1<<15);
        }
    }
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            for(k=0;k<4;k++) {
                for(l=0;l<4;l++) {
                    int n = l + k * 4 + j * 16 + i * 80;
                    n_slen2[n] = i|(j<<3)|(k<<6)|(l<<9)|(0<<12);
                }
            }
        }
    }
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            for(k=0;k<4;k++) {
                int n = k + j * 4 + i * 20;
                n_slen2[n+400] = i|(j<<3)|(k<<6)|(1<<12);
            }
        }
    }
}
