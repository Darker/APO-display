#include "UDPInterface.h"

UDPInterface::UDPInterface()
{

}

void UDPInterface::sendDatagram(const unsigned char* d, const size_t len, const UDPInterface::Address& a)
{
    sendingDatagrams.push_back(Datagram((const char*)d, len, a));
}

void UDPInterface::datagramLoop()
{
    waitForData.wait();
    dataMutex.lock();
    if(sendingDatagrams.size()>0) {
        for(size_t i=0, l=sendingDatagrams.size(); i<l; ++i) {
            sendDatagramNow(sendingDatagrams[i]);
        }
        sendingDatagrams.clear();
    }

    dataMutex.unlock();
}
