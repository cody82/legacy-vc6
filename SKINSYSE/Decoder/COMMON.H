#ifndef COMMON_H 
#define COMMON_H 

#define real double
#define NEW_DCT9
#define M_PI    3.14159265358979323846
#define M_SQRT2 1.41421356237309504880
#define SBLIMIT                 32
#define SCALE_BLOCK             12
#define SSLIMIT                 18

struct ID3TagStruct {
    char TagHeader[3];
    char Title[30];
    char Artist[30];
    char Album[30];
    char Year[4];
    char Comment[30];
    unsigned char Genre;
};

struct gr_info_s {
      int scfsi;
      unsigned part2_3_length;
      unsigned big_values;
      unsigned scalefac_compress;
      unsigned block_type;
      unsigned mixed_block_flag;
      unsigned table_select[3];
      unsigned subblock_gain[3];
      unsigned maxband[3];
      unsigned maxbandl;
      unsigned maxb;
      unsigned region1start;
      unsigned region2start;
      unsigned preflag;
      unsigned scalefac_scale;
      unsigned count1table_select;
      real *full_gain[3];
      real *pow2gain;
};

struct bandInfoStruct {
  int longIdx[23];
  int longDiff[22];
  int shortIdx[14];
  int shortDiff[13];
};

struct III_sideinfo
{
  unsigned main_data_begin;
  unsigned private_bits;
  struct {
    struct gr_info_s gr[2];
  } ch[2];
};

#endif 
