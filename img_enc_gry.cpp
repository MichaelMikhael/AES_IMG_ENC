#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/video/tracking.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
//#include <opencv2/contrib/contrib.hpp>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "/home/prog/cryptopp820/aes.h"
#include <math.h>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <string>

using namespace cv;
using namespace std;

int arr_counter=0;

//string key = "Michael MiKhaelm";
//uint8_t key[16] = {0x4d,0x69,0x63,0x68,0x61,0x65,0x6c,0x20,0x4d,0x4d,0x69,0x6b,0x68,0x61,0x65,0x6c};
//string key[16] = {"0x4d","0x69","0x63","0x68","0x61","0x65","0x6c","0x20","0x4d","0x4d","0x69","0x6b","0x68","0x61","0x65","0x6c"};
string key[16] = {"0x54","0x68","0x61","0x74","0x73","0x20","0x6d","0x79","0x20","0x4b","0x75","0x6e","0x67","0x20","0x46","0x75"};
//string pt[16] = {"0x54","0x77","0x6f","0x20","0x4f","0x6e","0x65","0x20","0x4e","0x69","0x6e","0x65","0x20","0x54","0x77","0x6f"};
string pt[16] = {"0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00","0x00"};
string mix_col[4][4] = {"0x02","0x01","0x01","0x03","0x03","0x02","0x01","0x01","0x01","0x03","0x02","0x01","0x01","0x01","0x03","0x02"};



//string round_const[10] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a};
//string round_const[10] = {"0x01","0x02","0x03","0x04","0x05","0x06","0x07","0x08","0x09","0x0a"};
string round_const[10] = {"0x01","0x02","0x04","0x08","0x10","0x20","0x40","0x80","0x1b","0x36"};

//string ssss[1200];

string round0[10][16];
string round_fin[10][16];
string temp[4]; 
string l_shift[4];
string add_rc[10];
string sb[4];
string tmp_sb;
string tmp_rndcons;
int c=0,b0=0;

string tmp_mat[4][4];
string shift_row_mat[4][4];
string sr_fin[4][4];
int counter = 0;
string mct[16];

int rnd=0;
string tmp_rnd_key;
string tmp_rnd_xres;
string tmp_res;
string tmp_sb_sr;
string mix_col_mat[4][4];
string cypher_text[11][16];
string shift_row_fin[4][4];

int row=0,col=0;

int temp_c=0, temp_r=0;
string mul_temp[4],xor_temp;
int c1=0,r1=0,nxt_cl=0;
int mcm_cntr_c = 0, mcm_cntr_r = 0, srm_cntr_c = 0, srm_cntr_r = 0, colm=0, mcntr=0;

string a2;
int rct=0;
string tk[4][4];


string int2hex_plaintext(int i)
{
    
    stringstream h;
    h << std::hex <<i;
    string hex_val(h.str());

    return hex_val;
    //return h;
}



string sbox(string ip)
{
 uint8_t sbox_val;

 istringstream ss(ip);
 unsigned long tempval;
 ss >> hex >> tempval;

 bitset<8> b(tempval);
 bitset<4> bR = ((b >> 4).to_ulong());
 bitset<4> bC = ((b & b).to_ulong());

 int row = (int)(bR.to_ulong());
 int col = (int)(bC.to_ulong());
 
 static const uint8_t s_box[16][16]=
 {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
 };
 
 sbox_val = s_box[row][col];

 
 return int2hex_plaintext(sbox_val);
 //return tempval;
}

