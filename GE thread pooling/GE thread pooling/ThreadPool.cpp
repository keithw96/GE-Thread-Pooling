#include "ThreadPool.h"

/// <summary>
/// Performs the task on the front of the queue
/// </summary>
/// <param name="param"> current instance of workQueue </param>
/// <returns></returns>
int doNextTask(void* param)
{
	std::function<void()> currentTask;
	WorkQueue* workQueue = (WorkQueue*)param;
	while (currentTask = workQueue->nextTask())
	{
		currentTask();
	}
	return 0;
}

/// <summary>
/// Creates a number of threads based on system specs minus one as a safety
/// </summary>
ThreadPool::ThreadPool()
{
	int numOfThreads = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < numOfThreads; i++)
	{
		m_threads.push_back(SDL_CreateThread(doNextTask, "Work", &workQueue));
	}
}

/// <summary>
/// Deconstructor
/// </summary>
ThreadPool::~ThreadPool()
{

}

/// <summary>
/// Add the passed task to the queue of tasks
/// </summary>
/// <param name="task"> Function to be added to queue of tasks </param>
void ThreadPool::addTask(std::function<void()> task)
{
	workQueue.addTask(task);
}