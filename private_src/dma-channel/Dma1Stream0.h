#pragma once
#include <base/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <DmaStream.h>

namespace bsp
{
    class Dma1Stream0 :
        public bsp::DmaStream
    {
    private:
        bool _is_open = false;

    public:
        static Dma1Stream0 &Instance();

        std::string Name() const override;
        void Open(bsp::IDmaOptions const &options, void *parent) override;

        bool IsOpen() const override
        {
            return _is_open;
        }

        void Close() override
        {
            _is_open = false;
        }
    };
} // namespace bsp
