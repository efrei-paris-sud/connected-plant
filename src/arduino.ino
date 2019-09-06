
//Librairie qui permet à la arduino de communiqué en série sur les broches 1 et 2
#include <SoftwareSerial.h>
//Définie notre broche de communication, ici la broche 0 noté D3 sur la arduino
int PinAnalogiqueHumidite=0;   

//notre variables d'humidité sol   
int hsol;  

//défini nos broches de communication RX et TX sur les broches D2 et D3 
SoftwareSerial sw(2, 3); 

void setup(){ 
    Serial.begin(9600); 
    pinMode(PinAnalogiqueHumidite, INPUT);     
    Serial.begin(115200);
    sw.begin(115200); 


}

void loop() { 
    //lit la valeur du capteur
    hsol = analogRead(PinAnalogiqueHumidite); 

    //envoi la valeur du capteur
    sw.print("\"hsolValue\":");
    sw.print(hsol);//offset
    sw.println();
    
    //défini la frequence d'envoi en miliseconde, soit ici 10sec
    delay(10000);

}



