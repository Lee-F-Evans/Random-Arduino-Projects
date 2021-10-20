
void Motor1(String x){
  if(x == "FWD"){
    digitalWrite(EN1,HIGH);
    digitalWrite(EN2,LOW);
    }else if(x == "RVS"){
    digitalWrite(EN1,LOW);
    digitalWrite(EN2,HIGH);
    } else {
    digitalWrite(EN1,LOW);
    digitalWrite(EN2,LOW);  
    }  
}

void Motor2(String x){
  if(x == "FWD"){
    digitalWrite(EN3,HIGH);
    digitalWrite(EN4,LOW);
    }else if(x == "RVS"){
    digitalWrite(EN3,LOW);
    digitalWrite(EN4,HIGH);
    } else {
    digitalWrite(EN3,LOW);
    digitalWrite(EN4,LOW);  
    }
  }