string mulBy2(string ip)
{
 uint8_t sbox_val;

 istringstream ss(ip);
 unsigned long tempval;
 ss >> hex >> tempval;

 bitset<8> b(tempval);
 bitset<4> bR = ((b >> 4).to_ulong());
 bitset<4> bC = ((b & b).to_ulong());

 int row = (int)(bR.to_ulong());
 int col = (int)(bC.to_ulong());
 
 static const uint8_t s_box[16][16]=
 {
 0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,
0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,
0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,
0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,
0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,
0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,
0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,
0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,
0x1b,0x19,0x1f,0x1d,0x13,0x11,0x17,0x15,0x0b,0x09,0x0f,0x0d,0x03,0x01,0x07,0x05,
0x3b,0x39,0x3f,0x3d,0x33,0x31,0x37,0x35,0x2b,0x29,0x2f,0x2d,0x23,0x21,0x27,0x25,
0x5b,0x59,0x5f,0x5d,0x53,0x51,0x57,0x55,0x4b,0x49,0x4f,0x4d,0x43,0x41,0x47,0x45,
0x7b,0x79,0x7f,0x7d,0x73,0x71,0x77,0x75,0x6b,0x69,0x6f,0x6d,0x63,0x61,0x67,0x65,
0x9b,0x99,0x9f,0x9d,0x93,0x91,0x97,0x95,0x8b,0x89,0x8f,0x8d,0x83,0x81,0x87,0x85,
0xbb,0xb9,0xbf,0xbd,0xb3,0xb1,0xb7,0xb5,0xab,0xa9,0xaf,0xad,0xa3,0xa1,0xa7,0xa5,
0xdb,0xd9,0xdf,0xdd,0xd3,0xd1,0xd7,0xd5,0xcb,0xc9,0xcf,0xcd,0xc3,0xc1,0xc7,0xc5,
0xfb,0xf9,0xff,0xfd,0xf3,0xf1,0xf7,0xf5,0xeb,0xe9,0xef,0xed,0xe3,0xe1,0xe7,0xe5
 };
 
 sbox_val = s_box[row][col];

 
 return int2hex_plaintext(sbox_val);
 //return tempval;
}

string mulBy3(string ip)
{
 uint8_t sbox_val;

 istringstream ss(ip);
 unsigned long tempval;
 ss >> hex >> tempval;

 bitset<8> b(tempval);
 bitset<4> bR = ((b >> 4).to_ulong());
 bitset<4> bC = ((b & b).to_ulong());

 int row = (int)(bR.to_ulong());
 int col = (int)(bC.to_ulong());
 
 static const uint8_t s_box[16][16]=
 {
 0x00,0x03,0x06,0x05,0x0c,0x0f,0x0a,0x09,0x18,0x1b,0x1e,0x1d,0x14,0x17,0x12,0x11,
0x30,0x33,0x36,0x35,0x3c,0x3f,0x3a,0x39,0x28,0x2b,0x2e,0x2d,0x24,0x27,0x22,0x21,
0x60,0x63,0x66,0x65,0x6c,0x6f,0x6a,0x69,0x78,0x7b,0x7e,0x7d,0x74,0x77,0x72,0x71,
0x50,0x53,0x56,0x55,0x5c,0x5f,0x5a,0x59,0x48,0x4b,0x4e,0x4d,0x44,0x47,0x42,0x41,
0xc0,0xc3,0xc6,0xc5,0xcc,0xcf,0xca,0xc9,0xd8,0xdb,0xde,0xdd,0xd4,0xd7,0xd2,0xd1,
0xf0,0xf3,0xf6,0xf5,0xfc,0xff,0xfa,0xf9,0xe8,0xeb,0xee,0xed,0xe4,0xe7,0xe2,0xe1,
0xa0,0xa3,0xa6,0xa5,0xac,0xaf,0xaa,0xa9,0xb8,0xbb,0xbe,0xbd,0xb4,0xb7,0xb2,0xb1,
0x90,0x93,0x96,0x95,0x9c,0x9f,0x9a,0x99,0x88,0x8b,0x8e,0x8d,0x84,0x87,0x82,0x81,
0x9b,0x98,0x9d,0x9e,0x97,0x94,0x91,0x92,0x83,0x80,0x85,0x86,0x8f,0x8c,0x89,0x8a,
0xab,0xa8,0xad,0xae,0xa7,0xa4,0xa1,0xa2,0xb3,0xb0,0xb5,0xb6,0xbf,0xbc,0xb9,0xba,
0xfb,0xf8,0xfd,0xfe,0xf7,0xf4,0xf1,0xf2,0xe3,0xe0,0xe5,0xe6,0xef,0xec,0xe9,0xea,
0xcb,0xc8,0xcd,0xce,0xc7,0xc4,0xc1,0xc2,0xd3,0xd0,0xd5,0xd6,0xdf,0xdc,0xd9,0xda,
0x5b,0x58,0x5d,0x5e,0x57,0x54,0x51,0x52,0x43,0x40,0x45,0x46,0x4f,0x4c,0x49,0x4a,
0x6b,0x68,0x6d,0x6e,0x67,0x64,0x61,0x62,0x73,0x70,0x75,0x76,0x7f,0x7c,0x79,0x7a,
0x3b,0x38,0x3d,0x3e,0x37,0x34,0x31,0x32,0x23,0x20,0x25,0x26,0x2f,0x2c,0x29,0x2a,
0x0b,0x08,0x0d,0x0e,0x07,0x04,0x01,0x02,0x13,0x10,0x15,0x16,0x1f,0x1c,0x19,0x1a
 };
 
 sbox_val = s_box[row][col];

 
 return int2hex_plaintext(sbox_val);
 //return tempval;
}

