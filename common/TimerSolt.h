#ifndef HEADER_COMMON_TIMERSOLT
#define HEADER_COMMON_TIMERSOLT

#include "Timer.h"

namespace hudp {

    // timer event interface
    class CTimerSolt {
    public:
        CTimerSolt() : _data(nullptr), _next(nullptr) {}
        virtual ~CTimerSolt() {}

        //*********************
        // the timer call back
        //*********************
        virtual void OnTimer(void* pt) = 0;
        
        // attach to timer
        void Attach(CTimer* timer, uint16_t ms) {
            timer->AddTimer(ms, this);
        }

        CTimerSolt* GetNext() {
            if (_next) {
                return _next;
            }
            return nullptr;
        }
        CTimerSolt* SetNext(CTimerSolt* ti) {
            _next = ti;
        }
        
        void* GetData() {
            return _data;
        };
        void SetData(void* data) {
            _data = data;
        };

    private:
        void* _data;
        CTimerSolt *_next;
    };
}

#endif