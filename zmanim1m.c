/* zmncal.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <string.h>

 static double rd = .017453292;
 double lat,slat,clat,lon,lonh;
 double x, h, l,sl,tl,m,sm,t;
 double srf,ssf,csgm;
 double sgm,ssgm,ra,tra,bigt;
 float vh;
 int  sr,ss,srd,ssd,srh, srm, ssh, ssm ,hour;
 int alos,ks,ksg,ztf,chatz,bigmin,min,rabtam,plag,th,cand;
 int daynum,year,numo,mo;
 int loh, lom,lah, lam;
 int i,j,k,y,wd,o,yr,tz,choz,a;
 int fr_da_ap,dt,la_da_oc;
 char prz,prs;
 char string[30];
 char year_str[5];
 char place[20];
 int numo,ay;
 int monprn[] = {1,2,3,4,5,6,7,8,9,10,11,12} ;

 int weekday( int mo,int dt,int yr );
 int get_leap( int year);
 void getzm(int);
 void printc(void);
 void printr(void);
 void printch(void);
 
 void printrh(void);
 void getplace(void);
 void intro(void);
 int  getdn(int monum);
 void help1(void);
 void box1(int,int,int,int);
 void calprn(int mo,int year);
 void cal_box(int b, int t, int n);
 int  add_day(int,int);

static char *months[] = {"JANUARY  ","FEBRUARY ","MARCH    ","APRIL    ","MAY      ","JUNE     ",
		    "JULY     ","AUGUST   ","SEPTEMBER","OCTOBER  ","NOVEMBER ","DECEMBER "};

static int dpm[] = {31,28,31,30,31,30,31,31,30,31,30,31};

static char *days[] = {"SUN ","MON ","TUES","WED ","THUR","FRI ","SHBS"};

static *cities[]= {"N.Y.C.         ",
		   "Baltimore MD   ",
		   "Boston MA      ",
		   "Cleveland OH   ",
		   "Chicago IL     ",
		   "Denver CO      ",
		   "Detroit MI     ",
		   "L.A. CA        ",
		   "Lakewood, NJ   ",
		   "Miami, FL      ",
		   "Minneapolis MN ",
		   "Montreal Que.  ",
		   "Pittsburgh PA  ",
		   "Philadelphia PA",
		   "St. Louis MO   ",
		   "Seattle WA     ",
		   "Toronto Ont.   ",
		   "Far Rockaway,NY",
		   "White Lake, NY" ,
		   "Another Place  "
		    };
 FILE *zmanim;
 main(void)


{
    intro();
    getplace();
    
    
   // _clearscreen(_GCLEARSCREEN);
   
    printf(" For what year would you like this chart printed?\r\n");
    printf("                                                   ===> ");
    scanf("%d",&year);
    wd = weekday(1,1,year) - 1;
    if (get_leap(year) ) dpm[1] = 29; else dpm[1] = 28;

   // _clearscreen(_GCLEARSCREEN);

    getyn:
{
    printf("");
    printf("\n   Now, you can print a chart for a whole year or only for\r\nseveral months.\r\n\r\n");
    printf(" Would you like to print charts for the whole year? (y/n) ==> ");
    prz = getchar();
    // _clearscreen(_GCLEARSCREEN);

	  if(prz == 'y')
		{
		 for(ay = 0; ay <= 11;ay++)
		 monprn[ay] = ay + 1 ;
		 numo = 12;
		}
	  else

	  {
		gnm:
		{
		mo = 1;
		printf("\r\n\r\n  For how many months would you like charts printed? >  ");
		scanf("%d",&numo);
		}
		if(numo < 1 && numo > 11) goto gnm;
		printf("  Please enter the month number(s) of the month(s) for which you would charts\r\n  (ex. for January, press \"1\" February, \"2\"\r\n\r\n\r\n");
		if(numo == 1) printf("Which month would you like to print? => ");
		else printf("  Which is the the first month? ==> ");
		scanf("%d",&monprn[0]);

        }
    
     while( mo < numo )
     {
	  printf("  Next month? ==> ");
	  scanf("%d", &monprn[mo]);
	  mo+= 1;
	  flushall();

     }

	  }

    help1();
    prs = getchar();

   // _clearscreen(_GCLEARSCREEN);


	       y = 0;

	       printf("\r\n\r\n\r\n\r\nPlease wait while your chart is being printed.\r\n\r\nIt could take a couple of minutes.");
	       for (j = 0; j <= numo - 1; j++)
		 {
		    if(prs == 'c')
		     {
			printch();
		     }
		    else if(prs == 'r')
		     {
			printrh();
		     }
		    else
		     {
		     printf("\r\nPlease call again!\n\tThanks for trying Zmnprn.");
		     exit(1);
		      }

		    daynum = getdn(monprn[j]) + 1;

		    for(i = 0 ;i < dpm[monprn[j]-1];i++)

		     {
		    getzm(daynum);
		    /* (prs == 'c') */
		    printc();
		    /*printf("daynum==>%d	monprn[j]==> %d	i==> %d	dpm==> %d", daynum,monprn[j],i,dpm);*/
		    /* else if(prs == 'r')
		    printr(); */
		    daynum++; 
		    }
		    fprintf(zmanim,"\r\n\t M\"A Zman Tfillah, SUBTRACT 24 min.  ");
  			fprintf(zmanim,"M\"A Mincha Gedolah, ADD six min.\r\n");
  			fprintf(zmanim,"\t M\"A Plag, ADD 57 min.\r\n");
