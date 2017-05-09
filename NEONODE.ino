#include <FS.h>
#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define TRIGGER_PIN 16
//json
bool shouldSaveConfig = false;


char mqtt_server[20];
char mqtt_port[20] = "8080";
char blynk_token[20] = "YOUR_BLYNK_TOKEN";
char mqtt_pass[20] = "YOUR MQTT PASSWORD";
//json
// Connect to the WiFi
const char* ssid = "ZeeWifi";
const char* password = "9270268";
const char* accusrname = "Your user ID";
const char* accpw = "Your Password";
int incomingByte = 0;   // for incoming serial data
int value = 1;
WiFiClient espClient;
PubSubClient client(espClient);
const byte interruptPin = 14;
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;
const byte ledPin = 13; // Pin with LED on Adafruit Huzzah
String uid = "";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 4, NEO_GRB + NEO_KHZ800);

const uint8_t PROGMEM gamma8[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void saveConfigCallback () {
	Serial.println("Should save config");
	shouldSaveConfig = true;
}


void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	
	if (strcmp(topic, "ledStatus") == 0) {
		// whatever you want for this topic
		//	char outchar;
		//	for (int i = 0; i < length; i++) {
		//		int receivedChar = (int)payload[i];
		//		Serial.println(topic);
		//		Serial.println(receivedChar);
		//		outchar = outchar + receivedChar;
		//		if (receivedChar == '0') {
		//			// ESP8266 Huzzah outputs are "reversed"
		//			digitalWrite(4, HIGH);
		//
		//			} else {
		//
		//			digitalWrite(4, LOW);
		//
		//		}
		//
		//
		//	}
		char message[length + 1];
		for (int i = 0; i < length; i++) {
			message[i] = (char)payload[i];
		}
		message[length] = '\0';
		Serial.println("after for : ");
		Serial.println(message);
		Serial.println();
		String anvalstr = message;
		Serial.println(anvalstr);
		Serial.println();
		int anval =  anvalstr.toInt();
		Serial.println(anval);
		analogWrite(4,anval);
		
	}
	if (strcmp(topic, "ledStatus1") == 0) {
		//	for (int i = 0; i < length; i++) {
		//		char receivedChar = (char)payload[i];
		//		Serial.println(topic);
		//		Serial.println(receivedChar);
		//
		//		if (receivedChar == '0') {
		//			// ESP8266 Huzzah outputs are "reversed"
		//			digitalWrite(ledPin, HIGH);
		//
		//			} else {
		//			digitalWrite(ledPin, LOW);
		//			Serial.println();
		//		}
		//	}
		char message[length + 1];
		for (int i = 0; i < length; i++) {
			message[i] = (char)payload[i];
		}
		message[length] = '\0';
		Serial.println("after for : ");
		Serial.println(message);
		Serial.println();
		String anvalstr = message;
		Serial.println(anvalstr);
		Serial.println();
		int anval =  anvalstr.toInt();
		Serial.println(anval);
		analogWrite(ledPin,anval);
		
	}
	if (strcmp(topic, "ledStatus2") == 0) {
		//	for (int i = 0; i < length; i++) {
		//		char receivedChar = (char)payload[i];
		//		Serial.println(topic);
		//		Serial.println(receivedChar);
		//
		//		if (receivedChar == '0') {
		//			// ESP8266 Huzzah outputs are "reversed"
		//			digitalWrite(15, HIGH);
		//
		//			} else {
		//			digitalWrite(15, LOW);
		//			Serial.println();
		//		}
		//	}
		char message[length + 1];
		for (int i = 0; i < length; i++) {
			message[i] = (char)payload[i];
		}
		message[length] = '\0';
		Serial.println("after for : ");
		Serial.println(message);
		Serial.println();
		String anvalstr = message;
		Serial.println(anvalstr);
		Serial.println();
		int anval =  anvalstr.toInt();
		Serial.println(anval);
		analogWrite(15,anval);
		
	}
	if (strcmp(topic, "rgbval") == 0) {
		//	for (int i = 0; i < length; i++) {
		//		char receivedChar = (char)payload[i];
		//		Serial.println(topic);
		//		Serial.println(receivedChar);
		//
		//		if (receivedChar == '0') {
		//			// ESP8266 Huzzah outputs are "reversed"
		//			digitalWrite(15, HIGH);
		//
		//			} else {
		//			digitalWrite(15, LOW);
		//			Serial.println();
		//		}
		//	}
		char message[length + 1];
		for (int i = 0; i < length; i++) {
			message[i] = (char)payload[i];
		}
		message[length] = '\0';
		Serial.println("after for : ");
		Serial.println(message);
		Serial.println();
		String anvalstr = message;
		Serial.println(anvalstr);
		long number = (long) strtol( &anvalstr[1], NULL, 16);
		int r = number >> 16;
		int g = number >> 8 & 0xFF;
		int b = number & 0xFF;
		
		int rg = pgm_read_byte(&gamma8[r]);
		Serial.print("red is ");
		analogWrite(ledPin,rg);
		Serial.println(r);
		Serial.println("--r---rg--");
		Serial.println(rg);
		
		Serial.print("green is ");
		int gg = pgm_read_byte(&gamma8[g]);
		analogWrite(15,gg);

		Serial.println(g);
		Serial.println("--r---gg--");
		Serial.println(gg);
		Serial.print("blue is ");
		int bg = pgm_read_byte(&gamma8[b]);
		analogWrite(4,bg);
		Serial.println(b);
		Serial.println("--r---bg--");
		Serial.println(bg);
		int anval =  anvalstr.toInt();
		
colorset(strip.Color(rg, gg, bg));
		
		
	}
}


