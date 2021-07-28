//          By Keshav Verma
//          keshaverma.17@gmail.com
//
//
//
//              PLEASE READ THE BELOW POINTS CAREFULLY, AND REFER TO THE README FILE ATTACHED FOR MORE CLEARITY.
//
//
//Hardware part:
//      This module will look like a watch.
//      The inner of the watch should be metallic(I used alumenium foil) and connected to A0(analogRead pin 0 of node MCU), so that it is touched to the hand from inside.
//      A metallic foil will be used as touch shield(With the help of garbage values, when the sheet is touched garbage values in analogRead pin will increase)
//      this metal foil will be placed over node mcu, and divided into four parts.
//      divide the shield into 4 parts Middle portion, Up Portion, left Portion, Right Portion
//      Middle portion of the shield will be connected to pin 0 of node MCU
//      UP portion of the shield will be connected to pin 16 of node MCU
//      Left portion of the shield will be connected to pin 12 of node MCU
//      Right portion of the shield will be connected to pin 15 of node MCU
//      A vibrator motor is also used in this(Very small motor used in mobile phones). It will be connected to a transistor in transistor as an amplifier mode, so that when the trigger pin of transistor is provided a high, the vibrator motor starts.
//      the trigger pin of transistor is connected to pin no. 13 of the node MCU.
//      Connect the node MCU with a battery with VIN Pin on it.
// Here, the hardware part is complete.
// _______________________________________________________________________________________________________________________
       
// Mobile application Part:
//     Download Mobile app and Create a blynk key(You can refer to youtube for that), and add this key to code below in auth[] array.
//     Create a New Project  
//     Add a terminal into the project which will be medium for two way communication
//     Name its Input as V1 (Note that it is most important for communication, and thats why I have mentioned it in BlynkWrite function also) as the node MCU is programmed to listen for V1
//     Software part is complete
  

// How to use:
// The hardware touch shield is divided into 4 parts,, (RIGHT(r),LEFT(l), UP(u),  MID(m)  )
// TO START CREATING MESSAGE:  swipe mid to up and then to down again (retrun2down function)  M->U->M    
// after that, you are ready to tap in morse(on 'm' and 'u')  to create message   'm' is for dot, and 'u' is for dash
// remember that you will be able to type character by character
// So, to accumulate next character to the message string, tap on right(r), after that, you are ready to tap for next character
// once you have written the message, You have to tap to the left(l), and after that ,, the message will be transferred to blynk server and then to application; 
// TO KNOW TIME IN HOURS AND MINUTES IN MORSE: swipe up to mid and then to up again (return2up function) U->M->U
// after that you will feel the morse vibrations of hours and minutes  
// if you missed any message or could not understand it,, you can swipe left to right(l2r) function, it will re play that message on your wrist


//_________________________________________________________________________________________________________________________
//  Instructions:
//
//use Arduino IDE
//Select proper board for NodeMCU(I dont exactly remember the Board name, you can refer from internet)
//battery voltage ~5V, in my case, i dont used voltage regulator.
//You will have to download libraries that I have used in this project. they may not be already downloaded in arduino IDE.
//Change Your Wifi Netowrk name accordingly
//Change your password accordingly
//


#include <NTPClient.h>                              // date time management
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiUdp.h>                                 // for offset calculation

char auth[] = "paEPn5Kulttw6yup-A8EgDH1QA-7cJa";  //Change this key with your blynk key
char ssid[] = "Net";
char pass[] = "12345678";

long int utctimeseconds= 19800; // because, for india, utc offset time is 5:30, so 5.5*60*60
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utctimeseconds);

int dot =150;
int dash= 450;
int gap =150;
int nextchar=1200;
int nextword= 700;
String newstr="";
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(12,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(0,OUTPUT);   
  pinMode(15,OUTPUT);   
  pinMode(4,OUTPUT);  
  pinMode(13,OUTPUT);   
  timeClient.begin();
}

BLYNK_WRITE(V1)             //recievd text to morse 
{
  String textIn= param.asStr();
  newstr=textIn +"";
  Serial.println( textIn); 
  Serial.print(textIn.length());
  for (int i=0; i<textIn.length(); i++)
  {
  impulse(textIn[i]);
  }
  
}


void dashfxn()
             {digitalWrite(13,HIGH);//dash
             delay(dash);
             digitalWrite(13,LOW);
             delay(gap);}

void dotfxn()
             {digitalWrite(13,HIGH);//dot
             delay(dot);
             digitalWrite(13,LOW);
             delay(gap);}

