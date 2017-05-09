#ifndef UDPINTERFACE_H
#define UDPINTERFACE_H

#include <string>
#include <stdint.h>
#include <vector>
#include "WaitMutex.h"
class UDPInterface
{
public:
    UDPInterface();
    class Address {
    public:
        Address(const std::string& address, const uint32_t port);
        const std::string address;
        const uint32_t port;
        bool operator==(const Address& other) const {
            return other.port == port && other.address==address;
        }
        bool isValid() const {
            return port>0 && address.length()>0;
        }
        operator bool() const {
            return isValid();
        }
    };
    class Datagram {
    public:
        Datagram(const char* d, const size_t l, const Address& a) : data(d), dataLen(l), address(a) {}
        const char* data;
        const size_t dataLen;
        const Address address;
    };
    // creates IO thread for this socket
    virtual void startIOThread() = 0;

    virtual bool bind(const Address&) = 0;
    // This function is thread safe
    // datagram will be put to queue and sent asap
    void sendDatagram(const unsigned char*, const size_t, const Address&);
    // This function isn't thread safe
    // datagram will be sent immediatelly using underlying socket
    // implementation
    //returns number of bytes written
    virtual int sendDatagramNow(const Datagram& d) = 0;
    // returns true if there are datagrams to be read
    virtual bool hasDatagrams() const = 0;
    // reads all incoming datagrams into given array
    virtual void readInputDatagrams(std::vector<Datagram>& input) = 0;

    virtual ~UDPInterface(){}
protected:
    // thread which sends and receives data
    virtual void datagramLoop();
    // All datagrams to be sent
    std::vector<Datagram> sendingDatagrams;
    std::vector<Datagram> receivedDatagrams;
    std::mutex dataMutex;
    // sleep until data is to be sent or is received
    // must be awoken using underlying impleentation
    // when datagram is received
    WaitMutex waitForData;
};

#endif // UDPINTERFACE_H
