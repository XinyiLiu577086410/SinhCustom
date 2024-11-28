#include "kernel_operator.h"
using namespace AscendC;
const int32_t BUFFER_NUM = 2;
class KernelSinh {
public:
    __aicore__ inline KernelSinh() {}
    __aicore__ inline void Init(GM_ADDR x, GM_ADDR y, int32_t tileNum, int32_t bufferNum, int32_t blockLength, int32_t tileLength)
    {
        //考生补充初始化代码
        m_tileNum     = tileNum; 
        m_bufferNum   = bufferNum; 
        m_blockLength = blockLength; 
        m_tileLength  = tileLength;
        this->xGm.SetGlobalBuffer((__gm__ half*)x + m_blockLength * AscendC::GetBlockIdx(), m_blockLength);
        this->yGm.SetGlobalBuffer((__gm__ half*)y + m_blockLength * AscendC::GetBlockIdx(), m_blockLength);
        this->pipe.InitBuffer(this->inQueueX,  m_bufferNum, m_tileLength * sizeof(half));
        this->pipe.InitBuffer(this->outQueueY, m_bufferNum, m_tileLength * sizeof(half));
    }
    __aicore__ inline void Process()
    {
        //考生补充对“loopCount”的定义，注意对Tiling的处理
        const int32_t loopCount = m_tileNum * m_bufferNum;
        for (int32_t i = 0; i < loopCount; i++) {
            CopyIn(i);
            Compute(i);
            CopyOut(i);
        }
    }

private:
    __aicore__ inline void CopyIn(int32_t progress)
    {
        //考生补充算子代码
        auto tensor = this->inQueueX.AllocTensor<half>();
        AscendC::DataCopy(tensor, xGm[progress * m_tileLength], m_tileLength);
        this->inQueueX.EnQue<half>(tensor); 
    }
    __aicore__ inline void Compute(int32_t progress)
    {
        //考生补充算子计算代码
        auto tensor = this->inQueueX.DeQue<half>();
        auto tensorOut = this->outQueueY.AllocTensor<half>();
        AscendC::Exp(tensor, tensor, m_tileLength);
        AscendC::Reciprocal(tensorOut, tensor, m_tileLength);
        AscendC::Sub(tensorOut, tensor, tensorOut, m_tileLength);
        AscendC::Muls(tensorOut, tensorOut, (half)0.5f, m_tileLength);
        this->outQueueY.EnQue<half>(tensorOut);
        this->inQueueX.FreeTensor(tensor);
    }
    __aicore__ inline void CopyOut(int32_t progress)
    {
        //考生补充算子代码
        auto tensor = this->outQueueY.DeQue<half>();
        AscendC::DataCopy(yGm[progress * m_tileLength], tensor, m_tileLength);
        this->outQueueY.FreeTensor(tensor);
    }

private:
    TPipe pipe;
    TQue<QuePosition::VECIN, BUFFER_NUM> inQueueX;      //create queue for input, in this case depth is equal to buffer num
    TQue<QuePosition::VECOUT, BUFFER_NUM> outQueueY;    //create queue for output, in this case depth is equal to buffer num
    GlobalTensor<half> xGm;
    GlobalTensor<half> yGm;
    //考生补充自定义成员变量
    int32_t m_tileNum; 
    int32_t m_bufferNum; 
    int32_t m_blockLength; 
    int32_t m_tileLength;

};

extern "C" __global__ __aicore__ void sinh_custom(GM_ADDR x, GM_ADDR y, GM_ADDR workspace, GM_ADDR tiling) {
    GET_TILING_DATA(tiling_data, tiling);
    KernelSinh op;
    //补充init和process函数调用内容
    op.Init(x, y, tiling_data.tileNum, tiling_data.bufferNum, tiling_data.blockLength, tiling_data.tileLength);
    op.Process();
}
