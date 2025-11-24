#include<iostream>
#include<queue>
using namespace std;

struct Process {
    int name;
    int burst_time;
    int arrival_time;
};

static double avg_turn_around_time = 0;  
static double avg_waiting_time = 0;

void swap(Process &p1, Process &p2)
{
    Process temp;
    temp = p1;
    p1 = p2;
    p2 = temp;
}

// chọn tiến trình có burst nhỏ nhất đã đến
int findSRTF(Process *p, int n, int time_current)
{
    int idx = -1;
    int minBurst = 1e9;

    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival_time <= time_current && p[i].burst_time > 0)
        {
            if (p[i].burst_time < minBurst)
            {
                minBurst = p[i].burst_time;
                idx = i;
            }
        }
    }
    return idx;
}

// sort theo arrival time tăng dần (đúng)
void sortByArrivalTime(Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
                swap(p[i], p[j]);
            else if (p[i].arrival_time == p[j].arrival_time)
            {
                if (p[i].burst_time > p[j].burst_time)
                    swap(p[i], p[j]);
            }
        }
    }
}

void Input(Process *p, int n)
{
    srand(time(0)); 

    for (int i = 0; i < n; i++)
    {
        cout << "==============\n";
        cout << "Nhap ID Process: ";
        cin >> p[i].name;

        p[i].arrival_time = rand() % 21;      // [0, 20]
        p[i].burst_time   = 2 + rand() % 11;  // [2, 12]

        cout << "Arrival time: " << p[i].arrival_time << endl;
        cout << "Burst time: " << p[i].burst_time << endl;
    }
}

void SelectionFunction(Process *p, int n)
{
    sortByArrivalTime(p, n);

    int waiting_time[100] = {0};
    int completed = 0;

    int time_current = p[0].arrival_time;

    cout << "Process    Waiting-time    Turn around time\n";

    while (completed < n)
    {
        int idx = findSRTF(p, n, time_current);

        // CPU idle → tăng thời gian, không tăng waiting_time cho process chưa đến
        if (idx == -1)
        {
            // tăng chờ cho tất cả tiến trình đã đến nhưng chưa được chạy
            for (int i = 0; i < n; i++)
            {
                if (p[i].arrival_time <= time_current && p[i].burst_time > 0)
                    waiting_time[i]++;
            }
            time_current++;
            continue;
        }

        // tăng waiting time cho các process khác
        for (int i = 0; i < n; i++)
        {
            if (i != idx && p[i].arrival_time <= time_current && p[i].burst_time > 0)
                waiting_time[i]++;
        }

        // chạy 1 đơn vị thời gian
        p[idx].burst_time--;
        time_current++;

        // tiến trình hoàn thành
        if (p[idx].burst_time == 0)
        {
            int tat = time_current - p[idx].arrival_time;
            cout << p[idx].name << "          "
                 << waiting_time[idx] << "                "
                 << tat << endl;

            avg_waiting_time += waiting_time[idx];
            avg_turn_around_time += tat;

            completed++;
        }
    }
}

int main()
{
    Process *p = new Process[100];
    int n;
    cout << "Nhap so luong tien trinh: ";
    cin >> n;

    Input(p, n);

    SelectionFunction(p, n);

    cout << "avg waiting time: " << avg_waiting_time / n << endl;
    cout << "avg turnaround time: " << avg_turn_around_time / n << endl;

    delete[] p;
    return 0;
}