void lastdash()
             {digitalWrite(13,HIGH);//dash
             delay(dash);
             digitalWrite(13,LOW);}

void lastdot()
             {digitalWrite(13,HIGH);//dot
             delay(dot);
             digitalWrite(13,LOW);}


    

void impulse(char x)
{
  if (x=='A'||x=='a')   {dotfxn();  lastdash();}
//______________________________________________________________________________
  if (x=='B'|| x=='b')  {    dashfxn();  dotfxn();    dotfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='C'|| x=='c')  {    dashfxn();    dotfxn();    dashfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='D'|| x=='d')  {   dashfxn();   dotfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='E'|| x=='e')  {    lastdot();  }
//______________________________________________________________________________
if (x=='F'|| x=='f')  {    dotfxn();    dotfxn();    dashfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='G'|| x=='g')  {    dashfxn();    dashfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='H'|| x=='h')  {    dotfxn();    dotfxn();    dotfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='I'|| x=='i')  {    dotfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='J'|| x=='j')  {    dotfxn();    dashfxn();  dashfxn();   lastdash();  }
//______________________________________________________________________________
if (x=='K'|| x=='k')  {    dashfxn();    dotfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='L'|| x=='l')  {    dotfxn();    dashfxn();    dotfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='M'|| x=='m')  {    dashfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='N'|| x=='n')  {    dashfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='O'|| x=='o')  {    dashfxn();    dashfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='P'|| x=='p')  {    dotfxn();    dashfxn();    dashfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='Q'|| x=='q')  {    dashfxn();    dashfxn();    dotfxn();    lastdash(); }
//______________________________________________________________________________
if (x=='R'|| x=='r')  {    dotfxn();    dashfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='S'|| x=='s')  {    dotfxn();    dotfxn();    lastdot();  }
//______________________________________________________________________________
if (x=='T'||x=='t')  {    lastdash();  }
//______________________________________________________________________________
if (x=='U'|| x=='u')  {    dotfxn();    dotfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='V'|| x=='v')  {    dotfxn();    dotfxn();    dotfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='W'|| x=='w')  {    dotfxn();    dashfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='X'|| x=='x')  {    dashfxn();    dotfxn();    dotfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='Y'|| x=='y')  {    dashfxn();    dotfxn();    dashfxn();    lastdash();  }
//______________________________________________________________________________
if (x=='Z'|| x=='z')  {    dashfxn();    dashfxn();    dotfxn();    lastdot();  }  
//______________________________________________________________________________
if (x==' ')  {    delay(nextword);  }
//______________________________________________________________________________
if (x=='1')  {  dotfxn();   delay(100);  dashfxn(); delay(100); dashfxn(); delay(100); dashfxn(); delay(100);  lastdash(); }//   .----
//_________________________________________________________________________________________________________________________________________
if (x=='2')  {  dotfxn();   delay(100);  dotfxn();  delay(100); dashfxn(); delay(100); dashfxn(); delay(100);  lastdash(); }//   ..---
//_________________________________________________________________________________________________________________________________________
if (x=='3')  {  dotfxn();   delay(100);  dotfxn();  delay(100); dotfxn();  delay(100); dashfxn(); delay(100);  lastdash(); }//   ...--
//__________________________________________________________________________________________________________________________________________
if (x=='4')  {  dotfxn();   delay(100);  dotfxn();  delay(100); dotfxn();  delay(100); dotfxn();  delay(100); lastdash(); }//   ....-
//__________________________________________________________________________________________________________________________________________
if (x=='5')  {  dotfxn();   delay(100);  dotfxn();  delay(100); dotfxn();  delay(100); dotfxn();  delay(100);  lastdot(); }//    .....
//__________________________________________________________________________________________________________________________________________
if (x=='6')  {  dashfxn();  delay(100);  dotfxn();  delay(100); dotfxn();  delay(100); dotfxn();  delay(100); lastdot(); }//    -....
//__________________________________________________________________________________________________________________________________________
if (x=='7')  {  dashfxn();  delay(100);  dashfxn(); delay(100); dotfxn();  delay(100); dotfxn();  delay(100);  lastdot(); }//    --...
//__________________________________________________________________________________________________________________________________________
if (x=='8')  {  dashfxn();  delay(100);  dashfxn(); delay(100); dashfxn(); delay(100); dotfxn();  delay(100); lastdot(); }//    ---..
//__________________________________________________________________________________________________________________________________________
if (x=='9')  {  dashfxn();  delay(100);  dashfxn(); delay(100); dashfxn(); delay(100); dashfxn(); delay(100); lastdot(); }//    ----.
//__________________________________________________________________________________________________________________________________________
if (x=='0')  {  dashfxn();  delay(100);  dashfxn(); delay(100); dashfxn();  delay(100); dashfxn(); delay(100); lastdash(); }//   -----
//__________________________________________________________________________________________________________________________________________
delay(nextchar);}




