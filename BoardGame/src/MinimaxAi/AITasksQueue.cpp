#include "AITasksQueue.h"

void AITasksQueue::SpawnWorkers()
{
    // Spawn workers
    const int numThreads = std::thread::hardware_concurrency();
    for (int i = 0; i < numThreads; ++i)
    {
        workers.emplace_back(AITaskWorker(*this));
    }
}

void AITasksQueue::Push(std::function<void()> task, int taskPriority)
{
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);

        m_tasks.push({ taskPriority, std::move(task) });
    }
    m_condition.notify_one();
}

std::function<void()> AITasksQueue::Pop()
{
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_condition.wait(lock, [this]()
    {
        return !m_tasks.empty() || stop;
    });

    if (stop) return nullptr;

    auto task = std::move(m_tasks.top());
    m_tasks.pop();
    return task.m_task;
}

void AITasksQueue::Shutdown()
{
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        stop = true;
    }
    m_condition.notify_all();

    for (auto& worker : workers)
    {
        if (worker.joinable())
            worker.join();
    }

}
