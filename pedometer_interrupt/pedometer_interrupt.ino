#define xpin A7
#define ypin A6
#define zpin A3
#define powerpin A2
#define gnd A0
//#define fake 3

int fake = 0;//pin 2 on arduino

float threshhold=149.0;

float xval[100]={0};
float yval[100]={0};
float zval[100]={0};
float xavg;
float yavg;
float zavg;
volatile int steps;
int flag=0;
int a = 0;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(powerpin,OUTPUT);
pinMode(powerpin,INPUT);
pinMode(gnd,OUTPUT);
digitalWrite(powerpin,HIGH);
digitalWrite(gnd,LOW);
pinMode(13,OUTPUT);

attachInterrupt(fake, pedometer, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(steps);
}

void pedometer()
{
  digitalWrite(fake, LOW);
  calibrate();
  //int a = 0;
  int acc=0;
  float totvect[100]={0};
  float totave[100]={0};
  float xaccl[100]={0};
   float yaccl[100]={0};
    float zaccl[100]={0};
    for (int i=0;i<100;i++)
{
xaccl[i]=float(analogRead(xpin));
//delay(1);



yaccl[i]=float(analogRead(ypin));
//delay(1);


zaccl[i]=float(analogRead(zpin));
//delay(1);



 totvect[i] = sqrt(((xaccl[i]-xavg)* (xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
 totave[i] = (totvect[i] + totvect[i-1]) / 2 ;
 //Serial.println(totave[i]);
 //delay(200);

if (totave[i]>threshhold && flag==0)
{
  a = steps;
  steps=steps+1;
  flag=1;
  
 
}
 else if (totave[i] > threshhold && flag==1)
{
 
}
  if (totave[i] <threshhold  && flag==1)
  {flag=0;}
 // Serial.println('\n');
  //Serial.print("steps=");
  //Serial.println(steps);
}
if(a!=steps)
{
  digitalWrite(fake, HIGH);
  }


}


void calibrate()

{

  digitalWrite(13,HIGH);
  
  float sum=0;
  float sum1=0;
  float sum2=0;
for (int i=0;i<100;i++)
{
  xval[i]=float(analogRead(xpin));

  sum=xval[i]+sum;
}
//delay(100);
xavg=sum/100.0;

Serial.println(xavg);

for (int j=0;j<100;j++)
{
yval[j]=float(analogRead(ypin));

sum1=yval[j]+sum1;
}
yavg=sum1/100.0;

Serial.println(yavg);
//delay(100);
for (int i=0;i<100;i++)
{
zval[i]=float(analogRead(zpin));

sum2=zval[i]+sum2;
}
zavg=sum2/100.0;
//delay(100);
Serial.println(zavg);

digitalWrite(13,LOW);

}