#define leftpin 12
#define rightpin 15
#define midpin 0
#define uppin 16

  int prevu,prevl,prevr,prevm;
  int r,u,m,l,four;
  int uplined,uplineu,rline,lline;
  int rightswipe, leftswipe, swipeup, swipedown;   // --------------------------cipher later wala
  int return2down,rightl,return2up,leftl,l2r,r2l;
  int touchstatus=0;
  int a[4];
  int arraypos=0;
  int c=0,sum=0;
  char X;
  char msg[15];
  String str;
  int hours,minutes;


void gettouch()                                                                          // tells that which portion of the sheild is touched
{digitalWrite(leftpin,LOW);digitalWrite(uppin,HIGH);digitalWrite(midpin,LOW);digitalWrite(rightpin,LOW);if(analogRead(0)>200) {u=1;   delay(1);}   //touch u
digitalWrite(leftpin,LOW);digitalWrite(uppin,LOW);digitalWrite(midpin,LOW);digitalWrite(rightpin,HIGH);if(analogRead(0)>200) {l=1;   delay(1);}   //touch l
digitalWrite(leftpin,HIGH);digitalWrite(uppin,LOW);digitalWrite(midpin,LOW);digitalWrite(rightpin,LOW);if (analogRead(0)>200) {r=1;  delay(1);}   //touch r
digitalWrite(leftpin,LOW);digitalWrite(uppin,LOW);digitalWrite(midpin,HIGH);digitalWrite(rightpin,LOW);if (analogRead(0)>200) {m=1;  delay(1);}   //touch m
digitalWrite(16,LOW); digitalWrite(0,LOW);  digitalWrite(15,LOW); digitalWrite(4,HIGH);      if (analogRead(0)>100)  four=1;        delay(1);  //detect touch none
}
void getswipe()  {if (prevu==1&&prevm==0&&u==1&&m==1)   swipedown=1;   // uses the previous and the current values of the sheild to determine the swipe patterns b/w consecutive portions
                  if(prevu==0&&prevm==1&&u==1&&m==1)    swipeup=1;
                  if(prevr==0&&prevm==1&&r==1&&m==1)    rightswipe=1;
                  if(prevl==0&&prevm==1&&l==1&&m==1)    leftswipe=1;}
void getpattern()
{
//____________________________________________________________________________________________
if (swipedown==1&&uplined==0) uplined=1;         /* the main one*/
if(uplined==1&&m==1&&r==1)
       {rightl=1;                                                                               //character L is made on up, middle and right sheild
       uplined=0;}
else if (uplined==1&&m==1&&l==1)
       {leftl=1;                                                                                //opposite of character L is made on up middle and left sheild
       uplined=0;}
else if (uplined==1&&swipeup==1)
        {return2up=1;                                                                              //swipedown and then swipeup is performed
        uplined=0;}
else if (r==0&&u==0&&m==0&&l==0)    uplined=0;                                                    //unload the variable for return to up

//________________________________________________________________________________________________
if(swipeup==1&&uplineu==0) uplineu=1;          /* the main two*/
if (uplineu==1&&swipedown==1)                                                                     //swipeup and swipedown is performed
  {return2down=1;
  uplineu=0;}
else if(r==0&&u==0&&m==0&&l==0)    uplineu=0;     //unload the variable for 

//__________________________________________________________________________________________________
if(prevl==1&&prevm==0&&l==1&&m==1)  lline=1;                                                         //check leftline moving left to right
if (lline==1&&rightswipe==1)
  {l2r=1;
  lline=0;}
else if(r==0&&u==0&&m==0&&l==0)    lline=0;

if(prevr==1&&prevm==0&&m==1&&r==1)  rline=1;                                                         //check rightline moving right to left
if(rline==1&& leftswipe==1)
  {r2l=1;
  rline=0;}
else if(r==0&&u==0&&m==0&&l==0)    rline=0;
//___________________________________________________________________________________________________
}
void assign()   {  prevr=r;   prevu=u;   prevl=l;   prevm=m;  }
//**************************************************************************************************************************************************************************************





