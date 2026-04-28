#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct RedGroup
{
    string name;
    vector<int> redTypes;
};

struct Button
{
    string name;
    unordered_set<int> bindRedTypes;
    unordered_set<int> bindGroups;
};

struct Panel
{
    string name;
    vector<int> buttons;
};

class RedDotSystem
{
private:
    int N, M, X, Y;

    vector<string> redNames;
    vector<int> redState;

    vector<RedGroup> groups;
    vector<Button> buttons;
    vector<Panel> panels;

    unordered_map<string, int> redId;
    unordered_map<string, int> groupId;
    unordered_map<string, int> buttonId;
    unordered_map<string, int> panelId;

    vector<int> groupState;
    vector<int> buttonState;
    vector<int> panelState;

public:
    RedDotSystem(int n, int m, int x, int y)
        : N(n), M(m), X(x), Y(y)
    {
        redNames.resize(N);
        redState.resize(N);

        groups.resize(M);
        buttons.resize(X);
        panels.resize(Y);

        groupState.resize(M);
        buttonState.resize(X);
        panelState.resize(Y);
    }

    void readRedTypes()
    {
        for (int i = 0; i < N; i++)
        {
            cin >> redNames[i] >> redState[i];
            redId[redNames[i]] = i;
        }
    }

    void readGroups()
    {
        for (int i = 0; i < M; i++)
        {
            string name;
            int num;
            cin >> name >> num;

            groups[i].name = name;
            groupId[name] = i;

            for (int j = 0; j < num; j++)
            {
                string redName;
                cin >> redName;
                groups[i].redTypes.push_back(redId[redName]);
            }
        }
    }

    void readButtons()
    {
        for (int i = 0; i < X; i++)
        {
            string name;
            int num;
            cin >> name >> num;

            buttons[i].name = name;
            buttonId[name] = i;

            for (int j = 0; j < num; j++)
            {
                string bindName;
                cin >> bindName;

                if (redId.count(bindName))
                {
                    buttons[i].bindRedTypes.insert(redId[bindName]);
                }
                else if (groupId.count(bindName))
                {
                    buttons[i].bindGroups.insert(groupId[bindName]);
                }
            }
        }
    }

    void readPanels()
    {
        for (int i = 0; i < Y; i++)
        {
            string name;
            int num;
            cin >> name >> num;

            panels[i].name = name;
            panelId[name] = i;

            for (int j = 0; j < num; j++)
            {
                string btnName;
                cin >> btnName;
                panels[i].buttons.push_back(buttonId[btnName]);
            }
        }
    }

    vector<int> calcPanelState()
    {
        // 1. 计算红点类型集合状态
        for (int i = 0; i < M; i++)
        {
            groupState[i] = 0;
            for (int red : groups[i].redTypes)
            {
                if (redState[red])
                {
                    groupState[i] = 1;
                    break;
                }
            }
        }

        // 2. 计算按钮状态
        for (int i = 0; i < X; i++)
        {
            buttonState[i] = 0;

            for (int red : buttons[i].bindRedTypes)
            {
                if (redState[red])
                {
                    buttonState[i] = 1;
                    break;
                }
            }

            if (buttonState[i])
                continue;

            for (int group : buttons[i].bindGroups)
            {
                if (groupState[group])
                {
                    buttonState[i] = 1;
                    break;
                }
            }
        }

        // 3. 计算界面状态
        vector<int> result(Y, 0);

        for (int i = 0; i < Y; i++)
        {
            for (int btn : panels[i].buttons)
            {
                if (buttonState[btn])
                {
                    result[i] = 1;
                    break;
                }
            }
        }

        return result;
    }

    void showRed(const string &name)
    {
        if (redId.count(name))
        {
            redState[redId[name]] = 1;
        }
    }

    void hideRed(const string &name)
    {
        if (redId.count(name))
        {
            redState[redId[name]] = 0;
        }
    }

    void removeBind(const string &btnName, const string &bindName)
    {
        if (!buttonId.count(btnName))
            return;

        int btn = buttonId[btnName];

        if (redId.count(bindName))
        {
            buttons[btn].bindRedTypes.erase(redId[bindName]);
        }
        else if (groupId.count(bindName))
        {
            buttons[btn].bindGroups.erase(groupId[bindName]);
        }
    }

    void addBind(const string &btnName, const string &bindName)
    {
        if (!buttonId.count(btnName))
            return;

        int btn = buttonId[btnName];

        if (redId.count(bindName))
        {
            buttons[btn].bindRedTypes.insert(redId[bindName]);
        }
        else if (groupId.count(bindName))
        {
            buttons[btn].bindGroups.insert(groupId[bindName]);
        }
    }

    void ask(const string &name)
    {
        calcPanelState();

        if (buttonId.count(name))
        {
            int btn = buttonId[name];
            cout << (buttonState[btn] ? "YES" : "NO") << '\n';
        }
        else if (panelId.count(name))
        {
            int panel = panelId[name];
            cout << (panelState[panel] ? "YES" : "NO") << '\n';
        }
    }

    void executeOperation(const string &op)
    {
        vector<int> before = calcPanelState();

        if (op == "Show")
        {
            string name;
            cin >> name;
            showRed(name);
        }
        else if (op == "Hide")
        {
            string name;
            cin >> name;
            hideRed(name);
        }
        else if (op == "Remove")
        {
            string btnName, bindName;
            cin >> btnName >> bindName;
            removeBind(btnName, bindName);
        }
        else if (op == "Bind")
        {
            string btnName, bindName;
            cin >> btnName >> bindName;
            addBind(btnName, bindName);
        }
        else if (op == "Ask")
        {
            string name;
            cin >> name;

            vector<int> now = calcPanelState();

            if (buttonId.count(name))
            {
                int btn = buttonId[name];
                cout << (buttonState[btn] ? "YES" : "NO") << '\n';
            }
            else if (panelId.count(name))
            {
                int panel = panelId[name];
                cout << (now[panel] ? "YES" : "NO") << '\n';
            }

            return;
        }

        vector<int> after = calcPanelState();

        for (int i = 0; i < Y; i++)
        {
            if (before[i] == 1 && after[i] == 0)
            {
                cout << panels[i].name << '\n';
            }
        }

        panelState = after;
    }

    void initState()
    {
        panelState = calcPanelState();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, X, Y;
    cin >> N >> M >> X >> Y;

    RedDotSystem system(N, M, X, Y);

    system.readRedTypes();
    system.readGroups();
    system.readButtons();
    system.readPanels();

    system.initState();

    int S;
    cin >> S;

    while (S--)
    {
        string op;
        cin >> op;
        system.executeOperation(op);
    }

    return 0;
}