string arc(string wrd,string rc)
{
 istringstream ss(wrd);
 unsigned long res_w;
 ss >> hex >> res_w;

 istringstream ss0(rc);
 unsigned long res_rc;
 ss0 >> hex >> res_rc;

 unsigned long xor_res = res_rc ^ res_w ;

 return int2hex_plaintext(xor_res);
}

string xor_res(string wrd,string rc)
{
 istringstream ss(wrd);
 unsigned long res_w;
 ss >> hex >> res_w;

 istringstream ss0(rc);
 unsigned long res_rc;
 ss0 >> hex >> res_rc;

 unsigned long xor_res = res_rc ^ res_w ;

 return int2hex_plaintext(xor_res);
}

string xor_res4i(string i1,string i2, string i3, string i4)
{
 istringstream ss(i1);
 unsigned long res_i1;
 ss >> hex >> res_i1;

 istringstream ss0(i2);
 unsigned long res_i2;
 ss0 >> hex >> res_i2;

 istringstream ss1(i3);
 unsigned long res_i3;
 ss1 >> hex >> res_i3;

 istringstream ss2(i4);
 unsigned long res_i4;
 ss2 >> hex >> res_i4;
 

 unsigned long xor_res = res_i1 ^ res_i2 ^ res_i3 ^ res_i4;

 return int2hex_plaintext(xor_res);
}

string mul_res(string wrd,string rc)
{
 istringstream ss(wrd);
 unsigned long res_w;
 ss >> hex >> res_w;

 istringstream ss0(rc);
 unsigned long res_rc;
 ss0 >> hex >> res_rc;

 unsigned long xor_res = res_rc * res_w ;

 return int2hex_plaintext(xor_res);
}

string mod_res(string wrd)
{
 istringstream ss(wrd);
 unsigned long res_w;
 ss >> hex >> res_w;

 istringstream s("0xf9");
 unsigned long res;
 s >> hex >> res;



 unsigned long xor_res = res_w % res ;

 return int2hex_plaintext(xor_res);
}

//void GetRoundKey()
string GetRoundKey(int i,int j)
{

  for(int i=0;i<=11;i++)
  {
    
      if(i<1)
      {
        for(int b=0;b<=15;b++){round0[i][b] = key[b];} 
      }
      
    
      if(i>0)
      {
       for(int n=0;n<=3;n++)
       {
        temp[n] = round0[i-1][n+12];
        

        if(n==3)
        {

          for(int ctr=0;ctr<=3;ctr++)
          {
            l_shift[ctr] = temp[ctr+1];
            if(ctr==3){l_shift[3] = temp[0];}
            tmp_sb = sbox(l_shift[ctr]);
            sb[ctr] = tmp_sb;
            tmp_rndcons = arc(sb[0],round_const[i-1]);
           

            if(b0==0)
            {
             round0[i][b0] = xor_res(tmp_rndcons,round0[i-1][b0]);
            }
            if(b0>0 && ctr>0)
            {
             round0[i][b0] = xor_res(tmp_sb,round0[i-1][b0]);
            }

            
            b0++;
            if(b0==4){b0=0;}
          }
        }

       }
       
       
      
       for (int ctr0=0;ctr0<=3;ctr0++){round0[i][ctr0+4] = xor_res(round0[i][ctr0],round0[i-1][ctr0+4]);}
       for (int ctr0=0;ctr0<=3;ctr0++){round0[i][ctr0+8] = xor_res(round0[i][ctr0+4],round0[i-1][ctr0+8]);}
       for (int ctr0=0;ctr0<=3;ctr0++){round0[i][ctr0+12] = xor_res(round0[i][ctr0+8],round0[i-1][ctr0+12]);}

      }
     
    }

  
   
  round_fin[i][j] = round0[i][j];


  

return round_fin[i][j];

}

