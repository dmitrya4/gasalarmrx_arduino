#define BitIsClear(reg, bit)    ((reg & (1<<bit)) == 0)
#define SetBit(reg, bit)          reg |= (1<<bit)           
#define ClearBit(reg, bit)       reg &= (~(1<<bit))
#define InvBit(reg, bit)          reg ^= (1<<bit)
#define BitIsSet(reg, bit)       ((reg & (1<<bit)) != 0)

#define portb_direct()             DDRB |= (1<<PORTB5)|(1<<PORTB1)|(1<<PORTB3)
#define cmd_on()                   PORTB |= (1<<PINB1);//Команда на сервер
#define cmd_off()                  PORTB &= ~(1<<PINB1);//Команда на сервер  
#define led_on()                   PORTB |= (1<<PINB5)
#define led_off()                  PORTB &= ~(1<<PINB5)
#define zummer_on()                PORTB |= (1<<PINB3); //Пищалка вкл.
#define zummer_off()               PORTB &= ~(1<<PINB3); //Пищалка выкл.

volatile float d0 = 4.8;
volatile float d1 = 0.3;
volatile float d2 = 2000;
volatile float d3 = 0.145;
volatile float d4 = 15;

int a,k,j;
char txbit1[32]={1,0,1,1,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0};
char txbit2[32]={0,1,0,0,1,1,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,0,0,1,1};
char rxdata1[32];
char rxdata2[32];
unsigned char n = 32;
int result1, result2;

void setup() {
//Направление работы порта.
 portb_direct() ; 
    
//Выкл. аналог.компаратора    
  ACSR=0x80;
              
}

void loop() {
//Видимо ждем старт-бита?   
   if(BitIsSet(PINB,2)){ 
      delay(d0);//5ms  
       //Приём битов
      for(a=0;a<32;a++){
        if(BitIsSet(PINB,2)){
          rxdata1[a] = 1;
         }
          else{
           rxdata1[a] = 0;
        }   
          delay(d1);//5ms   
      }           
          result1=memcmp(rxdata1, txbit1, n);                          
            
      for(a=0;a<32;a++){
        if(BitIsSet(PINB,2)){
          rxdata2[a] = 1;
        }
          else{
           rxdata2[a] = 0;
        }   
          delay(d1);//5ms   
      }       
          result2=memcmp(rxdata2, txbit2, n); 
                          
      if(result1==0 && result2==0){  
        cmd_on();//Команда на сервер
        delay(d2);
        cmd_off();//Команда на сервер  
        led_on();//LED ON                  
           for(k=0;k<10;k++){  
              for(j=0;j<10000;j++){
                 zummer_on(); //Пищалка вкл. 
                 delay(d3);
                 zummer_off(); //Пищалка выкл. 
                 delay(d3);
              }
           } 


     }   

  }
      led_off();//LED Off
      delay(d4);
    
}
