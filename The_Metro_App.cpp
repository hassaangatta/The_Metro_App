#include <bits/stdc++.h>
#include <stdlib.h>
#include <unordered_set>
#include <windows.h>
#include <conio.h>
using namespace std;
#define INF 0x3f3f3f3f

int total_dist = 0, total_cost = 0;

class stop
{
public:
    string name;
    stop *next;
    stop *adj;
    int distance;
    stop(string st)
    {
        name = st;
        distance = 0;
        next = NULL;
        adj = NULL;
    }
    stop(string st, int n)
    {
        name = st;
        distance = n;
        next = NULL;
        adj = NULL;
    }
};

class City_map
{
public:
    stop *head;
    stack<string> paths;
    City_map()
    {
        // td = 0;
        head = NULL;
    }
    void addNew(string name)
    {
        stop *NS = new stop(name);
        if (head == NULL)
        {
            head = NS;
        }
        else
        {
            stop *curr = head;
            NS->next = curr;
            head = NS;
        }
    }
    void addNew(string source, string name, int n)
    {
        stop *NS = new stop(name, n);
        stop *curr = head;
        while (curr->name != source && curr != NULL)
            curr = curr->next;

        while (curr->adj != NULL)
            curr = curr->adj;

        curr->adj = NS;
    }
    void Display()
    {
        stop *curr = head;
        stop *temp = curr;
        while (curr != NULL)
        {
            cout << curr->name;
            temp = curr->adj;
            while (temp != NULL)
            {
                cout << " -> " << temp->name << "  " << temp->distance;
                temp = temp->adj;
            }

            cout << endl;
            curr = curr->next;
        }
    }
    stop *Search(string data)
    {
        stop *temp = head;
        while (temp->name != data && temp != NULL)
            temp = temp->next;
        return temp;
    }
    vector<string> Shortest_distance(string start, string end)
    {
        stop *source = Search(start);
        unordered_map<string, int> dist;
        unordered_map<string, string> connections;
        stop *temp = head;
        while (temp != NULL)
        {
            dist[temp->name] = INF;
            temp = temp->next;
        }
        unordered_set<string> visited;
        set<pair<int, string>> st;
        st.insert({0, source->name});
        dist[source->name] = 0;

        while (st.size() > 0)
        {
            auto node = *st.begin();
            string v = node.second;
            stop *curr = Search(v);
            curr = curr->adj;
            st.erase(st.begin());
            if (visited.count(v))
                continue;
            visited.insert(v);
            while (curr != NULL)
            {
                string curr_child = v;
                string child = curr->name;
                int wt = curr->distance;
                if (dist[v] + wt < dist[child])
                {
                    dist[child] = dist[v] + wt;
                    st.insert({dist[child], child});
                    connections[child] = curr_child;
                }
                curr = curr->adj;
            }
            string a = *(visited.begin());
            if (a == end)
                break;
        }

        string any;
        paths.push(end);
        do
        {
            any = search_path(connections, paths.top());
            paths.push(any);
        } while (any != start);

        cout << endl;
        vector<string> p;
        while (!paths.empty())
        {
            any = paths.top();
            p.push_back(any);
            //            cout << paths.top() << " ";
            paths.pop();
        }
        return p;
    }
    string search_path(unordered_map<string, string> &m, string s)
    {
        for (auto i : m)
        {
            if (s == i.first)
                return i.second;
        }
        return "";
    }
    void rutes_dectription(vector<string> s)
    {
        total_cost = 0;
        total_dist = 0;
        vector<string> v1;
        vector<string> v2;
        auto j = s.end();
        j--;
        for (auto i = s.begin(); i != j; i++)
        {
            auto it = i;
            it++;
            string temp1 = *i, temp2 = *it;
            ifstream filein;
            filein.open("adjencies_rutes.txt");
            string str, line, s1, s2, s3;
            while (getline(filein, line))
            {
                stringstream s(line);
                getline(s, s1, ',');
                getline(s, s2, ',');
                getline(s, s3);
                if (s1 == *i && s2 == *it)
                {
                    if (s3 == "1")
                    {
                        str = "Red Line";
                        break;
                    }
                    else if (s3 == "2")
                    {
                        str = "Green Line";
                        break;
                    }
                    else if (s3 == "3")
                    {
                        str = "Orange Line";
                        break;
                    }
                    else if (s3 == "4")
                    {
                        str = "Blue Line";
                        break;
                    }
                    else if (s3 == "5")
                    {
                        str = "Yellow Line";
                        break;
                    }
                }
            }
            filein.close();
            if (count(v1.begin(), v1.end(), str) == 0 && str != "")
            {
                v1.push_back(str);
                v2.push_back(*i);
            }
        }
        total_cost = 50 * v1.size();
        for (auto i = s.begin(); i != j; i++)
        {
            auto it = i;
            it++;
            string temp1 = *i, temp2 = *it;
            ifstream filein;
            filein.open("adjencies.txt");
            string str, line, s1, s2, s3;
            while (getline(filein, line))
            {
                stringstream s(line);
                getline(s, s1, ',');
                getline(s, s2, ',');
                getline(s, s3);
                int t = stoi(s3);
                if (s1 == *i && s2 == *it)
                {
                    total_dist += t;
                }
            }
            filein.close();
        }
        cout << "Total Cost: Rs " << total_cost << endl;
        cout << "Total Distance: " << total_dist << " Km" << endl;
        auto it1 = v1.begin();
        for (auto i = v2.begin(); i != v2.end(); i++)
        {
            cout << "Take  ";
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 10);
            cout << *it1;
            SetConsoleTextAttribute(h, 7);
            cout << " from ";
            SetConsoleTextAttribute(h, 10);
            cout << *i << endl;
            it1++;
            SetConsoleTextAttribute(h, 7);
        }
    }
    void DFS(unordered_map<string, int> visited, int cost, int pre, vector<int> &dist, string st, string en, vector<string> path, vector<vector<string>> &all_paths)
    {
        visited[st] = 1;
        if (st == en)
        {
            all_paths.push_back(path);
            dist.push_back(cost);
            cost = 0;
        }
        else
        {
            stop *curr = Search(st);
            curr = curr->adj;
            while (curr != NULL)
            {
                if (visited[curr->name] == 0)
                {
                    visited[curr->name] = 1;
                    path.push_back(curr->name);
                    if (curr->distance != pre)
                        cost += 50;
                    DFS(visited, cost, curr->distance, dist, curr->name, en, path, all_paths);
                    path.pop_back();
                    if (curr->distance != pre)
                        cost -= 50;
                }
                curr = curr->adj;
            }
        }
        visited[st] = 0;
    }
    vector<string> min_cost(string start, string end)
    {
        unordered_map<string, int> visited;
        vector<vector<string>> all_paths;
        vector<string> path;
        vector<int> dist;
        path.push_back(start);
        DFS(visited, 0, -1, dist, start, end, path, all_paths);
        int min = INT_MAX;
        auto it = dist.begin();
        for (vector<string> i : all_paths)
        {
            if (*it < min)
            {
                path = i;
                min = *it;
            }
            it++;
        }
        return path;
    }
};
void Print(vector<string> s)
{
    ifstream infile, writefile;
    infile.open("graph.txt");
    writefile.open("stops.txt");
    string line;
    if (!s.empty())
    {
        while (getline(infile, line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                char c;
                c = line[i];
                if (c == '*')
                {
                    string temp;
                    getline(writefile, temp);
                    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                    if (count(s.begin(), s.end(), temp))
                    {
                        SetConsoleTextAttribute(h, 10);
                    }
                    cout << temp;
                    SetConsoleTextAttribute(h, 7);
                }
                else if (c == ' ')
                    cout << ' ';
                else if (c == '|')
                    cout << '|';
                else if (c == '-')
                    cout << '-';
            }
            cout << endl;
        }
    }
    else
    {
        while (getline(infile, line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                char c;
                c = line[i];
                if (c == '*')
                {
                    string temp;
                    getline(writefile, temp);
                    cout << temp;
                }
                else if (c == ' ')
                    cout << ' ';
                else if (c == '|')
                    cout << '|';
                else if (c == '-')
                    cout << '-';
            }
            cout << endl;
        }
    }
    writefile.close();
    infile.close();
}
City_map creat_map(City_map &m)
{
    ifstream infile;
    infile.open("stops.txt");
    string line;
    while (getline(infile, line))
    {
        m.addNew(line);
    }
    infile.close();
    infile.open("adjencies.txt");
    string s1, s2, s3;
    while (getline(infile, line))
    {
        stringstream s(line);
        getline(s, s1, ',');
        getline(s, s2, ',');
        getline(s, s3);
        m.addNew(s1, s2, stoi(s3));
    }
    infile.close();
    return m;
}
City_map creat_map_rutes(City_map &m)
{
    ifstream infile;
    infile.open("stops.txt");
    string line;
    while (getline(infile, line))
    {
        m.addNew(line);
    }
    infile.close();
    infile.open("adjencies_rutes.txt");
    string s1, s2, s3;
    while (getline(infile, line))
    {
        stringstream s(line);
        getline(s, s1, ',');
        getline(s, s2, ',');
        getline(s, s3);
        m.addNew(s1, s2, stoi(s3));
    }
    infile.close();
    return m;
}

