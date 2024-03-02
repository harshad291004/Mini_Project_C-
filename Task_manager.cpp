#include <iostream> 
#include <string> 
#include <algorithm> // for std::sort 
using namespace std; 
class Task { 
protected: 
    string taskName; 
    string description; 
    int priority; // 1 (high) to 5 (low) 
public: 
    Task(const string& name, const string& desc, int prio) 
    : taskName(name), description(desc), priority(prio) {}   
    int getPriority() const { return priority; } 
    void setPriority(int prio) { priority = prio; } 
    virtual void displayDetails() const { 
        cout << "Task: " << taskName << "\nDescription: " << description 
             << "\nPriority: " << priority << "\n"; 
    } 
    virtual ~Task() {} 
}; 
class DeadlineTask : public Task { 
private: 
    string deadlineDate; 
public: 
    DeadlineTask(const string& name, const string& desc, int prio, 
                 const string& deadline) 
    : Task(name, desc, prio), deadlineDate(deadline) {}  
    void displayDetails() const override { 
        Task::displayDetails(); 
        cout << "Deadline: " << deadlineDate << "\n"; 
    } 
    ~DeadlineTask() {} 
}; 
class TaskManager { 
private: 
    Task* tasks[100]; // Maximum of 100 tasks for simplicity 
    int taskCount = 0; // Number of tasks currently in the list 
public: 
    TaskManager() { 
        for (int i = 0; i < 100; ++i) { 
            tasks[i] = nullptr; 
        } 
    } 
    void addTask(Task* newTask) { 
        if (taskCount < 100) { 
            tasks[taskCount++] = newTask; 
            sortTasksByPriority(); 
        } 
    } 
    void markTaskAsComplete(int index) { 
        if (index >= 0 && index < taskCount) { 
            delete tasks[index]; 
            tasks[index] = nullptr; 
            // Shift tasks to fill the gap 
            for (int i = index; i < taskCount - 1; ++i) {  
                tasks[i] = tasks[i + 1]; 
                tasks[i + 1] = nullptr; 
            } 
            taskCount--; 
//Instruction to change the prirority of other successeding tasks ,after completion of a tasks 
            // Adjust priorities of other tasks 
            for (int i = index; i < taskCount; ++i) { 
                tasks[i]->setPriority(tasks[i]->getPriority() - 1); 
            } 
        } 
    } 
//Change was instructed  
//Instruction to display tasks in a sorted manner  
    void sortTasksByPriority() { 
        sort(tasks, tasks + taskCount, [](Task* a, Task* b) { 
            return a->getPriority() < b->getPriority(); 
        }); 
    } 
    void generateProgressReport() const { 
        cout << "Task List:\n"; 
        bool tasksExist = false; 
        for (int i = 0; i < taskCount; ++i) { 
            if (tasks[i] != nullptr) { 
                tasks[i]->displayDetails(); 
                cout << "------------------------\n"; 
                tasksExist = true; 
            } 
        }  
        if (!tasksExist) { 
            cout << "No tasks found.\n"; 
        } 
    } 
    ~TaskManager() { 
        for (int i = 0; i < 100; ++i) { 
            if (tasks[i] != nullptr) { 
                delete tasks[i]; 
            } 
        } 
    } 
}; 
int main() { 
    TaskManager manager; 
    int choice; 
    do { 
        cout << "\nMenu:\n"; 
        cout << "1. Add Task\n"; 
        cout << "2. Mark Task as Complete\n"; 
        cout << "3. Display Tasks\n"; 
        cout << "4. Exit\n"; 
        cout << "Enter your choice: "; 
        cin >> choice; 
        cin.ignore(); // Ignore the newline character left in the stream 
        switch (choice) { 
            case 1: { 
                string name, desc, deadline; 
                int prio;
                cout << "Enter task name: "; 
                getline(cin, name); 
                cout << "Enter task description: "; 
                getline(cin, desc); 
                cout << "Enter task priority (1-5): "; 
                cin >> prio; 
                // 
                if(prio>5){ 
                    cout<<"INVALID! Priority limit reached!!"<<endl; 
                    break; 
                } 
                cin.ignore(); // Ignore the newline character left in the stream 
                cout << "Enter deadline : "; 
                getline(cin, deadline); 
                Task* newTask = new Task(name, desc, prio); 
                manager.addTask(newTask); 
                cout << "Task added successfully.\n"; 
                break; 
            } 
            case 2: { 
                int index; 
                cout << "Enter index of task to mark as complete: "; 
                cin >> index; 
                manager.markTaskAsComplete(index); 
                cout << "Task marked as complete.\n"; 
                break; 
            } 
            case 3: 
 
                manager.generateProgressReport(); 
                break; 
            case 4: 
                cout << "Exiting program.\n"; 
                break; 
            default: 
                cout << "Invalid choice. Please try again.\n"; 
        } 
    } while (choice != 4); 
    return 0; 
} 