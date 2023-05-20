#include <WiFi.h>
#include "esp_camera.h"
#include <base64.h>

// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid = "";
const char* password = "";

//=============================
// SERVER IP AND PORT
//=============================
const uint16_t port = 8080; // unsigned 16 bit integer
const char* host = "192.168.0.75";
camera_fb_t* fb = NULL; // Set frame buffer pointer


//=============================
// CAMERA PINS
//=============================
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
//==============================


//=============================
// Connect to Network
//=============================
void setup()
{
  Serial.begin(115200); // listen on baud

  // connect to wifi 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

//=============================
// CAMERA CONFIG SETUP
//=============================
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;

//config.frame_size = FRAMESIZE_UXGA; // set image res to 1600x1200

  config.pixel_format = PIXFORMAT_JPEG; // for streaming and image type ?
//=============================

//=============================
// SELECT QUALITY
//=============================
// if 4MB extra ram is present else use lower frame size
if (psramFound()){
  config.frame_size = FRAMESIZE_UXGA; // set image res to 1600x1200
  config.jpeg_quality = 10; // lower number = higher quality 10-63
  config.fb_count = 2; // frame buffer 
} else {
  config.frame_size = FRAMESIZE_SVGA; // set image res to 800x600
  config.jpeg_quality = 12; // lower number = higher quality 10-63
  config.fb_count = 1; // frame buffer 
  }

//=============================
// INITIALISE CAMERA
//=============================
esp_err_t err = esp_camera_init(&config);
if (err != ESP_OK) {
  Serial.printf("Camera init failed with error 0x%x", err);
  return;
  } else {
    Serial.println("Camera Ready!");
  }
}

void loop()
{
  WiFiClient client; 

  if (!client.connect(host, port)){
    Serial.println(" Connection failed");
    delay(4000);
    return;
  }

  Serial.println("Connected to server");
  
  //client.print("hello from Sails");

  fb = esp_camera_fb_get(); // take an image and save to buffer
  if(!fb){
    Serial.println("Image capture failed");
    return;
  } else {
    Serial.println("Image capture successful!");
  }

  //const char* imageData = (const char*)fb->buf; // get data from frame buffer
  // size_t size = fb->len; // size of image
  // Serial.println(size);
  
  String encodedImage = base64::encode(fb->buf, fb->len);
  Serial.println(encodedImage);
  
  client.print(encodedImage); // send image data + length of data -- research more on function 
  // can also do a time stamp to avoid doing it server side?
  esp_camera_fb_return(fb); // clear buffer

  String response = client.readString();
  Serial.println(response);

  Serial.println("Disconnecting");
  client.stop();

  delay(15000);
}
