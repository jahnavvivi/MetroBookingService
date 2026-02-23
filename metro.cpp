#include<bits/stdc++.h>
using namespace std;

class MetroGraph{
private:
    unordered_map<string,vector<pair<string,string>>>adj;
    unordered_map<string,vector<string>>routes;

public:
    void addRoute(string routeId,vector<string>stops){
        routes[routeId] = stops;
        for(int i=0; i<stops.size()-1; i++){
            string u=stops[i];
            string v=stops[i+1];

            adj[u].push_back({v,routeId});
            adj[v].push_back({u,routeId});
        }
    }
    bool stopExists(string stop){
        return (adj.find(stop)!=adj.end());
    }
    void displayRoutes(){
        cout<<"===== Metro Lines ====="<<endl;
        for(auto &route:routes){
            cout<<"Line: "<<route.first<<endl;
            cout<<"Stops: ";
            for(int i=0; i<route.second.size(); i++){
                cout<<route.second[i];
                if(i!=route.second.size()-1)
                    cout<<" -> ";
            }
            cout<<endl<<endl;
        }

        cout<<"Interchange Stations: ";
        for(auto &node:adj){
            if(node.second.size()>2)
                cout<<node.first<<" ";
        }
        cout<<endl;
    }

    struct State{
        int cost;
        string stop;
        string route;

        bool operator>(const State &other)const{
            return cost>other.cost;
        }
    };

    pair<vector<string>,int> findShortestPath(string source,string dest){
        unordered_map<string,int>dist;
        unordered_map<string,string>parent;
        unordered_map<string,string>usedRoute;

        for(auto &node:adj)
            dist[node.first] = INT_MAX;

        priority_queue<State,vector<State>,greater<State>>pq;

        dist[source] = 0;
        pq.push({0,source,""});

        while(!pq.empty()){
            State curr = pq.top();
            pq.pop();

            if(curr.stop==dest)
                break;

            for(auto &neighbor:adj[curr.stop]){
                string nextStop = neighbor.first;
                string routeId = neighbor.second;

                int newCost = curr.cost+1;

                if(curr.route!="" && curr.route!=routeId)
                    newCost+=1;

                if(newCost<dist[nextStop]){
                    dist[nextStop] = newCost;
                    parent[nextStop] = curr.stop;
                    usedRoute[nextStop] = routeId;
                    pq.push({newCost,nextStop,routeId});
                }
            }
        }

        vector<string>path;

        if(dist[dest]==INT_MAX)
            return {path,-1};

        string curr = dest;
        while(curr!=source){
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(source);
        reverse(path.begin(),path.end());

        int transfers = 0;
        string lastRoute = "";

        for(int i=1; i<path.size(); i++){
            string r = usedRoute[path[i]];
            if(lastRoute!="" && lastRoute!=r)
                transfers++;
            lastRoute = r;
        }

        return {path,transfers};
    }
};

class BookingService{
public:
    string generateBookingId(){
        return "book"+to_string(rand()%100000);
    }
    string generateQR(string bookingId){
        string secret = "MoveInSyncSecret";
        hash<string>hasher;
        size_t hashed = hasher(bookingId+secret);
        return bookingId + "_" + to_string(hashed);
    }
};

int main(){
    MetroGraph metro;
    BookingService bookingService;

    metro.addRoute("Blue",{"A","B","C","D"});
    metro.addRoute("Yellow",{"C","E","F","I"});
    metro.addRoute("Red",{"G","H","D","J","I"});

    int choice;

    while(true){
        cout<<endl;
        cout<<"===== Metro Booking Service ====="<<endl;
        cout<<"1. Show Metro Lines"<<endl;
        cout<<"2. Find Route"<<endl;
        cout<<"3. Create Booking"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice==1){
            metro.displayRoutes();
        }

        else if(choice==2){
            string source,destination;
            cout<<"Enter Source: ";
            cin>>source;
            cout<<"Enter Destination: ";
            cin>>destination;

            if(source == destination){
                cout<<"Source and destination are same."<<endl;
                continue;
            }
            if(!metro.stopExists(source)||!metro.stopExists(destination)){
                cout<<"Invalid stop."<<endl;
                continue;
            }

            auto result = metro.findShortestPath(source,destination);
            if(result.second == -1){
                cout<<"No path exists."<<endl;
                continue;
            }

            cout<<"Route: ";
            for(int i=0; i<result.first.size(); i++){
                cout<<result.first[i];
                if(i!=result.first.size()-1)
                    cout<<" -> ";
            }
            cout<<endl;
            cout<<"Transfers: "<<result.second<<endl;
        }

        else if(choice == 3){
            string source,destination;
            cout<<"Enter Source: ";
            cin>>source;
            cout<<"Enter Destination: ";
            cin>>destination;

            if(source == destination){
                cout<<"Source and destination are same."<<endl;
                continue;
            }
            if(!metro.stopExists(source) || !metro.stopExists(destination)){
                cout<<"Invalid stop."<<endl;
                continue;
            }
            auto result = metro.findShortestPath(source,destination);
            if(result.second == -1){
                cout<<"No path exists. Booking not created."<<endl;
                continue;
            }

            string bookingId = bookingService.generateBookingId();
            string qr = bookingService.generateQR(bookingId);

            cout<<"Booking Created Successfully!"<<endl;
            cout<<"Route: ";
            for(int i=0; i<result.first.size(); i++){
                cout<<result.first[i];
                if(i!=result.first.size()-1)
                    cout<<" -> ";
            }

            cout<<endl;
            cout<<"Transfers: "<<result.second<<endl;
            cout<<"Booking ID: "<<bookingId<<endl;
            cout<<"QR String: "<<qr<<endl;
        }

        else if(choice==4){
            cout<<"Exiting..."<<endl;
            break;
        }

        else{
            cout<<"Invalid choice."<<endl;
        }
    }

    return 0;
}