int main()
{
    vector<string> s;
    City_map m1, m2;
    string start;
    string end;
    m1 = creat_map(m1);
    m2 = creat_map_rutes(m2);
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t =====================================================";
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    cout << "\n\n\t\t\t\t\t\t\t\t\t  WELCOME TO OUR APP!\n";
    SetConsoleTextAttribute(h, 7);
    cout << "\n\t\t\t\t\t\t\t =====================================================\n\n";
    cout << "\n\n\t\t\t\t\t\t   DESIGNED BY:";
    cout << "\n\n\t\t\t\t\t\t\t\tHassaan Shahid\n\n\t\t\t\t\t\t\t\tFarhan Ahmed\n\n\t\t\t\t\t\t\t\tAimal Amir";
    cout << "\n\n\n\t\t\t\t\t\t\t\t     Press any key to continue.. ";
    getch();
    system("cls");
    cout << "\n\n\t\t\t\t\t\t================================================================================";
    SetConsoleTextAttribute(h, 14);
    cout << "\n\t\t\t\t\t\t\t\t                  THE METRO APP                                    ";
    SetConsoleTextAttribute(h, 7);
    cout << "\n\t\t\t\t\t\t================================================================================\n\n\n\n";
    Print(s);
    cout << endl
         << endl;
    cout << "Enter Starting Point: ";
    getline(cin, start);
    cout << "Enter Destination: ";
    getline(cin, end);
    int op;
    cout << "1- Least Time Consuming: " << endl;
    cout << "2- Most Cost Effective: " << endl;
    cin >> op;
    system("CLS");
    switch (op)
    {
    case 1:
        s = m1.Shortest_distance(start, end);
        Print(s);
        m1.rutes_dectription(s);
        break;
    case 2:
        s = m2.min_cost(start, end);
        Print(s);
        m2.rutes_dectription(s);
        break;
    }
}