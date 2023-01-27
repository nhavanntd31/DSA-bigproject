#include <bits/stdc++.h>
#include "draw.h"
// #include "agorithm.h"
using namespace std;

const int maxn = 1000;

class Graph
{

public:
    vector<Vertex> vList;
    vector<pair<int, pair<int, string>>> adj[maxn]; // cạnh kề, (tên,kc)
    int numberofVertex;
    int test =0;
public:
    Graph()
    {
        numberofVertex = 0;
        initwindow(900, 700, "Visualization"); // khởi tạo cửa sổ
        setbkcolor(WHITE);                     // set backgroundcolor là white
        cleardevice();
        setcolor(BLACK); // đổi màu để vẽ thành màu đen
        drawxyAxis();    // vẽ trục tọa độ
    }
    ~Graph() = default;
    void addVertex(int x, int y, string placeName)
    { // đỉnh: tọa độ x, y, tên điểm
        // Thêm vertex đấy vào trong vector để lưu
        numberofVertex++;
        Vertex temp = {x, y, placeName};
        vList.push_back(temp);
        // B2 : vẽ lên màn hình
        drawVertex(x, y, stringToChars(placeName));
    }
    void addOneWayEdge(string name1, string name2, string streetName, string cost)
    {
        // đường 1 chiều: điểm đầu, điểm cuối, tên đường, khoảng cách
        //    Thêm đường đấy vào trong danh sách kề array adj.
        int intCost = stoi(cost);
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);    
        //    adj[index1] : là 1 cái vector chứa các thông tin của các đỉnh kề với đỉnh index1  dưới dạng {index của đỉnh,{khoảng cách, tên đường}};
        adj[index1].push_back({index2, {intCost, streetName}});
        //    Vẽ lên màn hình
        drawOneWayEdge(vList[index1], vList[index2], stringToChars(streetName), stringToChars(cost));
    }
    void addTwoWayEdge(string name1, string name2, string streetName, string cost)
    {
        // đường 2 chiều: điểm đầu, điểm cuối, tên đường, khoảng cách
        int intCost = stoi(cost);
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);
        //    adj[index1] : là 1 cái vector chứa các thông tin của các đỉnh kề với đỉnh index1  dưới dạng {index của đỉnh,{khoảng cách, tên đường}};
        adj[index1].push_back({index2, {intCost, streetName}});
        adj[index2].push_back({index1, {intCost, streetName}});
        //    Vẽ lên màn hình
        drawTwoWayEdge(vList[index1], vList[index2], stringToChars(streetName), stringToChars(cost));
    }
    void removeEdge(string streetName)
    {
        // xóa 1 đường : xóa trong danh sách kề : tốt nhất là xóa theo kiểu đường 2 chiều
        pair<int,int> info = getEdge(streetName);
        for (int i = 0;i < adj[info.first].size();i++){
            if (adj[info.first].at(i).first == info.second ) adj[info.first].erase(adj[info.first].begin()+i);
        }
        for (int i = 0;i < adj[info.second].size();i++){
            if (adj[info.second].at(i).first == info.first ) adj[info.second].erase(adj[info.first].begin()+i);
        }
        // xóa trên màn hìn
        deleteOneWayEdge(vList[info.first],vList[info.second]);
    }
    void removeVertex(string placeName)
    {
        // xóa 1 đỉnh : xóa hết các đỉnh trong vector kề của đỉnh này trong list, xóa hết đỉnh này ở mọi vector kề khác
        int index = getVertex(placeName);
        deleteVertex(vList[index]);
        while( !adj[index].empty() ) 
        {
            int temp = adj[index].back().first;
            deleteOneWayEdge(vList[index],vList[temp]);
            adj[index].pop_back();
        }
        for (int i = 0; i < numberofVertex; i++ )
        {
            if (adj[i].empty()) continue;
            for (int j = 0; j < adj[i].size(); j++) 
            {
                if (adj[i][j].first == index)
                {
                    deleteOneWayEdge(vList[i],vList[index]);
                    adj[i].erase(adj[i].begin()+j);
                }
            }
        }
        
    }
    void removeAll()
    {
        
        // xóa hết :

        for (int i = 0;i < numberofVertex;i++){
            while (!adj[i].empty()) adj[i].pop_back();
        }
        while (!vList.empty()) vList.pop_back();
        // xóa hết màn hình , vẽ lại trục tọa độ
        cleardevice();
        drawxyAxis();
        cout << "Remove All" << endl;
    };
    vector<int> getShortestWay(string name1, string name2)
    {
        vector<int> temp;
        temp.push_back(1);
    };
    void highlightWay(vector<int> path)
    {
        cout << "Highlight Way" << endl;
    }
    void unhighlightWay(vector<int> path)
    {
        cout << "Un-highlight Way" << endl;
    }
    void dfs(); // Minh
    void printList()
    {
        for (int i = 0; i < numberofVertex; i++)
        {   
            if (adj[i].empty()) continue;
            cout << vList[i].name << ":"
                 << " ";
            for (auto x : adj[i])
            {
                cout << "{" << vList[x.first].name << ",{" << x.second.first << "," << x.second.second << "},";
            }
            cout << endl;
        }
    }
    int getVertex(string name)
    {
        string temp;
        for (int i = 0; i < numberofVertex; i++)
        {
            string temp = vList[i].name;
            if (temp == name)
                return i;
        }
        return -1;
    }

    int getCost(string name1, string name2)
    {
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);
        for (auto x : adj[index1])
        {
            if (index2 == x.first)
                return x.second.first;
        }
    };
    pair<int, int> getEdge(string name)
    {
        for (int i = 0; i < numberofVertex; i++)
        {
            for (auto x : adj[i])
            {
                if (x.second.second == name)
                    return {i, x.first};
            }
        }
    }
};

