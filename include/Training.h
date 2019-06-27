#ifndef __TRAINING_H_
#define __TRAINING_H_

#define TRAINING_FREQUENCY 10.0

class Training
{
public:
	float *traj[6];
	float desired_force[6];
	int current_count;
	int max_count;
	
	int ramp_count;
	int ramp_max;
	int hold_count;
	int hold_min;
	
	// Determines the trajectory type using a bitwise notation
	//      Each bit corresponds to a direction, in the order:
	//              [x y z rot-x rot-y rot-z]
	//      100000 corresponds to x-direction force control with position
	//              control in all other directions
	//      111000 corresponds to translational force control with
	//              rotational position control
	int trajectory_type;
	
	bool flag_trajectory_ready;
	bool flag_training_start;
	bool flag_training_pause;
	bool flag_training_stop;
	
	// Constructor/destructor
	Training();
	~Training();
	
	// Read the trajectory from a data file
	void ReadTrajectoryFile(char* filename);
	
private:

	
};

#endif
