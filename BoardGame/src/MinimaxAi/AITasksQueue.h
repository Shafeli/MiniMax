#pragma once
#include <functional>
#include <mutex>
#include <queue>

class AITaskWorker;

class AITasksQueue
{

    struct Task
    {
        int priority;  // Higher value = higher priority
        std::function<void()> m_task;

        // higher priority first
        bool operator<(const Task& other) const
        {
            return priority < other.priority;
        }
    };

    std::vector<std::thread> workers;
    std::priority_queue<Task> m_tasks;
    std::mutex m_queueMutex;
    std::condition_variable m_condition;
    bool stop = false;

public:
    void SpawnWorkers();

    // Priority defaultes to 1
    void Push(std::function<void()> task, int taskPriority = 1);

    std::function<void()> Pop();

    void Shutdown();
};

class AITaskWorker
{
    AITasksQueue& m_queue;  // Task list

public:
    explicit AITaskWorker(AITasksQueue& queue) : m_queue(queue) {}

    void operator()() const
    {
        while (true)
        {
            auto job = m_queue.Pop();

            if (!job) break;  // Exit

            job();  // Do the thing
        }
    }
};
