#include <stdio.h>
#include <stdint.h>
#include <limits.h>

/* weatherlog_t is a "weather sensor log type"
    which is really defined as a 64-bit unsigned
    integer.  See below. */
typedef uint64_t weatherlog_t;

unsigned int add(unsigned int, unsigned int);
unsigned int sub(unsigned int, unsigned int);
unsigned int mul(unsigned int, unsigned int);

void print_half_nybbles(unsigned int);
unsigned int reverse_half_nybbles(unsigned int);

int has_odd(unsigned int);
unsigned int make_odd(unsigned int);

int is_negative(int);

weatherlog_t pack_log_entry(unsigned int, unsigned int, unsigned int,
			    unsigned int,
			    int, int,
			    unsigned int, unsigned int);

unsigned int get_year(weatherlog_t entry);
unsigned int get_month(weatherlog_t entry);
unsigned int get_day(weatherlog_t entry);
unsigned int get_zip(weatherlog_t entry);
unsigned int get_high(weatherlog_t entry);
unsigned int get_low(weatherlog_t entry);
unsigned int get_precip(weatherlog_t entry);
unsigned int get_wind(weatherlog_t entry);
int binary_conversion(int num){
  if (num == 0) {
    return 0;
  }
else {
  return(num % 2)+10 *binary_conversion(num/2);
 }
}
int main(int argc, char **argv) {
  unsigned int i, j;
  int x, y;
  unsigned int year, month, day,
    zip, high_temp, low_temp, precip, avg_wind_speed;
  weatherlog_t log_entry;

  printf("Enter an integer: ");
  scanf("%u", &i);
  printf("Enter another integer: ");
  scanf("%u", &j);
  printf("One more integer, please (CHECK if -): ");
  scanf("%d", &x);
  printf("Please enter a positive integer: ");
  scanf("%d", &y);

  printf("%d + %d = %u\n",i ,j, add(i,j));
  printf("%d - %d = %u\n",i,j, sub(i,j)); 
  printf("%d * %d = %u\n",i,j, mul(i,j)); 
  
  if (is_negative(x)==1) 
    printf("%d is negative\n", x); 
  else 
    printf("%d is non-negative\n", x); 
  
  if (has_odd(y)) { 
    printf("%x has an odd number of bits in its binary representation\n", y); 
  } 
  else { 
    printf("%x has an even number of bits in its binary representation\n", y); 
    printf("but %x has an odd number of bits in its binary representation\n", make_odd(y)); 
  } 
  ///////////\*************FINISHED*********************\//////////////////////////////////// 
  printf("The half-nybbles of %d (in hex 0x%x) are:", x, x); 
  print_half_nybbles(x); 
  
  printf("%x with reversed half-nybbles is %x\n", x, reverse_half_nybbles(x)); 
  printf("Enter a year: ");
  scanf("%u", &year);
  
  printf("Enter a month as an integer (1-12): ");
  scanf("%u", &month);
  
  printf("Enter a day as an integer (1-31): ");
  scanf("%u", &day);
  
  printf("Enter a zip code as an integer (0-99999): ");
  scanf("%u", &zip);
  
  printf("Enter a temperature as an integer: ");
  scanf("%u", &high_temp);
  
  printf("Enter another temperature as an integer: ");
  scanf("%u", &low_temp);
  
  
  printf("Enter rainfall amount as an integer (mm): ");
  scanf("%u", &precip);
  
  printf("Enter a as an integer (km/hr): ");
  scanf("%u", &avg_wind_speed);
  
  
  log_entry=pack_log_entry(year, month, day, zip, high_temp, low_temp,
			   precip, avg_wind_speed);
  printf("You entered: %u/%u/%u for zip %5d: high %d F, low %d F, precip %d mm, wind speed %d km/hr\n",
	 get_day(log_entry), get_month(log_entry), get_year(log_entry),
	 get_zip(log_entry), get_high(log_entry), get_low(log_entry),
	 get_precip(log_entry), get_wind(log_entry));
  
  return 0;
}
/******************************************************/
unsigned int add(unsigned int i, unsigned int j) {
  /* can be done in a total of 7 lines, including one to declare an unsigned int, */
  /* two for a while loop, and one for the return
     You're not required to do it in 7 lines though . */
  int sum,carry;
  if (j==0) {
    return i;
  }
  //Binary debugger. 
   /* printf("%s%d\n","i= ",i);  */
   /* printf("%s%d\n","j= ",j);  */
   /* printf("%s%d\n","i in BINARY= ",binary_conversion(i));  */
   /* printf("%s%d\n","j in BINARY= ",binary_conversion(j));  */
  //End Binary debugger. 
  sum = i^j;
  
  //  printf("%s%d\n","SUM= ",binary_conversion(sum));
  carry = (i&j)<<1;
  //printf("%s%d\n","CARRY= ",binary_conversion(carry));
  return add(sum,carry);
  //  return i + j;
}

unsigned int sub(unsigned int i, unsigned int j) {
  /*Similar 7 lines, although there is a shorter way */
   if(i<j){ //So I thought it would be necessary to have a catch
     while (i != 0) { //for negative numbers, but affter I used programming calculaters
       int borrow = (~j) & i; //I realized it just does the same stuff! so it's unnessarry to add. 
       j=i^j; //if im wrong this stage can be re added but it changes the dynamic of the math because 
       i= borrow <<1; //subtraction is not communicative!!!!
     } 
     return j; 
     //  return i - j; 
   }    
  //END of unnecessary catch statement.
  //START of actual subtraction while method
  while (j != 0) {
    int borrow = (~i) & j;
    i=i^j;
    j= borrow <<1;
  }
  return i;
//  return i - j;
}

