#include "DmaStream.h"

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
