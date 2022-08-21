#include "DataReadNetwork.h"

#include <iostream>
#include "ObjectWriter.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath =argv[1];
    string method = argv[2];
    string config = argv[3];
    string plan = argv[4];
    string localMethod = "Kryo";

    if (strcasecmp(plan.c_str(), "d2d") == 0 || strcasecmp(plan.c_str(), "d2m") == 0)
        localMethod = method;

    Network network(config);
    MachineInfo *machineInfo = network.getCurrentMachine();
    ObjectReader reader(inDataPath, localMethod);

    if (machineInfo->getNodeType() == LEAF) {
        ArrayList<RootData> list = new ArrayList<>();
        reader.readObjects(0, machineInfo.getNrow(), list);
        Collections.sort(list);

        ObjectWriter writer = new ObjectWriter(method, machineInfo.getTotalNRow(), Const.NETWORK_PAGESIZE);
        Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());
        for (RootData rd : list)
            writer.writeObjectToNetworkPage(rd, client.dos, client.dis);

        writer.flushToNetwork(client.dos, client.dis);
        client.socket.close();

    }

    return 0;
}