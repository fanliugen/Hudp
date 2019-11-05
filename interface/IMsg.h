#ifndef HEADER_INTERFACE_MSG
#define HEADER_INTERFACE_MSG

#include "CommonType.h"

namespace hudp {
    // msg base class.
    class CMsg
    {
    public:
        CMsg() {}
        virtual ~CMsg() {}
        // translate user flag to hudp flag.
        virtual void TranslateFlag() = 0;
        
        virtual void SetFlag(uint16_t flag) = 0;
        virtual uint16_t GetFlag() = 0;

        virtual void SetHandle(const Handle& handle) = 0;
        virtual const Handle& GetHandle() = 0;
        
        virtual void SetBody(const std::string& body) = 0;
        virtual std::string& GetBody() = 0;

        // get buffer that is serialized
        virtual bool GetSerializeBuffer(char* buf, uint16_t& len) = 0;
    };
}
#endif