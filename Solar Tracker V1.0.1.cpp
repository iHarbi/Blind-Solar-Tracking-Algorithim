
  
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Servo.h>
 float B, EOT, Solar_time, Decimal_hours, HAng_rad, delay_NIGHT_t_SEC, hours, minutes, Phay, Alpha, DeltaDEG, DeltaRad, Day_length, Limit_hour,PhayDgr,AlphaDgr,Null;
  int n,i,INTPHAYDGREE;
  float PII=3.1415926535897932384626433832795;
  float hour_LT,minutes_LT,longdeg,latdeg,longrad,latrad;
  Servo ServoV;
  Servo ServoH;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.print("=========------------------------=========\n");
  Serial.print("SERVO ZERO INTIALIZAION:\n");
ServoV.attach(9);
ServoH.attach(10);

ServoV.write(0);
ServoH.write(0);
  Serial.print("SERVO INITIALIZED\n");
  delay(10000);

  hour_LT = 15.; /*Hour--> CLOCK TIME*/
  minutes_LT = 9.;  /*Minute--> CLOCK TIME*/
  longdeg = 31.381523; /*Latitude and longitude coordinates*/
  latdeg =  31.037933 ; /*Latitude and longitude coordinates*/
  longrad = (longdeg * PII) / 180.;
  latrad = (latdeg * PII) / 180.;
  /*n==> DAY Number , i==> LOOP intger */
  n =359;

  Decimal_hours = hour_LT + minutes_LT / 60.; /*Decimal= CLOCK TIME*/
  B = ((2 * PII / 364.) * (n - 81)); /*RADIAN B*/
  EOT = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B); /*MINUTES OUTPUT*/
  Solar_time = Decimal_hours + ((-4 * (30. - 31.381523) + EOT) / 60.); /*Mansoura lies EAST cairo*/ /*-4(31.240967-31.381523)/60=.0087902*/

  
}