unsigned int mul(unsigned int i, unsigned int j) {
  /* can be done in a total of 8 lines including one to declare unsigned ints */
  /* two for a for loop, and one for the return */
  if (j==0)
    return 0;
 
 if (j>0)
    return (add(i,mul(i,sub(j,1))));

  if (j<0)
    return -mul(i,-j);
  //  return i * j;
}

/* prints the half-nybbles (i.e. 2 bit values) of x,
   one half-nybble at a time */
void print_half_nybbles(unsigned int x) {
    unsigned int i = 0, t = 0x3;
    while(t != 0) {
        printf("%u", (x & t) >> i);
        t <<= 2;
        i = add(i,2);
    }
    printf("\n");
}

/* returns the reverse of the half-nybbles of i */
unsigned int reverse_half_nybbles(unsigned int i) {
    unsigned r = 0, s = 0, t = 0x3, j = 0;
    while(j < mul(sizeof(i),8)) {
        r = (i >> j) & t;
        s<<=2;
        s = add(s,r);
        j = add(j,2);
    }
    return s;
}

/* returns 1 if x < 0
 returns 0 otherwise
 
 Do not use the <, > operators. */
int is_negative(int x) {
    return (x & 0x80000000) != 0;
}

/* returns 1 if x's binary representation
 has an odd number of 1s or 0 otherwise */
int has_odd(unsigned int x) {
    unsigned int count = 0, i = 0, j = 1;
    while(i < mul(sizeof(x),8)) {
        if((x & j) == j)
            count = add(count,1);
        i = add(i,1);
        j = mul(j,2);
    }
    return (count & 1) == 1;
}

/* If x's binary representation contains an odd number of 1s, x is
 returned. Otherwise, it returns a copy of x, but with its most significant
 bit modified so that there is an odd number of 1s. */
unsigned int make_odd(unsigned int x) {
    if(!has_odd(x))
        x ^= 0x80000000;
    return x;
}


/* combines all of the arguments into a single weatherlog_t entry as described below */
weatherlog_t pack_log_entry(unsigned int year, unsigned int month, unsigned int day,
                            unsigned int zip, int high_temp, int low_temp,
                            unsigned int precip, unsigned int avg_wind_speed) {
    weatherlog_t log_entry = 0;

    log_entry ^= sub(year,2000);
    log_entry <<= 4;
    log_entry ^= month;
    log_entry <<= 5;
    log_entry ^= day;
    log_entry <<= 16;
    log_entry ^= zip;
    log_entry <<= 8;
    log_entry ^= high_temp;
    log_entry <<= 8;
    log_entry ^= low_temp;
    log_entry <<= 10;
    log_entry ^= precip;
    log_entry <<= 7;
    log_entry ^= avg_wind_speed;

    return log_entry;
}

unsigned int get_year(weatherlog_t entry) {
    return entry >> 58;
}

unsigned int get_month(weatherlog_t entry) {
    return 0xf & (entry >> 54);
}

unsigned int get_day(weatherlog_t entry) {
    return 0x1f & (entry >> 49);
}

unsigned int get_zip(weatherlog_t entry) {
    return 0xffff & (entry >> 33);
}

unsigned int get_high(weatherlog_t entry){
    return 0xff & (entry >> 25);
}

unsigned int get_low(weatherlog_t entry) {
    return 0xff & (entry >> 17);
}

unsigned int get_precip(weatherlog_t entry) {
    return 0x3ff & (entry >> 7);
}

unsigned int get_wind(weatherlog_t entry) {
    return 0x7f & entry;
}



/* weatherlog_t

   A particular weather sensor called the WeatherJuicer 2000 TM stores a
   log entry each day, representing weather activity from the
   previous 24 hours. Each entry includes a:

   - year :: 6 bits -- stored as the number of years since the year 2000.
   - month :: 4 bits
   - day :: 5 bits
   - zip_code :: 16 bits
   - high_temp :: in degrees Fahrenheit, stored as an 8-bit signed integer
   - low_temp :: in degrees Fahrenheit, stored as 8-bit signed integer
   - precipitation :: in mm. stored as a 10-bit unsigned integer.
   - average_wind_speed :: 7 bits. unsigned int km/hr.

   All of these are packed into a 64 bit unsigned integer in the above order.

   For example, if on September 16, 2015, on Temple's main campus, which
   is in zip code 19122, we have 15 mm of rain, a high temperature of 85
   degrees, a low temperature of 65 degrees, and an average wind speed of
   5 km/hour.

   We'd store:
- year :: 2015, which is 15 years from 2000, so 001111
- month :: September, which is the 9th month, so 1001.
- day :: 16, which is 1 0000
- zip_code :: 19122 which is 0100 1010 1011 0010
- high_temp :: 85F, so 0101 0101
- low_temp :: 65F, so 0100 0001
- precipitation :: 35 mm so 00 0010 0011
- average wind speed :: 5 km/h, so 000 0101

And all would be packed into a single 64-bit unsigned integer:

00 1111 1001 10000 0100 1010 1011 0010 0101 0101 0100 0001 00 0010 0011 000 0101

OR

0011 1110 0110 0000 1001 0101 0110 0100 1010 1010 1000 0010 0001 0001 1000 0101

OR

0x3e609564aa821185


We define this weather log as its own datatype called weatherlog_t, which
under the covers is really a 64-bit unsigned int. This is done in the line:

typedef uint64_t weatherlog_t;

*/
