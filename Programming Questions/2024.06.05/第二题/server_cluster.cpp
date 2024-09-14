#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Server {
    int id;
    int files;
};

bool compareServers(const Server &a, const Server &b){
    return a.id< b.id;
}

int main(){
    string line;

    // 读取第一行服务器信息
    getline(cin, line);
    stringstream ss(line);
    vector<Server> servers;
    string serverInfo;

    while(ss >> serverInfo){
        int id, files;
        sscanf(serverInfo.c_str(),"%d,%d",&id, &files);
        servers.push_back({id, files});
    }

    sort(servers.begin(),servers.end(), compareServers);

    // 读取第二行操作信息
    getline(cin, line);
    stringstream ssOps(line);
    string operation;
    vector<string> operations;
    
    while(ssOps >> operation){
        operations.push_back(operation);
    }

    for(size_t i=0;i < operations.size();++i){
        if(operations[i]=="d"){
            int id = stoi(operations[++i]);
            auto it = find_if(servers.begin(), servers.end(),[id](const Server &s){ return s.id == id; });
            if(it != servers.end()){
                int nextIndex = (it-servers.begin()+ 1) % servers.size();
                servers[nextIndex].files += it->files;
                servers.erase(it);
            }
        }else if(operations[i]== "i"){
            int id= stoi(operations[++i]);
            int files = stoi(operations[++i]);
            auto it = lower_bound(servers.begin(),servers.end(), id, [](const Server &s,int id){ return s.id < id; });
            int nextIndex=(it-servers.begin()) % servers.size();
            if(it != servers.end()){
                servers[nextIndex].files -= files;
                servers.insert(it, {id, files});
            }else{
                servers[0].files -= files;
                servers.push_back({id, files});
                sort(servers.begin(),servers.end(),compareServers);
            }
        }
    }

    vector<Server> result;
    int maxFiles =0;

    for(const auto &server : servers){
        if(server.files >maxFiles){
            result.clear();
            result.push_back(server);
            maxFiles = server.files;
        }else if(server.files == maxFiles){
            result.push_back(server);
        }
    }

    for(size_t i=0;i < result.size();++i){
        if(i > 0) cout << " ";
        cout << result[i].id << ","<< result[i].files;
    }
    cout << endl;

    return 0;

}