
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <string>
#include <limits>

using namespace std;
using namespace std::chrono;

struct Task {
    string id, name;
    int deadline = 0, profit = 0, duration = 0;
};

struct ScheduleResult {
    vector<Task> scheduled;
    int totalProfit = 0;
    double executionMs = 0;
};

class TaskScheduler {
    vector<Task> tasks;

    int maxDeadline() const {
        int m = 0;
        for (auto &t : tasks) m = max(m, t.deadline);
        return m;
    }


    static void packBySlot(const vector<Task> &subset, int slots,
                            vector<Task> &out, int &profit) {
        vector<bool> slot(slots + 1, false);
        for (auto &t : subset) {
            for (int s = min(t.deadline, slots); s >= 1; s--) {
                if (!slot[s]) {
                    slot[s] = true;
                    out.push_back(t);
                    profit += t.profit;
                    break;
                }
            }
        }
    }

    static int readPositiveInt(const string &prompt) {
        int v;
        do {
            cout << prompt;
            cin >> v;
            if (v <= 0) cout << "Value must be greater than 0.\n";
        } while (v <= 0);
        return v;
    }

    void printTaskRow(const Task &t) const {
        cout << left << setw(10) << t.id << setw(25) << t.name
             << setw(10) << t.deadline << setw(10) << t.profit
             << setw(10) << t.duration << "\n";
    }

public:
    void showMenu() const {
        cout << "\n===================================================\n";
        cout << "      JOB & TASK SCHEDULER WITH DEADLINES\n";
        cout << "===================================================\n";
        cout << "1.  Add Task(s)\n2.  Display Tasks\n3.  Edit Task\n";
        cout << "4.  Delete Task\n5.  Search Task\n6.  Load Sample Data\n";
        cout << "7.  Sort By Profit\n8.  Sort By Deadline\n";
        cout << "9.  Show Statistics\n10. Save Tasks To File\n";
        cout << "11. Load Tasks From File\n12. Run Greedy Scheduler\n";
        cout << "13. Run Brute Force Scheduler\n14. Compare Algorithms\n";
        cout << "15. Exit\n";
        cout << "===================================================\n";
    }

    void addTasks() {
        int n = readPositiveInt("Enter Number of Tasks : ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < n; i++) {
            Task t;
            cout << "\n-- Task " << i + 1 << " --\n";
            cout << "Task ID : "; cin >> t.id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Task Name : "; getline(cin, t.name);
            t.deadline = readPositiveInt("Deadline : ");
            t.profit = readPositiveInt("Profit : ");
            t.duration = readPositiveInt("Duration (Hours) : ");
            tasks.push_back(t);
        }
        cout << "\nTasks Added Successfully.\n";
    }

    void displayTasks() const {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        cout << "\n" << left << setw(10) << "ID" << setw(25) << "Name"
             << setw(10) << "Deadline" << setw(10) << "Profit"
             << setw(10) << "Hours" << "\n" << string(65, '-') << "\n";
        for (auto &t : tasks) printTaskRow(t);
        cout << string(65, '-') << "\n";
    }

