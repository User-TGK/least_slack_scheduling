#include <climits>
#include <sstream>
#include <iostream>

#include "Job.h"

Job::Job(unsigned long id)
	: id(id), startTime(ULONG_MAX), endTime(ULONG_MAX), freeTime(0)
{
}

Job::~Job()
{
}

unsigned long Job::getDuration() const
{
	unsigned long duration = 0;
	for (auto const &t : tasks)
		duration += t.duration;
	return duration;
}

std::string Job::toString() const
{
	std::stringstream ss;
	ss << id << "\t" << startTime << "\t" << endTime << std::endl;
	return ss.str();
}

bool Job::operator<(const Job &job) const
{
	unsigned long lDuration = getDuration();
	unsigned long rDuration = job.getDuration();
	return lDuration > rDuration ||
		   (lDuration == rDuration && id < job.getId());
	;
}

unsigned long Job::getId() const
{
	return id;
}

void Job::addTasks(std::string &tasksString)
{
	std::string buffer;
	unsigned short nTasks = 0;
	std::string durationString;
	std::string resourceString;
	unsigned short currentIndex = 0;

	for (unsigned short i = currentIndex; i < tasksString.length(); ++i)
	{
		if (!isspace(tasksString[i]))
		{
			if (resourceString.empty())
			{
				for (unsigned short j = i; j < tasksString.length(); ++j)
				{
					if (isspace(tasksString[j]))
					{
						i = j;
						break;
					}
					resourceString += tasksString[j];
				}
			}
			else
			{
				durationString += tasksString[i];
				if (isspace(tasksString[i + 1]) || i == tasksString.length() - 1)
				{
					Task newTask((unsigned long)std::stoi(durationString),
								 (unsigned long)std::stoi(resourceString));
					tasks.push_back(newTask);
					++nTasks;
					//Reset all
					durationString.clear();
					resourceString.clear();
				}
			}
		}
	}
}

bool Job::update(unsigned long time)
{
	if (startTime == ULONG_MAX)
		startTime = time;
	unsigned long dur = tasks.begin()->duration;
	if (tasks.size() == 1)
	{
		endTime = time + dur;
		return true;
	}
	else
		tasks.erase(tasks.begin());
	return false;
}

Task &Job::getNextTask()
{
	return tasks[0];
}

unsigned long Job::getFreeTime() const
{
	return freeTime;
}

void Job::setFreeTime(unsigned long freeTime)
{
	this->freeTime = freeTime;
}

Job::Job(const Job &job)
	: id(job.id), startTime(job.startTime), endTime(job.endTime), freeTime(job.freeTime), tasks(job.tasks)
{
}
