// #include <SoftwareSerial.h>
// char val; 
// int txPIN = 18;
// int rxPIN = 19;
// SoftwareSerial mySerial (rxPIN, txPIN);
// // mySerial 用戶自行定義序列名稱
// // rxPin 序列接收腳位，txPin 序列傳送腳位
// SoftwareSerial BT (18, 19); // 自行訂序列名稱「BT」
// // 設定 Arduino 第 10 腳位接收，第11 腳位傳送
// // Arduino rx 接 BT TXD, Arduino tx 接 BT RXD

// void setup () {
// Serial.begin (9600);
// BT.begin(9600);
// }

// void loop() {
//   // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
//   if (Serial.available()) {
//     val = Serial.read();
//     Serial.print(val);
//     BT.print(val);
//   }

//   // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
//   if (BT.available()) {
//     val = BT.read();
//     Serial.print(val);
//   }
// }
char val;  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT begin!");

  // 設定藍牙模組的連線速率
  // 如果是HC-05要進AT mode，請改成38400
  // 一般模式都是9600!!
  // 18TX 19RX
  Serial1.begin(9600);
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    Serial1.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial1.available()) {
    val = Serial1.read();
    Serial.print(val);
  }
}