void reconnect() {

	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		wifiap();
		
		// Attempt to connect
		if (client.connect("ESP8266 Client")) {
			Serial.println("connected");
			// ... and subscribe to topic
			client.subscribe("ledStatus");
			client.subscribe("ledStatus1");
			client.subscribe("ledStatus2");
			client.subscribe("rgbval");
			} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());

			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
			
		}
	}
}
void handleInterrupt() {
	
	interruptCounter++;
}
void wifiap(){
	
	if (!interruptCounter == 0) {
		interruptCounter = 0;
		noInterrupts();
		Serial.println("Pin Triggered Going to ApOnDemand");
		Serial.println("@crlf");
		//WiFiManager
		//Local intialization. Once its business is done, there is no need to keep it around
		WiFiManager wifiManager;

		//reset settings - for testing
		//wifiManager.resetSettings();

		//sets timeout until configuration portal gets turned off
		//useful to make it all retry or go to sleep
		//in seconds
		wifiManager.setTimeout(120);
		WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 20);
		WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 20);
		WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 20);
		//
		wifiManager.addParameter(&custom_mqtt_server);
		wifiManager.addParameter(&custom_mqtt_port);
		wifiManager.addParameter(&custom_blynk_token);
		//wifiManager.addParameter(&wusername);
		//wifiManager.addParameter(&wpassword);
		//it starts an access point with the specified name
		//here  "AutoConnectAP"
		//and goes into a blocking loop awaiting configuration

		//WITHOUT THIS THE AP DOES NOT SEEM TO WORK PROPERLY WITH SDK 1.5 , update to at least 1.5.1
		WiFi.mode(WIFI_STA);

		if (!wifiManager.startConfigPortal("OnDemandAP")) {
			Serial.println("failed to connect and hit timeout");
			delay(3000);
			//reset and try again, or maybe put it to deep sleep
			ESP.reset();
			delay(5000);
		}
		//
		
		//if you get here you have connected to the WiFi
		Serial.println("connected...yeey :)");
		
		strcpy(mqtt_server, custom_mqtt_server.getValue());
		strcpy(mqtt_port, custom_mqtt_port.getValue());
		strcpy(blynk_token, custom_blynk_token.getValue());
		
		Serial.println("saving config");
		DynamicJsonBuffer jsonBuffer;
		JsonObject& json = jsonBuffer.createObject();
		json["mqtt_server"] = mqtt_server;
		json["mqtt_port"] = mqtt_port;
		json["blynk_token"] = blynk_token;

		File configFile = SPIFFS.open("/config.json", "w");
		if (!configFile) {
			Serial.println("failed to open config file for writing");
		}

		json.printTo(Serial);
		json.printTo(configFile);
		configFile.close();
		//end save
		

		//epwriteid(wusername.getValue());
		//epwritepw(wpassword.getValue());
		interrupts();
	}
	
}


void bindi(int period){
	for (int bcount = 0; bcount <= period; ++bcount )
	{
		delay(5);
		digitalWrite(2,HIGH);
		delay(95);
		digitalWrite(2,LOW);
	}
}
void setup()
{

	Serial.begin(9600);
	
	Serial.println("mounting FS...");

	if (SPIFFS.begin()) {
		Serial.println("mounted file system");
		if (SPIFFS.exists("/config.json")) {
			//file exists, reading and loading
			Serial.println("reading config file");
			File configFile = SPIFFS.open("/config.json", "r");
			if (configFile) {
				Serial.println("opened config file");
				size_t size = configFile.size();
				// Allocate a buffer to store contents of the file.
				std::unique_ptr<char[]> buf(new char[size]);

				configFile.readBytes(buf.get(), size);
				DynamicJsonBuffer jsonBuffer;
				JsonObject& json = jsonBuffer.parseObject(buf.get());
				json.printTo(Serial);
				if (json.success()) {
					Serial.println("\nparsed json");

					strcpy(mqtt_server, json["mqtt_server"]);
					strcpy(mqtt_port, json["mqtt_port"]);
					strcpy(blynk_token, json["blynk_token"]);

					} else {
					Serial.println("failed to load json config");
				}
			}
		}
		} else {
		Serial.println("failed to mount FS");
	}
	
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
	pinMode(15, OUTPUT);
	pinMode(ledPin, OUTPUT);
	pinMode(4,OUTPUT);
	bindi(10);
	
	bindi(5);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
strip.begin();
strip.show(); // Initialize all pixels to 'off'
colorset(strip.Color(25, 10, 0));
strip.show();
}

void colorset(uint32_t c) {
	for(uint16_t i=0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(250);
	}
}

void loop()
{

	if (!client.connected()) {
		
		reconnect();

	}
	client.loop();
	wifiap();
	
	
	if (Serial.available() > 0) {
		// read the incoming byte:
		incomingByte = Serial.read();

		// say what you got:

	}
}
