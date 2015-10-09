//
//  Header.h
//  
//
//  Created btemp Александр Малышев on 21.05.15.
//
//

#ifndef _Header_h
#define _Header_h


WITH temp as (SELECT distinct cast(B_VOL as int) as B_VOL from utb)

SELECT up,down,side,cast(sqrt(up*down)/2 as numeric(6,2)) from (
                                                          SELECT tmp1.B_VOL as up,
                                                          tmp2.B_VOL as down,
                                                          tmp3.B_VOL as side,
                                                          tmp1.B_VOL+tmp2.B_VOL as sum,
                                                          tmp3.B_VOL * 2 as dblSide
                                                          from temp tmp1,temp tmp2,temp tmp3
                                                          where tmp1.B_VOL<tmp2.B_VOL
                                                          )u where sum=dblSide



#endif
