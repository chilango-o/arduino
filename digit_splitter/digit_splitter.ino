/*---------------------------------------------------------------
based on the original idea by Rahulkar, code extracted from instructable:
"7 Segment Digital Thermometer using ATtiny 85"
@http://www.instructables.com/id/7-Segment-Digital-Thermometer-using-ATtiny-85/

simple example of code used to "separate" or "split" the digits
in a float number, eg 123.32 -> (1-2-3-3-2), it relies on the modulo
opeartor (%) and the ability of separating the decimals from the
original number and then transform them to an integer variable so
modulo can work

My interest is to apply it when dealing with float numbers and
want to print them over a 7-segment display.
---------------------------------------------------------------*/

float num; //variable where the float number will be stored

void setup(){
  Serial.begin(9600);  //begin the Serial communication
}

void loop(){
  Serial.println("Write the number to split, it handle numbers up to xxx.xx");
  while(Serial.available()==0){} //wait for the user to  write the number in the terminal
  num=Serial.parseFloat();  //obtain the number from the terminal and handle it as a float variable
  int ones, tens, hundreds, fones, ftens; //set variable to hold the 5 expected digits (eg 123.45, hundreds-1, tens-2, ones-3, fones-4, ftens-5)
  int v=(int)num;      //get the integer value of the float num, basicly it just get the number without the decimals (eg 123)
  float diff=num-v;    //variable used to store the difference between the float number minus the integer number, it stores only the decimal numbers (eg 0.45)
  diff=diff*100;       //prepares the number for the modulo operation, to get the ftens digit (eg 45.00)
  ftens=(int)diff%10;  //gets the ftens digit using the integer of diff (eg 45%10=5)
  diff=diff/10;        //prepares de diff value to get the fones (eg 4.5)
  fones=(int)diff%10;  //gets the fones digit using the integer of diff (eg 4%10=4)
  ones=v%10;           //gets the ones digit, it uses back the integer value of the float original number (eg 123%10=3)
  tens=(v/10)%10;      //gets the tens digit by moving the decimal point un place to the left (eg (123/10)%10 = 12%10=2) remember integer variables ignore the decimals
  hundreds=v/100;      //gets the hundreds digit by moving the decimal point another place to the left (eg 123/100=1) no need for the modulo now as it just remains the wanted digit
  
  Serial.print("num= ");              //display the digits on the serial monitor
  Serial.println(num);
  Serial.print("hundreds= ");
  Serial.println(hundreds);
  Serial.print("tens= ");
  Serial.println(tens);
  Serial.print("ones= ");
  Serial.println(ones);
  Serial.print("decimal ones= ");
  Serial.println(fones);
  Serial.print("decimal tens= ");
  Serial.println(ftens);
  Serial.println("");
}
