#ifndef MAGLEVCONTROL_H
#define MAGLEVCONTROL_H

#include "ml_api.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ForceSensor.h"
#include "maglev_parameters.h"

#define SAVE_FORCE_COLS 67
#define SAVE_FORCE_DATA 400000
#define NUM_TRANSITIONS 1000
#define MAGLEV_FREQUENCY 10.0

class MaglevControl
{
public:
        // Arrays of current gains to use in controllers
	double current_force_gains[6][3];
	double current_position_gains[6][4];
	double current_internal_gains[6][4];
	bool force_control_directions[6];
	
	double current_position[6];
	double desired_force[6];
        double desired_position[6];
	double control_freq;
	bool flag_maglev_start;
	bool flag_force_control_start;
	
	MaglevControl();
	~MaglevControl();
	
	void maglevConnect (  );
	void maglevClearError (  );
	void maglevTakeOff ( bool thumb );
	void maglevLand (  );
	void maglevTurnOff ( );
	
	void maglevReadPositionGain(double [6][4]);
	void maglevGetInternalGains();
	void maglevSetInternalGains();
	//void maglevSetForceGain( double * gains);
	float maglevGetFrequency( );
	void maglevSetFrequency( int f );
	void maglevGetSpeed ( double * speed );
	void maglevSetForce ( double * new_force );
	
	void maglevStartForceController();
	void maglevStopForceController();
	void maglevController ( Reading curr_force);
	//Tom This is what the above line used to say
	//void maglevController (  double * , double * );
	void maglevSaveGains();
	
	void maglevSaveForce();
	void maglevStopSaveForce();
	void maglevPrintGainMatrices();
	void maglevGetPosition();
private:
	// Arrays of gains to achieve after transitions
	double desired_force_gains[6][3];
	double desired_position_gains[6][4];
	double desired_internal_gains[6][4];
	
	double gain_scale;
	double position_old[6];
	double integral[6];
        double currents[6];
        double temperature[6];
        double raw_force_signal[6];
        double maglev_force[6];
	ml_device_handle_t maglev_handle;
	ml_gainset_type_t mp_gain_type;
	ml_fault_t current_fault;
	ml_gain_vec_t gain_vec;
        
	char force_gain_file_name[20];
	
	// Parameters for the low-pass velocity filter
	double alpha;
	double tau;
	double cutoff_frequency;
	
	//long long int *save_force_data;
	double save_force_data[SAVE_FORCE_DATA][SAVE_FORCE_COLS];
	bool flag_save_force;
	int save_force_counter;
	FILE *save_force_file;
	long long int click_per_sec;
	
	void maglevInitGains();
	//int tick_callback_handler( ml_device_handle_t, ml_position_t * );	
	int maglevMove2Position ( double * new_position );
	void maglevGetForce();
	void maglevGetCurrent();
	void maglevGetTemperature();
	inline double minValue(double my_array[6]);
	void maglevCompensateForGravity();
	void maglevGetGravityVector(double gravity[DATA_SIZE]);
};

#endif