    void editTask() {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        string id;
        cout << "\nEnter Task ID : "; cin >> id;
        for (auto &t : tasks) {
            if (t.id == id) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "New Name : "; getline(cin, t.name);
                t.deadline = readPositiveInt("New Deadline : ");
                t.profit = readPositiveInt("New Profit : ");
                t.duration = readPositiveInt("New Duration : ");
                cout << "\nTask Updated Successfully.\n";
                return;
            }
        }
        cout << "\nTask Not Found.\n";
    }

    void deleteTask() {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        string id;
        cout << "\nEnter Task ID : "; cin >> id;
        auto it = find_if(tasks.begin(), tasks.end(),
                           [&](const Task &t) { return t.id == id; });
        if (it == tasks.end()) { cout << "\nTask Not Found.\n"; return; }
        tasks.erase(it);
        cout << "\nTask Deleted Successfully.\n";
    }

    void searchTask() const {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        string id;
        cout << "\nEnter Task ID : "; cin >> id;
        for (auto &t : tasks) {
            if (t.id == id) {
                cout << "\n-- Task Details --\n";
                printTaskRow(t);
                return;
            }
        }
        cout << "\nTask Not Found.\n";
    }

    void loadSampleData() {
        tasks = {
            {"T101", "Login Module", 2, 100, 2},
            {"T102", "Database Design", 1, 60, 1},
            {"T103", "Dashboard UI", 2, 80, 2},
            {"T104", "Testing", 3, 50, 2},
            {"T105", "Documentation", 4, 40, 1},
            {"T106", "Deployment", 3, 120, 2},
        };
        cout << "\nSample Data Loaded Successfully.\n";
    }

    void sortByProfit() {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        sort(tasks.begin(), tasks.end(),
             [](const Task &a, const Task &b) { return a.profit > b.profit; });
        cout << "\nSorted By Profit.\n";
        displayTasks();
    }

    void sortByDeadline() {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.deadline == b.deadline ? a.profit > b.profit
                                             : a.deadline < b.deadline;
        });
        cout << "\nSorted By Deadline.\n";
        displayTasks();
    }

    void showStatistics() const {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        int totalProfit = 0, totalDuration = 0;
        const Task *best = &tasks[0];
        for (auto &t : tasks) {
            totalProfit += t.profit;
            totalDuration += t.duration;
            if (t.profit > best->profit) best = &t;
        }
        cout << "\n-- Project Statistics --\n";
        cout << "Total Tasks     : " << tasks.size() << "\n";
        cout << "Total Profit    : " << totalProfit << "\n";
        cout << "Average Profit  : " << fixed << setprecision(2)
             << (double)totalProfit / tasks.size() << "\n";
        cout << "Total Duration  : " << totalDuration << " Hours\n";
        cout << "Best Task       : " << best->name
             << " (Profit " << best->profit << ")\n";
    }

    void saveToFile() const {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        ofstream fout("tasks.txt");
        if (!fout) { cout << "\nUnable to Create File.\n"; return; }
        fout << tasks.size() << "\n";
        for (auto &t : tasks)
            fout << t.id << "\n" << t.name << "\n" << t.deadline << "\n"
                 << t.profit << "\n" << t.duration << "\n";
        cout << "\nTasks Saved Successfully.\n";
    }

    void loadFromFile() {
        ifstream fin("tasks.txt");
        if (!fin) { cout << "\nFile Not Found.\n"; return; }
        int n;
        fin >> n;
        fin.ignore();
        tasks.clear();
        for (int i = 0; i < n; i++) {
            Task t;
            getline(fin, t.id);
            getline(fin, t.name);
            fin >> t.deadline >> t.profit >> t.duration;
            fin.ignore();
            tasks.push_back(t);
        }
        cout << "\nTasks Loaded Successfully.\n";
    }

    void printSchedule(const ScheduleResult &r, const string &title) const {
        cout << "\n-- " << title << " --\n";
        if (r.scheduled.empty()) { cout << "No Tasks Scheduled.\n"; return; }
        cout << left << setw(10) << "ID" << setw(25) << "Name"
             << setw(10) << "Profit" << setw(10) << "Deadline" << "\n"
             << string(55, '-') << "\n";
        for (auto &t : r.scheduled)
            cout << left << setw(10) << t.id << setw(25) << t.name
                 << setw(10) << t.profit << setw(10) << t.deadline << "\n";
        cout << string(55, '-') << "\n";
        cout << "Scheduled  : " << r.scheduled.size() << "\n";
        cout << "Profit     : " << r.totalProfit << "\n";
        cout << "Time       : " << fixed << setprecision(5)
             << r.executionMs << " ms\n";
    }

  
    ScheduleResult greedyScheduler(bool report = true) {
        ScheduleResult r;
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return r; }

        auto start = high_resolution_clock::now();
        vector<Task> sorted = tasks;
        sort(sorted.begin(), sorted.end(),
             [](const Task &a, const Task &b) { return a.profit > b.profit; });
        packBySlot(sorted, maxDeadline(), r.scheduled, r.totalProfit);
        r.executionMs = duration<double, milli>(
            high_resolution_clock::now() - start).count();

        if (report) printSchedule(r, "GREEDY RESULT");
        return r;
    }


    ScheduleResult bruteForceScheduler(bool report = true) {
        ScheduleResult r;
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return r; }
        if (tasks.size() > 20) {
            cout << "\nBrute Force supports only up to 20 tasks.\n";
            return r;
        }

        auto start = high_resolution_clock::now();
        int n = tasks.size(), slots = maxDeadline();

        for (int mask = 0; mask < (1 << n); mask++) {
            vector<Task> subset;
            for (int i = 0; i < n; i++)
                if (mask & (1 << i)) subset.push_back(tasks[i]);

            vector<Task> current;
            int profit = 0;
            packBySlot(subset, slots, current, profit);

            if (current.size() == subset.size() && profit > r.totalProfit) {
                r.totalProfit = profit;
                r.scheduled = current;
            }
        }
        r.executionMs = duration<double, milli>(
            high_resolution_clock::now() - start).count();

        if (report) printSchedule(r, "BRUTE FORCE RESULT");
        return r;
    }

    void compareAlgorithms() {
        if (tasks.empty()) { cout << "\nNo Tasks Available.\n"; return; }
        ScheduleResult g = greedyScheduler();
        ScheduleResult b = bruteForceScheduler();

        cout << "\n-- Algorithm Comparison --\n";
        cout << left << setw(20) << "Parameter" << setw(15) << "Greedy"
             << setw(15) << "Brute Force" << "\n" << string(50, '-') << "\n";
        cout << left << setw(20) << "Total Profit" << setw(15) << g.totalProfit
             << setw(15) << b.totalProfit << "\n";
        cout << left << setw(20) << "Time (ms)" << fixed << setprecision(5)
             << setw(15) << g.executionMs << setw(15) << b.executionMs << "\n";
        cout << (g.totalProfit == b.totalProfit
                     ? "\nGreedy matched the optimal solution.\n"
                     : "\nBrute Force found a better solution.\n");
        cout << "Complexity -> Greedy: O(n log n) | Brute Force: O(2^n)\n";
    }
};

int main() {
    TaskScheduler scheduler;
    int choice;

    do {
        scheduler.showMenu();
        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice) {
            case 1:  scheduler.addTasks(); break;
            case 2:  scheduler.displayTasks(); break;
            case 3:  scheduler.editTask(); break;
            case 4:  scheduler.deleteTask(); break;
            case 5:  scheduler.searchTask(); break;
            case 6:  scheduler.loadSampleData(); break;
            case 7:  scheduler.sortByProfit(); break;
            case 8:  scheduler.sortByDeadline(); break;
            case 9:  scheduler.showStatistics(); break;
            case 10: scheduler.saveToFile(); break;
            case 11: scheduler.loadFromFile(); break;
            case 12: scheduler.greedyScheduler(); break;
            case 13: scheduler.bruteForceScheduler(); break;
            case 14: scheduler.compareAlgorithms(); break;
            case 15: cout << "\nThank You.\n"; break;
            default: cout << "\nInvalid Choice.\n";
        }
    } while (choice != 15);

    return 0;
}