/* fprintf(zmanim, "\r\nZmncal Ver. 1.3 (C) copyright Howard J. Ochs 1196 E. 10th St. Brooklyn, NY 11230 (718) 377-2604 "); */

		    fclose(zmanim);
		      

		    
		 }

	     // _clearscreen(_GCLEARSCREEN);
	      printf("\r\n\r\n\r\n\r\nEnjoy your charts and don't miss any zmanim!\r\n\r\n\tThanks for using zmnprn.\r\n" ) ;
	      return 0;
}

void intro(void)

{
   // _clearscreen(_GCLEARSCREEN);
        
    printf("\r\nWelcome to Zmncal Ver. 1.5f!\r\n(C) 1991 Shore Tech,Howard Joseph Ochs\r\n1121A Sage St.Far Rockaway, NY 11691 (718) 327-6050\r\n\r\n");
    printf("This program will print charts of the daily zmanim, to help you make sure\r\n");
    printf("that you will not miss any.\r\n\r\n");
    printf("The program is preprogrammed with zmanim for many major American cities.\r\n");
    printf("For any other location in the U.S. or Canada, just follow the program's \r\ninstructions ");
    printf("and be prepared to supply the longitude, latitude and time \r\nzone of the place that ");
    printf("you would like to know zmanim for.\r\n\r\n");
    printf("For more information, see accompanying file, zmnprn.doc.\r\n");
     
     k= 0;
    while(k== 0)
    	{
    printf("               Please press any key to continue .... ");
    k= getchar();
    	}      
    // _clearscreen(_GCLEARSCREEN);

}

    void help1(void)

{
   // _clearscreen(_GCLEARSCREEN);
    printf("Excellent.\n\nNow, we are ready to print chart(s) for %d.\r\n",year);
    if(prz == 'n')
       printf( "We will be printing charts for:\r\n");
       for(i = 0;i < numo ; i++)
	{
	   printf( "%s, ",months[monprn[i] - 1]);
	   if( monprn[i] % 5 == 0 )
	      printf("\r\n");
	}                                                                                   if(numo > 1 )
    {
	printf("\r\n\r\nMake sure that you have at least");
	if(prz == 'y')
	numo = 12;
	printf( " %d ", numo);
    printf( "sheets of paper in your printer.\r\n\r\n");
    }
    else printf("\n\n");
    printf("To print the complete chart, set your printer to condensed print and\r\n");
    printf("                                                   press ==> \'c\'\r\n\r\n");
    printf("If you would like an abridged chart, or if your printer doesn't \r\nsupport condensed print,\r\n");
    printf("                                                   press ==> \'r\'\r\n\r\n\r\n");
    printf("To terminate this program because your printer isn't ready \r\nor if you aren't ready,\r\n");
    
    printf("press any other key...\r");
    
    prs= getchar();
    
}

