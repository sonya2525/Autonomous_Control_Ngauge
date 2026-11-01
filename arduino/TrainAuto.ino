#define MODE 2 //自動運転モード。1は距離センサで停止。2は一定時間後停止。
#define trigPin 11
#define echoPin 12
#define LED_IN 4
#define TRAIN_IN 9
const int DIN_PIN = 2; //物理スイッチの入力ポート

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //9600baudのSerial Monitorに飛ばすおまじない
  pinMode(LED_IN, OUTPUT); //LEDの位置
  pinMode(TRAIN_IN, OUTPUT); //電車の電源位置
  pinMode(trigPin, OUTPUT);//Trigピンの電源位置
  pinMode(echoPin, INPUT);//echoピンの電源位置
  pinMode(DIN_PIN, INPUT_PULLUP);//プルアップでDIN_PINを入力ポートモードにする

  digitalWrite(LED_IN, LOW); //アウトプットピンの初期化
  digitalWrite(TRAIN_IN, LOW); //電車アウトプットピンの初期化
  digitalWrite(trigPin, LOW);  // Added this line
  digitalWrite(echoPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int switch_flag;
  long duration, distance;
  if(MODE == 1){
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    delay( 10 ); //10ms待機
    if (distance < 8){  // This is where the LED On/Off happens
      digitalWrite(LED_IN, LOW);//LEDをOFFにする
      digitalWrite(TRAIN_IN, LOW);//LEDをOFFにする
      //delay( 3000 ); //3秒待機
      //digitalWrite(LED_IN, HIGH);//LEDをONにする
      //digitalWrite(TRAIN_IN, HIGH);//電車をONにする
      //delay( 3000 ); //3秒待機
    }else{
      digitalWrite(LED_IN, HIGH);//LEDをONにする
      digitalWrite(TRAIN_IN, HIGH);//電車をONにする
    }
    if (distance >= 200 || distance <= 0){
      Serial.println("Out of range");
    }else{
      Serial.print(distance);
      Serial.println(" cm");
    }
    //delay(50);
  }else{
    switch_flag = digitalRead( DIN_PIN ); //スイッチの入力を検知する
    Serial.println( switch_flag ); //Serial Monitorに入力フラグを表示する
    delay( 100 ); //スイッチの入力において、連続入力しているようにさせない停止時間
    //スイッチが押されたor押されていない時の処理
    if(switch_flag == 1){ //スイッチが押されていない時
      digitalWrite(LED_IN, LOW);//LEDをOFFにする
      digitalWrite(TRAIN_IN, LOW);//電車をOFFにする
    }else{
      digitalWrite(LED_IN, HIGH);//LEDをONにする
      digitalWrite(TRAIN_IN, HIGH);//電車をONにする
      delay( 5000 ); //3秒待機
    }
  }
}