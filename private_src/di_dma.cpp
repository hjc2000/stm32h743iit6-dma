#include "Dma1Stream0.h"
#include "Dma1Stream1.h"
#include "DmaOptions.h"
#include <base/container/Dictionary.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/dma.h>
#include <bsp-interface/di/interrupt.h>
#include <map>

std::shared_ptr<bsp::IDmaOptions> DICreate_DmaOptions()
{
    return std::shared_ptr<bsp::IDmaOptions>{new bsp::DmaOptions{}};
}

namespace
{
    class Initializer
    {
    private:
        bsp::Dma1Stream0 _dma1_stream0;
        bsp::Dma1Stream1 _dma1_stream1;

        void Add(bsp::IDmaChannel *o)
        {
            _dic.Add(o->Name(), o);
        }

    public:
        Initializer()
        {
            Add(&_dma1_stream0);
            Add(&_dma1_stream1);
        }

        base::Dictionary<std::string, bsp::IDmaChannel *> _dic;
    };

    class Getter :
        public base::SingletonGetter<Initializer>
    {
    public:
        std::unique_ptr<Initializer> Create() override
        {
            return std::unique_ptr<Initializer>{new Initializer{}};
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
} // namespace

base::IDictionary<std::string, bsp::IDmaChannel *> const &DI_DmaChannelCollection()
{
    Getter g;
    return g.Instance()._dic;
}
