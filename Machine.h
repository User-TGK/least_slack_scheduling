#pragma once

#include "Task.h"

/**
 * 	A machine that can run a task
 */
struct Machine
{
	/**
	 * Constructor
	 * @param id id of the machine
	 */
	Machine(unsigned long id);

	/**
	 * Destructor
	 */
	virtual ~Machine();
	
	/**
	 * Unique identifier
	 */
	unsigned long id;

	/**
	 * Time at wich the machine will be free to handle another task
	 */
	unsigned long freeTime;
};
