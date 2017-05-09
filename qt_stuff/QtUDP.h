#ifndef QTUDP_H
#define QTUDP_H
#include "../UDPInterface.h"
#include <QUdpSocket>
class QtUDP: public UDPInterface
{
public:
    // This function isn't thread safe
    // datagram will be sent immediatelly using underlying socket
    // implementation
    //returns number of bytes written
    int sendDatagramNow(const Datagram& d) override;
    // returns true if there are datagrams to be read
    bool hasDatagrams() const override;
    // reads all incoming datagrams into given array
    void readInputDatagrams(std::vector<Datagram>& input) override;
protected:
    QUdpSocket internalSocket;
    // thread used to notify socket thread that datagrams are available
    QThread notifyThread;
};

#endif // QTUDP_H