void getzm(int daynum)
{
 slat = sin( lat * rd );
 clat = cos( lat * rd );

 lonh = lon / 15;

  /* for sunrise */

  t = daynum + ( 6 - lonh ) / 24;
  m = 0.985600 * t - 3.289;
  sm = sin( m * rd );
  l = m + 1.916 * sm + 0.020 * sin( 2 * (m  * rd) ) + 282.634 - 360;
  tl = tan( l * rd );
  sl = sin( l * rd );
  tra = 0.91746 * tl;
  ra = atan( tra ) / rd;
  if(ra > 90.0)
       ra = (90 +ra) / 15 ;
  else
       ra = (180 + ra) / 15 ;
  ssgm = .39782 * sl ;
  csgm = cos( asin( ssgm ) );
  x =( -0.01488 - ssgm * slat ) / ( csgm * clat );
  h = ( 360 - acos( x ) / rd ) / 15 ;
  bigt = h + ra - 0.0657100 * t - 6.622;
  if (bigt < 0) bigt = bigt + 12;
  srf = (  ( bigt - lonh ) - 5  - tz) ;
  if(srf > 12)
       srf = srf -12;

  fr_da_ap = weekday(4,1,year);
  la_da_oc = weekday(10,31,year);

  if(fr_da_ap == 1)
      {
	if(daynum > 97 && daynum < 301 + get_leap(year) )
	  srf = srf + 1;
      }
  else if( daynum >  ( 91 + get_leap(year) ) + (7 - fr_da_ap) % 7 && daynum < (304 + get_leap(year) ) - (la_da_oc - 1) )
	  srf = srf + 1;
  if(srf<= 0)
    srf+= 12;

  srf = srf * 60;

    /* for sunset */

    t = daynum + ( 18 - lonh ) / 24;
    m = 0.985600 * t - 3.289;
    sm = sin(m * rd );
    l = m + 1.916 * sm + 0.020 * sin( 2 * ( m  * rd ) ) + 282.634 - 360 ;
    tl = tan(l * rd );
    sl = sin(l * rd );
    tra = 0.91746 * tl;
    ra = atan(tra ) / rd;
    ra = ( 180 + ra ) / 15 ;
    ssgm = .39782 * sl ;
    csgm = cos( asin( ssgm ) );
    x = ( -0.01488 - ssgm * slat ) / ( csgm * clat );
    h = ( acos( x ) / rd ) / 15;
    bigt = h + ra - 0.0657100 * t - 6.622;
     if(bigt < 0 ) bigt = bigt + 12;
     if(bigt < 1.0)
	bigt = bigt + 12;
    ssf = ( bigt - lonh + 7 - tz ) ;

    if(fr_da_ap == 1)
       {
	if(daynum > 97 && daynum < 301 + get_leap(year) )
	   ssf = ssf + 1;
       }
   else if( daynum >  ( 91 + get_leap(year) ) + (7 - fr_da_ap) % 7 && daynum < (304 + get_leap(year) ) - (la_da_oc - 1) )
	   ssf = ssf + 1;
   if(ssf< 12 )
      ssf+= 12;
   ssf = ssf * 60;


  vh     = ( ssf - srf ) / 12.0;
  alos   = round(srf - 72);
  rabtam = round(ssf + 72);
  ksg    = round(srf + vh * 3 );
  ks     = ksg - 36;
  ztf    = round(srf + vh * 4 );
  chatz  = round( srf + ( (ssf - srf) / 2.0 ) );
	   if (chatz >= 780 ) chatz = chatz - 720;
  bigmin = round( srf + ( (ssf - srf) / 2.0 ) + vh / 2.0 );
  // min    = round(ssf - vh * 3 );
  plag   = round(ssf - vh * 1.25 );
  cand   = round(ssf) - 18;
  th     = round(ssf + 50.0 + round( ((((ssf-srf)-740.0)/180)*2.0) ) ); /* (daynum * (2.0/172.0) ) ) */
  }


int get_leap( int year)

{
    if ( 0 == ( year % 400 ) )  return( 1 );
    else if ( 0 == ( year % 100 ) )  return( 0 );
    else if ( 0 == ( year % 4 ) )    return( 1 );
    else                             return( 0 );
}

int getdn(int monum)

{
   int d = 0;

  for( i = 0; i < (monum - 1); i++ )
     d += dpm[i]  ;
     return(d);
}

void getplace(void)

