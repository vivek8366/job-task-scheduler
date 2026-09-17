Job & Task Scheduler with Deadlines

A C++ implementation of the classic **Job Sequencing with Deadlines** problem using a greedy algorithm. The project schedules jobs to maximize total profit while satisfying their deadlines.

It also includes a **brute-force approach** for small datasets to verify and compare the results produced by the greedy strategy.

📌 Overview

In many real-world scheduling systems, multiple tasks compete for limited time slots. Each task may have a deadline and an associated profit or priority.

The objective of this project is to:

* Schedule jobs within their deadlines.
* Maximize the total achievable profit.
* Demonstrate the use of greedy algorithm design.
* Show the importance of sorting as a preprocessing step.
* Compare the greedy solution with brute-force search for small datasets.

🎯 Problem Statement

Given `N` jobs, where each job has:

* A unique job ID
* A deadline
* A profit

Each job requires exactly **one unit of time** and must be completed on or before its deadline.

The goal is to select and schedule jobs such that:

1. Every selected job is completed within its deadline.
2. No two jobs occupy the same time slot.
3. The total profit is maximized.

🧠 Algorithm

 Greedy Approach

The greedy strategy follows these steps:

1. Sort all jobs in descending order of profit.
2. Find the latest available time slot before the job's deadline.
3. Assign the job to that slot if it is available.
4. Continue until all jobs have been considered.
5. Calculate the total profit.

 Example

Consider the following jobs:

| Job | Deadline | Profit |
| --- | -------- | ------ |
| J1  | 2        | 100    |
| J2  | 1        | 50     |
| J3  | 2        | 20     |
| J4  | 1        | 40     |
| J5  | 3        | 70     |

The jobs are first sorted according to profit:

`J1 → J5 → J2 → J4 → J3`

The scheduler then places each job into the latest available slot before its deadline.

A possible optimal schedule is:

`J2 → J1 → J5`

with total profit:

`50 + 100 + 70 = 220`

🔍 Brute-Force Comparison

For small datasets, the project can also generate possible job selections and schedules using brute-force search.

The brute-force result can then be compared with the greedy result.

This helps demonstrate that the greedy approach produces the optimal solution for the standard Job Sequencing with Deadlines problem while being significantly more efficient than checking every possible arrangement.

⚙️ Technologies Used

* **Language:** C++
* **Algorithm:** Greedy Algorithm
* **Concepts:** Sorting, Scheduling, Priority Queue
* **Verification:** Brute-Force Search
* **Libraries:** C++ Standard Template Library (STL)

 📊 Complexity

Let `N` be the number of jobs and `D` be the maximum deadline.

 Sorting

```text
O(N log N)
```

Greedy Scheduling

With a simple slot-search implementation:

```text
O(N × D)
```

Therefore, the overall complexity is approximately:

```text
O(N log N + N × D)
```

The complexity can be further optimized using data structures such as Disjoint Set Union (DSU).

🚀 How to Run

 1. Clone the repository

```bash
git clone https://github.com/YOUR-USERNAME/job-task-scheduler.git
```

 2. Navigate to the project

```bash
cd job-task-scheduler
```

 3. Compile

```bash
g++ main.cpp -o scheduler
```

 4. Run



On Windows:

```bash
scheduler.exe
```

📥 Sample Input

```text
5
J1 2 100
J2 1 50
J3 2 20
J4 1 40
J5 3 70
```

📤 Sample Output

```text
Scheduled Jobs:
J2 J1 J5

Maximum Profit: 220
```

✨ Features

* Greedy job scheduling
* Deadline constraint handling
* Profit maximization
* Sorting-based preprocessing
* Brute-force verification
* Small-dataset comparison
* Console-based C++ implementation
* Easy-to-understand algorithm demonstration

🎓 Learning Objectives

This project demonstrates:

* Greedy algorithm design
* Sorting as preprocessing
* Priority-based decision making
* Scheduling problems
* Optimization under constraints
* Brute-force versus greedy approaches
* Time and space complexity analysis

🔮 Future Enhancements

Possible improvements include:

* GUI-based scheduling dashboard
* Interactive task creation
* Real-time task management
* Task priorities and categories
* Multiple-resource scheduling
* Disjoint Set Union optimization
* CSV/JSON data import and export
* Performance visualization
* Web-based task scheduler

🤝 Contributing

Contributions are welcome.

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Commit your changes.
5. Push the branch.
6. Create a Pull Request.

📄 License

This project is licensed under the MIT License.

👨‍💻 Author

**Vivek Kumar Yadav**

GitHub: `https://github.com/vivek8366`
