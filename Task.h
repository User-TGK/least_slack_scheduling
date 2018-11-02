#pragma once
/**
 * Container for all info about a task
 */
struct Task
{
	/**
	 * Constructor
	 * @param duration duration of the task
	 * @param machineId id of the machine this task runs on
	 */
	Task(unsigned long duration, unsigned long machineId);
	
	/**
	 * Destructor
	 */
	virtual ~Task();

	/**
	 * How long the task takes to complete
	 */
	unsigned long duration;

	/** 
	 * Id of the machine this task runs on
	*/
	unsigned long machineId;
};
