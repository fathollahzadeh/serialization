#include "Network.h"

Network::Network(const string &config) : config(config) { }

Network::~Network() {}

void Network::readConfigFile(const string &config) {
    map<string, string> rootLeaf;
    ifstream infile;
    infile.open(config.c_str());
    string line;
    string val;
    const char separator = ',';
    while (getline(infile, line)) {
        stringstream streamData(line);
        vector<string> cols;
        while (getline(streamData, val, separator)) {
            cols.push_back(val);
        }
        string ip = cols[0];
        int port = atoi(cols[1].c_str());
        string root = cols[2];
        int nrow = atoi(cols[3].c_str());
        rootLeaf[ip] = root;
        MachineInfo *nsi = new MachineInfo(ip, port, nrow);
        machineInfos[ip] = nsi;

    }
    infile.close();
    infile.clear();

    for (auto const &rl: rootLeaf) {
        string root = rl.first;
        if (strcasecmp(root.c_str(), "root") == 0)
            continue;
        machineInfos[root]->addLeaf(machineInfos[rl.first]);
        machineInfos[rl.first]->setRoot(machineInfos[root]);
    }

    for (auto const &mi: machineInfos) {
        int sumLeaf = computeNRow(mi.second) - mi.second->getNrow();
        mi.second->setNrowLeaf(sumLeaf);
    }
}

int Network::computeNRow(MachineInfo *node) {
    if (node->getLeaves().size() == 0)
        return node->getNrow();
    else {
        int sum = node->getNrow();
        for (int i = 0; i < node->getLeaves().size(); ++i)
            sum += computeNRow(node->getLeaves().at(i));

        return sum;
    }
}

MachineInfo *Network::getCurrentMachine() {
    char host[256];
    struct hostent *host_entry;
    host_entry = gethostbyname(host); //find host information
    string ipstr(inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]))); //Convert into IP string
    return machineInfos[ipstr];
}

