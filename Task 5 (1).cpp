#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Task class definition
class Task {
public:
    int id;
    std::string title;
    std::string description;

    Task(int id, const std::string& title, const std::string& description)
        : id(id), title(title), description(description) {}

    // To write Task object to a file
    friend std::ostream& operator<<(std::ostream& os, const Task& task) {
        os << task.id << "\n" << task.title << "\n" << task.description << "\n";
        return os;
    }

    // To read Task object from a file
    friend std::istream& operator>>(std::istream& is, Task& task) {
        is >> task.id;
        is.ignore(); // Ignore the newline character after the id
        std::getline(is, task.title);
        std::getline(is, task.description);
        return is;
    }
};

// Function declarations
void createTask(std::vector<Task>& tasks, int& currentId);
void readTasks(const std::vector<Task>& tasks);
void updateTask(std::vector<Task>& tasks);
void deleteTask(std::vector<Task>& tasks);
void loadTasksFromFile(std::vector<Task>& tasks, int& currentId);
void saveTasksToFile(const std::vector<Task>& tasks);

const std::string filename = "tasks.txt";

int main() {
    std::vector<Task> tasks;
    int currentId = 1; // To assign unique IDs to tasks

    // Load tasks from file
    loadTasksFromFile(tasks, currentId);

    int choice;

    while (true) {
        std::cout << "\nTask Manager\n";
        std::cout << "1. Create Task\n";
        std::cout << "2. Read Tasks\n";
        std::cout << "3. Update Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createTask(tasks, currentId);
                break;
            case 2:
                readTasks(tasks);
                break;
            case 3:
                updateTask(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                saveTasksToFile(tasks);
                return 0;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

void createTask(std::vector<Task>& tasks, int& currentId) {
    std::string title, description;
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter task title: ";
    std::getline(std::cin, title);
    std::cout << "Enter task description: ";
    std::getline(std::cin, description);
    
    tasks.emplace_back(currentId++, title, description);
    std::cout << "Task created successfully!\n";
}

void readTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.id << "\nTitle: " << task.title << "\nDescription: " << task.description << "\n\n";
    }
}

void updateTask(std::vector<Task>& tasks) {
    int id;
    std::cout << "Enter task ID to update: ";
    std::cin >> id;
    std::cin.ignore(); // Clear the input buffer
    
    for (auto& task : tasks) {
        if (task.id == id) {
            std::string title, description;
            std::cout << "Enter new task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter new task description: ";
            std::getline(std::cin, description);
            task.title = title;
            task.description = description;
            std::cout << "Task updated successfully!\n";
            return;
        }
    }
    std::cout << "Task with ID " << id << " not found.\n";
}

void deleteTask(std::vector<Task>& tasks) {
    int id;
    std::cout << "Enter task ID to delete: ";
    std::cin >> id;
    std::cin.ignore(); // Clear the input buffer

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            std::cout << "Task deleted successfully!\n";
            return;
        }
    }
    std::cout << "Task with ID " << id << " not found.\n";
}

void loadTasksFromFile(std::vector<Task>& tasks, int& currentId) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Task task(0, "", "");
        while (inFile >> task) {
            tasks.push_back(task);
            if (task.id >= currentId) {
                currentId = task.id + 1;
            }
        }
        inFile.close();
        std::cout << "Tasks loaded successfully from " << filename << "\n";
    } else {
        std::cout << "No existing task file found. Starting fresh.\n";
    }
}

void saveTasksToFile(const std::vector<Task>& tasks) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& task : tasks) {
            outFile << task;
        }
        outFile.close();
        std::cout << "Tasks saved successfully to " << filename << "\n";
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}
