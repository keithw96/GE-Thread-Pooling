#include "SDL.h"
#include "WorkQueue.h"
#include <vector>
#include <functional>
#include <SDL_mutex.h>
#include <SDL_thread.h>

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	void addTask(std::function<void()> newTask);

private:
	std::vector<SDL_Thread*> m_threads;

	WorkQueue workQueue;
};