// Mai
class Menu
{

private:
    Graph graph1;

public:
    void AddPlace()
    {

        int x, y;
        string name;
        system("cls");
        cout << "=== ADD PLACE ===" << endl;
        cout << "Codinates: ";
        cin >> x >> y;
        cout << "Name: ";
        fflush(stdin);
        getline(cin, name);
        graph1.addVertex(x, y, name);
        // system("pause");
    };
    void AddWay()
    {
        int option;
        string s1, s2, name, distance;
        do
        {
            cout << "=== ADD WAY ===" << endl;
            cout << "1. Add two-way street" << endl;
            cout << "2. Add one-way street" << endl;
            cout << "0. Back" << endl;
            cin >> option;
            system("cls");
            switch (option)
            {
            case 1:
                cout << "=== ADD TWO-WAY STREET ===" << endl;
                cout << "Way between 2 place" << endl;
                cout << "from: ";
                fflush(stdin);
                getline(cin, s1);
                cout << "to: ";
                fflush(stdin);
                getline(cin, s2);
                cout << "Name of the way: ";
                fflush(stdin);
                getline(cin, name);
                cout << "Distance: ";
                cin >> distance;
                graph1.addTwoWayEdge(s1, s2, name, distance);
                // system("pause");
                break;
            case 2:
                cout << "=== ADD ONE-WAY STREET ===" << endl;
                cout << "Way between 2 place" << endl;
                cout << "from: ";
                fflush(stdin);
                getline(cin, s1);
                cout << "to: ";
                fflush(stdin);
                getline(cin, s2);
                cout << "Name of the way: ";
                fflush(stdin);
                getline(cin, name);
                cout << "Distance: ";
                cin >> distance;
                graph1.addOneWayEdge(s1, s2, name, distance);
                // system("pause");
                break;
            default:
                break;
            }
        } while (option != 0);
    };
    void Remove()
    {
        string p, w;
        int option;
        do
        {
            cout << "=== REMOVE ===" << endl;
            cout << "1. Revome a place" << endl;
            cout << "2. Remove a way" << endl;
            cout << "3. Remove all" << endl;
            cout << "0. Back" << endl;
            cin >> option;
            system("cls");
            switch (option)
            {
            case 1:
                cout << "=== REMOVE A PLACE ===" << endl;
                cout << "Enter place: ";
                fflush(stdin);
                getline(cin, p);
                graph1.removeVertex(p);
                system("pause");
                break;
            case 2:
                cout << "=== REMOVE A WAY ===" << endl;
                cout << "Enter name of the way: ";
                fflush(stdin);
                getline(cin, w);
                graph1.removeEdge(w);
                system("pause");
                break;
            case 3:
                cout << "=== REMOVE ALL ===" << endl;
                graph1.removeAll();
                break;
            default:
                break;
            }
        } while (option != 0);
    };
    void Edit()
    {
        // string w, p, place;
        // int way, option;
        // do
        // {
        //     cout << "=== EDIT INFO ===" << endl;
        //     cout << "1. Edit name of a place";
        //     cout << "2. Edit distance of a way";
        //     cout << "0. Back";
        //     cin >> option;
        //     switch (option)
        //     {
        //     case 1:
        //         cout << "Edit name of a place: ";
        //         getline(cin, p);
        //         // place.getVertex(p);
        //         break;
        //     case 2:
        //         cout << " Edit distance of a way";
        //         break;
        //     default:
        //         break;
        //     }
        // } while (option != 0);
        graph1.printList();
        system("pause");
    };
    void Hightlight()
    {
        // fflush(stdin);
        string begin, end;
        cout << "=== FIND SHORTEST WAY ===" << endl;
        cout << "from: ";
        getline(cin, begin);
        fflush(stdin);
        cout << " to: ";
        getline(cin, end);

        vector<int> path = graph1.getShortestWay(begin, end);
        graph1.highlightWay(path);
        system("pause");
        graph1.unhighlightWay(path);
    };
};

int main()
{
    int option;
    Menu menu1;
    do {
        system("cls");
        cout << "==== MAPS ====" << endl;
        cout << "1. Add place" << endl;
        cout << "2. Add way" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Print adjacency list" << endl;
        cout << "5. Highlight" << endl;
        cout << "0. Exit" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            menu1.AddPlace();
            break;
        case 2:
            menu1.AddWay();
            break;
        case 3:
            menu1.Remove();
            break;
        case 4:
            menu1.Edit();
            break;
        case 5:
            menu1.Hightlight();
            break;
        default:
            break;
        }
    } while (option!=0);
    // Graph graph1;
    // graph1.addVertex(200, 200, "DHBK");
    // graph1.addVertex(400, 400, "DHKTQD");
    // // cout << graph1.getVertex("DHBK");
    // // graph1.printList();
    // graph1.addOneWayEdge("DHBK", "DHKTQD", "TDN", "500");
    // // highlightVertex(graph1.vList[0]);

    // // highlightEdge(graph1.vList[0],graph1.vList[1]);
    // graph1.removeEdge("TDN");
    // getch();
    // closegraph();
    return 0;
}