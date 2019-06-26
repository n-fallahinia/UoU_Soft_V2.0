//This is a class to handle force sensor
//It start a force sensor, read it with a certain of frequency
//The reading is stored in a queue.
#ifndef FORCESENSOR_H
#define FORCESENSOR_H

#include <comedilib.h>
#include <iostream>

#define FORCE_FREQUENCY 10.0

using namespace std;

struct Reading
{
  double raw_force_signal[6];
  double force[6];
  double time;
};

class ForceSensor
{
public:
    bool flag_force_sensor;
    
    
    ForceSensor();
    void readNewData();
    void startForceSensor();
	Reading curr_force;
	
private:
	
    comedi_t *device;
    int analog_input;
    int analog_output;
    int num_inputs;
    int num_outputs;
    int channel_start;
    int channel_end; 
    int max_range;
    int counter;
    char device_name[20];
    long long int click_sec;
    
    double time_start;

    double force_offset[6];
    double voltage_offset;

    void forceOffset ( double * );
    void getOffset ();
    void voltage2Force ( double * voltage, double * force);
    void readVoltage ( double voltage[] );

};
#endif
