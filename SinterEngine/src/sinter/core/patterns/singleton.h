#pragma once

// Internal
#include <sinter/core/defines.h>

namespace sinter::core
{

    template<typename T>
    class Singleton
    {
    public:
        NO_COPY(Singleton);
        NO_MOVE(Singleton);

        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

    protected:
        Singleton() = default;
        ~Singleton() = default;
    };

} // namespace sinter::core