int hex2int(string i)
{
int out;  
std::stringstream s;
s<<hex<<i;
s>>out;

return out;
}




int encrypt(int i)
{

string enc_val;

pt[0] = int2hex_plaintext(i);  


for(int m=0;m<=15;m++)
  {
   tmp_rnd_key = GetRoundKey(0,m);
   tmp_rnd_xres = pt[m];
   tmp_res = xor_res(tmp_rnd_xres,tmp_rnd_key);
   cypher_text[0][m] = tmp_res;
  }


for(int round_num=1;round_num<=10;round_num++)
{

  for(int i=0;i<=15;i++)
  {

  

  
   tmp_mat[row][col] = sbox(cypher_text[round_num-1][i]);
   
   
   row++;

   if(row==4){row=0;col++;}
   if(col==4){row=0;col=0;}

   if(i==15)
   { 

      for(int rw=0;rw<=3;rw++)
        {
         for(int cl=0;cl<=3;cl++)
          {
            
           if(rw==0)
           {
            shift_row_mat[rw][cl] = tmp_mat[rw][cl];
           }

           if(rw==1)
            {
             shift_row_mat[rw][cl] = tmp_mat[rw][cl+1];
             shift_row_mat[rw][3] = tmp_mat[rw][0];
            }

           if(rw==2)
            {
             shift_row_mat[rw][cl] = tmp_mat[rw][cl+2];
             shift_row_mat[rw][2] = tmp_mat[rw][0];
             shift_row_mat[rw][3] = tmp_mat[rw][1];
            }

           if(rw==3)
            {
             shift_row_mat[rw][0] = tmp_mat[rw][3]; 
             shift_row_mat[rw][1] = tmp_mat[rw][0];
             shift_row_mat[rw][2] = tmp_mat[rw][1];
             shift_row_mat[rw][3] = tmp_mat[rw][2];
            }
            

         
          }
        }

        c1=0;r1=0;nxt_cl=0;

     for(int r=0;r<=15;r++)
       {
        for(int c=0;c<=3;c++)
          {
              
              

              if(mix_col[c][c1]=="0x01")
               {
                mul_temp[c] = shift_row_mat[c][r1];
               }

               if(mix_col[c][c1]=="0x02")
              {
               mul_temp[c] = mulBy2(shift_row_mat[c][r1]);
              }

              if(mix_col[c][c1]=="0x03")
              {
               mul_temp[c] = mulBy3(shift_row_mat[c][r1]);
              }

            
            
              
            if(c==3)
             {  
              mix_col_mat[nxt_cl][c1] = xor_res4i(mul_temp[0],mul_temp[1],mul_temp[2],mul_temp[3]); 
              
              nxt_cl++;
              r1++;
                     
              if(nxt_cl==4){c1++;nxt_cl=0;}
              if(r1==4){r1=0;}
             }   
             

          }    
        }


   if(round_num<10)
   {
    for(int n=0;n<=3;n++)
    {
      for(int m=0;m<=3;m++)
      {
        tk[m][n] = GetRoundKey(round_num,rct);
        tmp_res = xor_res(mix_col_mat[n][m],tk[m][n]);
        cypher_text[round_num][rct]=tmp_res;
        
        rct++;
        if(rct==16){rct=0;}
      }
    }  
   }
   
   if(round_num==10)
   {
    for(int n=0;n<=3;n++)
    {
      for(int m=0;m<=3;m++)
      {
        tk[m][n] = GetRoundKey(round_num,rct);
        tmp_res = xor_res(shift_row_mat[m][n],tk[m][n]);
        cypher_text[round_num][rct]=tmp_res;
        
        rct++;
        if(rct==16){rct=0;}
      }
    }  
   }





    }

   
  }
}

enc_val = cypher_text[10][0];

return hex2int(enc_val);
}



