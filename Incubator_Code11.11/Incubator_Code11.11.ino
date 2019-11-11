
              
              // libraieries       
                     
#include <DallasTemperature.h>       // installing dallasTemperature libarary makes easier to handle the data.
#include <OneWire.h>                 // include onewire. (dowload zip file then include)
#define ONE_WIRE_BUS 10              // data wire is plugged into pin 10 on arduino
#include "DHT.h"                     // 
#define DHTPIN 6                     //
#define DHTTYPE DHT22                //

              // Led pins
              
int whiteLedOptimal = 5;           // Pin White LED is connected to 5
int blueLedBelow = 3;              // Pin Blue LED is connected to 3
int redLedAbove = 4;               // Pin Red LED is connected to 4


              // peltier pins
              
int peltier4 = 7;
int peltier3 = 8;
int peltierPinB = 9;    // pulse width modulation pin to set the speed of motor connects to Arduino pin 9


              // Temperature sensor pin
              
int temp_sensor1 = 2;       // Pin DS18B20 Sensor is connected to 2


int temp_sensor2 = 6;

              // humidity sensor pin

int humidity = 6; ///////////////////////////////////

              // fan pin
              
int fan = A0;

              // Temperature control, change according to the desired temperature 
              
int lowerLimit = 25;      //define the lower threshold for the temperature
int upperLimit = 27;      //define the upper threshold for the temperature


              //heat speed, defines how rapid the cooling/heating is   
        
int heatAmount = 102;            // Set heatamount between 0-255 depending on the desired rate of heating
int coolAmount = 255;            // Set cooling between 0-255 depending on the desired rate of colling


              // variables
              
int refresh = 1000;         // ties with the dealy at the end, value determines how often temperature is read.
float temperature1 = 0;      //Variable to store the temperature in, using decimal.
float temperature2 = 0;


//////////////////////////
//// code starts here////
////////////////////////


DHT dht(DHTPIN, DHTTYPE);                   // DHT 
OneWire oneWirePin(temp_sensor1);           //One Wire Digital Temperature Sensor for DS18B20
DallasTemperature sensors(&oneWirePin);    // Dallas Temperature library allows easy temperature readings


void setup()  {

              // starts serial communication between Ardino and the software. use 9600 baud rate. this is the speed of the sent data. 
  
  Serial.begin(9600);                      
humidity = dht.readHumidity();  ////////////////

temperature2 = dht.readTemperature();
 
               //Setup the LEDS to act as outputs
               
  pinMode(redLedAbove,OUTPUT);
  pinMode(whiteLedOptimal,OUTPUT);
  pinMode(blueLedBelow,OUTPUT);


              // set up peltier pins to act as outputs 
              
  pinMode(peltierPinB, OUTPUT);    
  pinMode(peltier4, OUTPUT);
  pinMode(peltier3, OUTPUT);


              // set up fan to act as output
              
  pinMode(fan, OUTPUT);


            // Initialize the DS18B20 temperature sensor
            
  sensors.begin();
  dht.begin();  //////////////////////////////
}




