#include "MachineInfo.h"

MachineInfo::MachineInfo() {
    this->root = nullptr;
}

MachineInfo::~MachineInfo() {}

MachineInfo::MachineInfo(const string &ip, int port, int nrow){
    this->ip = ip;
    this->port = port;
    this->nrow = nrow;
    this->nrowLeaf = 0;
}

NodeType MachineInfo::getNodeType() {
   if (root == nullptr)
        return ROOT;
    else if (leaves.empty())
        return LEAF;
    else
        return MIDDLE;
}

int MachineInfo::getTotalNRow() {
    return nrow + nrowLeaf;
}

const string &MachineInfo::getIp() const {
    return ip;
}

void MachineInfo::setIp(const string &ip) {
    MachineInfo::ip = ip;
}

int MachineInfo::getPort() const {
    return port;
}

void MachineInfo::setPort(int port) {
    MachineInfo::port = port;
}

MachineInfo *MachineInfo::getRoot() const {
    return root;
}

void MachineInfo::setRoot(MachineInfo *root) {
    MachineInfo::root = root;
}

int MachineInfo::getNrow() const {
    return nrow;
}

void MachineInfo::setNrow(int nrow) {
    MachineInfo::nrow = nrow;
}

int MachineInfo::getNrowLeaf() const {
    return nrowLeaf;
}

void MachineInfo::setNrowLeaf(int nrowLeaf) {
    MachineInfo::nrowLeaf = nrowLeaf;
}

const vector<MachineInfo *> &MachineInfo::getLeaves() const {
    return leaves;
}

void MachineInfo::setLeaves(const vector<MachineInfo *> &leaves) {
    MachineInfo::leaves = leaves;
}

void MachineInfo::addLeaf(MachineInfo * leaf) {
    this->leaves.push_back(leaf);
}