string ret_mc[16];

int main()
{

  Mat im_src = imread("/home/prog/UTEP/Cyber_Security/project/1.jpg");
  resize(im_src,im_src,Size(45,45));
  Mat im_src_gry;
  cvtColor(im_src,im_src_gry,CV_BGR2GRAY);

    Mat im_enc = im_src_gry.clone();
    im_enc = Scalar::all(0);

  
  /*
  int arr_blue[(im_src.rows)*(im_src.cols)];
  int arr_green[(im_src.rows)*(im_src.cols)];
  int arr_red[(im_src.rows)*(im_src.cols)];

  Vec3b pxl_colr[(im_src.rows)*(im_src.cols)];
  */  

  int arr_blue[496][496];
  int arr_green[496][496];
  int arr_red[496][496];

  //Vec3b pxl_colr[496][496];  
  uchar pxl_colr[496][496];  

  int arr_blue_enc[496][496];
  int arr_green_enc[496][496];
  int arr_red_enc[496][496];

  //Vec3b pxl_colr_enc[496][496];  
  uchar pxl_colr_enc[im_src_gry.rows][im_src_gry.cols];  
    

    
    for(int i=0;i<im_src_gry.rows;i++)
    {
      for(int j=0;j<im_src_gry.cols;j++)
      {
        pxl_colr[i][j] = (int)im_src_gry.at<uchar>(i,j);
        
      //arr_blue[i][j] = pxl_colr[i][j].val[0];
       //arr_green[i][j] = pxl_colr[i][j].val[1];
        //arr_red[i][j] = pxl_colr[i][j].val[2];
        
        //im_enc.at<Vec3b>(i,j) = pxl_colr_enc[i][j];
       // pxl_colr_enc[i][j].val[0] = encrypt(arr_blue[i][j]);
       // pxl_colr_enc[i][j].val[0] = encrypt(11);
       // pxl_colr_enc[i][j].val[1] = encrypt(arr_green[i][j]);
       // pxl_colr_enc[i][j].val[1] = encrypt(arr_red[i][j]);
       //arr_blue_enc[i][j]= encrypt(arr_blue[i][j]);
       //arr_green_enc[i][j]=encrypt(arr_green[i][j]);
       //arr_red_enc[i][j]=encrypt(arr_red[i][j]);


      }
    }
//cout<<encrypt(arr_blue[250][250])<<endl;
for(int i=0;i<im_src.rows;i++)
    {
      for(int j=0;j<im_src.cols;j++)
      {
        //pxl_colr[i][j] = im_src.at<Vec3b>(i,j);
        //int temp = encrypt(arr_blue[i][j]);
        //int i;
        //cout<<i<<endl;
        //i++;
        //arr_blue[i][j] = pxl_colr[i][j].val[0];
        //arr_green[i][j] = pxl_colr[i][j].val[1];
        //arr_red[i][j] = pxl_colr[i][j].val[2];
       pxl_colr_enc[i][j] = im_enc.at<uchar>(i,j); 

       pxl_colr_enc[i][j] = encrypt(pxl_colr[i][j]);
       //pxl_colr_enc[i][j].val[1] = encrypt(arr_green[i][j]);
       //pxl_colr_enc[i][j].val[2] = encrypt(arr_red[i][j]);
       im_enc.at<uchar>(i,j) = pxl_colr_enc[i][j];

      }
    }

    //arr_counter = 0;








cout<<"im_src:"<<(int)im_src_gry.at<uchar>(0,0)<<endl;
cout<<"im_enc:"<<(int)im_enc.at<uchar>(0,0)<<endl;

//cout<<"im_src:"<<im_src.type()<<endl;
//cout<<"im_enc:"<<im_enc.at<uint>(0,0)<<endl;







  //cout<<encrypt(5)<<endl;
  

//pxl_colr_enc[250][250].val[0] = encrypt(arr_blue[0][0]);

/*
for(int sd=0;sd<=15;sd++)
{
  cout<<cypher_text[10][sd]<<endl;
}
*/


  imshow("im_src_gry",im_src_gry);
  imshow("im_enc",im_enc);
  waitKey(0);

}