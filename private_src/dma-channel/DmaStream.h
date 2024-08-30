#pragma once
#include <bsp-interface/dma/IDmaChannel.h>
#include <hal.h>

namespace bsp
{
    class DmaStream :
        public bsp::IDmaChannel
    {
    private:
        void LinkDmaToUartTx(UART_HandleTypeDef &uart);
        void LinkDmaToUartRx(UART_HandleTypeDef &uart);

    protected:
        DMA_HandleTypeDef _dma_handle{};

    public:
        /// @brief 剩余的未传输的字节数。
        /// @note 将本次启动 DMA 所设置的目标传输字节数减去本属性，即可得到传输了多少个字节。
        /// @return
        int RemainingUntransmittedBytes() override
        {
            return __HAL_DMA_GET_COUNTER(&_dma_handle);
        }

        void LinkDmaToParent(void *parent);
    };
} // namespace bsp
