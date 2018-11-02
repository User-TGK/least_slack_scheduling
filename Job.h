#pragma once

#include <queue>
#include <string>

#include "Task.h"
/**
 * A Job is a collection of tasks that have to be run on resources.
 */
class Job
{
  public:
	/**
	 * Constructor, only an id is given. 
	 * All other values are given a standard value.
	 * @param id id of the job
	 */
	explicit Job(unsigned long id);


	/**
	 * Copy Constructor. 
	 * Note: Copies the list of tasks by value.
	 * @param job Job to copy
	 */
	Job(const Job& job);


	virtual ~Job();
	/**
	 * Returns a string representation of the job that can be used
	 * to print to the output.
	 * @returns String representation of the job
	 */
	std::string toString() const;

	/** 
	 * Compares 2 jobs by slack and returns true if the left side job has a lower slack.
	*/
	bool operator<(const Job &job) const;

	/**
	 * Adds tasks to a job
	 * @param tasksString String representation of the tasks
	 */
	void addTasks(std::string &tasksString);

	/**
	 * updates the job. Side effect: Removes the last task.
	 * @param time current time
	 * @returns wether the job has finished or not
	 */
	bool update(unsigned long time);

	/**
	 * @returns the free time
	 */
	unsigned long getFreeTime() const;

	/**
	 * Sets the free time
	 * @param freeTime freetime to set 
	 */
	void setFreeTime(unsigned long freeTime);

	/**
	 * returns the id
	 * @returns id
	 */
	unsigned long getId() const;

	/**
	 * returns the next task in queue
	 * @returns the next task
	 */
	Task &getNextTask();

	/**
	 * returns the duration
	 * @returns the duration
	 */
	unsigned long getDuration() const;

  private:
	/**
	 * Identifier of the job
	 */
	unsigned long id;

	/**
	 * Time at wich the first task of this job started running
	 */
	unsigned long startTime;

	/**
	 * Time at wich the last task of this job finished
	 */
	unsigned long endTime;

	/**
	 * Time at wich a new task can be processed
	 */
	unsigned long freeTime;

	/**
	 * Contains all the tasks of this job
	 */
	std::vector<Task> tasks;
};
