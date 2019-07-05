#include "BitStreamPool.h"
using namespace hudp;

CBitStreamPool::CBitStreamPool() {
    ExpendFree();
}

CBitStreamPool::~CBitStreamPool() {
    size_t size = _free_queue.Size();
    CBitStream* bit_stream;
    for (int i = 0; i < size; i++) {
        _free_queue.Pop(bit_stream);
        delete bit_stream;
    }
}

void CBitStreamPool::ExpendFree() {
    CBitStream* bit_stream;
    for (int i = 0; i < __init_pool_size; i++) {
        bit_stream = new CBitStream();
        _free_queue.Push(bit_stream);
    }
}

void CBitStreamPool::ReduceFree() {
    size_t size = _free_queue.Size() / 2;
    CBitStream* bit_stream;
    for (int i = 0; i < size; i++) {
        _free_queue.Pop(bit_stream);
        delete bit_stream;
    }
}

CBitStream* CBitStreamPool::GetBitStream() {
    CBitStream* bit_stream = nullptr;
    if (_free_queue.Size() == 0) {
        ExpendFree();
    }
    _free_queue.Pop(bit_stream);
    return bit_stream;
}

void CBitStreamPool::FreeBitStream(CBitStream* bit_stream) {
    bit_stream->Clear();
    _free_queue.Push(bit_stream);
}