{
    gp:

      {
    printf("\n  Please choose from one of the following major cities or\r\n ");
    printf("choose (20), for another place\r\n");
    
    printf("\n (1) N.Y.C.          (2)  Baltimore, MD\r\n (3) Boston, MA      (4)  Cleveland, OH\r\n");
    printf(" (5) Chicago, IL     (6)  Denver, CO\r\n (7) Detroit, MI     (8)  L.A., CA\r\n (9) Lakewood, N.J.  ");
    printf("(10) Miami, FL\r\n(11) Minneapolis, MN (12) Montreal, Que.\r\n(13) Pittsburgh, PA  ");
    printf("(14) Philadelphia, PA\r\n(15) St. Louis, MO   (16) Seattle, WA\r\n(17) Toronto, Ont.   (18) Far Rockaway, NY\r\n");
    printf("(19) White Lake, NY\r\n(20) Elsewhere\r\n\n");
    printf("        =======> ");

    scanf("%d",&choz);
       }
	       if (choz == 1)  { lat = 40.63395; lon = -73.98262; tz = 0;
				}
	   else if(choz == 2)  { lat = 39.3;      lon = -76.633333; tz = 0;
				}
	   else if(choz == 3)  { lat = 42.35;     lon = -71.083333; tz = 0;
				}
	   else if(choz == 4)  { lat = 41.466666; lon = -81.616666; tz = 0;
				}
	   else if(choz == 5)  { lat = 41.833333; lon = -87.616666; tz = 1;
				}
	   else if(choz == 6)  { lat = 39.75;     lon = -105;       tz = 2;
				}
	   else if(choz == 7)  { lat = 42.333333; lon = -83.05;     tz = 0;
				}
	   else if(choz == 8)  { lat = 34.05;     lon = -118.25;    tz = 3;
				}
	   else if(choz == 9)  { lat = 40.05;     lon = -74.13;     tz = 0;
				}
	   else if(choz == 10) { lat = 25.766666; lon = -80.2;      tz = 0;
				}
	   else if(choz == 11) { lat = 44.983333; lon = -93.233333; tz = 1;
				}
	   else if(choz == 12) { lat = 45.5;      lon = -73.833333; tz = 0;
				}
	   else if(choz == 13) { lat = 40.45;     lon = -79.95;     tz = 0;
				}
	   else if(choz == 14) { lat = 39.95;     lon = -75.166666; tz = 0;
				}
	   else if(choz == 15) { lat = 38.583333; lon = -90.2;      tz = 1;
				}
	   else if(choz == 16) { lat = 47.616666; lon = -122.33333; tz = 3;
				}
	   else if(choz == 17) { lat = 43.666666; lon = -79.4;      tz = 0;
				}
	   else if(choz == 18) { lat = 40.6;      lon = -73.75; tz = 0;
				}
	   else if(choz == 19) { lat = 41.666666; lon = -74.86666; tz = 0;
				}
	   else if(choz == 20) {
				
			//	_clearscreen(_GCLEARSCREEN);
				
			
				printf(" You have chosen another place.\r\n\n");
				printf("What is the name of this place?\r\n    ==>> ");
				fflush(stdin);
				gets(cities[18]);
				printf("\r\n\r\n Please enter latitude of place.\r\n");
				printf("              (dd:mm)    =====> ");
				scanf("%d:%d" , &lah , &lam);
			//	_clearscreen(_GCLEARSCREEN);
			
				printf("\r\n\n\n\n Please enter west longitude of place.\r\n");
				printf(" All of North American has west longitude.\r\n");
				printf("          ( - dd:mm)    =====> - ");
				scanf( "%d:%d" , &loh , &lom);
				lat = lah + lam / 60.0;
				lon = 0 - (loh + lom / 60.0);
			//	_clearscreen(_GCLEARSCREEN);
			
				printf("\r\n\r\n Now, please enter the time zone of the place.\r\n Enter the number of hour before EST.\r\n");
				printf(" Disragard daylight savings - the program will\r\n automatically adjust  for it.\r\n\n");
				printf(" (-1) Atlantic  (0) Eastern \r\n (1) Central  (2) Mountain\r\n (3) Pacific\r\n\n");
				printf("                        =====> ");
				scanf("%d",&tz);
			//	_clearscreen(_GCLEARSCREEN);
			
				printf("\n\nWhat is the name of this place?\r\n===> ");
				fgets(place,20,stdin);
				}
	      else goto gp;

}

void printch(void)

{  // zmanim= fopen("c:\zmanim.new","w");
   
				_itoa(year,year_str,10);
				strcpy(string,cities[choz- 1]);
				strcat(string,months[monprn[j]- 1]);
				strcat(string,",");
				strcat(string,year_str);
			
		    zmanim= fopen(string,"w"); 

	fprintf(zmanim, "                 %s                         %s %d\r\n\r\n\r\n",cities[choz- 1],months[monprn[j]- 1], year);
	fprintf(zmanim, "\t          Alos  Sunrise      K\"S       Zman   Chatzos Mincha Plag Candles Sunset Tzeis Rabbeinu Var.\n");
	fprintf(zmanim, "\t                           M\"A/GR\"A    Tfillah        Gedolah                            Tam    Hour\r\n\r\n");
}

