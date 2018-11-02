#pragma once

#include <istream>
#include <list>

#include "Job.h"
#include "Machine.h"

/** 
 * Class that allows you to schedule jobs and tasks according to the least slack algorithm
*/
class JobShop
{
public:
	/**
	 * Constructor
	 */
	JobShop();

	/**
	 * Destructor
	 */
	virtual ~JobShop();

	/**
	 * Schedules a collection of jobs and tasks
	 * @param input input stream 
	 * @param output output stream
	 */
	void schedule(std::istream *input, std::ostream *output);

private:
	/**
	 * extracts jobs and machines from an input stream
	 * @param input stream
	 * @param collection of jobs to store the jobs in
	 * @param collection of machiens to store the machines in
	 */
	void extract(std::istream *input, std::vector<Job> &jobs, std::vector<Machine> &machines);
};
