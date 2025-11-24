#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> 
#include <algorithm>
using namespace std;


struct Process
{
    int name;        
    int burst_time;    
    int arrival_time;  
};


static double avg_turn_around_time = 0;  // Tổng thời gian hoàn thành (TAT)
static double avg_waiting_time = 0;      // Tổng thời gian chờ (WT)

void swap(Process &p1, Process &p2)
{
    Process temp = p1;
    p1 = p2;
    p2 = temp;
}

// Hàm sắp xếp danh sách tiến trình theo thời điểm đến (Arrival Time)
void SortByArrivalTime(Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
            {
                swap(p[i], p[j]);
            }
        }
    }
}

// Hàm nhập thông tin tiến trình
void Input(Process *p, int n)
{
    srand(time(0)); 

    for (int i = 0; i < n; i++)
    {
        cout << "==============\n";
        cout << "Nhap ID Process: ";
        cin >> p[i].name;

        // Sinh giá trị ngẫu nhiên
        p[i].arrival_time = rand() % 21;      // [0, 20]
        p[i].burst_time   = 2 + rand() % 11;  // [2, 12]

        cout << "Arrival time: " << p[i].arrival_time << endl;
        cout << "Burst time: " << p[i].burst_time << endl;
    }
}

// Hàm sắp xếp theo Burst Time (SJF logic)
void sortByBurstTime(Process *p, int n, int time_current)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].arrival_time <= time_current && p[i].burst_time > p[j].burst_time)
            {
                swap(p[i], p[j]);
            }
        }
    }
}

// Hàm thực hiện thuật toán SJF
void SelectionFunction(Process *p, int n)
{
    SortByArrivalTime(p, n);

    int time_current = 0;
    if (n > 0)
        time_current = p[0].arrival_time; 

    cout << "\n------------------------------------------------------------\n";
    cout << left << setw(8) << "Name"
         << setw(10) << "ArrTime"
         << setw(10) << "BurTime"
         << setw(10) << "Finish"
         << setw(10) << "TAT"
         << setw(10) << "WT" << endl;
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        sortByBurstTime(p + i, n - i, time_current);

        if (time_current < p[i].arrival_time)
            time_current = p[i].arrival_time;

        time_current += p[i].burst_time;

        int tat = time_current - p[i].arrival_time;  // Turnaround time
        int wt  = tat - p[i].burst_time;             // Waiting time

        // Cộng dồn để tính trung bình
        avg_turn_around_time += tat;
        avg_waiting_time += wt;

        // In thông tin tiến trình
        cout << left << setw(8) << ("P" + to_string(p[i].name))
             << setw(10) << p[i].arrival_time
             << setw(10) << p[i].burst_time
             << setw(10) << time_current
             << setw(10) << tat
             << setw(10) << wt << endl;
    }
}

int main()
{
    int n;
    cout << "Nhap so luong process: ";
    cin >> n;

    Process *p = new Process[n];
    Input(p, n); // Nhập dữ liệu

    avg_turn_around_time = 0;
    avg_waiting_time = 0;

    cout << "\n=== KET QUA SJF (NON-PREEMPTIVE) ===\n";
    SelectionFunction(p, n);

    cout << "------------------------------------------------------------\n";
    if (n > 0)
    {
        cout << fixed << setprecision(2);
        cout << "Average Waiting Time = " << avg_waiting_time / n << endl;
        cout << "Average Turnaround Time = " << avg_turn_around_time / n << endl;
    }
    else
    {
        cout << "Khong co process de tinh toan.\n";
    }

    delete[] p;
    return 0;
}