void printc(void)

{
  fprintf(zmanim, "\t%s %2d  %2d:%.2d %2d:%.2d:%.2d  %2d:%.2d/",days[(wd + daynum -1 ) % 7 ],i + 1,alos / 60,alos % 60,(int)(srf) / 60, (int)(srf) % 60, (int)( (srf - (int)(srf) ) * 60.0 ),ks / 60, ks % 60);
  fprintf(zmanim, "%2d:%.2d   %2d:%.2d  %2d:%.2d  ",ksg / 60, ksg % 60, ztf/60, ztf % 60,chatz/60, chatz % 60);
  if(bigmin /60 > 12) fprintf(zmanim, "%2d:%.2d  ",bigmin /60 - 12,bigmin % 60);
  else                fprintf(zmanim, "%2d:%.2d  ",bigmin /60, bigmin % 60);
  fprintf(zmanim, "%2d:%.2d",plag / 60 - 12, plag % 60);
 	 if (  (daynum + wd  ) % 7 == 6 )
		fprintf(zmanim," %2d:%.2d " ,cand/60 -12,cand % 60);
	 
	else ( fprintf(zmanim,"       "));  
  fprintf(zmanim, "%2d:%.2d:%.2d",(int)(ssf / 60.0) - 12,(int)(ssf) % 60, (int)( (ssf - (int)(ssf) ) * 60.0 ) );
  fprintf(zmanim, " %2d:%.2d  ",th /60 - 12, th % 60);
  fprintf(zmanim, "%2d:%.2d   %.1f\r\n",rabtam / 60 - 12, rabtam % 60, vh );
  if ( ( daynum + wd  ) % 7 == 0 )
  fprintf(zmanim, "\r\n");
 

   
}

void printrh(void)

{
	fprintf(zmanim, "                                   %s %d\n\n",months[monprn[j] - 1],year);
	fprintf(zmanim, "          Sunrise   K\"S      K\"S    Zman     Mincha   Sunset   Tzeis   Var.\n");
	fprintf(zmanim, "                    M\"A      GR\"A   Tfillah  Gedolah                   Hour\n\n");
}

void printr(void)

{
  fprintf(zmanim, "%s %2d   %2d:%.2d   %2d:%.2d:%.2d  ",days[(wd + daynum -1 ) % 7 ],i + 1,(int)(srf) / 60, (int)(srf) % 60, (int)( (srf - (int)(srf) ) * 60.0 ),ks / 60, ks % 60);
  fprintf(zmanim, "%2d:%.2d    %2d:%.2d    ",ksg / 60, ksg % 60, ztf/60, ztf % 60);
  if(bigmin /60 > 12) fprintf(zmanim, "%2d:%.2d   ",bigmin /60 - 12,bigmin % 60);
  else                fprintf(zmanim, "%2d:%.2d   ",bigmin /60 ,bigmin % 60);
  fprintf(zmanim, "%2d:%.2d    %2d:%.2d    ",th / 60 - 12, th % 60,(int)(ssf / 60.0) - 12, round(ssf) % 60 );
  fprintf(zmanim, "%.1f\n", vh );
  if ( (daynum + wd ) % 7 == 0 )
  fprintf(zmanim, "\n");

}

int weekday( int mo,int dt,int yr )

{
int da;
if(mo <= 2)
    {
    mo += 12;
	yr -= 1;
    }

da =( (dt + mo * 2 + (mo + 1) * 6/10 + yr + (yr / 4 - yr / 100) + yr / 400 + 2) ) % 7 ;

if(!da) da = 7;

return(da);
}

int round(double d)

{
int x;
x = (int)(d);
if(d - x >= 0.5) x+=1;
return(x);
}





int add_day(int day_num, int many)
{
   int i,j;

for(i =1;i<=many;i++)
 {
   fprintf(zmanim,"\xb3");

   fprintf(zmanim,"%2d",day_num);

   for(j=1;j <=8;j++)
   fprintf(zmanim," ");

   fprintf(zmanim,"\xb3 ");

   day_num += 1;
 }
return(day_num);
}



int friday(mo,day,year)
{
    int first_friday = 7 - weekday(mo,1,year);
    if(!first_friday) first_friday += 7;
    if(day == first_friday || day == first_friday % 7) return(1);
    else return(0);
}


