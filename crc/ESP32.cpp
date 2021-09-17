//Firmware of ESP32



String rcvd;
String poly = "1011";
unsigned int poly_len;
unsigned int rcvd_len;
int crc(void);
void setup() {
Serial.begin(9600); // initialize UART with baud rate of 9600 bps
poly_len = poly.length();
}
void loop() {
if(Serial.available()) {
rcvd = Serial.readString();// read one byte from serial buffer and save to
rcvd_len = rcvd.length();
if(crc()){
Serial.write("OK");
}
else{
Serial.write("ERR");
}
}
}
int crc(void){
char rcvd_data[30];
rcvd.toCharArray(rcvd_data, 30);
for (int i = 0; i < rcvd_len; i++) {
if (rcvd_data[i] == '1') {
for (int j = 0; j < poly_len; j++) {
if (rcvd_data[i + j] == poly[j])
rcvd_data[i + j] = '0';
else
rcvd_data[i + j] = '1';
}
}
}
for (int i = 0; i < strlen(rcvd_data); i++){
if (rcvd_data[i] == '1'){
return 0;}
}
return 1;
}
