#include <iostream>
#include <algorithm>
#include <sstream>

#include "JobShop.h"
#include "Job.h"
#include "Machine.h"

JobShop::JobShop()
{
}

JobShop::~JobShop()
{
}

void JobShop::schedule(std::istream *input, std::ostream *output)
{
	std::vector<Job> jobs;
	std::vector<Job> finishedJobs;
	//Extract and create the jobs and machines
	std::vector<Machine> machines;

	extract(input, jobs, machines);

	//Start the loop of scheduling
	unsigned long time = 0;
	while (!jobs.empty())
	{
		std::sort(jobs.begin(), jobs.end());
		for (auto &m : machines)
		{
			if (time >= m.freeTime)
			{
				for (auto j = jobs.begin(); j != jobs.end(); ++j)
				{
					Task &t = j->getNextTask();
					if (t.machineId == m.id && j->getFreeTime() <= time)
					{
						j->setFreeTime(t.duration + time);
						m.freeTime = t.duration + time;
						if (j->update(time))
						{
							finishedJobs.push_back(*j);
							jobs.erase(j++);
						}
						break;
					}
				}
			}
		}
		++time;
	}
	std::sort(finishedJobs.begin(), finishedJobs.end(), [](Job &j1, Job &j2) { return j1.getId() < j2.getId(); });
	for (auto const &j :finishedJobs)
	{
		*output << j.toString();
	}
}

void JobShop::extract(std::istream *input, std::vector<Job> &jobs, std::vector<Machine> &machines)
{
	std::string buffer;
	unsigned long nJobs = 0;
	unsigned long nMachines = 0;

	std::getline(*input, buffer);
	std::string jobsString;
	std::string resourceString;

	for (unsigned short i = 0; i < buffer.length(); ++i)
	{
		if (std::isspace(buffer[i]) == 0)
		{
			if (jobsString.empty())
			{
				for (unsigned short j = i; j < buffer.length(); ++j)
				{
					if (std::isspace(buffer[j]))
					{
						i = j;
						break;
					}
					jobsString += buffer[j];
				}
			}
			else
			{
				resourceString += buffer[i];
			}

		}
	}
	nMachines = (unsigned long) std::stoi(resourceString);
	nJobs = (unsigned long) std::stoi(jobsString);

	for (unsigned short i = 0; i < nMachines; ++i)
	{
		Machine m(i);
		machines.push_back(m);
	}

	for (unsigned short i = 0; i < nJobs; ++i)
	{
		buffer.clear();
		std::getline(*input, buffer);
		Job j(i);
		j.addTasks(buffer);
		//At the end, add the job to the list
		jobs.push_back(j);
	}
}