void loop() {
  Serial.print("=========------------------------=========\n");
  Serial.print("longrad:\n");
  Serial.print(longrad);
  Serial.print("=============\n");
    Serial.print("latrad:\n");
  Serial.print(latrad);
  Serial.print("------------\n");
  Serial.print("Decimal_hours=\n");
  Serial.print(Decimal_hours);
Serial.print("--------------\n");
  Serial.print("EOT\n");
  Serial.print(EOT);
  Serial.print("--------------\n");
  Serial.print("Solar Time \n");
  Serial.print(Solar_time);
  Serial.print("--------------\n");

  /*Correction of  relation to calcualte Solar Time is Required*/

  for (i = n; i <= 365; i++) {
    
    Decimal_hours = Solar_time;
    
     Serial.print("OUTER LOOP Decimal_hours  \n" );
     Serial.print(Decimal_hours);
     Serial.print("--------------\n");

  Serial.print("ith Day Of The year =\n");
  Serial.print(i);
  Serial.print("--------------\n");


    DeltaDEG = 23.4500000 * sin((360. / 365.) * (i + 284) * (PII/180.));
    
    Serial.print("OUTER LOOP Delta\n" );
    Serial.print(DeltaDEG);
    Serial.print("--------------\n");
    
    DeltaRad = DeltaDEG * (PII / 180.);
    
        Serial.print("OUTER LOOP DeltaRAD\n" );
        Serial.print(DeltaRad);
        Serial.print("--------------\n");

        
    Day_length = (2. / 15.) * (acos(-tan(latrad) * tan(DeltaRad))) * (180. / PII);
    Limit_hour = Day_length / 2;
    Serial.print("DAYlengh=\n");
    Serial.print(Day_length);
    Serial.print("--------------\n");
        Serial.print("Limit_hour=\n");
    Serial.print(Limit_hour);
    Serial.print("--------------\n");


    if (Decimal_hours < 12.) {
      while ((12. - Decimal_hours) < Limit_hour) {
        HAng_rad = (-1. / 4.) * ((12.-Decimal_hours) * 60.) * (PII / 180.);
        Serial.print("Hour Angle Dgr =\n");
        Serial.print(HAng_rad*(180./PII));
        Serial.print("--------------\n");
        
        Alpha = asin(sin(latrad) * sin(DeltaRad) + cos(latrad) * cos(DeltaRad) * cos(HAng_rad)); /*Radian output */
        ServoH.write((Alpha*180./PII));
        Phay = asin((cos(DeltaRad) * sin(HAng_rad)) / (cos(Alpha)));
            Serial.print("Alpha=\n");
            Serial.print(Alpha*(180./PII));
            Serial.print("--------------\n");
            Serial.print("Phay");
            Serial.print(Phay*(180./PII)); 
            Serial.print("--------------\n");
            PhayDgr=Phay*(180./PII);

                Serial.print("--------ENTERING PHAY LOOP------\n");
            if ( PhayDgr < 0. && PhayDgr < -90. ) 
            {
              
              ServoV.write(180);
            Serial.print("Phay Correction <-90&&<0. \n");
            Serial.print("SERVO ANGLE IS 180"); 
            Serial.print("--------------\n");
            }
              else if ( PhayDgr > 0. && PhayDgr > 90. )
              {
                Serial.print("Phay Correction >90&&>0. \n");
            Serial.print("SERVO ANGLE IS 0"); 
            Serial.print("--------------\n");
            ServoV.write(0);
            }
                
                else if (PhayDgr > 0.)
                {
                   Serial.print("Phay Correction >0. \n");
                   Serial.print("SERVO ANGLE IS at"); 
                  Serial.print("--------------\n");
                  Serial.print(180-abs((int)round(PhayDgr)));
                  ServoV.write(180-abs((int)round(PhayDgr)));
                  
            Serial.print(Phay*(180./PII)); 
            Serial.print("--------------\n");
            }
                  else if (PhayDgr<0.){
           Serial.print("Phay Correction <0. \n");
             Serial.print("SERVO ANGLE IS at"); 
             Serial.print("--------------\n");            
            Serial.print(abs((int)round(PhayDgr))); 
            Serial.print("--------------\n");
            Serial.print("SERVO ANGLE IS 90+PAHY\n "); 
                    ServoV.write(abs((int)round(PhayDgr)));
                    }
                    

      Serial.print("--------EXITING PHAY LOOP------\n");



        
        /*SERVO ATTACHED ANGELS*/
    
        
        HAng_rad = HAng_rad + (1. / 24.) * (PII / 180.);
        Serial.print("Hour Angle Dgr NEW =\n");
        Serial.print(HAng_rad*(180./PII));
        Serial.print("--------------\n");
        Decimal_hours = Decimal_hours + (1. / 360.); /*10 Seconds Based Angles UPDATE*/
      Serial.print("Decimal_hours NEW \n" );
     Serial.print(Decimal_hours);
     Serial.print("--------------\n");


        
        delay(10000);
        
      }
    }
    else if (Decimal_hours == 12.) {
      while (Decimal_hours == 12.) {
        /*ZERO  hour angle*/
        Alpha = asin(sin(latrad) * sin(DeltaRad) + cos(latrad) * cos(DeltaRad));
        Phay = asin((cos(DeltaRad)) / (cos(Alpha)));
        /*SERVO ATTACHED ANGELS*/
       
         
        HAng_rad = HAng_rad + (1. / 24.) * (PII / 180.);
        Decimal_hours = Decimal_hours + (1. / 360.); /*10 Seconds Based Angles UPDATE*/
        delay(10000);

      }
    }
    else if (Decimal_hours > 12.) {
      while ((Decimal_hours - 12.) < Limit_hour) {
        HAng_rad = (1. / 4.) * ((Decimal_hours-12.) * 60.) * (PII / 180.);
                Serial.print("Hour Angle Dgr =\n");
        Serial.print(HAng_rad*(180./PII));
        Serial.print("--------------\n");
        
        Alpha = asin(sin(latrad) * sin(DeltaRad) + cos(latrad) * cos(DeltaRad) * cos(HAng_rad)); /*Radian output */  
        ServoH.write(180.-Alpha*180./PII);     
        Phay = asin((cos(DeltaRad) * sin(HAng_rad)) / (cos(Alpha)));
        PhayDgr=Phay*(180./PII);
        INTPHAYDGREE=(int) PhayDgr;
            Serial.print("Alpha=\n");
            Serial.print(Alpha*(180./PII));
            Serial.print("--------------\n");
            Serial.print("Phay");
            Serial.print(Phay*(180./PII)); 
            Serial.print("--------------\n");


            
        /*SERVO ATTACHED ANGELS*/


 Serial.print("--------ENTERING PHAY LOOP------\n");
            if ( PhayDgr < 0. && PhayDgr < -90. ) 
            {
              
            ServoV.write(180);
            Serial.print("Phay Correction <-90 \n");
            Serial.print("SERVO ANGLE IS 180"); 
            Serial.print("--------------\n");
            }
              else if ( PhayDgr > 0. && PhayDgr > 90. )
              {
            Serial.print("Phay Correction >90 \n");
            Serial.print("SERVO ANGLE IS 0"); 
            Serial.print("--------------\n");
            ServoV.write(0);
            
            }
                
                else if (PhayDgr > 0.)
                {
                    Serial.print("Phay Correction >0. \n");
                    Serial.print("SERVO ANGLE IS at"); 
                    Serial.print("--------------\n");
                    Serial.print(180-abs((int)round(PhayDgr)));
                    ServoV.write(180-abs((int)round(PhayDgr)));
                  
                    
                    Serial.print("--------------\n");
            }
                  else if (PhayDgr<0.){
            Serial.print("Phay Correction <0. \n");
             Serial.print("SERVO ANGLE IS at"); 
             Serial.print("--------------\n");            
            Serial.print(abs((int)round(PhayDgr))); 
            Serial.print("--------------\n");
            Serial.print("SERVO ANGLE IS 90+PAHY\n "); 
                    ServoV.write(abs((int)round(PhayDgr)));
                    }
                    
 Serial.print("--------EXITING PHAY LOOP------\n");



     
         
        HAng_rad = HAng_rad + (1. / 24.) * (PII / 180.);
        Decimal_hours = Decimal_hours + (1. / 360.); /*10 Seconds Based Angles UPDATE*/
        delay(10000);
      }

    }
    /*TIME DELAY ALL NIGHT */
             Serial.print("-------WAITING FOR NEW DAY-------\n");
    delay_NIGHT_t_SEC = 2. * (12. - Limit_hour) * 3600.;
              Serial.print("--------------\n");
              Serial.print(delay_NIGHT_t_SEC);
              Serial.print("--------------\n");
       Null=round(delay_NIGHT_t_SEC);
              Serial.print("--------------\n");
              Serial.print(Null);
           
     Decimal_hours=(12.-Limit_hour)+0.1;
     Solar_time=Decimal_hours;
                Serial.print("----------I+1 DAY DECIMAL HOURS AT SUN RISE----\n");
                Serial.print(Decimal_hours);
                Serial.print("----------I+1 DAY SOLAR HOURS AT SUN RISE----\n");
               Serial.print(Solar_time);
                Serial.print("--------------\n");
    HAng_rad = (-1. / 4.) * ((12.-Decimal_hours) * 60.) * (PII / 180.);
    
               Serial.print("--------HOUR ANGLE IN RAD------\n");
                Serial.print(HAng_rad);
                Serial.print("--------------\n");

    delay((int) Null);
               Serial.print("------FINISH WAITING--------\n");
    //SETINNG HOUR ANGLE <SOLAR TIME <DECIMAL HOUR 
 
    
    

/*Don't Forget to set the New value of n+1 Day 
and Serial Print of OUTPUT to verify the values */














  }



}
