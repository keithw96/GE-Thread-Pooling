#include "WorkQueue.h"

/// <summary>
/// Constructor
/// create the mutex and condition
/// </summary>
WorkQueue::WorkQueue() :
	m_condition(SDL_CreateCond()),
	m_mutex(SDL_CreateMutex())
{

}

/// <summary>
/// Add passed task to the queue of tasks
/// Mutex prevents overwriting of tasks
/// </summary>
/// <param name="newTask"> Function to be added to queue of tasks </param>
void WorkQueue::addTask(std::function<void()> newTask)
{
	SDL_LockMutex(m_mutex);
	m_tasks.push(newTask);
	SDL_CondSignal(m_condition);
	SDL_UnlockMutex(m_mutex);
}

/// <summary>
/// Returns the task at the front of the queue and removes it from the queue
/// </summary>
/// <returns> Next Task </returns>
std::function<void()> WorkQueue::nextTask()
{
	std::function<void()> nextJob;
	SDL_LockMutex(m_mutex);

	while (m_tasks.size() == 0)
	{
		SDL_CondWait(m_condition, m_mutex);
	}
	nextJob = m_tasks.front();
	m_tasks.pop();

	SDL_UnlockMutex(m_mutex);
	return nextJob;
}