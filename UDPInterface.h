#ifndef UDPINTERFACE_H
#define UDPINTERFACE_H

#include <string>
#include <stdint.h>
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
//    class Datagram {
//        Datagram()

//        const unsigned char* data;
//        const bool isChecked;
//        const int repeatTimeout;
//        const int repeatCount;
//        int attampts;
//    };

    bool bind(const Address&);
    int sendDatagram();
};

#endif // UDPINTERFACE_H
