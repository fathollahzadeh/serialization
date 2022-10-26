#ifndef CPP_MACHINEINFO_H
#define CPP_MACHINEINFO_H

#include <iostream>
#include <vector>
#include "Const.h"

using namespace std;

class MachineInfo {

private:
    string ip;
    int port;
    MachineInfo *root;
    int nrow;
    int nrowLeaf;
    vector<MachineInfo*> leaves;

public:
    MachineInfo();

    MachineInfo(const string &ip, int port, int nrow);

    virtual ~MachineInfo();

    NodeType getNodeType();

    int getTotalNRow();

    const string &getIp() const;

    void setIp(const string &ip);

    int getPort() const;

    void setPort(int port);

    MachineInfo *getRoot() const;

    void setRoot(MachineInfo *root);

    int getNrow() const;

    void setNrow(int nrow);

    int getNrowLeaf() const;

    void setNrowLeaf(int nrowLeaf);

    const vector<MachineInfo *> &getLeaves() const;

    void setLeaves(const vector<MachineInfo *> &leaves);

    void addLeaf(MachineInfo * leaf);

};


#endif //CPP_MACHINEINFO_H