void loop(){

                // temperature reading is requested 
                
  sensors.requestTemperatures();  

                // humidity reading is requested
  
  humidity = dht.readHumidity();    
  
                // temperature is obtained and printed in Celsius, only one sensor is used in this code so index is 0.
                
  temperature1 = sensors.getTempCByIndex(0);
  
  temperature2 = dht.readTemperature();    

 
                // temperature and humidity are printed
                
  Serial.println("peltier Temperature is ");
  Serial.println(temperature1);
  Serial.println(" ");

  Serial.println("room temperature is");
  Serial.println(temperature2);
  Serial.println(" ");
  
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
              
               // according the temperature reading above there are three possibilites what the code will do
               // 1. possibility: if the temperature is lower or equal to the lower limit set previously, "Below" will be printed
               
  if(temperature1 <= lowerLimit){   
    Serial.println("Below");

              // blue led will lit, red and white led will be off
            
    digitalWrite(blueLedBelow, HIGH);
    digitalWrite(redLedAbove, LOW);
    digitalWrite(whiteLedOptimal, LOW);

              // peltier pin 3 will be active and peltier pin 4 will be inactive causing peltier to heat up
   
    digitalWrite(peltier3,HIGH);              
    digitalWrite(peltier4,LOW);

              // previously set heat amount will be initialized 
              
    analogWrite(peltierPinB,heatAmount);

              // Heating up will be printed

    analogWrite(fan,255);
              
    Serial.println("Heating up");  
   
  }


              // 2. possibility: if temperature within the set upper and lower temperature limits; "Optimal" will be printed
              
  else if(temperature1 > lowerLimit && temperature1 < upperLimit){  
    Serial.println("Optimal");

              // White led will be actve, red and blue led will be off
   
    digitalWrite(whiteLedOptimal, HIGH);
    digitalWrite(redLedAbove, LOW);
    digitalWrite(blueLedBelow, LOW);

              // Both peltier pins will be off so no heating nor cooling will take place
   
    digitalWrite(peltier3,LOW);              
    digitalWrite(peltier4,LOW);

              // "Heating off" will be printed

    analogWrite(fan,255);
    
    Serial.println("Heating off");
   
  }


              // 3. possibility: if the temperature will be equal or above the set upper limit "Above" will be printed Fan speed will vary depending on temperature
                         
              
  else if(temperature1 >= upperLimit){  
    Serial.println("Above");

              // Red led will be active, white and blue leds will be off
   
    digitalWrite(redLedAbove, HIGH);
    digitalWrite(whiteLedOptimal, LOW);
    digitalWrite(blueLedBelow, LOW);

              // Peltier 4 will be active and peltier 3 will be inactive. Causing the peltier element to initilaize colling.
   
    digitalWrite(peltier3,LOW);              
    digitalWrite(peltier4,HIGH);

              // previously set cool amount will be initialized
    
    analogWrite(peltierPinB,coolAmount);  

              // to assist cooling fan will be turned on at 20%
    
    analogWrite(fan,255);

              // "Cooling down" will be printed
    
    Serial.println("Cooling down");
    Serial.println("Fan speed at 20%");

  }

              //////////////////////////////Fan speed at 40%

    //else if(temperature1 >= 31){  
    //Serial.println("Above");

              // Red led will be active, white and blue leds will be off
   
    //digitalWrite(redLedAbove, HIGH);
    //digitalWrite(whiteLedOptimal, LOW);
    //digitalWrite(blueLedBelow, LOW);

              // Peltier 4 will be active and peltier 3 will be inactive. Causing the peltier element to initilaize colling.
   
    //digitalWrite(peltier3,LOW);              
    //digitalWrite(peltier4,HIGH);

              // previously set cool amount will be initialized
    
    //analogWrite(peltierPinB,coolAmount);  

              // to assist cooling fan will be turned on at 40%
    
    //analogWrite(fan,102);

              // "Cooling down" will be printed
    
    //Serial.println("Cooling down");
   //Serial.println("Fan speed at 40%");


    //}
             
              //Fan speed at 60%

        //else if(temperature1 >= 33){  
    //Serial.println("Above");

              // Red led will be active, white and blue leds will be off
   
    //digitalWrite(redLedAbove, HIGH);
    //digitalWrite(whiteLedOptimal, LOW);
    //digitalWrite(blueLedBelow, LOW);

              // Peltier 4 will be active and peltier 3 will be inactive. Causing the peltier element to initilaize colling.
   
    //digitalWrite(peltier3,LOW);              
    //digitalWrite(peltier4,HIGH);

              // previously set cool amount will be initialized
    
    //analogWrite(peltierPinB,coolAmount);  

              // to assist cooling fan will be turned on 60%
    
    //analogWrite(fan,153);

              // "Cooling down" will be printed
    
    //Serial.println("Cooling down");
    //Serial.println("Fan speed at 60%");

        //}
            //Fan speed at 80%
    
        //else if(temperature1 >= 35){  
    //Serial.println("Above");

              // Red led will be active, white and blue leds will be off
   
    //digitalWrite(redLedAbove, HIGH);
    //digitalWrite(whiteLedOptimal, LOW);
    //digitalWrite(blueLedBelow, LOW);

              // Peltier 4 will be active and peltier 3 will be inactive. Causing the peltier element to initilaize colling.
   
    //digitalWrite(peltier3,LOW);              
    //digitalWrite(peltier4,HIGH);

              // previously set cool amount will be initialized
    
    //analogWrite(peltierPinB,coolAmount);  

              // to assist cooling fan will be turned on at 80%
    
    //analogWrite(fan,200);

              // "Cooling down" will be printed
    
    //Serial.println("Cooling down");
    //Serial.println("Fan speed at 80%"); 

        //}   
              //Fan speed at 100%


            //else if(temperature1 >= 37){  
    //Serial.println("Above");

              // Red led will be active, white and blue leds will be off
   
    //digitalWrite(redLedAbove, HIGH);
    //digitalWrite(whiteLedOptimal, LOW);
    //digitalWrite(blueLedBelow, LOW);

              // Peltier 4 will be active and peltier 3 will be inactive. Causing the peltier element to initilaize colling.
   
    //digitalWrite(peltier3,LOW);              
    //digitalWrite(peltier4,HIGH);

              // previously set cool amount will be initialized
    
    //analogWrite(peltierPinB,coolAmount);  

              // to assist cooling fan will be turned on at 100%
    
    //analogWrite(fan,255);

              // "Cooling down" will be printed
    
    //Serial.println("Cooling down");
    //Serial.println("Fan speed at 100%");


   
  //}

              //defines how often the temperature reading is carried out. can be changed at the variables
 
  delay(refresh); 
   } 




   
