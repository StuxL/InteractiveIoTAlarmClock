// This #include statement was automatically added by the Particle IDE.
#include "SparkFun_MMA8452Q.h"
#include "application.h"
#include "Particle.h"

SYSTEM_THREAD(ENABLED);

os_thread_return_t detect_orientation(void*);

Thread *sensor_thread;

enum Orientation
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    FLAT
};

MMA8452Q accel;                   // create instance of the MMA8452 class

volatile Orientation current_status = FLAT;

int standing_up = 0;
int time_standing = 0;
String publish_string;

void setup() {
  Particle.variable("standingup", publish_string);
  Wire.begin();

  if (accel.begin() == false) {
    Particle.publish("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  
  sensor_thread = new Thread("OrientationThread", detect_orientation);
}

//Main timer thread
void loop() {
    //sprintf(publish_string, '''{"standing": "%d", "seconds": "%d"}''', standing_up, time_standing);
    publish_string = String( "{\"standing\":\"" + String(standing_up) + "\",\"seconds\":\"" + String(time_standing) +"\"}");
    if (current_status == LEFT || current_status == RIGHT)
    {
        if (!standing_up)
        {
            time_standing = 0;
            standing_up = 1;
        }
        time_standing++;
    }
    else
    {
        standing_up = 0;
    }
    delay(1000);
}

//Sensor reading thread
os_thread_return_t detect_orientation(void*)
{
    while (true)
    {
        if (accel.isRight() == true) 
        {
          current_status = RIGHT;
        }
        else if (accel.isLeft() == true) 
        {
          current_status = LEFT;
        }
        else if (accel.isUp() == true) 
        {
          current_status = UP;
        }
        else if (accel.isDown() == true) 
        {
          current_status = DOWN;
        }
        else if (accel.isFlat() == true) 
        {
          current_status = FLAT;
        }
        delay(500);
    }
}