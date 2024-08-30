#include "DmaStream.h"
#include <stdexcept>

void bsp::DmaStream::LinkDmaToUartTx(UART_HandleTypeDef &uart)
{
    uart.hdmatx = &_dma_handle;
    _dma_handle.Parent = &uart;
}

void bsp::DmaStream::LinkDmaToUartRx(UART_HandleTypeDef &uart)
{
    uart.hdmarx = &_dma_handle;
    _dma_handle.Parent = &uart;
}

void bsp::DmaStream::LinkDmaToParent(void *parent)
{
    switch (_dma_handle.Init.Request)
    {
    case DMA_REQUEST_USART1_TX:
        {
            LinkDmaToUartTx(*static_cast<UART_HandleTypeDef *>(parent));
            break;
        }
    case DMA_REQUEST_USART1_RX:
        {
            LinkDmaToUartRx(*static_cast<UART_HandleTypeDef *>(parent));
            break;
        }
    default:
        {
            throw std::runtime_error{"不支持的请求"};
        }
    }
}
