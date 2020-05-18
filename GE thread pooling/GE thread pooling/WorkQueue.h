#include <functional>
#include <queue>
#include <SDL_thread.h>
#include <thread>

class WorkQueue
{
public:
	WorkQueue();

	void addTask(std::function<void()>);
	std::function<void()> nextTask();

private:
	std::queue<std::function<void()>> m_tasks;

	SDL_mutex* m_mutex;
	SDL_cond* m_condition;
};