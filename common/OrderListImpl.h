#ifndef HEADER_COMMON_ORDERLIST
#define HEADER_COMMON_ORDERLIST

#include <mutex>

#include "TSQueue.h"
#include "CommonType.h"
#include "IOrderList.h"
#include "HudpConfig.h"

namespace hudp {
    
    class CMsg;
    // order list base class
    class CRecvList : public COrderList {
    public:
        CRecvList();
        virtual ~CRecvList();

        virtual void Clear() {}
        // add a item to order list
        // return 0, msg is normal
        // return 1, repeat msg
        // return 2, continuously disordered messages
        virtual uint16_t Insert(std::shared_ptr<CMsg> msg) = 0;

        // make id little than order list max size
        uint16_t HashFunc(uint16_t id);
    protected:
        uint16_t _discard_msg_count;
    };

    // receive list that reliable and orderly 
    class CReliableOrderlyList : public CRecvList {
    public:
        CReliableOrderlyList(uint16_t start_id);
        virtual ~CReliableOrderlyList();
        virtual void Clear();
        // add a item to order list
        // return 0 if success
        // return 1 if msg is repeat
        virtual uint16_t Insert(std::shared_ptr<CMsg> msg);
    private:
        std::mutex _mutex;
        uint16_t _expect_id;

        std::shared_ptr<CMsg> _order_list[__msx_cache_msg_num];
        base::CTSQueue<std::shared_ptr<CMsg>> _recv_list;
    };

    //  receive list that only reliable
    class CReliableList : public CRecvList {
    public:
        CReliableList(uint16_t start_id);
        virtual ~CReliableList();
        // add a item to order list
        // return 0 if success
        // return 1 if msg is repeat
        virtual uint16_t Insert(std::shared_ptr<CMsg> msg);
    private:
        std::mutex _mutex;
        uint16_t   _order_list[__msx_cache_msg_num];
        uint16_t   _expect_id;
    };

    // receive list that only orderly
    class COrderlyList : public CRecvList {
    public:
        COrderlyList(uint16_t start_id);
        virtual ~COrderlyList();
        // add a item to order list
        // always return 0
        virtual uint16_t Insert(std::shared_ptr<CMsg> msg);
    private:
        uint16_t _expect_id;
    };
}
#endif
