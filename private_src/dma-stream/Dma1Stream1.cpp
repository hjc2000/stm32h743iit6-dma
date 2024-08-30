#include "Dma1Stream1.h"
#include "DmaOptions.h"

bsp::Dma1Stream1 &bsp::Dma1Stream1::Instance()
{
    class Getter : public base::SingletonGetter<Dma1Stream1>
    {
    public:
        std::unique_ptr<Dma1Stream1> Create() override
        {
            return std::unique_ptr<Dma1Stream1>{new Dma1Stream1{}};
        }

        void Lock() override
        {
            DI_InterruptSwitch().DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_InterruptSwitch().EnableGlobalInterrupt();
        }
    };

    Getter o;
    return o.Instance();
}

std::string bsp::Dma1Stream1::Name() const
{
    return "dma1_stream1";
}

void bsp::Dma1Stream1::Open(bsp::IDmaOptions const &options, void *parent)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭才能再次打开"};
    }

    _is_open = true;

    __HAL_RCC_DMA1_CLK_ENABLE();
    _dma_handle.Instance = DMA1_Stream1;
    _dma_handle.Init = static_cast<bsp::DmaOptions const &>(options);
    HAL_DMA_Init(&_dma_handle);
    LinkDmaToParent(parent);
}
