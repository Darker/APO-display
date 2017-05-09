#include "QtUDP.h"

QtUDP::QtUDP()
{

}

int QtUDP::sendDatagramNow(const UDPInterface::Datagram& d)
{
    internalSocket.writeDatagram(d.data, d.address.address, d.address.port);
}

bool QtUDP::hasDatagrams() const
{
    return internalSocket.hasPendingDatagrams();
}

void QtUDP::readInputDatagrams(std::vector<UDPInterface::Datagram>& input)
{
    while(internalSocket.hasPendingDatagrams()) {
        //todo
    }
}