void loop()
{
  Blynk.run();
  r=0,u=0,m=0,l=0,four=0;                                  //touches;
rightswipe=0, leftswipe=0, swipeup=0, swipedown=0;       //swipes;
return2down=0,return2up=0,rightl=0,leftl=0,r2l=0,l2r=0;      //patterns;
digitalWrite(13,LOW);
gettouch();
getswipe();

if (swipeup==1)      { Serial.println("swipeup");     delay(100);}
if (swipedown==1)    { Serial.println("swipedown");   delay(100);}           //just for acknowledgement
if (rightswipe==1)   { Serial.println("rightswipe");  delay(100);}
if (leftswipe==1)    { Serial.println("leftswipe");   delay(100);}
getpattern();
if (return2down==1)  {Serial.println("return to down"); digitalWrite(13,HIGH); delay(1000); digitalWrite(13,LOW);}   //__________________ready for morse
if (rightl==1)       {Serial.println("right l");         delay(1000);}
if (leftl==1)        {Serial.println("left l");          delay(1000);}
if (return2up==1)    {Serial.println("return to up");    }
if (l2r==1)          {Serial.println("left to right");   }
if (r2l==1)          {Serial.println("right to left");   delay(1000);}

if (l2r==1)
{
    for (int i=0; i<newstr.length(); i++)
  {
  impulse(newstr[i]);     //the last message recieved from the application is stored in newstr[], when swipe is done from left to right,, then it will vibrate again..
  }
}


if (return2up==1)    {timeClient.update();                //if user wants to get time
                      hours =   timeClient.getHours();
                      minutes = timeClient.getMinutes();
                      char h1= (hours/10)+48;
                      char h2= (hours%10)+48;
                      char m1= (minutes/10)+48;
                      char m2= (minutes%10)+48;
                      
                      Serial.print(hours + " ");
                      Serial.println(minutes);
                      impulse(h1);
                      delay(400);
                      impulse(h2);
                      delay(400);
                      impulse(' ');
                      delay(400);
                      impulse(m1);
                      delay(400);
                      impulse(m2);
                      delay(1000);}


while (return2down==1)
{
  l=0,r=0,m=0,u=0,touchstatus=0;
  gettouch();

    if(l==1)
      {Serial.println("signal sent");
      arraypos=0;
      Blynk.virtualWrite(V1,str);
      delay(500);
      str="";
      break;}
        
     if(prevu==0&&u==1)
      {Serial.println("dash");delay(100);
      touchstatus=11;}
     if(prevm==0&&m==1)
      {Serial.println("dot");delay(100);
      touchstatus=2;}

      
if(touchstatus==11||touchstatus==2)
   {a[arraypos]=touchstatus;
    arraypos=arraypos+1;
    if (arraypos>4) 
    {Serial.println("out of bounds");arraypos=0;}
    }

if(prevr==0&&r==1)
      {arraypos=0;
       sum=0;
       ++c;
        sum=a[3]+(a[2]*a[2])+ (a[1]*a[1]*a[1]) +(a[0]*a[0]*a[0]*a[0]);
        if(sum==1347) X='a';
        if(sum==14655) X='b';
        if(sum==14772) X='c';
        if(sum==14653) X='d';
        if(sum==16)    X='e';
        if(sum==147)   X='f';
        if(sum==15976) X='g';
        if(sum==30)    X='h';
        if(sum==24)    X='i';
        if(sum==1479)  X='j';
        if(sum==14770) X='k';
        if(sum==1353)  X='l';
        if(sum==15972) X='m';
        if(sum==14649) X='n';
        if(sum==16093) X='o';
        if(sum==1470)  X='p';
        if(sum==15987) X='q';
        if(sum==1351)  X='r';
        if(sum==28)    X='s';
        if(sum==14641) X='t';
        if(sum==145)   X='u';
        if(sum==39)    X='v';
        if(sum==1468)  X='w';
        if(sum==14664) X='x';
        if(sum==14781) X='y';
        if(sum==15978) X='z';
        
       str+=X;
       Serial.print(X);
       Serial.print("      ");
       Serial.print(sum);
       Serial.println(" waiting for next word ");
       delay(100);
       a[0]=0;  a[1]=0;  a[2]=0;  a[3]=0;}
assign();
}

assign();
    Serial.print(u);
    Serial.print(" ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print(m);
    Serial.print(" ");
    Serial.print(l);
    Serial.println(" ");
    delay(5);
}
