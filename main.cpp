#include <fstream>
#include <vector>
#include <deque>
#include <string>

void shipToPier(int pier, bool* pierData, std::deque<std::string>& shipsParked, std::deque<std::string>& shipsQueue){
    if(!shipsQueue.empty()) {
        for (int i = 0; i < pier; i++) {
            if (!pierData[i]) {
                pierData[i] = true;
                shipsParked[i] = shipsQueue.front();
                shipsQueue.erase(shipsQueue.begin());
                break;
            }
        }
    }
}

int main() {
    std::fstream fin;
    std::ofstream fout;
    fin.open("ships.in");
    fout.open("ships.out");

    if(!fin){
        fout << "Input file can't be found.";
        fin.close();
        fout.close();
        return 0;
    }

    if(fin.peek() == EOF){
        fout << "Input file is empty.";
        fin.close();
        fout.close();
        return 0;
    }

    int pier, operationId, freePier;
    std::string shipName;
    std::deque<std::string> shipsQueue;

    fin >> pier;

    std::deque<std::string> shipsParked(pier);
    bool* pierData = new bool[pier];

    for(int i = 0; i < pier; i++){
        pierData[i] = false;
    }

    while(fin.peek() != EOF){
        fin >> operationId;
        switch (operationId) {
            case 1:
                std::getline(fin, shipName);
                shipsQueue.push_back(shipName);
                shipToPier(pier, pierData, shipsParked, shipsQueue);
                break;

            case 2:
                fin >> freePier;
                pierData[freePier - 1] = false;
                shipsParked[freePier - 1] = "";
                shipToPier(pier, pierData, shipsParked, shipsQueue);
                break;

            case 3:
                if(!shipsQueue.empty()){
                    fout << "Queue is: " << std::endl;
                    for(int i = 0; i < shipsQueue.size(); i++){
                        fout << "   " << i + 1 << ". ";
                        fout << shipsQueue[i] << " " << std::endl;
                    }
                    fout << std::endl;
                }
                else{
                    fout << "No queue of ships detected." << std::endl;
                }
                fout << "-------------------------------" << std::endl;
                break;

            case 4:
                if(!shipsParked.empty()) {
                    fout << "Pier statuses: " << std::endl;
                    for (int i = 0; i < shipsParked.size(); i++) {
                        fout << "   Pier " << i + 1 << ": ";
                        if(!shipsParked[i].empty())
                            fout << shipsParked[i] << " " << std::endl;
                        else
                            fout << " This pier is empty" << std::endl;
                    }
                }
                fout << "-------------------------------" << std::endl;
                break;

            default:
                break;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
